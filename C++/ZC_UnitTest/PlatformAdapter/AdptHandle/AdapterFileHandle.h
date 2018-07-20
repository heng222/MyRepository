/********************************************************
*                                                                                                            
* 文 件 名： AdapterFileHandle.h   
* 作    者： 董欣 
* 创建时间： 2016-09-01
* 功能描述： 平台适配层文件操作头文件 
* 备    注： 无 
*
********************************************************/ 

#ifndef ADAPTER_FILE_HANDLE_H_
#define ADAPTER_FILE_HANDLE_H_


#include "../../Common/CommonTypes.h"
#include "../PlatItf/AdptPlatFileInterface.h"
#include "../PlatItf/AdptPlatBasicTypeDefinition.h"
#include "../PlatItf/AdptPlatFileInterface.h"

#define FileWriteCycMax     20u                /*写文件超时门限(周期号)*/
#define FILE_NAME_MAX_LEN   32u                /*文件名长度*/

 /*当前操作文件的状态*/
typedef enum FileStatus
{
    e_File_First = 1u,
    e_File_Second = 2u
}E_FileStatus;


/*写文件操作状态转移定义*/
typedef enum WriteStatus
{
    e_Init   = 1u,
    e_Open   = 2u,
    e_Write  = 3u,
    e_Delete = 4u,
    e_Close  = 5u,
    e_Error  = 6u,
    e_Sync   = 7u,
    e_Sucess = 8u
}E_WriteStatus;

#ifdef __cplusplus
extern "C" {
#endif

/*
*  功能描述：  设置文件操作所需的配置文件名字
*  参数说明:str1        第一个文件的名称
*            str2        第二个文件的名称
*  返回值:    无
*/
UINT8_S AdapterSetCfgFileName(CHAR_S name1[],UINT8_S nameLen1, CHAR_S name2[],  UINT8_S nameLen2);

/*
*  功能描述：  读文件操作,从两个文件中选取最新的读取
*  参数说明:   UINT8* pBuff,       输出读取的数据
*              UINT32_S buffLength,  输出读取数据长度
*  返回值:       readDataLen,0读取失败;>0读取成功
*/
UINT32_S AdapterFileReadProc(UINT8_S* buff, UINT32_S buffLength);


/*
*  功能描述：  多周期循环写文件操作
*  参数说明:   UINT8* pBuff,       输入写文件数据
*              UINT32_S buffLength， 输入写文件数据长度
*  返回值:       returnValue，文件写入操作所处的状态
*/
E_WriteStatus AdapterCycleWriteFile(UINT8_S* pBuff, UINT32_S buffLength);


#ifdef __cplusplus
}
#endif

#endif
