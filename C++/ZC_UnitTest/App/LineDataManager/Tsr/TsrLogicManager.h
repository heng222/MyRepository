/************************************************************************
*
* 文件名   ：  TsrLogicManager.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  临时限速逻辑处理管理
* 备  注   ：  无
*
************************************************************************/
#ifndef TSR_LOGCI_MANAGER_H_
#define TSR_LOGCI_MANAGER_H_

#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*
	* 功能描述： 删除某个ZCID的临时限速信息
	* 参数说明： const UINT16 zcId, Id信息    
	* 返回值  ： 无     
	*/
	void DeleteSingleZcTsrInfo(const UINT16_S zcId);

    /*
    * 功能描述： 查询相邻ZC传来的临时限速信息是否在本ZC中
    * 参数说明： const UINT16_S startLink, 起点Link 
    *            const UINT32_S startOffset, 起点Offset
    *            const UINT16_S endLink,  终点Link
    *            const UINT32_S endOffset 终点Offset
    * 返回值  ： 无     
    */
    UINT8_S CheckMaTsrInLocalZc(const UINT16_S startLink,const UINT32_S startOffset,const UINT16_S endLink,const UINT32_S endOffset);

#ifdef __cplusplus
}
#endif

#endif
