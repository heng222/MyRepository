/******************************************************************************
 *File Name         :    Vcp_File_Interface.h
 *Copyright         :    Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :    2014/02/15
 *Module Id      :  SD-SM_PAB-1012
 *Description    :    SM�ṩ���й�PAB���ļ������ӿ�
 *                  �Կ⺯������ʽ�ṩ
 *
 *+----------+---------------------------------------------------------------+
 *| Design   |    �����ͨ�ź�ϵͳͨ�ð�ȫ�����ƽ̨�������SM_PAB           |
 *|  File    |    �����ϸ���˵����Vcp_File_Interface���_B.1               |
 *+----------+--------------+------------+-----------------------------------+
 *| Version  |    Author    |    Date    |            Description            |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0001 | ZhuHui       | 2014/02/15 |  File Create                      |
 *+----------+--------------+------------+-----------------------------------+
 *
 ******************************************************************************/

#include "Vcp_File_Interface.h"

static unsigned int  FileDataLen = 0u;



/******************************************************************************
 *Name      : F_VCP_FileExist
 *Function  : ��ѯ�ļ��Ƿ����
 *Para      : @inFileName : �����ļ���
 *Return    : ����ļ����ڷ���e_TRUE�����򷵻�e_FALSE
 *Note      :
 ******************************************************************************/
E_SysBool F_VCP_FileExist(const CHARACTER* inFileName)
{
	E_SysBool retVal = e_FALSE;
#if 0 /* TODO FILE*/
    FILE *retIsExit = NULL;/*�ļ��Ƿ����*/

    retIsExit = fopen(inFileName, "r");

    if (retIsExit!=NULL)
    {
        retVal = e_TRUE;
    } 
    else
    {
		retVal = e_FALSE;
    }
 #endif 
    return retVal;
}


/******************************************************************************
 *Name      : F_VCP_FileInquire
 *Function  : ��ȡ�ļ���Ϣ
 *Para      : @inFileName    : �����ļ���
 *            @outFileDetail : ����ļ���Ϣ(����ΪptrNULL)
 *Return    : �����ȡ�ɹ�=>����e_TRUE�����򷵻�e_FALSE
 *Note      : ��һ��������д���ļ��ú�����Ч
 ******************************************************************************/
E_SysBool F_VCP_FileInquire(const CHARACTER*  inFileName,
                            T_VCP_FileDetail* outFileDetail)
{
	E_SysBool retVal = e_TRUE;

	(*outFileDetail).Size = FileDataLen;

	return retVal;
}


/******************************************************************************
 *Name      : F_VCP_FileOpen
 *Function  : ���ļ�(R/W/E)
 *Para      : @inFileName : �����ļ���
 *            @inOpenOpt  : ���������
 *            @outHUsr    : ����û��ļ����
 *Return    : ���ش�״̬
 *Note      :
 ******************************************************************************/
INT32  F_VCP_FileOpen(const CHARACTER*        inFileName,
                     const E_VCP_FileOpenOpt inOpenOpt,
                     INT32* const pfile)

{
	INT32  retVal = c_VCP_FOpenErrFatal;
	#if 0 /* TODO FILE*/
	FILE *tempVal = NULL;

    switch (inOpenOpt)
    {
        case e_VCP_FOpenRead:
            tempVal = fopen(inFileName,"rb");
            break;
		case e_VCP_FOpenWrite:
            tempVal = fopen(inFileName,"wb");
            break;
        default:
            break;
    }

    if (NULL!= tempVal)
    {
        retVal = c_VCP_FOpenOk;
    } 
    else
    {
		retVal = c_VCP_FOpenErrFatal;
    }

	*pfile = (INT32)&tempVal;
#endif
	return retVal;
}


/******************************************************************************
 *Name      : F_VCP_FileRead
 *Function  : ��ȡ�ļ�
 *Para      : @pfile     : �����û����
 *            @inReadLen  : �����ȡ����
 *            @inReadBuff : �����ȡ���ݻ���
 *Return    : ���ض�ȡ״̬
 *Note      : �����HUsr֮ǰ�Ķ������Ѿ���ɣ�������Ӧ�˴�����
 ******************************************************************************/
INT32  F_VCP_FileRead(INT32  pfile,
                     const unsigned int  inReadLen,
                     UINT8*       inReadBuff)
{
	unsigned int  dataLen = 0;/*��ȡ���ݳ���*/
    
	INT32  retRead = c_VCP_FReadErrFatal;/*��ȡ�Ƿ�ɹ�*/
	#if 0 /* TODO FILE*/
FILE *tempVal = NULL;
	FileDataLen = 0u;
    if (inReadBuff != NULL)
    {
        dataLen = fread(inReadBuff,sizeof(UINT8),inReadLen,pfile);
		if (dataLen > 0 )
		{
			FileDataLen = dataLen;
			retRead = c_VCP_FReadDone;
		}
    }
#endif
    return retRead;
}



