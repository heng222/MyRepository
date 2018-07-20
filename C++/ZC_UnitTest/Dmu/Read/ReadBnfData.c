/*************************************************
  �ļ���   ��ReadBnfData.c
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� ��Bnf��������ͷ�ļ�
			DmuCommonRead����Ĺ��ܿɷֽ����£�
			1��	��ȡ�������ļ����ұ��浽�ڴ�
			2��	��ȡ�������ļ����ݱ�ʶ��
			3��	��ȡ�������ļ�CRC��
			4��	��ȡ�������ļ���·��ţ�
			5��	��ȡ�������ļ��д��������͵����ݳ��ȺͶ�Ӧ��index��
			6��	��ȡ�������ļ��д��������͵�������Ϣ��
			7��	��ȡϵͳ��Ҫ�Ƚϵ������ļ��İ汾�ţ�
			8��	��ȡ�����ӱ�İ汾�ţ�
			9��	��ȡϵͳ��Ҫ�Ƚϵ������ļ���CRC��
  ��ע    ���ޡ� 
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
static UINT16_S IndexNumber = 0u;/*��������*/
static UINT8_S gSubTabVerIndexNum = 0u;       /*�����ӱ�汾����������*/
static UINT8_S gInterSysCmpVerIndexNum = 0u;  /*ϵͳ��Ƚ����ݰ汾�ĸ���*/

/*�洢�������ļ�����������*/
static BnfDataParseStruct* ReadDataStru = NULL;
static SubTabVersionStruct* gpSubTabVersionStru = NULL;
static InterSysCmpVerStruct  * gpInterSysCmpVerStru = NULL;

/**********************�ڲ�ʹ�ú�������START*****************************/
static void  ReadBnfDataHeadFromBnfByte(const UINT8_S *pBnfData,BnfDataHeadStruct * pDadaHead);
static INT8_S  ReadBnfDataWriteStru(const UINT8_S* pdata,const INT32_S dataHeadLen);
static void  ReadBnfDataSubTabVersion(const UINT8_S *pBnfData);
static void  ReadBnfDataSubTabVersion(const UINT8_S *pBnfData);
/***********************�ڲ�ʹ�ú�������END******************************/

/*********************************************
*�������ܣ��Ӷ����������ж�ȡ����ͷ
*����˵����
*�������:pBnfData�Ƕ��������ݵ�ַ
*�������:pDadaHead�Ǵ洢����ͷ�ṹָ��    
*����ֵ����
*********************************************/
static void  ReadBnfDataHeadFromBnfByte(const UINT8_S *pBnfData,BnfDataHeadStruct * pDadaHead)
{
    if((NULL != pBnfData) && (NULL != pDadaHead))
    {
        /*��ȡ���ݱ�ʶ*/
        pDadaHead->dataSignNum = LongFromChar(pBnfData);
        pBnfData += 4;

        /*��ȡ���ݰ汾*/
        pDadaHead->dataFileVersion = LongFromChar(pBnfData);
        pBnfData += 4;
        
        /*��ȡ�����ļ�CRC*/
        pDadaHead->crc = LongFromChar(pBnfData);
        pBnfData += 4;
            
        /*��ȡ���ݳ���*/
        pDadaHead->dataLength = LongFromChar(pBnfData);
    }
}

