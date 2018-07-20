/********************************************************
*                                                                                                            
* 文件名  ： CommonQueue.h   
* 版权说明： 
* 版 本 号： 1.0
* 创建时间： 2008.07.29
* 作    者： 
* 功能描述： 队列函数实现  
* 使用注意： 1.本队列适用的应用方式有(单任务应用），（两任务并行），（一个应用+一个中断）。
*            2 本队列支持的两任务或者中断函数必须是一读一写，不支持两个任务同时读或者两个任务同时写
*            3 申请足够空间防止队列写满。
*            4 请不要输入 0 qsize。
*            5 如果多任务或者中断情况下，如果空间小于两帧数据的容量，会发生死锁：数据长度不够读，剩余空间又不够写，发生死锁
*   
* 修改记录：   
*
********************************************************/ 
#ifndef COMMONQUEUE_H_
#define COMMONQUEUE_H_

#include "CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif


/*以下部分为队列相关的定义*/
typedef  UINT8_S   QueueElement;
typedef struct SQueueStruct
{
    UINT32_S in; /* 写队列数据指针 */
    UINT32_S out; /* 读队列数据指针 */
    UINT32_S qsize; /*队列容量*/
    QueueElement *q; /*队列数据*/
} QueueStruct;


/*
* 功能描述： 队列初始化函数，用于初始化一个队列，与QueueElementFree配对使用
*            为队列结构体中的q分配空间，并将队列的size初始化
* 参数说明： QueueStruct *pQueue,    待分配空间的队列
*            UINT32_S QSize,           队列需要的长度
* 返回值  ： 1，成功
*            0，失败
*/
UINT8_S QueueInitial(QueueStruct *pQueue, UINT32_S QSize);


/*
* 功能描述： 队列初始化函数，用于初始化一个队列
*            QSize初始化，与QueueInitial相比，采用传入的空间作为队列元素的空间。
* 参数说明： QueueStruct *pQueue,               待分配空间的队列
*            UINT32_S QSize,                      队列需要的长度
*            QueueElement pQueueElementSpace[], 队列需要的内存空间
* 返回值  ： 1，成功
*            0，失败
* 使用注意： 1，确认pQueueElementSpace数组的大小大于等于QSize，以免异常。
*            2，如果使用这个函数初始化，则不再调用QueueElementFree进行空间释放。
*/
UINT8_S StaticQueueInitial(QueueStruct *pQueue, UINT32_S QSize,QueueElement pQueueElementSpace[]);

/*
* 功能描述： 队列扫描函数，可以读出队列中的数据，但是对队列的读写指针都不产生影响，即读到的数据还在队列中
* 参数说明： UINT32_S DataLen,              要读出的数据长度;
*            QueueElement *pData,         读出的数据要存放的数组;
*            QueueStruct *pQueue,         要读出数据的队列
* 返回值：   1，成功
*            0，失败，队列数据长度不够
*/
UINT8_S QueueScan(UINT32_S DataLen,QueueElement *pData,const QueueStruct *pQueue);


/*
* 功能描述： 读队列函数，可以读出队列中的数据,并存放在一个数组中，数据读出后读指针发生变化，即读出的数据已不存在队列中
* 参数说明： UINT32_S  DataLen,                 要读出的数据长度;
*            QueueElement     *pData,         读出的数据要存放的数组;
*            QueueStruct *pQueue,             要读出数据的队列
* 返回值 ：  1，成功
*            0，失败，队列数据长度不够
*/
UINT8_S QueueRead(UINT32_S DataLen, QueueElement *pData,QueueStruct *pQueue);

/*
* 功能描述： 清队列函数，把队列中的in，out值置0
* 参数说明： QueueStruct *pQueue， 需要清的队列指针
* 返回值：   1，成功
*/
UINT8_S QueueClear(QueueStruct *pQueue);

/*
*    功能描述： 读出队列中可用数据长度
*    参数说明： QueueStruct *pQueue,        要读出的数据长度的队列;
*    返回值  ： 返回队列中可用的数据长度，如果队列为空，返回0
*/
UINT32_S QueueStatus (const QueueStruct *pQueue);

/*
* 功能描述： 写队列函数，将一个数组中的数据写到一个队列中
*            对一个队列的操作不可以两个任务同时写入
*            队列是不可以写满的，如果写不下函数返回0
* 参数说明： UINT32_S  DataLen,             要写入的数据长度;
*            QueueElement *pData,         要写入的数据存放的数组;
*            QueueStruct *pQueue,         要写入数据的队列
* 返回值 ：  1，成功
*            0，失败,队列已满
*/
UINT8_S QueueWrite(UINT32_S DataLen,const QueueElement *pData,QueueStruct *pQueue);

/*
* 函数描述： 队列存储空间释放函数
*            在不需要某个队列的时候，把队列的元素数组空间释放掉,与QueueInitial配对使用
* 参数说明： QueueStruct *pQueue,       队列
* 返回值  ： 1，成功
*/
UINT8_S QueueElementFree(QueueStruct *pQueue);

/*
* 功能描述： 在队列中删除一定的元素。
* 参数说明： UINT16_S Length,             要删除的元素个数
*            QueueStruct *pQueue,       要删除元素的队列
* 返回值 ：  1，成功
*            0，失败
*/
UINT8_S QueueElementDiscard( UINT16_S Length, QueueStruct *pQueue);

/*
*    功能描述： 读出队列中可用空间大小
*    参数说明： QueueStruct *pQueue,  指定的队列
*    返回值  ： 返回队列中可用的空间大小,由于队列不能写满，最大可用空间为qsize-1
*/
UINT32_S QueueGetSpace (const QueueStruct *pQueue);

#ifdef __cplusplus
}
#endif

#endif
