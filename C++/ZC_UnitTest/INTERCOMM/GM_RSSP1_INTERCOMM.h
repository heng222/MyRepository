/**
* @file GM_RSSP1_INTERCOMM.h
* @brief ������ͨ�ſ������ӿ�ͷ�ļ�
* @author 
* @date 2017-10-17 15:31:27
* @version
* <pre><b>copyright: </b></pre>
* <pre><b>email: </b></pre>
* <pre><b>company: </b></pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/


#ifndef _GM_RSSP1_INTERCOMM_H_
#define _GM_RSSP1_INTERCOMM_H_
#include "../GM_Define.h"
#include "../FSFB/GM_RSSP1_Lib_Def.h"

#ifdef LINK_Part
#include "../FSFB/UDP/FSFB_UDP_Init.h"
#endif

#ifdef CFM_Part
#include "../FSFB/CFM/GM_RSSP1_CFM.h"
#endif
#ifdef __cplusplus
extern "C"
{
#endif

#ifdef LINK_Part
	/**
    * @brief IO��ͨ�ſ���������CPU��ͨ������
    *
    * Detailed description.
    * @return GM_BOOL
    */
	GM_BOOL GM_RSSP1_INTERCOMM_IOB_From_CPUB(FSFB_LNK_connection_struct *pLNK_con, FSFB_LNK_object_struct *pLNK);
	/**
    * @brief IO��ͨ�ſ�������CPU�巢��ͨ������
    *
    * Detailed description.
    * @return GM_BOOL
    */
	GM_BOOL GM_RSSP1_INTERCOMM_IOB_To_CPUB(FSFB_LNK_connection_struct *pLNK_con, FSFB_LNK_object_struct *pLNK);
#endif

#ifdef  CFM_Part
	/**
    * @brief CPU��ͨ�ſ���������IO��ͨ������
    *
    * Detailed description.
    * @return GM_BOOL
    */
	GM_BOOL GM_RSSP1_INTERCOMM_CPUB_From_IOB();
	/**
    * @brief CPU��ͨ�ſ�������IO�巢��ͨ������
    *
    * Detailed description.
    * @return GM_BOOL
    */
	GM_BOOL GM_RSSP1_INTERCOMM_CPUB_To_IOB(GM_RSSP1_CFM_object_struct* pCFM);
#endif

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif