/*************************************************
  �ļ���   ��RouteData.h
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
#ifndef ROUTE_DATA_H_
#define ROUTE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define ROUTE_NAME_BYTE_LEN                  24                          /*��·�����ֽڳ���*/
#define ROUTE_SEC_MAX_NUM                      ( 9 + 11)                              /*����������Ŀ*/
#define ROUTE_PROTECT_SEC_MAX_NUM             5                             /*����������Ŀ*/
#define ROTRE_ACCESS_SEC_MAX_NUM              (4  + 1)                           /*�ӽ����������Ŀ*/
#define ROUTE_TRG_SEC_MAX_NUM                  (4 +1 )                        /*�������������Ŀ*/
#define ROUTE_LINE_BYTE_NUM                  (106+30)                         /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*Route�����ݽṹ��*/
typedef struct BnfRouteStruct
{
    UINT16_S  routeId;                                                    /*�������*/
    UINT8_S  routeName[ROUTE_NAME_BYTE_LEN];                                /*��·����*/
    UINT16_S  routeType;                                                    /*��·����*/
    UINT16_S  startSignalId;                                                /*��ʼ�źŻ����*/
    UINT16_S  endSignalId;                                                /*��ֹ�źŻ����*/
    UINT16_S  includeAxleSecNum;                                            /*��������������Ŀ*/
    UINT16_S  AxleSec[ROUTE_SEC_MAX_NUM];                                    /*�������α��*/
    UINT16_S  protectSecNum;                                                /*����������Ŀ*/
    UINT16_S  protectSecId[ROUTE_PROTECT_SEC_MAX_NUM];                    /*�������α��*/
    UINT16_S  blogAccessSegNum;                                            /*��ʽ�ӽ�������Ŀ*/    
    UINT16_S  blogAccessSegId[ROTRE_ACCESS_SEC_MAX_NUM];                    /*��ʽ�ӽ����α��*/
    UINT16_S  cbtcAccessSegNum;                                            /*CBTC�ӽ�������Ŀ*/    
    UINT16_S  cbtcAccessSegId[ROTRE_ACCESS_SEC_MAX_NUM];                    /*CBTC�ӽ����α��*/
    UINT16_S  blocTrgAreaNum;                                                /*��ʽ������������*/
    UINT16_S  blocTrgAreaId[ROUTE_TRG_SEC_MAX_NUM];                        /*��ʽ��������ID*/
    UINT16_S  cbtcTrgAreaNum;                                                /*CBTC������������*/
    UINT16_S  cbtcTrgAreaId[ROUTE_TRG_SEC_MAX_NUM];                        /*CBTC��������ID*/    
    UINT16_S  manageCI;                                                    /*����CI������*/

    /*��̬�����ֶ�*/
    UINT16_S  manageZCId;                                                    /*����ZC����ID*/
}BnfRouteStruct;

/*
* ���������� ��RouteDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocRouteDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡRouteData����
* ����˵����
* ����ֵ  �� 
            BnfRouteStruct*
*/
BnfRouteStruct *GetRouteData(void);

/*
* ���������� ��ȡRouteData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfRouteStruct*
*/
BnfRouteStruct *GetRouteDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDRouteDataStru�Ľṹ���±�
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetRouteDataStruIndex(const UINT16_S routeId);

/*
** ���������� ��ȡָ��IDRouteDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfRouteStruct* GetIndexIdRouteDataStru(const UINT16_S routeId);

/*
** ���������� ��ȡָ��IDRouteDataStru�Ľ�·����
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ��·����
*/ 
UINT8_S* GetRouteDataStrurouteName(const UINT16_S routeId);

/*
** ���������� ��ȡָ��IDRouteDataStru�Ľ�·����
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��·����
*/ 
UINT16_S GetRouteDataStrurouteType(const UINT16_S routeId);

/*
** ���������� ��ȡָ��IDRouteDataStru����ʼ�źŻ����
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��ʼ�źŻ����
*/ 
UINT16_S GetRouteDataStrustartSignalId(const UINT16_S routeId);

/*
** ���������� ��ȡָ��IDRouteDataStru����ֹ�źŻ����
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��ֹ�źŻ����
*/ 
UINT16_S GetRouteDataStruendSignalId(const UINT16_S routeId);

