#include "cpptest.h"

CPPTEST_CONTEXT("LineDataManagerUnitTest/Tsr.UnitTest/源文件/TsrInitManager.c");
CPPTEST_TEST_SUITE_INCLUDED_TO("LineDataManagerUnitTest/Tsr.UnitTest/源文件/TsrInitManager.c");

CPPTEST_TEST_SUITE(TestSuite_TsrInitManager_c_c16e6ba3);
CPPTEST_TEST(TestSuite_TsrInitManager_c_c16e6ba3_test_InitTsrLocalInfo_001);
CPPTEST_TEST_SUITE_END();
        

void TestSuite_TsrInitManager_c_c16e6ba3_test_InitTsrLocalInfo_001();
CPPTEST_TEST_SUITE_REGISTRATION(TestSuite_TsrInitManager_c_c16e6ba3);

void TestSuite_TsrInitManager_c_c16e6ba3_setUp()
{
}

void TestSuite_TsrInitManager_c_c16e6ba3_tearDown()
{
}


/* CPPTEST_TEST_CASE_BEGIN test_InitTsrLocalInfo_001 */
/* CPPTEST_TEST_CASE_CONTEXT void InitTsrLocalInfo(void) */
void TestSuite_TsrInitManager_c_c16e6ba3_test_InitTsrLocalInfo_001()
{
    /* Pre-condition initialization */
    /* Initializing global variable gTsrOfZcCurSum */ 
    {
         gTsrOfZcCurSum  = 0u;
    }
    {
        /* Tested function call */
        InitTsrLocalInfo();
        /* Post-condition check */
        CPPTEST_POST_CONDITION_UINTEGER("UINT16_S gTsrOfZcCurSum", ( gTsrOfZcCurSum ));
    }
}
/* CPPTEST_TEST_CASE_END test_InitTsrLocalInfo_001 */
