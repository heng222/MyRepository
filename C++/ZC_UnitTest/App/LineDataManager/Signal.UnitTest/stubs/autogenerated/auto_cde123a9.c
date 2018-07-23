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
#include "..\..\..\Dmu\DmuComm\Data\SignData.h"
#include "..\..\DmuZc\Data\ZcSignInfoData.h"
#include "..\..\SysDataManager\SysConfigData.h"
#include "..\Change\ChangeConfigData.h"
#include "..\Mask\MaskConfigData.h"
#include "..\Signal\SignalStatusData.h"
#include "..\Signal\SignalConfigData.h"

/** User stub definition for function: UINT8_S GetAppointObsInChangeArea(const UINT16_S, const UINT8_S) */
EXTERN_C_LINKAGE UINT8_S GetAppointObsInChangeArea (const UINT16_S obsId, const UINT8_S obsType) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetAppointObsInChangeArea (const UINT16_S obsId, const UINT8_S obsType) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_002"))
	{
		return (unsigned char)5;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_003"))
	{
		return (unsigned char)1;
	}
	else
	{
		return (unsigned char)RETURN_SUCCESS;
	}

}

/** User stub definition for function: UINT16_S GetMaskOfSignalLightOffNum(void) */
EXTERN_C_LINKAGE UINT16_S GetMaskOfSignalLightOffNum () ;
EXTERN_C_LINKAGE UINT16_S CppTest_Stub_GetMaskOfSignalLightOffNum (void) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLightOffType_001"))
	{
		return (unsigned short)0;
	}
	else
	{
		return (unsigned char)5;
	}
}

/** User stub definition for function: UINT16_S GetSignDataStrusignProperty(const UINT16_S) */
EXTERN_C_LINKAGE UINT16_S GetSignDataStrusignProperty (const UINT16_S signId) ;
EXTERN_C_LINKAGE UINT16_S CppTest_Stub_GetSignDataStrusignProperty (const UINT16_S signId) 
{
	return (unsigned short)0;
}


/** User stub definition for function: UINT16_S GetLineSignalBelongZcId(const UINT16_S) */
EXTERN_C_LINKAGE UINT16_S GetLineSignalBelongZcId (const UINT16_S signalId) ;
EXTERN_C_LINKAGE UINT16_S CppTest_Stub_GetLineSignalBelongZcId (const UINT16_S signalId) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_002"))
	{
		return (unsigned short)11;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_004"))
	{
		return (unsigned short)21;
	}
	else
	{
		return (unsigned char)25;
	}
}

UINT8_S ID;
/** User stub definition for function: UINT16_S GetLocalZcId(void) */
EXTERN_C_LINKAGE UINT16_S GetLocalZcId () ;
EXTERN_C_LINKAGE UINT16_S CppTest_Stub_GetLocalZcId (void) 
{
	if (CppTest_IsCurrentTestCase("TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_002")) {
		return (unsigned short)12;
	}
	if (CppTest_IsCurrentTestCase("TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_003")) {
		if (ID % 2 == 1) {
			return (unsigned short) 25;
		}
		if (ID % 2 == 0) {
			return (unsigned short) 1;
		}
	}
	if (CppTest_IsCurrentTestCase("TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_004")) {
		if (ID % 2 == 1) {
			return (unsigned short) 25;
		}
		if (ID % 2 == 0) {
			return (unsigned short) 21;
		}
	}

	if(CppTest_IsCurrentTestCase("TestSuite_SignalLogicManager_c_29990a1b_test_SignalControl_001"))
	{
		return (unsigned short)9;
	}
	else
	{
		return (unsigned short)25;
	}
	/*else {
		return (unsigned char) 9;
	}*/
}

/** User stub definition for function: UINT8_S GetSignDataStruprotectiveDir(const UINT16_S) */
EXTERN_C_LINKAGE UINT8_S GetSignDataStruprotectiveDir (const UINT16_S signId) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetSignDataStruprotectiveDir (const UINT16_S signId) 
{
	return (unsigned char)0;
}

/** User stub definition for function: UINT16_S GetLineSignalBelongCiId(const UINT16_S) */
EXTERN_C_LINKAGE UINT16_S GetLineSignalBelongCiId (const UINT16_S signalId) ;
EXTERN_C_LINKAGE UINT16_S CppTest_Stub_GetLineSignalBelongCiId (const UINT16_S signalId) 
{
	return (unsigned short)0;
}

