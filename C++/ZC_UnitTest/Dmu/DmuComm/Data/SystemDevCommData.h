/*************************************************
  �ļ���   ��SystemDevCommData.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� SystemDevCommData���ݹ���
			DmuCommonData�����SystemDevCommData���ܿɷֽ����£�
			1��	��SystemDevCommDataStru�ṹ��ָ�����ռ�
			2��	��ȡSystemDevCommData����
			3��	��ȡSystemDevCommData��Ϣ
			4��	��ȡָ��IDSystemDevCommDataStru�Ľṹ���±�
			5��	��ȡָ��IDSystemDevCommDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDSystemDevCommDataStru��ͨ�Ŷ�������
			7��	��ȡָ��IDSystemDevCommDataStru��ͨ�Ŷ�����(Device_Type+Device_ID)
			8��	��ȡָ��IDSystemDevCommDataStru��ͨ�Ŷ�����Ϣ

  ��ע    ���ޡ� 
*************************************************/
#ifndef SYSTEMDEVCOMM_DATA_H_
#define SYSTEMDEVCOMM_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  SYSTEMDEVCOMM_COMMOBJECT_MAX_NUM          15                                            /*ͨ�Ŷ���������*/
#define  SYSTEMDEVCOMM_LINE_BYTE_NUM              34                                            /*һ�������ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*�豸ͨ�Ź�ϵ�����ݽṹ��*/
typedef struct BnfSystemDevCommStruct
{
    UINT16_S  devName;                                                    /*���豸���(Device_Type+Device_ID)*/    
    UINT16_S  commObjectNum;                                                /*ͨ�Ŷ�������*/
    UINT16_S  commObjectIdBuff[SYSTEMDEVCOMM_COMMOBJECT_MAX_NUM];            /*ͨ�Ŷ�����(Device_Type+Device_ID)*/
}BnfSystemDevCommStruct;

/*
* ���������� ��SystemDevCommDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocSystemDevCommDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡSystemDevCommData����
* ����˵����
* ����ֵ  �� 
            BnfSystemDevCommStruct*
*/
BnfSystemDevCommStruct *GetSystemDevCommData(void);

/*
* ���������� ��ȡSystemDevCommData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfSystemDevCommStruct*
*/
BnfSystemDevCommStruct *GetSystemDevCommDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDSystemDevCommDataStru�Ľṹ���±�
* ����˵���� const UINT16_S devName;���豸���(Device_Type+Device_ID)
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetSystemDevCommDataStruIndex(const UINT16_S devName);

/*
** ���������� ��ȡָ��IDSystemDevCommDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S devName;���豸���(Device_Type+Device_ID)
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfSystemDevCommStruct* GetIndexIdSystemDevCommDataStru(const UINT16_S devName);

/*
** ���������� ��ȡָ��IDSystemDevCommDataStru��ͨ�Ŷ�������
* ����˵���� const UINT16_S devName;���豸���(Device_Type+Device_ID)
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ͨ�Ŷ�������
*/ 
UINT16_S GetSystemDevCommDataStrucommObjectNum(const UINT16_S devName);

/*
** ���������� ��ȡָ��IDSystemDevCommDataStru��ͨ�Ŷ�����(Device_Type+Device_ID)
* ����˵���� const UINT16_S devName;���豸���(Device_Type+Device_ID)
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ͨ�Ŷ�����(Device_Type+Device_ID)
*/ 
UINT16_S* GetSysDevComDataComObjIdBuf(const UINT16_S devName);

/*
** ���������� ��ȡָ��IDSystemDevCommDataStru��ͨ�Ŷ�����Ϣ
* ����˵���� const UINT16_S devName;���豸���(Device_Type+Device_ID)
* �������:     UINT16_S* pCommObjectId   ͨ�Ŷ�����
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ͨ�Ŷ�����(Device_Type+Device_ID)
*/ 
UINT16_S GetSysDevComDataComObjInfo(const UINT16_S devName,UINT16_S* pCommObjectId);

#ifdef __cplusplus
}
#endif

#endif
