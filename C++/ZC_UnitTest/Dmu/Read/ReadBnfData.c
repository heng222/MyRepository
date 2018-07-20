/*************************************************
  文件名   ：ReadBnfData.c
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： 读Bnf配置数据头文件
			DmuCommonRead组件的功能可分解如下：
			1）	读取二进制文件并且保存到内存
			2）	获取二进制文件数据标识；
			3）	获取二进制文件CRC；
			4）	获取二进制文件线路编号；
			5）	获取二进制文件中此输入类型的数据长度和对应的index；
			6）	获取二进制文件中此输入类型的数据信息；
			7）	获取系统间要比较的数据文件的版本号；
			8）	获取数据子表的版本号；
			9）	获取系统间要比较的数据文件的CRC。
  备注    ：无。 
*************************************************/

#include "ReadBnfData.h"
#include "ReadDataTypeDefine.h"
#include "../../Common/Copy.h"
#include "../../Common/Malloc.h"
#include "../DmuComm/DataHandle/DmuCommDataTypeDefine.h"
#include "../../Common/CRC32.h"
#include "../../PlatformAdapter/AppItf/AdptAppFileInterface.h"

#ifdef PLATFORM_ARTESYN_FILEOPERATION
#include "../../cspadpt/Vcp_File_Interface.h"
#endif

static BnfDataHeadStruct  BnfDataDHStru;
static UINT8_S IsDataRead = 0u;
static UINT16_S IndexNumber = 0u;/*索引个数*/
static UINT8_S gSubTabVerIndexNum = 0u;       /*数据子表版本号索引个数*/
static UINT8_S gInterSysCmpVerIndexNum = 0u;  /*系统间比较数据版本的个数*/

/*存储二进制文件表数据数组*/
static BnfDataParseStruct* ReadDataStru = NULL;
static SubTabVersionStruct* gpSubTabVersionStru = NULL;
static InterSysCmpVerStruct  * gpInterSysCmpVerStru = NULL;

/**********************内部使用函数声明START*****************************/
static void  ReadBnfDataHeadFromBnfByte(const UINT8_S *pBnfData,BnfDataHeadStruct * pDadaHead);
static INT8_S  ReadBnfDataWriteStru(const UINT8_S* pdata,const INT32_S dataHeadLen);
static void  ReadBnfDataSubTabVersion(const UINT8_S *pBnfData);
static void  ReadBnfDataSubTabVersion(const UINT8_S *pBnfData);
/***********************内部使用函数声明END******************************/

/*********************************************
*函数功能：从二进制数据中读取数据头
*参数说明：
*输入参数:pBnfData是二进制数据地址
*输出参数:pDadaHead是存储数据头结构指针    
*返回值：无
*********************************************/
static void  ReadBnfDataHeadFromBnfByte(const UINT8_S *pBnfData,BnfDataHeadStruct * pDadaHead)
{
    if((NULL != pBnfData) && (NULL != pDadaHead))
    {
        /*读取数据标识*/
        pDadaHead->dataSignNum = LongFromChar(pBnfData);
        pBnfData += 4;

        /*读取数据版本*/
        pDadaHead->dataFileVersion = LongFromChar(pBnfData);
        pBnfData += 4;
        
        /*读取整个文件CRC*/
        pDadaHead->crc = LongFromChar(pBnfData);
        pBnfData += 4;
            
        /*读取数据长度*/
        pDadaHead->dataLength = LongFromChar(pBnfData);
    }
}

