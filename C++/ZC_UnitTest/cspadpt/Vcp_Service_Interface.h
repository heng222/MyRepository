/******************************************************************************
 *File Name         :    Vcp_Service_Interface.h
 *Copyright         :    Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :    2012/03/11
 *Module Id      :  SD-SM_PAB-1010
 *Description    :    SM�ṩ���й�PAB��BSP�ӿ�(���ļ�ֻʵ��ETH�ڰ�)
 *                  ����������ʵ�ֶ��ѿ⺯������ʽ�ṩ
 *
 *+----------+---------------------------------------------------------------+
 *| Design   |    �����ͨ�ź�ϵͳͨ�ð�ȫ�����ƽ̨�������SM_PAB           |
 *|  File    |    �����ϸ���˵����Vcp_Service_Interface���_B.2            |
 *+----------+--------------+------------+-----------------------------------+
 *| Version  |    Author    |    Date    |            Description            |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0001 | YanGuang     | 2012/03/11 |  File Create                      |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0002 | YanGuang     | 2013/04/17 |(1)�Ժ���ָ�����͵��β����const   |
 *|          |              |            |   �޶���                          |
 *|          |              |            |(2)�޸�TAG_CellMsg��˵��           |
 *|          |              |            |(3)�޸�F_VCP_UsrDataRecv�β�       |
 *|          |              |            |   �޸�F_VCP_UsrDataRecvMutual�β� |
 *|          |              |            |   �޸�F_VCP_DevInfSummary�β�     |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0003 | YanGuang     | 2013/08/28 |(1)ɾ������״̬                    |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0004 | YanGuang     | 2013/10/29 |���ӽӿں���:                      |
 *|          |              |            |(1)F_VCP_UsrIndicator              |
 *|          |              |            |(2)F_VCP_UsrInquiryParamVersion    |
 *|          |              |            |���ӽӿڳ���:                      |
 *|          |              |            |(1)c_UsrIndicatorA                 |
 *|          |              |            |(2)c_UsrIndicatorB                 |
 *|          |              |            |(3)c_UsrIndicatorOn                |
 *|          |              |            |(4)c_UsrIndicatorOff               |
 *|          |              |            |(5)c_InquiryLoc                    |
 *|          |              |            |(6)c_InquiryRem                    |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0005 | ZhuHui       | 2014/03/20 |(1)ɾ���ļ�������ݽṹ������      |
 *|          |              |            |(2)��ӽӿ�F_VCP_GetVcpId          |
 *|          |              |            |           F_VCP_GetHwVersion      |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0006 | ZhuHui       | 2014/08/20 |(1)��E_SysDevStatus�����һ��״̬  |
 *|          |              |            |   e_SysDevTesting                 |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0007 | ZhuHui       | 2014/10/10 |(1)��ӽӿ�F_VCP_GetLocBspVersion  |
 *|          |              |            |(2)�޸�F_VCP_UsrDataSend           |
 *|          |              |            |   ����޷���ƽ̨���跢���������  |
 *+----------+--------------+------------+-----------------------------------+
 *| C.B.0001 | ZhuHui       | 2015/08/20 |(1)Ethģʽ��ͨ���½ӿڷ���/����    |
 *|          |              |            |   ϵ���û�����                    |
 *|          |              |            |   ��Ӻ��ʶϵ���û�������󳤶�  |
 *+----------+--------------+------------+-----------------------------------+
 *
 ******************************************************************************/

/******************************************************************************
*    Multi-Include-Prevent Start Section
****************************************************************************/
#ifndef VCP_SERVICE_INTERFACE_H_
#define VCP_SERVICE_INTERFACE_H_
#define ZC_adpter_VERSION   "1.0.0.0"
#define ZC_CSP_VERSION      "1.2.0.0"/*ARTESYNʹ�õ�ϵͳ�汾Ϊ1.2*/
#define MAX_CFG_FILE_NUMBER    8U


