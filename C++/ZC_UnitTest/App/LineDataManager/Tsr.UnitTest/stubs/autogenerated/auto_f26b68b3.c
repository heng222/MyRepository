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
#include "..\..\DmuZc\DataHandle\DmuZcDataHandle.h"
#include "..\..\SysDataManager\SysConfigData.h"

/** Auto-generated stub definition for function: UINT16_S GetLineMaxTSRSpeed(void) */
EXTERN_C_LINKAGE UINT16_S GetLineMaxTSRSpeed () ;
EXTERN_C_LINKAGE UINT16_S CppTest_Auto_Stub_GetLineMaxTSRSpeed (void) 
{
    return (unsigned short)0;
}

/** Auto-generated stub definition for function: UINT8_S CheckLogicIdBetweenPoints(const UINT8_S, const UINT16_S, const UINT32_S, const UINT16_S, const UINT32_S, const UINT8_S, UINT16_S *) */
EXTERN_C_LINKAGE UINT8_S CheckLogicIdBetweenPoints (const UINT8_S selfFlag, const UINT16_S headSeg, const UINT32_S headOffset, const UINT16_S TailSeg, const UINT32_S TailOffset, const UINT8_S direction, UINT16_S  logicSectionId[]) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Auto_Stub_CheckLogicIdBetweenPoints (const UINT8_S selfFlag, const UINT16_S headSeg, const UINT32_S headOffset, const UINT16_S TailSeg, const UINT32_S TailOffset, const UINT8_S direction, UINT16_S  logicSectionId[]) 
{
    return (unsigned char)0;
}

/** Auto-generated stub definition for function: UINT8_S CheckLocRelationBetweenTwoPoints(const UINT16_S, const UINT32_S, const UINT16_S, const UINT32_S, UINT8_S) */
EXTERN_C_LINKAGE UINT8_S CheckLocRelationBetweenTwoPoints (const UINT16_S seg1, const UINT32_S offset1, const UINT16_S seg2, const UINT32_S offset2, UINT8_S dir) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Auto_Stub_CheckLocRelationBetweenTwoPoints (const UINT16_S seg1, const UINT32_S offset1, const UINT16_S seg2, const UINT32_S offset2, UINT8_S dir) 
{
    return (unsigned char)0;
}
