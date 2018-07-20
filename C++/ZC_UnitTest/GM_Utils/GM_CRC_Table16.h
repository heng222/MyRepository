/**
* @file GM_CRC_Table16.h
* @brief 常用CRC查表用的表
* @author 
* @date 
* @version
* <pre><b>copyright: 

*/
#ifndef _GM_CRC_TABLE16_H
#define _GM_CRC_TABLE16_H

#include "GM_Utils_Base.h"
#include "GM_CRC_Reflect.h"

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

    /** @brief 多项式0x11021的正序CRC表 */
    extern const GM_UINT16 GM_CRC16_Table_0x11021_MSB[];

    /** @brief 多项式0x11021的逆序CRC表(0x18408) */
    extern const GM_UINT16 GM_CRC16_Table_0x11021_LSB[];

    /** @brief 多项式0x10811的正序CRC表 */
    extern const GM_UINT16 GM_CRC16_Table_0x10811_MSB[];

    /** @brief 多项式0x10811的逆序CRC表, FSFB2中会用到该CRC表 */
    extern const GM_UINT16 GM_CRC16_Table_0x10811_LSB[];

    /**
    * @brief GM_CRC_Build_CRC16_Table
    *
    * 根据多项式和顺序决定CRC表
    * @param[in] polynomial 多项式 0x1021
    * @param[out] pCRCTable CRC表
    * @param[in] isHighFirst 1为逆序 传入0x8408, 通常为正序0 传入0x1021.
    * @return GM_BOOL
    */
    GM_BOOL GM_CRC_Build_CRC16_Table(GM_UINT32 polynomial, GM_UINT16* pCRCTable, GM_BOOL isHighFirst);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_CRC_TABLE_H */

