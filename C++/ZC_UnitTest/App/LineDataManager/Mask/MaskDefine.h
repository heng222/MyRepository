/************************************************************************
*
* �ļ���   ��  MaskDefine.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��λ�ĺ궨��
* ��  ע   ��  ��
*
************************************************************************/
#ifndef MASK_DEFINE_H_
#define MASK_DEFINE_H_

#include "../../SysDataManager/SysDefine.h"

/*ZC��CI����λ�����������ֵ*/
#define ZC_TO_CI_MASK_SUM_MAX                5000U      /*ZC��CI����λ�����������ֵ*/

/*����ZC��CI����λ�����������ֵ*/
#define SINGLE_ZC_TO_CI_MASK_SUM_MAX         1000U      /*ZC��CI����λ�����������ֵ*/

/*CI��ZC����λ�����������ֵ*/
#define CI_TO_ZC_MASK_SUM_MAX                5000U      /*CI��ZC����λ�����������ֵ*/

/*����CI��ZC����λ�����������ֵ*/
#define SINGLE_CI_TO_ZC_MASK_SUM_MAX         1000U      /*CI��ZC����λ�����������ֵ*/

/*���ع���ĵ�����λ��Ӧ���豸�������ֵ*/
#define SINGLE_MASK_DEVICE_SUM_MAX           5U         /*���ع���ĵ�����λ��Ӧ���豸�������ֵ*/


/*����ZC��CIͨ����λ������Ϣ*/
#define CI_ZC_SWITCH_MASK_LEN                8U         /*CI-ZC��������Ϣ*/
#define CI_ZC_SIGNAL_MASK_LEN                8U         /*CI-ZC�źŻ�������Ϣ*/
#define CI_ZC_PSD_MASK_LEN                   4U         /*CI-ZC-PSD������Ϣ*/
#define CI_ZC_ESB_MASK_LEN                   4U         /*CI-ZC-ESB������Ϣ*/
#define CI_ZC_AC_SGMT_MASK_LEN               14U        /*CI-ZC�������γ�����Ϣ*/ 
#define CI_ZC_SECTION_MASK_LEN               6U         /*CI-ZC�߼����γ�����Ϣ*/
#define CI_ZC_ROUTE_MASK_LEN                 8U         /*CI-ZC��·������Ϣ*/  /* 4->8 */
#define CI_ZC_OVERLAP_MASK_LEN               4U         /*CI-ZC�������γ�����Ϣ*/
#define CI_ZC_DR_MASK_LEN                    8U         /*CI-ZC�����۷�������Ϣ*/

/*����ZC��CI��λ������Ϣ*/
#define SWITCH_FRONT_MASK_TYPE               1U         /*����λ��Ϣ��λ����*/
#define SWITCH_SIDE_MASK_TYPE                2U         /*����λ��Ϣ��λ����*/
#define SWITCH_LOCK_MASK_TYPE                3U         /*����������Ϣ��λ����*/
#define SIGNAL_STATUS_MASK_TYPE              4U         /*�źŻ�״̬��Ϣ��λ��Ϣ*/
#define SIGNAL_CROSS_MASK_TYPE               5U         /*�źŻ���ѹ��Ϣ��λ��Ϣ*/
#define SIGNAL_LIGHT_OFF_MASK_TYPE           6U         /*�źŻ��������Ϣ��λ��Ϣ*/
#define PSD_STATUS_MASK_TYPE                 7U         /*PSD״̬��Ϣ��λ��Ϣ*/
#define ESB_STATUS_MASK_TYPE                 8U         /*ESB״̬��Ϣ��λ��Ϣ*/
#define AC_UP_DIR_MASK_TYPE                  9U         /*�������з���״̬��Ϣ��λ��Ϣ*/
#define AC_DOWN_DIR_MASK_TYPE                10U        /*�������з���״̬��Ϣ��λ��Ϣ*/
#define AC_OCC_STATUS_MASK_TYPE              11U        /*����ռ��״̬��Ϣ��λ��Ϣ*/
#define AC_LOCK_STATUS_MASK_TYPE             12U        /*��������״̬��Ϣ��λ��Ϣ*/
#define AC_ARB_STATUS_MASK_TYPE              13U        /*����ARB״̬��Ϣ��λ��Ϣ*/
#define AC_STOP_STATUS_MASK_TYPE             14U        /*����ͣ��״̬��Ϣ��λ��Ϣ*/
#define SECTION_UT_OCC_MASK_TYPE             15U        /*�߼�����UTռ��״̬��Ϣ��λ��Ϣ*/
#define SECTION_CT_OCC_MASK_TYPE             16U        /*�߼�����CTռ��״̬��Ϣ��λ��Ϣ*/
#define SECTION_TSR_MASK_TYPE                17U        /*�߼�������ʱ����״̬��Ϣ��λ��Ϣ*/
#define ROUTE_STATUS_MASK_TYPE               18U        /*��·״̬��Ϣ��λ��Ϣ*/
#define OVERLAP_STATUS_MASK_TYPE             19U        /*��������״̬��Ϣ��λ��Ϣ*/
#define DR_LAMP_TWINKLE_STATUS_MASK_TYPE     20U        /*�����۷���������Ϣ��λ��Ϣ*/
#define DR_LAMP_STEADY_STATUS_MASK_TYPE      21U        /*�����۷����ȵ���Ϣ��λ��Ϣ*/
#define DR_BUTTON_STATUS_MASK_TYPE           22U        /*�����۷���ťվ̨��Ϣ��λ��Ϣ*/
#define ROUTE_STOP_REQUEST_MASK_TYPE         23U        /* ��·ͣ����֤������λ */
#define ROUTE_STOP_CONFIRM_MASK_TYPE         24U        /* ��·ͣ����֤ȷ����λ */

#endif
