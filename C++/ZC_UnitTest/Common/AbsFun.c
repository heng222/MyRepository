/********************************************************
*                                                                                                            
* �� �� ���� AbsFun.c
* ��Ȩ˵����  
* ����ʱ�䣺 2013-10-25
* ��    �ߣ� ������
* ���������� �����ֵ���� 
* �޸ļ�¼��   
*
********************************************************/
#include "AbsFun.h"
#include "stdlib.h"
#include "math.h"

/*
*  ��������:��DouBle���͵����ݵľ���ֵ
*  ����˵����  
*  ����ֵ��    
*/
FLOAT64_S AbsFloat64Func(FLOAT64_S value)
{
    FLOAT64_S retVal = 0;/*��������ֵ*/
    retVal = fabs(value);

    return retVal;
}


/*
*  ��������:��Float���͵����ݵľ���ֵ
*  ����˵����  
*  ����ֵ��    
*/
FLOAT32_S AbsFloat32Func(FLOAT32_S value)
{
    FLOAT32_S retVal = (FLOAT32_S)0;/*��������ֵ*/
    retVal = (FLOAT32_S)fabs((FLOAT64_S)value);

    return retVal;
}

/*
*  ��������:��INI32���͵����ݵľ���ֵ
*  ����˵����  
*  ����ֵ��    
*/
INT32_S AbsInt32Func(INT32_S value)
{
    INT32_S retVal = 0;/*��������ֵ*/
    retVal = abs(value);

    return retVal;
}

/*
*  ��������:��INI16���͵����ݵľ���ֵ
*  ����˵����  
*  ����ֵ��    
*/
INT16_S AbsInt16Func(INT16_S value)
{
    INT16_S retVal = 0;/*��������ֵ*/
    retVal = abs(value);

    return retVal;
}
