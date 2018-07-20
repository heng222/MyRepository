/********************************************************
* 
* �� �� ���� AdptPlatFileInterface.h
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-01 
* ���������� ������ṩ��ƽ̨����ļ������ӿ�ͷ�ļ�  
* ��    ע�� �� 
* 
********************************************************/ 

#ifndef ADPT_PLAT_FILE_INTERFACE_H_
#define ADPT_PLAT_FILE_INTERFACE_H_

#include "AdptPlatBasicTypeDefinition.h"
#include "../../Common/CommonTypes.h"

/*��ѯ����״̬ */
/*���                        */
/*R: ���رճɹ�               */
/*W: д�رղ�У��ɹ�         */
/*D: ɾ���                   */
#define FILE_INQ_FINISH       1u
/*��������/��/д          */
#define FILE_INQ_REQ_DONE     2u
/*����ִ��ʧ��                */
#define FILE_INQ_ERR_FATAL    3u
/*��Ч�ľ��                  */
#define FILE_INQ_ERR_HANDLE   4u


/******************************************************************************
 *    Global Struct    Define Section
 ******************************************************************************/
/*�����ļ��򿪷�ʽ*/
typedef enum AdptFileOpenOption
{
  AdptFOpenRead        = 0u,  /*����ʽ���ļ�              */
  AdptFOpenWrite       = 1u,  /*д���ļ���ʽ���ļ�, ��У��*/
  AdptFOpenWriteNCheck = 2u,  /*д���ļ���ʽ���ļ�, ��У��*/
  AdptFOpenExchange    = 3u   /*�ļ���Ϣ����                */
}AdptFileOpenOpt;

/*����*/
typedef struct AdptProgress
{
  UINT32_S Total;     /* ��������             */
  UINT32_S Done;      /* �������             */
  UINT32_S LastQuota; /* ���һ������������� */
}AdptProgressStruct;

/*�����ļ���ϸ��Ϣ*/
typedef struct AdptFileDetail
{
  UINT32_S     Size ;  /*�ļ���С    */
  AdptRealClkStruct  CTime;  /*����ʱ��    */
  AdptRealClkStruct  LTime;  /*������ʱ��*/
}AdptFileDetailStruct;


#ifdef __cplusplus
extern "C" {
#endif

/*
*  �����������ж��ļ��Ƿ���ں���
*  ����˵��:const CHAR* fileName  �ļ�����
*  ����ֵ:    1����   0 ������
*/
UINT8_S AdptPlatFileExist(const CHAR_S* fileName);

/*
*  ������������ȡ�ļ���Ϣ
*  ����˵��:  inFileName    : �����ļ���
*             outFileDetail : ����ļ���Ϣ(����ΪptrNULL)
*  ����ֵ:    1��ȡ�ɹ�   0 ��ȡʧ��
*  ע: ��һ��������д���ļ��ú�����Ч
*/
UINT8_S AdptPlatFileInquire(const CHAR_S* fileName, AdptFileDetailStruct* outFileDetail);

/*
*  ����������  �ļ��򿪺���
*  ����˵��:const char* fileName        �ļ��ĵ�ַ
*            const UINT8 openMode        �ļ��򿪷�ʽ        
*            FILEType *pfile                ���
*  ����ֵ:    1�ɹ�   0 ʧ��
*/
UINT8_S AdptPlatFileOpen(const CHAR_S* fileName, const UINT8_S openMode, FILEType *pfile);


/*
*  ���������� �ļ���ȡ����
*  ����˵��:    const FILEType pfile                
*            const CHAR* fileName        �������ļ�
*            UINT8* dataBuf                ���ݴ洢����
            UINT32 count                �����С
*  ����ֵ:    0 ��ȡʧ��   >0 �ļ���С
*/
UINT32_S AdptPlatFileRead (const FILEType pfile,const CHAR_S* fileName,UINT8_S* dataBuf, UINT32_S count);


/*
*  �����������ļ�д����
*  ����˵��:const FILEType* fileHUsr,const UINT32 writeLen,UINT8Type writeDataBuf
*  ����ֵ:    1д�ɹ�   0 дʧ��
*/
UINT8_S AdptPlatFileWrite(const FILEType fileHUsr, const UINT32_S writeLen, UINT8_S *writeDataBuf);


/*
*  ����������  �ļ��رպ���
*  ����˵��:FILEType *pfile                ������ļ�
*  ����ֵ:    1�ɹ�   0 ʧ��
*/
UINT8_S AdptPlatFileClose(FILEType fileHUsr);

/*
*  ����������  �ļ��ͷž�� 
*  ����˵��:FILEType *pfile                ������ļ�
*  ����ֵ:    1�ɹ�   0 ʧ��
*/
UINT8_S AdptPlatFileRelease(FILEType fileHUsr);

/*
*  �����������ļ�ɾ������
*  ����˵��:const CHAR* fileName  �ļ�����
*  ����ֵ:    1ɾ���ɹ�   0 ɾ��ʧ��
*/
UINT8_S AdptPlatFileDelete(const CHAR_S* fileName, FILEType* fileHUsr);



/*
*  ������������ѯ�ļ����״̬
*  ����˵��:   fileName  �ļ�����
*              outProgress �������
*  ����ֵ:   ��ѯ����״̬
*/
UINT8_S AdptPlatFileStatusInquire(const FILEType inHUsr, AdptProgressStruct* outProgress);

/*
*  ������������ѯ��һ�����ļ�״̬�ʹ�С 
*  ����˵��:   inHUsr  �ļ���� 
*              outStatus �ļ�״̬ 
*              size �ļ���С
*  ����ֵ:   0 ��ѯʧ��  1 ��ѯ�ɹ�
*/
UINT8_S AdptPlatFileExcStatusInquire(const FILEType inHUsr, UINT8_S* outStatus, UINT32_S* size);

#ifdef __cplusplus
}
#endif

#endif

