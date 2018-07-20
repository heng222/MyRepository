/********************************************************
*                                                                                                            
* 文 件 名： AdptAppFileInterface.h   
* 作    者： 董欣 
* 创建时间： 2016-09-01
* 功能描述： 平台适配层提供给应用的接口头文件 
* 备    注： 无 
*
********************************************************/ 

#ifndef ADPT_APP_FILE_INTERFACE_H_
#define ADPT_APP_FILE_INTERFACE_H_


#include "../../Common/CommonTypes.h"
#include "../PlatItf/AdptPlatFileInterface.h"

#define FILE_WRITE_PRO_ERROR     0u
#define FILE_WRITE_PRO_SUCC      1u
#define FILE_WRITE_PRO_WRITTING  2u


#ifdef __cplusplus
extern "C" {
#endif

/* 
*  功能描述：  设置应用所需的配置文件名字
*  参数说明:str1        第一个文件的名称
*            str2        第二个文件的名称
*  返回值:    无
*/
UINT8_S AdptAppSetCfgFileName(CHAR_S name1[],UINT8_S nameLen1, CHAR_S name2[],    UINT8_S nameLen2);

/*
*  功能描述：判断文件是否存在函数
*  参数说明:const CHAR* fileName  文件名称
*  返回值:    1存在   0 不存在
*/
UINT8_S AdptAppFileExist(const CHAR_S* fileName);

/*
*  功能描述：获取文件信息
*  参数说明:inFileName    : 输入文件名
*           outFileDetail : 输出文件信息(可以为ptrNULL)
*  返回值:    1获取成功   0 获取失败
*/
UINT8_S AdptAppFileInquire(const CHAR_S* fileName, AdptFileDetailStruct* outFileDetail);

/*
*  功能描述：  文件打开函数
*  参数说明:
*  输入参数: const char* fileName        输入文件名
*            const UINT8 openMode        文件打开方式        
*                    0,  读方式打开文件
*                    1,  写新文件方式打开文件, 带校验
*                    2,  写新文件方式打开文件, 无校验
*                    3,  文件信息交换
*  输出参数: *pfile                句柄
*  返回值:    1成功   0 失败
*/
UINT32_S AdptAppFileOpen(const CHAR_S* fileName, const UINT8_S openMode,FILEType *pfile);

/*
*  功能描述： 文件读取函数
*  参数说明:  const FILEType pfile     输入句柄
*             const CHAR* fileName     输入文件名
*             UINT8* dataBuf           输出数据存储缓存
*             UINT32_S count             数据存储缓存区大小
*  返回值:    0 读取失败   >0 文件大小
*/
UINT32_S AdptAppFileRead (const FILEType pfile, const CHAR_S* fileName, UINT8_S* dataBuf, UINT32_S count);

/*
*  功能描述：文件写函数
*  参数说明:  const FILEType* fileHUsr, 文件句柄
*             const UINT32_S writeLen,    写入数据长度
*             UINT8Type writeDataBuf,   写入数据缓存
*  返回值:    1写成功   0 写失败
*/
UINT8_S AdptAppFileWrite(const FILEType fileHUsr, const UINT32_S writeLen, UINT8_S * writeDataBuf);

/*
*  功能描述：  文件关闭函数
*  参数说明:FILEType *pfile                文件句柄
*  返回值:    1成功   0 失败
*/
UINT8_S AdptAppFileClose(FILEType fileHUsr);

/*
*  功能描述：文件删除函数
*  参数说明:const CHAR* fileName  输入文件名称
*           FILEType* fileHUsr    输出句柄
*  返回值:    1删除成功   0 删除失败
*/
UINT8_S AdptAppFileDelete(const CHAR_S* fileName, FILEType* fileHUsr);

/*
*  功能描述：  读文件操作
*  参数说明:   UINT8* pBuff,       输出读取的数据
*              UINT32_S buffLength,  输出读取数据长度
*  返回值:       readDataLen,0读取失败;>0读取成功
*/
UINT32_S AdptAppFileReadProc(UINT8_S* buff, UINT32_S buffLength);

/*
*  功能描述：  写文件操作
*  参数说明:   UINT8* pBuff, UINT32_S buffLength
*  返回值:       returnValue，文件写入操作所处的状态
*                0,失败
*                1,成功
*                2,处理中
*/
UINT8_S AdptAppCycleWriteFile(UINT8_S* pBuff, UINT32_S buffLength);

#ifdef __cplusplus
}
#endif

#endif



