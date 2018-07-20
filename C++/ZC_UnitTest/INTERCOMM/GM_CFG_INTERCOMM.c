/**
* @file GM_CFG_INTERCOMM.c
* @brief 内外网通信控制器接口实现文件
* @author 
* @date 2017-10-17 15:36:43
* @version
* <pre><b>copyright: </b></pre>
* <pre><b>email: </b></pre>
* <pre><b>company: </b></pre>
* <pre><b>All rights reserved.</b></pre>
* <pre><b>modification:</b></pre>
* <pre>Write modifications here.</pre>
*/
#include "GM_CFG_INTERCOMM.h"
#include "GM_CFG_INTERCOMM_Manage.h"
#include "..\cspadpt\Vcp_Service_Interface.h"
#include "..\GM_Utils\GM_Memset.h"
#include "..\GM_Utils\GM_Memcpy.h"

Cfg_Data_struct g_Rssp1_Cfg;
Cfg_App_Connection_struct g_Cfg_Intercom_App_Connection[MAX_CONNECTION_NUM];
/***********************************************************************************************
*
*
* 板通信控制器部分
*
*
***********************************************************************************************/

/**
* @brief 内网通信配置初始化
*
* Detailed description.
* @return GM_BOOL
*
*/

GM_BOOL GM_CFG_INTERCOMM_Initialize(void)
{
    GM_BOOL l_Result = GM_FALSE;
    TCP_Object_struct *pTCP = NULL;
    Cfg_App_Connection_struct *pAppConn = NULL;
    UINT8 l_Index  = 0U;
	size_t tmpCfgSize = sizeof(g_Rssp1_Cfg);
	size_t tmpConSize = sizeof(g_Cfg_Intercom_App_Connection);

    GM_memset((void *)(&g_Rssp1_Cfg), 0x00U, tmpCfgSize);        
    GM_memset((void *)(&g_Cfg_Intercom_App_Connection[0U]), 0x00U, tmpConSize);        
    pTCP = GM_CFG_INTERCOM_Get_TCPObject();
    
    if(pTCP == NULL)
    {
        
       l_Result = GM_FALSE;            
    }
    else
    {
        if(TCP_Initialize_Library_OK == GM_CFG_INTERCOM_TCP_Initialize_Library(pTCP))
        {
           l_Result = GM_TRUE;        
        }
        else
	    {
           l_Result = GM_FALSE;			
	    }		
		
		
		if(pTCP->libraryState == Library_State_Operational)
		{
		    for(l_Index = 0U; l_Index < MAX_CONNECTION_NUM; l_Index++)
		    {  
			    pAppConn = (Cfg_App_Connection_struct*)&g_Cfg_Intercom_App_Connection[l_Index];
			
			    pAppConn->index = l_Index;
			    pAppConn->App_State = App_State_Unknow;			
			    pAppConn->exchge_data = NULL;

			    if(l_Index == 0U)  /*ì?êa′|àí*/
			    {				
			        pAppConn->exchge_data  =  &g_Rssp1_Cfg;
			    }
			
		    }			
						
		}

	}
	
	return l_Result;
				
}

/**
* @brief 内网通信TCP处理 
*
* Detailed description.
* @return GM_BOOL
*
*/

void GM_CFG_INTERCOMM_TcpProcess(void)
{
    GM_BOOL l_Result = GM_FALSE;
    TCP_Object_struct *pTCP = NULL;

    
    pTCP = GM_CFG_INTERCOM_Get_TCPObject();
    
    if((pTCP != NULL) && (pTCP->libraryState == Library_State_Operational))
    {        
      GM_CFG_INTERCOMM_TCP_Socket_Maintain(pTCP);
      GM_CFG_INTERCOMM_TCP_Conn_Recv_Sock_Dat(pTCP);
      GM_CFG_INTERCOMM_TCP_Conn_Send_Sock_Dat(pTCP);
        
    }
                        
}

/**
* @brief 内网通信应用处理 
*
* Detailed description.
* @return GM_BOOL
*
*/

void GM_CFG_INTERCOMM_AppProcess(void)
{
    GM_BOOL l_Result = GM_FALSE;
    TCP_Object_struct *pTCP = NULL;

    
    pTCP = GM_CFG_INTERCOM_Get_TCPObject();
    
    if((pTCP != NULL) && (pTCP->libraryState == Library_State_Operational))
    {        
      GM_CFG_INTERCOMM_APP_Conn_Exchange_Dat();
        
    }
                        
}

/**
* @brief 内网通信数据交互 
*
* Detailed description.
* @return GM_BOOL
*
*/

