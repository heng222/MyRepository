/*************************************************
  �ļ���   ��RouteData.c
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� RouteData���ݹ���
			DmuCommonData�����RouteData���ܿɷֽ����£�
			1��	��RouteDataStru�ṹ��ָ�����ռ�
			2��	��ȡRouteData����
			3��	��ȡRouteData��Ϣ
			4��	��ȡָ��IDRouteDataStru�Ľṹ���±�
			5��	��ȡָ��IDRouteDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDRouteDataStru�Ľ�·����
			7��	��ȡָ��IDRouteDataStru�Ľ�·����
			8��	��ȡָ��IDRouteDataStru����ʼ�źŻ����
			9��	��ȡָ��IDRouteDataStru����ֹ�źŻ����
			10��	��ȡָ��IDRouteDataStru�İ�������������Ŀ
			11��	��ȡָ��IDRouteDataStru�ļ������α��
			12��	��ȡָ��IDRouteDataStru�ı���������Ŀ
			13��	��ȡָ��IDRouteDataStru�ı������α��
			14��	��ȡָ��IDRouteDataStru�ĵ�ʽ�ӽ�������Ŀ
			15��	��ȡָ��IDRouteDataStru�ĵ�ʽ�ӽ����α��
			16��	 ��ȡָ��IDRouteDataStru��CBTC�ӽ�������Ŀ
			17��	��ȡָ��IDRouteDataStru��CBTC�ӽ����α��
			18��	��ȡָ��IDRouteDataStru�ĵ�ʽ������������
			19��	��ȡָ��IDRouteDataStru�ĵ�ʽ��������ID
			20��	��ȡָ��IDRouteDataStru��CBTC������������
			21��	��ȡָ��IDRouteDataStru��CBTC��������ID
			22��	��ȡָ��IDRouteDataStru������CI������
			23��	��ȡ��·��·���ID
			24��	��ȡ��·��Ӧ����������Ϣ
			25��	��ȡ��·��Ӧ����������Ϣ
			26��	��ȡ��·��·����ZCID

  ��ע    ���ޡ�
 
*************************************************/

#include "RouteData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/MemSet.h"
#include "../../../Common/Copy.h"

static BnfRouteStruct* RouteDataStru = NULL;   /*����RouteData���ݽṹ��*/
static UINT16_S LineNumRoute = 0u;/*������*/


/*
* ���������� ��RouteDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocRouteDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == RouteDataStru))
    {
        RouteDataStru = (BnfRouteStruct*)MemoryMalloc((UINT32_S)sizeof(BnfRouteStruct) * lineNum);
        if (RouteDataStru != NULL)
        {
            LineNumRoute = lineNum;
            /*��ֵΪ��Чֵ*/
            MemorySet(RouteDataStru,lineNum*sizeof(BnfRouteStruct),UINT8_NULL,lineNum*sizeof(BnfRouteStruct));
        }
    }
}

/*
* ���������� ��ȡRouteData����
* ����˵����
* ����ֵ  �� 
BnfRouteStruct*
*/
BnfRouteStruct *GetRouteData(void)
{
    return RouteDataStru;
}