/*
** ���������� ��ȡָ��IDRouteDataStru�İ�������������Ŀ
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��������������Ŀ
*/ 
UINT16_S GetRouteDataStruincludeAxleSecNum(const UINT16_S routeId);

/*
** ���������� ��ȡָ��IDRouteDataStru�ļ������α��
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: �������α��
*/ 
UINT16_S* GetRouteDataStruAxleSec(const UINT16_S routeId);

/*
** ���������� ��ȡָ��IDRouteDataStru�ı���������Ŀ
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����������Ŀ
*/ 
UINT16_S GetRouteDataStruprotectSecNum(const UINT16_S routeId);

/*
** ���������� ��ȡָ��IDRouteDataStru�ı������α��
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: �������α��
*/ 
UINT16_S* GetRouteDataStruprotectSecId(const UINT16_S routeId);

/*
** ���������� ��ȡָ��IDRouteDataStru�ĵ�ʽ�ӽ�������Ŀ
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��ʽ�ӽ�������Ŀ
*/ 
UINT16_S GetRouteDataStrublogAccessSegNum(const UINT16_S routeId);

/*
** ���������� ��ȡָ��IDRouteDataStru�ĵ�ʽ�ӽ����α��
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ��ʽ�ӽ����α��
*/ 
UINT16_S* GetRouteDataStrublogAccessSegId(const UINT16_S routeId);

/*
** ���������� ��ȡָ��IDRouteDataStru��CBTC�ӽ�������Ŀ
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: CBTC�ӽ�������Ŀ
*/ 
UINT16_S GetRouteDataStrucbtcAccessSegNum(const UINT16_S routeId);

/*
** ���������� ��ȡָ��IDRouteDataStru��CBTC�ӽ����α��
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: CBTC�ӽ����α��
*/ 
UINT16_S* GetRouteDataStrucbtcAccessSegId(const UINT16_S routeId);

/*
** ���������� ��ȡָ��IDRouteDataStru�ĵ�ʽ������������
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��ʽ������������
*/ 
UINT16_S GetRouteDataStrublocTrgAreaNum(const UINT16_S routeId);

/*
** ���������� ��ȡָ��IDRouteDataStru�ĵ�ʽ��������ID
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ��ʽ��������ID
*/ 
UINT16_S* GetRouteDataStrublocTrgAreaId(const UINT16_S routeId);

/*
** ���������� ��ȡָ��IDRouteDataStru��CBTC������������
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: CBTC������������
*/ 
UINT16_S GetRouteDataStrucbtcTrgAreaNum(const UINT16_S routeId);

/*
** ���������� ��ȡָ��IDRouteDataStru��CBTC��������ID
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: CBTC��������ID
*/ 
UINT16_S* GetRouteDataStrucbtcTrgAreaId(const UINT16_S routeId);

/*
** ���������� ��ȡָ��IDRouteDataStru������CI������
* ����˵���� const UINT16_S routeId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����CI������
*/ 
UINT16_S GetRouteDataStrumanageCI(const UINT16_S routeId);

/*
* ���������� ��ȡ��·��·���ID
* ����˵���� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:��·���ID
*/
UINT16_S GetLineRouteMaxId(void);

/*
* ���������� ��ȡ��·��Ӧ����������Ϣ
* ����˵���� const UINT16_S routeId,��·ID
*            UINT16_S* pOverlapId����������IDָ��
* ����ֵ  �� 0xff: ��ȡ����ʧ��
*            >=0:������������
*/
UINT16_S GetLineRouteOfOverlapInfo(const UINT16_S routeId,UINT16_S* pOverlapId);

/*
* ���������� ��ȡ��·��Ӧ����������Ϣ
* ����˵���� const UINT16_S routeId,��·ID
*            UINT16_S* pAcId����������ID�������
* ����ֵ  �� 0xff: ��ȡ����ʧ��
*            >=0:������������
*/
UINT16_S GetLineRouteOfAcInfo(const UINT16_S routeId,UINT16_S* pAcId);

/*
* ���������� ��ȡ��·��·����ZCID
* ����˵���� const UINT16_S routeId,��·ID
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:����ZCID
*/
UINT16_S GetLineRouteBelongZcId(const UINT16_S routeId);

#ifdef __cplusplus
}
#endif

#endif
