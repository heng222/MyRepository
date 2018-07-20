
/********************************************************
*                                                                                                            
* �� �� ���� Vcp_Service_Interface.c   
* ��    �ߣ� ������
* ����ʱ�䣺 2018-05-11
* ���������� CSPƽ̨����㺯�� 
* ��    ע�� �� 
*
********************************************************/  


#include <stddef.h>
#include "Vcp_Service_Interface.h"

#include "../App/InitManager/InitManager.h"
#include "../App/SysDataManager/SysConfigData.h"
#include "../App/SysDataManager/SysDefine.h"
#include "../PlatformAdapter/AppItf/AdptAppExtDevDataInterface.h"
#include "../PlatformAdapter/AppItf/AdptAppCommonDef.h"
#include "../PlatformAdapter/AppItf/AdptAppServiceInterface.h"
#include "../Common/CommonTypes.h"
#include "../App/MainManager/MainLogicManager.h"
#include "datanZC1.h"
static UINT8  g_LocalMachineId;  /*��ϵ��ϵ��,1ϵ2ϵ*/
static UINT32 g_CycleNum;        /*�����ں�*/
static UINT8  g_LocalDeviceId;   /*��ZC�ĳ�վ���*/
static UINT8  g_ExternCommProtocalType = (UINT8) ENUM_EXT_ETH_COMM_TYPE_RSSP1;
extern RSSP1_MQ_LINK_struct g_Link_MQ[GM_RSSP1_MAX_SAFETY_CONNECTION_NUM];
QueueStruct gCbtcRcvDataQue;         /*CBTC��APP���ݶ��� */
QueueStruct gCbtcSndDataQue;         /*APP��CBTC���ݶ��� */
QueueStruct AppLogDataQue;
GM_BOOL  CSP_Init_Result;						 /*����ƽ̨��ʼ�����*/
GM_BOOL  g_FsioErrorState;
UINT8 g_OppoMachineState;

CommunicationDevStatusStruct ComDevStatusInfo[COM_DEV_TYPE_SUM];  /* ��������ͨ��״̬�ṹ��*/


/*********************************�ڲ��������� BEGIN****************************************/



UINT8  CSPADPT_Get_DeviceType_By_DeviceId(UINT32 DevId);

GM_BOOL  CSPADPT_App_Set_DevId(void);

GM_VLE_ABAS_Type_enum CSPADPT_Get_Machine_ABAS(void);

void CSPADPT_Set_OppoMachine_State(UINT8 state);

UINT8 CSPADPT_Get_DeviceType_By_DeviceId(UINT32 DevId);

void  CSPADPT_Raw_Send_Message();

void  CSPADPT_Rssp1_Send_Manage(void);

void CSPADPT_Raw_Send_Interface(GM_UINT16 m_Dest, UINT8*  m_Msg_Ptr, UINT32 m_Msg_Length);

void CSPADPT_Rssp1_Send_Interface(GM_UINT16 m_Dest, UINT8*  m_Msg_Ptr, UINT32 m_Msg_Length);

void CSPADPT_Rssp2_Send_Interface(GM_UINT16 m_Dest, UINT8*  m_Msg_Ptr, UINT32 m_Msg_Length);

void CSPADPT_Raw_Receive_Message();

void CSPADPT_Rssp1_Receive_Message();

void CSPADPT_Rssp2_Receive_Message();

void CSPADPT_RSSP1_Comm_Message_Process(UINT8* m_Msg_Ptr, UINT32 m_Length);

GM_BOOL CSPADPT_Process_RTD_ErrCode(void);

UINT32 CSPADPT_Change_Bit_To_Byte(UINT8 *m_Data_Ptr, UINT16 m_Bgn_Index, UINT8 m_Data_Size);


/* ZC ������ CAN ͨ��
GM_BOOL* CSPADPT_Get_FSIO_Error_State_Ptr(void);

GM_BOOL CSPADPT_Is_FSIO_Error(void);
*/

/*******************************************END*********************************************/

/*******************************************************************************************
*�������ܣ��ṩ���û���ȡ����ʱ�ӵĽӿ�

*����˵����CSPƽ̨������ʱ��ʱ��API

*����ֵ��

*******************************************************************************************/

E_SysBool F_VCP_CalendarClkGet(T_CalendarClk* const outClk)
{
	return e_TRUE;
}

/*******************************************************************************************
*�������ܣ�CSPƽ̨��ʼ�������������ȡϵ����CAN������̫����ͨ��״̬����ʼ�����У���ȡ���õȡ�
					 ��ʼ��ʧ��ӡԭ����healthy.c���á�

*����˵������

*����ֵ��1����ʼ���ɹ�
				 0����ʼ��ʧ��

*******************************************************************************************/
GM_BOOL  CSPADPT_App_Initialization(void)
{
	CSP_Init_Result = GM_FALSE;
	
	UINT32 mSysID=0U;
	UINT16 localIdAndType = 0U; 
        UINT8 adapterInit = 0U;
	do
	{
		
		F_VCP_GetSystemId(&mSysID);
		if(mSysID <= 0)	
		{
		printf("Fail to get SysID My ID is %d \n",mSysID);	
		 break;	
		}
		/*complete internal communication initialization
		CSP_Init_Result = INTERCOMM_CAN_Tcp_Initialization();
		if(CSP_Init_Result == GM_FALSE)
		{
		   printf("INTERCOMM_CAN_Tcp_Initialization() return 0x%x\n", CSP_Init_Result);	
           break;		   
		}*/

		/*complete fsio msg queue initialization  ������CAN
		CSP_Init_Result = FSIOPKT_Msg_Que_Init();  	
		if(CSP_Init_Result == GM_FALSE)
		{
		   printf("FSIOPKT_Msg_Que_Init() return 0x%x\n", CSP_Init_Result);	
           break;		   
		}		
		*/
		/*complete ci app msg queue initialization*/
		CSP_Init_Result = CSPADPT_App_Que_Init();  	
		if(CSP_Init_Result == GM_FALSE)
		{
		   printf("CSPADPT_App_Que_Init() return 0x%x\n", CSP_Init_Result);	
           		  break;   
		}			

		/*complete app config read initialization*/
		CSP_Init_Result = CSPADPT_App_Config_Data_Init();
		if(CSP_Init_Result == GM_FALSE)
		{
		   printf("CSPADPT_App_Config_Data_Init() return 0x%x\n", CSP_Init_Result);
  break;
           	}	
		
		/*complete configfile transmision initialization*/
		CSP_Init_Result = GM_CFG_INTERCOMM_Initialize();
		if(CSP_Init_Result == GM_FALSE)
		{
		   printf("GM_CFG_INTERCOMM_Initialize() return 0x%x\n", CSP_Init_Result);	
           		     break;
		}		
		
		/*complete safety protocal(rssp-1) initialization*/
		CSP_Init_Result = CSPADPT_Safety_Protocal_Init();
		if(CSP_Init_Result == GM_FALSE)
		{
		   printf("CSPADPT_Safety_Protocal_Init() return 0x%x\n", CSP_Init_Result);
        	     break;
		}
		
		/*������־��ʼ��*/
		CSP_Init_Result = GM_LOG_INTERCOMM_INIT();
		if (CSP_Init_Result == GM_FALSE)
		{
		   printf("GM_LOG_INTERCOMM_INIT() return 0x%x\n", CSP_Init_Result);
           	  break;
		}
		SYNC_INTERCOMM_Init();
		
		CSPADPT_Init_ExtDev_Comm_Status();
	
	    /* 20180527  ���ZC�ϵ��ʼ���ĺ��� */
		/* 1�����ݳ�ʼ�� */
		CSP_Init_Result = InitAllLocalInfo();
		if (CSP_Init_Result == GM_FALSE)
                {
		printf("InitAllLocalInfo() return 0x%x\n", CSP_Init_Result);
                break;
                } 
		
		/* 2��������ʼ�� */
		localIdAndType = ((UINT16_S)(((UINT16_S)DEVTYPE_ZC) << 8u) + GetLocalZcId());

        /* ������ʼ�� */

        AdptAppSetLocalName(localIdAndType);

        adapterInit = AdptAppExtDevInit();

        printf("IdType:0x%x,%d\n",localIdAndType,adapterInit);
	
		CSP_Init_Result = GM_TRUE;		
		
		
	}while(0);
	
	printf("CSPADPT_App_Initialization result is %d\n",CSP_Init_Result);
	return CSP_Init_Result;

}
/**
* @brief CSP�����ģ�� Ӧ��������ӿ�,�����շ�����ѯƽ̨����״̬
*
* Detailed description.
* @param[in]  void
* @param[out] void
* @return GM_BOOL
*/
/*******************************************************************************************
*�������ܣ�CSPƽ̨���������������healthy.c���������Ե��ã������շ������ϵͳ����״̬�ȡ�
					 ���ϲ�APPƽ̨�ĺ���״̬�쳣ʱl_MainResult=0��ƽ̨����Ϊ�ǽ�����

*����˵������

*����ֵ��l_Result��ZC�������ṩ��ƽ̨��Ľ���״̬��
				 1������ 

*******************************************************************************************/
GM_BOOL  CSPADPT_App_Main(void)
{
	
	GM_BOOL l_Result = GM_TRUE;
	GM_BOOL l_Rt = GM_FALSE;	
	UINT32 l_Size = 0U;	
	UINT32 l_Addr = 0U;
	UINT32* l_Addr2 = NULL;	
	INT8_S l_MainResult = 1U;
  	g_CycleNum++;
	UINT32 masterID;
      	printf("g_CycleNum = %d \n",g_CycleNum  );
	/* 20180527 
	AdptAppAddCycNum();
	*/

	 /* 
	Test_Send_Receive();
	*/

	/*Se Pkt Sending Watch Dog
	CSPADPT_Pkt_Wd_Set();*/
/*************************INPUT PROCESS*********************/

    /*Receive CAN Message
    INTERCOMM_CAN_Maintain_TCP();	
	  INTERCOMM_CAN_Receive_Msg();
	  */
	
	/*manage config file transmit between CPU and ETH*/
    CSPADPT_Cfg_Intercomm_Manage();
	/*manage syn channle maintain*/
    SYNC_INTERCOMM_Matain_Proc();	
	/*manage syn message receive*/
	CSPADPT_SYN_Receive_Message();
	
	/*manage CFM&SFM information receiving.*/
	CSPADPT_Rssp1_Receive_Manage();
	
	/*receive message from rssp1 module*/
    CSPADPT_Rssp1_Receive_Message();
		
	/*manage CFM&SFM information sending*/
	CSPADPT_Rssp1_Send_Manage();	
		
	/*receive raw protocal message from intercomm module*/	
	CSPADPT_Raw_Receive_Message();
		
	/*������������*/
    AdptAppExtDevInDataManage();	                     
      /*ƽ̨UDP�������ݴ���*/
    InterfaceInputProcessToLocalQueue(); 
	
/***********************PROCESS******************************/	
	
	/*Pre-Process Input Message from FSIO ��ʱ������CAN*/	
   /* FSIOPKT_Process_FSIO_To_APP_Msg();*/	
	
    /*Do The MainProcess of ZC APP Function ����ѯZC �ӿں� �޸� ������  MainProcess();	
    l_MainResult	 = ZC_Function_healthy(); */
	l_MainResult =  ZcSystemAppMain();
	 if(l_MainResult != 1U)
	 {
		 F_VCP_UsrHaltSystem(0);  /*����Ϊ�ǽ���*/
         printf("-----------------------MainProcess=%d\n", l_MainResult);		 
	 }
	 /*ΪVcp_Service_TestInterface �ṩ���ں�*/
	 UpdataRunCycNum(g_CycleNum);
	
    /*Pre_Porcess Output Message to FSIO*/
	/*FSIOPKT_Pack_Out_To_FSIO_Frame();*/
	/*Rearm WatchDog
	CSPADPT_Rearm_WatchDog();*/
	
	
/*********************OUTPUT MSG***************************/	

    
    InterfaceOutputProcessToPlatform();
    AdptAppExtDevOutDataManage();
	
	/*Send CAN frame through the TCP to ETH IO
	INTERCOMM_CI_CAN_Send_Msg();*/
	
	/*send app raw message to INTERCOMM module*/		
   	 CSPADPT_Raw_Send_Message();		
	
	/*send app message to rssp1 module*/		
    	CSPADPT_Rssp1_Send_Message();	
	
	
	/*manage syn message send*/
	CSPADPT_SYN_Send_Message();
	
	/*process err from RTD*/
	CSPADPT_Process_RTD_ErrCode();
	
	
		
/**********************************END****************************************************/		
	
	return l_Result;
	
}


/**
* @brief CSP�����ģ�� �����豸ID��ȡ�豸����
*
* Detailed description.
* @param[in]  UINT32 DevId �豸ID
* @param[out] void
* @return UINT8
*/
/*******************************************************************************************
*�������ܣ���ȡ�豸ID,

*����˵����UINT32 DevId Ҫ�жϵ��豸

*����ֵ��  UINT8 l_Type �豸ID ZC=0x1E,ATP=0x14,CI=0x3C,ATS=0x03

*******************************************************************************************/
UINT8  CSPADPT_Get_DeviceType_By_DeviceId(UINT32 DevId)
{
	UINT8 l_Type = 0U;

	/*��Ĭ��rssp1����豸���豸ID����Ӧ�ò��豸ID���ж���(ZC=0x1E,ATP=0x14,CI=0x3C,ATS=0x03)*/
	l_Type = (UINT8)((DevId&0xFF00U)>>8U);

	return l_Type;


}


/**
* @brief CSP�����ģ�� ����ͬ����Ϣ
*
* Detailed description.
* @param[in]  void
* @param[out] void
* @return void
*/
/*******************************************************************************************
*�������ܣ�CSP�����ģ�� ����ͬ����Ϣ���ж�intercomm���Ƿ���ɽ��ա�

*����˵������

*����ֵ����

*******************************************************************************************/
void  CSPADPT_SYN_Receive_Message(void)
{
	
	if(GM_TRUE != GM_CFG_INTERCOMM_Is_Cfg_Transmitted_OK())
	{
		return;
	}	
	
    SYNC_INTERCOMM_Recv_Proc();	
	
}

/*******************************************************************************************
*�������ܣ�CSP�����ģ�� ����ͬ����Ϣ

*����˵������

*����ֵ����

*******************************************************************************************/
void  CSPADPT_SYN_Send_Message(void)
{
	
	UINT32* l_CyclePtr = NULL;
	
	l_CyclePtr = CSPADPT_Get_Main_Cycle_Ptr();
	
	if(l_CyclePtr == NULL)
	{
		return;
	}
	
	if(GM_TRUE != GM_CFG_INTERCOMM_Is_Cfg_Transmitted_OK())
	{
		return;
	}	
	

		SYNC_INTERCOMM_Send_Proc();	


	
}

/*******************************************************************************************
*�������ܣ������ģ�� ����RSSP1��Ϣ��ں�����ͨ����ȡ�������жϽ���ģʽ��֮���ȡ����gCbtcRcvDataQue��
					 ������д��gCbtcRcvDataQue

*����˵������

*����ֵ����
*******************************************************************************************/
void  CSPADPT_Rssp1_Receive_Message()
{
	
    UINT8  l_Msg_Buf[1024U] = {0U};  
    UINT8  l_Buf[1024U] = {0U};  
    UINT32 l_addr = 0U;
    UINT32 l_lenth = 0U;
    UINT32 l_Msg_Lenth = 0U;
    UINT8   l_Rssp1_Msg_Type = 0U;
	QueueStruct* l_QueuePtr = NULL;	
	/*��ȡ����ģʽ�Ƿ�ΪRSSP1 ģʽ*/
	if(ENUM_EXT_ETH_COMM_TYPE_RSSP1 != CSPADPT_Get_External_Comm_Protocal_Type())
	{
		return;		
	}	

    GM_memset((void*)l_Msg_Buf, 0x00U, (size_t)(sizeof(l_Msg_Buf)));
	
	/*������Ϣ����*/
	l_QueuePtr = CSPADPT_Get_Cbtc_Rcv_Que_Ptr();
	/*�ж�FSFB���Ƿ���rssp1����*/
    while (1 == GM_RSSP1_APP_Interface_Rcv_App_Dat((GM_UINT8*)l_Msg_Buf, &l_addr, &l_lenth))
    {
				
        l_Rssp1_Msg_Type = l_Msg_Buf[1];
				/*�жϰ������Ƿ�Ϸ� 0x11ΪRSSP1 ���ݰ� 0x13λintercomm�㷢����ͨ��״̬��*/
        if(l_Rssp1_Msg_Type != 0x11U && l_Rssp1_Msg_Type != 0x13U)
        {
            continue;
        }
        
       /*printf("Rssp1 Data from %x, len %d, 0x%x 0x%x 0x%x 0x%x\n",
            l_addr, l_lenth, l_Msg_Buf[0], l_Msg_Buf[1], l_Msg_Buf[2], l_Msg_Buf[3]);*/
        /*RSSP1 ��д�����ݶ���*/
        if(l_Rssp1_Msg_Type == 0x11U)
        {			
		   l_lenth = l_lenth - 6U; 	
		   l_Msg_Lenth = 0U;	   
		   GM_memset((void*)l_Buf, 0x00U, (size_t)(sizeof l_Buf));	   
		   *(GM_UINT16*)(l_Buf + l_Msg_Lenth) = l_lenth  + 5U;	 
		   l_Msg_Lenth += 2U;
		   *(UINT8*)(l_Buf + l_Msg_Lenth) = CSPADPT_Get_DeviceType_By_DeviceId(l_addr);	/*�豸����*/
		   
		   printf("0x%x-%d\n",l_addr, l_lenth + 6U);

		   l_Msg_Lenth += 1U;	   
		   *(UINT8*)(l_Buf + l_Msg_Lenth) = (UINT8)(l_addr&0x0FU);	/*�豸��վ���*/   	   
		   l_Msg_Lenth += 1U;
		   *(GM_UINT16*)(l_Buf + l_Msg_Lenth) = 0U;		
		   l_Msg_Lenth += 2U;	
		   *(UINT8*)(l_Buf + l_Msg_Lenth) = 0U;			   
		   l_Msg_Lenth += 1U;	   
		   memcpy(l_Buf+l_Msg_Lenth, (UINT8*)(l_Msg_Buf+6), l_lenth); 
		   l_Msg_Lenth += l_lenth;	 
		   QueueWrite(l_Msg_Lenth,(QueueElement*) l_Buf,l_QueuePtr);					
				
        }
        /*0x13�� ����intercommͨ��״̬*/
        else
        {         
            /*����ͨ��״̬*/	
            CSPADPT_RSSP1_Comm_Message_Process((UINT8*)(l_Msg_Buf + 2U), (l_lenth-2U));
  
        }


        GM_memset((void*)l_Msg_Buf, 0x00U, (size_t)(sizeof(l_Msg_Buf)));
        l_lenth = 0U;
        l_addr = 0U;

    }	
	

}

/*******************************************************************************************
*�������ܣ�CSP�����ģ�� ������Э����Ϣ��ں���

*����˵������

*����ֵ����
*******************************************************************************************/
void  CSPADPT_Raw_Receive_Message()
{
    UINT8  l_Msg_Buf[1024U] = {0U};  
    UINT8  l_Buf[1024U] = {0U};  
    UINT32 l_addr = 0U;
    UINT32 l_lenth = 0U;
    UINT32 l_Msg_Lenth = 0U;
    UINT8   l_Rssp1_Msg_Type = 0U;
	  QueueStruct* l_QueuePtr = NULL;	
    GM_RSSP1_SFM_object_struct *pFSFB_SFM = NULL;	
    GM_RSSP1_com_pri_struct recv_pri;	
    GM_UINT16 con_index = 0U;	
    GM_UINT16 dest_addr = 0U;	
		GM_BOOL bRet = GM_FALSE;	
	/*�жϵ�ǰģʽΪ��Э��,RAWͨ��ģʽ*/
		if(ENUM_EXT_ETH_COMM_TYPE_RAW != CSPADPT_Get_External_Comm_Protocal_Type())
			{
				return;		
			}	
	
    l_QueuePtr = CSPADPT_Get_Cbtc_Rcv_Que_Ptr();  
    pFSFB_SFM = GM_RSSP1_Get_SFM_Object();
    
    for (con_index=0U; con_index< pFSFB_SFM->connection_nums; con_index++)
    {
				 
		l_addr =  pFSFB_SFM->connection[con_index].dest_addr;
		/*�ж��Ƿ��FSFB���յ�����*/
		while(!FSFB_Is_Msg_Queue_Empty(&(g_Link_MQ[con_index].RCV_SND_MQ[0].RCV_MQ)))
		  {
		    GM_memset((void*)(&recv_pri), 0x00U, (size_t)(sizeof(recv_pri)));
			
			bRet = FSFB_Msg_Queue_Get(&(g_Link_MQ[con_index].RCV_SND_MQ[0].RCV_MQ), (void*)&recv_pri);
			if (bRet)
				{
				printf("Raw 0x%x-%d\n", l_addr,recv_pri.bytes_count);
			   l_Msg_Lenth = 0U;	   
			   GM_memset((void*)l_Buf, 0x00U, (size_t)(sizeof l_Buf));	   
			   *(GM_UINT16*)(l_Buf + l_Msg_Lenth) = recv_pri.bytes_count + 5U;	 
			   l_Msg_Lenth += 2U;
			   *(UINT8*)(l_Buf + l_Msg_Lenth) = CSPADPT_Get_DeviceType_By_DeviceId(l_addr);	/*�豸����*/
			   l_Msg_Lenth += 1U;	   
			   *(UINT8*)(l_Buf + l_Msg_Lenth) = (UINT8)(l_addr&0x0FU);	/*�豸��վ���*/   	   
			   l_Msg_Lenth += 1U;
			   *(GM_UINT16*)(l_Buf + l_Msg_Lenth) = 0U;		
			   l_Msg_Lenth += 2U;	
			   *(UINT8*)(l_Buf + l_Msg_Lenth) = 0U;			   
			   l_Msg_Lenth += 1U;	   
			   memcpy(l_Buf+l_Msg_Lenth, (UINT8*)(recv_pri.byte), recv_pri.bytes_count); 
			   
			    l_Msg_Lenth += recv_pri.bytes_count;	 
			    QueueWrite(l_Msg_Lenth,(QueueElement*) l_Buf,l_QueuePtr);	
				
				}
  
		  }
		
    }	

}
/*******************************************************************************************
*�������ܣ�������RSSP1���ͨ��״̬

*����˵����UINT8* m_Msg_Ptr intercomm �㷢��������
				   UINT32 m_Length	intercomm ���͹��������ݳ���

*����ֵ�� ��
*******************************************************************************************/


void CSPADPT_RSSP1_Comm_Message_Process(UINT8* m_Msg_Ptr, UINT32 m_Length)
{
	UINT32 l_Node_Count = 0U;
	UINT32 l_Tmp_Length = 0U;
	UINT32 l_CommIndex = 0U;
	GM_UINT16 l_BitIndex = 0U;
	UINT32 l_Index = 0U;
	UINT8  l_SFM_State = 0U;
	GM_UINT16 l_Dev_Id = 0U;
	UINT8  l_Comm_State = 0U;
	UINT32 l_ChnIndex = 0U;	
	UINT8  l_DesType = 0U;
	UINT8  l_DesId = 0U;

	APP_RSSPI_COMM_STATE* l_Comm_State_Ptr = NULL;
	APP_RSSPI_COMM_STATE l_Tmp_Comm_State = {0};
	if((m_Msg_Ptr != NULL) && (m_Length > 0U))
	{
		l_Node_Count = *(UINT8*)m_Msg_Ptr;
		l_Tmp_Length = l_Node_Count*8U + 1U;
		l_CommIndex += 1U;
		/*
		printf("rssp1-comm-proc %d %d\n",m_Length,l_Tmp_Length);
		*/
		if(m_Length == l_Tmp_Length)
		{
			for (l_Index = 0U; l_Index < l_Node_Count; l_Index++)
			{
				l_Comm_State_Ptr = (APP_RSSPI_COMM_STATE*)(m_Msg_Ptr+l_CommIndex);
				l_BitIndex = 0U;
				GM_memset((void*)(&l_Tmp_Comm_State), 0x00, (size_t)(sizeof(l_Tmp_Comm_State)));
				l_Tmp_Comm_State.Index = l_Comm_State_Ptr->Index;
				l_Tmp_Comm_State.Des_Source_ID = l_Comm_State_Ptr->Des_Source_ID;
				l_BitIndex += 32U;
				l_Tmp_Comm_State.SFM_State = (UINT8)CSPADPT_Change_Bit_To_Byte((UINT8*)l_Comm_State_Ptr,l_BitIndex,(UINT8)4U);
				l_BitIndex += 4U;
				l_Tmp_Comm_State.Des_MS_State = (UINT8)CSPADPT_Change_Bit_To_Byte((UINT8*)l_Comm_State_Ptr,l_BitIndex,(UINT8)4U);
				l_BitIndex += 4U;
				l_Tmp_Comm_State.Udp_Chn_Num = (UINT8)CSPADPT_Change_Bit_To_Byte((UINT8*)l_Comm_State_Ptr,l_BitIndex,(UINT8)4U);
				l_BitIndex += 4U;
				l_Tmp_Comm_State.Udp_Chn_State = (UINT8)CSPADPT_Change_Bit_To_Byte((UINT8*)l_Comm_State_Ptr,l_BitIndex,(UINT8)8U);
				l_BitIndex += 8U;
				l_CommIndex += sizeof(APP_RSSPI_COMM_STATE);
				if(l_Tmp_Comm_State.SFM_State == 0x0F)
				{
					l_Comm_State = TRANSMIT_2OO2_STATE_GOOD;
					for (l_ChnIndex = 0U; l_ChnIndex < l_Tmp_Comm_State.Udp_Chn_Num; l_ChnIndex++)
					{	
						if((l_Tmp_Comm_State.Udp_Chn_State&(0x01<<l_ChnIndex)) > 0U)
						{
						}
						else
						{
							l_Comm_State = TRANSMIT_2OO2_STATE_LINK;
							break;							
						}
					}				
				}
				else
				{
					l_Comm_State = TRANSMIT_2OO2_STATE_BAD;					
				}
				
				
				
				l_DesType = (UINT8)((l_Tmp_Comm_State.Des_Source_ID&0xFF00U)>>8U);
				l_DesId = (UINT8)(l_Tmp_Comm_State.Des_Source_ID&0x00FFU);
			/*	CSPADPT_CI_Set_ExtDev_Comm_Status(l_DesType, l_DesId, l_Comm_State);*/
			}
		}
		else
		{
		}
	}
	else
	{
	}
	
	
}

/*******************************************************************************************
*�������ܣ� ��ʼ��ͨ��״̬��Ĭ��ΪOK
*����˵����
*����ֵ��
*******************************************************************************************/
 
void CSPADPT_Init_ExtDev_Comm_Status(void)
{
	UINT8 ii =0U;
	UINT8 jj =0U;

	/*������LEU��ZC��CI�ȵ�ͨ��״̬����*/
	/* Ū�����ٴ򿪰�
	for (ii = 0U; ii < (UINT8)COM_DEV_TYPE_SUM; ii++)
	{
		ComDevStatusInfo[ii].DeviceTypeOther = TransmitRelaDataStru[ii].SystemType;
		ComDevStatusInfo[ii].ComDevSum = TransmitRelaDataStru[ii].DeviceSum;
		for (jj = 0U; jj < (UINT8)(TransmitRelaDataStru[ii].DeviceSum); jj++)
		{
			ComDevStatusInfo[ii].ComDevIdBuf[jj] = TransmitRelaDataStru[ii].DeviceIdBuf[jj];
			ComDevStatusInfo[ii].ComDevIdComStatusBuf[jj] = TRANSMIT_2OO2_STATE_BAD;
		}
	}*/
	
	g_FsioErrorState = GM_TRUE;
	g_OppoMachineState = 0U;

}
/**
* @brief ��ȡϵ��
*
* Detailed description.
* @param[in]  outSysId Ҫ�жϵ�ϵ
* @param[out] s_Machine_Id 1 Iϵ 2 IIϵ
* @return s_Machine_Id
*/
/*******************************************************************************************
*�������ܣ���ȡϵ�𡣸�������IP����������жϵ�ǰ��Iϵ��IIϵ

*����˵����UINT32* const outSysId ���ڴ���ϵ��ı���

*����ֵ��  UINT32* const outSysId 1��I ϵ  2��II ϵ 
*******************************************************************************************/
void  F_VCP_GetSystemId(UINT32* const outSysId)
{
	static UINT8 s_Machine_Id = 0U;
   	UINT8* l_Addr = NULL;
   	FSC_VPD_IP_SUBNET_DATA l_Data;
	size_t l_Size = 0U;
	
	if(s_Machine_Id == 0U)
	{
		l_Addr = (UINT8*)(&l_Data);
		l_Size = (size_t)sizeof(FSC_VPD_IP_SUBNET_DATA);
		GM_memset((void*)(&l_Data), 0x00U, l_Size);
		
		fscVpdIpSubnetGet((FSC_VPD_IP_SUBNET_DATA*)(&l_Data));		
		
		if(*(UINT8*)(l_Addr+11) == 10U)
			s_Machine_Id = 2U;
		else
			s_Machine_Id = 1U;			
			
	    printf("fscVpdIpSubnetGet %d\n", *(UINT8*)(l_Addr+11));					
	}
	*(outSysId)=s_Machine_Id;
}
/**
* @brief ��ȡ��ϵ
*
* Detailed description.
* @param[in]  outSysId
* @param[out] masterId 1:Iϵ�� 2:IIϵ��
* @return masterId
*/
/*******************************************************************************************
*�������ܣ���ȡ��ϵ��ID�����Ȼ�ȡ��ǰϵ��ID�����жϵ�ǰϵ�Ƿ�Ϊ��

*����˵����UINT32* const outSysId �洢ϵ��ı���

*����ֵ��  UINT32* const outSysId 1 ��IϵΪ��
								                  2 ��IIϵΪ�� 
*******************************************************************************************/
void  F_VCP_GetMasterId(UINT32* const outSysId)
{
	UINT32 masterId = 0;
	GM_UINT16 activeStatus = 0x0U;
	fscCsArbActiveStatusGet(&activeStatus, TRUE);
	activeStatus = (activeStatus&SRB_Master_Value);
	F_VCP_GetSystemId(outSysId);
	if(activeStatus == SRB_Master_Value&&*(outSysId)==1U)
		{
			*(outSysId) = 1U;
		}			
	else if(activeStatus == SRB_Master_Value&&*(outSysId)==2U)
		{
			*(outSysId)= 2U;			
		}	                    
	  	
}

          
/******************************************************************************************* 
*�������ܣ� �����ģ�飬Ӧ�������ļ���ʼ������ȡ�û������ļ�������ȡ�����б�
						����ṹ����� APP_CONFIG_HEAD ����ȡ�ļ�index��ֵ��APP_CONFIG_PER_FILE_HEAD���ڱ���ÿ���ļ�����Ϣ��
						����CSP��˵��Ҫ��ȡ������Ϣ�����⻹Ҫ��ȡ��ZC���ӵ�ƽ̨��������Ϣ ��
  					��VCPƽ̨��c_DeviceInfTable�������CSP                                                                                  
*����˵���� ��                                                                               
*����ֵ��   l_Result GM_TRUE  1�� �ɹ�
										 GM_FALSE 0�� ʧ��                                                                              
*******************************************************************************************/ 
  
GM_BOOL  CSPADPT_App_Config_Data_Init(void)
{
	GM_BOOL l_Result = GM_FALSE;
	VOID* l_Config_Area;
	APP_CONFIG_HEAD* l_Config_File_Head_Ptr = NULL;  /* ������ */
	APP_CONFIG_PER_FILE_HEAD* l_Per_File_Head_Ptr = NULL;  /* ÿ������ */
	UINT32 l_Offset = 0U;
	UINT32 l_Index = 0U;
 
	GM_memset((void*)&g_App_Config_Head, 0x00, (size_t)sizeof (APP_CONFIG_HEAD));/* ��ʼ�����ַΪ0 */
	
	l_Config_File_Head_Ptr = CSPADPT_Get_App_Config_File_Head();/* �������ڴ洢���õ�ȫ�ֽṹ�� */
	l_Config_Area = CSPADPT_Get_User_Config_Addr();             /* ��ȡϵͳ�д洢�����׵�ַ */


	if(l_Config_Area != NULL)
	{
		/*Check and Decompose the config data*/		
		l_Config_File_Head_Ptr->phymemaddr = l_Config_Area;/*Ϊȫ�����ýṹ�帳ֵ�������û��������׵�ַ*/
    l_Config_File_Head_Ptr->filenum    = *(UINT8*)(l_Config_Area + l_Offset);/* ���ø���һ���ֽ� */
		
	  /*  printf("CI_App_Config_Data_Set() File Num = %d, %d\n", 
				*(UINT8*)(l_Config_Area + l_Offset),
				l_Config_File_Head_Ptr->filenum);		*/
		
		l_Offset += 1U;
			
		for(l_Index = 0U; l_Index < l_Config_File_Head_Ptr->filenum && l_Index < MAX_CFG_FILE_NUMBER; l_Index++)
		{   
		    /*�ڴ���= �Ѿ��洢�ĵ�ַ�б�*/
			l_Per_File_Head_Ptr = (APP_CONFIG_PER_FILE_HEAD*)(l_Config_Area + l_Offset);
			l_Config_File_Head_Ptr->perfile[l_Index].filetype = l_Per_File_Head_Ptr->filetype;
			l_Config_File_Head_Ptr->perfile[l_Index].fileid = l_Per_File_Head_Ptr->fileid;
			l_Config_File_Head_Ptr->perfile[l_Index].filesize = l_Per_File_Head_Ptr->filesize;
			l_Config_File_Head_Ptr->perfile[l_Index].fileoffset = l_Per_File_Head_Ptr->fileoffset;

			l_Offset += sizeof(APP_CONFIG_PER_FILE_HEAD);

	    /*
	    	printf("CI_App_Config_Data_Set() The %d File type=0x%x, id = %d, size = 0x%x  offset = 0x%x\n", 
			  l_Index + 1,
				l_Config_File_Head_Ptr->perfile[l_Index].filetype,
				l_Config_File_Head_Ptr->perfile[l_Index].fileid,
				l_Config_File_Head_Ptr->perfile[l_Index].filesize,
				l_Config_File_Head_Ptr->perfile[l_Index].fileoffset);
			*/

		}
		/* 
			����ZC��4������������Ҫͬ��������������Ҫͬ��
			0.��·��������BNF
			1.ZC.ID
			2.RSSP1
			3.ͨ�������ļ�
		*/
		l_Result = CSPADPT_App_Set_DevId();
	}
	else
	{
	    l_Result = GM_FALSE;
	}

	return l_Result;
	/*����״̬���Բ��ò�
	void CSPADPT_Init_ExtDev_Comm_Status(void)
	void CSPADPT_Set_ExtDev_Comm_Status(UINT8 m_Type, UINT8 m_Id, UINT8 m_State)
	*/
	
}

/******************************************************************************************* 
*�������ܣ��������õĸ�ʽ����Ҫϸ��˵���������������ݽṹҪ��һ������                                                         
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

UINT32 F_VCP_GetDevCfgDetail(const UINT32   inListLen, T_DevCfgDetail outDevCfgDetailList[],UINT32*  outDevNum)
{
	UINT32 retVal = 0U;
	UINT8  funcVal = 0U;
	UINT8 commDevNum = 0U;
	UINT32 devType = 0U;
	UINT32 devId = 0U;
	UINT16 localName = 0U;
	UINT8 localType = 0U;
	UINT8 devStartIndex = 0U;
	UINT8 index =0U;
	devStartIndex = 4U;
	/*commDevNum = GetCommDevNum();*/
	UINT8*  Comm_CFG_Addr; 
	UINT32* Comm_CFG_Size;
	GM_BOOL  result = GM_FALSE;
	/*�����ENUM_CONFIG_DAT_TYPE_CIAPP ��������Ϊ�������Ա��ȡ��ͨ������*/
	result = 1;
	*outDevNum = 74;
	
	
		for(index=0;index<inListLen;index++)
		{
		outDevCfgDetailList[index].BasicInfo.DevType=c_DeviceInfTable[index].Type;
		outDevCfgDetailList[index].BasicInfo.AppId=c_DeviceInfTable[index].AppId;
		outDevCfgDetailList[index].BasicInfo.AccSys=c_DeviceInfTable[index].SysId;
		outDevCfgDetailList[index].ExInfo.RecvNum=10;
		outDevCfgDetailList[index].ExInfo.SendNum=10;	
		}
	return result;
		
}



/******************************************************************************************* 
*�������ܣ�  ���ָ���豸������ ��ǿ��VCP�����ڶ�ܵ�ͨ�ţ�CSPϵͳ��û�ж�ܵ����ܵ��Ų���û�����塣  
                                                                              
*����˵����  @inDevType: �����豸���߼�����
 *          @inAppId  : �����豸��Ӧ��ID Ӧ��ID��Ψһ��ʾ
 *          @inDevSys : �����豸������ϵ��
 *          @inPipeId : ����ʹ��Э��汾
                        ENUM_EXT_ETH_COMM_TYPE_INVALID = 0x00U,      ��Ч����
                        ENUM_EXT_ETH_COMM_TYPE_RAW     = 0x55U,      ��Э��
                        ENUM_EXT_ETH_COMM_TYPE_RSSP1   = 0xAAU,      RSSP-1Э��
                        ENUM_EXT_ETH_COMM_TYPE_RSSP2   = 0xBBU       Ԥ��
           @ioUsrBuff: ����/������ݵĻ���
                                                                               
*����ֵ��   ���� E_UsrRxStatus, ָʾ��ȡ���ݵ�״̬                                                                                 
*******************************************************************************************/ 

E_UsrRxStatus F_VCP_UsrDataRecvEx(const UINT32 inDevType,const UINT32 inAppId,const UINT32 inDevSys,const UINT32 ProtocolType,T_UsrBuff* ioUsrBuff)
{	
	E_UsrTxStatus result = e_UsrTxErrStatus;   /* �ɹ���ʱ��ķ���ֵ e_UsrRxLcAppNew*/
	UINT32 m_inDevType	  = inDevType;
	UINT32 m_ProtocolType = ProtocolType;
	QueueStruct* l_QueuePtr = NULL;	
	UINT32 l_QueLen = 0U;
	UINT8  l_Buf[1500U] = {0U};
	UINT32 l_Len = 0U; 
	
	
	l_QueuePtr = CSPADPT_Get_Cbtc_Rcv_Que_Ptr();

#if 0
	/*���Э�����Ͳ���ֱ�� ���ش�*/
	if(ProtocolType != CSPADPT_Get_External_Comm_Protocal_Type())
	{
		return;		
	}	

#else
     l_QueLen = QueueStatus(l_QueuePtr);

   
     if(l_QueLen >= 12U)
     {
         /* ����ʽ: ���ݳ���(2) + ����(1) + ���(1) + Ԥ��(3) + ��������(n) */
	     memset((void*)l_Buf, 0x00U, (size_t)(sizeof l_Buf));
	     QueueScan(7U, l_Buf, l_QueuePtr); /* ���ݳ��� */
		 
		 l_Len = l_Buf[0];
		 l_Len = (((l_Len ) << 8u) + l_Buf[1]);
		 
	    
	     if((l_QueLen >= (l_Len + 2U))  && (l_Len > 4U))
	     {
	   
	         /* �ж����ͺͱ�� */	
			 if((inDevType == (UINT32)l_Buf[2]) && (inAppId == (UINT32)l_Buf[3]))
			 {
			     /* ��ȡǰ7���ֽ� */
			     QueueRead(7U, l_Buf, l_QueuePtr); 

				 memset(l_Buf, 0x00U, sizeof l_Buf);
				 
		         l_Len = l_Len - 5U;
		         QueueRead(l_Len, l_Buf, l_QueuePtr);

				 /* �ڴ渴�� */
				 memcpy(ioUsrBuff->ptrMsg,l_Buf,l_Len);
				 ioUsrBuff->dataLen = l_Len;

				 result = e_UsrRxLcAppNew;

				 printf("&&3:%d 0x%02x 0x%02x\n",l_Len,*(ioUsrBuff->ptrMsg),*(ioUsrBuff->ptrMsg + 1));
			 }	
	     }
	}

	 return result;
	


    
#endif

}


/******************************************************************************************* 
*�������ܣ�   CSP�����ģ�� ��ȡ����CBTC������Ϣ�Ķ���ָ��                                                                               
*����˵����                                                                                  
*����ֵ��     &gCbtcRcvDataQue                                                                               
*******************************************************************************************/ 

QueueStruct* CSPADPT_Get_Cbtc_Rcv_Que_Ptr()
{
  return &gCbtcRcvDataQue;
}


/******************************************************************************************* 
*�������ܣ�  CSP�����ģ�� ��ȡ����CBTC������Ϣ�Ķ���ָ��                                                                                
*����˵����                                                                                  
*����ֵ��    &gCbtcSndDataQue                                                                                
*******************************************************************************************/ 

QueueStruct* CSPADPT_Get_Cbtc_Send_Que_Ptr()
{
  return &gCbtcSndDataQue;
}
/******************************************************************************************* 
*�������ܣ�  CSP�����ģ�� ��ȡӦ����־��ӡ                                                                           
*����˵����                                                                                  
*����ֵ��    &gCbtcSndDataQue                                                                                
*******************************************************************************************/ 

QueueStruct* CSPADPT_Get_APP_LOG_Ptr()
{
	return &AppLogDataQue;
}

/******************************************************************************************* 
*�������ܣ� CSP�����ģ�� ����RSSP2��Ϣ��ں��� ��ʱԤ��                                                                                 
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

void CSPADPT_Rssp2_Receive_Message(const UINT32 inDevType,T_UsrBuff* ioUsrBuff)
{
}


/******************************************************************************************* 
*�������ܣ���ָ���豸�������� ��ǿ�͡�CSPƽ̨����󳤶�������UDP�����ֵ������Ҫ��ܵ��ˡ�
 					 ���Ǳ���ԭ����β��䣬�ܵ��Ų�����Ч��������û�п������ݵ�Э�����ͣ����ϲ�Ӧ����Э�����䡣		                                                                            
*����˵���� @inDevType: �����豸���߼�����
 *          @inAppId  : �����豸��Ӧ��ID
 *          @inDevSys : �����豸������ϵ��
 *          @ProtocolType(inPipeId) : ����CSPƽ̨���������������Э�����ͣ�0��Э�飬1 RSSP-1,2 RSSP-2
 *          @inData   : �����û��ṩ���ڴ����ݵĻ���
 *          @inDataLen: �����û��ṩ��������ݵĳ���
                                                                                 
*����ֵ��                                                                                    
*******************************************************************************************/ 

 
E_UsrTxStatus F_VCP_UsrDataSendEx(const UINT32 inDevType, const UINT32 inAppId, const UINT32 ProtocolType, const UINT32 inPipeId, const void*  inData, const UINT32 inDataLen)
{
#if 0
	E_UsrTxStatus result = e_FALSE;  /* �ɹ��󷵻� e_UsrTxSuccess */
	UINT32 m_inDevType    = inDevType;
	UINT32 m_ProtocolType = ProtocolType;
	/*�ƻ�ǰ10���豸����Ϊ����ͨ��*/
	if (m_inDevType<10)
		{
			/*ProtocolType 0���㷢 1��RSSP-1 2:RSSP-2 ����Ҫһ������ת������*/
			
			switch (m_ProtocolType)
				{
			case 0:
				{
				result=e_TRUE;
				break;
				}
			case 1:
				{
				result=e_TRUE;
				break;
				}
		 		case 2:	
				{
				break;
				}
				default:
				break;
				}
	
    }
				
			
	else
		{
		/*CAN*/
		
		}
	return result;
#else
    E_UsrTxStatus result = e_FALSE;  /* �ɹ��󷵻� e_UsrTxSuccess */
	QueueStruct* l_QueuePtr = NULL;	
	UINT8  l_Buf[1524U] = {0U};
	UINT32 l_Len = 0U;
	UINT32 l_QueLen = 0U;	
	UINT16 tmp_Len = 0U;

	memset((void*)l_Buf, 0x00U, (size_t)(sizeof l_Buf));

	/* if(DEVTYPE_MAINTAIN != inDevType) */


        if(0x1b != inDevType) 
	{
	    l_QueuePtr = CSPADPT_Get_Cbtc_Send_Que_Ptr();


		/* ����ʽ: ���ݳ���(2) + ����(1) + ���(1) + Ԥ��(2) + ��������(n) */
		if((NULL != inData)  && (0u < inDataLen))
		{
		    tmp_Len = ((UINT16)inDataLen + 4u);
		    /* ��д���� */
		    l_Buf[0] = (UINT8)((tmp_Len >> 8u) & 0x00ffu);
			l_Buf[1] = (UINT8)(tmp_Len & 0x00ffu);
			
			/* ���� */
			l_Buf[2] = (UINT8)(inDevType & 0x000000ffu);
			
			/* ��� */
			l_Buf[3] = (UINT8)(inAppId & 0x000000ffu);

			/* Ԥ��(2) */
			l_Buf[4] = 0u;
			l_Buf[5] = 0u;

			/* �������� */
			memcpy(&l_Buf[6],inData,inDataLen);

			QueueWrite(tmp_Len + 2u,l_Buf,l_QueuePtr);

			result = e_UsrTxSuccess;
		}
	}
	else
	{

		
		CSPADPT_Log_Record_Pack((UINT8*)inData,inDataLen);
		/* ��־���� 
	    l_QueuePtr = CSPADPT_Get_APP_LOG_Ptr();*/

		 /*ֱ��д����־����  
		QueueWrite(inDataLen,inData,l_QueuePtr);
		*/

		result = e_UsrTxSuccess;
	}

	
	return 	result;
    

#endif
	
}


/******************************************************************************************* 
*�������ܣ�  �����ģ�� ������Э����Ϣ��ں�����������������������Ե��á�                                                                              
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 


void  CSPADPT_Raw_Send_Message()
{
	
	UINT8  l_Buf[1024] = {0U};
	UINT32 l_Len = 0U;
	UINT32 l_QueLen = 0U;	
  GM_UINT16 l_addr = 0U;	
  GM_UINT16 source_addr = 0U;	
	QueueStruct* l_QueuePtr = NULL;	
  GM_RSSP1_SFM_object_struct *pFSFB_SFM = NULL;
	
	if(ENUM_EXT_ETH_COMM_TYPE_RAW != CSPADPT_Get_External_Comm_Protocal_Type())
	{
		return;			
	}
	
	if(GM_TRUE != GM_CFG_INTERCOMM_Is_Cfg_Transmitted_OK())
	{
		return;	
	}

  GM_memset((void*)l_Buf, 0x00U, (size_t)(sizeof(l_Buf)));
  pFSFB_SFM = GM_RSSP1_Get_SFM_Object();
  l_QueuePtr = CSPADPT_Get_Cbtc_Send_Que_Ptr();/*��ȡ���ڷ������ݵĶ���*/
  source_addr = pFSFB_SFM->source_addr;	
	while((l_QueLen = QueueStatus(l_QueuePtr)) >= 12U)
	{
		memset(l_Buf, 0x00U, sizeof l_Buf);
		QueueRead(2U, l_Buf, l_QueuePtr); 
		l_Len = *(GM_UINT16*)l_Buf;
			
		if(l_QueLen >= l_Len + 2U  && l_Len > 4U)
		{
				
			 QueueRead(1U, l_Buf, l_QueuePtr); 		
			 QueueRead(1U, l_Buf+1, l_QueuePtr); 		
			 QueueRead(2U, l_Buf+2, l_QueuePtr); 
			 
			 l_addr = *(GM_UINT16*)l_Buf;

			 memset(l_Buf, 0x00U, sizeof l_Buf);				 
			 l_Len = l_Len-4U;
			 QueueRead(l_Len, l_Buf, l_QueuePtr); 				 
			 CSPADPT_Raw_Send_Interface(l_addr, (UINT8*)l_Buf, l_Len);
			 
		}

	}

}

/******************************************************************************************* 
*�������ܣ� �����ģ�� ��Э����Ϣ������INTERCOMMģ��ӿں���                                                                                 
*����˵����  UINT16 m_Dest       Ŀ���豸ID                     
             UINT8*  m_Msg_Ptr   ��������Ϣ        
             UINT32 m_Msg_Length ��������Ϣ����                                                                     
*����ֵ��    ��                                                                                
*******************************************************************************************/ 


void CSPADPT_Raw_Send_Interface(GM_UINT16 m_Dest, UINT8*  m_Msg_Ptr, UINT32 m_Msg_Length)
{
   
    GM_BOOL rt =GM_FALSE;
    GM_RSSP1_SFM_object_struct *pFSFB_SFM = NULL;
    GM_UINT16 i = 0U;
    GM_UINT16 dest_addr = 0U;	
    GM_RSSP1_com_pri_struct send_pri;
    GM_RSSP1_Write_Q_Return_Enum q_write_rt;
	
		if(m_Msg_Length > GM_RSSP1_MAX_SAFETY_DAT_LEN)
		return;

		GM_memset((void*)(&send_pri), 0, (size_t)sizeof(GM_RSSP1_com_pri_struct));	
  
    pFSFB_SFM = GM_RSSP1_Get_SFM_Object(); /* �������� */
    
    for (i=0U; i< pFSFB_SFM->connection_nums; i++)
    {
        dest_addr = pFSFB_SFM->connection[i].dest_addr;
         
        if((dest_addr&0xFFFFU) == m_Dest)
        {
            
	      GM_memcpy((void*)(send_pri.byte) , (void*)m_Msg_Ptr , (size_t)m_Msg_Length);
          send_pri.bytes_count = m_Msg_Length;	
          /*���͵���Ϣ����д�����*/		
		  q_write_rt = FSFB_Msg_Queue_Write(&(g_Link_MQ[i].RCV_SND_MQ[0].SND_MQ) , (void*)(&send_pri));
		  /*printf("CI_Raw_Send: dest=0x%x len=%d, result=%d\n",dest_addr, m_Msg_Length, q_write_rt);	*/	
          break;			
			
        }
        
    }
    
}


/******************************************************************************************* 
*�������ܣ� CSP�����ģ�� ����RSSP1��Ϣ��ں��� ������������������Ե��á�
                                                                               
*����˵����
                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

void CSPADPT_Rssp1_Send_Message(void)
{
	
	UINT8  l_Buf[1024U] = {0U};
	UINT32 l_Len = 0U;
	UINT32 l_QueLen = 0U;	
  UINT16 l_addr = 0x0301U;	
  UINT16 source_addr = 0U;	
	QueueStruct* l_QueuePtr = NULL;	
  GM_RSSP1_SFM_object_struct *pFSFB_SFM = NULL;
	
	if(ENUM_EXT_ETH_COMM_TYPE_RSSP1 != CSPADPT_Get_External_Comm_Protocal_Type())
	{
		return;			
	}
	
	if(GM_TRUE != GM_CFG_INTERCOMM_Is_Cfg_Transmitted_OK())
	{
		return;	
	}

    GM_memset((void*)l_Buf, 0x00U, (size_t)(sizeof(l_Buf)));
 
    pFSFB_SFM = GM_RSSP1_Get_SFM_Object();
    l_QueuePtr = CSPADPT_Get_Cbtc_Send_Que_Ptr();
    
      source_addr = pFSFB_SFM->source_addr;
	/*���Է�������
	UINT8 DATA[16]={0,14,0x03,0x01,0,0,1,2,3,4,5,6,7,8,9,10};
	QueueWrite(16,(QueueElement*)DATA,l_QueuePtr);*/
			
	while((l_QueLen = QueueStatus(l_QueuePtr)) >= 12U)
	{
		memset((void*)l_Buf, 0x00U, (size_t)(sizeof l_Buf));
		QueueRead(2U, l_Buf, l_QueuePtr); /*���ݳ���*/
		l_Len = *(UINT16*)l_Buf;
			
		if(l_QueLen >= l_Len + 2U  && l_Len > 4U)
		{
				
			 QueueRead(1U, l_Buf, l_QueuePtr); 		
			 QueueRead(1U, l_Buf+1, l_QueuePtr); 		
			 QueueRead(2U, l_Buf+2, l_QueuePtr); 
			 
			 l_addr = *(UINT16*)l_Buf;
		 
			 memset(l_Buf, 0x00U, sizeof l_Buf);				 
			 l_Len = l_Len-4U;
			 QueueRead(l_Len, l_Buf, l_QueuePtr); 				 
				 
			 CSPADPT_Rssp1_Send_Interface(l_addr, (UINT8*)l_Buf, l_Len);
			 
		}
	}		
			 
}
/**
* @brief CSP�����ģ�� ��Ϣ���͹�����
*
* Detailed description.
* @param[in]  void
* @param[out] void
* @return void
*/

/******************************************************************************************* 
*�������ܣ�                                                                                  
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

void  CSPADPT_Rssp1_Send_Manage(void)
{
	
	if(ENUM_EXT_ETH_COMM_TYPE_RSSP1 == CSPADPT_Get_External_Comm_Protocal_Type())
	{
	    GM_RSSP1_SFM_Interface_Proc_Send();
	    GM_RSSP1_CFM_Interface_Proc_Send();
	}
	else
	if(ENUM_EXT_ETH_COMM_TYPE_RAW == CSPADPT_Get_External_Comm_Protocal_Type())
	{
	    GM_RSSP1_CFM_Interface_Proc_Send_For_Raw();	
	}
	else
	{
	
	}
	
}



/******************************************************************************************* 
*�������ܣ�  CSP�����ģ�� ��RSSP2ģ�����Ϣ���ͽӿ�     Ԥ��                                                                           
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 


void CSPADPT_RSSP2_Send_Manage(void)
{

}

/******************************************************************************************* 
*�������ܣ� CSP�����ģ�� ��RSSP1ģ�����Ϣ���ͽӿ�                                                                                 
*����˵����
            UINT16 m_Dest    Ŀ���豸ID
            UINT8*  m_Msg_Ptr  ��������Ϣ
            UINT32 m_Msg_Length ��������Ϣ����                                                                                  
*����ֵ��  ��                                                                                  
*******************************************************************************************/ 

