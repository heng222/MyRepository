/************************************************************************
*
* �ļ���   ��  SysStatusData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ZCϵͳ״̬����
* ��  ע   ��  ��
*
************************************************************************/
#include "SysStatusData.h"

LocalZcInfoStruct gLocalZcInfoStru;                  /*����ZC״̬��Ϣ�ṹ*/

/*
* ���������� ����ZC״̬�������ݽṹ
* ����˵���� void    
* ����ֵ  �� NULL: ��ȡ����ʧ��
*			!NULL: ����ZC״̬�������ݽṹ
*/
LocalZcInfoStruct* LocalZcInfoData(void)
{
	return &gLocalZcInfoStru;
}

/*
* ���������� ��ȡZC�������ں�
* ����˵���� ��    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: localZC�����ں�
*/
UINT32_S GetZcCycle(void)
{
	return gLocalZcInfoStru.ZcCycle;
}

/*
* ���������� ����ZC���ں�
* ����˵���� UINT32 zcCycle,���ں�    
* ����ֵ  �� ��
*/
void SetZcCycle(UINT32_S zcCycle)
{
	if (zcCycle < 0xffffffffU)
	{
		gLocalZcInfoStru.ZcCycle = zcCycle;
	} 
	else
	{
		gLocalZcInfoStru.ZcCycle = 0U;
	}
}

/*
* ���������� �ۼ�ZC���ں�
* ����˵���� ��   
* ����ֵ  �� ��
*/
void AddZcCycle(void)
{
	if (gLocalZcInfoStru.ZcCycle < 0xffffffffU)
	{
		gLocalZcInfoStru.ZcCycle++;
	} 
	else
	{
		gLocalZcInfoStru.ZcCycle = 0U;
	}
}

/*
* ���������� ��ʼ��ZC��ϵͳ״̬��Ϣ
* ����˵���� ��   
* ����ֵ  �� ��
*/
void InitZcSysStatusData(void)
{
	gLocalZcInfoStru.ZcCycle = 0U;
}
