/************************************************************************
 �ļ�����  MADefine.h
 ����  ��  ZC��
 ����ʱ�� ��  2015-04-18
 ���� ��  �ƶ���Ȩ�궨��
 ��ע �� ��
************************************************************************/
#ifndef MA_DEFINE_H_
#define MA_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"
#include "../../LineDataManager/Route/RouteDefine.h"
#include "../Train/TrainDefine.h"

/*�ƶ���Ȩ�������ϰ�������*/
#define MA_AREA_OBS_SUM_MAX              (ROUTE_OF_OBS_SUM_MAX * SIZE_MAX_ROUTENUM)    /*�������������ֵ*/

/*�ƶ���Ȩ��������ʱ��������*/
#define MA_AREA_TSR_SUM_MAX              20U                                          /*�����ƶ���Ȩ��������ʱ��������*/

/*MA�յ����Զ���*/
#define	MA_END_ATT_CBTC					 1U			                                  /*�˳�CBTC�յ�*/
#define MA_END_ATT_REVERT				 2U			                                  /*�۷���*/
#define	MA_END_ATT_OTHER			     3U			                                  /*���������յ�*/

/*MA�յ��ϰ�������*/
#define MA_OBS_TYPE_COMM_UNCT_TRAIN      1U

/*MA����*/
#define NORMAL_MA_TYPE                   0xaaU                                        /*�����ƶ���Ȩ*/
#define ABNORMAL_MA_TYPE                 0x55U                                        /*�����ƶ��ƶ���Ȩ*/
#define CANCELLATION_MA_TYPE             0x88U                                        /*ע�����͵��ƶ���Ȩ*/
#define NO_MA_TYPE                       0xddU                                        /*���ƶ���Ȩ*/

#endif
