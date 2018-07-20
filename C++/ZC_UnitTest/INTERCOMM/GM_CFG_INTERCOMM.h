/**
* @file GM_CFG_INTERCOMM.h
* @brief ?����a��?����D??????��?��?������???t
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
        Exchg_Msg_Type_Unknow   = 0x00U,         /**< δ֪״̬, ������*/
        Exchg_Msg_Type_Req      = 0x11U,         /**< ����֡*/        
        Exchg_Msg_Type_Ack      = 0x22U,         /**< Ӧ��֡*/
        Exchg_Msg_Type_Dat      = 0x33U,         /**< ����֡*/
        Exchg_Msg_Type_Over     = 0x44U         /**< ����֡ */        

    } Exchg_Msg_Type_Enum;    


    typedef enum
    {
        App_State_Unknow        = 0U,         /**< δ֪״̬, ������, ���뾭����ʼ�� */
        App_State_Need_Req      = 111U,         /**< ������ʼ�����״̬, �ɽ�����һ������ */        
        App_State_Waiting_Req   = 222U,         /**< ������ʼ�����״̬, �ɽ�����һ������ */
        App_State_Waiting_Ack   = 333U,         /**< �������� */
        App_State_Need_Ack    = 444U,         /**< �������� */        
        App_State_Hand_OK     = 555U/*,*/         /**< ������, ��Ϊ�ϲ��ṩ���� */

    } App_State_Enum;    
    
    
    typedef struct
    {
        GM_UINT32               length;                  /**< ���ó���*/
        GM_UINT8                cfg[MAX_CFG_FILE_LEN];             /**< �洢����*/

    } GM_PACKED Cfg_Data_struct;    

    typedef struct
    {
        GM_INT32                index;                  /**< �����±�*/
        App_State_Enum          App_State;              /**< APP״̬, ��Ӧ�ò�Ľ���״̬*/
        Cfg_Data_struct*        exchge_data;             /**< ���������������ڴ洢App_State_Hand_OK֮�󽻻����߷��͵�����*/

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