/*********************************************
*函数功能：从二进制数据中读取系统间数据校验版本号
*参数说明：
*输入参数:pBnfData是二进制数据地址
*返回值：无
*********************************************/
static void  ReadInterSysCmpVersion(const UINT8_S *pBnfData)
{
    UINT8_S i = 0u;/*循环使用*/
    if(NULL != pBnfData)
    {
        gInterSysCmpVerIndexNum = *pBnfData;
        pBnfData++;

        if (gInterSysCmpVerIndexNum > 0u)
        {
            gpInterSysCmpVerStru = (InterSysCmpVerStruct*)MemoryMalloc((UINT32_S)sizeof(InterSysCmpVerStruct) * gInterSysCmpVerIndexNum);
            
            if(NULL != gpInterSysCmpVerStru)
            {
                for (i = 0u; i < gInterSysCmpVerIndexNum; i++)
                {
                    /*读取版本号*/
                    gpInterSysCmpVerStru[i].cmpDataFileVersion = LongFromChar(pBnfData);
                    pBnfData += 4;
                }
            }
        }
        
    }

}


    /*********************************************
*函数功能：从二进制数据中读取各自表数据版本号
*参数说明：
*输入参数:pBnfData是二进制数据地址
*返回值：无
*********************************************/
static void  ReadBnfDataSubTabVersion(const UINT8_S *pBnfData)
{
    UINT8_S i = 0u;/*循环使用*/
    if(NULL != pBnfData)
    {
        gSubTabVerIndexNum = *pBnfData;
        pBnfData++;

        if (gSubTabVerIndexNum > 0u)
        {
            gpSubTabVersionStru = (SubTabVersionStruct*)MemoryMalloc( (UINT32_S)sizeof(SubTabVersionStruct) * gSubTabVerIndexNum );
            
            if(NULL != gpSubTabVersionStru)
            {
                for (i = 0u; i < gSubTabVerIndexNum; i++)
                {
                    /*比较版本类型:如ZC-CI*/
                    gpSubTabVersionStru[i].subTabType = *pBnfData;
                    pBnfData++;

                    gpSubTabVersionStru[i].subTabDataVer = LongFromChar(pBnfData);
                    pBnfData += 4;

                    gpSubTabVersionStru[i].subTabDataCrc = LongFromChar(pBnfData);
                    pBnfData += 4;

                }
            }
        }

    }

}
/*********************************************
* 函数功能 ：读取二进制文件并且保存到内存
* 参数说明 ：
* 输入参数 :bnfFileName 二进制文件地址
* 返回值：0:成功
*         1:打开二进制文件失败
          2:读取二进制文件失败
          3:校验失败，版本号不一致
          5:二进制数据文件的地址为空
          -1数据读取不成功
          -2读取数据的总长度不一致
**********************************/
INT8_S ReadBnfData(const CHAR_S * bnfFileName)
{
    INT8_S retVal = 0;/*函数返回值*/
    UINT32_S tmpDataLen = 0u;/*数据长度*/
    UINT32_S tempRetVal = 0;/*临时存放函数返回值*/
    UINT32_S cRCresult = 0u;   /*校验码*/
    FILEType pfile = NULL;/*初始化*/
    UINT8_S* pBnfData = NULL;
    INT32_S index = 0;
	
#ifdef PLATFORM_ARTESYN_FILEOPERATION
    UINT8*  Bnf_CFG_Addr = NULL; 
	UINT32* Bnf_CFG_Size = 0u;
    GM_BOOL  result = GM_FALSE;
	UINT32_S l_Addr = 0U;
#endif

#ifndef PLATFORM_ARTESYN_FILEOPERATION
	pBnfData = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S) * BNF_MAX_FILE_LEN);
#endif

