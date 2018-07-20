/********************************************************
*                                                                                                            
* 文 件 名： CommonQueue.c   
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
*            6 本队列最大支持4g的数据，但是使用者应根据平台情况酌情申请空间。
* 修改记录：   
*
********************************************************/ 

#include "CommonQueue.h"
#include "stdlib.h"


/*
* 功能描述： 队列初始化函数，用于初始化一个队列，与QueueElementFree配对使用
*            为队列结构体中的q分配空间，并将队列的size初始化
* 参数说明： QueueStruct *pQueue,    待分配空间的队列
*            UINT32_S QSize,           队列需要的长度
* 返回值  ： 1，成功
*            0，失败
*/
UINT8_S QueueInitial(QueueStruct *pQueue, UINT32_S QSize)
{
    UINT8_S bRet = 0;

    /*对输入值进行判断*/
    if((NULL != pQueue)&&(0!=QSize))
    {
        /*输入值合法*/

        /* in=out=0， 队列清空 */
        pQueue->in = 0; 
        pQueue->out = 0;    
        pQueue->qsize = QSize;
        pQueue->q = (QueueElement* ) malloc(sizeof(QueueElement) * pQueue->qsize);
        if(pQueue->q != NULL)
        {
            /*成功初始化*/

            bRet =    1 ;
        }
        else
        {
            bRet =    0 ;
        }
    }
    else
    {
        /*输入值不合法*/

        bRet =    0 ;
    }

    return bRet;

}


/*
* 功能描述： 队列初始化函数，用于初始化一个队列
*            QSize初始化，与QueueInitial相比，采用传入的空间作为队列元素的空间。
* 参数说明： QueueStruct *pQueue,               待分配空间的队列
*            UINT32_S QSize,                      队列需要的长度
*            QueueElement pQueueElementSpace[], 队列需要的内存空间
* 返 回 值： 1，成功
*            0，失败
* 使用注意： 1，确认pQueueElementSpace数组的大小大于等于QSize，以免异常。
*            2，如果使用这个函数初始化，则不再调用QueueElementFree进行空间释放。
*/
UINT8_S StaticQueueInitial(QueueStruct *pQueue, UINT32_S QSize,QueueElement pQueueElementSpace[])
{
    UINT8_S bRet = 0;

    /*对输入值进行判断*/
    if((NULL != pQueue)&&(0!=QSize))
    {
        /*输入值合法*/

        /* in=out=0， 队列清空 */
        pQueue->in = 0; 
        pQueue->out = 0;    
        pQueue->qsize = QSize;

        pQueue->q = pQueueElementSpace;     /*%RELAX<MISRA_17_6>*/
        bRet =    1 ;

    }
    else
    {
        /*输入值不合法*/
        bRet =    0 ;
    }

    return bRet;    
}

/*
* 功能描述： 队列扫描函数，可以读出队列中的数据，但是对队列的读写指针都不产生影响，即读到的数据还在队列中
* 参数说明： UINT32_S DataLen,              要读出的数据长度;
*            QueueElement *pData,         读出的数据要存放的数组;
*            QueueStruct *pQueue,         要读出数据的队列
* 返回值：   1，成功
*            0，失败，队列数据长度不够
*/
UINT8_S QueueScan(UINT32_S DataLen,QueueElement *pData,const QueueStruct *pQueue)
{
    register UINT32_S i,j;
    register QueueElement *pOut;
    UINT8_S bRet = 0u;

    /*如果队列中的数据不够读就返回错误,必须防止读出0个数据*/
    if( (QueueStatus(pQueue)<DataLen) || (DataLen == 0) )         
    {
        bRet =    0 ; 
    }
    else
    {

        if((NULL != pData) && (NULL != pQueue) && (NULL != pQueue->q))
        {
            /*到达此处必然能够保证读到必须的数据*/
            pOut =    & ( pQueue->q[pQueue->out] );
            j = pQueue->qsize - (pQueue->out);

            /*由于已经能够判定有足够的数据，不需要再对in值进行判断*/
            if( j >= DataLen )        
            {
                /*不翻转可以读完数据    */
                for(i=0;i<DataLen;i++)
                {
                    *pData = *pOut;
                    pData++;
                    pOut++;
                }             
            } 
            else
            {     
                /*不翻转不能读完数据*/

                /*读到队列尾*/
                for(i=0;i<j ;i++)     
                {
                    *pData = *pOut;
                    pData++;
                    pOut++;
                } 

                /*将out指针指向头*/
                pOut = & pQueue->q[0];     

                /*从队列头开始读剩下的数*/
                for(;i<DataLen;i++) 
                {
                    *pData = *pOut;
                    pData++;
                    pOut++;
                } 

            }     
            bRet =    1u ;
        
        }
    }


    return bRet; /* 返回1，读数据成功 */    
}


/*
* 功能描述： 读队列函数，可以读出队列中的数据,并存放在一个数组中，数据读出后读指针发生变化，即读出的数据已不存在队列中
* 参数说明： UINT32_S  DataLen,                 要读出的数据长度;
*            QueueElement     *pData,         读出的数据要存放的数组;
*            QueueStruct *pQueue,             要读出数据的队列
* 返回值 ：  1，成功
*            0，失败，队列数据长度不够
*/
UINT8_S QueueRead(UINT32_S DataLen, QueueElement *pData,QueueStruct *pQueue)
{
    register UINT32_S i,j;
    register QueueElement *pOut;
    UINT8_S bRet = 0u;

    /*如果队列中的数据不够读就返回错误,必须防止读出0个数据*/
    if( (QueueStatus(pQueue)<DataLen) || (DataLen == 0) )         
    {
        bRet =    0 ; 
    }
    else
    {

        if((NULL != pData) && (NULL != pQueue) && (NULL != pQueue->q))
        {
            /*到达此处必然能够保证读到必须的数据*/
            pOut =    & ( pQueue->q[pQueue->out] );
            j = pQueue->qsize - (pQueue->out);

            /*由于已经能够判定有足够的数据，不需要再对in值进行判断*/
            if( j > DataLen )        
            {
                /*不翻转可以读完数据    */

                for(i=0;i<DataLen;i++)
                {
                    *pData = *pOut;
                    pData++;
                    pOut++;
                }             
                pQueue->out += DataLen;                    
            } 
            else 
            {       
                /*j<=DataLen 不翻转不能读完数据*/

                /*读到队列尾*/
                for(i=0;i<j;i++)     
                {
                    *pData = *pOut;
                    pData++;
                    pOut++;
                }     

                /*将out指针指向头*/
                pOut = & pQueue->q[0];     

                /*从队列头开始读剩下的数*/
                for(;i<DataLen;i++)
                {
                    *pData = *pOut;
                    pData++;
                    pOut++;
                }

                pQueue->out = DataLen - j;     
            }     
            bRet =    1 ;

        
        }

    }
    return bRet; /* 返回1，读数据成功 */    
}

/*
* 功能描述： 清队列函数，把队列中的in，out值置0
* 参数说明： QueueStruct *pQueue， 需要清的队列指针
* 返回值：   1，成功
*/
UINT8_S QueueClear(QueueStruct *pQueue)
{
    UINT8_S retVal  = 0u;
    if(NULL != pQueue)
    {
        /* in=out=0 队列清空 */
        pQueue->in = 0u; 
        pQueue->out = 0u; 
    	retVal = 1u;
    
    }
    return    retVal ;
}

