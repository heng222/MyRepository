/********************************************************
*                                                                                                            
* �� �� ���� AdapterFileHandle.h   
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-01
* ���������� ƽ̨������ļ�����ͷ�ļ� 
* ��    ע�� �� 
*
********************************************************/ 

#ifndef ADAPTER_FILE_HANDLE_H_
#define ADAPTER_FILE_HANDLE_H_


#include "../../Common/CommonTypes.h"
#include "../PlatItf/AdptPlatFileInterface.h"
#include "../PlatItf/AdptPlatBasicTypeDefinition.h"
#include "../PlatItf/AdptPlatFileInterface.h"

#define FileWriteCycMax     20u                /*д�ļ���ʱ����(���ں�)*/
#define FILE_NAME_MAX_LEN   32u                /*�ļ�������*/

 /*��ǰ�����ļ���״̬*/
typedef enum FileStatus
{
    e_File_First = 1u,
    e_File_Second = 2u
}E_FileStatus;


/*д�ļ�����״̬ת�ƶ���*/
typedef enum WriteStatus
{
    e_Init   = 1u,
    e_Open   = 2u,
    e_Write  = 3u,
    e_Delete = 4u,
    e_Close  = 5u,
    e_Error  = 6u,
    e_Sync   = 7u,
    e_Sucess = 8u
}E_WriteStatus;

#ifdef __cplusplus
extern "C" {
#endif

/*
*  ����������  �����ļ���������������ļ�����
*  ����˵��:str1        ��һ���ļ�������
*            str2        �ڶ����ļ�������
*  ����ֵ:    ��
*/
UINT8_S AdapterSetCfgFileName(CHAR_S name1[],UINT8_S nameLen1, CHAR_S name2[],  UINT8_S nameLen2);

/*
*  ����������  ���ļ�����,�������ļ���ѡȡ���µĶ�ȡ
*  ����˵��:   UINT8* pBuff,       �����ȡ������
*              UINT32_S buffLength,  �����ȡ���ݳ���
*  ����ֵ:       readDataLen,0��ȡʧ��;>0��ȡ�ɹ�
*/
UINT32_S AdapterFileReadProc(UINT8_S* buff, UINT32_S buffLength);


/*
*  ����������  ������ѭ��д�ļ�����
*  ����˵��:   UINT8* pBuff,       ����д�ļ�����
*              UINT32_S buffLength�� ����д�ļ����ݳ���
*  ����ֵ:       returnValue���ļ�д�����������״̬
*/
E_WriteStatus AdapterCycleWriteFile(UINT8_S* pBuff, UINT32_S buffLength);


#ifdef __cplusplus
}
#endif

#endif