#ifdef PLATFORM_ARTESYN_FILEOPERATION
    if((0 == IsDataRead)&&(bnfFileName != NULL))
    {
#else
    if((NULL != pBnfData)&&(0 == IsDataRead)&&(bnfFileName != NULL))
    {
#endif

#ifdef PLATFORM_ARTESYN_FILEOPERATION
    /* 雅特生平台 20180529 */
	result = CSPADPT_Get_SpeciConfig_Addr_Size( ENUM_CONFIG_DAT_TYPE_CIAPP,(UINT8_S*)(&l_Addr), &tmpDataLen);
	
	if ((GM_TRUE == result) && (tmpDataLen > 0u))
	{
		/*读取成功，继续执行*/
		pBnfData = (UINT8_S*)l_Addr;
        retVal = 0;
		
	}
	else
	{
		/*记录文件读取失败的错误*/
		retVal = 2;
	}
#else
        /*打开二进制文件*/
        tempRetVal = AdptAppFileOpen(bnfFileName,0,&pfile);
        /*判断打开二进制文件是否成功*/
        if (1 == tempRetVal)
        {
            tmpDataLen = AdptAppFileRead(pfile,bnfFileName,pBnfData,BNF_MAX_FILE_LEN);
            if(tmpDataLen > 0u)
            {
                /*读取成功，继续执行*/
                retVal = 0;
            }
            else
            {
                /*记录文件读取失败的错误*/
                retVal = 2;
            }
            AdptAppFileClose(pfile);
        }
        else
        {
            /*打开二进制文件失败*/
            retVal = 1;
        }
#endif
    }
    else
    {
        if (bnfFileName == NULL)
        {
            /*二进制数据文件的地址为空*/
            retVal = 5;
        }
        else
        {
            /*此二进制文件已经读取*/
        }
    }
        
    if((0 == retVal) && (NULL != pBnfData))    
    {
        /*解析数据头*/
        ReadBnfDataHeadFromBnfByte(pBnfData,&BnfDataDHStru);         
        

        /*CRC计算,除数据标识和CRC本身剩余的部分*/
        cRCresult = Crc32(&pBnfData[BNF_FILE_CRCDATA_INDEX], BnfDataDHStru.dataLength+4u);
        /*CRC校验*/
        if(cRCresult == BnfDataDHStru.crc)
        {
            /*数据读取标志设为1*/
            IsDataRead = 1u;
        }
        else
        {         
            /*"校验失败，版本号不一致"*/
            retVal = 3;
        }    
    }
    else
    {
        /*文件失败*/
    }

    if ((0 == retVal )&& (NULL != pBnfData))
    {
        ReadInterSysCmpVersion(&pBnfData[BNF_FILE_DATA_INDEX]);

        index = BNF_FILE_DATA_INDEX + BNF_SUB_TAB_VER_IDX_LEN + gInterSysCmpVerIndexNum * BNF_CMP_VER_BLOCK_LEN;

        ReadBnfDataSubTabVersion(&pBnfData[index]);

        index = index + BNF_CMP_VER_IDX_LEN + gSubTabVerIndexNum * (BNF_SUB_TAB_VER_LEN + BNF_SUB_TAB_CRC_LEN + BNF_SUB_TAB_TYPE_LEN);

        retVal = ReadBnfDataWriteStru(&pBnfData[index],index);
    }
	
    return retVal;
}

/*********************************************************
*函数功能：将二进制文件的数据存储在对应的数据类型的队列中
*参数说明：
  输入参数：UINT8* pdata      二进制文件的数据
  全局变量：QueueStruct BnfDadaBuff[BNF_TABLE_NUM][BNP_TABLE_SHEET_MAX_NUM]
*返回值：   0成功
            -1数据读取不成功
            -2读取数据的总长度不一致
**********************************************************/ 
static INT8_S  ReadBnfDataWriteStru(const UINT8_S* pdata,const INT32_S dataHeadLen)
{
    INT8_S retVal = 0;        /*函数返回值*/
    UINT32_S i = 0u;          /*循环使用*/
    UINT32_S index = 0u;      /*读取数据偏移量*/
    UINT32_S tempDatalen = 0u;/*临时存放块长度*/

    if(NULL != pdata)
    {
        /*索引个数*/
        IndexNumber = ShortFromChar(&pdata[index]);
        index += 2u;
    }
    else
    {
        retVal = -1;
    }

    if((IndexNumber >0u) && (0u == retVal))
    {

        ReadDataStru = (BnfDataParseStruct*)MemoryMalloc((UINT32_S)sizeof(BnfDataParseStruct)*IndexNumber);
        if(NULL != ReadDataStru)
        {
            for(i = 0u;i < IndexNumber;i++)
            {
                /*读取变标号*/
                ReadDataStru[i].tableID = pdata[index];
                index++;
                /*读取表单编号*/
                ReadDataStru[i].sheetId = pdata[index];
                index++;

                /*列长度*/
                ReadDataStru[i].rowLength = ShortFromChar(&pdata[index]);
                index += 2u;

                /*读取块长度*/
                tempDatalen = LongFromChar(&pdata[index]);
                ReadDataStru[i].dataLen = tempDatalen;
                index += 4u;
            
                if (tempDatalen > 0u)
                {
                    /*根据块的数据长度分配空间*/
                    ReadDataStru[i].pDataBuff = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S) * tempDatalen);
                    /*获取数据内容*/
                    retVal = MemoryCpy(ReadDataStru[i].pDataBuff,tempDatalen,&pdata[index],tempDatalen);
                    if(retVal != 0)
                    {
                        break;
                    }
                    else
                    {
                        index += tempDatalen;
                    }
                }
            }
        }
        else
        {
            retVal = -1;
        }
    }


    if (0 == retVal)
    {
        if ((index + dataHeadLen - BNF_FILE_DATA_INDEX) != BnfDataDHStru.dataLength)
        {
            /*读取数据的总长度不一致*/
            retVal =-2;
        }
        else
        {
            /*成功读取数据*/
        }
    }

    return retVal;
}





