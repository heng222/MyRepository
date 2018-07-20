/********************************************************
*                                                                                                            
* 文 件 名： Copy.h
* 版权说明：  
* 创建时间： 2013-10-25
* 作    者： 
* 功能描述： 复制函数头文件
* 修改记录：   
*
********************************************************/
#ifndef COPY_H_
#define COPY_H_

#include "CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


/* 函数功能 : 内存拷贝函数。
*  参数说明 : void *pDest, 目的地址
*             UINT32_S destBuffSize, 缓冲区长度，最大可用拷贝的数据长度
*             const void *pSrc, 源地址
*             UINT32_S count, 拷贝长度
*  返回值:    1, 未拷贝，拷贝长度大于报警长度
*             0, 拷贝成功
*/
UINT8_S MemoryCpy(void *pDest, UINT32_S destBuffSize, const void *pSrc, UINT32_S count);









#ifdef __cplusplus
}
#endif

#endif
