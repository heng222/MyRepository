/********************************************************                                                                                                           
 �� �� ���� ChangeDefine.h
 ��    �ߣ� ZC��
 ����ʱ�䣺 2015.04.18
 ������ �л�����궨��  
 ��ע�� ��  
********************************************************/ 


#ifndef CHANGE_DEFINE_H_
#define CHANGE_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"

/*�л���·�������ֵ*/
#define CHANGE_LINE_SUM_MAX                      300U    /*�����л���·���ֵ*/

/*���ع�����л���·�������ֵ*/
#define CHANGE_LINE_LOCAL_SUM_MAX                30U     /*���屾�ع�����л���·���ֵ*/

#define CHANGE_LINE_SWITCH_MAX                   10U     /*���嵥����·����������������*/

/*�л������������ֵ*/
#define CHANGE_AREA_SUM_MAX                      50U    /*�����л��������ֵ*/

/*���ع����������·�������ֵ*/
#define CHANGE_AREA_LOCAL_SUM_MAX                30U     /*���屾�ع�����л��������ֵ*/

#define CHANGE_AREA_OBS_MAX                      50U     /*���嵥���������������ϰ�������*/

#define CHANGE_AREA_ROUTE_MAX                    20U
#define CHANGE_AREA_OVERLAP_MAX                  20U
#define CHANGE_AREA_SIGNAL_MAX                   20U
#define CHANGE_AREA_SWITCH_MAX                   20U
#define CHANGE_AREA_PSD_MAX                      20U
#define CHANGE_AREA_ESB_MAX                      20U
#define CHANGE_AREA_DRBUTTON_MAX                 20U
#define CHANGE_AREA_DRLAMP_MAX                   20U
#define CHANGE_AREA_AC_MAX                       50U
#define CHANGE_AREA_LOGIC_MAX                    500U

/*����ZC��λֵ*/
#define  BIT_TRUE				1U
#define  BIT_FALSE              0U
#define  BIT_DEFAULT            2U
#define  BIT_LOSE               3U               /*�����Ŀ�*/

/*����ZC�л����������ϰ�����λ��С*/
#define ZC_NZC_MASK_NUM_MAX     1000U             /*��λ���ֵ*/

/*����ZC-NZC��λ���С*/
#define ZC_NZC_SWITCH_MASK_SUM     10U           /*������λ���ݴ�С*/
#define ZC_NZC_SIGNAL_MASK_SUM     8U            /*�źŻ���λ���ݴ�С*/
#define ZC_NZC_PSD_MASK_SUM        8U            /*��������λ���ݴ�С*/
#define ZC_NZC_ESB_MASK_SUM        8U            /*����ͣ����ť��λ���ݴ�С*/
#define ZC_NZC_AC_MASK_SUM         9U            /*����������λ���ݴ�С*/  /*8->9*/
#define ZC_NZC_ROUTE_MASK_SUM      8U            /*��·��λ���ݴ�С*/
#define ZC_NZC_OVERLAP_MASK_SUM    8U            /*����������λ���ݴ�С*/
#define ZC_NZC_DR_MASK_SUM         10U           /*�����۷���������ť�͵ƣ���λ���ݴ�С*/

/* ����������ο��л��ķ��� */
#define AC_CHANGER_DIR_DOUBLE  0xccU   /* ���кͷ��� */
#endif
