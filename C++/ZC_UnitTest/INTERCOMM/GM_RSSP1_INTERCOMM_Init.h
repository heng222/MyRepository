/**
* @file GM_RSSP1_INTERCOMM_Init.h
* @brief ������ͨ�ſ�������ʼ��ͷ�ļ�
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


#ifndef _GM_RSSP1_INTERCOMM_INIT_H_
#define _GM_RSSP1_INTERCOMM_INIT_H_

#include "GM_RSSP1_INTERCOMM_Def.h"
#include "../FSFB/GM_RSSP1_Lib_Def.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
    * @brief ͨ�ſ�����������ݽṹ��ʼ��
    *
    * Detailed description.
	* @param[in] pINTERCOMM:ͨ�ſ������ṹ��ָ��
	* @param[in] type:ͨ�ſ����������������ͣ���ο�GM_RSSP1_INTERCOMM_Type_Enum
    * @return GM_BOOL
    */
    extern GM_BOOL GM_RSSP1_INTERCOMM_Init(INTERCOM_Cfg_struct* pINTERCOMM, int type);
	/**
    * @brief ���ͨ�ſ������������Ƿ�Ϸ�
    *
    * Detailed description.
	* @param[in] type:ͨ�ſ�����������
    * @return GM_BOOL
    */
	GM_BOOL GM_RSSP1_INTERCOMM_Type_Vaild(int type);
	/**
    * @brief ͨ�ſ�����������ݽṹ��ʼ���Ƿ����
    *
    * Detailed description.
    * @return GM_BOOL
    */
	GM_BOOL GM_RSSP1_INTERCOMM_Init_Finished();
		/**
    * @brief ��ȡͨ�ſ�����������ݽṹ��ָ��
    *
    * Detailed description.
    * @return GM_BOOL
    */
	INTERCOM_Cfg_struct* GM_RSSP1_INTERCOMM_Get_Stru();
#ifdef __cplusplus
}
#endif /* extern "C" */


#endif