void GM_CFG_INTERCOMM_APP_Conn_Exchange_Dat(void)
{
    UINT8 l_Index  = 0U;    
    TCP_Object_struct *pTCP = NULL;    
    TCP_Connection_struct *pTCP_Con = NULL;    
    Cfg_App_Connection_struct* pAppConn = NULL;    
 
    UINT32 l_Size = 0U;    
    UINT32 l_Addr = 0U;

    pTCP = GM_CFG_INTERCOM_Get_TCPObject();    


	
#ifdef CFM_Part	
	CSPADPT_Get_SpeciConfig_Addr_Size(ENUM_CONFIG_DAT_TYPE_RSSPI, (UINT8*)&l_Addr, &l_Size);	
#endif	
	
		
	for(l_Index = 0U; l_Index < MAX_CONNECTION_NUM; l_Index++)
	{  
		pAppConn = (Cfg_App_Connection_struct*)&g_Cfg_Intercom_App_Connection[l_Index];
	   pTCP_Con = (TCP_Connection_struct *)(&pTCP->connection[l_Index]);	
	   
	   	   
        if(pTCP_Con->TCP_State != Layer_State_Connected)
        {
            pAppConn->App_State = App_State_Unknow;
        }
	   
        switch(pAppConn->App_State)
		{
			
			case App_State_Unknow:
			{
				if(pTCP_Con->TCP_State == Layer_State_Connected)
				{
                    if(pTCP->is_server == GM_TRUE)
                    {
                       pAppConn->App_State = App_State_Waiting_Req;
                    }
                    else
                    {
                       pAppConn->App_State = App_State_Need_Req;
                    }
                    
				
				
				}
				else
				{
					
				}
				break;
								
			}
			case App_State_Waiting_Req:
			{
				if(pTCP->is_server == GM_TRUE)
				{
										
                    if(GM_TRUE == GM_CFG_INTERCOMM_APP_Check_Recv_Dat(pTCP_Con->rcv_buf.p_rcv_buf, (UINT32)pTCP_Con->rcv_buf.valid_dat_len,Exchg_Msg_Type_Req))
                    {
                        
                       if(GM_TRUE == GM_CFG_INTERCOMM_APP_Set_Send_Dat(pTCP_Con->send_buf.p_rcv_buf, 
                                                                       (UINT32 *)&(pTCP_Con->send_buf.valid_dat_len),
                                                                       (UINT8*)l_Addr,
                                                                       l_Size,
                                                                       Exchg_Msg_Type_Dat))
						{
					      pAppConn->App_State = App_State_Need_Ack; /*·t???÷??ê?μ????óoó￡?éè??×′ì??a???′ó|′e*/																			   
						}
						
						                    printf("222, send len=%d\n", pTCP_Con->send_buf.valid_dat_len);	
						
					}
		            pTCP_Con->rcv_buf.valid_dat_len = 0U;		

					
					
                  					 
				}
				else
				{
					
				}
				break;
								
			}			
			case App_State_Need_Req:
			{
				if(pTCP->is_server != GM_TRUE)
				{
					

                   if(GM_TRUE == GM_CFG_INTERCOMM_APP_Set_Send_Dat(pTCP_Con->send_buf.p_rcv_buf, 
                                                                   (UINT32 *)&(pTCP_Con->send_buf.valid_dat_len),
                                                                   NULL,
                                                                   0U,
                                                                   Exchg_Msg_Type_Req))
					{
					  pAppConn->App_State = App_State_Waiting_Ack; /*?í?§??·￠?í???óoó￡?éè??×′ì??aμè′yó|′e*/																			   
					}					
					
				}
				else
				{
					
				}
				break;
								
			}				
			case App_State_Waiting_Ack:
			{
				if(pTCP->is_server != GM_TRUE)
				{
					
                    if(GM_TRUE == GM_CFG_INTERCOMM_APP_Check_Recv_Dat(pTCP_Con->rcv_buf.p_rcv_buf, (UINT32)pTCP_Con->rcv_buf.valid_dat_len,Exchg_Msg_Type_Dat))
                    {
                        
                       if(GM_TRUE == GM_CFG_INTERCOMM_APP_Set_Send_Dat(pTCP_Con->send_buf.p_rcv_buf, 
                                                                       (UINT32 *)&(pTCP_Con->send_buf.valid_dat_len),
                                                                       NULL,
                                                                       0U,
                                                                       Exchg_Msg_Type_Over))
						{
					      pAppConn->App_State = App_State_Hand_OK; /*·t???÷??ê?μ????óoó￡?éè??×′ì??a???′ó|′e*/																			   
						}
						
                        if(pAppConn->exchge_data != NULL)
                        {
                           GM_memcpy((void *)(pAppConn->exchge_data->cfg), (const void *)(pTCP_Con->rcv_buf.p_rcv_buf), (size_t)(pTCP_Con->rcv_buf.valid_dat_len));    
                           pAppConn->exchge_data->length = pTCP_Con->rcv_buf.valid_dat_len;
                        }
                            
                        
                        pTCP_Con->rcv_buf.valid_dat_len = 0U;    
						
					}
					else
					{
						/*waiting*/
					}
					
										
				}
				else
				{
					
				}
				break;
								
			}				
			case App_State_Need_Ack:
			{
				if(pTCP->is_server == GM_TRUE)
				{
					
                    if(GM_TRUE == GM_CFG_INTERCOMM_APP_Check_Recv_Dat(pTCP_Con->rcv_buf.p_rcv_buf, (UINT32)pTCP_Con->rcv_buf.valid_dat_len,Exchg_Msg_Type_Over))
                    {                    
                       pAppConn->App_State = App_State_Hand_OK; /*?í?§??·￠?í???óoó￡?éè??×′ì??a??ê?3é1|*/    
                    }        
                    pTCP_Con->rcv_buf.valid_dat_len = 0U;    
					
				}
				else
				{
					
				}
				break;
								
			}	
            default:
                break;			
			
			
			
		}
		
		

	}		
	
	
}

