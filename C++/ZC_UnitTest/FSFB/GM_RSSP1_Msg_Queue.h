/**
* @file GM_RSSP1_Msg_Queue.h
* @brief FSFB使用的相关消息队列定义
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

	#define GM_MAX_QUEUE_ELE_LEN    GM_RSSP1_MAX_USER_DAT_LEN+20    /*队列元素的最大字节数*/

    /**
    * @brief RSSP1队列元素的类型
    *
    * 队列操作函数需要根据类型, 区别是何种队列.
    */
    typedef enum
    {
        FSFB_Q_TYPE_SFM_U2L_PRI     = 0x10,  /**< SFM 应用层服务请求原语队列 */
        FSFB_Q_TYPE_SFM_L2U_PRI     = 0x12,  /**< SFM 向应用层报告连接状态、事件队列     */

        FSFB_Q_TYPE_CFM_U2L_PRI     = 0x20,  /**< CFM 来自安全层的原语队列       */
        FSFB_Q_TYPE_CFM_L2U_PRI     = 0x22,  /**< CFM 向安全层报告原语队列     */

        FSFB_Q_TYPE_SENT_PKT    = 0x30,  /**< 通信通道待发送的数据包队列 */
        FSFB_Q_TYPE_RCVD_PKT    = 0x32,  /**< 通信通道接收到的数据包队列 */

        FSFB_Q_TYPE_UNKNOWN         = 0xff
    }GM_RSSP1_Msg_Queue_TYPE_Enum;

    typedef struct
    {
        GM_RSSP1_Msg_Queue_TYPE_Enum    type;           /**< 队列的类型 */

        GM_UINT32                      head_Position;  /**< 头指针 */
        GM_UINT32                      tail_Position;  /**< 尾指针 */
        GM_UINT32                      count;          /**< 当前队列中已有的元素个数 */

        GM_UINT32                      Q_size;         /**< 队列总容量 */
        GM_UINT32                      Q_offset;       /**< 队列头地址偏移量 */
    } GM_PACKED GM_RSSP1_Msg_Queue_struct;

    /**
    * @brief FSFB-2队列状态
    *
    * 主要用于FSFB_Msg_Queue_Write时, 返回状态, 提示队列已满.
    */
    typedef enum
    {
        Q_WRITE_OK_NOT_FULL     = 0x11, /**< 队列未满 */
        Q_WRITE_OK_FULL         = 0x22, /**< 队列已满 */
        Q_WRITE_FAIL            = 0xff  /**< 写队列失败 */
    } GM_RSSP1_Write_Q_Return_Enum;

    /**
    * @brief 队列初始化
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
    * @brief 队列清空.
    *
    * (前提:已初始化).
    * @param[in] pQueuestruct
    * @return GM_BOOL
    */
    GM_BOOL FSFB_Msg_Queue_Clear(GM_RSSP1_Msg_Queue_struct *pQueuestruct);

    /**
    * @brief FSFB_Is_Msg_Queue_Empty
    *
    * 判断队列是否为空.
    * @param[in] pQueuestruct 队列结构体指针
    * @return GM_BOOL
    */
    GM_BOOL FSFB_Is_Msg_Queue_Empty(GM_RSSP1_Msg_Queue_struct *pQueuestruct);

    /**
    * @brief FSFB_Is_Msg_Queue_Full
    *
    * 判断队列是否已满.
    * @param[in] pQueuestruct 队列结构体指针
    * @return GM_BOOL
    */
    GM_BOOL FSFB_Is_Msg_Queue_Full(GM_RSSP1_Msg_Queue_struct *pQueuestruct);

    /**
    * @brief FSFB_Is_Msg_Queue_Full
    *
    * 获得队列中元素个数.
    * @param[in] pQueuestruct
    * @return GM_INT32
    */
    GM_INT32 FSFB_Get_Queue_Count(GM_RSSP1_Msg_Queue_struct *pQueuestruct);

    /**
    * @brief FSFB_Msg_Queue_Get
    *  出队列
    * 从队列头部获取一个元素.队列长度-1.
    * @param[in] pQueuestruct 队列结构体指针
    * @param[in] pQElement 将队列头返回到本参数中
    * @return GM_BOOL  成功返回GM_TRUE;如果队列已空, 则返回FALSEA
    */
    GM_BOOL FSFB_Msg_Queue_Get(GM_RSSP1_Msg_Queue_struct *pQueuestruct, void *pQElement);

    /**
    * @brief FSFB_Msg_Queue_Write
    * 入队列
    * 向队列尾存入一个元素.
    * @note 如果队列已满, 将先弹出队头元素, 再存入新数据.
    * @param[in/out] pQueuestruct 队列结构体指针
    * @param[in] pQElement 将本参数所指向的元素存入到队列中
    * @return FSFB_Write_Queue_Return_Enum  MQ_STATUS_FULL: 队列已满, MQ_STATUS_NOT_FULL:队列未满
    */
    GM_RSSP1_Write_Q_Return_Enum FSFB_Msg_Queue_Write(GM_RSSP1_Msg_Queue_struct *pQueuestruct, void *pQElement);

    /**
    * @brief FSFB_Msg_Queue_Pop
    * 弹出队头元素
    *
    * 删除队头的元素, 队列长度-1.
    * @param[in/out] pQueuestruct 队列结构体指针
    * @return GM_BOOL  成功返回GM_TRUE;队列已空, 返回FALSEA
    */
    GM_BOOL FSFB_Msg_Queue_Pop(GM_RSSP1_Msg_Queue_struct  *pQueuestruct);

#ifdef __cplusplus
}
#endif


#endif
