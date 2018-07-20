/********************************************************
* 
* �� �� ���� LoadCommFailTime.h 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� CommFailTime����ͷ�ļ� 
* ��    ע�� �� 
* 
********************************************************/ 

#ifndef LOAD_COMMFAILTIME_H_
#define LOAD_COMMFAILTIME_H_


#include "../../../Common/CommonTypes.h"
#include "../Data/CommFailTimeData.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* ���������� ����CommFailTime����
* ����˵���� void
* ����ֵ  �� void
*/
INT8_S LoadCommFailTimeData(void);

#ifdef __cplusplus
}
#endif
#endif