/*
* ���������� ��ȡRouteData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
BnfRouteStruct*
*/
BnfRouteStruct *GetRouteDataInfo(UINT16_S* lineNum)
{

    BnfRouteStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumRoute;
        retVal = RouteDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDRouteDataStru�Ľṹ���±�
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetRouteDataStruIndex(const UINT16_S routeId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumRoute; i++)
    {
        if (routeId == RouteDataStru[i].routeId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDRouteDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfRouteStruct* GetIndexIdRouteDataStru(const UINT16_S routeId)
{
    BnfRouteStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumRoute)
    {
        retVal = &RouteDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDRouteDataStru�Ľ�·����
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ��·����
*/ 
UINT8_S* GetRouteDataStrurouteName(const UINT16_S routeId)
{
    UINT8_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].routeName;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDRouteDataStru�Ľ�·����
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��·����
*/ 
UINT16_S GetRouteDataStrurouteType(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].routeType;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDRouteDataStru����ʼ�źŻ����
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��ʼ�źŻ����
*/ 
UINT16_S GetRouteDataStrustartSignalId(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].startSignalId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDRouteDataStru����ֹ�źŻ����
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��ֹ�źŻ����
*/ 
UINT16_S GetRouteDataStruendSignalId(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].endSignalId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDRouteDataStru�İ�������������Ŀ
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��������������Ŀ
*/ 
UINT16_S GetRouteDataStruincludeAxleSecNum(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].includeAxleSecNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDRouteDataStru�ļ������α��
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: �������α��
*/ 
UINT16_S* GetRouteDataStruAxleSec(const UINT16_S routeId)
{
    UINT16_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].AxleSec;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDRouteDataStru�ı���������Ŀ
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����������Ŀ
*/ 
UINT16_S GetRouteDataStruprotectSecNum(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].protectSecNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDRouteDataStru�ı������α��
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: �������α��
*/ 
UINT16_S* GetRouteDataStruprotectSecId(const UINT16_S routeId)
{
    UINT16_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].protectSecId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDRouteDataStru�ĵ�ʽ�ӽ�������Ŀ
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��ʽ�ӽ�������Ŀ
*/ 
UINT16_S GetRouteDataStrublogAccessSegNum(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].blogAccessSegNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDRouteDataStru�ĵ�ʽ�ӽ����α��
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ��ʽ�ӽ����α��
*/ 
UINT16_S* GetRouteDataStrublogAccessSegId(const UINT16_S routeId)
{
    UINT16_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].blogAccessSegId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDRouteDataStru��CBTC�ӽ�������Ŀ
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: CBTC�ӽ�������Ŀ
*/ 
UINT16_S GetRouteDataStrucbtcAccessSegNum(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].cbtcAccessSegNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDRouteDataStru��CBTC�ӽ����α��
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: CBTC�ӽ����α��
*/ 
UINT16_S* GetRouteDataStrucbtcAccessSegId(const UINT16_S routeId)
{
    UINT16_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].cbtcAccessSegId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDRouteDataStru�ĵ�ʽ������������
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��ʽ������������
*/ 
UINT16_S GetRouteDataStrublocTrgAreaNum(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].blocTrgAreaNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDRouteDataStru�ĵ�ʽ��������ID
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ��ʽ��������ID
*/ 
UINT16_S* GetRouteDataStrublocTrgAreaId(const UINT16_S routeId)
{
    UINT16_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].blocTrgAreaId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDRouteDataStru��CBTC������������
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: CBTC������������
*/ 
UINT16_S GetRouteDataStrucbtcTrgAreaNum(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].cbtcTrgAreaNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDRouteDataStru��CBTC��������ID
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: CBTC��������ID
*/ 
UINT16_S* GetRouteDataStrucbtcTrgAreaId(const UINT16_S routeId)
{
    UINT16_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].cbtcTrgAreaId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDRouteDataStru������CI������
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����CI������
*/ 
UINT16_S GetRouteDataStrumanageCI(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].manageCI;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* ���������� ��ȡ��·��·���ID
* ����˵���� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:��·���ID
*/
UINT16_S GetLineRouteMaxId(void)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S routeId = 0u;/*��·ID*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumRoute; i++)
    {
        if (routeId < RouteDataStru[i].routeId)
        {
            routeId = RouteDataStru[i].routeId;
        }
    }

    if(routeId != 0u)
    {
        retVal = routeId;
    }

    return retVal;
}

/*
* ���������� ��ȡ��·��Ӧ����������Ϣ
* ����˵���� const UINT16_S routeId,��·ID
*            UINT16_S* pOverlapId����������IDָ��
* ����ֵ  �� 0xff: ��ȡ����ʧ��
*            >=0:������������
*/
UINT16_S GetLineRouteOfOverlapInfo(const UINT16_S routeId,UINT16_S* pOverlapId)
{
    UINT16_S retVal = UINT16_NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/

    if (pOverlapId != NULL)
    {
        if (bufIndex < LineNumRoute)
        {
            MemoryCpy(pOverlapId,sizeof(UINT16_S)*ROUTE_PROTECT_SEC_MAX_NUM,RouteDataStru[bufIndex].protectSecId,sizeof(UINT16_S)*ROUTE_PROTECT_SEC_MAX_NUM);
            retVal = RouteDataStru[bufIndex].protectSecNum;
        }
        else
        {
            retVal = UINT16_NULL;
        }
    }
    else
    {
        retVal = UINT16_NULL;
    }

    return retVal;
}

/*
* ���������� ��ȡ��·��Ӧ����������Ϣ
* ����˵���� const UINT16_S routeId,��·ID
*            UINT16_S* pAcId����������ID�������
* ����ֵ  �� 0xffFF: ��ȡ����ʧ��
*            >=0:������������
*/
UINT16_S GetLineRouteOfAcInfo(const UINT16_S routeId,UINT16_S* pAcId)
{
    UINT16_S retVal = UINT16_NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/

    if (pAcId != NULL)
    {
        bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
        if (bufIndex < LineNumRoute)
        {
            MemoryCpy(pAcId,sizeof(UINT16_S)*ROUTE_SEC_MAX_NUM,RouteDataStru[bufIndex].AxleSec,sizeof(UINT16_S)*ROUTE_SEC_MAX_NUM);
            retVal = RouteDataStru[bufIndex].includeAxleSecNum;
        }
        else
        {
            /*Do nothing currently !*/
        }
    }
    else
    {
        retVal = UINT16_NULL;
    }

    return retVal;
}

/*
* ���������� ��ȡ��·��·����ZCID
* ����˵���� const UINT16_S routeId,��·ID
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:����ZCID
*/
UINT16_S GetLineRouteBelongZcId(const UINT16_S routeId)
{
    UINT16_S retVal = UINT16_NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetRouteDataStruIndex(routeId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].manageZCId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}
