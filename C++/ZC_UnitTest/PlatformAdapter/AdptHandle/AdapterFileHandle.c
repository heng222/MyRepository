/********************************************************
*                                                                                                            
* �� �� ���� AdapterFileHandle.c   
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-01
* ���������� ƽ̨������ļ������ļ� 
* ��    ע�� �� 
*
********************************************************/ 

#include "AdapterFileHandle.h"
#include "../PlatformLog/AdapterLog.h"
#include "../../Common/MemSet.h"
#include "../../Common/Copy.h"
#include "../PlatItf/AdptPlatFileInterface.h"

static E_WriteStatus gWriteStatus = e_Init;            /*�ļ�д����״̬ת�Ʊ���*/
static E_FileStatus gFileStatus = e_File_First;        /*�ļ�������״̬*/
static FILEType gFileHandle = 0L;                      /*�ļ��������*/
static CHAR_S* gpFileCurPath = NULL;                   /*��ǰ�����ļ�·��*/
static UINT8_S gWriteFileCycTimer = 0u;                 /*д�ļ���ʱ��*/

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
*  ����������  �����ļ���������������ļ�����
*  ����˵��:str1        ��һ���ļ�������
*            str2        �ڶ����ļ�������
*  ����ֵ:    ��
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
*  ����������  ���ļ�����,�������ļ���ѡȡ���µĶ�ȡ
*  ����˵��:   UINT8_S* pBuff,       �����ȡ������
*              UINT32_S buffLength,  �����ȡ���ݳ���
*  ����ֵ:       readDataLen,0��ȡʧ��;>0��ȡ�ɹ�
*/
UINT32_S AdapterFileReadProc(UINT8_S* buff, UINT32_S buffLength)
{
    UINT32_S readDataLen = 0u;
    UINT32_S rtnValue = 0u;
    UINT8_S chooseFile = 0u;
    CHAR_S* tempFilePath = NULL;

    if ( NULL != buff )
    {
        chooseFile = AdapterFileChooseByTime(gFilePathFirst,gFilePathSecond);  /*��ȡ����޸��ļ��ı��*/

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

                /* ��ǰ�����ʹ�õĽӿ�Ϊ�ܹ������ͷž����close�ӿ����Բ���Ҫ�ͷ� */
                /*AdptPlatFileRelease(gFileHandle);*/
            }
        }
    }

    return readDataLen;
}


