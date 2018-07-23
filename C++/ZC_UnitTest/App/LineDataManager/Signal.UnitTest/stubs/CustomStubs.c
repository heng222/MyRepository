#include "cpptest.h"

/**
 * This file contains user stub definitions.
 *
 * To create a user stub:
 * 1. Open stub template list:
 *    - Eclipse IDE: type 'stub' and press <Ctrl> <Space>
 *    - Microsoft Visual Studio IDE: use context menu C++test->Insert Snippet...
 * 2. Choose the stub template from the list.
 * 3. #include the header file where the function you want to stub is originally 
 *    declared as well as any supporting header files as necessary.
 * 4. Fill out the stub signature to match that of the original function, 
 *    while keeping the CppTest_Stub prefix when it applies.
 *    Note: for C++ operators, use appropriate stub names - e.g.:
 *        CppTest_Stub_operator_new    for operator new
 *        CppTest_Stub_operator_delete for operator delete
 *        CppTest_Stub_operator_plus   for operator +
 *    Refer to C++test User's Guide for a complete list of stub names for operators. 
 * 5. Fill out the body of the stub according to intent.
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
#include "..\Signal\SignalLogicManager.h"

/** User stub definition for function: UINT8_S JudgeTrainAcrossOfSingalSignal(const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S JudgeTrainAcrossOfSingalSignal (const UINT16_S signalId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_JudgeTrainAcrossOfSingalSignal (const UINT16_S signalId) 
{
    return (unsigned char)RETURN_SUCCESS;
}

/** User stub definition for function: UINT8_S JudgeTrainNeedSingalLoc(const UINT16_S, const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S JudgeTrainNeedSingalLoc (const UINT16_S signalId, const UINT16_S trainId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_JudgeTrainNeedSingalLoc (const UINT16_S signalId, const UINT16_S trainId) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_016"))
	{
		return RETURN_ERROR;
	}

    return (unsigned char)RETURN_SUCCESS;
}

/** User stub definition for function: UINT8_S CalculateAcOfSignalLighten(const UINT16_S, UINT8_S *, UINT16_S *) */
EXTERN_C_LINKAGE UINT8_S CalculateAcOfSignalLighten (const UINT16_S signalId, UINT8_S * acNum, UINT16_S  acIdBuff[]) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_CalculateAcOfSignalLighten (const UINT16_S signalId, UINT8_S * acNum, UINT16_S  acIdBuff[]) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_001"))
	{
		return RETURN_ERROR;
	}
	else if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_012"))
	{
	    return RETURN_SUCCESS;
	}
	else if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_013"))
	{
	    return RETURN_SUCCESS;
	}
	else
	{
		*acNum = 1;
	    return RETURN_SUCCESS;
	}

}