/*********************************************
*�������ܣ��Ӷ����������ж�ȡϵͳ������У��汾��
*����˵����
*�������:pBnfData�Ƕ��������ݵ�ַ
*����ֵ����
*********************************************/
static void  ReadInterSysCmpVersion(const UINT8_S *pBnfData)
{
    UINT8_S i = 0u;/*ѭ��ʹ��*/
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
                    /*��ȡ�汾��*/
                    gpInterSysCmpVerStru[i].cmpDataFileVersion = LongFromChar(pBnfData);
                    pBnfData += 4;
                }
            }
        }
        
    }

}


    /*********************************************
*�������ܣ��Ӷ����������ж�ȡ���Ա����ݰ汾��
*����˵����
*�������:pBnfData�Ƕ��������ݵ�ַ
*����ֵ����
*********************************************/
static void  ReadBnfDataSubTabVersion(const UINT8_S *pBnfData)
{
    UINT8_S i = 0u;/*ѭ��ʹ��*/
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
                    /*�Ƚϰ汾����:��ZC-CI*/
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
* �������� ����ȡ�������ļ����ұ��浽�ڴ�
* ����˵�� ��
* ������� :bnfFileName �������ļ���ַ
* ����ֵ��0:�ɹ�
*         1:�򿪶������ļ�ʧ��
          2:��ȡ�������ļ�ʧ��
          3:У��ʧ�ܣ��汾�Ų�һ��
          5:�����������ļ��ĵ�ַΪ��
          -1���ݶ�ȡ���ɹ�
          -2��ȡ���ݵ��ܳ��Ȳ�һ��
**********************************/
INT8_S ReadBnfData(const CHAR_S * bnfFileName)
{
    INT8_S retVal = 0;/*��������ֵ*/
    UINT32_S tmpDataLen = 0u;/*���ݳ���*/
    UINT32_S tempRetVal = 0;/*��ʱ��ź�������ֵ*/
    UINT32_S cRCresult = 0u;   /*У����*/
    FILEType pfile = NULL;/*��ʼ��*/
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
    /* ������ƽ̨ 20180529 */
	result = CSPADPT_Get_SpeciConfig_Addr_Size( ENUM_CONFIG_DAT_TYPE_CIAPP,(UINT8_S*)(&l_Addr), &tmpDataLen);
	
	if ((GM_TRUE == result) && (tmpDataLen > 0u))
	{
		/*��ȡ�ɹ�������ִ��*/
		pBnfData = (UINT8_S*)l_Addr;
        retVal = 0;
		
	}
	else
	{
		/*��¼�ļ���ȡʧ�ܵĴ���*/
		retVal = 2;
	}
#else
        /*�򿪶������ļ�*/
        tempRetVal = AdptAppFileOpen(bnfFileName,0,&pfile);
        /*�жϴ򿪶������ļ��Ƿ�ɹ�*/
        if (1 == tempRetVal)
        {
            tmpDataLen = AdptAppFileRead(pfile,bnfFileName,pBnfData,BNF_MAX_FILE_LEN);
            if(tmpDataLen > 0u)
            {
                /*��ȡ�ɹ�������ִ��*/
                retVal = 0;
            }
            else
            {
                /*��¼�ļ���ȡʧ�ܵĴ���*/
                retVal = 2;
            }
            AdptAppFileClose(pfile);
        }
        else
        {
            /*�򿪶������ļ�ʧ��*/
            retVal = 1;
        }
#endif
    }
    else
    {
        if (bnfFileName == NULL)
        {
            /*�����������ļ��ĵ�ַΪ��*/
            retVal = 5;
        }
        else
        {
            /*�˶������ļ��Ѿ���ȡ*/
        }
    }
        
    if((0 == retVal) && (NULL != pBnfData))    
    {
        /*��������ͷ*/
        ReadBnfDataHeadFromBnfByte(pBnfData,&BnfDataDHStru);         
        

        /*CRC����,�����ݱ�ʶ��CRC����ʣ��Ĳ���*/
        cRCresult = Crc32(&pBnfData[BNF_FILE_CRCDATA_INDEX], BnfDataDHStru.dataLength+4u);
        /*CRCУ��*/
        if(cRCresult == BnfDataDHStru.crc)
        {
            /*���ݶ�ȡ��־��Ϊ1*/
            IsDataRead = 1u;
        }
        else
        {         
            /*"У��ʧ�ܣ��汾�Ų�һ��"*/
            retVal = 3;
        }    
    }
    else
    {
        /*�ļ�ʧ��*/
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
*�������ܣ����������ļ������ݴ洢�ڶ�Ӧ���������͵Ķ�����
*����˵����
  ���������UINT8* pdata      �������ļ�������
  ȫ�ֱ�����QueueStruct BnfDadaBuff[BNF_TABLE_NUM][BNP_TABLE_SHEET_MAX_NUM]
*����ֵ��   0�ɹ�
            -1���ݶ�ȡ���ɹ�
            -2��ȡ���ݵ��ܳ��Ȳ�һ��
**********************************************************/ 
static INT8_S  ReadBnfDataWriteStru(const UINT8_S* pdata,const INT32_S dataHeadLen)
{
    INT8_S retVal = 0;        /*��������ֵ*/
    UINT32_S i = 0u;          /*ѭ��ʹ��*/
    UINT32_S index = 0u;      /*��ȡ����ƫ����*/
    UINT32_S tempDatalen = 0u;/*��ʱ��ſ鳤��*/

    if(NULL != pdata)
    {
        /*��������*/
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
                /*��ȡ����*/
                ReadDataStru[i].tableID = pdata[index];
                index++;
                /*��ȡ�����*/
                ReadDataStru[i].sheetId = pdata[index];
                index++;

                /*�г���*/
                ReadDataStru[i].rowLength = ShortFromChar(&pdata[index]);
                index += 2u;

                /*��ȡ�鳤��*/
                tempDatalen = LongFromChar(&pdata[index]);
                ReadDataStru[i].dataLen = tempDatalen;
                index += 4u;
            
                if (tempDatalen > 0u)
                {
                    /*���ݿ�����ݳ��ȷ���ռ�*/
                    ReadDataStru[i].pDataBuff = (UINT8_S*)MemoryMalloc((UINT32_S)sizeof(UINT8_S) * tempDatalen);
                    /*��ȡ��������*/
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
            /*��ȡ���ݵ��ܳ��Ȳ�һ��*/
            retVal =-2;
        }
        else
        {
            /*�ɹ���ȡ����*/
        }
    }

    return retVal;
}





/**********************************************
*�������ܣ���ȡ�������ļ��汾��
*����˵����
  ���������dataFileVersion    4�ֽ�  ���ݱ�ʶ
*����ֵ��   0�ɹ���1���ݶ�ȡ���ɹ�
**********************************************/
INT8_S  GetBnfDataFileVersion(UINT32_S* dataFileVersion)
{
    INT8_S retVal = 1;/*��������ֵ*/

    if((1u == IsDataRead) && (NULL != dataFileVersion))
    {
        *dataFileVersion = BnfDataDHStru.dataFileVersion;

        retVal = 0;
    }
    
    return retVal;
}


/**********************************************
*�������ܣ���ȡ�������ļ�CRC
*����˵����
  ���������dataFileCrc    4�ֽ�  CRC
*����ֵ��   0�ɹ���1���ݶ�ȡ���ɹ�
**********************************************/
INT8_S  GetBnfDataFileCrc(UINT32_S* dataFileCrc)
{
    INT8_S retVal = 1;/*��������ֵ*/

    if((1u == IsDataRead) && (NULL != dataFileCrc))
    {
        *dataFileCrc = BnfDataDHStru.crc;

        retVal = 0;
    }
    
    return retVal;
}

/**********************************************
*�������ܣ���ȡ�������ļ���·���
*����˵����
  ���������dataFileSignNum    4�ֽ�  ��·���
*����ֵ��   0�ɹ���1���ݶ�ȡ���ɹ�
**********************************************/
INT8_S  GetBnfDataFileSignNum(UINT32_S* dataFileSignNum)
{
    INT8_S retVal = 1;/*��������ֵ*/

    if((1u == IsDataRead) && (NULL != dataFileSignNum))
    {
        *dataFileSignNum = BnfDataDHStru.dataSignNum;

        retVal = 0;
    }
    
    return retVal;
}
/**********************************************************
*�������ܣ���ȡ�������ļ��д��������͵����ݳ��ȺͶ�Ӧ��index
*����˵����
  ���������dataType ��������   �ɲ�ѯ�����궨�巽ʽ����
            sheetID ����ID      �����        
  ���������indexId   �ṹ��ָ��ƫ��
            dataLength ���ݳ���
*����ֵ��   0�ɹ�
            1�ӿڷ�������
            2������������ͺͱ���Ŵ���
**********************************************************/
INT8_S GetReadBnfDataLen(UINT8_S dataType, UINT8_S sheetID , UINT32_S * dataLength, UINT8_S* indexId)
{
    INT8_S retVal = 0u;/*��������ֵ*/
    UINT8_S i = 0u;    /*ѭ��ʹ��*/

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
        /*���ݱ����ͺͱ���Ż�ȡ���ݳ���*/
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
                /*�������Ѿ���ȡ,ֱ���˳�*/
                break;
            }
            else
            {
                /*����ִ��ѭ��*/
            }
        }
        
    }
    else
    {
        /*���Ż����Ŵ���*/
        retVal = 2u;
    }
    
    return retVal;
}


