/**
* @file FSFB_lib_init.h
* @brief ��ʼ��FSFBģ��
* @author JiangHongjun
* @date 2010-2-7 16:23:35
* @version
* <pre><b>copyright: CASCO</b></pre>
* <pre><b>email: </b>jianghongjun@casco.com.cn</pre>
* <pre><b>company: </b>http://www.casco.com.cn</pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/


#ifndef _GM_RSSP1_SFM_INIT_H_
#define _GM_RSSP1_SFM_INIT_H_

#include "GM_RSSP1_SFM.h"
#include "../GM_RSSP1_Lib_Def.h"
#include "../GM_RSSP1_MQ_Interface.h"
#ifdef __cplusplus
extern "C"
{
#endif

    /**
    * @brief ��ʼ��һ��FSFBͨ��ģ�����ñ���
    *
    * Detailed description.
    * @param[in] init_file_path
    * @param[in] pCfg
    * @return GM_BOOL
    */
#if 0
    GM_BOOL GM_RSSP1_Init_Comm_Cfg_SFM(char *init_file_path , GM_RSSP1_comm_cfg_struct *pCfg);
#endif
    /**
    * @brief ��ʼ��CSPƽ̨һ��FSFBͨ��ģ�����ñ���
    *
    * Detailed description.
    * @param[in] init_file_path
    * @param[in] pCfg
    * @return GM_BOOL
    */
	GM_BOOL GM_RSSP1_Init_Comm_Cfg_SFM_CSP(char *init_file, GM_RSSP1_comm_cfg_struct *pCfg);


    /**
    * @brief ��ʼ��FSFBͨ�ŵ�ȫ������
    *
    * Detailed description.
    * @param[in] pCfg
    * @param[in] pIniFileContent
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_Init_Comm_Global_SFM(GM_RSSP1_comm_cfg_struct *pCfg , GM_INT8 *pIniFileContent);

    /**
    * @brief ��ʼ��FSFBͨ��ÿһ�����ӵ�����
    *
    * Detailed description.
    * @param[in] pCfg
    * @param[in] pIniFileContent
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_Init_Comm_Connection_SFM(GM_RSSP1_comm_cfg_struct *pCfg , GM_INT8 *pIniFileContent);

	/**
    * @brief  ��ʼ��SFMģ��
    *
    * Detailed description.
    * @param[in] pcfg
    * @param[in] pSFM
    * @return GM_BOOL GM_RSSP1_SFM_Init_Lib
    */
    GM_BOOL GM_RSSP1_SFM_Init_Lib(GM_RSSP1_comm_cfg_struct *pcfg, GM_RSSP1_SFM_object_struct *pSFM);

#if 0
	GM_BOOL GM_RSSP1_SFM_Init(char *file_path);
#endif
    GM_BOOL GM_RSSP1_SFM_Init_CSP(char* pcfg, GM_UINT32 len);

	GM_BOOL GM_RSSP1_SFM_Init_Addr(GM_UINT8 *addr);

	    /**
    * @brief ��ʼ��һ��FSFBͨ��ģ�����ñ���
    *
    * Detailed description.
    * @param[in] init_file_path
    * @param[in] pCfg
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_Init_Comm_Cfg_SFM_Addr(GM_UINT8 *pFileContent , GM_RSSP1_comm_cfg_struct *pCfg);

    /**
    * @brief ��ʼ��FSFBͨ�ŵ�ȫ������
    *
    * Detailed description.
    * @param[in] pCfg
    * @param[in] pIniFileContent
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_Init_Comm_Global_SFM_Addr(GM_RSSP1_comm_cfg_struct *pCfg , GM_UINT8 *pFileContent, GM_UINT8 **r_ptr);

    /**
    * @brief ��ʼ��FSFBͨ��ÿһ�����ӵ�����
    *
    * Detailed description.
    * @param[in] pCfg
    * @param[in] pIniFileContent
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_Init_Comm_Connection_SFM_Addr(GM_RSSP1_comm_cfg_struct *pCfg , GM_UINT8 *pFileContent, GM_UINT8 **r_ptr);

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif
