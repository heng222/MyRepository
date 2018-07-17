
#ifndef _EXERCISES_H_938384737u_
#define _EXERCISES_H_938384737u_
//////////////////////////////////////////////////////////////////////////

#ifdef TARGETDLL_EXPORTS
	#define TARGETDLL_API __declspec(dllexport)
#else
	#define TARGETDLL_API __declspec(dllimport)
#endif


/*求最大公约数*/
TARGETDLL_API int CalcGreatestCommonDivisor(int number1, int number2);


/* 计算字符个数 */
TARGETDLL_API int CalcCharacterCount(const char* string);

/* 自定义测试函数 */
TARGETDLL_API int DoSomething(int value1, int value2);
//////////////////////////////////////////////////////////////////////////
#endif