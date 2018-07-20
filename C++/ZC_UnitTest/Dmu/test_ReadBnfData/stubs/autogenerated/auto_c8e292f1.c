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
#include "..\..\Common\CRC32.h"
#include "..\..\Common\Convert.h"
#include "..\..\Common\Copy.h"
#include "..\..\Common\Malloc.h"
#include "..\..\cspadpt\Vcp_File_Interface.h"

#include "..\Read\ReadBnfDataTypeDefine.h"

/** Auto-generated stub definition for function: void * MemoryMalloc(UINT32_S) */
InterSysCmpVerStruct tmp;
BnfDataParseStruct readData;
UINT8_S BnfData;
EXTERN_C_LINKAGE void * MemoryMalloc (UINT32_S size) ;
EXTERN_C_LINKAGE void * CppTest_Auto_Stub_MemoryMalloc (UINT32_S size) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadInterSysCmpVersion_004"))
	{
		return &tmp;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfDataSubTabVersion_004"))
	{
		return &tmp;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfDataWriteStru_003"))
	{
		return &readData;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfDataWriteStru_004"))
	{
		return &readData;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfDataWriteStru_005"))
	{
		return &readData;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfDataWriteStru_006"))
	{
		return &readData;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfData_002"))
	{
		return &BnfData;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfData_003"))
	{
		return &BnfData;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfData_004"))
	{
		return &BnfData;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfData_005"))
	{
		return &BnfData;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfData_006"))
	{
		return &BnfData;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfData_007"))
	{
		return &BnfData;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfData_008"))
	{
		return &BnfData;
	}
	else
	{
		return (unsigned char)0;
	}
}

/** Auto-generated stub definition for function: GM_BOOL CSPADPT_Get_SpeciConfig_Addr_Size(ENUM_TYPE_CONFIG_DAT, UINT8 *, UINT32 *) */
EXTERN_C_LINKAGE GM_BOOL CSPADPT_Get_SpeciConfig_Addr_Size (ENUM_TYPE_CONFIG_DAT m_Type, UINT8 * m_Addr, UINT32 * m_Size) ;
EXTERN_C_LINKAGE GM_BOOL CppTest_Auto_Stub_CSPADPT_Get_SpeciConfig_Addr_Size (ENUM_TYPE_CONFIG_DAT m_Type, UINT8 * m_Addr, UINT32 * m_Size) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfData_003"))
	{
		* m_Size = 0;
		return 1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfData_004"))
	{
		* m_Size = 1;
		return 1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfData_007"))
	{
		* m_Size = 1;
		* m_Addr = 1;
		return 1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfData_008"))
	{
		* m_Size = 1;
		* m_Addr = 1;
		return 1;
	}
    return 0;

}

/** Auto-generated stub definition for function: UINT8_S MemoryCpy(void *, UINT32_S, const void *, UINT32_S) */
EXTERN_C_LINKAGE UINT8_S MemoryCpy (void * pDest, UINT32_S destBuffSize, const void * pSrc, UINT32_S count) ;
EXTERN_C_LINKAGE UINT8_S CppTest_Auto_Stub_MemoryCpy (void * pDest, UINT32_S destBuffSize, const void * pSrc, UINT32_S count) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_GetReadBnfDataInfo_008"))
	{
		return (unsigned char)1;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_GetReadBnfDataInfo_009"))
	{
		return (unsigned char)0;
	}
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfDataWriteStru_006"))
	{
		return (unsigned char)1;
	}
}

/** Auto-generated stub definition for function: UINT16_S ShortFromChar(const UINT8_S *) */
EXTERN_C_LINKAGE UINT16_S ShortFromChar (const UINT8_S * pInput) ;
EXTERN_C_LINKAGE UINT16_S CppTest_Auto_Stub_ShortFromChar (const UINT8_S * pInput) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfDataWriteStru_002"))
	{
		return (unsigned short)1;
	}
	else
	{
		return 1;
	}
}

/** Auto-generated stub definition for function: UINT32_S Crc32(const UINT8_S *, UINT32_S) */
EXTERN_C_LINKAGE UINT32_S Crc32 (const UINT8_S * pData, UINT32_S DataLen) ;
EXTERN_C_LINKAGE UINT32_S CppTest_Auto_Stub_Crc32 (const UINT8_S * pData, UINT32_S DataLen) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfData_002"))
	{
		return 0U;
	}
	else if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfData_008"))
	{
		return 0U;
	}
	else
	{
		return 1U;
	}
}

/** Auto-generated stub definition for function: UINT32_S LongFromChar(const UINT8_S *) */
EXTERN_C_LINKAGE UINT32_S LongFromChar (const UINT8_S * pInput) ;
EXTERN_C_LINKAGE UINT32_S CppTest_Auto_Stub_LongFromChar (const UINT8_S * pInput) 
{
	if(CppTest_IsCurrentTestCase("TestSuite_ReadBnfData_c_1b0f4b17_test_ReadBnfDataWriteStru_003"))
	{
		return 0U;
	}
	else
	{
		return 1U;
	}
}
