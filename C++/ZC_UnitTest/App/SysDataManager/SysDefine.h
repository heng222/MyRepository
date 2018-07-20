/************************************************************************
*
* �ļ���   ��  SysDefine.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ����ϵͳʹ�õĺ�
* ��  ע   ��  ��
*
************************************************************************/

#ifndef SYS_DEFINE_H_
#define SYS_DEFINE_H_

#include "../../Dmu/DmuComm/DataHandle/DmuCommDataTypeDefine.h"
#include "../../PlatformAdapter/AppItf/AdptAppCommonDef.h"

/*----------Common----------*/
#define RETURN_ERROR                        ((UINT8_S)(0x00U))	          /*��������ʧ��*/
#define RETURN_SUCCESS                      ((UINT8_S)(0x01U))	          /*�������سɹ�*/
#define SIGNED_RETURN_SUCCESS               0x01	                      /*�������سɹ�-�з���*//*-bye-*/
#define RETURN_NULL                         ((UINT8_S)(0x00U))              /*���ؿ�ָ��*/
#define RETURN_UINT8_MAX_VALUE              ((UINT8_S)(0xffU))              /*��������Ĭ�����ֵ��8λ��*/
#define RETURN_UINT16_MAX_VALUE             ((UINT16_S)(0xffffU))            /*��������Ĭ�����ֵ��16λ��*/
#define RETURN_UINT32_MAX_VALUE             ((UINT32_S)(0xffffffffU))        /*��������Ĭ�����ֵ��32λ��*/

#define FLAG_SET                            ((UINT8_S)(0x55U))              /*��־λ����λ*/
#define FLAG_UNSET                          ((UINT8_S)(0xAAU))              /*��־λδ��λ*/
#define DEFAULT_0XFF                        ((UINT8_S)(0xffU))              /*������ʼֵΪ0xff*/
#define SIZE_UINT8                          (sizeof(UINT8_S))    /*UINT8������Ӧ�ֽڳ���*/
#define SIZE_UINT16                         (sizeof(UINT16_S))    /*UINT16������Ӧ�ֽڳ���*/
#define SIZE_UINT32                         (sizeof(UINT32_S))   /*UINT32������Ӧ�ֽڳ���*/
#define DEFAULT_UINT8_VALUE                 ((UINT8_S)(0xffU))              /*�г�ʹ�õ�Ĭ��ֵ��8λ��*/
#define DEFAULT_UINT16_VALUE                ((UINT16_S)(0xffffU))            /*�г�ʹ�õ�Ĭ��ֵ��16λ��*/
#define DEFAULT_UINT32_VALUE                ((UINT32_S)(0xffffffffU))        /*�г�ʹ�õ�Ĭ��ֵ��32λ��*/

#define COMM_CI_SUM_MAX                      6U                /*��ZCͨ�ŵ������������*/
#define COMM_ATS_SUM_MAX                     1U                /*��ZCͨ�ŵ����ATS����*/
#define COMM_DSU_SUM_MAX                     1U                /*��ZCͨ�ŵ����DSU����*/
#define COMM_ZC_SUM_MAX                      6U                /*��ZCͨ�ŵ����nZC����*/
#define COMM_TRAIN_SUM_MAX                   40U                /*��ZCͨ�ŵ�����г�����*/

#define LOG_SUM_MAX                          15U               /* ��־�ְ����� */

#define LINE_ZC_SUM_MAX                      20U              /*��·����ZC����*/
#define LINE_CI_SUM_MAX                      20U               /*��·����CI����(����CIID)*/

/* Ϊ��ʹ�ü����������Ͷ��� */
#define	INNER_DEVTYPE_CI	                         ((UINT8_S)(DEVTYPE_CI))             /*CI�������ͺ����*/	
#define	INNER_DEVTYPE_ZC	                         ((UINT8_S)(DEVTYPE_ZC))             /*����ZC���ݺ����*/	
#define	INNER_DEVTYPE_ATS	                         ((UINT8_S)(DEVTYPE_ATS))               /*ATS���ݺ����*/	
#define	INNER_DEVTYPE_TRAIN                          ((UINT8_S)(DEVTYPE_VOBC))             /*����ATP���ݺ����*/
#define	INNER_DEVTYPE_NTP		                     ((UINT8_S)(DEVTYPE_NTP))             /*NTP���ݺ����*/
#define ZC_DEVTYPE_MIC                                    ((UINT32_S)(0x0302))             /*ͨ�Ű�����*/
#define ZC_DEVTYPE_SME                                    ((UINT32_S)(0x0301))             /*����������*/

/*������־�����*/
#define	INNER_DEVTYPE_LOG		                     ((UINT8_S)(DEVTYPE_MAINTAIN))             /*��־���ݺ����*/

#define LINE_MAX_TRAIN_ID                    151U              /*��·�����г�ID*/

#define ZC_RESET_STATUS_FLAG_SET             ((UINT8_S)(0x55U))             /*zc��λ��־λ����λ*/
#define ZC_RESET_STATUS_FLAG_UNSET           ((UINT8_S)(0xAAU))             /*zc��λ��־λδ��λ*/

#define ZC_INIT_NTP_TIME_SUCC_FLAG_SET       ((UINT8_S)(0x55U))             /*ZC��ʼ���ϵ�Уʱ�ɹ�*/
#define ZC_INIT_NTP_TIME_SUCC_FLAG_UNSET     ((UINT8_S)(0xAAU))             /*ZC��ʼ���ϵ�Уʱ���ɹ�*/