void CSPADPT_Rssp1_Send_Interface(GM_UINT16 m_Dest, UINT8*  m_Msg_Ptr, UINT32 m_Msg_Length)
{
   
    GM_BOOL rt =GM_FALSE;
    GM_RSSP1_SFM_object_struct *pFSFB_SFM = NULL;
    UINT8 dat[1024] = {0U}; 
    GM_UINT16 i = 0U;
    GM_UINT16 source_addr = 0U;
    GM_UINT16 dest_addr = 0U;
    GM_UINT16 dat_len = 0;
	  void* src_ptr = NULL;
   	void* dst_ptr = NULL; 
  
    pFSFB_SFM = GM_RSSP1_Get_SFM_Object();
    /* ����RSSP-1Э������ȫ������һ���ҵ� m_Dest*/
    
    for (i=0U; i< pFSFB_SFM->connection_nums; i++)
    {
        source_addr = pFSFB_SFM->source_addr;
        dest_addr = pFSFB_SFM->connection[i].dest_addr;

        /*printf("pFSFB_SFM->connection_nums = %d\n",pFSFB_SFM->connection_nums);*/
      
        
         /*���������ӵ��豸���� 1402 Ϊ���� */
       if(((dest_addr&0xFFFFU) == m_Dest)||((CSPADPT_Get_DeviceType_By_DeviceId(m_Dest) == 0x14U) 
        	&& (dest_addr == 0x1402U)))
        	
        {
            dat[0]   = (UINT8)((source_addr & 0xff00U) >> 8U);
            dat[1]   = (UINT8)(source_addr & 0x00ffU);
            dat[2]   = (UINT8)((dest_addr & 0xff00U) >> 8U);
            dat[3]   = (UINT8)(dest_addr & 0x00ffU);
						src_ptr = (void*)m_Msg_Ptr;
						dst_ptr = (void*)(dat + 4);
            GM_memcpy(dst_ptr, src_ptr, m_Msg_Length);
            dat_len = 4 + m_Msg_Length;			
            rt = GM_RSSP1_Send_App_Dat(dat , (UINT32)dat_len);
	
        }
		

    }
}
/******************************************************************************************* 
*�������ܣ�  RSSP2 ����Ԥ��                                                                                
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

void CSPADPT_Rssp2_Send_Interface(GM_UINT16 m_Dest, UINT8*  m_Msg_Ptr, UINT32 m_Msg_Length)
{

}

/******************************************************************************
 *Name    : F_VCP_UsrDataWatch
 *Function: �ṩ���û�ÿ�����ڽ��е������ݼ��Ľӿڣ�CSPƽ̨�����ݳ��ȿ�������MTU������Ƴ��ȣ�1400��
 *          �ڴ�����Ϊ1400      
 *Para    : @inData    : Ϊ��Ϣ�����׵�ַ
 *          @inDataLen : Ϊ��Ϣ���ݳ���(���ֽ�Ϊ��λ)
 *Return  : ����ɹ��򷵻�e_TRUE, ���򷵻�e_FALSE
 *Note    :
******************************************************************************/

E_SysBool F_VCP_UsrDataWatch(const UINT8* const inData,const UINT32 inDataLen)
{
	/*ֻ�ж������Ƿ񳬹���󳤶� �ж����ݳ����Ƿ񳬹���UDP������� ������̫������MTUΪ1500 ����UDP����Ϊ1400*/
	const UINT32 MaxLength = 1400;
	E_SysBool result =e_FALSE;
	if (MaxLength>inDataLen)
		{
		result = e_TRUE;
		}
	return result;
}
/******************************************************************************************* 
*�������ܣ� ����ͬ����CSP�������������ÿ�����ڶ������ϵ��ͬ��������Ӧ�ò���APP�ٵ����ˡ�
                                                                            
*����˵����                                                                                  

*����ֵ��                                                                                    
*******************************************************************************************/ 
E_SysBool F_VCP_UsrDataSendMutual(const void* const inData,const UINT32 inDataLen)
{
		/*UINT32* l_CyclePtr = NULL;
		
		if(GM_TRUE != GM_CFG_INTERCOMM_Is_Cfg_Transmitted_OK())
		{
			return e_FALSE;
		}	
		SYNC_INTERCOMM_Send_Proc();
		*/
		return e_TRUE;
}
/******************************************************************************
 *Name    : F_VCP_UsrDataRecvMutual
 *Function: ��ϵ�û�������ϵ�û����͵�����
 *Para    :  @ioMsg : ����/������ݵĻ���,��ṹ����:
 *                    typedef  struct TAG_CellMsg
 *                    {
 *                      UINT8*  ptrMsg ; [>Out: �洢���׵�ַ               <]
 *                      UINT32  dataLen; [>I/O: �洢������/�洢�������ݳ���<]
 *                    } T_CellMsg;
 *Return  : ���� E_UsrRxStatus, ָʾ��ȡ���ݵ�״̬
 *           . e_UsrRxLcEmpty  = 1, �߼�ͨ������Ϊ��
 *           . e_UsrRxLcAppNew = 2, �߼�ͨ��(�û�)��ϢΪ��
 *           . e_UsrRxLcAppOld = 3, �߼�ͨ��(�û�)��ϢΪ��
 *           . e_UsrRxLcMsgErr = 4, �߼�ͨ������Ϣ����
 *           . e_UsrRecvCfgErr = 5  �û��ṩ�Ľ���������Ϣ����
 *Note    :
******************************************************************************/
E_UsrRxStatus F_VCP_UsrDataRecvMutual(T_CellMsg* const ioMsg)
{
	if(GM_TRUE != GM_CFG_INTERCOMM_Is_Cfg_Transmitted_OK())
		{
			return e_UsrRxLcMsgErr;
		}	
		
		SYNC_INTERCOMM_Recv_Proc(); 
	    return e_UsrRxLcAppNew;

}

/******************************************************************************
 *Name    : F_VCP_UsrHaltSystem
 *Function: ���û������жϳ����ش������ҪֹͣӦ�ô���ʱ���ô˽ӿں�����
 *          ���������洢���ϴ���(�Ա��û�����ά��)����5���ں���ִֹ���û�Ӧ�ô�
 *          �����CSPƽֱ̨������Ϊ崻�״̬
 *Para    : @inErrCode: ������ϴ���
 *Return  : void
 *Note    :
 *C.A.0002  YanGuang  2013/04/17  �޸�ԭ���
 *                                �����������ڿ�ʼ��ִֹ���û�Ӧ�ô������
 *                                ��Ϊ ��������ִֹ���û�Ӧ�ô������
******************************************************************************/

void F_VCP_UsrHaltSystem(const UINT32 inErrCode)
{
	
	GM_BOOL l_Result = GM_FALSE;
	FSC_STATUS rc = FSC_UNSUCCESSFUL;
	GM_UINT16 l_ModuleHealthVal = 0x0180U;  /*Bit 7 = FSCCS_CHASSIS_CPU_A_MODULE (0x0080) 
	                                       Bit 8 = FSCCS_CHASSIS_CPU_B_MODULE (0x0100) */
	rc = fscCsChassisModHlthForceSet(l_ModuleHealthVal);/*CPU_A,CPU_Bͬʱ����Ϊ���ϡ�*/
    if (rc != FSC_SUCCESSFUL)
    {
        printf("CSPADPT_ZC_Set_To_UnHealth() failed with 0x%08x\n", rc);
	    CSPADPT_Process_RTD_ErrCode();
    }
    else
    {
		l_Result = GM_TRUE;
        printf("CSPADPT_ZC_Set_To_UnHealth Successful.\n");
    }
	
}
/******************************************************************************************* 
*�������ܣ�CSP�����ģ�� ����RTD��ϴ���         
                                                                         
*����˵����   
                                                                               
*����ֵ��                                                                                    
*******************************************************************************************/ 


GM_BOOL CSPADPT_Process_RTD_ErrCode(void)
{

	FSC_STATUS rc;
	FSC_RTD_TEST_RUN_t const test;
	FSC_RTD_TEST_RUN_t *testp = NULL;
	GM_BOOL isRunning = GM_FALSE;
	GM_UINT16 appFault = FSCCS_APP_BIT_SAFETY_MODE;

	testp = &test;
	rc = fscRtdIsRunning((BOOL*)(&isRunning));
	if (rc == FSC_SUCCESSFUL && isRunning == GM_TRUE)
	{
		rc = fscRtdTestStatAll (testp);
		if (rc == FSC_SUCCESSFUL)
		{
			if((testp->rtd_result & 0xFFFF) > 0U)
			{
				/* One or more tests failed, go unhealthy (Action 3) if reported
				* failure is in range of Safety Relevant failures
				* Use RTD test code as APP failure code
				*/
				/* NEED TO VERIFY THIS RANGE AND EXCEPTIONS
				* BASED ON CURRENT ACTIONS
				*/
				if(testp->rtd_tstCode >= FSC_RTD_VFPGA_SGCMP_ERROR
				&& testp->rtd_tstCode <= FSC_RTD_CFPGA_GEOADDR_ERROR)
				{
					switch (testp->rtd_tstCode)
					{
						case FSC_RTD_CFPGA_BOOTBK_ERROR:
						case FSC_RTD_VFPGA_VER_ERROR:
						case FSC_RTD_VFPGA_NOTHTH_ERROR:
						/* Not Safety Relevant faults */
						break;
					default:
						appFault = FSC_ERROR_TYPE(testp->rtd_tstCode);
					}
					/* If reported fault not SR, but more faults
					* exist, scan for one that is SR
					*/
					if (appFault == FSCCS_APP_BIT_SAFETY_MODE
					&& (testp->rtd_result & 0xFFFF) > 1)
					{
						/* Loop through all failed test groups (bits set
						* in ((testp->testResult >> 16) & 0xFFFF))
						* and all tests within each group, comparing
						* tstCode with SR failures
						* Set appFault if any are SR. Up to application
						* if/how to report multiple faults��
						*/
					}
				}
	        }
		}
		else
		{
		    appFault = FSC_ERROR_TYPE(rc);
		}
	}
	else /* RTD not running or API failure */
	{
   
	   if(rc == FSC_SUCCESSFUL)
	   {
		   appFault = 0;
	   }
	   else
	   {
		   appFault = FSC_ERROR_TYPE(rc);		   
	   }
	   
	}

	/* If error / fault detected, log event and de-assert APP health */
	if (appFault != FSCCS_APP_BIT_SAFETY_MODE)
	{
		printf("RTD appFault = 0x%x\n");
	    fscCsEhAppFaultSet (appFault); /* Go Unhealthy */
	}	
	
	return isRunning;
	
}
/******************************************************************************
 *Name    : F_VCP_InquiryDevStatus
 *Function: �ṩ���û����������VCP�豸ָ����Ϣ��ȡVCP�豸�ĵ�ǰ״̬�Ľӿ�
 *Para    : @inDevType: �����豸���߼�����
 *          @inAppId  : �����豸��Ӧ�ñ��
 *          @inClique : �����豸����ϵ���ʶ
 *Return  : ����ָ���豸����ϸ��Ϣ(�����豸������ ״̬ E_SysDevStatus):
 *          . e_SysDevNotExist = 1, �豸������
 *          . e_SysDevInit     = 2, �豸��ʼ��
 *          . e_SysDevNormal   = 4, �豸����״̬
 *          . e_SysDevFault    = 5  �豸����״̬
 *Note    :
******************************************************************************/


T_SysDevInf F_VCP_InquiryDevStatus(const UINT32 inDevType, const UINT32 inAppId,const UINT32 inClique)
{
	 GM_UINT16 m_Health=0;
	 GM_BOOL result;
	 struct TAG_SysDevInf m_TAG_SysDevInf;
	 m_TAG_SysDevInf.Detail.DevType=inDevType;
	 m_TAG_SysDevInf.Detail.AppId=inAppId;
	 m_TAG_SysDevInf.Detail.AccSys=inClique;
	 fscCsChassisModHlthQualGet (&m_Health,result);
	 /*�ص��Ƿ���ֵ���� ��detail��ɶ��*/
	if (m_Health==0)
		{
		 m_TAG_SysDevInf.Status=e_SysDevNormal;
		}
	else
		{
		m_TAG_SysDevInf.Status=e_SysDevFault;
		}
	return m_TAG_SysDevInf;
}


