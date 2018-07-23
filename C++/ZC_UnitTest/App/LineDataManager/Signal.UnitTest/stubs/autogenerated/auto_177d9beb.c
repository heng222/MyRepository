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
#include "..\..\..\PlatformAdapter\PlatformLog\AdapterLog.h"

/** User stub definition for function: UINT8_S AdptAppLogPrintf(UINT8_S, const CHAR_S *, ...) */
EXTERN_C_LINKAGE UINT8_S AdptAppLogPrintf (UINT8_S chRunSystem, const CHAR_S * lpszFormat, ...) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Stub_AdptAppLogPrintf (UINT8_S chRunSystem, const CHAR_S * lpszFormat, ...) 
{
    return (unsigned char)0;
}
