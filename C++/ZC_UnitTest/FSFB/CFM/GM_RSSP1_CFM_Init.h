/**
* @file FSFB_lib_init.h
* @brief 初始化FSFB模块
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


#ifndef _GM_RSSP1_CFM_Init_H_
#define _GM_RSSP1_CFM_Init_H_

#include "../GM_RSSP1_Lib_Def.h"
#include "../GM_RSSP1_MQ_Interface.h"
#include "GM_RSSP1_CFM.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
    * @brief 初始化一个FSFB通信模块配置变量
    *
    * Detailed description.
    * @param[in] init_file_path
    * @param[in] pCfg
    * @return GM_BOOL
    */
#if 0
    GM_BOOL GM_RSSP1_Init_Comm_Cfg_CFM(char *init_file_path , GM_RSSP1_comm_cfg_struct *pCfg);
#endif 


    /**
    * @brief 初始化CSP的一个FSFB通信模块配置变量
    *
    * Detailed description.
    * @param[in] init_file_path
    * @param[in] pCfg
    * @return GM_BOOL
    */
	GM_BOOL GM_RSSP1_Init_Comm_Cfg_CFM_CSP(char *init_file , GM_RSSP1_comm_cfg_struct *pCfg);

    /**
    * @brief 初始化FSFB通信的全局配置
    *
    * Detailed description.
    * @param[in] pCfg
    * @param[in] pIniFileContent
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_Init_Comm_Global_CFM(GM_RSSP1_comm_cfg_struct *pCfg , GM_INT8 *pIniFileContent);

    /**
    * @brief 初始化FSFB通信每一个连接的配置
    *
    * Detailed description.
    * @param[in] pCfg
    * @param[in] pIniFileContent
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_Init_Comm_Connection_CFM(GM_RSSP1_comm_cfg_struct *pCfg , GM_INT8 *pIniFileContent);


    /**
    * @brief 初始化FSFB的安全、通信模块。
    *
    * Detailed description.
    * @param[in] file_path
    * @param[in] p_cfg
    * @param[in] pSFM
    * @param[in] pCFM
    * @return GM_BOOL
    */
#if 0
    GM_BOOL GM_RSSP1_CFM_Init(char *file_path);
#endif
    /**
    * @brief 初始化CSP下FSFB的安全、通信模块。
    *
    * Detailed description.
    * @param[in] file_path
    * @param[in] p_cfg
    * @param[in] pSFM
    * @param[in] pCFM
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_CFM_Init_CSP(char *pcfg, GM_UINT32 len);

	    /**
    * @brief  初始化CFM模块
    *
    * Detailed description.
    * @param[in] pcfg
    * @param[in] pCFM
    * @return GM_BOOL GM_RSSP1_CFM_Init_Lib
    */
	GM_BOOL GM_RSSP1_CFM_Init_Lib(GM_RSSP1_comm_cfg_struct *pcfg, GM_RSSP1_CFM_object_struct *pCFM);

    /**
    * @brief 初始化一个FSFB通信模块配置变量
    *
    * Detailed description.
    * @param[in] init_file_path
    * @param[in] pCfg
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_Init_Comm_Cfg_CFM_Addr(GM_UINT8 *pFileContent , GM_RSSP1_comm_cfg_struct *pCfg);

    /**
    * @brief 初始化FSFB通信的全局配置
    *
    * Detailed description.
    * @param[in] pCfg
    * @param[in] pIniFileContent
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_Init_Comm_Global_CFM_Addr(GM_RSSP1_comm_cfg_struct *pCfg , GM_UINT8 *pFileContent, GM_UINT8 **r_ptr);

    /**
    * @brief 初始化FSFB通信每一个连接的配置
    *
    * Detailed description.
    * @param[in] pCfg
    * @param[in] pIniFileContent
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_Init_Comm_Connection_CFM_Addr(GM_RSSP1_comm_cfg_struct *pCfg , GM_UINT8 *pFileContent,GM_UINT8 **r_ptr);


    /**
    * @brief 初始化FSFB的安全、通信模块。
    *
    * Detailed description.
    * @param[in] file_path
    * @param[in] p_cfg
    * @param[in] pSFM
    * @param[in] pCFM
    * @return GM_BOOL
    */
    GM_BOOL GM_RSSP1_CFM_Init_Addr(GM_UINT8 *addr);

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif
