/*************************************************
  �ļ���   ��ArData.c
  ����     ������      
  ����ʱ�� ��2016-8-10
  �������� �� ����ArData���ݹ���
				 DmuCommonData���ArData.c ���ܿɷֽ����£�
				1��	��ArDataStru�ṹ��ָ�����ռ�
				2��	 ��ȡArData����
				3��	��ȡArData��Ϣ
				4��	��ȡָ��IDArDataStru�Ľṹ���±�
				5��	��ȡָ��IDArDataStru�Ľṹ��ָ��
				6��	��ȡָ��IDArDataStru�������۷�����վ̨���
				7��	��ȡָ��IDArDataStru�Ľ�����Ӧͣ������
				8��	��ȡָ��IDArDataStru�Ļ��˵��Ӧͣ������
				9��	��ȡָ��IDArDataStru���˳�վ̨���
				10��	��ȡָ��IDArDataStru���˳����Ӧͣ������
				11��	��ȡָ��IDArDataStru�������۷���ID
				12��	��ȡָ��IDArDataStru�������۷���ťID
				13��	��ȡ��·�����۷���ť���ID
				14��	��ȡ��·�����۷���ťID��Ӧ�Ľ�����Ӧͣ������
				15��	 ��ȡ��·�����۷������ID
				16��	��ȡ��·�����۷���ID��Ӧ�Ľ�����Ӧͣ������
				17��	��ȡ��·�����۷���ť����ZCid
				18��	��ȡ��·�����۷���ť����CIid
				19��	��ȡ��·�����۷�������ZCID
				20��	��ȡ��·�����۷�������CIid
				21��	�жϴ�ͣ�����Ƿ��������۷����д���
				22��	�жϴ�ͣ�����Ƿ��������۷����е��˳�����

  ��ע    ���ޡ�
 
*************************************************/

#include "ArData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/MemSet.h"

static BnfArStruct* ArDataStru = NULL;   /*����ArData���ݽṹ��*/
static UINT16_S LineNumAr = 0u;/*������*/


/*
* �������ƣ�MallocArDataStru
* ���������� ��ArDataStru�ṹ��ָ�����ռ�
* ��������� UINT16_S lineNum �����������
* ��������� ��
* ����ֵ  �� void
*/
void MallocArDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == ArDataStru))
    {
        ArDataStru = (BnfArStruct*)MemoryMalloc((UINT32_S)sizeof(BnfArStruct) * lineNum);
        if (ArDataStru != NULL)
        {
            LineNumAr = lineNum;
            /*��ֵΪ��Чֵ*/
            MemorySet(ArDataStru,lineNum*sizeof(BnfArStruct),UINT8_NULL,lineNum*sizeof(BnfArStruct));
        }
    }
}

/*
* �������ƣ�GetArData
* ���������� ��ȡArData����
* ��������� ��
* ��������� ��
* ����ֵ  �� 
BnfArStruct*
*/
BnfArStruct *GetArData(void)
{
    return ArDataStru;
}


