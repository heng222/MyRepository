/******************************************************************************
 *File Name         :    Vcp_File_Interface.h
 *Copyright         :    Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :    2014/02/15
 *Module Id      :  SD-SM_PAB-1012
 *Description    :    SM提供的有关PAB的文件操作接口
 *                  以库函数的形式提供
 *
 *+----------+---------------------------------------------------------------+
 *| Design   |    轨道交通信号系统通用安全计算机平台主机插件SM_PAB           |
 *|  File    |    软件详细设计说明书Vcp_File_Interface组件_B.1               |
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
 *Function  : 查询文件是否存在
 *Para      : @inFileName : 输入文件名
 *Return    : 如果文件存在返回e_TRUE，否则返回e_FALSE
 *Note      :
 ******************************************************************************/
E_SysBool F_VCP_FileExist(const CHARACTER* inFileName)
{
	E_SysBool retVal = e_FALSE;
#if 0 /* TODO FILE*/
    FILE *retIsExit = NULL;/*文件是否存在*/

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
 *Function  : 获取文件信息
 *Para      : @inFileName    : 输入文件名
 *            @outFileDetail : 输出文件信息(可以为ptrNULL)
 *Return    : 如果获取成功=>返回e_TRUE，否则返回e_FALSE
 *Note      : 对一个打开正在写的文件该函数无效
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
 *Function  : 打开文件(R/W/E)
 *Para      : @inFileName : 输入文件名
 *            @inOpenOpt  : 输入打开类型
 *            @outHUsr    : 输出用户文件句柄
 *Return    : 返回打开状态
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
 *Function  : 读取文件
 *Para      : @pfile     : 输入用户句柄
 *            @inReadLen  : 输入读取长度
 *            @inReadBuff : 输入读取数据缓冲
 *Return    : 返回读取状态
 *Note      : 必须此HUsr之前的读请求已经完成，才能响应此次请求
 ******************************************************************************/
INT32  F_VCP_FileRead(INT32  pfile,
                     const unsigned int  inReadLen,
                     UINT8*       inReadBuff)
{
	unsigned int  dataLen = 0;/*读取数据长度*/
    
	INT32  retRead = c_VCP_FReadErrFatal;/*读取是否成功*/
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
 *Function  : 写入文件
 *Para      : @inHUsr      : 输入用户句柄
 *            @inWriteLen  : 输入写入长度
 *            @inWriteBuff : 输入写入数据缓冲
 *Return    : 返回写入状态
 *Note      :
 ******************************************************************************/
INT32  F_VCP_FileWrite(const INT32  fileHUsr,
                      const unsigned int  inWriteLen,
                      UINT8*       inWriteBuff)
{
	INT32  retVal = c_VCP_FWriteErrFatal;/*函数返回值*/
	unsigned int  retLen = 0;/*文件写返回值*/
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
 *Function  : 关闭句柄
 *Para      : @inHUsr    : 输入用户句柄
 *            @inIsForce : 输入是否强制关闭 (无效参数)
 *Return    : 返回关闭状态
 *Note      : 为了向后兼容, 两函数行为上有如下区别
 *            F_VCP_FileClose    : 非周期阶段, 系统会主动释放句柄
 *            F_VCP_FileCloseExt : 非周期阶段, 系统不会主动释放句柄
 ******************************************************************************/
INT32  F_VCP_FileClose(const INT32 fileHUsr,
                      const E_SysBool inIsForce)
{
	INT32  retVal = c_VCP_FCloseErrFatal;
	INT32  retClose = 0;/*关闭是否成功*/
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
 *Function  : 删除文件
 *Para      : @inFileName : 输入文件名
 *            @outHUsr    : 输出用户句柄
 *Return    : 返回删除状态
 *Note      :
 ******************************************************************************/
INT32  F_VCP_FileDelete(const CHARACTER* inFileName,
						 INT32*           fileHUsr)
{
	INT32  retVal = c_VCP_FDeleteErrFatal;
	INT32  retDelete = 0;/*文件删除返回值*/
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
 *Function  : 查询文件句柄状态
 *Para      : @inHUsr         : 输入用户句柄
 *            @outProgress    : 输出进度
 *            @outOperateInfo : 输出操作信息
 *Return    : 返回文件句柄对应状态
 *Note      : 1. 为保证兼容性, F_VCP_FileStatusInquire查询返回c_VCP_FInqFinish或
 *               负值, 平台会主动释放句柄
 *            2. 为方便用户使用, F_VCP_FileStatusInquireExt任何情况下,
 *               平台不会释放句柄, 需要用户通过F_VCP_FileHandleRelease释放
 ******************************************************************************/
INT32  F_VCP_FileStatusInquire(const INT32     fileHUsr,
                              T_VCP_Progress* outProgress)
{
	INT32  retVal = c_VCP_FInqFinish;
	return retVal;
}



/******************************************************************************
 *Name      : F_VCP_FileHandleRelease
 *Function  : 释放句柄
 *Para      : @inHUsr : 输入用户句柄
 *Return    : 返回文件句柄释放状态
 *Note      :
 ******************************************************************************/
INT32  F_VCP_FileHandleRelease(const INT32 fileHUsr)
{
	INT32  retVal = c_VCP_FRlsSuccess;
	return retVal;
}



/******************************************************************************
 *Name      : F_VCP_FileExInfoInquire
 *Function  : 查询交换的文件信息
 *Para      : @inHUsr    : 输入用户句柄
 *            @outExInfo : 输出交换信息
 *Return    : 如果句柄正确返回e_TRUE，否则返回e_FALSE
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
*函数功能： CSP适配层模块 获取UserConfigArea首地址，地址为CSP平台数据区地址    
                                                                             
*参数说明： 无          
                                                                       
*返回值：   无                                                                            
*******************************************************************************************/ 

VOID* CSPADPT_Get_User_Config_Addr(void)
{
	VOID* l_Config_Area = NULL;
	l_Config_Area = sdRgnAddrGet("UserConfigArea");   /*CSP API*/
	
	return l_Config_Area;

}
/******************************************************************************************* 
*函数功能： CSP适配层模块 获取全局配置表结构体
                                                                             
*参数说明： 无          
                                                                       
*返回值：   无                                                                            
*******************************************************************************************/ 


APP_CONFIG_HEAD* CSPADPT_Get_App_Config_File_Head(void)
{
	return (APP_CONFIG_HEAD*)&g_App_Config_Head;
}

/******************************************************************************************* 
*函数功能：适配层模块，根据文件类型获取单个文件存储地址及长度                                                                                  
*参数说明：    
 	        ENUM_TYPE_CONFIG_DAT m_Type 配置文件类型
 	        UINT8* m_Addr  文件存储地址的缓存
 	        UINT32* m_Size 文件长度缓存
 	        UINT8* m_Addr  获取的文件存储地址
 	        UINT32* m_Size 获取的文件长度                                                                              
*返回值： l_Result                                                                                    
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


								  
