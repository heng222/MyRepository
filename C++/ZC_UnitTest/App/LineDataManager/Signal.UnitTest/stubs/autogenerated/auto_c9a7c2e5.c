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
#include "..\..\..\Common\MemSet.h"
#include "..\..\..\Dmu\DmuComm\DataHandle\DmuCommDataHandle.h"
#include "..\..\DmuZc\DataHandle\DmuZcDataHandle.h"
#include "..\..\MaintainManager\MaintainManager.h"
#include "..\..\SysDataManager\SysConfigData.h"
#include "..\..\TrainManager\Train\TrainLogicManager.h"
#include "..\..\TrainManager\Train\TrainStatusData.h"
#include "..\AC\ACConfigData.h"
#include "..\AC\ACStatusData.h"
#include "..\Signal\SignalConfigData.h"
#include "..\Signal\SignalStatusData.h"

/** User stub definition for function: UINT8_S GetAcUtFlag(const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S GetAcUtFlag (const UINT16_S acId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetAcUtFlag (const UINT16_S acId) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_004"))
	{
		return (unsigned char)AC_UT_OCC_STATUS;
	}
}

/** User stub definition for function: UINT8_S GetSignalCbtcLightOffType(const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S GetSignalCbtcLightOffType (const UINT16_S signalId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetSignalCbtcLightOffType (const UINT16_S signalId) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_009"))
	{
		return (unsigned char)SIGNAL_LIGHT_COMMAND;
	}
	else if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_010"))
	{
		return (unsigned char)SIGNAL_OFF_COMMAND;
	}
	else if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_011"))
	{
		return (unsigned char)0;
	}
}

/** User stub definition for function: UINT8_S CheckSignalPostion(const UINT16_S, UINT16_S *, UINT32_S *) */
EXTERN_C_LINKAGE UINT8_S CheckSignalPostion (const UINT16_S signalId, UINT16_S * seg, UINT32_S * offset) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_CheckSignalPostion (const UINT16_S signalId, UINT16_S * seg, UINT32_S * offset) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_001"))
	{
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_002"))
	{
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_003"))
	{
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_004"))
	{
		* seg = 5;
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_005"))
	{
		* seg = 5;
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_006"))
	{
		* seg = 5;
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_007"))
	{
		* seg = 5;
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_008"))
	{
		* seg = 5;
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_009"))
	{
		* seg = 5;
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_010"))
	{
		* seg = 5;
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_011"))
	{
		* seg = 5;
		return (unsigned char)0;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_012"))
	{
		* seg = 5;
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_013"))
	{
		* seg = 5;
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_014"))
	{
		return (unsigned char)1;
	}

	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainNeedSingalLoc_001"))
	{
		return (unsigned char)0;
	}
	else if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainNeedSingalLoc_002"))
	{
		return (unsigned char)1;
	}
	else if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainNeedSingalLoc_003"))
	{
		* seg = 0;
		return (unsigned char)1;
	}

	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_020"))
	{
		return (unsigned char)0;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_021"))
	{
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_022"))
	{
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_023"))
	{
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_024"))
	{
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_025"))
	{
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_026"))
	{
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_027"))
	{
		return (unsigned char)1;
	}
	else
	{
		* seg = 5;
		return (unsigned char)1;
	}


}

/** User stub definition for function: UINT8_S CheckLocRelationBetweenTwoPoints(const UINT16_S, const UINT32_S, const UINT16_S, const UINT32_S, UINT8_S) */
UINT8_S EE;
EXTERN_C_LINKAGE UINT8_S CheckLocRelationBetweenTwoPoints (const UINT16_S seg1, const UINT32_S offset1, const UINT16_S seg2, const UINT32_S offset2, UINT8_S dir) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_CheckLocRelationBetweenTwoPoints (const UINT16_S seg1, const UINT32_S offset1, const UINT16_S seg2, const UINT32_S offset2, UINT8_S dir) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_004"))
	{
		return (unsigned char)0;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_005"))
	{
		return (unsigned char)0x01U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_006"))
	{
		return (unsigned char)0x01U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_007"))
	{
		return (unsigned char)0x01U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_008"))
	{
		return (unsigned char)0x01U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_013"))
	{
		if(EE % 2 == 1)
		{
			EE++;
			return (unsigned char)0x01U;
		}
		if(EE % 2 == 0)
		{
			EE++;
			return (unsigned char)0;
		}
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_021"))
	{
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_022"))
	{
		return (unsigned char)0;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_023"))
	{
		return (unsigned char)3;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_024"))
	{
		return (unsigned char)3;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_025"))
	{
		return (unsigned char)3;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_026"))
	{
		return (unsigned char)3;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_027"))
	{
		return (unsigned char)3;
	}
}

/** User stub definition for function: UINT8_S GetAcTrainOfAcNum(const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S GetAcTrainOfAcNum (const UINT16_S acId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetAcTrainOfAcNum (const UINT16_S acId) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_003"))
	{
		return (unsigned char)0;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_004"))
	{
		return (unsigned char)0;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_005"))
	{
		return (unsigned char)22;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_006"))
	{
		return (unsigned char)22;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_007"))
	{
		return (unsigned char)22;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_008"))
	{
		return (unsigned char)22;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_009"))
	{
		return (unsigned char)22;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_010"))
	{
		return (unsigned char)22;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_011"))
	{
		return (unsigned char)22;
	}
	else
	{
		return RETURN_SUCCESS;
	}

}

/** User stub definition for function: UINT8_S CheckPointNearestSignalBaseDir(const UINT8_S, const UINT16_S, const UINT32_S, UINT16_S *) */
EXTERN_C_LINKAGE UINT8_S CheckPointNearestSignalBaseDir (const UINT8_S dir, const UINT16_S seg, const UINT32_S offset, UINT16_S * outSignalId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_CheckPointNearestSignalBaseDir (const UINT8_S dir, const UINT16_S seg, const UINT32_S offset, UINT16_S * outSignalId) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_007"))
	{
		return (unsigned char)0;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_008"))
	{
		* outSignalId = 0;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_009"))
	{
		* outSignalId = 1;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_010"))
	{
		* outSignalId = 1;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_011"))
	{
		* outSignalId = 1;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_012"))
	{
		* outSignalId = 1;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_013"))
	{
		* outSignalId = 1;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_014"))
	{
		* outSignalId = 1;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_015"))
	{
		* outSignalId = 0;
		return (unsigned char)RETURN_SUCCESS;
	}
	else
	{
		* outSignalId = 10;
		return (unsigned char)RETURN_SUCCESS;
	}
}

/** User stub definition for function: UINT8_S GetAcStatusNow(const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S GetAcStatusNow (const UINT16_S acId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetAcStatusNow (const UINT16_S acId) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_007"))
	{
		return (unsigned char)0;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_008"))
	{
		return (unsigned char)AC_OCC_STATUS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_002"))
	{
		return (unsigned char)0;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_003"))
	{
		return (unsigned char)AC_OCC_STATUS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_004"))
	{
		return (unsigned char)AC_OCC_STATUS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_005"))
	{
		return (unsigned char)AC_OCC_STATUS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_006"))
	{
		return (unsigned char)AC_OCC_STATUS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_007"))
	{
		return (unsigned char)AC_OCC_STATUS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_008"))
	{
		return (unsigned char)AC_OCC_STATUS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_009"))
	{
		return (unsigned char)AC_OCC_STATUS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_010"))
	{
		return (unsigned char)AC_OCC_STATUS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_011"))
	{
		return (unsigned char)AC_OCC_STATUS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_012"))
	{
		return (unsigned char)0;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_013"))
	{
		return (unsigned char)AC_OCC_STATUS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_025"))
	{
		return (unsigned char)AC_FREE_STATUS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_026"))
	{
		return (unsigned char)0;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_027"))
	{
		return (unsigned char)0;
	}
}

/** User stub definition for function: UINT8_S GetTrainSafeLoc(const UINT16_S, TrainSafeLocStruct *) */
EXTERN_C_LINKAGE UINT8_S GetTrainSafeLoc (const UINT16_S trainId, TrainSafeLocStruct * pTrainSafeLocStru) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetTrainSafeLoc (const UINT16_S trainId, TrainSafeLocStruct * pTrainSafeLocStru) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_002"))
	{
		return (unsigned char)0;
	}
	else if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_012"))
	{
		return (unsigned char)0;
	}
	else if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_006"))
	{
		return (unsigned char)0;
	}
	else
	{
		return (unsigned char)RETURN_SUCCESS;
	}
}

/** User stub definition for function: UINT8_S LogPrintf(UINT8_S, const char *, ...) */
EXTERN_C_LINKAGE UINT8_S LogPrintf (UINT8_S chRunSystem, const char * lpszFormat, ...) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_LogPrintf (UINT8_S chRunSystem, const char * lpszFormat, ...) 
{
	return (unsigned char)0;
}

/** User stub definition for function: UINT8_S CheckFrontLink(const UINT8_S, const UINT16_S, UINT16_S *) */
EXTERN_C_LINKAGE UINT8_S CheckFrontLink (const UINT8_S dir, const UINT16_S segId, UINT16_S * outSegId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_CheckFrontLink (const UINT8_S dir, const UINT16_S segId, UINT16_S * outSegId) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainNeedSingalLoc_005"))
	{
		return (unsigned char)0;
	}
	else if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainNeedSingalLoc_006"))
	{
		* outSegId = 0;
		return (unsigned char)1;
	}
	else if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainNeedSingalLoc_007"))
	{
		* outSegId = 1;
		return (unsigned char)1U;
	}
	else if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainNeedSingalLoc_008"))
	{
		* outSegId = 4;
		return (unsigned char)1U;
	}
	else if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainNeedSingalLoc_009"))
	{
		* outSegId = 4;
		return (unsigned char)1U;
	}
	else
	{
		return RETURN_SUCCESS;
	}
}

/** User stub definition for function: UINT8_S SetTrainFrontSignal(const UINT16_S, const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S SetTrainFrontSignal (const UINT16_S trainId, const UINT16_S trainFrontSignal) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_SetTrainFrontSignal (const UINT16_S trainId, const UINT16_S trainFrontSignal) 
{
	return (unsigned char)0;
}

/** User stub definition for function: UINT8_S GetSignalCrossType(const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S GetSignalCrossType (const UINT16_S signalId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetSignalCrossType (const UINT16_S signalId) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainAcrossSingalManager_001"))
	{
		return (unsigned char)0;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainAcrossSingalManager_002"))
	{
		return (unsigned char)FLAG_SET;
	}
}

/** User stub definition for function: UINT32_S GetSignalLightLength(void) */
EXTERN_C_LINKAGE UINT32_S GetSignalLightLength () ;
EXTERN_C_LINKAGE UINT32_S CppTest_Stub_GetSignalLightLength (void) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_002"))
	{
		return 0U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_003"))
	{
		return 0U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_004"))
	{
		return 0U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_005"))
	{
		return 0U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_006"))
	{
		return 0U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_007"))
	{
		return 0U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_008"))
	{
		return 0U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_009"))
	{
		return 0U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_009"))
	{
		return 0U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_010"))
	{
		return 0U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_011"))
	{
		return 0U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_012"))
	{
		return 0U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_013"))
	{
		return 0U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_CalculateAcOfSignalLighten_006"))
	{
		return 0U;
	}
	else
	{
		return 5U;
	}

}

/** User stub definition for function: UINT8_S GetSignalCrashType(const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S GetSignalCrashType (const UINT16_S signalId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetSignalCrashType (const UINT16_S signalId) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_010")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_011")) {
		return (unsigned char) FLAG_SET;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_012")) {
		return (unsigned char) FLAG_SET;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_016")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_017")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_018")) {
		return (unsigned char) FLAG_SET;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_019")) {
		return (unsigned char) FLAG_SET;
	}
}

/** User stub definition for function: UINT8_S CheckNextPointOnDistance(const UINT16_S, const UINT32_S, const UINT8_S, const UINT32_S, UINT16_S *, UINT32_S *, UINT16_S *) */
EXTERN_C_LINKAGE UINT8_S CheckNextPointOnDistance (const UINT16_S seg1, const UINT32_S offset1, const UINT8_S dir, const UINT32_S distance, UINT16_S * outSeg, UINT32_S * outOffset, UINT16_S * errorSwitchId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_CheckNextPointOnDistance (const UINT16_S seg1, const UINT32_S offset1, const UINT8_S dir, const UINT32_S distance, UINT16_S * outSeg, UINT32_S * outOffset, UINT16_S * errorSwitchId) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_004")) {
		return (unsigned char) 3;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_005")) {
		return (unsigned char) 3;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_006")) {
		return (unsigned char) 3;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_007")) {
		return (unsigned char) 3;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_008")) {
		return (unsigned char) 3;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_010")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_013")) {
		return (unsigned char) 3;
	}
	else if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_015")) {
		return (unsigned char) 3;
	}
}

/** User stub definition for function: UINT8_S SetTrainSignalProtection(const UINT16_S, const UINT8_S) */
EXTERN_C_LINKAGE UINT8_S SetTrainSignalProtection (const UINT16_S trainId, const UINT8_S signalProtection) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_SetTrainSignalProtection (const UINT16_S trainId, const UINT8_S signalProtection) 
{
	return (unsigned char)0;
}

/** User stub definition for function: UINT16_S GetTrainAcrossSignalDis(void) */
EXTERN_C_LINKAGE UINT16_S GetTrainAcrossSignalDis () ;
EXTERN_C_LINKAGE UINT16_S CppTest_Stub_GetTrainAcrossSignalDis (void) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_001")) {
		return (unsigned char) 0U;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_002")) {
		return (unsigned char) 0U;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_003")) {
		return (unsigned char) 0U;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_004")) {
		return (unsigned char) 0U;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_005")) {
		return (unsigned char) 0U;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_006")) {
		return (unsigned char) 0U;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_007")) {
		return (unsigned char) 0U;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_008")) {
		return (unsigned char) 0U;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_009")) {
		return (unsigned char) 0U;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_010")) {
		return (unsigned char) 0U;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_012")) {
		return (unsigned char) 0U;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_013")) {
		return (unsigned char) 0U;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_014")) {
		return (unsigned char) 0U;
	}
}

/** User stub definition for function: UINT16_S GetSignalId(const UINT16_S) */
EXTERN_C_LINKAGE UINT16_S GetSignalId (const UINT16_S bufIndex) ;
EXTERN_C_LINKAGE UINT16_S CppTest_Stub_GetSignalId (const UINT16_S bufIndex) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_InitFailureNZcSignal_001")) {
		return (unsigned short) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_InitFailureNZcSignal_002")) {
		return (unsigned short) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_InitFailureNZcSignal_003")) {
		return (unsigned short) 0;
	}

}

/** User stub definition for function: UINT8_S GetAcBoundaryType(const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S GetAcBoundaryType (const UINT16_S acId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetAcBoundaryType (const UINT16_S acId) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainAcrossSingalManager_002")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_001")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_002")) {
		return (unsigned char) 0;
	} else
	{
		return (unsigned char) 2;
	}
}

/** User stub definition for function: UINT8_S GetTrainStatus(const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S GetTrainStatus (const UINT16_S trainId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetTrainStatus (const UINT16_S trainId) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_003")) {
		return (unsigned char) TRAIN_STATE_REVERSE;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_005")) {
		return (unsigned char) TRAIN_STATE_REVERSE;
	} else
	{
		return (unsigned char) 0;
	}
}

/** User stub definition for function: UINT8_S MemorySet(void *, UINT32_S, UINT8_S, UINT32_S) */
EXTERN_C_LINKAGE UINT8_S MemorySet (void * pDest, UINT32_S destBuffSize, UINT8_S c, UINT32_S count) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_MemorySet (void * pDest, UINT32_S destBuffSize, UINT8_S c, UINT32_S count) 
{
	return (unsigned char)0;
}

/** User stub definition for function: UINT8_S SetSignalStatus(const UINT16_S, UINT8_S) */
EXTERN_C_LINKAGE UINT8_S SetSignalStatus (const UINT16_S signalId, UINT8_S signalStatus) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_SetSignalStatus (const UINT16_S signalId, UINT8_S signalStatus) 
{
	return (unsigned char)0;
}

/** User stub definition for function: UINT8_S GetTrainSignalProtection(const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S GetTrainSignalProtection (const UINT16_S trainId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetTrainSignalProtection (const UINT16_S trainId) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_004")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_005")) {
		return (unsigned char) FLAG_SET;
	}
	else {
		return (unsigned char) FLAG_UNSET;
	}
}

/** User stub definition for function: UINT8_S GetTrainType(const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S GetTrainType (const UINT16_S trainId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetTrainType (const UINT16_S trainId) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_002")) {
		return (unsigned char) TRAIN_MODE_TO_RM0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_003")) {
		return (unsigned char) TRAIN_MODE_TO_RM0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_004")) {
		return (unsigned char) TRAIN_MODE_TO_RM0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_005")) {
		return (unsigned char) TRAIN_MODE_TO_RM0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_006")) {
		return (unsigned char) TRAIN_MODE_TO_RM0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_007")) {
		return (unsigned char) TRAIN_MODE_TO_RM0;
	}
	else if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_008")) {
		return (unsigned char) TRAIN_MODE_TO_RM0;
	}
	else if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_015")) {
		return (unsigned char) TRAIN_MODE_CBTC;
	}
	else if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_016")) {
		return (unsigned char) TRAIN_MODE_CBTC;
	}

	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_006")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_008")) {
		return (unsigned char) TRAIN_MODE_TO_RM0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_009")) {
		return (unsigned char) TRAIN_MODE_TO_RM0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_010")) {
		return (unsigned char) TRAIN_MODE_TO_RM0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_011")) {
		return (unsigned char) TRAIN_MODE_TO_RM0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_002")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_014")) {
		return (unsigned char) 0;
	} else {
		return (unsigned char) TRAIN_MODE_CBTC;
	}
}

/** User stub definition for function: UINT8_S CheckRearACStatus(const UINT16_S, const UINT8_S, UINT16_S *) */
EXTERN_C_LINKAGE UINT8_S CheckRearACStatus (const UINT16_S acId, const UINT8_S dir, UINT16_S * rearAcId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_CheckRearACStatus (const UINT16_S acId, const UINT8_S dir, UINT16_S * rearAcId) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_CalculateAcOfSignalLighten_007")) {
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_CalculateAcOfSignalLighten_008")) {
		*rearAcId = 0;
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_CalculateAcOfSignalLighten_009")) {
		*rearAcId = 1;
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_CalculateAcOfSignalLighten_010")) {
		return (unsigned char) 2;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_CalculateAcOfSignalLighten_011")) {
		return (unsigned char) 3;
	}
}

/** User stub definition for function: UINT8_S GetSignalStatus(const UINT16_S) */
UINT8_S STATUS;
EXTERN_C_LINKAGE UINT8_S GetSignalStatus (const UINT16_S signalId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetSignalStatus (const UINT16_S signalId) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_009")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_010")) {
		return (unsigned short) SIGNAL_STATE_STOP;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_011")) {
		return (unsigned short) SIGNAL_STATE_STOP;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_012")) {
		return (unsigned short) SIGNAL_STATE_STOP;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_013")) {
		return (unsigned short) SIGNAL_STATE_PASS;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_014")) {
		return (unsigned short) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_015")) {
		return (unsigned short) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_016")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_017")) {
		if (STATUS % 2 == 1) {
			STATUS++;
			return (unsigned char)SIGNAL_STATE_STOP;
		}
		if (STATUS % 2 == 0) {
			STATUS++;
			return (unsigned char)0 ;
		}
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_018")) {
		if (STATUS % 2 == 1) {
			STATUS++;
			return (unsigned char)SIGNAL_STATE_STOP;
		}
		if (STATUS % 2 == 0) {
			STATUS++;
			return (unsigned char)0;
		}
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_019")) {
		if (STATUS % 2 == 1) {
			STATUS++;
			return (unsigned char)SIGNAL_STATE_STOP;
		}
		if (STATUS % 2 == 0) {
			STATUS++;
			return (unsigned char)0;
		}
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_020")) {
		return (unsigned char) SIGNAL_STATE_STOP;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_021")) {
		return (unsigned char) SIGNAL_STATE_STOP;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_022")) {
		return (unsigned char) SIGNAL_STATE_STOP;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_023")) {
		return (unsigned char) SIGNAL_STATE_STOP;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_024")) {
		return (unsigned char) SIGNAL_STATE_STOP;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_025")) {
		return (unsigned char) SIGNAL_STATE_STOP;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_026")) {
		return (unsigned char) SIGNAL_STATE_STOP;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_027")) {
		return (unsigned char) SIGNAL_STATE_STOP;
	}
}

/** User stub definition for function: UINT16_S GetTrainFrontSignal(const UINT16_S) */
EXTERN_C_LINKAGE UINT16_S GetTrainFrontSignal (const UINT16_S trainId) ;
EXTERN_C_LINKAGE UINT16_S CppTest_Stub_GetTrainFrontSignal (const UINT16_S trainId) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_003")) {
		return (unsigned short) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_013")) {
		return (unsigned short) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_014")) {
		return (unsigned short) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_015")) {
		return (unsigned short) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_016")) {
		return (unsigned short) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_017")) {
		return (unsigned short) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_018")) {
		return (unsigned short) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_019")) {
		return (unsigned short) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_020")) {
		return (unsigned short) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_021")) {
		return (unsigned short) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_022")) {
		return (unsigned short) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_023")) {
		return (unsigned short) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_024")) {
		return (unsigned short) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_025")) {
		return (unsigned short) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_026")) {
		return (unsigned short) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_027")) {
		return (unsigned short) 1;
	} else {
		return (unsigned short) 0;
	}

}

/** User stub definition for function: void SetTrainToModeToRM0(const UINT16_S) */
EXTERN_C_LINKAGE void SetTrainToModeToRM0 (const UINT16_S trainId) ;
EXTERN_C_LINKAGE void CppTest_Stub_SetTrainToModeToRM0 (const UINT16_S trainId) 
{
}

/** User stub definition for function: UINT8_S GetTrainCurSum(void) */
EXTERN_C_LINKAGE UINT8_S GetTrainCurSum () ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetTrainCurSum (void) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_001")) {
		return (unsigned char) 3;
	} else {
		return (unsigned char) 3;
	}
}

/** User stub definition for function: UINT16_S GetTrainIdOfIndex(const UINT8_S) */
EXTERN_C_LINKAGE UINT16_S GetTrainIdOfIndex (const UINT8_S index) ;
EXTERN_C_LINKAGE UINT16_S CppTest_Stub_GetTrainIdOfIndex (const UINT8_S index) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_001")) {
		return (unsigned short) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_002")) {
		return (unsigned short) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_003")) {
		return (unsigned short) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_004")) {
		return (unsigned short) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_005")) {
		return (unsigned short) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_006")) {
		return (unsigned short) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_007")) {
		return (unsigned short) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_008")) {
		return (unsigned short) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_009")) {
		return (unsigned short) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_010")) {
		return (unsigned short) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_012")) {
		return (unsigned short) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_013")) {
		return (unsigned short) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_014")) {
		return (unsigned short) 0;
	}
}

/** User stub definition for function: UINT16_S GetSignalChangeAttribute(const UINT16_S) */
EXTERN_C_LINKAGE UINT16_S GetSignalChangeAttribute (const UINT16_S signalId) ;
EXTERN_C_LINKAGE UINT16_S CppTest_Stub_GetSignalChangeAttribute (const UINT16_S signalId) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_InitFailureNZcSignal_001")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_InitFailureNZcSignal_002")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_InitFailureNZcSignal_003")) {
		return (unsigned short) 0x55;
	}
}

/** User stub definition for function: UINT8_S GetSignalBelongZcId(const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S GetSignalBelongZcId (const UINT16_S signalId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetSignalBelongZcId (const UINT16_S signalId) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_InitFailureNZcSignal_001")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_InitFailureNZcSignal_002")) {
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_InitFailureNZcSignal_003")) {
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalControl_001")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalControl_002")) {
		return (unsigned char) 9;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalControl_003")) {
		return (unsigned char) 9;
	}
}

/** User stub definition for function: UINT8_S GetSignalProtectDir(const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S GetSignalProtectDir (const UINT16_S signalId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetSignalProtectDir (const UINT16_S signalId) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_003")) {
		return (unsigned char) 0x55;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_004")) {
		return (unsigned char) 0x55;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_005")) {
		return (unsigned char) 0x55;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_006")) {
		return (unsigned char) 0x55;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_007")) {
		return (unsigned char) 0x55;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_008")) {
		return (unsigned char) 0x55;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_009")) {
		return (unsigned char) 0x55;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_010")) {
		return (unsigned char) 0x55;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_012")) {
		return (unsigned char) 0x55;
	}
	if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_013")) {
		return (unsigned char) 0x55;
	}
	else if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_014")) {
		return (unsigned char) 1;
	}
	else if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_015")) {
		return (unsigned char) 0x55;
	}
	else if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_016")) {
		return (unsigned char) 0x55;
	}

	if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_007")) {
		return (unsigned char) RETURN_ERROR;
	}
	else if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_013"))
	{
		//return 0x55;
	}

	if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_012")) {
		return (unsigned char) 0x55;
	}
	if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_019")) {
		return (unsigned char) 0x55;
	}
	if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_027")) {
		return (unsigned char) 0x55;
	} else {
		return (unsigned char) 1;
	}
}

/** User stub definition for function: UINT8_S GetTrainUnsafeDirection(const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S GetTrainUnsafeDirection (const UINT16_S trainId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetTrainUnsafeDirection (const UINT16_S trainId) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_001")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_002")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_008")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_009")) {
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_010")) {
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_011")) {
		return (unsigned char) 1;
	}
	else
	{
		return (unsigned char) 0x55;
	}
}

/** User stub definition for function: UINT8_S GetSignalLightOffType(const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S GetSignalLightOffType (const UINT16_S signalId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetSignalLightOffType (const UINT16_S signalId) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalControl_002")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalControl_003")) {
		return (unsigned char) FLAG_SET;
	}
}

/** User stub definition for function: UINT8_S GetSignalDefaultStatus(const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S GetSignalDefaultStatus (const UINT16_S signalId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetSignalDefaultStatus (const UINT16_S signalId) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_012")) {
		return (unsigned char) SIGNAL_LIGHT_COMMAND;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_013")) {
		return (unsigned char) SIGNAL_OFF_COMMAND;
	}
}

/** User stub definition for function: UINT8_S CheckFirstAcOfSignal(const UINT16_S, UINT16_S *) */
EXTERN_C_LINKAGE UINT8_S CheckFirstAcOfSignal (const UINT16_S signalId, UINT16_S * acId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_CheckFirstAcOfSignal (const UINT16_S signalId, UINT16_S * acId) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_006")) {
		*acId = 0;
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_007")) {
		*acId = 20;
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_008")) {
		*acId = 20;
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_023")) {

		return (unsigned char) 3;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_024")) {
		*acId = 0;
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_025")) {
		*acId = 20;
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_026")) {
		*acId = 20;
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_027")) {
		*acId = 20;
		return (unsigned char) 1;
	}
}

/** User stub definition for function: UINT16_S GetAcBelongZcId(const UINT16_S) */
EXTERN_C_LINKAGE UINT16_S GetAcBelongZcId (const UINT16_S acId) ;
EXTERN_C_LINKAGE UINT16_S CppTest_Stub_GetAcBelongZcId (const UINT16_S acId) 
{

	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_TrainCrashSignal_002")) {
		return (unsigned short) 9;
	} else {
		return (unsigned short) 0;
	}
}

/** User stub definition for function: UINT8_S SetSignalCrossStatus(const UINT16_S, UINT8_S) */
EXTERN_C_LINKAGE UINT8_S SetSignalCrossStatus (const UINT16_S signalId, UINT8_S crossStatus) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_SetSignalCrossStatus (const UINT16_S signalId, UINT8_S crossStatus) 
{
	if (CppTest_IsCurrentTestCase("")) {
		return (unsigned char) 0;
	}

}

/** User stub definition for function: UINT8_S CheckOutsideAcOfSignal(const UINT16_S, UINT16_S *) */
EXTERN_C_LINKAGE UINT8_S CheckOutsideAcOfSignal (const UINT16_S signalId, UINT16_S * acId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_CheckOutsideAcOfSignal (const UINT16_S signalId, UINT16_S * acId) 
{
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_001")) {
		return (unsigned char) 0;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_002")) {
		*acId = 1;
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_003")) {
		*acId = 1;
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_004")) {
		*acId = 1;
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_005")) {
		*acId = 1;
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_006")) {
		*acId = 1;
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_007")) {
		*acId = 1;
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_008")) {
		*acId = 1;
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_009")) {
		*acId = 1;
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_010")) {
		*acId = 1;
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_011")) {
		*acId = 1;
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_012")) {
		*acId = 1;
		return (unsigned char) 1;
	}
	if (CppTest_IsCurrentTestCase(
			"TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_013")) {
		*acId = 1;
		return (unsigned char) 1;
	}

	if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_CalculateAcOfSignalLighten_003")) {
		return (unsigned char) 0;
	}
	else if (CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_CalculateAcOfSignalLighten_004")) {
		*acId = 0;
		return (unsigned char) 1;
	}
	else
	{
		*acId = 1;
		return (unsigned char) 1;
	}

}

/** User stub definition for function: UINT8_S GetTrainUnSafeLoc(const UINT16_S, TrainSafeLocStruct *) */
EXTERN_C_LINKAGE UINT8_S GetTrainUnSafeLoc (const UINT16_S trainId, TrainSafeLocStruct * pTrainUnSafeLocStru) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetTrainUnSafeLoc (const UINT16_S trainId, TrainSafeLocStruct * pTrainUnSafeLocStru) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainNeedSingalLoc_002"))
	{
		return (unsigned char)3;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainNeedSingalLoc_003"))
	{
		pTrainUnSafeLocStru->TrainHeadLink = 0;
		pTrainUnSafeLocStru->TrainTailLink = 1;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainNeedSingalLoc_004"))
	{
		pTrainUnSafeLocStru->TrainHeadLink = (UINT16_S)1;
		pTrainUnSafeLocStru->TrainTailLink = (UINT16_S)5;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainNeedSingalLoc_005"))
	{
		pTrainUnSafeLocStru->TrainHeadLink = 1;
		pTrainUnSafeLocStru->TrainTailLink = 1;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainNeedSingalLoc_006"))
	{
		pTrainUnSafeLocStru->TrainHeadLink = 1;
		pTrainUnSafeLocStru->TrainTailLink = 0;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainNeedSingalLoc_007"))
	{
		pTrainUnSafeLocStru->TrainHeadLink = 1;
		pTrainUnSafeLocStru->TrainTailLink = 0;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainNeedSingalLoc_008"))
	{
		pTrainUnSafeLocStru->TrainHeadLink = 10;
		pTrainUnSafeLocStru->TrainTailLink = 10;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainNeedSingalLoc_009"))
	{
		pTrainUnSafeLocStru->TrainHeadLink = 10;
		pTrainUnSafeLocStru->TrainTailLink = 4;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_003"))
	{
		pTrainUnSafeLocStru->TrainHeadLink = 10;
		pTrainUnSafeLocStru->TrainTailLink = 10;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_004"))
	{
		pTrainUnSafeLocStru->TrainHeadLink = 1;
		pTrainUnSafeLocStru->TrainTailLink = 5;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_005"))
	{
		pTrainUnSafeLocStru->TrainHeadLink = 1;
		pTrainUnSafeLocStru->TrainTailLink = 5;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_006"))
	{
		pTrainUnSafeLocStru->TrainHeadLink = 1;
		pTrainUnSafeLocStru->TrainTailLink = 5;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_007"))
	{
		pTrainUnSafeLocStru->TrainHeadLink = 1;
		pTrainUnSafeLocStru->TrainTailLink = 5;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_008"))
	{
		pTrainUnSafeLocStru->TrainHeadLink = 1;
		pTrainUnSafeLocStru->TrainTailLink = 5;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_010"))
	{
		pTrainUnSafeLocStru->TrainHeadLink = 1;
		pTrainUnSafeLocStru->TrainTailLink = 5;
		return (unsigned char)RETURN_SUCCESS;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_013"))
	{
		pTrainUnSafeLocStru->TrainHeadLink = 1;
		pTrainUnSafeLocStru->TrainTailLink = 5;
		return (unsigned char)RETURN_SUCCESS;
	}
	else if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_015"))
	{
		pTrainUnSafeLocStru->TrainHeadLink = 1;
		pTrainUnSafeLocStru->TrainTailLink = 5;
		return (unsigned char)RETURN_SUCCESS;
	}
	else if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_JudgeTrainAcrossOfSingalSignal_016"))
	{
		pTrainUnSafeLocStru->TrainHeadLink = 1;
		pTrainUnSafeLocStru->TrainTailLink = 5;
		return (unsigned char)RETURN_SUCCESS;
	}
}

/** User stub definition for function: UINT16_S GetTrainLength(const UINT16_S) */
EXTERN_C_LINKAGE UINT16_S GetTrainLength (const UINT16_S trainId) ;
EXTERN_C_LINKAGE UINT16_S CppTest_Stub_GetTrainLength (const UINT16_S trainId) 
{
	return (unsigned short)0;
}

/** User stub definition for function: UINT8_S CheckAcLength(const UINT16_S, UINT32_S *) */
EXTERN_C_LINKAGE UINT8_S CheckAcLength (const UINT16_S acId, UINT32_S * length) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_CheckAcLength (const UINT16_S acId, UINT32_S * length) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_CalculateAcOfSignalLighten_005"))
	{
		return (unsigned char)0;
	}
	else
	{
		return (unsigned char)1;
	}
}

/** User stub definition for function: UINT16_S GetTrainTrainHeadAC(const UINT16_S) */
EXTERN_C_LINKAGE UINT16_S GetTrainTrainHeadAC (const UINT16_S trainId) ;
EXTERN_C_LINKAGE UINT16_S CppTest_Stub_GetTrainTrainHeadAC (const UINT16_S trainId) 
{
	return (unsigned short)0;
}

/** User stub definition for function: UINT8_S GetAcTrainSequenceBuff(const UINT16_S, const UINT8_S, UINT16_S *) */
EXTERN_C_LINKAGE UINT8_S GetAcTrainSequenceBuff(const UINT16_S acId, const UINT8_S bufSzie, UINT16_S  trainIdSequBuff[]) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetAcTrainSequenceBuff (const UINT16_S acId, const UINT8_S bufSzie, UINT16_S  trainIdSequBuff[])
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalLightAndOffDeal_005"))
	{
		return (unsigned char)0;
	}
	else
	{
		return RETURN_SUCCESS;
	}
}

/** User stub definition for function: UINT8_S SetSignalLightOffStatus(const UINT16_S, UINT8_S) */
EXTERN_C_LINKAGE UINT8_S SetSignalLightOffStatus (const UINT16_S signalId, UINT8_S lightOffStatus) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_SetSignalLightOffStatus (const UINT16_S signalId, UINT8_S lightOffStatus) 
{

	return (unsigned char)0;

}

/** User stub definition for function: UINT8_S GetSignalBelongCiId(const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S GetSignalBelongCiId (const UINT16_S signalId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetSignalBelongCiId (const UINT16_S signalId) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_InitFailureCiSignal_001"))
	{
		return (unsigned char)0;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_InitFailureCiSignal_002"))
	{
		return (unsigned char)1;
	}

}
