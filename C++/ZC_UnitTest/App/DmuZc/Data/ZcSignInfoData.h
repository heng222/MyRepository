/*******************************************
* �ļ���	��  ZcSignInfoData.h
* ��  ��	��  ZC��
* ����ʱ��	��  2015-5-25
* ��������	��	����ZcSignInfoData���ݹ���
* ��  ע	��  ��
*******************************************/
#ifndef ZCSIGNINFO_DATA_H_
#define ZCSIGNINFO_DATA_H_

#include "../../../Common/CommonTypes.h"

#define ZCSIGNINFO_LINE_BYTE_NUM                 6U                           	/*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*ZC�źŻ������ݽṹ��*/
typedef struct BnfZcSignInfoStruct
{
	UINT16_S  signId;						/*�źŻ�ID*/
	UINT16_S  throughSignFlag;            /*���źű�־*/
	UINT16_S  lightFlag;                  /*�����־*/
}BnfZcSignInfoStruct;

/*******************************************
* ������	��  MallocZcSignInfoDataStru
* ��������	��	���� ZcSignInfoDataStru
* ���룺  ��
* �����  ��
* ����ֵ  :  NULL: ��ȡ����ʧ��
*			!NULL: �ɹ�
*******************************************/
void MallocZcSignInfoDataStru(UINT16_S lineNum);


/*******************************************
* ������	��  GetZcSignInfoData
* ��������	��	��ȡZcSignInfoData����
* ���룺  ��
* �����  ��
* ����ֵ  :  NULL: ��ȡ����ʧ��
*			!NULL: �ɹ�
*******************************************/
BnfZcSignInfoStruct *GetZcSignInfoData(void);

/*******************************************
* ������	��
* ���������� ��ȡZcSignInfoData��Ϣ
* ����˵�����������:UINT16* lineNum  ��������
* ����ֵ  �� 
			BnfZcSignInfoStruct*
*/
BnfZcSignInfoStruct *GetZcSignInfoDataInfo(UINT16_S* lineNum);
/*******************************************
* ������	��
** ���������� ��ȡָ��IDZcSignInfoDataStru�Ľṹ���±�
* ����˵���� const UINT16 signId;�źŻ�ID
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*			<0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetZcSignInfoDataStruIndex(const UINT16_S signId);

/*******************************************
* ������	��
** ���������� ��ȡָ��IDZcSignInfoDataStru�Ľṹ��ָ��
* ����˵���� const UINT16 signId;�źŻ�ID
* ����ֵ  :  NULL: ��ȡ����ʧ��
*			!NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfZcSignInfoStruct* GetIndexIdZcSignInfoDataStru(const UINT16_S signId);

/*******************************************
* ������	��
** ���������� ��ȡָ��IDZcSignInfoDataStru�Ĵ��źű�־
* ����˵���� const UINT16 signId;�źŻ�ID
* ����ֵ  :  0: ��ȡ����ʧ��
*			>0: ���źű�־
*/ 
UINT16_S GetZcSignInfoDataStruthroughSignFlag(const UINT16_S signId);

/*******************************************
* ������	��
** ���������� ��ȡָ��IDZcSignInfoDataStru�������־
* ����˵���� const UINT16 signId;�źŻ�ID
* ����ֵ  :  0: ��ȡ����ʧ��
*			>0: �����־
*/ 
UINT16_S GetZcSignInfoDataStrulightFlag(const UINT16_S signId);


#ifdef __cplusplus
}
#endif

#endif
