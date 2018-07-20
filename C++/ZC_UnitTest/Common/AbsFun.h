/********************************************************
*                                                                                                            
* �� �� ���� AbsFun.h
* ��Ȩ˵����  
* ����ʱ�䣺 2013-10-25
* ��    �ߣ� 
* ���������� �����ֵ����ͷ�ļ�
* �޸ļ�¼��   
*
********************************************************/
#ifndef ABS_FUN_H_
#define ABS_FUN_H_

#include "CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

/*
*  ��������:��DouBle���͵����ݵľ���ֵ
*  ����˵����  
*  ����ֵ��    
*/
FLOAT64_S AbsFloat64Func(FLOAT64_S value);


/*
*  ��������:��Float���͵����ݵľ���ֵ
*  ����˵����  
*  ����ֵ��    
*/
FLOAT32_S AbsFloat32Func(FLOAT32_S value);

/*
*  ��������:��INI32���͵����ݵľ���ֵ
*  ����˵����  
*  ����ֵ��    
*/
INT32_S AbsInt32Func(INT32_S value);

/*
*  ��������:��INI16���͵����ݵľ���ֵ
*  ����˵����  
*  ����ֵ��    
*/
INT16_S AbsInt16Func(INT16_S value);

#ifdef __cplusplus
}
#endif

#endif
