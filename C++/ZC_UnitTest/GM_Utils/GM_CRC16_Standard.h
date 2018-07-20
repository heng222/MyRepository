

#ifndef _GM_CRC16_STARDAND_H
#define _GM_CRC16_STARDAND_H

#include "GM_CRC_Reflect.h"
#include "GM_CRC_Table16.h"

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */


    /**
    * @brief
    *
    * 计算标准正向CRC16 
    * @param[in] Data 被校验的数据
    * @param[in] DataLen 被校验的数据长度(字节)
	* @param[in] Poly CRC16采用的多项式
	* @param[in] isHighFirst  正序逆序
    * @param[in] pCRCTable CRC表
    * @param[in] pCRC 返回CRC校验码   
    * @return GM_BOOL GM_CRC_Calculate_CRC16_Standard_H
	*/
    GM_BOOL GM_CRC_Calculate_CRC16_Standard_Seed(GM_UINT8* Data, GM_UINT16 DataLen, GM_UINT16 Seed, GM_UINT16 Poly, GM_BOOL isHighFirst, const GM_UINT16* pCRC16Table, GM_UINT16* pCRC);	

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif 
