/**
* @file GM_MultiThread.c
* @brief ʵ���˿�ƽ̨���̡߳����⡢�źŹ���.Linux�µ��߳����ȼ�������Ҫ����
* @author 
* @date 
* @version

*/
#include "GM_MultiThread.h"

#ifdef WIN32
GM_BOOL GM_Thread_Create(GM_THREAD* thread, GM_THREAD_FUNC myfunc, const char* threadName, int stackSize, int priority, const GM_Thread_Arg_Struct* pargs)
{
	GM_THREAD tmpThread = 0u;
	GM_BOOL rt          = GM_FALSE;
	unsigned int ThrAddr = 0u;

	if (stackSize < 0)
	{
		return GM_FALSE;
	}
	if ((priority != THREAD_PRIORITY_HIGHEST)&&(priority != THREAD_PRIORITY_ABOVE_NORMAL)
		&&(priority != THREAD_PRIORITY_NORMAL)&&(priority != THREAD_PRIORITY_BELOW_NORMAL)
		&&(priority != THREAD_PRIORITY_LOWEST)&&(priority != THREAD_PRIORITY_IDLE))
	{
		return GM_FALSE;
	}

	tmpThread = (GM_THREAD)_beginthreadex(NULL, stackSize, myfunc, pargs, 0, &ThrAddr);

	if (tmpThread > 0u)
	{
		rt = SetThreadPriority(tmpThread, priority);

		if ((rt == GM_TRUE)&&(thread != NULL))
		{
			*thread = tmpThread;
		}
		return rt;
	}
	else
	{
		return GM_FALSE;
	}
}

GM_THREAD GM_Thread_Self(void)
{
	GM_THREAD td = GetCurrentThreadId();

	return td;
}
#endif
#ifdef QNX
GM_BOOL GM_Thread_Create(GM_THREAD* thread, GM_THREAD_FUNC myfunc, const char* threadName, int stackSize, int priority, const GM_Thread_Arg_Struct* args)
{
	GM_THREAD tmpThread = 0;
	GM_THREAD rt        = 0;
	pthread_attr_t attr = { 0 };
	struct sched_param params;
	/*���ȼ�63Ϊ��ߣ�1Ϊ���*/
	if ((priority > GM_TASK_PRIORITY_63) || (priority < GM_TASK_PRIORITY_1) || (stackSize <= 0))
	{
		return GM_FALSE;
	}

	pthread_attr_init(&attr);

	rt = pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);
	if(rt != 0)
	{
		return GM_FALSE;
	}
	params.sched_priority = priority;
	rt = pthread_attr_setschedparam(&attr, &params);
	if(rt != 0)
	{
		return GM_FALSE;
	}

	rt = pthread_attr_setstacksize(&attr,(size_t)stackSize );
	if(rt != 0)
	{
		return GM_FALSE;
	}

	if (NULL == thread)
	{
		rt = pthread_create(&tmpThread, &attr, myfunc, args);
	}
	else
	{
		rt = pthread_create(thread, &attr, myfunc, args);
	}

	if (0 == rt)
	{
		return GM_TRUE;
	}
	else
	{
		return GM_FALSE;
	}
}

GM_THREAD GM_Thread_Self(void)
{
	GM_THREAD rt = pthread_self();

	return rt;
}
#endif 
#ifdef VXWORKS
GM_BOOL GM_Thread_Create(GM_THREAD* thread, GM_THREAD_FUNC myfunc, const char* threadName, int stackSize, int priority, const GM_Thread_Arg_Struct * pargs)
{/*����Ĳ���ָ�� ���ܸ�ֵ���ֲ�����*/
	GM_THREAD tmpThread = 0;

	/*GM_TASK_PRIORITY_99Ϊ������ȼ���99�� GM_TASK_PRIORITY_0Ϊ������ȼ���0*/
	if ((priority > GM_TASK_PRIORITY_99) || (priority < GM_TASK_PRIORITY_0) || (stackSize <= 0))
	{
		return GM_FALSE;
	}

	/*GM_Log_Msg(0, "������ַ��[%d] %d %d %d",pargs, pargs->args1, pargs->args2, pargs->args3,0,0);*/
	if (NULL != pargs)
	{
		tmpThread = taskSpawn(threadName, priority, VX_FP_TASK, stackSize, (FUNCPTR)myfunc,
			pargs->args0, pargs->args1, pargs->args2, pargs->args3, pargs->args4, 
			pargs->args5, pargs->args6, pargs->args7, pargs->args8, pargs->args9);
	}
	else
	{
		tmpThread = taskSpawn(threadName, priority, VX_FP_TASK, stackSize, (FUNCPTR)myfunc,
			0, 0, 0, 0, 0,0, 0, 0, 0,0);	
	}

	if (thread != NULL)
	{/*��ָ�븳ֵ���޸�0223bug��*/
		*thread = tmpThread;
	}

	if (ERROR == tmpThread)
	{
		return GM_FALSE;
	}
	else
	{
		return GM_TRUE;
	}
}

GM_THREAD GM_Thread_Self(void)
{
	GM_THREAD td = taskIdSelf();

	return td;
}
#endif


