/********************************************************
*                                                                                                            
* �� �� ���� AdptAppFileInterface.c   
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-01
* ���������� ƽ̨������ṩ��Ӧ�õĽӿ� 
* ��    ע�� �� 
*
********************************************************/ 

#include "AdptAppFileInterface.h"
#include "../AdptHandle/AdapterFileHandle.h"
#include "../../Common/MemSet.h"
#include "../PlatformLog/AdapterLog.h"
#include "../../Common/Copy.h"

/*
*  ����������  ����Ӧ������������ļ�����
*  ����˵��:name1        ��һ���ļ�������
*             nameLen1  ��һ���ļ��ĳ��� 
*            name2        �ڶ����ļ�������
*            nameLen2  �ڶ����ļ��ĳ���
*  ����ֵ:    1,�ɹ�    0,ʧ��
*/
UINT8_S AdptAppSetCfgFileName(CHAR_S name1[],UINT8_S nameLen1, CHAR_S name2[],  UINT8_S nameLen2)
{
    UINT8_S retVal = 0u;

    retVal = AdapterSetCfgFileName(name1,nameLen1,name2,nameLen2);

    return retVal;
}




/*
*  �����������ж��ļ��Ƿ���ں���
*  ����˵��:const CHAR* fileName  �ļ�����
*  ����ֵ:    1����   0 ������
*/
UINT8_S AdptAppFileExist(const CHAR_S* fileName)
{
    UINT8_S retVal = 0u;/*��������ֵ*/

    if ( fileName != NULL )
    {
        retVal = AdptPlatFileExist(fileName);
    }

    return retVal;
}

/*
*  ������������ȡ�ļ���Ϣ
*  ����˵��:inFileName    : �����ļ���
*           outFileDetail : ����ļ���Ϣ(����ΪptrNULL)
*  ����ֵ:    1��ȡ�ɹ�   0 ��ȡʧ��
*/
UINT8_S AdptAppFileInquire(const CHAR_S* fileName, AdptFileDetailStruct* outFileDetail)
{
    UINT8_S result = 0u;

    if (( fileName != NULL ) && ( outFileDetail != NULL ))
    {
        result = AdptPlatFileInquire(fileName, outFileDetail);
    }
    return result;
}

/*
*  ����������  �ļ��򿪺���
*  ����˵��:
*  �������: const char* fileName        �����ļ���
*            const UINT8 openMode        �ļ��򿪷�ʽ        
*                    0,  ����ʽ���ļ�
*                    1,  д���ļ���ʽ���ļ�, ��У��
*                    2,  д���ļ���ʽ���ļ�, ��У��
*                    3,  �ļ���Ϣ����
*  �������: *pfile                ���
*
*  ����ֵ:    1�ɹ�   0 ʧ��
*/
UINT32_S AdptAppFileOpen(const CHAR_S* fileName, const UINT8_S openMode,FILEType *pfile)
{
    UINT32_S  retVal = 0u;/*��������ֵ*/

    if (( fileName != NULL ) && ( pfile != NULL ))
    {
        retVal = AdptPlatFileOpen(fileName, openMode, pfile);
    }

    return retVal;
}

/*
*  ���������� �ļ���ȡ����
*  ����˵��:  const FILEType pfile     ������
*             const CHAR* fileName     �����ļ���
*             UINT8* dataBuf           ������ݴ洢����
*             UINT32_S count             ���ݴ洢��������С
*  ����ֵ:    0 ��ȡʧ��   >0 �ļ���С
*/
UINT32_S AdptAppFileRead (const FILEType pfile, const CHAR_S* fileName, UINT8_S* dataBuf, UINT32_S count)
{
    UINT32_S dataLen = 0u;/*��ȡ���ݳ���*/

    if (( fileName != NULL ) && ( dataBuf != NULL ))
    {
        dataLen = AdptPlatFileRead(pfile, fileName, dataBuf, count);
    }

    return dataLen;
}

/*
*  �����������ļ�д����
*  ����˵��:  const FILEType* fileHUsr, �ļ����
*             const UINT32_S writeLen,    д�����ݳ���
*             UINT8Type writeDataBuf,   д�����ݻ���
*  ����ֵ:    1д�ɹ�   0 дʧ��
*/
UINT8_S AdptAppFileWrite(const FILEType fileHUsr, const UINT32_S writeLen, UINT8_S * writeDataBuf)
{
    UINT8_S retVal = 0u;/*��������ֵ*/

    if ( writeDataBuf != NULL )
    {
        retVal = AdptPlatFileWrite(fileHUsr, writeLen, writeDataBuf);
    }

    return retVal;
}

/*
*  ����������  �ļ��رպ���
*  ����˵��:FILEType *pfile                �ļ����
*  ����ֵ:    1�ɹ�   0 ʧ��
*/
UINT8_S AdptAppFileClose(FILEType fileHUsr)
{
    UINT8_S retVal = 0u;/*��������ֵ*/

    retVal = AdptPlatFileClose(fileHUsr);

    return retVal;
}

/*
*  �����������ļ�ɾ������
*  ����˵��:const CHAR* fileName  �����ļ�����
*           FILEType* fileHUsr    ������
*  ����ֵ:    1ɾ���ɹ�   0 ɾ��ʧ��
*/
UINT8_S AdptAppFileDelete(const CHAR_S* fileName, FILEType* fileHUsr)
{
    UINT8_S retVal = 0u;/*��������ֵ*/

    if (( fileName != NULL ) && ( fileHUsr != NULL ))
    {
        retVal = AdptPlatFileDelete(fileName, fileHUsr);
    }

    return retVal;
}

/*
*  ����������  ���ļ�����,�������ļ���ѡȡ���µĶ�ȡ
*  ����˵��:   UINT8* pBuff,       �����ȡ������
*              UINT32_S buffLength,  �����ȡ���ݳ���
*  ����ֵ:       readDataLen,0��ȡʧ��;>0��ȡ�ɹ�
*/
UINT32_S AdptAppFileReadProc(UINT8_S* buff, UINT32_S buffLength)
{
    UINT32_S readDataLen = 0u;

    if ( buff != NULL )
    {
        readDataLen = AdapterFileReadProc(buff, buffLength);
    }

    return readDataLen;
}

/*
*  ����������  Ӧ������ѭ��д�ļ�����
*  ����˵��:   UINT8* pBuff, UINT32_S buffLength
*  ����ֵ:       returnValue���ļ�д�����������״̬
*                0,ʧ��
*                1,�ɹ�
*                2,������
*/
UINT8_S AdptAppCycleWriteFile(UINT8_S* pBuff, UINT32_S buffLength)
{
    UINT8_S retVal = 0u;
    E_WriteStatus retStatus = e_Init;

    if ( pBuff != NULL )
    {
        retStatus = AdapterCycleWriteFile (pBuff, buffLength);

        if (e_Sucess == retStatus)
        {
            retVal = FILE_WRITE_PRO_SUCC;
        }
        else if (e_Error == retStatus)
        {
            retVal = FILE_WRITE_PRO_ERROR;
        }
        else
        {
            retVal = FILE_WRITE_PRO_WRITTING;
        }
    }
    return retVal;
}