/**********************************************
*函数功能：获取二进制文件版本号
*参数说明：
  输出参数：dataFileVersion    4字节  数据标识
*返回值：   0成功，1数据读取不成功
**********************************************/
INT8_S  GetBnfDataFileVersion(UINT32_S* dataFileVersion)
{
    INT8_S retVal = 1;/*函数返回值*/

    if((1u == IsDataRead) && (NULL != dataFileVersion))
    {
        *dataFileVersion = BnfDataDHStru.dataFileVersion;

        retVal = 0;
    }
    
    return retVal;
}


/**********************************************
*函数功能：获取二进制文件CRC
*参数说明：
  输出参数：dataFileCrc    4字节  CRC
*返回值：   0成功，1数据读取不成功
**********************************************/
INT8_S  GetBnfDataFileCrc(UINT32_S* dataFileCrc)
{
    INT8_S retVal = 1;/*函数返回值*/

    if((1u == IsDataRead) && (NULL != dataFileCrc))
    {
        *dataFileCrc = BnfDataDHStru.crc;

        retVal = 0;
    }
    
    return retVal;
}

/**********************************************
*函数功能：获取二进制文件线路编号
*参数说明：
  输出参数：dataFileSignNum    4字节  线路编号
*返回值：   0成功，1数据读取不成功
**********************************************/
INT8_S  GetBnfDataFileSignNum(UINT32_S* dataFileSignNum)
{
    INT8_S retVal = 1;/*函数返回值*/

    if((1u == IsDataRead) && (NULL != dataFileSignNum))
    {
        *dataFileSignNum = BnfDataDHStru.dataSignNum;

        retVal = 0;
    }
    
    return retVal;
}
/**********************************************************
*函数功能：获取二进制文件中此输入类型的数据长度和对应的index
*参数说明：
  输入参数：dataType 数据类型   由查询函数宏定义方式给出
            sheetID 数据ID      表单编号        
  输出参数：indexId   结构体指针偏移
            dataLength 数据长度
*返回值：   0成功
            1接口防护错误
            2传入的数据类型和表单编号错误
**********************************************************/
INT8_S GetReadBnfDataLen(UINT8_S dataType, UINT8_S sheetID , UINT32_S * dataLength, UINT8_S* indexId)
{
    INT8_S retVal = 0u;/*函数返回值*/
    UINT8_S i = 0u;    /*循环使用*/

    if((NULL != dataLength) && (NULL != indexId))
    {
        * dataLength = 0u;
        * indexId = UINT8_NULL;
    }
    else
    {
         retVal = 1u;
    }


    if((dataType <= BNF_TABLE_NUM)&&(sheetID <= BNP_TABLE_SHEET_MAX_NUM)&&(IndexNumber > 0u)&&(NULL != ReadDataStru) && (0u == retVal))
    {
        /*根据表类型和表单编号获取数据长度*/
        for ( i = 0u; i < IndexNumber; i++)
        {
            if((ReadDataStru[i].tableID == dataType)&&(ReadDataStru[i].sheetId == sheetID)
                &&(ReadDataStru[i].pDataBuff != NULL))
            {
                *dataLength = ReadDataStru[i].dataLen;
                *indexId = i;
                break;
            }
            else if((ReadDataStru[i].tableID == dataType)&&(ReadDataStru[i].sheetId == sheetID)
                &&(NULL == ReadDataStru[i].pDataBuff))
            {
                /*此数据已经读取,直接退出*/
                break;
            }
            else
            {
                /*继续执行循环*/
            }
        }
        
    }
    else
    {
        /*表编号或表单编号错误*/
        retVal = 2u;
    }
    
    return retVal;
}


