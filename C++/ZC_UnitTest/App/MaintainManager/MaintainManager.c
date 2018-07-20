/********************************************************                                                                                                            
 �� �� ���� MaintainManager.c
 ��    �ߣ� ZC��
 ����ʱ�䣺 2015-04-18
 ������ ά����־����
 ��ע�� ��  
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
char chTempDebugArray[10000];           /*�����ӡǰ�ַ�����Ϣ*/ 

UINT8_S gLogPrintfType = 0xaaU;

/*************************************************
  ������:      SetLogPrintfType
  ��������:    ���ô�ӡlog��Ϣ����
  ����:        const UINT8_S logPrintfType ��¼��־��ʶ
  ���:        ��
  ����ֵ:      ��
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
  ������:      LogPrintf
  ��������:    ��ӡlog��Ϣ(Windows�����־��ӡ)
  ����:        UINT8_S chRunSystem, ��ʶ
               const char * lpszFormat ָ��
  ���:        ��
  ����ֵ:      0u ʧ��
               1u �ɹ�
*************************************************/
#ifdef SYS_TYPE_WINDOWS
UINT8_S LogPrintf(UINT8_S chRunSystem, const char * lpszFormat, ...)
{
#if 1
    UINT8_S retVal = 1U;
    va_list arg_ptr; 
    int n = 0;

    /*char chTempDebugArray[10000];*/           /*�����ӡǰ�ַ�����Ϣ*/ 

    MemorySet(&chTempDebugArray[0],(UINT32_S)(10000*SIZE_UINT8),DEFAULT_ZERO,(UINT32_S)(10000*SIZE_UINT8));

    /*��ʼ���ӵ�����������ʼ����*/
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
                /* Ԥ��Ϊ����log��¼��ʽ������д�ļ�֮�� */
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
  ������:      LogPrintf_Windows
  ��������:    ��ӡWindows��log��Ϣ
  ����:        const char * szFileName, �ļ���
               const char * lpszFormat, ָ��
               const UINT32_S dwLength, ����
  ���:        ��
  ����ֵ:      -1:  ʧ��
               !=-1: �ɹ�
*************************************************/
#ifdef SYS_TYPE_WINDOWS
INT32_S LogPrintf_Windows(const char * szFileName, const char * lpszFormat,const UINT32_S dwLength)
{

    INT32_S  iResult = 0;  /*��¼���ؽ��*/
    time_t rawtime;
    struct tm timeinfo;

    /*·�����*/
    WCHAR * pStrOne = NULL;
    WCHAR * pStrTwo = NULL;
    WCHAR * pStrThree = NULL;
    UINT16_S  wTempZCID = DEFAULT_ZERO;
    static FILE *fpTRACE = NULL;/*��ӡ�ļ���Ӧ�ı�ʶ*/
    WCHAR chStrBuffOne[50];
    WCHAR chStrBuffTwo[50];
    WCHAR chStrBuffThree[50];
    WCHAR chStrBuffThird[50];	

    /*��ʼ���ֲ�����*/
    memset(&chStrBuffOne[DEFAULT_ZERO],DEFAULT_ZERO,sizeof(WCHAR) * 50);
    memset(&chStrBuffTwo[DEFAULT_ZERO],DEFAULT_ZERO,sizeof(WCHAR) * 50);
    memset(&chStrBuffThree[DEFAULT_ZERO],DEFAULT_ZERO,sizeof(WCHAR) * 50);
    memset(&chStrBuffThird[DEFAULT_ZERO],DEFAULT_ZERO,sizeof(WCHAR) * 50);

    /*���ô�ӡ�ļ�·��*/
    pStrOne = L"DebugData";
    pStrTwo = L"\\\\";
    pStrThree = L".log";
    wTempZCID = GetLocalZcId();

    /*�����͵�ZCIDת�����ַ���*/
    _itow_s(wTempZCID,chStrBuffThree,50,10);

    /*ƴ�Ӵ�ӡ����ļ�·��*/
    wcscat_s(chStrBuffOne,50,pStrOne);
    wcscat_s(chStrBuffOne,50,chStrBuffThree);
    wcscat_s(chStrBuffOne,50,pStrTwo); 

    wcscat_s(chStrBuffTwo,50,pStrOne);
    wcscat_s(chStrBuffTwo,50,chStrBuffThree);
    wcscat_s(chStrBuffTwo,50,pStrTwo);     


    if (FLAG_UNSET == gLogPrintfType)
    {
        /*����¼����*/
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
        /* ��¼��־ */
        if (NULL == fpTRACE)
        {
            /*����һ���ļ�*/
            if (szFileName == NULL)
            {
                /*����һ��Ĭ�ϵ�Ŀ¼��Ĭ�ϵ��ļ�*/
                CreateDirectory(chStrBuffOne,NULL);
                time ( &rawtime );
                localtime_s(&timeinfo,&rawtime);
                swprintf(chStrBuffThird,40,L"%4d��%2d��%2d��_%2d_%2d_%2d",1900+timeinfo.tm_year,1+timeinfo.tm_mon,timeinfo.tm_mday,
                    timeinfo.tm_hour,timeinfo.tm_min,timeinfo.tm_sec); 
                wcscat_s(chStrBuffTwo,50,chStrBuffThird);
                wcscat_s(chStrBuffTwo,50,pStrThree);
                if ((fpTRACE = _wfopen(chStrBuffTwo, L"a+")) == NULL) /*׷����ʽ����*/
                {
                    iResult = -1;
                }
            }
            else
            {
                /*�����ﲻ��·���ĺϷ������ж�*/
                /*��������ļ�*/
                fopen_s(&fpTRACE,szFileName, "a+");

                /*׷����ʽ����*/
                if (fpTRACE == NULL) 
                {
                    iResult = -1;
                }
            }
        }

        if (filelength(fileno(fpTRACE)) >= 51200000)
        {
            /*�ر�ԭ�����ļ�*/
            fclose(fpTRACE);
            /*����һ��Ĭ�ϵ�Ŀ¼��Ĭ�ϵ��ļ�*/
            CreateDirectory(chStrBuffOne,NULL);
            time ( &rawtime );
            localtime_s(&timeinfo,&rawtime);
            swprintf(chStrBuffThird,40,L"%4d��%2d��%2d��_%2d_%2d_%2d",1900+timeinfo.tm_year,1+timeinfo.tm_mon,timeinfo.tm_mday,
                timeinfo.tm_hour,timeinfo.tm_min,timeinfo.tm_sec);
            wcscat_s(chStrBuffTwo,50,chStrBuffThird);
            wcscat_s(chStrBuffTwo,50,pStrThree);
            if ((fpTRACE = _wfopen(chStrBuffTwo, L"a+")) == NULL) /*׷����ʽ����*/
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
        /* ������ */
    }

    return iResult;
}
#endif

/*************************************************
  ������:      LogPrintBuff
  ��������:    ������������ת��Ϊ�ַ���
  ����:        const UINT8_S dataBuf[]�� �����׵�ַ
               const UINT16_S bufLength,���鳤��
               const UINT16_S dataLength ���ݳ���
  ���:        ��
  ����ֵ:      0U,ʧ��
               1U,�ɹ�
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
  ������:      LogBufPeriodClear
  ��������:    �����������
  ����:        ��
  ���:        ��
  ����ֵ:      0��
*************************************************/
void LogBufPeriodClear(void)
{
    MemorySet(gMaintainDataArr1, MAINTAIN_DATA_LEN_MAX, 0u, MAINTAIN_DATA_LEN_MAX);
    gMaintainLen1 = 0u;
}

/*************************************************
  ������:      GetgMaintainDataArr
  ��������:    ��ȡ��־�ֽ�������׵�ַ
  ����:        ��
  ���:        ��
  ����ֵ:      �����׵�ַ
*************************************************/
UINT8_S *GetgMaintainDataArr(void)
{
    return gMaintainDataArr1;
}

/*************************************************
  ������:      GetgMaintainLen
  ��������:    ��ȡ��־�������ֽڵ�����
  ����:        ��
  ���:        ��
  ����ֵ:      �ֽڳ���
*************************************************/
UINT32_S *GetgMaintainLen(void)
{
    return &gMaintainLen1;
}
