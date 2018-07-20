/*******************************************
* �ļ���	��  ZcSignInfoData.c
* ��  ��	��  ZC��
* ����ʱ��	��  2015-5-25
* ��������	��	����ZcSignInfoData���ݹ���
* ��  ע	��  ��
*******************************************/

#include "ZcSignInfoData.h"
#include "../../../Dmu/Read/ReadDataTypeDefine.h"
#include "../../../Common/Malloc.h"

static BnfZcSignInfoStruct* gZcSignInfoDataStru = NULL;   /*����ZcSignInfoData���ݽṹ��*/
static UINT16_S gLineNumZcSignInfo = 0U;/*������*/



/*******************************************
* ������	��  MallocZcSignInfoDataStru
* ��������	��	���� ZcSignInfoDataStru
* ���룺  ��
* �����  ��
* ����ֵ  :  NULL: ��ȡ����ʧ��
*			!NULL: �ɹ�
*******************************************/
void MallocZcSignInfoDataStru(UINT16_S lineNum)
{
	if ((lineNum > 0U)&&(NULL == gZcSignInfoDataStru))
	{
		gZcSignInfoDataStru = (BnfZcSignInfoStruct*)MemoryMalloc(((UINT32_S)(lineNum*sizeof(BnfZcSignInfoStruct))));
		gLineNumZcSignInfo = lineNum;
	}
}

/*******************************************
* ������	��  GetZcSignInfoData
* ��������	��	��ȡZcSignInfoData����
* ���룺  ��
* �����  ��
* ����ֵ  :  NULL: ��ȡ����ʧ��
*			!NULL: �ɹ�
*******************************************/
BnfZcSignInfoStruct *GetZcSignInfoData(void)
{
	return gZcSignInfoDataStru;
}


/*******************************************
* ������	��   
* ���������� ��ȡZcSignInfoData��Ϣ
* ����˵�����������:UINT16* lineNum  ��������
* ����ֵ  �� 
			BnfZcSignInfoStruct*
*/
BnfZcSignInfoStruct *GetZcSignInfoDataInfo(UINT16_S* lineNum)
{
    if (NULL != lineNum)
    {
        (*lineNum) = gLineNumZcSignInfo;
    }
	
	return gZcSignInfoDataStru;
}
/*******************************************
* ������	��
** ���������� ��ȡָ��IDZcSignInfoDataStru�Ľṹ���±�
* ����˵���� const UINT16 signId;�źŻ�ID
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*			<0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetZcSignInfoDataStruIndex(const UINT16_S signId)
{
	UINT16_S retVal = 0xFFFFU;/*��������ֵ*/

	UINT16_S i = 0U;/*ѭ��ʹ��*/

	for ( i = 0U; i < gLineNumZcSignInfo; i++)
	{
		if (signId == gZcSignInfoDataStru[i].signId)
		{
			retVal = i;
			break;
		}
	}
	return retVal;
}

/*******************************************
* ������	��
** ���������� ��ȡָ��IDZcSignInfoDataStru�Ľṹ��ָ��
* ����˵���� const UINT16 signId;�źŻ�ID
* ����ֵ  :  NULL: ��ȡ����ʧ��
*			!NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfZcSignInfoStruct* GetIndexIdZcSignInfoDataStru(const UINT16_S signId)
{
	BnfZcSignInfoStruct* retVal = NULL;/*��������ֵ*/
	UINT16_S bufIndex = 0U;  /*�����±�*/
	bufIndex = GetZcSignInfoDataStruIndex(signId);/*��ȡ�ṹ�������±�*/
	if (bufIndex < gLineNumZcSignInfo)
	{
		retVal = &gZcSignInfoDataStru[bufIndex];
	}
	else
	{
        /*Do nothing currently !*/
	}
	return retVal;
}

/*******************************************
* ������	��
** ���������� ��ȡָ��IDZcSignInfoDataStru�Ĵ��źű�־
* ����˵���� const UINT16 signId;�źŻ�ID
* ����ֵ  :  0: ��ȡ����ʧ��
*			>0: ���źű�־
*/ 
UINT16_S GetZcSignInfoDataStruthroughSignFlag(const UINT16_S signId)
{
	UINT16_S retVal = 0U;/*��������ֵ*/
	UINT16_S bufIndex = 0U;  /*�����±�*/
	bufIndex = GetZcSignInfoDataStruIndex(signId);/*��ȡ�ṹ�������±�*/
	if (bufIndex < gLineNumZcSignInfo)
	{
		retVal = gZcSignInfoDataStru[bufIndex].throughSignFlag;
	}
	else
	{
        /*Do nothing currently !*/
	}
	return retVal;
}

/*******************************************
* ������	��
** ���������� ��ȡָ��IDZcSignInfoDataStru�������־
* ����˵���� const UINT16 signId;�źŻ�ID
* ����ֵ  :  0: ��ȡ����ʧ��
*			>0: �����־
*/ 
UINT16_S GetZcSignInfoDataStrulightFlag(const UINT16_S signId)
{
	UINT16_S retVal = 0U;/*��������ֵ*/
	UINT16_S bufIndex = 0U;  /*�����±�*/
	bufIndex = GetZcSignInfoDataStruIndex(signId);/*��ȡ�ṹ�������±�*/

	if (bufIndex < gLineNumZcSignInfo)
	{
		retVal = gZcSignInfoDataStru[bufIndex].lightFlag;
	}
	else
	{
        /*Do nothing currently !*/
	}
	return retVal;
}

