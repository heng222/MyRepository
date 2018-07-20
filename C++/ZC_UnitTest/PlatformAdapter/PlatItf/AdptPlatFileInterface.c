/********************************************************
* 
* �� �� ���� AdptPlatFileInterface.c
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-01 
* ���������� ������ṩ��ƽ̨����ļ������ӿ��ļ�  
* ��    ע�� �� 
* 
********************************************************/ 

#include "../../cspadpt/GL_Basic_Type_Definition.h"
#include "AdptPlatFileInterface.h"
#include "../../cspadpt/Vcp_File_Interface.h"
#include "../../Common/MemSet.h"
/*
*  �����������ж��ļ��Ƿ���ں���
*  ����˵��:const CHAR* fileName  �ļ�����
*  ����ֵ:    1����   0 ������
*/
UINT8_S AdptPlatFileExist(const CHAR_S* fileName)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    E_SysBool retIsExit = e_FALSE;/*�ļ��Ƿ����*/

    if ( fileName != NULL )
    {
        retIsExit = F_VCP_FileExist(fileName);

        if (retIsExit == e_TRUE)
        {
            retVal = 1u;
        } 
        else
        {
            retVal = 0u;
        }
    }

    return retVal;
}

/*
*  ������������ȡ�ļ���Ϣ
*  ����˵��:  inFileName    : �����ļ���
*             outFileDetail : ����ļ���Ϣ(����ΪptrNULL)
*  ����ֵ:    1��ȡ�ɹ�   0 ��ȡʧ��
*  ע: ��һ��������д���ļ��ú�����Ч
*/
UINT8_S AdptPlatFileInquire(const CHAR_S* fileName, AdptFileDetailStruct* outFileDetail)
{
    UINT8_S retVal = 0u;
    E_SysBool result = e_FALSE;
    T_VCP_FileDetail vcpFileDetail = {0u};

    if ((NULL != outFileDetail) && (NULL != fileName))
    {
        result = F_VCP_FileInquire(fileName,&vcpFileDetail);

        if(e_TRUE == result)
        {
            outFileDetail->Size = vcpFileDetail.Size;

            outFileDetail->CTime.Year = vcpFileDetail.CTime.Year;
            outFileDetail->CTime.Month = vcpFileDetail.CTime.Month;
            outFileDetail->CTime.Day = vcpFileDetail.CTime.Day;
            outFileDetail->CTime.MiSec = vcpFileDetail.CTime.MiSec;

            outFileDetail->LTime.Year = vcpFileDetail.LTime.Year;
            outFileDetail->LTime.Month = vcpFileDetail.LTime.Month;
            outFileDetail->LTime.Day = vcpFileDetail.LTime.Day;
            outFileDetail->LTime.MiSec = vcpFileDetail.LTime.MiSec;

            retVal = 1u;
        }
        else
        {
            retVal = 0u;
        }
    }

    return retVal;
}


/*
*  ����������  �ļ��򿪺���
*  ����˵��:const char* fileName        �ļ��ĵ�ַ
*            const UINT8 openMode        �ļ��򿪷�ʽ        
*            FILEType *pfile                ���
*  ����ֵ:    1�ɹ�   0 ʧ��
*/
UINT8_S AdptPlatFileOpen(const CHAR_S* fileName, const UINT8_S openMode, FILEType *pfile)
{
    UINT8_S  retVal = 0u;/*��������ֵ*/
    INT32_S  tmpRet = 0;/*��������ֵ*/

    if ((NULL != pfile) && (NULL != fileName))
    {
        switch (openMode)
        {
            case AdptFOpenRead:
                tmpRet = F_VCP_FileOpen(fileName, e_VCP_FOpenRead, pfile);
                break;
            case AdptFOpenWrite:
                tmpRet = F_VCP_FileOpen(fileName, e_VCP_FOpenWrite, pfile);
                break;
            case AdptFOpenWriteNCheck:
                tmpRet = F_VCP_FileOpen(fileName, e_VCP_FOpenWriteNCheck, pfile);
                break;
            case AdptFOpenExchange:
                tmpRet = F_VCP_FileOpen(fileName, e_VCP_FOpenExchange, pfile);
                break;
            default:
                break;
        }

        if (c_VCP_FOpenOk == tmpRet)
        {
            retVal = 1u;
        } 
        else
        {
            retVal = 0u;
        }
    }

    return retVal;
}

/*
*  ���������� �ļ���ȡ����
*  ����˵��:    const FILEType pfile                
*            const CHAR* fileName        �������ļ�
*            UINT8* dataBuf                ���ݴ洢����
            UINT32 count                �����С
*  ����ֵ:    0 ��ȡʧ��   >0 �ļ���С
*/
UINT32_S AdptPlatFileRead (const FILEType pfile,const CHAR_S* fileName,UINT8_S* dataBuf, UINT32_S count)
{
    UINT32_S dataLen = 0u;/*��ȡ���ݳ���*/
    E_SysBool tmpRetVal = e_FALSE;/*��������ֵ*/
    T_VCP_FileDetail outFileDetail = {0u};
    INT32_S retRead = 0;/*��ȡ�Ƿ�ɹ�*/

    if ((NULL != dataBuf) && (NULL != fileName))
    {
        MemorySet(&outFileDetail, sizeof(T_VCP_FileDetail), 0u, sizeof(T_VCP_FileDetail));

        retRead = F_VCP_FileRead(pfile, count, dataBuf);

        if (retRead == c_VCP_FReadDone)
        {
            tmpRetVal = F_VCP_FileInquire(fileName, &outFileDetail);

            if (e_TRUE == tmpRetVal)
            {
                dataLen = outFileDetail.Size;
            }
        }
    }


    return dataLen;
}