/******************************************************************************************* 
*�������ܣ� �ṩ���û���ѯ�����汾��FPGA�汾�������ֻ��ӡCSP����汾�������汾                                                                                
*����˵���� @inDevType      : �����豸���߼�����        
            @inAppId        : �����豸��Ӧ�ñ��        
            @inAccSys       : �����豸����ϵ���ʶ     
            @outProcVersion : ��������汾         
            @outCommVersion : ���CSPƽ̨�汾                                                                                       
*����ֵ��   �����ѯ��ȷ�򷵻�e_TRUE, ����e_FALSE                                                                               
*******************************************************************************************/ 

E_SysBool  F_VCP_InquirySwVersion(const UINT32  inDevType, const UINT32  inAppId,  const UINT32  inAccSys,  UINT32* const outProcVersion, UINT32* const outCommVersion)
{
  /*��Ҫ��VCPƽ̨������ǲ��ǵײ������ƣ���CSPƽ̨�����ǲ��ǲ�һ�������Լ������İ汾�Ϳ��ԣ�*/
	E_SysBool result = e_TRUE;
  printf("ZC adpter Ver: %s\n",ZC_adpter_VERSION);
	printf("ZC adpter Ver: %s\n",ZC_CSP_VERSION);
	return result;
}
/******************************************************************************************* 
*�������ܣ�                                                                                  
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

void  F_VCP_DevInfSummary(T_SysDevInf* const outDevInfArray,UINT32* const ioDevInfTotal)
{

}


/******************************************************************************************* 
*�������ܣ�   CSP ƽֻ̨���������� �����outHwVersion=fpgaVerA+fpgaVerB                                                                                 
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

void F_VCP_GetHwVersion(CHAR* const outHwVersion)
{

	GM_UINT16  const lenA=8;
	CHAR * const fpgaVerB=NULL;
	GM_UINT16  const lenB=4;
	FSC_STATUS rc; 
	rc=fscCsFpgaVersionGet(outHwVersion,lenA,fpgaVerB,lenB);
	if(rc==0)
	{/*��16λ��ֵΪB�İ汾 ��16λ��ֵΪA�İ汾*/
	strcat(outHwVersion,fpgaVerB);
	}
	
}
/******************************************************************************************* 
*�������ܣ�                                                                                  
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

void F_VCP_GetVcpId(UINT32* const outVcpId)
{

}
/******************************************************************************************* 
*�������ܣ�                                                                                  
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

E_SysBool F_VCP_UsrIndicator(const UINT32 inIndicatorNo,
							 const UINT32 inAction)
{
	return e_TRUE;
}
/******************************************************************************************* 
*�������ܣ�                                                                                  
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

E_SysBool F_VCP_UsrInquiryParamVersion(const UINT32 inTarget,
									   UINT32*      outParamVersion,
									   UINT8        outParamCrc[],
									   const UINT32 inParamCrcLen)
{
	return e_TRUE;
}
/******************************************************************************************* 
*�������ܣ�                                                                                  
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

E_SysBool F_VCP_GetDevVerInf(const UINT32     inDevType,
							 const UINT32     inAppId,
							 const UINT32     inDevSys,
							 T_UsrDevVerInf*  outDevVerInf)
{
	return e_TRUE;
}
/******************************************************************************************* 
*�������ܣ�                                                                                  
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

void F_VCP_GetLocBspVersion(UINT32* const outBspVersion)
{

}
/**
* @brief 
*
* Detailed description.
* @param[in]  UINT8 *m_Data_Ptr
* @param[in]  UINT16 m_Bgn_Index
* @param[in]  UINT8 m_Data_Size
* @param[out] UINT8 *m_Data_Ptr
* @return UINT32
*/
/******************************************************************************************* 
*�������ܣ�  CSP�����ģ�� ��ָ��BITת��ΪBYTE                                                                                
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

UINT32 CSPADPT_Change_Bit_To_Byte(UINT8 *m_Data_Ptr, UINT16 m_Bgn_Index, UINT8 m_Data_Size)
{
	UINT8   i = 0U;
	UINT8   l_Data = 0U;
	UINT8   l_Byte_Count = 0U;
	UINT8   l_Data_Mode = 0U;
	UINT32  l_Return_Data = 0U;
	UINT16  l_Byte_Index = 0U;
	UINT8  l_Bit_Index = 0U;
	UINT8  l_Bit_Left = 0U;

	if (m_Data_Ptr != NULL)
	{
		l_Byte_Index = m_Bgn_Index / 8;
		l_Bit_Index = (UINT8)(m_Bgn_Index % 8);
		if(m_Data_Size > (8U - l_Bit_Index))
		{
			l_Bit_Left = (UINT8)(m_Data_Size - (8U - l_Bit_Index));

			if ((l_Bit_Left % 8U) > 0U)
			{
				l_Byte_Count = (UINT8)((l_Bit_Left / 8) + 1U);
			}
			else
			{
				l_Byte_Count = (UINT8)(l_Bit_Left / 8);
			}

			l_Data_Mode = (UINT8)(1U << (UINT8)(8U - l_Bit_Index));
			l_Data_Mode -= 1U;
			l_Data = *(m_Data_Ptr + l_Byte_Index) & l_Data_Mode;
			l_Return_Data = l_Return_Data | (l_Data << l_Bit_Left);

			while (i < l_Byte_Count)
			{
				if (l_Bit_Left < 8U)
				{
					l_Data = (UINT8)*(m_Data_Ptr + ((l_Byte_Index + 1U) + i)) >> (UINT8)(8U - l_Bit_Left);
					l_Return_Data = l_Return_Data | l_Data;
				}
				else
				{
					l_Data = *(m_Data_Ptr + ((l_Byte_Index + 1U) + i));
					l_Return_Data = l_Return_Data | (UINT32)(l_Data << (UINT8)(l_Bit_Left - 8U));
				}

				l_Bit_Left -= 8U;
				i++;
			}
		}
		else
		{
			l_Data_Mode = 1U << m_Data_Size;
			l_Data_Mode -= 1U;
			l_Data_Mode = l_Data_Mode << (UINT8)((8U - l_Bit_Index) - m_Data_Size);
			l_Data = *(m_Data_Ptr + l_Byte_Index);
			l_Return_Data = l_Data & l_Data_Mode;
			l_Return_Data = l_Return_Data >> ((8U - l_Bit_Index) - m_Data_Size);
		}
	}
	else
	{
		l_Return_Data = 0U;
	}

	return l_Return_Data;
}
/******************************************************************************************* 
*�������ܣ�                                                                                  
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

E_SysBool F_VCP_CalendarClkSet( const T_CalendarClk* const inClk )
{
	return e_TRUE;
}
/******************************************************************************************* 
*�������ܣ�                                                                                  
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

void F_VCP_SystemClkGet( T_SysClk* const outSysClk )
{
	
}
/******************************************************************************************* 
*�������ܣ�                                                                                  
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

E_SysBool F_VCP_UsrDataSend( const UINT32 inDevType, const UINT32 inAppId, const UINT32 inDevSys, const void* inData, const UINT32 inDataLen )
{
	return e_TRUE;
}
/******************************************************************************************* 
*�������ܣ�                                                                                  
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

void CSPADPT_Set_OppoMachine_State(UINT8 state)
{
	g_OppoMachineState = state;
}
/******************************************************************************************* 
*�������ܣ�                                                                                  
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

UINT8 CSPADPT_Get_OppoMachine_State(void)
{
	return g_OppoMachineState;
}

/******************************************************************************************* 
*�������ܣ�  CSP�����ģ�� ��ȡ�����������                                                                                 
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

UINT32* CSPADPT_Get_Main_Cycle_Ptr(void)
{
	return &g_CycleNum;
}

/******************************************************************************************* 
*�������ܣ�CSP�����ģ�� ��ȡ��CBTC����ͨ��ʹ�õ�Э������                                                                                  
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

ENUM_TYPE_EXTERN_ETH_COMM_PROTOCAL CSPADPT_Get_External_Comm_Protocal_Type(void)
{
	return (ENUM_TYPE_EXTERN_ETH_COMM_PROTOCAL) g_ExternCommProtocalType;
}

/******************************************************************************************* 
*�������ܣ� CAN ͨ��ʹ��                                                                                 
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 
/*
GM_BOOL* CSPADPT_Get_FSIO_Error_State_Ptr(void)
{
	return &g_FsioErrorState;
}
*/
/******************************************************************************************* 
*�������ܣ�    CAN ͨ��ʹ��                                                                                
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 
/*
GM_BOOL CSPADPT_Is_FSIO_Error(void)
{
	return g_FsioErrorState;
}
*/
/******************************************************************************************* 
*�������ܣ�                                                                                  
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

UINT8 CSPADPT_Get_Local_Machine_Id(void)
{
	return g_LocalMachineId;
}


/******************************************************************************************* 
*�������ܣ�  CSP�����ģ�� ���������ļ����ñ����豸����  ZC���ⲿ����Ҫ�����ý�������                                                                               
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

GM_BOOL  CSPADPT_App_Set_DevId(void)
{
	GM_BOOL l_Result = GM_FALSE;
	UINT32 l_Size = 0U;	
	UINT32 l_Addr = 0U;		
    INT32 l_value = -1;	
	UINT32 mSysID = 0U;
	
	
	CSPADPT_Get_SpeciConfig_Addr_Size(ENUM_CONFIG_DAT_TYPE_CIID, (UINT8*)(&l_Addr), &l_Size);
	if(l_Addr != 0U && l_Size > 0U)
	{		
		do
		{
			l_Result = GM_Ini_File_Read_Int("CI_GLOBAL", "localCiId", &l_value, (char*)l_Addr);

			if ((GM_FALSE == l_Result) || (l_value < 0))
			{
				g_LocalDeviceId = 0U;
				l_Result = GM_FALSE;
				break;
			}
			else
			{					
                g_LocalDeviceId = (UINT8)l_value;		

			}		


			
			l_Result = GM_Ini_File_Read_Int("CI_GLOBAL", "machineId", &l_value, (char*)l_Addr);

			if ((GM_FALSE == l_Result) || (l_value < 0))
			{
				g_LocalMachineId = 0U;
				l_Result = GM_FALSE;
				break;
			}
			else
			{	
			   F_VCP_GetSystemId(&mSysID);
               g_LocalMachineId = (UINT8)mSysID;	
               if((mSysID == 1U && g_LocalMachineId == 1U)
				  || (mSysID == 2U && g_LocalMachineId == 2U))
				{
					  /*Check OK*/
				}
				else
				{
				   printf("Machine ID Configure Err...%d\n", l_value);
				   g_LocalMachineId = 0U;
				   l_Result = GM_FALSE;
				   break;						
					
				}
				   				
			}					
			/*������þͲ�Ҫ���ˣ�����rssp1�����������ZC �� CI ��ȫһ�µĸ�ʽ*/
			l_Result = GM_Ini_File_Read_Int("CI_GLOBAL", "protocalType", &l_value, (char*)l_Addr);

			if ((GM_FALSE == l_Result) || (l_value < 0))
			{
				g_ExternCommProtocalType = (UINT8) ENUM_EXT_ETH_COMM_TYPE_INVALID;
				l_Result = GM_FALSE;
				break;
			}
			else
			{					
                g_ExternCommProtocalType = (UINT8)l_value;	
				
			}					
			           
			l_Result = GM_TRUE;			
			
			
		}while(0);
				  
	    printf("CSPADPT_CI_App_Set_DevId StationId=%d, MachineId=%d, ProtocalType=0x%x\n", g_LocalDeviceId, g_LocalMachineId,g_ExternCommProtocalType);		 
		
	}
	else
	{
		g_LocalDeviceId = 0U;
		g_LocalMachineId = 0U;		
    g_ExternCommProtocalType = ENUM_EXT_ETH_COMM_TYPE_INVALID;		
    l_Result = GM_FALSE;    
          
	}
	return l_Result;	
	
}

