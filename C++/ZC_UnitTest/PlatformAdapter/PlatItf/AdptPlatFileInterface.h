/********************************************************
* 
* 文 件 名： AdptPlatFileInterface.h
* 作    者： 董欣 
* 创建时间： 2016-09-01 
* 功能描述： 适配层提供给平台层的文件操作接口头文件  
* 备    注： 无 
* 
********************************************************/ 

#ifndef ADPT_PLAT_FILE_INTERFACE_H_
#define ADPT_PLAT_FILE_INTERFACE_H_

#include "AdptPlatBasicTypeDefinition.h"
#include "../../Common/CommonTypes.h"

/*查询操作状态 */
/*完成                        */
/*R: 读关闭成功               */
/*W: 写关闭并校验成功         */
/*D: 删完成                   */
#define FILE_INQ_FINISH       1u
/*完成申请打开/读/写          */
#define FILE_INQ_REQ_DONE     2u
/*操作执行失败                */
#define FILE_INQ_ERR_FATAL    3u
/*无效的句柄                  */
#define FILE_INQ_ERR_HANDLE   4u


/******************************************************************************
 *    Global Struct    Define Section
 ******************************************************************************/
/*定义文件打开方式*/
typedef enum AdptFileOpenOption
{
  AdptFOpenRead        = 0u,  /*读方式打开文件              */
  AdptFOpenWrite       = 1u,  /*写新文件方式打开文件, 带校验*/
  AdptFOpenWriteNCheck = 2u,  /*写新文件方式打开文件, 无校验*/
  AdptFOpenExchange    = 3u   /*文件信息交换                */
}AdptFileOpenOpt;

/*进度*/
typedef struct AdptProgress
{
  UINT32_S Total;     /* 总任务量             */
  UINT32_S Done;      /* 总完成量             */
  UINT32_S LastQuota; /* 最后一次申请的任务量 */
}AdptProgressStruct;

/*定义文件详细信息*/
typedef struct AdptFileDetail
{
  UINT32_S     Size ;  /*文件大小    */
  AdptRealClkStruct  CTime;  /*创建时间    */
  AdptRealClkStruct  LTime;  /*最后访问时间*/
}AdptFileDetailStruct;


#ifdef __cplusplus
extern "C" {
#endif

/*
*  功能描述：判断文件是否存在函数
*  参数说明:const CHAR* fileName  文件名称
*  返回值:    1存在   0 不存在
*/
UINT8_S AdptPlatFileExist(const CHAR_S* fileName);

/*
*  功能描述：获取文件信息
*  参数说明:  inFileName    : 输入文件名
*             outFileDetail : 输出文件信息(可以为ptrNULL)
*  返回值:    1获取成功   0 获取失败
*  注: 对一个打开正在写的文件该函数无效
*/
UINT8_S AdptPlatFileInquire(const CHAR_S* fileName, AdptFileDetailStruct* outFileDetail);

/*
*  功能描述：  文件打开函数
*  参数说明:const char* fileName        文件的地址
*            const UINT8 openMode        文件打开方式        
*            FILEType *pfile                句柄
*  返回值:    1成功   0 失败
*/
UINT8_S AdptPlatFileOpen(const CHAR_S* fileName, const UINT8_S openMode, FILEType *pfile);


/*
*  功能描述： 文件读取函数
*  参数说明:    const FILEType pfile                
*            const CHAR* fileName        二进制文件
*            UINT8* dataBuf                数据存储缓存
            UINT32 count                缓存大小
*  返回值:    0 读取失败   >0 文件大小
*/
UINT32_S AdptPlatFileRead (const FILEType pfile,const CHAR_S* fileName,UINT8_S* dataBuf, UINT32_S count);


/*
*  功能描述：文件写函数
*  参数说明:const FILEType* fileHUsr,const UINT32 writeLen,UINT8Type writeDataBuf
*  返回值:    1写成功   0 写失败
*/
UINT8_S AdptPlatFileWrite(const FILEType fileHUsr, const UINT32_S writeLen, UINT8_S *writeDataBuf);


/*
*  功能描述：  文件关闭函数
*  参数说明:FILEType *pfile                句柄或文件
*  返回值:    1成功   0 失败
*/
UINT8_S AdptPlatFileClose(FILEType fileHUsr);

/*
*  功能描述：  文件释放句柄 
*  参数说明:FILEType *pfile                句柄或文件
*  返回值:    1成功   0 失败
*/
UINT8_S AdptPlatFileRelease(FILEType fileHUsr);

/*
*  功能描述：文件删除函数
*  参数说明:const CHAR* fileName  文件名称
*  返回值:    1删除成功   0 删除失败
*/
UINT8_S AdptPlatFileDelete(const CHAR_S* fileName, FILEType* fileHUsr);



/*
*  功能描述：查询文件句柄状态
*  参数说明:   fileName  文件名称
*              outProgress 输出进度
*  返回值:   查询操作状态
*/
UINT8_S AdptPlatFileStatusInquire(const FILEType inHUsr, AdptProgressStruct* outProgress);

/*
*  功能描述：查询另一机的文件状态和大小 
*  参数说明:   inHUsr  文件句柄 
*              outStatus 文件状态 
*              size 文件大小
*  返回值:   0 查询失败  1 查询成功
*/
UINT8_S AdptPlatFileExcStatusInquire(const FILEType inHUsr, UINT8_S* outStatus, UINT32_S* size);

#ifdef __cplusplus
}
#endif

#endif

