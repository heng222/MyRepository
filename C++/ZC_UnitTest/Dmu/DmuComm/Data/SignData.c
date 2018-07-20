/*************************************************
  �ļ���   ��SignData.c
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� SignData���ݹ���
			DmuCommonData�����SignData���ܿɷֽ����£�
			1��	��SignDataStru�ṹ��ָ�����ռ�
			2��	��ȡSignData����
			3��	��ȡSignData��Ϣ
			4��	��ȡָ��IDSignDataStru�Ľṹ���±�
			5��	��ȡָ��IDSignDataStru�Ľṹ��ָ��
			6��	 ��ȡָ��IDSignDataStru���źŻ�����
			7��	��ȡָ��IDSignDataStru������
			8��	 ��ȡָ��IDSignDataStru������
			9��	��ȡָ��IDSignDataStru������seg���
			10��	 ��ȡָ��IDSignDataStru������Segƫ������cm��
			11��	��ȡָ��IDSignDataStru�ķ�������
			12��	��ȡָ��IDSignDataStru�ĵ�����Ϣ
			13��	��ȡ��·�źŻ����ID
			14��	�����������ǲ�ѯ��ǰSEG��ָ������������źŻ���Ϣ
			15��	��ȡ��·�źŻ�����ZC
			16��	��ȡ��·�źŻ�����CI
  ��ע    ���ޡ�
 
*************************************************/

#include "SignData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/MemSet.h"

static BnfSignStruct* SignDataStru = NULL;   /*����SignData���ݽṹ��*/
static UINT16_S LineNumSign = 0u;/*������*/


/*
* ���������� ��SignDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocSignDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == SignDataStru))
    {
        SignDataStru = (BnfSignStruct*)MemoryMalloc((UINT32_S)sizeof(BnfSignStruct) * lineNum);
        if (SignDataStru != NULL)
        {
            LineNumSign = lineNum;
            /*��ֵΪ��Чֵ*/
            MemorySet(SignDataStru,lineNum*sizeof(BnfSignStruct),UINT8_NULL,lineNum*sizeof(BnfSignStruct));
        }
    }
}

/*
* ���������� ��ȡSignData����
* ����˵����
* ����ֵ  �� 
BnfSignStruct*
*/
BnfSignStruct *GetSignData(void)
{
    return SignDataStru;
}


/*
* ���������� ��ȡSignData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
BnfSignStruct*
*/
BnfSignStruct *GetSignDataInfo(UINT16_S* lineNum)
{

    BnfSignStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumSign;
        retVal = SignDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDSignDataStru�Ľṹ���±�
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetSignDataStruIndex(const UINT16_S signId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumSign; i++)
    {
        if (signId == SignDataStru[i].signId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSignDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfSignStruct* GetIndexIdSignDataStru(const UINT16_S signId)
{
    BnfSignStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSignDataStruIndex(signId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSign)
    {
        retVal = &SignDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSignDataStru���źŻ�����
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: �źŻ�����
*/ 
UINT8_S* GetSignDataStrusignName(const UINT16_S signId)
{
    UINT8_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSignDataStruIndex(signId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].signName;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSignDataStru������
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����
*/ 
UINT16_S GetSignDataStrusignType(const UINT16_S signId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSignDataStruIndex(signId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].signType;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSignDataStru������
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����
*/ 
UINT16_S GetSignDataStrusignProperty(const UINT16_S signId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSignDataStruIndex(signId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].signProperty;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSignDataStru������seg���
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����seg���
*/ 
UINT16_S GetSignDataStrusignSegId(const UINT16_S signId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSignDataStruIndex(signId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].signSegId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSignDataStru�ķ���seg���
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����seg���
*/ 
UINT16_S GetSignDataStrusignProtectSegId(const UINT16_S signId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSignDataStruIndex(signId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].signProtectSegId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSignDataStru�ķ���segƫ����
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����seg���
*/ 
UINT32_S GetSignDataStrusignProtectSegOffset(const UINT16_S signId)
{
	UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSignDataStruIndex(signId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSign)
    {
    	retVal = SignDataStru[bufIndex].signProtectSegOffset;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSignDataStru������Segƫ������cm��
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����Segƫ������cm��
*/ 
UINT32_S GetSignDataStrusignSegOffset(const UINT16_S signId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSignDataStruIndex(signId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].signSegOffset;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSignDataStru��������������seg���
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����seg���
*/ 
UINT16_S GetSignDataStrusignProSegId(const UINT16_S signId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSignDataStruIndex(signId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].signProtectSegId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSignDataStru��������������Segƫ������cm��
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����Segƫ������cm��
*/ 
UINT32_S GetSignDataStrusignProSegOffset(const UINT16_S signId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSignDataStruIndex(signId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].signProtectSegOffset;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSignDataStru�ķ�������
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��������
*/ 
UINT8_S GetSignDataStruprotectiveDir(const UINT16_S signId)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSignDataStruIndex(signId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].protectiveDir;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSignDataStru�ĵ�����Ϣ
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ������Ϣ
*/ 
UINT32_S GetSignDataStrulightInfo(const UINT16_S signId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSignDataStruIndex(signId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].lightInfo;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* ���������� ��ȡ��·�źŻ����ID
* ����˵���� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:�źŻ����ID
*/
UINT16_S GetLineSignalMaxId(void)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S signId = 0u;/*�ź�ID*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumSign; i++)
    {
        if (signId < SignDataStru[i].signId)
        {
            signId = SignDataStru[i].signId;
        }
    }

    if(signId != 0u)
    {
        retVal = signId;
    }

    return retVal;
}

/*
* �������ܣ������������ǲ�ѯ��ǰSEG��ָ������������źŻ���Ϣ��
* ��ڲ�����UINT16 segId                seg���
*            UINT8_S  dir                    ���з���
* ���ڲ�����UINT16 findSignalIDBuff[]        �ҵ����źŻ�ID
*            UINT8_S* fingNum              ���ҵ��źŻ��ĸ���
* ����ֵ��  UINT8_S retVal 
*            ��ѯ�ɹ�:��ǰSEG�����źŻ�������0;
*            ��ѯ�ɹ�:��ǰSEG�ϴ����źŻ�������1      
*******************************************************************************************/
UINT8_S FindCurrentSegSignal(UINT16_S segId, UINT8_S dir, UINT16_S findSignalIDBuff[],UINT8_S* fingNum)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S i = 0u;/*ѭ���ñ���*/

    if((NULL != findSignalIDBuff) && (NULL != fingNum))
    {
        /*��ʼ���������*/
        *fingNum = (UINT8_S)DEFAULT_ZERO;

        /*�����źŻ���Ϣ���ҵ��ڵ�ǰseg�ϵ��źŻ�*/
        for (i=0u; i<LineNumSign; i++)
        {
            /*2010.9.6: �źŻ�λ�ø����߼�λ��*/
            if (segId == SignDataStru[i].signProtectSegId) 
            {
                /*�ж��ҵ����źŻ��ķ����Ƿ�������ķ�����ͬ*/
                /*˵����DMS�����У�0��ʾ�źŻ��ķ�������������seg���߼�������ͬ��
                1��ʾ�źŻ��ķ�������������seg���߼������෴*/
                if (((LINESEG_SAME_DIR == SignDataStru[i].protectiveDir) && (LINESEG_SAME_DIR == dir))
                    || ((LINESEG_CONVER_DIR == SignDataStru[i].protectiveDir) && (LINESEG_CONVER_DIR == dir)))
                {
                    /*�ҵ�������źŻ��������ѯ�������ѯ�ɹ�*/
                    findSignalIDBuff[*fingNum] = SignDataStru[i].signId;
                    *fingNum = *fingNum + 1u;
                }
            }
        }

        if ((*fingNum) > 0u)
        {
            retVal = 1u;
        } 

    }


    return retVal;
}

/*
* ���������� ��ȡ��·�źŻ�����ZC
* ����˵���� const UINT16_S signalId,�źŻ�ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����ZCId
*/
UINT16_S GetLineSignalBelongZcId(const UINT16_S signalId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSignDataStruIndex(signalId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].manageZCId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* ���������� ��ȡ��·�źŻ�����CI
* ����˵���� const UINT16_S signalId,�źŻ�ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����CIId
*/
UINT16_S GetLineSignalBelongCiId(const UINT16_S signalId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSignDataStruIndex(signalId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].manageCIId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}