/******************************************************************************************* 
*�������ܣ�  �����ģ�� Ӧ�ö��г�ʼ���ӿں���                                                                                
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

GM_BOOL  CSPADPT_App_Que_Init(void)
{
    GM_BOOL l_Init_Rlt = GM_FALSE;
    GM_BOOL l_Result = GM_FALSE;

	do
	{
		
		
		l_Init_Rlt = QueueInitial(&gCbtcRcvDataQue,5000U);
		if(GM_TRUE != l_Init_Rlt)
		{
			l_Result = GM_FALSE;	
			break;
		}
		
		
		l_Init_Rlt = QueueInitial(&gCbtcSndDataQue,5000U);
		if(GM_TRUE != l_Init_Rlt)
		{
			l_Result = GM_FALSE;	
            break;			
		}
		l_Init_Rlt = QueueInitial(&AppLogDataQue,24000U);
		if(GM_TRUE != l_Init_Rlt)
		{
			l_Result = GM_FALSE;	
            break;			
		}
		l_Result = GM_TRUE;
	
	}while(0);
	

	return l_Result;

}



/******************************************************************************************* 
*�������ܣ�  CSP�����ģ�� RSSP1��ȫЭ���ʼ����ں���                                                                                
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

GM_BOOL  CSPADPT_Safety_Protocal_Init(void)
{

	GM_BOOL l_Result = GM_FALSE;
	UINT32 l_Size = 0U;	
	UINT32 l_Addr = 0U;		
	char* l_Addr2 = NULL;		
	
	
	CSPADPT_Get_SpeciConfig_Addr_Size(ENUM_CONFIG_DAT_TYPE_RSSPI, (UINT8*)(&l_Addr), &l_Size);
	if(l_Addr == 0U)
	printf("CSPADPT_Safety_Protocal_Init no l_Addr\n");
	
	if( l_Size <= 0U)
		
	printf("CSPADPT_Safety_Protocal_Init no size\n");
	
	printf(" size = 0x%x\n",l_Size);
	if(l_Addr != 0U && l_Size > 0U)
	{
	  
	    l_Addr2 = (char*)l_Addr;
	    l_Result = GM_RSSP1_APP_Interface_Init_CSP((GM_RSSP_GET_ABAS_FUN)CSPADPT_Get_Machine_ABAS,l_Addr2, l_Size);
	  
	    printf("GM_RSSP1_APP_Interface_Init_CSP() return 0x%x\n", l_Result);		 
		
	}
	else
	{
        l_Result = GM_FALSE;      
	}

	return l_Result;

}


/******************************************************************************************* 
*�������ܣ� CSP�����ģ�� ��ȡ��ϵ��ǰ������־                                                                                 
*����˵����                                                                                  
*����ֵ��   GM_VLE_ABAS_Type_enum                                                                                 
*******************************************************************************************/ 

GM_VLE_ABAS_Type_enum CSPADPT_Get_Machine_ABAS(void)
{
	
    UINT16 activeStatus = 0x0U;
	GM_VLE_ABAS_Type_enum l_Type = ASAS_Type_Unknow;
		
	fscCsArbActiveStatusGet(&activeStatus, TRUE);
	
	activeStatus = (activeStatus&SRB_Master_Value);
	
	if(CSPADPT_Get_Local_Machine_Id() == 1U)
	{
	    if(activeStatus == SRB_Master_Value)
		{
			l_Type = ABAS_Type_A_AS;
		}			
		else
		{
			l_Type = ABAS_Type_A_SA;
					
		}
            				
	}
	else
	if(CSPADPT_Get_Local_Machine_Id() == 2U)
	{
	    if(activeStatus == SRB_Master_Value)
		{
			l_Type = ABAS_Type_B_AS;
		}			
		else
		{
			l_Type = ABAS_Type_B_SA;			
		}
            				
	}	
	else
	{
		/*Do Nothing*/
	}
	
  return l_Type;
}

/******************************************************************************************* 
*�������ܣ� CSP�����ģ�� ��ȡWatchDog ShareRgn�׵�ַ                                                                                 
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

VOID* CSPADPT_Get_WatchDog_ShareRgn_Addr(void)
{
	VOID* l_Config_Area = NULL;
	l_Config_Area = sdRgnAddrGet("sdRgn"); 
	
	return l_Config_Area;	
}
/******************************************************************************************* 
*�������ܣ�                                                                                  
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

void CSPADPT_Rearm_WatchDog(void)
{
	UINT32* l_Addr = NULL;
	UINT32* l_CycPtr = NULL;
	l_Addr = (UINT32*)CSPADPT_Get_WatchDog_ShareRgn_Addr();
	l_CycPtr = CSPADPT_Get_Main_Cycle_Ptr();
	
	if(l_Addr != NULL && l_CycPtr != NULL)
	{
		*(l_Addr) =  (*l_CycPtr);
	}
	else
	{
		/*Do Nothing*/
	}

}


/******************************************************************************************* 
*�������ܣ� CSP�����ģ�� ���÷������ݰ����Ź���ʱ�䵽��l_TimeValue��ƽ̨��û�����ݷ��;ͻ�����Ϊ�ǽ���״̬     
                                                                       
*����˵����   
                                                                                
*����ֵ��                                                                                    
*******************************************************************************************/ 

GM_BOOL CSPADPT_Pkt_Wd_Set(void)
{
	static GM_BOOL l_Result = GM_FALSE;
	FSC_STATUS rc;
	UINT32 l_TimeValue = 1500U;  /*1500ms*/
	
	if(GM_TRUE != GM_CFG_INTERCOMM_Is_Cfg_Transmitted_OK())
	{
		return l_Result;
	}	
	
	
	if(l_Result == GM_FALSE)
	{
		rc = fscVlPktWdEnable();	
		if (rc == FSC_SUCCESSFUL)
		{	
			rc = fscVlPktWdTimerValSet(l_TimeValue);
			if(rc == FSC_SUCCESSFUL)
			{
				l_Result = GM_TRUE;
			}
			else
			{
				l_Result = GM_FALSE;			
			}
			
		}
		else
		{
			l_Result = GM_FALSE;		
			printf("fscVlPktWdEnable Fail.\n");
		}
		printf("fscVlPktWdEnable %d.\n",l_Result);	
			
	}
	else
	{
		/*Do Nothing*/
	}


	return l_Result;
}

/******************************************************************************************* 
*�������ܣ�   CSP�����ģ�� ����Intercommģ�����ӿں���                                                                                
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

void  CSPADPT_Cfg_Intercomm_Manage(void)
{
	
    GM_CFG_INTERCOMM_TcpProcess();
	  GM_CFG_INTERCOMM_AppProcess();
			
}


/******************************************************************************************* 
*�������ܣ�    CSP�����ģ�� ��Ϣ���չ�����                                                                              
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 

void  CSPADPT_Rssp1_Receive_Manage(void)
{
	
	if(ENUM_EXT_ETH_COMM_TYPE_RSSP1 == CSPADPT_Get_External_Comm_Protocal_Type())
	{
	    GM_RSSP1_CFM_Interface_Proc_Recv();
	    GM_RSSP1_SFM_Interface_Proc_Recv();	
	}
	else
	if(ENUM_EXT_ETH_COMM_TYPE_RAW == CSPADPT_Get_External_Comm_Protocal_Type())
	{
	   GM_RSSP1_CFM_Interface_Proc_Recv_For_Raw();		
	} 
	else
	{
		/*Do Nothing*/
	}
	
	
}
/******************************************************************************************* 
*�������ܣ����ڸ��������ֺ����ṩƽ̨����״̬                                                                              
*����˵����                                                                                  
*����ֵ��                                                                                    
*******************************************************************************************/ 
void CSPADPT_Get_Running_State(UINT8* m_Buf, UINT32* m_Len)
{
	UINT32 l_Len = 0U;
	UINT32 m_MachineID=0;
	UINT32 m_MasterID=0;
	F_VCP_GetSystemId(&m_MachineID);
	F_VCP_GetMasterId(&m_MasterID);
	if(m_Buf == NULL || m_Len == NULL)
		return;

	*(UINT32*)(m_Buf + l_Len) = 9U;
	l_Len += 4U;
	*(UINT32*)(m_Buf + l_Len) = 0x55AAAA55U;
	l_Len += 4U;	

	if((m_MachineID==m_MasterID) == GM_TRUE)	
	{
		*(UINT8*)(m_Buf + l_Len) = 0xAAU;		
	}
	else
	{
		*(UINT8*)(m_Buf + l_Len) = 0x55U;			
	}	
	l_Len += 1U;	
	*(UINT32*)(m_Buf + l_Len) = g_CycleNum;	
	l_Len += 4U;	

	*m_Len = l_Len;


	
}
/******************************************************************************************* 
*�������ܣ�    ����־������д��Ӧ�÷��͹���������                                                                          
*����˵����                                                                                  
*����ֵ��    1 ��־д����гɹ�
         0 ��־д�����ʧ��
*******************************************************************************************/ 
GM_BOOL  CSPADPT_Log_Record_Pack(UINT8*  m_Msg_Ptr, UINT32 m_Msg_Length)
{
	
	GM_BOOL Result = GM_FALSE;
	QueueStruct* l_QueuePtr = NULL;
	UINT32 QueueSpace=0U;
	l_QueuePtr = CSPADPT_Get_APP_LOG_Ptr();
	QueueSpace = QueueGetSpace(l_QueuePtr);
	/*д������Ϊ�գ�����Ϊ�գ�ʣ��ռ䲻��*/
	if (m_Msg_Ptr==NULL||m_Msg_Length<=0||(QueueSpace<m_Msg_Length))
		{
			return Result;
		}
	GM_LOG_INTERCOMM_SEND(  m_Msg_Ptr, m_Msg_Length);
	
	return Result;
	
}

GM_BOOL Test_Send_Receive()
{
	const UINT32 inDevType= 0x03;
	const UINT32 inAppId  = 0X01;
	const UINT32 inDevSys = 0x01;
	const UINT32 ProtocolType=0;
	T_UsrBuff  ioUsrBuff;
	UINT8 DATA[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	ioUsrBuff.allocLen=20;
	ioUsrBuff.dataLen=20;
	ioUsrBuff.ptrMsg= &DATA;
	UINT32 inPipeId =1;
	UINT32 inDataLen =20;

 	
	F_VCP_UsrDataSendEx( inDevType,  inAppId, ProtocolType,  inPipeId, &DATA,  inDataLen);	

	T_UsrBuff  ioUsrBuff1;
	const UINT32 inDevType2= 0x14;
	const UINT32 inAppId2  = 0X02;
	F_VCP_UsrDataRecvEx( inDevType2,  inAppId2, inDevSys,  ProtocolType, &ioUsrBuff1);
}




