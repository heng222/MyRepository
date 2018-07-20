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
#include "..\..\Common\CRC32.h"
#include "..\..\Common\Convert.h"
#include "..\..\Common\Copy.h"
#include "..\..\Common\Malloc.h"
#include "..\..\cspadpt\Vcp_File_Interface.h"

#include "..\Read\ReadBnfDataTypeDefine.h"
/** User stub definition for function: void ReadInterSysCmpVersion(const UINT8_S *) */
EXTERN_C_LINKAGE void ReadInterSysCmpVersion (const UINT8_S * pBnfData) ;
EXTERN_C_LINKAGE void CppTest_Stub_ReadInterSysCmpVersion (const UINT8_S * pBnfData) 
{
}

/** User stub definition for function: void ReadBnfDataSubTabVersion(const UINT8_S *) */
EXTERN_C_LINKAGE void ReadBnfDataSubTabVersion (const UINT8_S * pBnfData) ;
EXTERN_C_LINKAGE void CppTest_Stub_ReadBnfDataSubTabVersion (const UINT8_S * pBnfData) 
{
}

/** User stub definition for function: INT8_S ReadBnfDataWriteStru(const UINT8_S *, const INT32_S) */
EXTERN_C_LINKAGE INT8_S ReadBnfDataWriteStru (const UINT8_S * pdata, const INT32_S dataHeadLen) ;
EXTERN_C_LINKAGE INT8_S CppTest_Stub_ReadBnfDataWriteStru (const UINT8_S * pdata, const INT32_S dataHeadLen) 
{
    return (signed char)1;
}
