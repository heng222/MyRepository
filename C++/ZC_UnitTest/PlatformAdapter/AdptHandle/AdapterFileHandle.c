/********************************************************
*                                                                                                            
* 文 件 名： AdapterFileHandle.c   
* 作    者： 董欣 
* 创建时间： 2016-09-01
* 功能描述： 平台适配层文件操作文件 
* 备    注： 无 
*
********************************************************/ 

#include "AdapterFileHandle.h"
#include "../PlatformLog/AdapterLog.h"
#include "../../Common/MemSet.h"
#include "../../Common/Copy.h"
#include "../PlatItf/AdptPlatFileInterface.h"

static E_WriteStatus gWriteStatus = e_Init;            /*文件写操作状态转移变量*/
static E_FileStatus gFileStatus = e_File_First;        /*文件所处的状态*/
static FILEType gFileHandle = 0L;                      /*文件操作句柄*/
static CHAR_S* gpFileCurPath = NULL;                   /*当前操作文件路径*/
static UINT8_S gWriteFileCycTimer = 0u;                 /*写文件计时器*/

CHAR_S gFilePathFirst[FILE_NAME_MAX_LEN];
CHAR_S gFilePathSecond[FILE_NAME_MAX_LEN];

static UINT8_S AdapterCycleWriteFileInit(void);
static UINT8_S AdapterCycleWriteFileOpen(void);
static UINT8_S AdapterCycleWriteFileWrite(UINT8_S* pBuff,UINT32_S buffLengh);
static UINT8_S AdapterCycleWriteFileClose(void);
static UINT8_S AdapterCycleWriteFileSuc(void);
static UINT8_S AdapterCycleWriteFileSync(void);
static void AdapterSetWriteFileCycTimer(const UINT8_S timer);
static void AdapterUpdateWriteFileCycTimer(void);
static UINT8_S AdapterGetWriteFileCycTimer(void);
static UINT8_S AdapterFileChooseByTime(const CHAR_S* fileName1,const CHAR_S* fileName2);
static UINT8_S AdapterFileCreateTimeCompare(const AdptRealClkStruct * createTime1, const AdptRealClkStruct * createTime2);
static void AdapterFilePathChoose(void);


/*
*  功能描述：  设置文件操作所需的配置文件名字
*  参数说明:str1        第一个文件的名称
*            str2        第二个文件的名称
*  返回值:    无
*/
UINT8_S AdapterSetCfgFileName(CHAR_S name1[],UINT8_S nameLen1, CHAR_S name2[],  UINT8_S nameLen2)
{
    UINT8_S retVal = 0u;

    if (( nameLen1 <= FILE_NAME_MAX_LEN) && (nameLen2 <= FILE_NAME_MAX_LEN) && (name1 != NULL) && (name2 != NULL))
    {
        MemorySet(gFilePathFirst,FILE_NAME_MAX_LEN,0u,FILE_NAME_MAX_LEN);
        MemorySet(gFilePathSecond,FILE_NAME_MAX_LEN,0u,FILE_NAME_MAX_LEN);

        MemoryCpy(gFilePathFirst,FILE_NAME_MAX_LEN,name1,nameLen1);
        MemoryCpy(gFilePathSecond,FILE_NAME_MAX_LEN,name2,nameLen2);
        retVal = 1u;
    }

    return retVal;
}


/*
*  功能描述：  读文件操作,从两个文件中选取最新的读取
*  参数说明:   UINT8_S* pBuff,       输出读取的数据
*              UINT32_S buffLength,  输出读取数据长度
*  返回值:       readDataLen,0读取失败;>0读取成功
*/
UINT32_S AdapterFileReadProc(UINT8_S* buff, UINT32_S buffLength)
{
    UINT32_S readDataLen = 0u;
    UINT32_S rtnValue = 0u;
    UINT8_S chooseFile = 0u;
    CHAR_S* tempFilePath = NULL;

    if ( NULL != buff )
    {
        chooseFile = AdapterFileChooseByTime(gFilePathFirst,gFilePathSecond);  /*获取最近修改文件的编号*/

        switch (chooseFile)
        {
            case 1u:
            gFileStatus = e_File_First;
            tempFilePath = gFilePathFirst;
            break;

            case 2u:
            gFileStatus = e_File_Second;
            tempFilePath = gFilePathSecond;
            break;

            default:
            break;
        }

        rtnValue = AdptPlatFileOpen(tempFilePath, (UINT8_S)AdptFOpenRead, &gFileHandle);

        if (1u == rtnValue)
        {
            readDataLen = AdptPlatFileRead (gFileHandle, tempFilePath, buff, buffLength);

            if (0u != readDataLen)
            {
                AdptPlatFileClose(gFileHandle);

                /* 当前适配层使用的接口为能够主动释放句柄的close接口所以不需要释放 */
                /*AdptPlatFileRelease(gFileHandle);*/
            }
        }
    }

    return readDataLen;
}


/*
*  功能描述：  根据文件创建时间获取最近创建的文件名称
*  参数说明:   const CHAR* fileName1，文件1名称；const CHAR* fileName2，文件2名称
*  返回值:     1,fileName1文件最近修改
*              2,fileName2文件最近修改
*              0,系统出错,或者只有一个文件正常存在
*/
static UINT8_S AdapterFileChooseByTime(const CHAR_S* fileName1,const CHAR_S* fileName2)
{
    UINT8_S rtnResult = 0u;
    UINT8_S retExist1 = 0u;/*函数返回值*/
    UINT8_S retExist2 = 0u;/*函数返回值*/
    UINT8_S retDetail1 = 0u;
    UINT8_S retDetail2 = 0u;

    AdptFileDetailStruct outFileDetail1;
    AdptFileDetailStruct outFileDetail2;

    if (( NULL != fileName1 ) && ( NULL != fileName2 ))
    {
        /*判断文件1是否存在*/
        retExist1 = AdptPlatFileExist(fileName1);
        /*判断文件2是否存在*/
        retExist2 = AdptPlatFileExist(fileName2);

        if ((1u == retExist1)&&(1u == retExist2))
        {

            retDetail1 = AdptPlatFileInquire(fileName1, &outFileDetail1);

            retDetail2 = AdptPlatFileInquire(fileName2, &outFileDetail2);

            if ((1u == retDetail1)&&(1u == retDetail2))
            {
                rtnResult = AdapterFileCreateTimeCompare(&outFileDetail1.CTime, &outFileDetail2.CTime);
            }
            else
            {
                rtnResult = 0u;
            }
        }
        else
        {
            rtnResult = 0u;
        }
    }

    return rtnResult;

}



/*
*  功能描述：比较两个文件的创建时间的先后
*  参数说明:AdptRealClk * CreateTime1, 第一个文件的创建时间
*           AdptRealClk * CreateTime2, 第二个文件的创建时间
*  返回值:  1  第一个文件后创建
*           2  第二个文件后创建
*           0,系统出错
*           两个文件同时创建，默认文件一最新创建
*/
static UINT8_S AdapterFileCreateTimeCompare(const AdptRealClkStruct * createTime1, const AdptRealClkStruct * createTime2)
{
    UINT8_S retVal = 0u;

    if (( NULL != createTime1 ) && ( NULL != createTime2 ))
    {
        if (createTime1->Year > createTime2->Year)
        {
            retVal = 1u;    
        }
        else if (createTime1->Year < createTime2->Year)
        {
            retVal = 2u;
        }
        else
        {
            if (createTime1->Month > createTime2->Month)
            {
                retVal = 1u;
            }
            else if (createTime1->Month < createTime2->Month)
            {
                retVal = 2u;
            }
            else
            {
                if (createTime1->Day > createTime2->Day)
                {
                    retVal = 1u;
                }
                else if (createTime1->Day < createTime2->Day)
                {
                    retVal = 2u;
                }
                else
                {
                    if (createTime1->MiSec > createTime2->MiSec)
                    {
                        retVal = 1u;
                    }
                    else if (createTime1->MiSec < createTime2->MiSec)
                    {
                        retVal = 2u;
                    }
                    else
                    {
                        retVal = 1u;
                    }
                }
            }

        }
    }

    return retVal;
}

/*
*  功能描述：  多周期循环写文件操作
*  参数说明:   UINT8* pBuff,       输入写文件数据
*              UINT32_S buffLength， 输入写文件数据长度
*  返回值:       returnValue，文件写入操作所处的状态
*/
E_WriteStatus AdapterCycleWriteFile(UINT8_S* pBuff, UINT32_S buffLength)
{
    E_WriteStatus returnValue = e_Init;

    if ( NULL != pBuff )
    {
        AdapterUpdateWriteFileCycTimer();

        if(AdapterGetWriteFileCycTimer() >= FileWriteCycMax)
        {
            AdapterSetWriteFileCycTimer(0u);
            returnValue = e_Error;
            gWriteStatus = e_Init;
        }
        else
        {
            switch (gWriteStatus)
            {
                case e_Init:
                    AdapterCycleWriteFileInit();
                    returnValue = e_Init;
                    break;

                case e_Open:
                    AdapterCycleWriteFileOpen();
                    returnValue = e_Open;
                    break;

                case e_Write:
                    AdapterCycleWriteFileWrite(pBuff, buffLength);
                    returnValue = e_Write;
                    break;

                case e_Close:
                    AdapterCycleWriteFileClose();
                    returnValue = e_Close;
                    break;

                case e_Sync:

                    AdapterCycleWriteFileSync();
                    returnValue = e_Sync;
                    break;

                case e_Sucess:

                    if(1u == AdapterCycleWriteFileSuc())
                    {
                        AdapterSetWriteFileCycTimer(0u);
                        returnValue = e_Sucess;
                    }
                    else
                    {
                        returnValue = e_Sync;
                    }

                    break;


                case e_Error:
                    AdapterSetWriteFileCycTimer(0u);
                    returnValue = e_Error;
                    break;

                default:
                    AdapterSetWriteFileCycTimer(0u);
                    returnValue = e_Error;
                    break;
            }

        }
    }

    printf("write pro:%s,%d,%d,%d\n",gpFileCurPath, gWriteStatus, returnValue, buffLength);

    return returnValue;
}


/*
*  功能描述：  多周期循环写文件操作过程中的初始化操作
*  参数说明:   无
*  返回值:    1成功   0 失败
*/
static UINT8_S AdapterCycleWriteFileInit(void)
{
    UINT8_S retVal = 0u;

    /* 写文件路径选择 */
    AdapterFilePathChoose();

    if (1u == AdptPlatFileExist(gpFileCurPath))
    {
        retVal = AdptPlatFileDelete(gpFileCurPath, &gFileHandle);
        gWriteStatus = e_Open;
    }
    else
    {
        /*创建打开文件*/
        retVal = AdptPlatFileOpen(gpFileCurPath, (UINT8_S)AdptFOpenWrite, &gFileHandle);
        gWriteStatus = e_Write;
    }

    return retVal;
}


/*
*  功能描述：  多周期循环写文件操作过程中的打开操作
*  参数说明:   无
*  返回值:    1成功   0 失败
*/
static UINT8_S AdapterCycleWriteFileOpen(void)
{
    UINT8_S retVal = 0u;
    AdptProgressStruct iProgress;
    UINT8_S fileStatus = 0u;         /*文件状态查询操作返回值*/

    fileStatus = AdptPlatFileStatusInquire(gFileHandle, &iProgress); /*查询文件状态*/

    if (FILE_INQ_FINISH == fileStatus)
    {
        retVal = AdptPlatFileOpen(gpFileCurPath, (UINT8_S)AdptFOpenWrite, &gFileHandle);
        gWriteStatus = e_Write;
    }
    else
    {
        /*Do nothing currently!*/
    }

    return retVal;

}

