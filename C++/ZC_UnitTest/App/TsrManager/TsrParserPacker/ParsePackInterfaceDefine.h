/*******************************************
�ļ���	��ParsePackInterfaceDefine.h
����	������
����ʱ�䣺2016-10
����	���ӿ�����ͷ�ļ�
��ע	����
*******************************************/

#ifndef PARSEPACK_INTERFACE_DEFINE_H_
#define PARSEPACK_INTERFACE_DEFINE_H_

/*ATS��DSU����궨��*/
#define ZC_TO_ATS_TSR_NORMAL_REPORT        0x0080         /*�����㱨TSR*/
#define ZC_TO_ATS_TSR_RESET_REPORT         0x0070         /*������㱨TSR*/
#define ATS_TO_ZC_TSR_FRT_CONFIRM          0x0071u         /*�״��ϵ�ȷ��*/
#define ZC_TO_ATS_TSR_FRT_CONFIRM_REPLY   0x0072u         /*�״��ϵ�ȷ�ϻظ�*/
#define ATS_TO_ZC_TSR_SEC_CONFIRM         0x0073u         /*�ٴ��ϵ�ȷ��*/
#define ZC_TO_ATS_TSR_SEC_CONFIRM_REPLY   0x0074u         /*�ٴ��ϵ�ȷ�ϻظ�*/
#define ATS_TO_ZC_TSR_FRT_SET              0x0090u         /*�״�����*/
#define ZC_TO_ATS_TSR_FRT_SET_REPLY       0x0091u         /*�״����ûظ�*/
#define ATS_TO_ZC_TSR_SEC_SET              0x0092u         /*�ٴ�����*/
#define ZC_TO_ATS_TSR_SEC_SET_REPLY        0x0093u         /*�ٴ����ûظ�*/
#define ATS_TO_ZC_TSR_FRT_CANCEL           0x00A0u         /*�״�ȡ��*/
#define ZC_TO_ATS_TSR_FRT_CANCEL_REPLY     0x00A1u         /*�״�ȡ���ظ�*/
#define ATS_TO_ZC_TSR_SEC_CANCEL           0x00A2u         /*�ٴ�ȡ��*/
#define ZC_TO_ATS_TSR_SEC_CANCEL_REPLY     0x00A3u         /*�ٴ�ȡ���ظ�*/

