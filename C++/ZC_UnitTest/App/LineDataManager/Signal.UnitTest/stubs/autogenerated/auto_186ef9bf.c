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
#include "..\Signal\SignalConfigData.h"

/** User stub definition for function: UINT16_S GetSignalSum(void) */
EXTERN_C_LINKAGE UINT16_S GetSignalSum () ;
EXTERN_C_LINKAGE UINT16_S CppTest_Stub_GetSignalSum (void) 
{
	if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_001")) {
		return (unsigned short) 5;
	}
	else if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_002")) {
		return (unsigned short) 5;
	}

	if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_InitFailureCiSignal_001")) {
		return (unsigned short) 5;
	}
	if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_InitFailureCiSignal_002")) {
		return (unsigned short) 5;
	}
	if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_InitFailureNZcSignal_001")) {
		return (unsigned short) 5;
	}
	if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_InitFailureNZcSignal_002")) {
		return (unsigned short) 5;
	}
	if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_InitFailureNZcSignal_003")) {
		return (unsigned short) 5;
	}

	if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalControl_001")) {
		return (unsigned short) 8;
	}
	if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalControl_002")) {
		return (unsigned short) 8;
	}
	if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalControl_003")) {
		return (unsigned short) 8;
	}

	if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainAcrossSingalManager_001")) {
		return (unsigned short) 6;
	}
	if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainAcrossSingalManager_002")) {
		return (unsigned short) 6;
	}

	if(CppTest_IsCurrentTestCase("TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalCrossStatus_002"))
	{
		return (unsigned short)0;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalLightOffStatus_001"))
	{
		return (unsigned short)0;
	}

	if(CppTest_IsCurrentTestCase("TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalStatus_001"))
	{
		return (unsigned short)0;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalStatusData_001"))
	{
		return (unsigned short)0;
	}

	if(CppTest_IsCurrentTestCase("TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalCrossStatus_001"))
	{
		return (unsigned short)0;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalLightOffStatus_001"))
	{
		return (unsigned short)0;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalStatus_001"))
	{
		return (unsigned short)0;
	}
	else
	{
		return (unsigned short)5;
	}
}

/** User stub definition for function: UINT16_S GetSignalConfigBufIndex(const UINT16_S) */
EXTERN_C_LINKAGE UINT16_S GetSignalConfigBufIndex (const UINT16_S signalId) ;
EXTERN_C_LINKAGE UINT16_S CppTest_Stub_GetSignalConfigBufIndex (const UINT16_S signalId) 
{
	return (unsigned short)0;
}