/**********************************************************
*函数功能：获取二进制文件中此输入类型的数据信息
*参数说明：
  输入参数：UINT16 rowLength   所有列总长度
              dataLength 数据长度
            indexId   结构体指针偏移
  输出参数：dataBuff   数据地址指针
*返回值：   0成功
            1入口参数检查不通过
            2拷取数据失败
**********************************************************/
INT8_S GetReadBnfDataInfo(UINT16_S rowLength,UINT32_S dataLength,UINT8_S indexId, UINT8_S * dataBuff)
{
    INT8_S retVal = 0;/*函数返回值*/
    UINT8_S findTypeFlag = 1u;/*是否找到此数据类型数据的标志*/

    if((NULL != ReadDataStru) && (NULL != dataBuff))
    {
        if ((indexId != UINT8_NULL)&&(&ReadDataStru[indexId] != NULL)
            &&(rowLength == ReadDataStru[indexId].rowLength)
            &&(dataLength == ReadDataStru[indexId].dataLen)
            &&(dataBuff != NULL))
        {
            retVal = MemoryCpy(dataBuff,dataLength,ReadDataStru[indexId].pDataBuff,dataLength);                        
            
            if(0 == retVal)
            {
                findTypeFlag = 0u;
            }
            else
            {
                /*拷取数据失败*/
                retVal = 2;
            }            
        }
        else
        {
            /*入口参数检查不通过*/
            retVal = 1;
        }

        if(0u == findTypeFlag)
        {
            /*将此数据类型的空间释放*/
            if(ReadDataStru[indexId].pDataBuff != NULL)
            {
                ReadDataStru[indexId].pDataBuff = NULL;

            }
        }
        else
        {
            /*Do nothing currently !*/
        }
    }

    
    return retVal;
}
/**********************************************
*函数功能：获取系统间要比较的数据文件的版本号
*参数说明：
    输出参数：const UINT8_S verIndex    获取数据版本号的编号(具有参见ReadDataTypeDefine.h中相关的定义)
    输出参数：bnfVersion    4字节版本号
*返回值：   0成功，1数据读取不成功
**********************************************/
INT8_S  GetInterSysCmpDataFileVer(const UINT8_S verIndex,UINT32_S* bnfVersion)
{
    INT8_S retVal = 1;/*函数返回值*/

    if((1u == IsDataRead) && (NULL != bnfVersion))
    {
        if((verIndex > 0u)&&(gInterSysCmpVerIndexNum >= verIndex))
        {
            if((NULL != gpInterSysCmpVerStru) && (NULL != bnfVersion))
            {
                *bnfVersion = gpInterSysCmpVerStru[verIndex - 1u].cmpDataFileVersion;
                retVal = 0;
            }
        }
            
    }
    
    return retVal;
}


/**********************************************
*函数功能：获取数据子表的版本号
*参数说明：
    输出参数：const UINT8_S subTabType    数据子表类型(具有参见ReadDataTypeDefine.h中相关的定义)
    输出参数：subTabVersion    4字节版本号
*返回值：   0成功，1数据读取不成功
**********************************************/
INT8_S  GetDataSubTabVer(const UINT8_S subTabType,UINT32_S* subTabVersion)
{
    INT8_S retVal = 1;/*函数返回值*/
    UINT8_S i = 0u;

    if((1u == IsDataRead) && ( NULL != subTabVersion))
    {

        for(i = 0u;i < gSubTabVerIndexNum;i++)
        {
            if(gpSubTabVersionStru[i].subTabType  == subTabType)
            {
                retVal = 0;
                *subTabVersion = gpSubTabVersionStru[i].subTabDataVer;
                break;
            }
        }
            
    }
    
    return retVal;
}

/**********************************************
*函数功能：获取系统间要比较的数据文件的CRC
*参数说明：
    输出参数：const UINT8_S cmpDataFileType    系统间比较数据文件类型(具有参见ReadDataTypeDefine.h中相关的定义)
    输出参数：bnfCrc    4字节Crc
*返回值：   0成功，1数据读取不成功
**********************************************/
INT8_S  GetDataSubTabCrc(const UINT8_S subTabType,UINT32_S* subTabDataCrc)
{
    INT8_S retVal = 1;/*函数返回值*/
    UINT8_S i = 0u;

    if((1u == IsDataRead) && ( NULL != subTabDataCrc))
    {

        for(i = 0u;i < gSubTabVerIndexNum;i++)
        {
            if(gpSubTabVersionStru[i].subTabType == subTabType)
            {
                retVal = 0;
                *subTabDataCrc = gpSubTabVersionStru[i].subTabDataCrc;
                break;
            }
        }
            
    }
    
    return retVal;
}











