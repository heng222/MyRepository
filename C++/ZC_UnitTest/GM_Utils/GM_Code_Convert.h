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
    * @defgroup �ֽ���λ֮���ת��
    * @brief
    *
    * Detailed description.
    * @{
    */
    /**
    * @brief GM_Code_BYTE2BIT
    *
    * �ֽ�ת��Ϊλ.
    * @param[in] pIn rg.ָ��2��byte 0x37 0x18
    * @param[in] bits rg.��16��bit
    * @param[out] pOut rg.pOutָ��16��bitλ 1110(7) 1100(3) 0001(8) 1000(1) ÿ8��bit�����������
    * @return GM_BOOL
    */
    GM_BOOL GM_Code_BYTE2BIT(const char* pIn, GM_UINT32 bits, int* pOut);

    /**
    * @brief GM_Code_BIT2BYTE
    *
    * λת��Ϊ�ֽ�.
    * @param[in] pIn  rg.pInָ��ʮ��bitλ 1110��7�� 1111��f�� 1100��3�� ÿ8��bit ���ҵ����
    * @param[in] bits rg.10
    * @param[out] pOut rg.�õ�2��byte �ֱ��� 0xf7 0x03
    * @return GM_BOOL
    */
    GM_BOOL GM_Code_BIT2BYTE(const int* pIn, GM_UINT32 bits, char* pOut);
    /** @} */

    /**
    * @defgroup BCD����ʮ����֮���ת��
    * @brief
    *
    * Detailed description.
    * @{
    */
    /**
    * @brief GM_Code_BCD2DEC
    *
    * ��BCD��תΪʮ������.
    * @param[in] BCDcode [0,0X9999] 39321
    * @return int
    */
    int GM_Code_BCD2DEC(int BCDcode);

    /**
    * @brief GM_Code_DEC2BCD
    *
    * ��ʮ������תΪBCD��.
    * @param[in] DECcode [0,9999]
    * @return int
    */
    int GM_Code_DEC2BCD(int DECcode);

    /**
    * @brief GM_Code_HEX2INT
    *
    * ��ʮ�������ַ���ת��Ϊʮ����.
    * @param[in] pHEX "09867f" ������ 0x
    * @param[in] len
    * @param[in] pDEC
    * @return GM_BOOL
    */
    GM_BOOL GM_Code_HEX2INT(const char* pHEX, GM_UINT8 len, int* pDEC);
    /** @} */

    /**
    * @defgroup �����ֽ����������ֽ���֮���ת��
    * @brief
    *
    * Detailed description.
    * @{
    */

    /**
    * @brief GM_Code_Is_Net
    *
    * �жϱ����������ֽ����������ֽ���.
    * @return GM_BOOL
    */
    GM_BOOL GM_Code_Is_Big_Endian(void);

    /**
    * @brief GM_Code_BL16
    *
    * ��С��֮���ת��.
    * @param[in] x
    * @return GM_UINT16
    */
    GM_UINT16 GM_Code_Big_Little_Endian16(GM_UINT16 x);

    /**
    * @brief GM_Code_BL32
    *
    * ��С��֮���ת��.
    * @param[in] x
    * @return GM_UINT32
    */
    GM_UINT32 GM_Code_Big_Little_Endian32(GM_UINT32 x);

    /**
    * @brief GM_Code_Big_Little_Endian64
    * ��С��֮���ת��.
    * Detailed description.
    * @param[in] x
    * @return GM_UINT64
    */
    GM_UINT64 GM_Code_Big_Little_Endian64(GM_UINT64 x);


    /**
    * @brief GM_nByte_Endian_Transfer
    * n�ֽڵĴ�С��ת��.
    * Detailed description.
    * @param[in] pData ת������
	* @param[in] byteNum	�ֽ��� > 1
    * @return GM_BOOL
    */
	GM_BOOL GM_nByte_Endian_Transfer(GM_UINT8 * pData,GM_UINT8 byteNum);
    /** @} */

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_CODE_CONVERT_H */

