#include "cpptest.h"

/** 
 * This file contains auto-generated stub definitions.
 *
 * Available C++test API functions (see C++test Users Guide for details):
 *     void CppTest_Assert(bool test, const char * message)
 *     void CppTest_Break()
 *     const char* CppTest_GetCurrentTestCaseName()
 *     const char* CppTest_GetCurrentTestSuiteName()
 *     bool CppTest_IsCurrentTestCase(const char* testCaseName)
 */

/** 
 * Header files where the stubbed functions are originally declared.
 * Verify #include directives and add any additional header files as necessary.
 */

/** Auto-generated stub definition for function: int FixValue(int, int) */
int FixValue (int value1, int value2) ;
int CppTest_Auto_Stub_FixValue (int value1, int value2) 
{
	if (CppTest_IsCurrentTestCase("test_DoSomething_1"))
	{
		return 1;
	}
	else if (CppTest_IsCurrentTestCase("test_DoSomething_2"))
	{
		return 2;
	}

    return 0;
}