/** User stub definition for function: UINT16_S GetZcSignInfoDataStrulightFlag(const UINT16_S) */
EXTERN_C_LINKAGE UINT16_S GetZcSignInfoDataStrulightFlag (const UINT16_S signId) ;
EXTERN_C_LINKAGE UINT16_S CppTest_Stub_GetZcSignInfoDataStrulightFlag (const UINT16_S signId) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_003"))
	{
		return (unsigned short)0x00U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_004"))
	{
		return (unsigned short)0x01U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_005"))
	{
		return (unsigned short)0x02U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_006"))
	{
		return (unsigned short)0x03U;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_007"))
	{
		return (unsigned short)9;
	}
}

/** User stub definition for function: UINT8_S GetMaskOfSignalLightOffIdBuff(const UINT16_S, UINT16_S *) */
EXTERN_C_LINKAGE UINT8_S GetMaskOfSignalLightOffIdBuff (const UINT16_S buffSize, UINT16_S  signalIdBuff[]) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetMaskOfSignalLightOffIdBuff (const UINT16_S buffSize, UINT16_S  signalIdBuff[]) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLightOffType_002"))
	{
		return (unsigned char)0;
	}
	else
	{
		signalIdBuff[2] = 10 ;
		return (unsigned char)RETURN_SUCCESS;
	}
}

/** User stub definition for function: UINT8_S GetMaskOfSignalCorssIdBuff(const UINT16_S, UINT16_S *) */
EXTERN_C_LINKAGE UINT8_S GetMaskOfSignalCorssIdBuff (const UINT16_S buffSize, UINT16_S  signalIdBuff[]) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_GetMaskOfSignalCorssIdBuff (const UINT16_S buffSize, UINT16_S  signalIdBuff[]) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalCorssType_002"))
	{
		return (unsigned char)0;
	}
	else
	{
		signalIdBuff[5] = 10;
		return (unsigned char)RETURN_SUCCESS;
	}

}

/** User stub definition for function: UINT16_S GetZcSignInfoDataStruthroughSignFlag(const UINT16_S) */
EXTERN_C_LINKAGE UINT16_S GetZcSignInfoDataStruthroughSignFlag (const UINT16_S signId) ;
EXTERN_C_LINKAGE UINT16_S CppTest_Stub_GetZcSignInfoDataStruthroughSignFlag (const UINT16_S signId) 
{
	return (unsigned short)0;
}

/** User stub definition for function: UINT16_S GetMaskOfSignalCorssNum(void) */
EXTERN_C_LINKAGE UINT16_S GetMaskOfSignalCorssNum () ;
EXTERN_C_LINKAGE UINT16_S CppTest_Stub_GetMaskOfSignalCorssNum (void) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalCorssType_001"))
	{
		return (unsigned short)0;
	}
	else
	{
		return (unsigned short)9;
	}

}

/** User stub definition for function: UINT16_S GetLineSignalMaxId(void) */
EXTERN_C_LINKAGE UINT16_S GetLineSignalMaxId () ;
EXTERN_C_LINKAGE UINT16_S CppTest_Stub_GetLineSignalMaxId (void) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_001"))
	{
		return (unsigned short)520;
	}
	else
	{
		return (unsigned short)20;
	}

}

/** User stub definition for variable: UINT16_S  gSignalIdBuff[500U] */
EXTERN_C_LINKAGE_START
extern UINT16_S  gSignalIdBuff[500U];
UINT16_S  CppTest_Variable_Stub_gSignalIdBuff[500U] = {(unsigned short)0, (unsigned short)0, (unsigned short)0, (unsigned short)0, (unsigned short)0, (unsigned short)0, (unsigned short)0, (unsigned short)0, (unsigned short)0, (unsigned short)0, (unsigned short)0, (unsigned short)0, (unsigned short)0, (unsigned short)0, (unsigned short)0, (unsigned short)0, (unsigned short)0, (unsigned short)0, (unsigned short)0, (unsigned short)0};
EXTERN_C_LINKAGE_END

/** User stub definition for variable: SignalDataStruct  gSignalDataStruBuff[100U] */
EXTERN_C_LINKAGE_START
extern SignalDataStruct  gSignalDataStruBuff[100U];
SignalDataStruct  CppTest_Variable_Stub_gSignalDataStruBuff[100U] = {{(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}};
EXTERN_C_LINKAGE_END

/** User stub definition for variable: UINT16_S gSignalCurSum */
EXTERN_C_LINKAGE_START
extern UINT16_S gSignalCurSum;
UINT16_S CppTest_Variable_Stub_gSignalCurSum = (unsigned short)0;
EXTERN_C_LINKAGE_END

/** User stub definition for variable: SignalConfigDataStruct  gSignalConfigDataStruBuff[100U] */
EXTERN_C_LINKAGE_START
extern SignalConfigDataStruct  gSignalConfigDataStruBuff[100U];
SignalConfigDataStruct  CppTest_Variable_Stub_gSignalConfigDataStruBuff[100U] = {{(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}, {(unsigned short)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0, (unsigned char)0}};
EXTERN_C_LINKAGE_END
