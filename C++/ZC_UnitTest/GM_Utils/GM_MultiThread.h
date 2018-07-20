/**
* @file GM_MultiThread.h
* @brief ʵ���˿�ƽ̨(Windows, Linux, VxWorks, ReWorks)�̡߳����⡢�źţ�sleep
* @author 
* @date 
* @version

*/

#ifndef _GM_MULTITHREAD_H
#define _GM_MULTITHREAD_H

#include "GM_MultiThread_Priority.h"

#ifdef WIN32
#include <PROCESS.H>
#include <WINSOCK2.H>
#endif

#ifdef VXWORKS
#include <taskLib.h>
#endif

#ifdef QNX
#include <pthread.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif /**< __cplusplus */

#ifdef WIN32
    typedef unsigned        GM_THREAD;
    typedef unsigned        GM_THREAD_FUNC_RETURN;
    typedef GM_THREAD_FUNC_RETURN(__stdcall* GM_THREAD_FUNC)(void* args);
#define GM_THREAD_CALL __stdcall
#endif
#ifdef QNX
    typedef pthread_t       GM_THREAD;
    typedef void*           GM_THREAD_FUNC_RETURN;
    typedef GM_THREAD_FUNC_RETURN(* GM_THREAD_FUNC)(void* args);
#define GM_THREAD_CALL
#endif
#ifdef VXWORKS
    typedef int             GM_THREAD;
    typedef int             GM_THREAD_FUNC_RETURN;
    typedef FUNCPTR         GM_THREAD_FUNC;
#define GM_THREAD_CALL
#endif

#define GM_THREAD_RETRUN static GM_THREAD_FUNC_RETURN GM_THREAD_CALL

	/** ���������Խṹ��  */
	typedef struct
	{
		int	priority;	/*���߳����ȼ�*/
		int	StackSize;	/*��ջ��С*/
		GM_THREAD	Thread;	/*�½��߳̾��*/
	}GM_PACKED GM_Thread_Property_Struct;

    /** ������ڲ����ṹ��  */
    typedef struct
    {
        int args0;
        int args1;
        int args2;
        int args3;
        int args4;
        int args5;
        int args6;
        int args7;
        int args8;
        int args9;
    }GM_PACKED GM_Thread_Arg_Struct;

    /**
    * @brief GM_Thread_Create
    *
    * @param[out] thread �߳̾��(��ΪNULL������߳̾��)
    * @param[in] myfunc �̺߳���
    * @param[in] threadName �߳���(��VxWorks�õ�)
    * @param[in] stackSize �̶߳�ջ��С(VxWorks��Windows����)
    * @param[in] priority ���ȼ�(VxWorks��Windows����) GM_TASK_PRIORITY_0 �� GM_TASK_PRIORITY_99
    * @param[in] args ����
    * @return GM_BOOL
    */
    GM_BOOL GM_Thread_Create(GM_THREAD* thread, GM_THREAD_FUNC myfunc, const char* threadName, int stackSize, int priority, const GM_Thread_Arg_Struct* pArgs);

    /**
    * @brief GM_Thread_Self
    *
    * @return GM_THREAD
    */
    GM_THREAD GM_Thread_Self(void);

#ifdef __cplusplus
}

#endif /**< __cplusplus */

#endif /**< _GM_MULTITHREAD_H */

