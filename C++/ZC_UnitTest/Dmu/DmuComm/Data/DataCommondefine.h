/*************************************************
  文件名   ：DataCommondefine.h
  作者     ：董欣      
  创建时间 ：2016-8-11
  功能描述 ：公用信息管理头文件  
  备注    ：无。 
*************************************************/

#ifndef DATA_COMMON_DEFINE_H_
#define DATA_COMMON_DEFINE_H_

#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BnfSngSwitchInfoStruct
{
    UINT16_S switchId;                    /*道岔编号*/
    UINT16_S switchStatus;                /*道岔状态*/    
}BnfSngSwitchInfoStruct;


#ifdef __cplusplus
}
#endif

#endif
