/************************************************************************
*
* �ļ���   ��  RouteDefine.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��·�궨��
* ��  ע   ��  ��
*
************************************************************************/
#ifndef ROUTE_DEFINE_H_
#define ROUTE_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"

/*��·�������ֵ*/
#define ROUTE_SUM_MAX                             1200U   /*�����·���ֵ*/

/*���ع���Ľ�·�������ֵ*/
#define ROUTE_LOCAL_SUM_MAX                       (100U + 210U)    /*���屾�ع���Ľ�·���ֵ*/ /* 210->310 */

/*������·�ڰ�������������������*/
#define ROUTE_OF_AC_SUM_MAX                       20U     /*��·�ڰ�������������������*/

/*������·�ڰ�������󱣻���������*/
#define ROUTE_OF_OVERLAP_SUM_MAX                  5U      /*��·�ڰ�������������������*/

/*������·�ڰ���������ϰ�������*/
#define ROUTE_OF_OBS_SUM_MAX                      10U     /*��·�ڰ���������ϰ�������*/

/*��·״̬*/
#define ROUTE_STATE_SET                           0x55U   /*��·������*/
#define ROUTE_STATE_UNSET                         0xaaU   /*��·δ����*/

#define ROUTE_STOP_REQ_SET                        0x55U   /* �н�·ͣ����֤���� */
#define ROUTE_STOP_REQ_UNSET                      0xaaU   /* �޽�·ͣ����֤���� */

#define ROUTE_STOP_CONFIRM_SET                        0x55U   /* �н�·ͣ����֤ȷ�� */
#define ROUTE_STOP_CONFIRM_UNSET                      0xaaU   /* �޽�·ͣ����֤ȷ�� */

#endif
