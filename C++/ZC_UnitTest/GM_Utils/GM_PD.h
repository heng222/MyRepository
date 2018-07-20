/**
* @file GM_PD.h
* @brief ͨ�����ʵ��PD���㣬��Ҫ��������У����.
* ���԰������PD���㿴���Ǽ���CRC,����һ������ִ��PD����֮������һ��32λ��ֵ.
* @author 
* @date 
* @version

*/
#ifndef _GM_PD_H
#define _GM_PD_H

#include "GM_PD_Table.h"

#ifdef __cplusplus
extern "C"
{
#endif

 
    /**
    * @brief GM_PD_Operation
    *
    * ��׼PD����.
    * ע��: ������жϵ��øú���,��ô��Ҫ����һ���ú����ĸ���,��Ϊ�мĴ�������
    * @param[in] isAlgorithmA ��ͨ��1����ͨ��2
    * @param[in] VSN1 VSN1
    * @param[in] VSN2 VSN2
    * @param[in] pPDPara Ҫ����PD���������
    * @param[in] paraNum �����С
    * @param[out] pResult PD������
    * @return GM_BOOL PD�����Ƿ�ɹ�
    */
    GM_BOOL GM_PD_Operation(GM_BOOL isAlgorithmA, GM_UINT32 VSN1, GM_UINT32 VSN2, GM_UINT32 *pPDPara, GM_UINT32 paraNum, GM_UINT32* pResult);

	/**
    * @brief GM_PD_Operation2
    *
    * ׷����PD����.
    * ע��: ������жϵ��øú���,��ô��Ҫ����һ���ú����ĸ���,��Ϊ�мĴ�������
    * @param[in] isAlgorithmA ��ͨ��1����ͨ��2
    * @param[in] VSN1 VSN1
    * @param[in] VSN2 VSN2
    * @param[in] pPDPara Ҫ����PD���������
    * @param[in] paraNum �����С
    * @param[out] pResult PD������
    * @return GM_BOOL PD�����Ƿ�ɹ�
    */
    GM_BOOL GM_PD_Operation2(GM_BOOL isAlgorithmA, GM_UINT32 VSN1, GM_UINT32 VSN2, GM_UINT32 *pPDPara, GM_UINT32 paraNum, GM_UINT32* pResult);

    /**
    * @brief GM_PD_Inverse
    *
    * �������PD������.
    * ע��: ������жϵ��øú���,��ô��Ҫ����һ���ú����ĸ���,��Ϊ�мĴ�������
    * @param[in] ��ͨ��1����ͨ��2
    * @param[in] VSN1 VSN1
    * @param[in] VSN2 VSN2
    * @param[in] pPDPara
    * @param[in] paraNum
    * @param[out] pResult
    * @return GM_BOOL
    */
    GM_BOOL GM_PD_Inverse(GM_BOOL isAlgorithmA, GM_UINT32 VSN1, GM_UINT32 VSN2, GM_UINT32 *pPDPara, GM_UINT32 paraNum, GM_UINT32* pResult);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_PD_H */

