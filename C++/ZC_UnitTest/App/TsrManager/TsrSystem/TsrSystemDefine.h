/*******************************************
�ļ���	��TsrSystemDefine.h
����	������
����ʱ�䣺2016-10
����	��ϵͳ��������ͷ�ļ�
��ע	����
*******************************************/

#ifndef TSR_SYSTEM_DEFINE_H_
#define TSR_SYSTEM_DEFINE_H_

#include "..\..\..\PlatformAdapter\AppItf\AdptAppCommonDef.h"

#define MAX_SECTION_ID_NUM  1000u   /*����߼�����ID*/

#define MAX_ATS_QUAN 16u            /*���ATS����*/

/*�����㱨TSR���������̶��ǻ㱨�г�λ����������25�������������0.8S��ǰ����20S��������1.2S��ǰ����30S*/
#define AUTOREPTSR_TIMESOVER_REPTRNPOS 25u

/*****����ֵ����*****/
#define TSR_ERROR               0x00u	    /*��������ʧ��*/
#define TSR_SUCCESS             0x01u	    /*�������سɹ�*/
#define DEFAULT_ZERO            0u
#define SIGNED_DEFAULT_ZERO     0

/*ZC����״̬*/
#define ZC_WORK_POP          0x55u         /*�ϵ�*/
#define ZC_WORK_NORMAL       0xaau         /*����*/

#define AUTO_REPLYTO_ATS    1u            /*�����㱨TSR��־,���������㱨TSR�������㱨TSR����*/

#define ANTI_RES_REPLYTO_ATS                   0x55u      /*δ�յ�ATS�����־*/
#define RES_REPLYTO_ATS                  0xaau      /*�յ�ATS�����־*/

/*Ӧ�����Ͷ���*/
#define APP_TYPE_ATS    DEVTYPE_ATS          /*ATS*/
/*#define APP_TYPE_LOG    DEVTYPE_MAINTAIN*/     /* ������־�豸���� */
/*#define APP_TYPE_RECORD DEVTYPE_RECORD*/       /* ��¼���豸���� */

#endif