/*
*  �����������ļ�д����
*  ����˵��:const FILEType* fileHUsr,const UINT32 writeLen,UINT8Type writeDataBuf
*  ����ֵ:    1д�ɹ�   0 дʧ��
*/
UINT8_S AdptPlatFileWrite(const FILEType fileHUsr, const UINT32_S writeLen, UINT8_S *writeDataBuf)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    INT32_S retLen = 0;/*�ļ�д����ֵ*/

    if (NULL != writeDataBuf)
    {
        retLen = F_VCP_FileWrite(fileHUsr, writeLen, writeDataBuf);

        if (retLen == c_VCP_FWriteDone)
        {
            retVal = 1u;
        } 
        else
        {
            retVal = 0u;
        }
    }

    return retVal;
}


/*
*  ����������  �ļ��رպ����ļ��������ͷž��
*  ����˵��:FILEType *pfile                ������ļ�
*  ����ֵ:    1�ɹ�   0 ʧ��
*/
UINT8_S AdptPlatFileClose(FILEType fileHUsr)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    INT32_S retClose = 0;/*�ر��Ƿ�ɹ�*/

    retClose = F_VCP_FileClose(fileHUsr, e_TRUE);

    if (retClose == c_VCP_FCloseFinish)
    {
        retVal = 1u;
    } 
    else
    {
        retVal = 0u;
    }

    return retVal;
}

/*
*  ����������  �ļ��ͷž�� 
*  ����˵��:FILEType *pfile                ������ļ�
*  ����ֵ:    1�ɹ�   0 ʧ��
*/
UINT8_S AdptPlatFileRelease(FILEType fileHUsr)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    INT32_S retRelease = 0;/*�ر��Ƿ�ɹ�*/

    retRelease = F_VCP_FileHandleRelease(fileHUsr);

    if (retRelease == c_VCP_FRlsSuccess)
    {
        retVal = 1u;
    } 
    else
    {
        retVal = 0u;
    }

    return retVal;
}


/*
*  �����������ļ�ɾ������
*  ����˵��:const CHAR* fileName  �ļ�����
*  ����ֵ:    1ɾ���ɹ�   0 ɾ��ʧ��
*/
UINT8_S AdptPlatFileDelete(const CHAR_S* fileName, FILEType* fileHUsr)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    INT32_S retDelete = 0;/*�ļ�ɾ������ֵ*/

    if ((NULL != fileHUsr) && (NULL != fileName))
    {
        retDelete = F_VCP_FileDelete(fileName,fileHUsr);

        if (retDelete == c_VCP_FDeleteFinish)
        {
            retVal = 1u;
        } 
        else
        {
            retVal = 0u;
        }
    }

    return retVal;
}
/*
*  ������������ѯ�ļ����״̬
*  ����˵��:   fileName  �ļ�����
*              outProgress �������
*  ����ֵ:   ��ѯ����״̬
*/
UINT8_S AdptPlatFileStatusInquire(const FILEType inHUsr, AdptProgressStruct* outProgress)
{
    UINT8_S retVal = 0u;
    INT32_S fileStatus = 0;
    T_VCP_Progress vcpProgress = {0u};

    fileStatus = F_VCP_FileStatusInquire(inHUsr,&vcpProgress); /*��ѯ�ļ�״̬*/

    if(NULL != outProgress)
    {
        outProgress->Done = vcpProgress.Done;
        outProgress->LastQuota = vcpProgress.LastQuota;
        outProgress->Total = vcpProgress.Total;

    }

    if (fileStatus == c_VCP_FInqFinish)
    {
        retVal = FILE_INQ_FINISH;
    } 
    else if (fileStatus == c_VCP_FInqDone)
    {
        retVal = FILE_INQ_REQ_DONE;
    }
    else if (fileStatus == c_VCP_FInqErrHandle)
    {
        retVal = FILE_INQ_ERR_HANDLE;
    }
    else
    {
        retVal = FILE_INQ_ERR_FATAL;
    }

    return retVal;
}

/*
*  ������������ѯ��һ�����ļ�״̬�ʹ�С 
*  ����˵��:   inHUsr  �ļ���� 
*              outStatus �ļ�״̬ 
*              size �ļ���С
*  ����ֵ:   0 ��ѯʧ��  1 ��ѯ�ɹ�
*/
UINT8_S AdptPlatFileExcStatusInquire(const FILEType inHUsr, UINT8_S* outStatus, UINT32_S* size)
{
    UINT8_S retVal = 0u;
    E_SysBool tempRet = e_FALSE;
    INT32_S fileStatus = 0u;
    T_VCP_FileExInfo outExInfo = {0u};

    tempRet = F_VCP_FileExInfoInquire(inHUsr, &outExInfo);

    if ( e_TRUE == tempRet )
    {
        fileStatus = outExInfo.OperateInfo.Status;

        if (fileStatus == c_VCP_FInqFinish)
        {
            *outStatus = FILE_INQ_FINISH;
        } 
        else if (fileStatus == c_VCP_FInqDone)
        {
            *outStatus = FILE_INQ_REQ_DONE;
        }
        else if (fileStatus == c_VCP_FInqErrHandle)
        {
            *outStatus = FILE_INQ_ERR_HANDLE;
        }
        else
        {
            *outStatus = FILE_INQ_ERR_FATAL;
        }

        *size = outExInfo.ExistInfo.Detail.Size;

        retVal = 1u;
    }
    else
    {
        *outStatus = FILE_INQ_ERR_HANDLE;
        *size = 0u;

        retVal = 0u;
    }

    return retVal;
}

