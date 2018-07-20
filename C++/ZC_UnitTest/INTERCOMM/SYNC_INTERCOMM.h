/**
* @file GM_RSSP1_INTERCOMM.h
* @brief ϵ��ͬ���ӿ�ͷ�ļ�
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


#ifndef _SYNC_INTERCOMM_H_
#define _SYNC_INTERCOMM_H_
#include "../GM_Define.h"
#include "../FSFB/GM_RSSP1_Lib_Def.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
* @brief ϵ��ͬ�� ά������ӿ�
*
* Detailed description.
* @return GM_BOOL
*/
GM_BOOL SYNC_INTERCOMM_Matain_Proc(void);

/**
* @brief ϵ��ͬ�� ������ӿ�
*
* Detailed description.
* @return GM_BOOL
*/
GM_BOOL SYNC_INTERCOMM_Recv_Proc(void);
/**
* @brief ϵ��ͬ�� �����ʹ���ӿ�
*
* Detailed description.
* @return GM_BOOL
*/
GM_BOOL SYNC_INTERCOMM_Send_Proc(void);


/**
* @brief ϵ��ͬ�� ��ȡ���ͻ���ָ��
*
* Detailed description.
* @return GM_BOOL
*/
GM_UINT8* SYNC_INTERCOMM_Get_Sync_Output_Ptr(void);

/**
* @brief ϵ��ͬ�� ��ȡ���ջ���ָ��
*
* Detailed description.
* @return GM_BOOL
*/
GM_UINT8* SYNC_INTERCOMM_Get_Sync_Input_Ptr(void);

/**
* @brief ϵ��ͬ�� ���÷������ݳ���
*
* Detailed description.
* @return GM_BOOL
*/
void SYNC_INTERCOMM_Set_Sync_Output_Length(GM_UINT32 Len);

/**
* @brief ϵ��ͬ�� ��ȡ���ջ��������ݳ���
*
* Detailed description.
* @return GM_BOOL
*/
GM_UINT32 SYNC_INTERCOMM_Get_Sync_Input_Length(void);



#ifdef __cplusplus
}
#endif /* extern "C" */

#endif