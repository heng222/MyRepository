/********************************************************                                                                                                            
 文 件 名： MaintainManager.c
 作    者： ZC组
 创建时间： 2015-04-18
 描述： 维护日志管理
 备注： 无  
********************************************************/
#include "MaintainManager.h"
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "../SysDataManager/SysConfigData.h"
#include "../../Common/MemSet.h"
#include "../../Common/Copy.h"
#include "../../PlatformAdapter/AppItf/AdptAppFileInterface.h"

#ifdef SYS_TYPE_WINDOWS
#include "../../Udp/SysConfig.h"
#include "io.h"
#endif

static UINT8_S gMaintainDataArr1[MAINTAIN_DATA_LEN_MAX] = {0u};
static UINT32_S gMaintainLen1 = 0u;
/*static UINT8_S gTempArr[3000] = {0u};*/
char chTempDebugArray[10000];           /*缓存打印前字符串信息*/ 

UINT8_S gLogPrintfType = 0xaaU;

/*************************************************
  函数名:      SetLogPrintfType
  功能描述:    设置打印log信息类型
  输入:        const UINT8_S logPrintfType 记录日志标识
  输出:        无
  返回值:      无
*************************************************/
void SetLogPrintfType(const UINT8_S logPrintfType)
{
    if ((FLAG_SET == logPrintfType) || (FLAG_UNSET == logPrintfType))
    {
        gLogPrintfType = logPrintfType;
    } 
    else
    {
        /*Do nothing currently !*/
    }
}

/*************************************************
  函数名:      LogPrintf
  功能描述:    打印log信息(Windows版的日志打印)
  输入:        UINT8_S chRunSystem, 标识
               const char * lpszFormat 指针
  输出:        无
  返回值:      0u 失败
               1u 成功
*************************************************/
#ifdef SYS_TYPE_WINDOWS
UINT8_S LogPrintf(UINT8_S chRunSystem, const char * lpszFormat, ...)
{
#if 1
    UINT8_S retVal = 1U;
    va_list arg_ptr; 
    int n = 0;

    /*char chTempDebugArray[10000];*/           /*缓存打印前字符串信息*/ 

    MemorySet(&chTempDebugArray[0],(UINT32_S)(10000*SIZE_UINT8),DEFAULT_ZERO,(UINT32_S)(10000*SIZE_UINT8));

    /*初始化从第三个参数开始查找*/
    va_start(arg_ptr,lpszFormat);
    n = vsprintf_s(chTempDebugArray,10000,lpszFormat,arg_ptr);
    va_end(arg_ptr);

    switch (chRunSystem)
    {
    case 1U:
        LogPrintf_Windows(NULL,chTempDebugArray,n);
        break;
    default:
        retVal = 0U;
        break;
    }
	
    return retVal;
#else

    va_list arg_ptr;
    INT32_S n = 0u;
    UINT8_S retVal = 0u;

    UINT32_S useLen = 0u;

    if ( NULL != lpszFormat )
    {
        useLen = MAINTAIN_DATA_LEN_MAX - gMaintainLen;

        va_start(arg_ptr,lpszFormat);
        n = vsprintf((CHAR_S *)&gTempArr[0u],lpszFormat, arg_ptr);
        va_end(arg_ptr);

        if(n  <= 0u)
        {
            retVal = 0u;
        }
        else
        {
            /*if (1u == chRunSystem)*/
            {
                if((UINT32_S)n >= useLen)
                {
                    MemoryCpy(&gMaintainDataArr[gMaintainLen], useLen, gTempArr, useLen);
                    gMaintainLen += useLen;
                }
                else
                {
                    MemoryCpy(&gMaintainDataArr[gMaintainLen], useLen, gTempArr, (UINT32_S)n);
                    gMaintainLen  += ((UINT32_S)n);
                }
                retVal = 1u;
            }
            /*else*/
            {
                /* 预留为其他log记录方式，比如写文件之类 */
                retVal = 0u;
            }
        }
    }
    else
    {
        retVal = 0u;
    }
    return retVal;
#endif
}
#endif
/*************************************************
  函数名:      LogPrintf_Windows
  功能描述:    打印Windows下log信息
  输入:        const char * szFileName, 文件名
               const char * lpszFormat, 指针
               const UINT32_S dwLength, 长度
  输出:        无
  返回值:      -1:  失败
               !=-1: 成功
*************************************************/
#ifdef SYS_TYPE_WINDOWS
INT32_S LogPrintf_Windows(const char * szFileName, const char * lpszFormat,const UINT32_S dwLength)
{

    INT32_S  iResult = 0;  /*记录返回结果*/
    time_t rawtime;
    struct tm timeinfo;

    /*路径相关*/
    WCHAR * pStrOne = NULL;
    WCHAR * pStrTwo = NULL;
    WCHAR * pStrThree = NULL;
    UINT16_S  wTempZCID = DEFAULT_ZERO;
    static FILE *fpTRACE = NULL;/*打印文件对应的标识*/
    WCHAR chStrBuffOne[50];
    WCHAR chStrBuffTwo[50];
    WCHAR chStrBuffThree[50];
    WCHAR chStrBuffThird[50];	

    /*初始化局部数组*/
    memset(&chStrBuffOne[DEFAULT_ZERO],DEFAULT_ZERO,sizeof(WCHAR) * 50);
    memset(&chStrBuffTwo[DEFAULT_ZERO],DEFAULT_ZERO,sizeof(WCHAR) * 50);
    memset(&chStrBuffThree[DEFAULT_ZERO],DEFAULT_ZERO,sizeof(WCHAR) * 50);
    memset(&chStrBuffThird[DEFAULT_ZERO],DEFAULT_ZERO,sizeof(WCHAR) * 50);

    /*设置打印文件路径*/
    pStrOne = L"DebugData";
    pStrTwo = L"\\\\";
    pStrThree = L".log";
    wTempZCID = GetLocalZcId();

    /*将整型的ZCID转换成字符型*/
    _itow_s(wTempZCID,chStrBuffThree,50,10);

    /*拼接打印输出文件路径*/
    wcscat_s(chStrBuffOne,50,pStrOne);
    wcscat_s(chStrBuffOne,50,chStrBuffThree);
    wcscat_s(chStrBuffOne,50,pStrTwo); 

    wcscat_s(chStrBuffTwo,50,pStrOne);
    wcscat_s(chStrBuffTwo,50,chStrBuffThree);
    wcscat_s(chStrBuffTwo,50,pStrTwo);     


    if (FLAG_UNSET == gLogPrintfType)
    {
        /*不记录数据*/
        if (NULL != fpTRACE)
        {
            fclose(fpTRACE);
            fpTRACE = NULL;
        } 
        else
        {
            /*Do nothing currently !*/
        }
    }
    else if(FLAG_SET == gLogPrintfType)
    {
        /* 记录日志 */
        if (NULL == fpTRACE)
        {
            /*创建一个文件*/
            if (szFileName == NULL)
            {
                /*创建一个默认的目录和默认的文件*/
                CreateDirectory(chStrBuffOne,NULL);
                time ( &rawtime );
                localtime_s(&timeinfo,&rawtime);
                swprintf(chStrBuffThird,40,L"%4d年%2d月%2d日_%2d_%2d_%2d",1900+timeinfo.tm_year,1+timeinfo.tm_mon,timeinfo.tm_mday,
                    timeinfo.tm_hour,timeinfo.tm_min,timeinfo.tm_sec); 
                wcscat_s(chStrBuffTwo,50,chStrBuffThird);
                wcscat_s(chStrBuffTwo,50,pStrThree);
                if ((fpTRACE = _wfopen(chStrBuffTwo, L"a+")) == NULL) /*追加形式创建*/
                {
                    iResult = -1;
                }
            }
            else
            {
                /*在这里不对路径的合法性作判断*/
                /*创建这个文件*/
                fopen_s(&fpTRACE,szFileName, "a+");

                /*追加形式创建*/
                if (fpTRACE == NULL) 
                {
                    iResult = -1;
                }
            }
        }

        if (filelength(fileno(fpTRACE)) >= 51200000)
        {
            /*关闭原来的文件*/
            fclose(fpTRACE);
            /*创建一个默认的目录和默认的文件*/
            CreateDirectory(chStrBuffOne,NULL);
            time ( &rawtime );
            localtime_s(&timeinfo,&rawtime);
            swprintf(chStrBuffThird,40,L"%4d年%2d月%2d日_%2d_%2d_%2d",1900+timeinfo.tm_year,1+timeinfo.tm_mon,timeinfo.tm_mday,
                timeinfo.tm_hour,timeinfo.tm_min,timeinfo.tm_sec);
            wcscat_s(chStrBuffTwo,50,chStrBuffThird);
            wcscat_s(chStrBuffTwo,50,pStrThree);
            if ((fpTRACE = _wfopen(chStrBuffTwo, L"a+")) == NULL) /*追加形式创建*/
            {
                iResult = -1;
            }
        }

        iResult = fprintf(fpTRACE, "%s", lpszFormat);

        if (iResult != -1)
        {
            fflush(fpTRACE);
        }
    }
    else
    {
        /* 不处理 */
    }

    return iResult;
}
#endif