/******************************************************************************
 *Name      : F_VCP_FileWrite
 *Function  : д���ļ�
 *Para      : @inHUsr      : �����û����
 *            @inWriteLen  : ����д�볤��
 *            @inWriteBuff : ����д�����ݻ���
 *Return    : ����д��״̬
 *Note      :
 ******************************************************************************/
INT32  F_VCP_FileWrite(const INT32  fileHUsr,
                      const unsigned int  inWriteLen,
                      UINT8*       inWriteBuff)
{
	INT32  retVal = c_VCP_FWriteErrFatal;/*��������ֵ*/
	unsigned int  retLen = 0;/*�ļ�д����ֵ*/
#if 0
    retLen = fwrite(inWriteBuff, inWriteLen,1, (FILE *)fileHUsr);
#endif
    if (retLen > 0)
    {
        retVal = c_VCP_FWriteDone;
    } 
    else
    {
		retVal = c_VCP_FWriteErrFatal;
    }

	return retVal;
}



/******************************************************************************
 *Name      : F_VCP_FileClose / F_VCP_FileCloseExt
 *Function  : �رվ��
 *Para      : @inHUsr    : �����û����
 *            @inIsForce : �����Ƿ�ǿ�ƹر� (��Ч����)
 *Return    : ���عر�״̬
 *Note      : Ϊ��������, ��������Ϊ������������
 *            F_VCP_FileClose    : �����ڽ׶�, ϵͳ�������ͷž��
 *            F_VCP_FileCloseExt : �����ڽ׶�, ϵͳ���������ͷž��
 ******************************************************************************/
INT32  F_VCP_FileClose(const INT32 fileHUsr,
                      const E_SysBool inIsForce)
{
	INT32  retVal = c_VCP_FCloseErrFatal;
	INT32  retClose = 0;/*�ر��Ƿ�ɹ�*/
#if 0
    retClose = fclose((FILE *)fileHUsr);
#endif
    if (0 == retClose)
    {
		retVal = c_VCP_FCloseFinish;
    } 
    else
    {
		retVal = c_VCP_FCloseErrFatal;
    }
	return retVal;
}


/******************************************************************************
 *Name      : F_VCP_FileDelete
 *Function  : ɾ���ļ�
 *Para      : @inFileName : �����ļ���
 *            @outHUsr    : ����û����
 *Return    : ����ɾ��״̬
 *Note      :
 ******************************************************************************/
INT32  F_VCP_FileDelete(const CHARACTER* inFileName,
						 INT32*           fileHUsr)
{
	INT32  retVal = c_VCP_FDeleteErrFatal;
	INT32  retDelete = 0;/*�ļ�ɾ������ֵ*/
#if 0
    retDelete = remove(inFileName);
#endif
    if (0 == retDelete)
    {
		retVal = c_VCP_FDeleteFinish;
    } 
    else
    {
		retVal = c_VCP_FDeleteErrFatal;
    }
	return retVal;
}


/******************************************************************************
 *Name      : F_VCP_FileStatusInquire / F_VCP_FileStatusInquireExt
 *Function  : ��ѯ�ļ����״̬
 *Para      : @inHUsr         : �����û����
 *            @outProgress    : �������
 *            @outOperateInfo : ���������Ϣ
 *Return    : �����ļ������Ӧ״̬
 *Note      : 1. Ϊ��֤������, F_VCP_FileStatusInquire��ѯ����c_VCP_FInqFinish��
 *               ��ֵ, ƽ̨�������ͷž��
 *            2. Ϊ�����û�ʹ��, F_VCP_FileStatusInquireExt�κ������,
 *               ƽ̨�����ͷž��, ��Ҫ�û�ͨ��F_VCP_FileHandleRelease�ͷ�
 ******************************************************************************/
INT32  F_VCP_FileStatusInquire(const INT32     fileHUsr,
                              T_VCP_Progress* outProgress)
{
	INT32  retVal = c_VCP_FInqFinish;
	return retVal;
}



/******************************************************************************
 *Name      : F_VCP_FileHandleRelease
 *Function  : �ͷž��
 *Para      : @inHUsr : �����û����
 *Return    : �����ļ�����ͷ�״̬
 *Note      :
 ******************************************************************************/
