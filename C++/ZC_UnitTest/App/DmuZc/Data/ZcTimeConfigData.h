/*******************************************
 * �ļ���	��  ZcTimeConfigData.h
 * �汾��	��  1.0  
 * ����ʱ��	��  2015-5-25
 * ��������	��	ZcTimeConfigData���ݹ���ͷ�ļ�
 * ʹ��ע��	��  
 * �޸ļ�¼	��	
*******************************************/
#ifndef ZCTIMECONFIG_DATA_H_
#define ZCTIMECONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"

#define ZCTIMECONFIG_LINE_BYTE_NUM                 	 8U                         /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*Уʱ���ñ����ݽṹ��*/
typedef struct BnfZcTimeConfigStruct
{
	UINT32_S errorTime;			/*NTPУʱ���ʱ��(ms)*/
	UINT32_S duration;			/*��ϵͳ��ʱ�ӷ�����Уʱ��ʱ����ms��*/	
}BnfZcTimeConfigStruct;

/*
* ���������� ��ZcTimeConfigDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16 lineNum �����������
* ����ֵ  �� void
*/
void MallocZcTimeConfigDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡZcTimeConfigData����
* ����˵����
* ����ֵ  �� 
			BnfZcTimeConfigStruct*
*/
BnfZcTimeConfigStruct *GetZcTimeConfigData(void);


/*
* ���������� ��ȡZcTimeConfigData��Ϣ
* ����˵�����������:UINT16* lineNum  ��������
* ����ֵ  �� 
			BnfZcTimeConfigStruct*
*/
BnfZcTimeConfigStruct *GetZcTimeDataInfo(UINT16_S* lineNum);

/*
** ���������� ��ȡNTPУʱ���ʱ��(ms)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*			<UINT32_NULL: NTPУʱ���ʱ��(ms)
*/ 
UINT32_S GetZcTimeNtprrorTime(void);

/*
** ���������� ��ȡ��ϵͳ��ʱ�ӷ�����Уʱ��ʱ����ms��
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*			<UINT32_NULL: ��ϵͳ��ʱ�ӷ�����Уʱ��ʱ����ms��
*/ 
UINT32_S GetZcTimeSystemDuration(void);

#ifdef __cplusplus
}
#endif

#endif