/*TSR��Ӧ��-ͨ��*/
#define TSR_UNKNOWN                0u                 /*δ֪��DSU��ATS�״�����Ӧ����Ϣ��*/
#define TSR_OK                     1u                 /*�ɹ�*/
#define TSR_RANDOMCODE_SEC_DIFFER_FROM_FIR                     2u                 /*�����������״����������벻һ��*/
#define TSR_OUTOFSETTIME_BETWEEN_FIR_SEC_CMD    3u/*�ȴ��������ʱ*/
#define TSR_CRC32_CHECK_ERROR    4u/*��������CRC32У��ʧ��*/
#define TSR_ATS_FRMAE_TYPE_INCORRECT    5u/*ATS�������ʹ���*/
/*TSR��Ӧ��-�ϵ�ȷ��*/
#define TSR_FIR_CONFIRM_CMD_INCORRECT        20u/*�״�ȥ�ϵ��ϵ�ȷ���������֮ǰ�����������*/
#define TSR_SEC_CONFIRM_CMD_INCORRECT        21u/*����ȥ�ϵ��ϵ�ȷ���������֮ǰ��������״��ϵ�ȷ�����*/
#define TSR_FIR_CONFIRM_CMD_INCORRECT_YETCONFIRMED        22u/*�״�ȥ�ϵ��ϵ�ȷ���������ϵͳ״̬��תΪ�����������ַ������״��ϵ�ȷ�����*/
/*TSR��Ӧ��-������ʱ����*/
#define TSR_FIR_SET_CMD_INCORRECT        30u/*�״�������ʱ�����������֮ǰ�����������*/
#define TSR_SEC_SET_CMD_INCORRECT        31u/*����������ʱ�����������֮ǰ��������״�������ʱ�������*/
#define TSR_TSRQUANTITY_OVERFLOW            32u/*������ʱ���ٸ����������ֵ*/
#define TSR_FIR_SET_TSRSPEEDVALUE_OVERFLOW            33u/*�״�������ʱ���ٵ��ٶȴ����������ֵ*/
#define TSR_FIR_SET_TSRSPEEDVALUE_GREATERTHAN_STATICDEFAULTVALUE            34u/*�״�������ʱ���ٵ��ٶȴ��ڱ��������߼�������С��̬����ֵ*/
#define TSR_SEC_SET_TSRSPEEDVALUE_DIFFERFROMFIR            35u/*���κ��״�������ʱ���ٵ��ٶȲ�һ��*/
#define TSR_FIR_SET_TSRLOGICSECTIONQUANTITY_OVERFLOW            36u/*�״�������ʱ���ٵ��߼����θ�����������߼����θ���*/
#define TSR_FIR_SET_NOTCOMPLYWITHRULES_LOGICSECTIONOUTOFTHISZC            37u/*�״�������ʱ���ٵ��߼����ι���ִ����߼����δ��ڲ����ڱ�ZC�ڣ�*/
#define TSR_FIR_SET_NOTCOMPLYWITHRULES_LOGICSECTIONHASBEENSET            38u/*�״�������ʱ���ٵ��߼����ι���ִ����߼����κ��Ѿ����õ���ʱ���ٵ��߼��������غϣ�*/
#define TSR_FIR_SET_NOTCOMPLYWITHRULES_LOGICSECTIONSARENOTONEBYONE            39u/*�״�������ʱ���ٵ��߼����ι���ִ����߼����β�������*/
#define TSR_FIR_SET_NOTCOMPLYWITHRULES_LOGSECATBOTHSWITCHPOSITON_A            40u/*�״�������ʱ���ٵ��߼����ι���ִ����߼����ΰ���ĳ������Ķ���λ��*/
#define TSR_FIR_SET_NOTCOMPLYWITHRULES_LOGSECATBOTHSWITCHPOSITON_B            41u/*�״�������ʱ���ٵ��߼����ι���ִ����߼�����ͬ�Ѿ�������ʱ�����߼����ΰ���ĳ������Ķ���λ��*/
#define TSR_SEC_SET_TSRLOGICSECTIONQUANTITY_OVERFLOW            42u/*����������ʱ���ٵ��߼����θ�����������߼����θ���*/
#define TSR_SEC_SET_TSRLOGICSECTIONQUANTITY_DIFFERFROMFIR            43u/*���κ��״�������ʱ���ٵ��߼����θ�����һ��*/
#define TSR_SEC_SET_TSRLOGICSECTIONID_DIFFERFROMFIR            44u/*���κ��״�������ʱ���ٵ��߼�����ID��һ��*/
/*TSR��Ӧ��-ȡ����ʱ����*/
#define TSR_FIR_CANCEL_CMD_INCORRECT            60u/*�״�ȡ����ʱ�����������֮ǰ�����������*/
#define TSR_SEC_CANCEL_CMD_INCORRECT            61u/*����ȡ����ʱ�����������֮ǰ��������״�ȡ����ʱ�������*/
#define TSR_FIR_CANCEL_CMD_INCORRECT_ZCHASNOTSR            64u/*�״�ȡ����ʱ���ٴ���ZCû����ʱ���٣�*/
#define TSR_FIR_CANCEL_TSRLOGICSECTIONQUANTITY_OVERFLOW           65u/*�״�ȡ����ʱ���ٵ��߼����θ�����������߼����θ���*/
#define TSR_FIR_CANCEL_CMD_INCORRECT_NOTSET           66u/*�״�ȡ����ʱ���ٴ���û���ҵ���Ӧ���õ���ʱ���٣�*/
#define TSR_SEC_CANCEL_TSRLOGICSECTIONQUANTITY_OVERFLOW           67u/*����ȡ����ʱ���ٵ��߼����θ�����������߼����θ���*/
#define TSR_SEC_CANCEL_TSRLOGICSECTIONQUANTITY_DIFFERFROMFIR           68u/*���κ��״�������ʱ���ٵ��߼����θ�����һ��*/
#define TSR_SEC_CANCEL_TSRLOGICSECTIONID_DIFFERFROMFIR           69u/*���κ��״�������ʱ���ٵ��߼�����ID��һ��*/

/*���һ��ATS������������*/
#define LAST_ATS_SET_CMD_DEFAULT    0u              /*Ĭ��ֵ û������*/
#define LAST_ATS_FR_SET_CMD         1u				/*�״���������*/
#define LAST_ATS_FR_CANCEL_CMD      2u				/*�״�ȡ������*/
#define LAST_ATS_FR_CONFIRM_CMD     3u				/*�״�ȥ�ϵ�����*/
#define LAST_ATS_SR_SET_CMD         4u
#define LAST_ATS_SR_CANSCEL_CMD      5u
#define LAST_ATS_SR_CONFIRM_CMD     6u

#endif 
