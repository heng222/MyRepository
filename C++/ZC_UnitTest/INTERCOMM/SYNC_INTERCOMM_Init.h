/**
* @file SYNC_INTERCOMM_Init.h
* @brief ˫ϵͬ����ʼ��ͷ�ļ�
* @author 
* @date 2017-10-17 14:56:35
* @version
* <pre><b>copyright: </b></pre>
* <pre><b>email: </b></pre>
* <pre><b>company: </b></pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/


#ifndef _SYNC_INTERCOMM_INIT_H_
#define _SYNC_INTERCOMM_INIT_H_

#include "SYNC_INTERCOMM_Def.h"
#include "../FSFB/GM_RSSP1_Lib_Def.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
    * @brief SYNC������ݽṹ��ʼ��
    *
    * Detailed description.
	* @param[in] pCfg:SYNC�ṹ��ָ��
	* @param[in] type:ͨ�ſ����������������ͣ���ο�GM_RSSP1_INTERCOMM_Type_Enum
    * @return GM_BOOL
    */
    extern GM_BOOL SYNC_INTERCOMM_Init(void);

	/**
    * @brief SYNC������ݽṹ��ʼ���Ƿ����
    *
    * Detailed description.
    * @return GM_BOOL
    */
	GM_BOOL SYNC_INTERCOMM_Init_Finished();
	void SYNC_INTERCOMM_Csp_Safety_Layer_Statistics(void);

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif
