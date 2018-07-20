/**
* @file GM_CFG_INTERCOMM.h
* @brief ?úíaí?í¨D??????÷?ó?úí·???t
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


#ifndef _GM_CFG_INTERCOMM_H_
#define _GM_CFG_INTERCOMM_H_
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

#define MAX_CFG_FILE_LEN   (1024U*100U)

    typedef enum
    {
        Exchg_Msg_Type_Unknow   = 0x00U,         /**< 未知状态, 不可用*/
        Exchg_Msg_Type_Req      = 0x11U,         /**< 请求帧*/        
        Exchg_Msg_Type_Ack      = 0x22U,         /**< 应答帧*/
        Exchg_Msg_Type_Dat      = 0x33U,         /**< 数据帧*/
        Exchg_Msg_Type_Over     = 0x44U         /**< 结束帧 */        

    } Exchg_Msg_Type_Enum;    


    typedef enum
    {
        App_State_Unknow        = 0U,         /**< 未知状态, 不可用, 必须经过初始化 */
        App_State_Need_Req      = 111U,         /**< 经过初始化后的状态, 可进行下一步操作 */        
        App_State_Waiting_Req   = 222U,         /**< 经过初始化后的状态, 可进行下一步操作 */
        App_State_Waiting_Ack   = 333U,         /**< 正在连接 */
        App_State_Need_Ack    = 444U,         /**< 正在连接 */        
        App_State_Hand_OK     = 555U/*,*/         /**< 已连接, 可为上层提供服务 */

    } App_State_Enum;    
    
    
    typedef struct
    {
        GM_UINT32               length;                  /**< 配置长度*/
        GM_UINT8                cfg[MAX_CFG_FILE_LEN];             /**< 存储配置*/

    } GM_PACKED Cfg_Data_struct;    

    typedef struct
    {
        GM_INT32                index;                  /**< 连接下标*/
        App_State_Enum          App_State;              /**< APP状态, 即应用层的交互状态*/
        Cfg_Data_struct*        exchge_data;             /**< 交换缓冲区，用于存储App_State_Hand_OK之后交换或者发送的数据*/

    } GM_PACKED Cfg_App_Connection_struct;
	
	
	
extern GM_BOOL GM_CFG_INTERCOMM_Initialize();	
extern void GM_CFG_INTERCOMM_TcpProcess();
extern void GM_CFG_INTERCOMM_AppProcess();	
extern GM_BOOL GM_CFG_INTERCOMM_Is_Cfg_Transmitted_OK(void);
void GM_CFG_INTERCOMM_APP_Conn_Exchange_Dat();
GM_BOOL GM_CFG_INTERCOMM_APP_Check_Recv_Dat(UINT8* pDat, UINT32 Len, Exchg_Msg_Type_Enum Type);
GM_BOOL GM_CFG_INTERCOMM_APP_Set_Send_Dat(UINT8* pBuf, UINT32* pBufLen,UINT8* pDat, UINT32 DatLen, Exchg_Msg_Type_Enum Type);	


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif