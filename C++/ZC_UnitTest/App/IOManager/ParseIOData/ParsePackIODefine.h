/************************************************************************
*
* �ļ���   ��  ParsePackIODefine.h
* ����ʱ�� ��  2014.04.14
* ����     ��  ZC��
* �������� ��  �������������ض���  
* ��  ע	��  ��
*
************************************************************************/

#ifndef PARSE_PACK_IO_DEFINE_H_
#define PARSE_PACK_IO_DEFINE_H_

#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif
	
/*ZC��CIͨ�ŵ�����ֽ�����*/
#define ZC_CI_COM_BYTE_SUM_MAX       1000U

/*ZC�복��ATPͨ�ŵ�����ֽ�����*/
#define ZC_TRAIN_COM_BYTE_SUM_MAX    500U

/*ZC������ZCͨ�ŵ�����ֽ�����*/
#define ZC_NZC_COM_BYTE_SUM_MAX      1300U

/*ZC��ATSͨ�ŵ�����ֽ�����*/
#define ZC_ATS_COM_BYTE_SUM_MAX      1300U
#define	DEV_TOTAL_FRAME_LEN          1300U/*-bye-*/


/*ZC��NTP������ֽ�����*/
#define ZC_NTP_COM_BYTE_SUM_MAX      1000U

#ifdef __cplusplus
}
#endif
#endif