#define TRANSMIT_2OO2_STATE_GOOD                  0x01U      /*ͨ������*/
#define TRANSMIT_2OO2_STATE_LINK                  0x02U      /*ά������*/
#define TRANSMIT_2OO2_STATE_BAD                   0x03U      /*ͨ���ж�*/
#define COM_DEV_TYPE_SUM                          8U
#define COM_DEV_MAX                               1400
#define SRB_Master_Value                          0xC0			/*��SRBģʽ����ϵ��־C3 ��������ģʽ��ΪC0*/


#ifdef WIN32
#pragma pack(1)
#define ADPTER_PACKED
#else
#define ADPTER_PACKED  __attribute__((__packed__))
#endif




/******************************************************************************
*    Debug switch Section
******************************************************************************/

/******************************************************************************
*    Include File Section ��������CSPƽ̨����
******************************************************************************/
/*
#include <vxworks.h>
#include <stdio.h>
#include <usrLib.h>
#include <arpa/inet.h>
*/

#include "fscVpd.h"
#include "fscRtd.h"
#include "fscCsDrv.h"
#include "fscLib.h"

#include "GL_Basic_Type_Definition.h"
#include "Vcp_Public_Definition.h"
#include "Vcp_Service_TestInterface.h"
#include "Vcp_File_Interface.h"
#include "..\GM_Utils\GM_MQ_Fixed.h"
#include "..\GM_Utils\GM_Memset.h"
#include "..\GM_Utils\GM_Memcpy.h"
#include "..\GM_Utils\GM_Ini_File.h"
#include "..\Common\CommonQueue.h"
#include "..\FSFB\GM_RSSP1_APP_Interface.h"
#include "..\FSFB\CFM\GM_RSSP1_CFM_Interface.h"
#include "..\FSFB\SFM\GM_RSSP1_SFM_Interface.h"
#include "..\INTERCOMM\GM_CFG_INTERCOMM.h"
#include "..\INTERCOMM\SYNC_INTERCOMM_Def.h"
#include "..\INTERCOMM\SYNC_INTERCOMM_Init.h"
#include "..\INTERCOMM\SYNC_INTERCOMM.h"
#include "..\INTERCOMM\GM_LOG_INTERCOMM.h"
/* CAN ͨ��
#include "..\INTERCOMM\CAN_INTERCOMM.h"
#include "..\fsiopkt\fsiopkt.h"
*/


/******************************************************************************
*    Global Macro Define Section
******************************************************************************/



/******************************************************************************
*    Global Struct    Define Section
******************************************************************************/
/*����ϵͳ�豸״̬*/
/*C.A.0003  ZhuHui  2013/08/21  ɾ������״̬*/
typedef  enum TAG_SysDevStatus
{
  e_SysDevNotExist= 1, /*�豸������   */
  e_SysDevInit    = 2, /*�豸��ʼ��   */
  e_SysDevNormal  = 4, /*�豸����״̬ */
  e_SysDevFault   = 5, /*�豸����״̬ */
  e_SysDevTesting = 6  /*�豸�Լ�     */
}E_SysDevStatus;

/*�����û����ݽ���״̬*/
typedef enum TAG_UsrRxStatus
{
  e_UsrRxLcEmpty  = 1,  /* ������   */
  e_UsrRxLcAppNew = 2,  /* ������   */
  e_UsrRxLcAppOld = 3,  /* ������   */
  e_UsrRxLcMsgErr = 4,  /* ���ݴ��� */ /* �������ݳ���������󳤶� */
  e_UsrRecvCfgErr = 5,  /* ���ô��� */ /* �û��ṩ������� */
  e_UsrRxErrDev   = 6   /* �����豸 */
}E_UsrRxStatus;

typedef enum TAG_UsrTxStatus
{
  e_UsrTxSuccess   = 1,  /* ���ͳɹ� */
  e_UsrTxErrDev    = 2,  /* �����豸 */
  e_UsrTxErrData   = 3,  /* �������� */ /* ��ָ��or���ݳ��� */
  e_UsrTxErrRepeat = 4,  /* �ظ����� */
  e_UsrTxErrStatus = 5   /* ����״̬ */ /* �������������״̬��Vcp�豸�������� */
}E_UsrTxStatus;

/*�����豸���ڵ�ϸ��*/
typedef struct TAG_DevDetail
{
  GM_UINT16 DevType; /*[2 byte] �豸����           */
  UINT8  DevCab ; /*[1 byte] �豸�Ĳ�����     */
  UINT8  DevPos ; /*[1 byte] �豸�Ĳ��λ��     */
  UINT8  AccCab ; /*[1 byte] ����Ĳ�����     */
  UINT8  AccPos ; /*[1 byte] ����Ĳ���λ��     */
  UINT8  AccSys ; /*[1 byte] �����ϵ��         */
  UINT8  AppId  ; /*[1 byte] ָʾ�豸��"Ӧ��ID" */
}T_DevDetail;

/* �����豸������Ϣ */
typedef struct TAG_DevExInfo
{
  UINT32 TxMsgLen; /*[4 byte] �豸���ͳ���   */
  UINT32 RxMsgLen; /*[4 byte] �豸���ճ���   */
  UINT32 SendNum ; /*[4 byte] �豸���͹ܵ��� */
  UINT32 RecvNum ; /*[4 byte] �豸���չܵ��� */
}T_DevExInfo;

/*����һ��VCP�豸����Ϣ*/
typedef struct TAG_SysDevInf
{
  T_DevDetail    Detail; /*[8 byte]*/
  E_SysDevStatus Status; /*[4 byte]*/
}T_SysDevInf;

/*�豸�汾��Ϣ*/
typedef struct TAG_UsrDevVerInf
{
  /*����Id����*/
  #define c_VCP_ManIdLen (10UL)

  UINT32    SwProc               ; /*�ں˳�������汾��*/
  UINT32    SwComm               ; /*ͨ�ų�������汾��*/
  T_RealClk Date                 ; /*��������          */
  UINT32    HwVer                ; /*Ӳ���汾��        */
  UINT8     ManId[c_VCP_ManIdLen]; /*�������          */
  UINT8     Reserve[2]           ; /*Ԥ��              */
}T_UsrDevVerInf;

/*�����豸������ϸ��Ϣ*/
typedef struct TAG_DevCfgDetail
{
  /*����豸������*/
  #define c_VCP_MaxDevNameLen (16UL)

  CHARACTER    DevName[c_VCP_MaxDevNameLen]; /* �豸��   */
  T_DevDetail  BasicInfo                   ; /* ������Ϣ */
  T_DevExInfo  ExInfo                      ; /* ������Ϣ */
}T_DevCfgDetail;

/*�����û�ָʾ��*/
#define c_UsrIndicatorA (0xAAUL)
#define c_UsrIndicatorB (0xBBUL)

/*�����û�ָʾ������*/
#define c_UsrIndicatorOff (0UL)
#define c_UsrIndicatorOn  (1UL)

/*��ѯ�������������ļ���ʶ*/
#define c_InquiryLoc (0UL)
/*��ѯ��һϵ���������ļ���ʶ*/
#define c_InquiryRem (1UL)

/* ���ϵ�以�����ݳ��� */
#define c_VCP_MaxMutualDataLen4Eth (100UL * 1024UL)
#define c_VCP_MaxMutualDataLen4Flr (1200UL)

/******************************************************************************
*    CSP Variable Declare Section BIGEN
******************************************************************************/

typedef enum enum_extern_eth_comm_protocal_type
{
	ENUM_EXT_ETH_COMM_TYPE_INVALID = 0x00U,      /*��Ч����*/
	ENUM_EXT_ETH_COMM_TYPE_RAW     = 0x55U,      /*��Э��*/
	ENUM_EXT_ETH_COMM_TYPE_RSSP1   = 0xAAU,      /*RSSP-1Э��*/
	ENUM_EXT_ETH_COMM_TYPE_RSSP2   = 0xBBU       /*Ԥ��RSSP-2Э��*/ 

}ENUM_TYPE_EXTERN_ETH_COMM_PROTOCAL;




/*�뵱ǰCI�豸ͨ�ŵ��豸ͨ��״̬�ṹ��*/
typedef struct  CommunicationDevStatus
{
	UINT8 DeviceIdCiLocal;					/*������ID*/
	UINT8 DeviceTypeOther;					/*�Է��豸����*/
	UINT8 ComDevSum;						    /*�������豸����*/
	UINT8 ComDevIdBuf[COM_DEV_MAX];			/*�������豸*/
	UINT8 ComDevIdComStatusBuf[COM_DEV_MAX];	/*�������豸ͨ��״̬*/
}ADPTER_PACKED CommunicationDevStatusStruct;


typedef struct
{
	GM_UINT16  Index;                      /*������:16*/
	GM_UINT16  Des_Source_ID;           /*Ŀ�ĵ�ַ:16*/
	UINT8   SFM_State;                  /*SFM״̬: 4*/
	UINT8   Des_MS_State;            /*Զ���豸������Ϣ: 4*/
	UINT8   Udp_Chn_Num;             /*UDPͨ����Ŀ: 4*/
	UINT8   Udp_Chn_State;           /*UDPͨ��״̬: 8*/
}ADPTER_PACKED  APP_RSSPI_COMM_STATE;


/******************************************************************************
*    CSP Variable Declare Section END
******************************************************************************/





/******************************************************************************
*    Global Variable Declare Section
******************************************************************************/


/******************************************************************************
*    Global Prototype Declare Section
******************************************************************************/
/******************************************************************************
 *Name    : F_VCP_UsrDataWatch
 *Function: �ṩ���û�ÿ�����ڽ��е������ݼ��Ľӿ�
 *          (������ε���ʱ�ı����ڵ��ۼ�ʵʱ���ݳ����Ѿ�����1400�ֽ��򱾺���
 *           ����Դ˴����ݽ��з���,������e_FALSE)
 *Para    : @inData    : Ϊ��Ϣ�����׵�ַ
 *          @inDataLen : Ϊ��Ϣ���ݳ���(���ֽ�Ϊ��λ)
 *Return  : ����ɹ��򷵻�e_TRUE, ���򷵻�e_FALSE
 *Note    :
******************************************************************************/
E_SysBool F_VCP_UsrDataWatch(const UINT8* const inData,
                             const UINT32       inDataLen);


/******************************************************************************
 *Name    : F_VCP_UsrDataRecv
 *Function: ���û��ṩ�������豸ָʾ(���ṩinDevType��inAppId ��inDevSys)��ɻ�
 *          ��ָ���豸�����ݣ�����(���ṩinDevType��inAppId)�ɻ����ϵ�豸�����ݡ�
 *          �û���ȡ���ݳɹ���ͬ�������ٴλ�ȡ��ͬ�豸�����ݣ�
 *          ������᷵�������ظ���ʶ(e_RxLcAppOld).
 *Para    : @inDevType : �����豸���߼�����
 *          @inAppId   : �����豸��Ӧ��ID
 *          @inDevSys  : �����豸������ϵ��
 *          @ioMsg     : ����/������ݵĻ���,��ṹ����:
 *                      typedef  struct TAG_CellMsg
 *                      {
 *                        UINT8*  ptrMsg ; [>Out: �洢���׵�ַ               <]
 *                        UINT32  dataLen; [>I/O: �洢������/�洢�������ݳ���<]
 *                      } T_CellMsg;
 *Return  : ���� E_UsrRxStatus, ָʾ��ȡ���ݵ�״̬
 *           . e_UsrRxLcEmpty  = 1, �߼�ͨ������Ϊ��
 *           . e_UsrRxLcAppNew = 2, �߼�ͨ��(�û�)��ϢΪ��
 *           . e_UsrRxLcAppOld = 3, �߼�ͨ��(�û�)��ϢΪ��
 *           . e_UsrRxLcMsgErr = 4, �߼�ͨ������Ϣ����
 *           . e_UsrRecvCfgErr = 5  �û��ṩ�Ľ���������Ϣ����
 *Note    :
 ******************************************************************************/
E_UsrRxStatus F_VCP_UsrDataRecv(const UINT32 inDevType,
                                const UINT32 inAppId,
                                const UINT32 inDevSys,
                                T_CellMsg*   ioMsg);

/******************************************************************************
 *Name    : F_VCP_UsrDataRecvEx
 *Function: ���ָ���豸������ ��ǿ��
 *Para    : @inDevType: �����豸���߼�����
 *          @inAppId  : �����豸��Ӧ��ID
 *          @inDevSys : �����豸������ϵ��
 *          @inPipeId : ����ܵ���
 *          @ioUsrBuff: ����/������ݵĻ���
 *Return  : ���� E_UsrRxStatus, ָʾ��ȡ���ݵ�״̬
 *Note    :
 ******************************************************************************/
E_UsrRxStatus F_VCP_UsrDataRecvEx(const UINT32 inDevType,
                                  const UINT32 inAppId,
                                  const UINT32 inDevSys,
                                  const UINT32 inPipeId,
                                  T_UsrBuff*   ioUsrBuff);


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
E_UsrRxStatus F_VCP_UsrDataRecvMutual(T_CellMsg* const ioMsg);


/******************************************************************************
 *Name    : F_VCP_UsrDataSend
 *Function: ��ָ���豸��������
 *Para    : @inDevType: �����豸���߼�����
 *          @inAppId  : �����豸��Ӧ��ID
 *          @inDevSys : �����豸������ϵ��
 *          @inData   : �����û��ṩ���ڴ����ݵĻ���
 *          @inDataLen: �����û��ṩ��������ݵĳ���
 *Return  : ���ͳɹ�=>����e_TRUE, ���򷵻�e_TRUE
 *Note    : ��������ͬһ�豸�ظ�����
******************************************************************************/
E_SysBool F_VCP_UsrDataSend(const UINT32 inDevType,
                            const UINT32 inAppId,
                            const UINT32 inDevSys,
                            const void*  inData,
                            const UINT32 inDataLen);




/******************************************************************************
 *Name    : F_VCP_UsrDataSendEx
 *Function: ��ָ���豸�������� ��ǿ��
 *Para    : @inDevType: �����豸���߼�����
 *          @inAppId  : �����豸��Ӧ��ID
 *          @inDevSys : �����豸������ϵ��
 *          @inPipeId : ����ָ���Ĺܵ���[0-14], �Ƕ�ܵ��豸��0
 *          @inData   : �����û��ṩ���ڴ����ݵĻ���
 *          @inDataLen: �����û��ṩ��������ݵĳ���
 *Return  : ����״̬
 *Note    : ��������ͬһ�豸�ظ�����
 ******************************************************************************/
E_UsrTxStatus F_VCP_UsrDataSendEx(const UINT32 inDevType,
                                  const UINT32 inAppId,
                                  const UINT32 inDevSys,
                                  const UINT32 ProtocolType,
                                  const void*  inData,
                                  const UINT32 inDataLen);



/******************************************************************************
 *Name    : F_VCP_UsrDataSendMutual
 *Function: �����û��������û��������ݵĽӿ�
 *Para    : @inData    : ��������
 *          @inDataLen : �������ݵĳ���
 *Return  : �ɹ��򷵻�e_TRUE, ���򷵻�e_TRUE��
 *Note    : һ���������ظ����ã�ֻ�������һ������
******************************************************************************/
E_SysBool F_VCP_UsrDataSendMutual(const void* const inData,
                                  const UINT32      inDataLen);

/******************************************************************************
 *Name    : F_VCP_UsrHaltSystem
 *Function: ���û������жϳ����ش������ҪֹͣӦ�ô���ʱ���ô˽ӿں�����
 *          ���������洢���ϴ���(�Ա��û�����ά��)����5���ں���ִֹ���û�Ӧ�ô�
 *          �����
 *Para    : @inErrCode: ������ϴ���
 *Return  : void
 *Note    :
 *C.A.0002  YanGuang  2013/04/17  �޸�ԭ���
 *                                �����������ڿ�ʼ��ִֹ���û�Ӧ�ô������
 *                                ��Ϊ ��������ִֹ���û�Ӧ�ô������
******************************************************************************/
void F_VCP_UsrHaltSystem(const UINT32 inErrCode);


