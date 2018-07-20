/**
* @file GM_RSSP1_Msg_Queue.h
* @brief FSFBʹ�õ������Ϣ���ж���
* @author JiangHongjun
* @date 2010-2-7 16:23:57
* @version
* <pre><b>copyright: CASCO</b></pre>
* <pre><b>email: </b>jianghongjun@casco.com.cn</pre>
* <pre><b>company: </b>http://www.casco.com.cn</pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/


#ifndef _GM_RSSP1_MSG_QUEUE_H_
#define _GM_RSSP1_MSG_QUEUE_H_

#include "GM_RSSP1_Lib_Def.h"

#ifdef __cplusplus
extern "C"
{
#endif

	#define GM_MAX_QUEUE_ELE_LEN    GM_RSSP1_MAX_USER_DAT_LEN+20    /*����Ԫ�ص�����ֽ���*/

    /**
    * @brief RSSP1����Ԫ�ص�����
    *
    * ���в���������Ҫ��������, �����Ǻ��ֶ���.
    */
    typedef enum
    {
        FSFB_Q_TYPE_SFM_U2L_PRI     = 0x10,  /**< SFM Ӧ�ò��������ԭ����� */
        FSFB_Q_TYPE_SFM_L2U_PRI     = 0x12,  /**< SFM ��Ӧ�ò㱨������״̬���¼�����     */

        FSFB_Q_TYPE_CFM_U2L_PRI     = 0x20,  /**< CFM ���԰�ȫ���ԭ�����       */
        FSFB_Q_TYPE_CFM_L2U_PRI     = 0x22,  /**< CFM ��ȫ�㱨��ԭ�����     */

        FSFB_Q_TYPE_SENT_PKT    = 0x30,  /**< ͨ��ͨ�������͵����ݰ����� */
        FSFB_Q_TYPE_RCVD_PKT    = 0x32,  /**< ͨ��ͨ�����յ������ݰ����� */

        FSFB_Q_TYPE_UNKNOWN         = 0xff
    }GM_RSSP1_Msg_Queue_TYPE_Enum;

    typedef struct
    {
        GM_RSSP1_Msg_Queue_TYPE_Enum    type;           /**< ���е����� */

        GM_UINT32                      head_Position;  /**< ͷָ�� */
        GM_UINT32                      tail_Position;  /**< βָ�� */
        GM_UINT32                      count;          /**< ��ǰ���������е�Ԫ�ظ��� */

        GM_UINT32                      Q_size;         /**< ���������� */
        GM_UINT32                      Q_offset;       /**< ����ͷ��ַƫ���� */
    } GM_PACKED GM_RSSP1_Msg_Queue_struct;

    /**
    * @brief FSFB-2����״̬
    *
    * ��Ҫ����FSFB_Msg_Queue_Writeʱ, ����״̬, ��ʾ��������.
    */
    typedef enum
    {
        Q_WRITE_OK_NOT_FULL     = 0x11, /**< ����δ�� */
        Q_WRITE_OK_FULL         = 0x22, /**< �������� */
        Q_WRITE_FAIL            = 0xff  /**< д����ʧ�� */
    } GM_RSSP1_Write_Q_Return_Enum;

    /**
    * @brief ���г�ʼ��
    *
    * Detailed description.
    * @param[in] pQueuestruct
    * @param[in] Q_size
    * @param[in] Q_offset
    * @param[in] type
    * @return GM_BOOL
    */
    GM_BOOL FSFB_Msg_Queue_Init(GM_RSSP1_Msg_Queue_struct *pQueuestruct , GM_UINT32 Q_size , GM_UINT32 Q_offset , GM_RSSP1_Msg_Queue_TYPE_Enum type);

    /**
    * @brief �������.
    *
    * (ǰ��:�ѳ�ʼ��).
    * @param[in] pQueuestruct
    * @return GM_BOOL
    */
    GM_BOOL FSFB_Msg_Queue_Clear(GM_RSSP1_Msg_Queue_struct *pQueuestruct);

    /**
    * @brief FSFB_Is_Msg_Queue_Empty
    *
    * �ж϶����Ƿ�Ϊ��.
    * @param[in] pQueuestruct ���нṹ��ָ��
    * @return GM_BOOL
    */
    GM_BOOL FSFB_Is_Msg_Queue_Empty(GM_RSSP1_Msg_Queue_struct *pQueuestruct);

    /**
    * @brief FSFB_Is_Msg_Queue_Full
    *
    * �ж϶����Ƿ�����.
    * @param[in] pQueuestruct ���нṹ��ָ��
    * @return GM_BOOL
    */
    GM_BOOL FSFB_Is_Msg_Queue_Full(GM_RSSP1_Msg_Queue_struct *pQueuestruct);

    /**
    * @brief FSFB_Is_Msg_Queue_Full
    *
    * ��ö�����Ԫ�ظ���.
    * @param[in] pQueuestruct
    * @return GM_INT32
    */
    GM_INT32 FSFB_Get_Queue_Count(GM_RSSP1_Msg_Queue_struct *pQueuestruct);

    /**
    * @brief FSFB_Msg_Queue_Get
    *  ������
    * �Ӷ���ͷ����ȡһ��Ԫ��.���г���-1.
    * @param[in] pQueuestruct ���нṹ��ָ��
    * @param[in] pQElement ������ͷ���ص���������
    * @return GM_BOOL  �ɹ�����GM_TRUE;��������ѿ�, �򷵻�FALSEA
    */
    GM_BOOL FSFB_Msg_Queue_Get(GM_RSSP1_Msg_Queue_struct *pQueuestruct, void *pQElement);

    /**
    * @brief FSFB_Msg_Queue_Write
    * �����
    * �����β����һ��Ԫ��.
    * @note �����������, ���ȵ�����ͷԪ��, �ٴ���������.
    * @param[in/out] pQueuestruct ���нṹ��ָ��
    * @param[in] pQElement ����������ָ���Ԫ�ش��뵽������
    * @return FSFB_Write_Queue_Return_Enum  MQ_STATUS_FULL: ��������, MQ_STATUS_NOT_FULL:����δ��
    */
    GM_RSSP1_Write_Q_Return_Enum FSFB_Msg_Queue_Write(GM_RSSP1_Msg_Queue_struct *pQueuestruct, void *pQElement);

    /**
    * @brief FSFB_Msg_Queue_Pop
    * ������ͷԪ��
    *
    * ɾ����ͷ��Ԫ��, ���г���-1.
    * @param[in/out] pQueuestruct ���нṹ��ָ��
    * @return GM_BOOL  �ɹ�����GM_TRUE;�����ѿ�, ����FALSEA
    */
    GM_BOOL FSFB_Msg_Queue_Pop(GM_RSSP1_Msg_Queue_struct  *pQueuestruct);

#ifdef __cplusplus
}
#endif


#endif
