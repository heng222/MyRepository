/********************************************************
*                                                                                                            
* �� �� ���� AdptAppFileInterface.h   
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-01
* ���������� ƽ̨������ṩ��Ӧ�õĽӿ�ͷ�ļ� 
* ��    ע�� �� 
*
********************************************************/ 

#ifndef ADPT_APP_FILE_INTERFACE_H_
#define ADPT_APP_FILE_INTERFACE_H_


#include "../../Common/CommonTypes.h"
#include "../PlatItf/AdptPlatFileInterface.h"

#define FILE_WRITE_PRO_ERROR     0u
#define FILE_WRITE_PRO_SUCC      1u
#define FILE_WRITE_PRO_WRITTING  2u


#ifdef __cplusplus
extern "C" {
#endif

/* 
*  ����������  ����Ӧ������������ļ�����
*  ����˵��:str1        ��һ���ļ�������
*            str2        �ڶ����ļ�������
*  ����ֵ:    ��
*/
UINT8_S AdptAppSetCfgFileName(CHAR_S name1[],UINT8_S nameLen1, CHAR_S name2[],    UINT8_S nameLen2);

/*
*  �����������ж��ļ��Ƿ���ں���
*  ����˵��:const CHAR* fileName  �ļ�����
*  ����ֵ:    1����   0 ������
*/
UINT8_S AdptAppFileExist(const CHAR_S* fileName);

/*
*  ������������ȡ�ļ���Ϣ
*  ����˵��:inFileName    : �����ļ���
*           outFileDetail : ����ļ���Ϣ(����ΪptrNULL)
*  ����ֵ:    1��ȡ�ɹ�   0 ��ȡʧ��
*/
UINT8_S AdptAppFileInquire(const CHAR_S* fileName, AdptFileDetailStruct* outFileDetail);

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
*  ����ֵ:    1�ɹ�   0 ʧ��
*/
UINT32_S AdptAppFileOpen(const CHAR_S* fileName, const UINT8_S openMode,FILEType *pfile);

/*
*  ���������� �ļ���ȡ����
*  ����˵��:  const FILEType pfile     ������
*             const CHAR* fileName     �����ļ���
*             UINT8* dataBuf           ������ݴ洢����
*             UINT32_S count             ���ݴ洢��������С
*  ����ֵ:    0 ��ȡʧ��   >0 �ļ���С
*/
UINT32_S AdptAppFileRead (const FILEType pfile, const CHAR_S* fileName, UINT8_S* dataBuf, UINT32_S count);

/*
*  �����������ļ�д����
*  ����˵��:  const FILEType* fileHUsr, �ļ����
*             const UINT32_S writeLen,    д�����ݳ���
*             UINT8Type writeDataBuf,   д�����ݻ���
*  ����ֵ:    1д�ɹ�   0 дʧ��
*/
UINT8_S AdptAppFileWrite(const FILEType fileHUsr, const UINT32_S writeLen, UINT8_S * writeDataBuf);

/*
*  ����������  �ļ��رպ���
*  ����˵��:FILEType *pfile                �ļ����
*  ����ֵ:    1�ɹ�   0 ʧ��
*/
UINT8_S AdptAppFileClose(FILEType fileHUsr);

/*
*  �����������ļ�ɾ������
*  ����˵��:const CHAR* fileName  �����ļ�����
*           FILEType* fileHUsr    ������
*  ����ֵ:    1ɾ���ɹ�   0 ɾ��ʧ��
*/
UINT8_S AdptAppFileDelete(const CHAR_S* fileName, FILEType* fileHUsr);

/*
*  ����������  ���ļ�����
*  ����˵��:   UINT8* pBuff,       �����ȡ������
*              UINT32_S buffLength,  �����ȡ���ݳ���
*  ����ֵ:       readDataLen,0��ȡʧ��;>0��ȡ�ɹ�
*/
UINT32_S AdptAppFileReadProc(UINT8_S* buff, UINT32_S buffLength);

/*
*  ����������  д�ļ�����
*  ����˵��:   UINT8* pBuff, UINT32_S buffLength
*  ����ֵ:       returnValue���ļ�д�����������״̬
*                0,ʧ��
*                1,�ɹ�
*                2,������
*/
UINT8_S AdptAppCycleWriteFile(UINT8_S* pBuff, UINT32_S buffLength);

#ifdef __cplusplus
}
#endif

#endif



