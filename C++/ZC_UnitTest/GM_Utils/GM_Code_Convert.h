/**
* @file GM_Code_Convert.h
* @brief
* @author 
* @date 
* @version

*/
#ifndef _GM_CODE_CONVERT_H
#define _GM_CODE_CONVERT_H

#include "GM_Utils_Base.h"
#include "GM_Memcpy.h"
#include "GM_Memset.h"

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

    /**
    * @defgroup 字节与位之间的转换
    * @brief
    *
    * Detailed description.
    * @{
    */
    /**
    * @brief GM_Code_BYTE2BIT
    *
    * 字节转换为位.
    * @param[in] pIn rg.指向2个byte 0x37 0x18
    * @param[in] bits rg.共16个bit
    * @param[out] pOut rg.pOut指向16个bit位 1110(7) 1100(3) 0001(8) 1000(1) 每8个bit，从右向左读
    * @return GM_BOOL
    */
    GM_BOOL GM_Code_BYTE2BIT(const char* pIn, GM_UINT32 bits, int* pOut);

    /**
    * @brief GM_Code_BIT2BYTE
    *
    * 位转换为字节.
    * @param[in] pIn  rg.pIn指向十个bit位 1110（7） 1111（f） 1100（3） 每8个bit 从右到左读
    * @param[in] bits rg.10
    * @param[out] pOut rg.得到2个byte 分别是 0xf7 0x03
    * @return GM_BOOL
    */
    GM_BOOL GM_Code_BIT2BYTE(const int* pIn, GM_UINT32 bits, char* pOut);
    /** @} */

    /**
    * @defgroup BCD码与十进制之间的转换
    * @brief
    *
    * Detailed description.
    * @{
    */
    /**
    * @brief GM_Code_BCD2DEC
    *
    * 将BCD码转为十进制数.
    * @param[in] BCDcode [0,0X9999] 39321
    * @return int
    */
    int GM_Code_BCD2DEC(int BCDcode);

    /**
    * @brief GM_Code_DEC2BCD
    *
    * 将十进制数转为BCD码.
    * @param[in] DECcode [0,9999]
    * @return int
    */
    int GM_Code_DEC2BCD(int DECcode);

    /**
    * @brief GM_Code_HEX2INT
    *
    * 将十六机制字符串转换为十进制.
    * @param[in] pHEX "09867f" 不包含 0x
    * @param[in] len
    * @param[in] pDEC
    * @return GM_BOOL
    */
    GM_BOOL GM_Code_HEX2INT(const char* pHEX, GM_UINT8 len, int* pDEC);
    /** @} */

    /**
    * @defgroup 主机字节序与网络字节序之间的转换
    * @brief
    *
    * Detailed description.
    * @{
    */

    /**
    * @brief GM_Code_Is_Net
    *
    * 判断本机是主机字节序还是网络字节序.
    * @return GM_BOOL
    */
    GM_BOOL GM_Code_Is_Big_Endian(void);

    /**
    * @brief GM_Code_BL16
    *
    * 大小端之间的转换.
    * @param[in] x
    * @return GM_UINT16
    */
    GM_UINT16 GM_Code_Big_Little_Endian16(GM_UINT16 x);

    /**
    * @brief GM_Code_BL32
    *
    * 大小端之间的转换.
    * @param[in] x
    * @return GM_UINT32
    */
    GM_UINT32 GM_Code_Big_Little_Endian32(GM_UINT32 x);

    /**
    * @brief GM_Code_Big_Little_Endian64
    * 大小端之间的转换.
    * Detailed description.
    * @param[in] x
    * @return GM_UINT64
    */
    GM_UINT64 GM_Code_Big_Little_Endian64(GM_UINT64 x);


    /**
    * @brief GM_nByte_Endian_Transfer
    * n字节的大小端转换.
    * Detailed description.
    * @param[in] pData 转换数据
	* @param[in] byteNum	字节数 > 1
    * @return GM_BOOL
    */
	GM_BOOL GM_nByte_Endian_Transfer(GM_UINT8 * pData,GM_UINT8 byteNum);
    /** @} */

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_CODE_CONVERT_H */