/*************************************************
  函数名:      LogPrintBuff
  功能描述:    将缓冲区数据转化为字符串
  输入:        const UINT8_S dataBuf[]， 数组首地址
               const UINT16_S bufLength,数组长度
               const UINT16_S dataLength 数据长度
  输出:        无
  返回值:      0U,失败
               1U,成功
*************************************************/
#ifdef SYS_TYPE_WINDOWS
UINT8_S LogPrintBuff(const UINT8_S dataBuf[],const UINT16_S bufLength,const UINT16_S dataLength)
{

    UINT16_S i = 0u;
    UINT8_S retVal = 0u;

    if (( dataBuf != NULL ) && (bufLength >= dataLength))
    {
        for (i = 0u; i < dataLength; i++)
        {
            LogPrintf(1u,"%02x ", dataBuf[i]);
        }
        LogPrintf(1u,"\n");

        retVal = 1u;
    }
    else
    {
        retVal = 0u;
    }

    return retVal;
}
#endif

/*************************************************
  函数名:      LogBufPeriodClear
  功能描述:    将缓冲区清空
  输入:        无
  输出:        无
  返回值:      0无
*************************************************/
void LogBufPeriodClear(void)
{
    MemorySet(gMaintainDataArr1, MAINTAIN_DATA_LEN_MAX, 0u, MAINTAIN_DATA_LEN_MAX);
    gMaintainLen1 = 0u;
}

/*************************************************
  函数名:      GetgMaintainDataArr
  功能描述:    获取日志字节数组的首地址
  输入:        无
  输出:        无
  返回值:      数组首地址
*************************************************/
UINT8_S *GetgMaintainDataArr(void)
{
    return gMaintainDataArr1;
}

/*************************************************
  函数名:      GetgMaintainLen
  功能描述:    获取日志数组中字节的数量
  输入:        无
  输出:        无
  返回值:      字节长度
*************************************************/
UINT32_S *GetgMaintainLen(void)
{
    return &gMaintainLen1;
}