/*
* �������ƣ�GetArDataInfo
* ���������� ��ȡArData��Ϣ
* �����������
* �������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
BnfArStruct* 
*/
BnfArStruct *GetArDataInfo(UINT16_S* lineNum)
{
    BnfArStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumAr;
        retVal =  ArDataStru;

    }
    return retVal;
}
/*
* �������ƣ�GetArDataStruIndex
* ���������� ��ȡָ��IDArDataStru�Ľṹ���±�
* ��������� const UINT16_S arId;���
* ��������� ��
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetArDataStruIndex(const UINT16_S arId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumAr; i++)
    {
        if (arId == ArDataStru[i].arId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
* �������ƣ�GetIndexIdArDataStru
* ���������� ��ȡָ��IDArDataStru�Ľṹ��ָ��
* ���˲����� const UINT16_S arId;���
* ��������� ��
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfArStruct* GetIndexIdArDataStru(const UINT16_S arId)
{
    BnfArStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetArDataStruIndex(arId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumAr)
    {
        retVal = &ArDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* �������ƣ�GetArDataStrustartPlartformId
* ���������� ��ȡָ��IDArDataStru�������۷�����վ̨���
* ��������� const UINT16_S arId;���
* ��������� ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����۷�����վ̨���
*/ 
UINT16_S GetArDataStrustartPlartformId(const UINT16_S arId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetArDataStruIndex(arId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumAr)
    {
        retVal = ArDataStru[bufIndex].startPlartformId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* �������ƣ�GetArDataStruarInStopPointId
* ���������� ��ȡָ��IDArDataStru�Ľ�����Ӧͣ������
* ��������� const UINT16_S arId;���
* �����������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ������Ӧͣ������
*/ 
UINT16_S GetArDataStruarInStopPointId(const UINT16_S arId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetArDataStruIndex(arId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumAr)
    {
        retVal = ArDataStru[bufIndex].arInStopPointId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* �������ƣ�GetArDataStrurevertPointId
* ���������� ��ȡָ��IDArDataStru�Ļ��˵��Ӧͣ������
* ��������� const UINT16_S arId;���
* ��������� ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ���˵��Ӧͣ������
*/ 
UINT16_S GetArDataStrurevertPointId(const UINT16_S arId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetArDataStruIndex(arId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumAr)
    {
        retVal = ArDataStru[bufIndex].revertPointId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* �������ƣ�GetArDataStruendPlartformId
* ���������� ��ȡָ��IDArDataStru���˳�վ̨���
* ��������� const UINT16_S arId;���
* ��������� ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �˳�վ̨���
*/ 
UINT16_S GetArDataStruendPlartformId(const UINT16_S arId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetArDataStruIndex(arId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumAr)
    {
        retVal = ArDataStru[bufIndex].endPlartformId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* �������ƣ�GetArDataStruaROutStopPointId
* ���������� ��ȡָ��IDArDataStru���˳����Ӧͣ������
* ��������� const UINT16_S arId;���
* ��������� ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �˳����Ӧͣ������
*/ 
UINT16_S GetArDataStruaROutStopPointId(const UINT16_S arId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetArDataStruIndex(arId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumAr)
    {
        retVal = ArDataStru[bufIndex].aROutStopPointId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* �������ƣ�GetArDataStruaRLampID
* ���������� ��ȡָ��IDArDataStru�������۷���ID
* ��������� const UINT16_S arId;���
* ��������� ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����۷���ID
*/ 
UINT16_S GetArDataStruaRLampID(const UINT16_S arId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetArDataStruIndex(arId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumAr)
    {
        retVal = ArDataStru[bufIndex].aRLampID;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* �������ƣ�GetArDataStruaRButtonId
* ���������� ��ȡָ��IDArDataStru�������۷���ťID
* ��������� const UINT16_S arId;���
* ��������� ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����۷���ťID
*/ 
UINT16_S GetArDataStruaRButtonId(const UINT16_S arId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetArDataStruIndex(arId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumAr)
    {
        retVal = ArDataStru[bufIndex].aRButtonId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* �������ƣ�GetLineDrButtonMaxId
* ���������� ��ȡ��·�����۷���ť���ID
* ��������� ��
* ��������� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:�����۷���ť���ID
*/
UINT16_S GetLineDrButtonMaxId(void)
{
    UINT16_S retVal = 0u;
    UINT16_S aRButtonId = 0u;/*�����۷���ťID*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumAr; i++)
    {
        if (aRButtonId < ArDataStru[i].aRButtonId)
        {
            aRButtonId = ArDataStru[i].aRButtonId;
        }
    }

    if(aRButtonId != 0u)
    {
        retVal = aRButtonId;
    }

    return retVal;
}

/*
* �������ƣ�GetLineDrButtonBelongPointId
* ���������� ��ȡ��·�����۷���ťID��Ӧ�Ľ�����Ӧͣ������
* ��������� const UINT16_S arButtonId   �����۷���ťID
* ��������� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:������Ӧͣ������
*/
UINT16_S GetLineDrButtonBelongPointId(const UINT16_S arButtonId)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumAr; i++)
    {
        if (arButtonId == ArDataStru[i].aRButtonId)
        {
            retVal = ArDataStru[i].arInStopPointId;
            break;
        }
    }

    return retVal;
}

/*
* �������ƣ�GetLineDrLampMaxId
* ���������� ��ȡ��·�����۷������ID
* ��������� ��
* ��������� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:�����۷������ID
*/
UINT16_S GetLineDrLampMaxId(void)
{
    UINT16_S retVal = 0u;
    UINT16_S aRLampID = 0u;/*�����۷���ID*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumAr; i++)
    {
        if (aRLampID < ArDataStru[i].aRLampID)
        {
            aRLampID = ArDataStru[i].aRButtonId;
        }
    }

    if(aRLampID != 0u)
    {
        retVal = aRLampID;
    }

    return retVal;
}

/*
* �������ƣ�GetLineDrLampBelongPointId
* ���������� ��ȡ��·�����۷���ID��Ӧ�Ľ�����Ӧͣ������
* ��������� const UINT16_S arLampID   �����۷���ID
* ��������� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:������Ӧͣ������
*/
UINT16_S GetLineDrLampBelongPointId(const UINT16_S arLampID)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumAr; i++)
    {
        if (arLampID == ArDataStru[i].aRLampID)
        {
            retVal = ArDataStru[i].arInStopPointId;
            break;
        }
    }

    return retVal;
}

/*
* �������ƣ�GetLineDrButtonBelongZcId
* ���������� ��ȡ��·�����۷���ť����ZCid
* ��������� const UINT16_S drButtonId,�����۷���ť
* ��������� ��
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����ZCid
*/
UINT16_S GetLineDrButtonBelongZcId(const UINT16_S drButtonId)
{
    UINT16_S retVal = 0u;
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumAr; i++)
    {
        if (drButtonId == ArDataStru[i].aRButtonId)
        {
            retVal = ArDataStru[i].manageZCId;
            break;
        }
    }

    return retVal;
}

/*
* �������ƣ�GetLineDrButtonBelongCiId
* ���������� ��ȡ��·�����۷���ť����CIid
* ��������� const UINT16_S drButtonId,�����۷���ť
* �����������
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����CIid
*/
UINT16_S GetLineDrButtonBelongCiId(const UINT16_S drButtonId)
{    
    UINT16_S retVal = 0u;
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumAr; i++)
    {
        if (drButtonId == ArDataStru[i].aRButtonId)
        {
            retVal = ArDataStru[i].manageCIId;
            break;
        }
    }

    return retVal;
}

/*
* �������ƣ�GetLineDrLampBelongZcId
* ���������� ��ȡ��·�����۷�������ZCID
* ��������� const UINT16_S drLampId,�����۷���ID
* ��������� ��
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����ZCID
*/
UINT16_S GetLineDrLampBelongZcId(const UINT16_S drLampId)
{    
    UINT16_S retVal = 0u;
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumAr; i++)
    {
        if (drLampId == ArDataStru[i].aRLampID)
        {
            retVal = ArDataStru[i].manageZCId;
            break;
        }
    }

    return retVal;
}

/*
* �������ƣ�GetLineDrLampBelongCiId
* ���������� ��ȡ��·�����۷�������CIid
* ��������� const UINT16_S drLampId,�����۷���ID
* ��������� ��
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����CIid
*/
UINT16_S GetLineDrLampBelongCiId(const UINT16_S drLampId)
{    
    UINT16_S retVal = 0u;
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumAr; i++)
    {
        if (drLampId == ArDataStru[i].aRLampID)
        {
            retVal = ArDataStru[i].manageCIId;
            break;
        }
    }

    return retVal;
}

/*
* �������ƣ�CheckSopPointIsAr
* ���������� �жϴ�ͣ�����Ƿ��������۷����д���
* ��������� const UINT16_S arId;���
* �����������
* ����ֵ  :  0:������
*             1:����
*/ 
UINT8_S CheckSopPointIsAr(const UINT16_S stopPointId)
{
    UINT8_S retVal = 0u;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumAr; i++)
    {
        if (stopPointId == ArDataStru[i].revertPointId)
        {
            retVal = 1u;
            break;
        }
    }
    return retVal;
}

/*
* �������ƣ�CheckSopPointIsExitAr
* ���������� �жϴ�ͣ�����Ƿ��������۷����е��˳�����
* ��������� const UINT16_S arId;���
* ��������� ��
* ����ֵ  :  0:������
*             1:����
*/ 
UINT8_S CheckSopPointIsExitAr(const UINT16_S stopPointId)
{
    UINT8_S retVal = 0u;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumAr; i++)
    {
        if(stopPointId == ArDataStru[i].aROutStopPointId)
        {
            retVal = 1u;
            break;
        }
    }
    return retVal;
}

