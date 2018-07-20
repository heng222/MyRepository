/*************************************************
  �ļ���   ��SystemDevCommData.c
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

#include "SystemDevCommData.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/Copy.h"

static BnfSystemDevCommStruct* SystemDevCommDataStru = NULL;   /*����SystemDevCommData���ݽṹ��*/
static UINT16_S LineNumSystemDevComm = 0u;/*������*/


/*
* ���������� ��SystemDevCommDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocSystemDevCommDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == SystemDevCommDataStru))
    {
        SystemDevCommDataStru = (BnfSystemDevCommStruct*)MemoryMalloc((UINT32_S)sizeof(BnfSystemDevCommStruct) * lineNum);
        LineNumSystemDevComm = lineNum;
    }
}

/*
* ���������� ��ȡSystemDevCommData����
* ����˵����
* ����ֵ  �� 
BnfSystemDevCommStruct*
*/
BnfSystemDevCommStruct *GetSystemDevCommData(void)
{
    return SystemDevCommDataStru;
}


/*
* ���������� ��ȡSystemDevCommData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
BnfSystemDevCommStruct*
*/
BnfSystemDevCommStruct *GetSystemDevCommDataInfo(UINT16_S* lineNum)
{

    BnfSystemDevCommStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumSystemDevComm;
        retVal = SystemDevCommDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDSystemDevCommDataStru�Ľṹ���±�
* ����˵���� const UINT16_S devName;���豸���(Device_Type+Device_ID)
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetSystemDevCommDataStruIndex(const UINT16_S devName)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumSystemDevComm; i++)
    {
        if (devName == SystemDevCommDataStru[i].devName)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSystemDevCommDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S devName;���豸���(Device_Type+Device_ID)
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfSystemDevCommStruct* GetIndexIdSystemDevCommDataStru(const UINT16_S devName)
{
    BnfSystemDevCommStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSystemDevCommDataStruIndex(devName);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSystemDevComm)
    {
        retVal = &SystemDevCommDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSystemDevCommDataStru��ͨ�Ŷ�������
* ����˵���� const UINT16_S devName;���豸���(Device_Type+Device_ID)
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ͨ�Ŷ�������
*/ 
UINT16_S GetSystemDevCommDataStrucommObjectNum(const UINT16_S devName)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSystemDevCommDataStruIndex(devName);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSystemDevComm)
    {
        retVal = SystemDevCommDataStru[bufIndex].commObjectNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSystemDevCommDataStru��ͨ�Ŷ�����(Device_Type+Device_ID)
* ����˵���� const UINT16_S devName;���豸���(Device_Type+Device_ID)
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ͨ�Ŷ�����(Device_Type+Device_ID)
*/ 
UINT16_S* GetSysDevComDataComObjIdBuf(const UINT16_S devName)
{
    UINT16_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSystemDevCommDataStruIndex(devName);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSystemDevComm)
    {
        retVal = SystemDevCommDataStru[bufIndex].commObjectIdBuff;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSystemDevCommDataStru��ͨ�Ŷ�����Ϣ
* ����˵���� const UINT16_S devName;���豸���(Device_Type+Device_ID)
* �������:     UINT16_S* pCommObjectId   ͨ�Ŷ�����
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ͨ�Ŷ�����(Device_Type+Device_ID)
*/ 
UINT16_S GetSysDevComDataComObjInfo(const UINT16_S devName,UINT16_S* pCommObjectId)
{
    UINT16_S retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSystemDevCommDataStruIndex(devName);/*��ȡ�ṹ�������±�*/

    if ((pCommObjectId != NULL)&&(bufIndex < LineNumSystemDevComm))
    {
        MemoryCpy(pCommObjectId,sizeof(UINT16_S)*SYSTEMDEVCOMM_COMMOBJECT_MAX_NUM,SystemDevCommDataStru[bufIndex].commObjectIdBuff,sizeof(UINT16_S)*SYSTEMDEVCOMM_COMMOBJECT_MAX_NUM);
        retVal = SystemDevCommDataStru[bufIndex].commObjectNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}