/******************************************************************************
 *Name    : F_VCP_DevInfSummary
 *Function: �û��ɲ�ѯ����VCP�豸�ĵ�ǰ״̬
 *Para    : @outDevInfArray: �������VCP�豸״̬�����飬״̬��������
 *           . e_SysDevNotExist =1, �豸������
 *           . e_SysDevInit     =2, �豸��ʼ��
 *           . e_SysDevTran     =3, �豸����״̬
 *           . e_SysDevNormal   =4, �豸����״̬
 *           . e_SysDevFault    =5  �豸����״̬
 *          @ioDevInfTotal : �����û��ṩ���������
 *                           �������VCP�豸������(����ָʾ��һ���βε����鳤��)

 *Return  : void
 *Note    :
 *C.A.0002  YanGuang  2013/04/17  ���β���outDevInfTotal��ΪioDevInfTotal
******************************************************************************/
void  F_VCP_DevInfSummary(T_SysDevInf* const outDevInfArray,
                          UINT32* const      ioDevInfTotal);



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
T_SysDevInf F_VCP_InquiryDevStatus(const UINT32 inDevType,
                                   const UINT32 inAppId,
                                   const UINT32 inClique);


/******************************************************************************
 *Name    : F_VCP_InquirySwVersion
 *Function: �ṩ���û���ѯ�������������汾��ͨ������汾�Ľӿ�
 *Para    : @inDevType      : �����豸���߼�����
 *          @inAppId        : �����豸��Ӧ�ñ��
 *          @inAccSys       : �����豸����ϵ���ʶ
 *          @outProcVersion : �����������汾
 *          @outCommVersion : ���ͨѶ����汾
 *
 *          |  �汾��ʶ  |  �汾����  |  ������  |  �汾���  |
 *          |-- 1 Byte --|-- 1 Byte --|-- 1 Byte --|-- 1 Byte --|
 *          �汾��ʶ��'V'
 *          �汾���ͣ�'A' - 'Z'
 *          �汾��ţ�1 - 15
 *          �����ţ���ʽ�汾��0
 *                    ���԰汾��'a' - 'z'
 *
 *          ��ʾʾ����
 *          0x56 -> 'V'
 *          0x43 -> 'C'
 *          0x61 -> 'a'
 *          0x56430001UL -> V.C.0001   ��ʽ��
 *          0x56436101UL -> V.C.0001a  ���԰�
 *
 *Return  : �����ѯ��ȷ�򷵻�e_TRUE, ����e_FALSE
 *Note    :
******************************************************************************/
E_SysBool  F_VCP_InquirySwVersion(const UINT32  inDevType,
                                  const UINT32  inAppId,
                                  const UINT32  inAccSys,
                                  UINT32* const outProcVersion,
                                  UINT32* const outCommVersion);


/******************************************************************************
 *Name    : F_VCP_SystemClkGet
 *Function: �ṩ���û���ȡϵͳʱ�ӵĽӿ�
 *Para    : @outSysClk: �����ǰϵͳʱ��(���ʽ����:)
 *          typedef  struct TAG_SysClk
 *          {
 *            UINT32 Sec ; [>[4 Byte] ����  <]
 *            UINT32 uSec; [>[4 Byte] ΢����<]
 *          }T_SysClk;
 *Return  : void
 *Note    :
******************************************************************************/
void  F_VCP_SystemClkGet(T_SysClk* const outSysClk);


/******************************************************************************
 *Name    : F_VCP_CalendarClkGet
 *Function: �ṩ���û���ȡ����ʱ�ӵĽӿ�
 *Para    : @outClk: �������ʱ��(���ʽ����:)
 *          typedef  struct TAG_CalendarClk
 *          {
 *            UINT32 Year    ;  [>[4 Byte] ���  <]
 *            UINT32 Mon     ;  [>[4 Byte] �·�  <]
 *            UINT32 Day     ;  [>[4 Byte] ����  <]
 *            UINT32 Hour    ;  [>[4 Byte] Сʱ  <]
 *            UINT32 Min     ;  [>[4 Byte] ����  <]
 *            UINT32 Sec     ;  [>[4 Byte] ����  <]
 *            UINT32 MiSec   ;  [>[4 Byte] ������<]
 *            UINT32 WeekDay ;  [>[4 Byte] ���ڼ�<]
 *          }T_CalendarClk;
 *Return  : void
 *Note    :
 *****************************************************************************/
E_SysBool  F_VCP_CalendarClkGet(T_CalendarClk* const outClk);


/******************************************************************************
 *Name    : F_VCP_CalendarClkSet
 *Function: ���ṩ���û���������ʱ�ӵĽӿ�(ע���ֶ�WeekDay�û����Բ���д)
 *Para    : @inClk: ��������ʱ��(���ʽ����:)
 *          typedef  struct TAG_CalendarClk
 *          {
 *            UINT32 Year    ;  [>[4 Byte] ���  <]
 *            UINT32 Mon     ;  [>[4 Byte] �·�  <]
 *            UINT32 Day     ;  [>[4 Byte] ����  <]
 *            UINT32 Hour    ;  [>[4 Byte] Сʱ  <]
 *            UINT32 Min     ;  [>[4 Byte] ����  <]
 *            UINT32 Sec     ;  [>[4 Byte] ����  <]
 *            UINT32 MiSec   ;  [>[4 Byte] ������<]
 *            UINT32 WeekDay ;  [>[4 Byte] ���ڼ�<]
 *          }T_CalendarClk;
 *Return  : ���óɹ�����e_TRUE,���򷵻�e_FALSE
 *Note    : 2���ں���Ч
******************************************************************************/
E_SysBool  F_VCP_CalendarClkSet(const T_CalendarClk* const inClk);


/******************************************************************************
 *Name    : F_VCP_GetSystemId
 *Function: �ṩ���û���ȡϵ����Ϣ�Ľӿ�
 *Para    : @outSysId: ���ϵ����Ϣ
 *           . 0x01��Iϵ;
 *           . 0x02��IIϵ;
 *Return  : void
 *Note    :
******************************************************************************/
void  F_VCP_GetSystemId(UINT32* const outSysId);


/******************************************************************************
 *Name    : F_VCP_GetMasterId
 *Function: �ṩ���û���ȡ����ϵ����Ϣ�Ľӿ�
 *Para    : @outSysId: ���ϵ����Ϣ
 *           . 0x01��Iϵ;
 *           . 0x02��IIϵ;
 *Return  : void
 *Note    :
******************************************************************************/
void  F_VCP_GetMasterId(UINT32* const outSysId);


/******************************************************************************
 *Name    : F_VCP_GetHwVersion
 *Function: �ṩ���û���ȡӲ���汾�ŵĽӿ�
 *Para    : @outHwVersion : ���Ӳ���汾�� Ҫ��outHwVersion�Ǹ�CHAR���鳤��Ϊ8
 *Return  : void
 *Note    :
******************************************************************************/
void F_VCP_GetHwVersion(CHAR* const outHwVersion);


/******************************************************************************
 *Name    : F_VCP_GetVcpId
 *Function: �ṩ���û���ȡƽ̨Id�Ľӿ�
 *Para    : @outVcpId : ���VcpId
 *Return  : void
 *Note    :
******************************************************************************/
void F_VCP_GetVcpId(UINT32* const outVcpId);


/******************************************************************************
 *Name    : F_VCP_UsrIndicator
 *Function: �ṩ���û�����ָʾ���Ľӿ�
 *Para    : @inIndicatorNo : �����û�ָʾ����
 *          @inAction      : ���붯��
 *Return  : ������������ȷ����e_TRUE�����򷵻�e_FALSE
 *Note    :
******************************************************************************/
E_SysBool F_VCP_UsrIndicator(const UINT32 inIndicatorNo,
                             const UINT32 inAction);


/******************************************************************************
 *Name    : F_VCP_UsrInquiryParamVersion
 *Function: �ṩ���û���ѯ�����ļ��Ľӿ�
 *Para    : @inTarget        : �����ѯĿ��
 *          @outParamVersion : ��������ļ��汾
 *          @outParamCrc     : ��������ļ�Crc
 *          @inParamCrcLen   : �����û��ṩ�Ĵ�������ļ�Crc�ڴ泤��
 *Return  : �����ѯ��ȷ����e_TRUE�����򷵻�e_FALSE
 *Note    :
 ******************************************************************************/
E_SysBool F_VCP_UsrInquiryParamVersion(const UINT32 inTarget,
                                       UINT32*      outParamVersion,
                                       UINT8        outParamCrc[],
                                       const UINT32 inParamCrcLen);


/******************************************************************************
 *Name    : F_VCP_GetDevVerInf
 *Function: �û����������VCP�豸ָ����Ϣ��ȡVCP�豸�İ汾��Ϣ
 *Para    : @inDevType    : �����豸���߼�����
 *          @inAppId      : �����豸��Ӧ�ñ��
 *          @inDevSys     : �����豸����ϵ���ʶ
 *          @outDevVerInf : ����豸�汾��Ϣ
 *Return  : ��ȡ���豸�İ汾��Ϣ������e_TRUE�����򷵻�e_FALSE
 *Note    :
******************************************************************************/
E_SysBool F_VCP_GetDevVerInf(const UINT32     inDevType,
                             const UINT32     inAppId,
                             const UINT32     inDevSys,
                             T_UsrDevVerInf*  outDevVerInf);


/******************************************************************************
 *Name    : F_VCP_GetLocBspVersion
 *Function: �ṩ���û���ȡBsp�汾�ŵĽӿ�
 *Para    : @outBspVersion : ���Bsp�汾��
 *Return  : void
 *Note    :
******************************************************************************/
void F_VCP_GetLocBspVersion(UINT32* const outBspVersion);


/******************************************************************************
 *Name    : F_VCP_GetDevCfgDetail
 *Function: ��ȡ��ϸ�豸����
 *Para    : @inListLen           : �����豸�б���
 *          @outDevCfgDetailList : ����豸�б�
 *          @outDevNum           : ����豸�б����豸��
 *Return  : �����豸������
 *Note    : ����豸�б��Ȳ���, ֻ�����inListLen���豸����
 *          ����ֵ���ܴ���outDevNum
 ******************************************************************************/
UINT32 F_VCP_GetDevCfgDetail(const UINT32   inListLen,
                             T_DevCfgDetail outDevCfgDetailList[],
                             UINT32*        outDevNum);



/***************************************began***************************************
 *����CSPƽ̨�Ĳ��������ͷ�ļ���
  Modified by Suomingyu 
  ��������ͷ�ļ������ݽṹ���Լ�������������	
 ***********************************************************************************/
GM_BOOL  CSPADPT_App_Initialization(void);

GM_BOOL  CSPADPT_App_Main(void);

UINT32* CSPADPT_Get_Main_Cycle_Ptr(void);

QueueStruct* CSPADPT_Get_Cbtc_Send_Que_Ptr();

QueueStruct* CSPADPT_Get_Cbtc_Rcv_Que_Ptr();

QueueStruct* CSPADPT_Get_APP_LOG_Ptr();

ENUM_TYPE_EXTERN_ETH_COMM_PROTOCAL CSPADPT_Get_External_Comm_Protocal_Type(void);

UINT8 CSPADPT_Get_OppoMachine_State(void);

UINT8 CSPADPT_Get_Local_Machine_Id(void);

GM_BOOL  CSPADPT_Log_Record_Pack(UINT8*  m_Msg_Ptr, UINT32 m_Msg_Length);

#endif