#define ZC_TWO_POINT_AC_NUM_MAX                 20U               /*����֮�����ļ�����������*/
#define ZC_TWO_POINT_SWITCH_NUM_MAX             30U               /*����֮�����ĵ�������*/
#define ZC_TWO_POINT_PSD_NUM_MAX                10U               /*����֮����������������*/
#define ZC_TWO_POINT_ESB_NUM_MAX                10U               /*����֮�����Ľ���ͣ����ť����*/

/*�ϰ���궨��*/
#define	OBS_TYPE_SIGNAL		((UINT8_S)(0x01U))    /*�źŻ�*/
#define	OBS_TYPE_PSD  		((UINT8_S)(0x02U))    /*������*/
#define	OBS_TYPE_ESB        ((UINT8_S)(0x03U))    /*վ̨����ͣ����ť*/
#define	OBS_TYPE_POINT		((UINT8_S)(0x04U))    /*����*/
#define	OBS_TYPE_PLATFORM	((UINT8_S)(0x05U))    /*վ̨����*/
#define	OBS_TYPE_EXIT	    ((UINT8_S)(0x06U))    /*��������*/
#define	OBS_TYPE_ZC_CHANGE	((UINT8_S)(0x07U))    /*ZC�߽��*/
#define	OBS_TYPE_RES		((UINT8_S)(0x08U))    /*��������*/
#define OBS_TYPE_TRAIN_TAIL	((UINT8_S)(0x09U))    /*ǰ���г���β*/
#define OBS_TYPE_TRAIN_HEAD	((UINT8_S)(0x0aU))    /*ǰ���г���ͷ*/
#define OBS_TYPE_AC	        ((UINT8_S)(0x0bU))    /*��������*/	
#define OBS_TYPE_UT	        ((UINT8_S)(0x0cU))    /*�������Σ���ͨ�ų�ռ�õ�ʹ�ü�������ʼ�˵������*/	
#define OBS_TYPE_OVERLAP	((UINT8_S)(0x0dU))    /*Overlap*/	
#define OBS_TYPE_DRB	    ((UINT8_S)(0x0eU))    /*�����۷���ť*/	
#define OBS_TYPE_DRL	    ((UINT8_S)(0x0fU))   /*�����۷���*/	
#define OBS_TYPE_ROUTE	    ((UINT8_S)(0x10U))    /*��·*/	
#define OBS_TYPE_LS	        ((UINT8_S)(0x11U))    /*�߼�����*/

#define ZC_TO_ATS_BLOCK_INFO          101U               /*ZC��ATS���г�ռ����Ϣ*/
#define ZC_ATS_PRTCL_VERSION          ((UINT16_S)(0x3001U))            /*ZC��ATSӦ�ò�ͨ��Э��汾��*/

/*����׷�ٲ����󷽼�������ǵ�RM�г�����*/
#define TRACE_RM_TRAIN_TYPE_TAIL    ((UINT8_S)(0x55U))  /*׷���������󷽼�������г���β�س���ȫ����*/
#define TRACE_RM_TRAIN_TYPE_BACK    ((UINT8_S)(0xAAU))  /*׷���������󷽼�������г���β���ڼ�������ʼ�˻س���ȫ����*/

/*����ZC���������ļ�·��*/
#ifdef SYS_TYPE_VXWORKS
#define ZC_ID_CONFIG_DATA  "ZcId.config"    /*ZCID�����ļ�·��*/
#endif

#ifdef SYS_TYPE_WINDOWS
#define ZC_DATA_INFO       "FS\\ZC.bnf"     /*ZCID�����ļ�·��*/
#endif

#ifdef SYS_TYPE_VXWORKS
#define ZC_DATA_INFO       "ZC.bnf"     /*ZCID�����ļ�·��*/
#endif


#define EMAP_DATA_VERSION_TYPE          1U   /*���ӵ�ͼ�汾������*/
#define SYS_CONFIG_DATA_VERSION_TYPE    2U   /*ϵͳ�������ݰ汾������*/

#define TIME_DIFF_1970                  0x83AA7E80U        /*��ϵͳ��NTPʱ���ʽ�1970����1900������� = 3600s*24h*(365days*70years+17days) */
#define TIME_MAX_WAIT_REC                 2              /*�ȴ�Ӧ���ĳ�ʱʱ����ms��������Ӧ��ϵͳУʱ������Χ�ڼ���*/


/*����ϵͳ����������*/
#define ZC_RUN_CYCLE_TIME               400U  /*����ϵͳ���е�����Ϊ400ms*/

/*������������ֵ*/
#define ZC_ERROR_CODE_1    0x0001U
#define ZC_ERROR_CODE_2    0x0002U
#define ZC_ERROR_CODE_3    0x0004U
#define ZC_ERROR_CODE_4    0x0008U
#define ZC_ERROR_CODE_5    0x0010U
#define ZC_ERROR_CODE_6    0x0020U
#define ZC_ERROR_CODE_7    0x0040U
#define ZC_ERROR_CODE_8    0x0080U
#define ZC_ERROR_CODE_9    0x0100U
#define ZC_ERROR_CODE_10   0x0200U
#define ZC_ERROR_CODE_11   0x0400U
#define ZC_ERROR_CODE_12   0x0800U
#define ZC_ERROR_CODE_13   0x1000U
#define ZC_ERROR_CODE_14   0x2000U
#define ZC_ERROR_CODE_15   0x4000U
#define ZC_ERROR_CODE_16   0x8000U

/* ����Ӧ������İ汾�� */
#define ZC_APP_VERSION V.0.0.6
#endif