/**
* @brief 内网通信接收数据检查 
*
* Detailed description.
* @return GM_BOOL
*
*/

GM_BOOL GM_CFG_INTERCOMM_APP_Check_Recv_Dat(UINT8* pDat, UINT32 Len, Exchg_Msg_Type_Enum Type)
{	
    #define  CFG    0x434647U    
    GM_BOOL l_Result = GM_FALSE;
    UINT8  l_Buf[256U];
    
    if((pDat == NULL) || (Len < 4U) )
        return l_Result;
    
    GM_memcpy(l_Buf, pDat, 4U);    
    if(l_Buf[0U] != (UINT8)Type)
        return l_Result;
    
    if((l_Buf[1U] != 0x43U) || (l_Buf[2U] != 0x46U) || (l_Buf[3U] != 0x47U) )
        return l_Result;
	
	if(Type == Exchg_Msg_Type_Dat)
	{
		printf("Check_Recv_Dat Type=%d, Len=%d\n", Type, Len);		
		if(Len < 8U)
           return l_Result;        

        if((*(UINT32*)(pDat + 4U) + 8U) == Len)   /*3¤?èD￡?é*/
        {
            l_Result = GM_TRUE;            
        }
		
		
	}
	else
	{
        l_Result = GM_TRUE;			
	}


	return l_Result;
	
}

/**
* @brief 内网通信数据发送组包 
*
* Detailed description.
* @return GM_BOOL
*
*/
GM_BOOL GM_CFG_INTERCOMM_APP_Set_Send_Dat(UINT8* pBuf, UINT32* pBufLen,UINT8* pDat, UINT32 DatLen, Exchg_Msg_Type_Enum Type)
{	

    GM_BOOL l_Result = GM_FALSE;
    UINT32 l_Len = 0U;
    
    if((pBuf == NULL) || (pBufLen == NULL))
        return l_Result;
	
	switch(Type)
	{
		case Exchg_Msg_Type_Req:
		case Exchg_Msg_Type_Ack:
		case Exchg_Msg_Type_Over:
		{
            *(UINT8*)(pBuf + l_Len) = Type;
            l_Len += 1U;
            *(UINT8*)(pBuf + l_Len) = 0x43U;
            l_Len += 1U;        
            *(UINT8*)(pBuf + l_Len) = 0x46U;
            l_Len += 1U;    
            *(UINT8*)(pBuf + l_Len) = 0x47U;
            l_Len += 1U;    
            *(UINT32*)pBufLen = l_Len;    

            l_Result = GM_TRUE;			
			break;
		}
		case Exchg_Msg_Type_Dat:
		{
            if((pDat == NULL) || (DatLen == 0U))
            {
               l_Result = GM_FALSE;                    
            }                
			else
			{
				
			  *(UINT8*)(pBuf + l_Len) = Type;
              l_Len += 1U;
              *(UINT8*)(pBuf + l_Len) = 0x43U;
              l_Len += 1U;        
              *(UINT8*)(pBuf + l_Len) = 0x46U;
              l_Len += 1U;    
              *(UINT8*)(pBuf + l_Len) = 0x47U;
              l_Len += 1U;    
			  *(UINT32*)(pBuf + l_Len) = DatLen;
			  l_Len += 4U;				  
        	  *(UINT32*)pBufLen = l_Len + DatLen;	
			  
			  GM_memcpy(pBuf + l_Len, pDat, DatLen);	
              l_Result = GM_TRUE;					
			}
			break;
		}
		default:
		   break;
		
	}
	printf("Set_Send_Dat Type=%d, Len=%d\n", Type, *(UINT32*)pBufLen );
	return l_Result;
	
}
	
/**
* @brief 内网通信数据判断文件传输是否完成 
*
* Detailed description.
* @return GM_BOOL
*
*/	
GM_BOOL GM_CFG_INTERCOMM_Is_Cfg_Transmitted_OK(void)
{
	
	UINT8 l_Index = 0U;
	static GM_BOOL s_Result = GM_FALSE;
	Cfg_App_Connection_struct* pAppConn = NULL;	

	
	if(s_Result == GM_FALSE)
	{
		pAppConn = (Cfg_App_Connection_struct*)&g_Cfg_Intercom_App_Connection[l_Index];
		
		if(pAppConn->App_State == App_State_Hand_OK)
		{
			s_Result = GM_TRUE;				
		}
		else
		{
		    s_Result = GM_FALSE;
		}			
		
	}
	else
	{
		/*Do Nothing*/
	}
	
	return s_Result;

}	
                       
		  


