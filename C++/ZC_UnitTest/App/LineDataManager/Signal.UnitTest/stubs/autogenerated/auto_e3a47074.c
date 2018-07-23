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
#include "..\AC\ACLogicManager.h"

/** User stub definition for function: UINT8_S JudgeAcOfSwitchPosInNeed(const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S JudgeAcOfSwitchPosInNeed (const UINT16_S acId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_JudgeAcOfSwitchPosInNeed (const UINT16_S acId) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_CalculateAcOfSignalLighten_012"))
	{
		return 0;
	}
    return (unsigned char)1;
}