/*
*  功能描述：  多周期循环写文件操作过程中的写入操作
*  参数说明:   UINT8* pBuff,
*              UINT32_S buffLengh
*  返回值:       1成功   0 失败
*/
static UINT8_S AdapterCycleWriteFileWrite(UINT8_S* pBuff,UINT32_S buffLengh)
{
    UINT8_S retVal = 0u;
    AdptProgressStruct iProgress;
    UINT8_S fileStatus = 0u;

    fileStatus = AdptPlatFileStatusInquire(gFileHandle, &iProgress);

    if(FILE_INQ_REQ_DONE == fileStatus)
    {
        retVal = AdptPlatFileWrite(gFileHandle, buffLengh, pBuff);

        gWriteStatus = e_Close;
    }
    else
    {
        /*暂不处理*/
    }

    return retVal;
}
/*
*  功能描述：  多周期循环写文件操作过程中的关闭操作
*  参数说明:   无
*  返回值:       1成功   0 失败
*/

static UINT8_S AdapterCycleWriteFileClose(void)
{
    UINT8_S retVal = 0u;
    UINT8_S fileStatus = 0u;
    AdptProgressStruct iProgress;

    fileStatus = AdptPlatFileStatusInquire(gFileHandle, &iProgress);

    if (FILE_INQ_REQ_DONE == fileStatus)
    {
        retVal = AdptPlatFileClose(gFileHandle);
        gWriteStatus = e_Sync;
    }

    return retVal;
}


/*
*  功能描述：  多周期循环写文件操作过程中与另一机同步操作
*  参数说明:   无
*  返回值:       1成功   0 失败
*/
static UINT8_S AdapterCycleWriteFileSync(void)
{
    UINT8_S retVal = 0u;
    UINT8_S fileStatus = 0u;
    AdptProgressStruct iProgress;

    fileStatus = AdptPlatFileStatusInquire(gFileHandle, &iProgress);

    if(FILE_INQ_ERR_HANDLE == fileStatus)
    {

        /*  返回成功之前需要查看另一主机文件状态，确保文件处理同步  */
        AdptPlatFileOpen(gpFileCurPath, (UINT8_S)AdptFOpenExchange, &gFileHandle);
        retVal = 1u;
        gWriteStatus = e_Sucess;
    }

    return retVal;
}


/*
*  功能描述：  多周期循环写文件操作过程中的成功操作
*  参数说明:   无
*  返回值:       1成功   0 失败
*/
static UINT8_S AdapterCycleWriteFileSuc(void)
{
    UINT8_S retVal = 0u;
    UINT8_S excRet = 0u;
    UINT8_S excStatus = 0u;
    UINT32_S excSize = 0u;
    AdptFileDetailStruct outFileDetail = {0u};
    UINT8_S inqRet = 0u;

    excRet = AdptPlatFileExcStatusInquire(gFileHandle, &excStatus, &excSize);

    inqRet = AdptPlatFileInquire(gpFileCurPath, &outFileDetail);

    /* 判断交换信息函数和查询函数是否成功  */
    if ((1u == excRet) && (1u == inqRet))
    {

        /* 判断文件大小是否相同，文件状态是否一致 */
        if ((excSize == outFileDetail.Size)&& (FILE_INQ_ERR_HANDLE == excStatus))
        {
            AdptPlatFileClose(gFileHandle);
            gWriteStatus = e_Init;
            gFileHandle = 0;
            retVal = 1u;
        }
    }

    return retVal;
}

/*
*  功能描述：  写文件路径选择
*  参数说明:   无
*  返回值:       无
*/
static void AdapterFilePathChoose(void)
{
    switch (gFileStatus)
    {
        case e_File_First:
        gFileStatus = e_File_Second;
        gpFileCurPath = gFilePathFirst;
        break;

        case e_File_Second:
        gFileStatus = e_File_First;
        gpFileCurPath = gFilePathSecond;
        break;

        default:
        break;
    }
}

/*
*    功能描述：设置写文件计时器
*    参数说明:const UINT8 timer
*  返回值:无
*/
static void AdapterSetWriteFileCycTimer(const UINT8_S timer)
{
    gWriteFileCycTimer = timer;
}

/*
*  功能描述：更新计时器
*  参数说明:无
*  返回值:无
*/
static void AdapterUpdateWriteFileCycTimer(void)
{
    gWriteFileCycTimer++;
}

/*
*  功能描述：获取计时器
*  参数说明:无
*  返回值:计时器
*/
static UINT8_S AdapterGetWriteFileCycTimer(void)
{
    return gWriteFileCycTimer;
}