/**********************************************************
*�������ܣ���ȡ�������ļ��д��������͵�������Ϣ
*����˵����
  ���������UINT16 rowLength   �������ܳ���
              dataLength ���ݳ���
            indexId   �ṹ��ָ��ƫ��
  ���������dataBuff   ���ݵ�ַָ��
*����ֵ��   0�ɹ�
            1��ڲ�����鲻ͨ��
            2��ȡ����ʧ��
**********************************************************/
INT8_S GetReadBnfDataInfo(UINT16_S rowLength,UINT32_S dataLength,UINT8_S indexId, UINT8_S * dataBuff)
{
    INT8_S retVal = 0;/*��������ֵ*/
    UINT8_S findTypeFlag = 1u;/*�Ƿ��ҵ��������������ݵı�־*/

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
                /*��ȡ����ʧ��*/
                retVal = 2;
            }            
        }
        else
        {
            /*��ڲ�����鲻ͨ��*/
            retVal = 1;
        }

        if(0u == findTypeFlag)
        {
            /*�����������͵Ŀռ��ͷ�*/
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
*�������ܣ���ȡϵͳ��Ҫ�Ƚϵ������ļ��İ汾��
*����˵����
    ���������const UINT8_S verIndex    ��ȡ���ݰ汾�ŵı��(���вμ�ReadDataTypeDefine.h����صĶ���)
    ���������bnfVersion    4�ֽڰ汾��
*����ֵ��   0�ɹ���1���ݶ�ȡ���ɹ�
**********************************************/
INT8_S  GetInterSysCmpDataFileVer(const UINT8_S verIndex,UINT32_S* bnfVersion)
{
    INT8_S retVal = 1;/*��������ֵ*/

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
*�������ܣ���ȡ�����ӱ�İ汾��
*����˵����
    ���������const UINT8_S subTabType    �����ӱ�����(���вμ�ReadDataTypeDefine.h����صĶ���)
    ���������subTabVersion    4�ֽڰ汾��
*����ֵ��   0�ɹ���1���ݶ�ȡ���ɹ�
**********************************************/
INT8_S  GetDataSubTabVer(const UINT8_S subTabType,UINT32_S* subTabVersion)
{
    INT8_S retVal = 1;/*��������ֵ*/
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
*�������ܣ���ȡϵͳ��Ҫ�Ƚϵ������ļ���CRC
*����˵����
    ���������const UINT8_S cmpDataFileType    ϵͳ��Ƚ������ļ�����(���вμ�ReadDataTypeDefine.h����صĶ���)
    ���������bnfCrc    4�ֽ�Crc
*����ֵ��   0�ɹ���1���ݶ�ȡ���ɹ�
**********************************************/
INT8_S  GetDataSubTabCrc(const UINT8_S subTabType,UINT32_S* subTabDataCrc)
{
    INT8_S retVal = 1;/*��������ֵ*/
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