/*
*    功能描述： 读出队列中可用数据长度
*    参数说明： QueueStruct *pQueue,        要读出的数据长度的队列
*    返回值  ： 返回队列中可用的数据长度，如果队列为空，返回0
*/
UINT32_S QueueStatus (const QueueStruct *pQueue)
{
    UINT32_S qStatus = 0u;
    UINT32_S retVal = 0u;

	if(NULL != pQueue)
    {
        if(pQueue->qsize!=0)
        {
            qStatus=(pQueue->in+pQueue->qsize-pQueue->out)%pQueue->qsize;
            retVal = qStatus;
        }
        else
        {
            /*此处程序出现错误，返回0，此处逻辑不严密*/
            retVal = 0u;
        }
    
    }
    return retVal;
}

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
UINT8_S QueueWrite(UINT32_S DataLen,const QueueElement *pData,QueueStruct *pQueue)
{
    register UINT32_S i,j;
    register QueueElement *pIn;
    UINT8_S bRet = 0u;

    /*先判断队列是否有能够的空间容纳写入的数据,如果队列要满了，就不允许写了 */
	if((NULL != pData) && (NULL != pQueue) && (NULL != pQueue->q))
    {
        if( DataLen >= (pQueue->qsize - QueueStatus(pQueue)) )
        {
            bRet =    0 ;    
        }
        else
        {

            /*由于已经能够判定有足够的空间，不需要再对out值进行判断*/
            j =    pQueue->qsize- (pQueue->in); 
            pIn =    & ( pQueue->q[pQueue->in] );

            if( j > DataLen )        
            { 
                /*写入时可以不用翻转*/

                /*用自加指令可以明显提高指令的执行速度*/
                for(i=0;i<DataLen;i++)
                {
                    *pIn = *pData;    
                    pIn++;
                    pData++;
                }

                pQueue->in += DataLen;    
            }
            else /*j <= DataLen*/
            {    
                /*写入过程中必然翻转*/

                /*将数据从当前指针到缓冲区尾部，写入的长度为j*/
                for(i=0;i<j;i++) 
                {
                    *pIn = *pData;    
                    pIn++;
                    pData++;
                }

                /*已经写到缓冲区尾部了，应该从缓冲区头开始写起*/
                pIn = & pQueue->q[0];

                /*从队列头开始写，i的初始值为j——即为上次写到缓冲区尾的长度 */
                for(;i<DataLen;i++)     
                {
                    *pIn = *pData;    
                    pIn++;
                    pData++;
                }

                /*调整队列的in指针为写入的总长度减去写到缓冲区尾的数据长度*/
                pQueue->in = DataLen - j;                
            }
            bRet= 1 ;
        }    
    }
    return bRet; 
}

/*
* 函数描述： 队列存储空间释放函数
*            在不需要某个队列的时候，把队列的元素数组空间释放掉,与QueueInitial配对使用
* 参数说明： QueueStruct *pQueue,       队列
* 返回值  ： 1，成功
*/
UINT8_S QueueElementFree(QueueStruct *pQueue)
{

    UINT8_S ret = 0u;

	if(NULL != pQueue)
    {
        /*队列指针归位*/
        pQueue->in = 0; 
        pQueue->out = 0;
        pQueue->qsize = 0;

        /*释放队列空间*/
        if(pQueue->q != NULL )
        {
            #ifdef SYS_TYPE_WINDOWS
            free(pQueue->q);
            #endif
            pQueue->q = NULL;
        	ret = 1u;
        }
    }
    return ret ;
}

/*
* 功能描述： 在队列中删除一定的元素。
* 参数说明： UINT16_S Length,             要删除的元素个数
*            QueueStruct *pQueue,       要删除元素的队列
* 返回值 ：  1，成功
*/
UINT8_S QueueElementDiscard( UINT16_S Length, QueueStruct *pQueue)
{
    UINT8_S bRet = 0u;

    
    if(NULL != pQueue)
    {
        /* 如果传入的字节数比元素个数还要大*/
        if( QueueStatus(pQueue) < Length)
        {
            QueueClear(pQueue);
        } 
        else
        {
            pQueue->out = (pQueue->out + Length) % pQueue->qsize;
        }
        
        bRet=1;
    }
    return bRet;
}

/*
*    功能描述： 读出队列中可用空间大小
*    参数说明： QueueStruct *pQueue,  指定的队列
*    返回值  ： 返回队列中可用的空间大小,由于队列不能写满，队列中有一个空间不能用
*/
UINT32_S QueueGetSpace (const QueueStruct *pQueue)
{
    UINT32_S qSpace = 0u;
    UINT32_S retVal = 0u;

	if(NULL != pQueue)
    {
        if(pQueue->qsize != 0u)
        {
            qSpace =(pQueue->out+pQueue->qsize-pQueue->in-1)%pQueue->qsize;
            retVal = qSpace;
        }
        else
        {
            /*此处程序出现错误，返回0，此处逻辑不严密*/
            qSpace = 0u;
            retVal = qSpace;
        }
    }
    return retVal;
}

