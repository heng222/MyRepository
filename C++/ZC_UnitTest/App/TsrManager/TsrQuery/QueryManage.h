/*******************************************
文件名	：QueryMange.h
作者	：董欣
创建时间：2016-10
描述	：查询函数管理
备注	：无
*******************************************/

#ifndef QUERY_MANAGE_H_
#define QUERY_MANAGE_H_

#include "../../../Common/CommonTypes.h"
#include "../TsrAdministrator/TsrDataAdmin.h"
#include "../../../Common/CircQueueStruct.h"

#define FILE_DATA_LEN      1504u


#ifdef __cplusplus
extern "C" {
#endif 

/*******************************************
函数名	：CheckLogicIdRealteZc
功能描述：查询出逻辑区段涉及到ZC的ID
输入	：UINT16* logicIds,   逻辑区段ID
		  UINT8_S logicNum,     逻辑区段个数
          UINT8_S maxZcNum,     ZC数量
输出	：UINT8_S* pRelateZcId, 包含ZCID的数组(注：逻辑区段属于哪个ZC，就把相应ZCID写进此数组)
返回值	：1:成功，	0:失败
*******************************************/
extern UINT8_S CheckLogicIdRealteZc(UINT16_S* logicIds, UINT8_S logicNum, UINT8_S maxZcNum, UINT8_S* pRelateZcId,UINT8_S *relateZcNum);

/*******************************************
函数名	：CheckSingleTSRSpeed
功能描述：判断临时限速数值是否高于设置的临时限速涉及到的逻辑区段的线路设计最高限速值
输入	：UINT16* pLogicId   逻辑区段ID
		  UINT8_S logicNum     逻辑区段数量
		  UINT8_S speed       设定临时限速速度
输出	：无
返回值	：2    设置的临时限速数值高于某一个逻辑区段的线路设计最高限速值
		  1    设置的临时限速数值没有高于任何一个逻辑区段的线路设计最高限速值
		  0    查询失败（除以上两种情况，其它均视为查询失败）
*******************************************/
extern UINT8_S CheckSingleTSRSpeed(UINT16_S* pLogicId,UINT8_S logicNum,UINT8_S speedValue);

/*******************************************
函数名	：CheckSingleTsrLogicId
功能描述：判断临时限速区域内逻辑区段的有效性
输入	：UINT16* pLogicId   逻辑区段ID
		  UINT8_S logicNum     逻辑区段数量
输出	：无
返回值	：1: 该临时限速内同时包含了同一道岔的定位和反位；
		  2: 该临时限速内的逻辑区段不连续;
          3: 该临时限速内存在ID不合法的逻辑区段;
		  4: 其他原因失败
		  0:成功
*******************************************/
extern UINT8_S CheckSingleTsrLogicId(UINT16_S* pLogicId,UINT8_S logicNum);

#ifdef __cplusplus
}
#endif
#endif