/*
*  ����������  �����ļ�����ʱ���ȡ����������ļ�����
*  ����˵��:   const CHAR* fileName1���ļ�1���ƣ�const CHAR* fileName2���ļ�2����
*  ����ֵ:     1,fileName1�ļ�����޸�
*              2,fileName2�ļ�����޸�
*              0,ϵͳ����,����ֻ��һ���ļ���������
*/
static UINT8_S AdapterFileChooseByTime(const CHAR_S* fileName1,const CHAR_S* fileName2)
{
    UINT8_S rtnResult = 0u;
    UINT8_S retExist1 = 0u;/*��������ֵ*/
    UINT8_S retExist2 = 0u;/*��������ֵ*/
    UINT8_S retDetail1 = 0u;
    UINT8_S retDetail2 = 0u;

    AdptFileDetailStruct outFileDetail1;
    AdptFileDetailStruct outFileDetail2;

    if (( NULL != fileName1 ) && ( NULL != fileName2 ))
    {
        /*�ж��ļ�1�Ƿ����*/
        retExist1 = AdptPlatFileExist(fileName1);
        /*�ж��ļ�2�Ƿ����*/
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
*  �����������Ƚ������ļ��Ĵ���ʱ����Ⱥ�
*  ����˵��:AdptRealClk * CreateTime1, ��һ���ļ��Ĵ���ʱ��
*           AdptRealClk * CreateTime2, �ڶ����ļ��Ĵ���ʱ��
*  ����ֵ:  1  ��һ���ļ��󴴽�
*           2  �ڶ����ļ��󴴽�
*           0,ϵͳ����
*           �����ļ�ͬʱ������Ĭ���ļ�һ���´���
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
*  ����������  ������ѭ��д�ļ�����
*  ����˵��:   UINT8* pBuff,       ����д�ļ�����
*              UINT32_S buffLength�� ����д�ļ����ݳ���
*  ����ֵ:       returnValue���ļ�д�����������״̬
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
*  ����������  ������ѭ��д�ļ����������еĳ�ʼ������
*  ����˵��:   ��
*  ����ֵ:    1�ɹ�   0 ʧ��
*/
static UINT8_S AdapterCycleWriteFileInit(void)
{
    UINT8_S retVal = 0u;

    /* д�ļ�·��ѡ�� */
    AdapterFilePathChoose();

    if (1u == AdptPlatFileExist(gpFileCurPath))
    {
        retVal = AdptPlatFileDelete(gpFileCurPath, &gFileHandle);
        gWriteStatus = e_Open;
    }
    else
    {
        /*�������ļ�*/
        retVal = AdptPlatFileOpen(gpFileCurPath, (UINT8_S)AdptFOpenWrite, &gFileHandle);
        gWriteStatus = e_Write;
    }

    return retVal;
}


/*
*  ����������  ������ѭ��д�ļ����������еĴ򿪲���
*  ����˵��:   ��
*  ����ֵ:    1�ɹ�   0 ʧ��
*/
static UINT8_S AdapterCycleWriteFileOpen(void)
{
    UINT8_S retVal = 0u;
    AdptProgressStruct iProgress;
    UINT8_S fileStatus = 0u;         /*�ļ�״̬��ѯ��������ֵ*/

    fileStatus = AdptPlatFileStatusInquire(gFileHandle, &iProgress); /*��ѯ�ļ�״̬*/

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
*  ����������  ������ѭ��д�ļ����������е�д�����
*  ����˵��:   UINT8* pBuff,
*              UINT32_S buffLengh
*  ����ֵ:       1�ɹ�   0 ʧ��
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
        /*�ݲ�����*/
    }

    return retVal;
}
/*
*  ����������  ������ѭ��д�ļ����������еĹرղ���
*  ����˵��:   ��
*  ����ֵ:       1�ɹ�   0 ʧ��
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
*  ����������  ������ѭ��д�ļ���������������һ��ͬ������
*  ����˵��:   ��
*  ����ֵ:       1�ɹ�   0 ʧ��
*/
static UINT8_S AdapterCycleWriteFileSync(void)
{
    UINT8_S retVal = 0u;
    UINT8_S fileStatus = 0u;
    AdptProgressStruct iProgress;

    fileStatus = AdptPlatFileStatusInquire(gFileHandle, &iProgress);

    if(FILE_INQ_ERR_HANDLE == fileStatus)
    {

        /*  ���سɹ�֮ǰ��Ҫ�鿴��һ�����ļ�״̬��ȷ���ļ�����ͬ��  */
        AdptPlatFileOpen(gpFileCurPath, (UINT8_S)AdptFOpenExchange, &gFileHandle);
        retVal = 1u;
        gWriteStatus = e_Sucess;
    }

    return retVal;
}


/*
*  ����������  ������ѭ��д�ļ����������еĳɹ�����
*  ����˵��:   ��
*  ����ֵ:       1�ɹ�   0 ʧ��
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

    /* �жϽ�����Ϣ�����Ͳ�ѯ�����Ƿ�ɹ�  */
    if ((1u == excRet) && (1u == inqRet))
    {

        /* �ж��ļ���С�Ƿ���ͬ���ļ�״̬�Ƿ�һ�� */
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
*  ����������  д�ļ�·��ѡ��
*  ����˵��:   ��
*  ����ֵ:       ��
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
*    ��������������д�ļ���ʱ��
*    ����˵��:const UINT8 timer
*  ����ֵ:��
*/
static void AdapterSetWriteFileCycTimer(const UINT8_S timer)
{
    gWriteFileCycTimer = timer;
}

/*
*  �������������¼�ʱ��
*  ����˵��:��
*  ����ֵ:��
*/
static void AdapterUpdateWriteFileCycTimer(void)
{
    gWriteFileCycTimer++;
}

/*
*  ������������ȡ��ʱ��
*  ����˵��:��
*  ����ֵ:��ʱ��
*/
static UINT8_S AdapterGetWriteFileCycTimer(void)
{
    return gWriteFileCycTimer;
}