INT32  F_VCP_FileHandleRelease(const INT32 fileHUsr)
{
	INT32  retVal = c_VCP_FRlsSuccess;
	return retVal;
}



/******************************************************************************
 *Name      : F_VCP_FileExInfoInquire
 *Function  : ��ѯ�������ļ���Ϣ
 *Para      : @inHUsr    : �����û����
 *            @outExInfo : ���������Ϣ
 *Return    : ��������ȷ����e_TRUE�����򷵻�e_FALSE
 *Note      :
 ******************************************************************************/
E_SysBool F_VCP_FileExInfoInquire(const INT32        inHUsr,
                                  T_VCP_FileExInfo* outExInfo)
{
	E_SysBool retVal = e_FALSE;
	if(NULL != outExInfo)
	{
		outExInfo->OperateInfo.Status = c_VCP_FInqErrHandle;
		outExInfo->ExistInfo.Detail.Size = FileDataLen;
	    retVal = e_TRUE;
	}
	return retVal;
}
								  

/******************************************************************************************* 
*�������ܣ� CSP�����ģ�� ��ȡUserConfigArea�׵�ַ����ַΪCSPƽ̨��������ַ    
                                                                             
*����˵���� ��          
                                                                       
*����ֵ��   ��                                                                            
*******************************************************************************************/ 

VOID* CSPADPT_Get_User_Config_Addr(void)
{
	VOID* l_Config_Area = NULL;
	l_Config_Area = sdRgnAddrGet("UserConfigArea");   /*CSP API*/
	
	return l_Config_Area;

}
/******************************************************************************************* 
*�������ܣ� CSP�����ģ�� ��ȡȫ�����ñ�ṹ��
                                                                             
*����˵���� ��          
                                                                       
*����ֵ��   ��                                                                            
*******************************************************************************************/ 


APP_CONFIG_HEAD* CSPADPT_Get_App_Config_File_Head(void)
{
	return (APP_CONFIG_HEAD*)&g_App_Config_Head;
}

/******************************************************************************************* 
*�������ܣ������ģ�飬�����ļ����ͻ�ȡ�����ļ��洢��ַ������                                                                                  
*����˵����    
 	        ENUM_TYPE_CONFIG_DAT m_Type �����ļ�����
 	        UINT8* m_Addr  �ļ��洢��ַ�Ļ���
 	        UINT32* m_Size �ļ����Ȼ���
 	        UINT8* m_Addr  ��ȡ���ļ��洢��ַ
 	        UINT32* m_Size ��ȡ���ļ�����                                                                              
*����ֵ�� l_Result                                                                                    
*******************************************************************************************/ 

GM_BOOL CSPADPT_Get_SpeciConfig_Addr_Size(ENUM_TYPE_CONFIG_DAT m_Type, UINT8* m_Addr, UINT32* m_Size)
{
	GM_BOOL l_Result = GM_FALSE;	
	APP_CONFIG_HEAD* l_Config_File_Head_Ptr = NULL;
	APP_CONFIG_PER_FILE_HEAD* l_Per_File_Head_Ptr = NULL;	
	UINT32 l_Offset = 0U;
	UINT32 l_Index = 0U;	
	UINT8* l_Addr = NULL;


	l_Config_File_Head_Ptr = CSPADPT_Get_App_Config_File_Head();

	if(l_Config_File_Head_Ptr == NULL 
		|| l_Config_File_Head_Ptr->phymemaddr == 0U 
		|| m_Addr == NULL 
		|| m_Size == NULL)
		
		{
				printf("CSPADPT_Get_SpeciConfig_Addr_Size no File_Head\n");
				return l_Result;
			}
	
	for(l_Index = 0U; l_Index < l_Config_File_Head_Ptr->filenum && l_Index < MAX_CFG_FILE_NUMBER; l_Index++)
	{
		l_Per_File_Head_Ptr = &l_Config_File_Head_Ptr->perfile[l_Index];
		if(l_Per_File_Head_Ptr->filetype == m_Type)
		{

			*(UINT32*)m_Addr  = l_Config_File_Head_Ptr->phymemaddr + 
				l_Per_File_Head_Ptr->fileoffset + 
				sizeof(APP_CONFIG_PER_FILE_HEAD)*l_Config_File_Head_Ptr->filenum + 1U;

			*(UINT32*)m_Size = l_Per_File_Head_Ptr->filesize;

			l_Result = GM_TRUE;
			break;
		}


	}	

	/*printf("CSPADPT_Get_SpeciConfig_Addr_Size result is %d\n",l_Result);*/
	return l_Result;	


}


								  
