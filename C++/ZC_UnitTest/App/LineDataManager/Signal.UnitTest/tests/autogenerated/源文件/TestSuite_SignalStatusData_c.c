#include "cpptest.h"

CPPTEST_CONTEXT("LineDataManagerUnitTest/Signal.UnitTest/源文件/SignalStatusData.c");
CPPTEST_TEST_SUITE_INCLUDED_TO("LineDataManagerUnitTest/Signal.UnitTest/源文件/SignalStatusData.c");

CPPTEST_TEST_SUITE(TestSuite_SignalStatusData_c_330d04ee);
CPPTEST_TEST(TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalCrossStatus_001);
CPPTEST_TEST(TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalCrossStatus_002);
CPPTEST_TEST(TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalLightOffStatus_001);
CPPTEST_TEST(TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalLightOffStatus_002);
CPPTEST_TEST(TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalStatus_001);
CPPTEST_TEST(TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalStatusData_001);
CPPTEST_TEST(TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalStatus_003);
CPPTEST_TEST(TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalCrossStatus_001);
CPPTEST_TEST(TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalCrossStatus_002);
CPPTEST_TEST(TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalCrossStatus_003);
CPPTEST_TEST(TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalCrossStatus_004);
CPPTEST_TEST(TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalLightOffStatus_001);
CPPTEST_TEST(TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalLightOffStatus_002);
CPPTEST_TEST(TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalLightOffStatus_003);
CPPTEST_TEST(TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalLightOffStatus_004);
CPPTEST_TEST(TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalStatus_001);
CPPTEST_TEST(TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalStatus_002);
CPPTEST_TEST(TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalStatus_003);
CPPTEST_TEST(TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalStatus_004);
CPPTEST_TEST_SUITE_END();
        

void TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalCrossStatus_001();
void TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalCrossStatus_002();
void TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalLightOffStatus_001();
void TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalLightOffStatus_002();
void TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalStatus_001();
void TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalStatusData_001();
void TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalStatus_003();
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalCrossStatus_001();
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalCrossStatus_002();
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalCrossStatus_003();
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalCrossStatus_004();
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalLightOffStatus_001();
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalLightOffStatus_002();
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalLightOffStatus_003();
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalLightOffStatus_004();
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalStatus_001();
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalStatus_002();
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalStatus_003();
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalStatus_004();
CPPTEST_TEST_SUITE_REGISTRATION(TestSuite_SignalStatusData_c_330d04ee);

void TestSuite_SignalStatusData_c_330d04ee_setUp()
{
}

void TestSuite_SignalStatusData_c_330d04ee_tearDown()
{
}


/*****************************************************************************
*Test Case Description : 设置信号机列车跨压信号机状态。
*Preconditions & Stubs : GetSignalConfigBufIndex返回值为0,GetSignalSum返回值为5。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_GetSignalCrossStatus_001 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S GetSignalCrossStatus(const UINT16_S) */
void TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalCrossStatus_001()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 2;
    {
        /* Tested function call */
        UINT8_S _return  = GetSignalCrossStatus(_signalId);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(0, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_GetSignalCrossStatus_001 */

/*****************************************************************************
*Test Case Description : 设置信号机列车跨压信号机状态。
*Preconditions & Stubs : GetSignalConfigBufIndex返回值为0,GetSignalSum返回值为0。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_GetSignalCrossStatus_002 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S GetSignalCrossStatus(const UINT16_S) */
void TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalCrossStatus_002()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0U;
    {
        /* Tested function call */
        UINT8_S _return  = GetSignalCrossStatus(_signalId);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_ERROR, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_GetSignalCrossStatus_002 */

/*****************************************************************************
*Test Case Description : 获取信号机信号机亮灭状态
*Preconditions & Stubs : GetSignalConfigBufIndex返回值为0,GetSignalSum返回值为0。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_GetSignalLightOffStatus_001 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S GetSignalLightOffStatus(const UINT16_S) */
void TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalLightOffStatus_001()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    {
        /* Tested function call */
        UINT8_S _return  = GetSignalLightOffStatus(_signalId);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_ERROR, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_GetSignalLightOffStatus_001 */

/*****************************************************************************
*Test Case Description : 获取信号机信号机亮灭状态
*Preconditions & Stubs : GetSignalConfigBufIndex返回值为0,GetSignalSum返回值为5。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_GetSignalLightOffStatus_002 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S GetSignalLightOffStatus(const UINT16_S) */
void TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalLightOffStatus_002()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    {
        /* Tested function call */
        UINT8_S _return  = GetSignalLightOffStatus(_signalId);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(0, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_GetSignalLightOffStatus_002 */

/*****************************************************************************
*Test Case Description : 获取信号机当前状态
*Preconditions & Stubs : GetSignalConfigBufIndex返回值为0,GetSignalSum返回值为0。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_GetSignalStatus_001 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S GetSignalStatus(const UINT16_S) */
void TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalStatus_001()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    {
        /* Tested function call */
        UINT8_S _return  = GetSignalStatus(_signalId);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_ERROR, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_GetSignalStatus_001 */


/*****************************************************************************
*Test Case Description : 设置信号机当前状态
*Preconditions & Stubs : GetSignalConfigBufIndex返回值为0,GetSignalSum返回值为0。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_GetSignalStatusData_001 */
/* CPPTEST_TEST_CASE_CONTEXT SignalDataStruct * GetSignalStatusData(void) */
void TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalStatusData_001()
{
    /* Pre-condition initialization */
    {
        /* Tested function call */
        SignalDataStruct * _return  = GetSignalStatusData();
        /* Post-condition check */

    }
}
/* CPPTEST_TEST_CASE_END test_GetSignalStatusData_001 */


/*****************************************************************************
*Test Case Description : 获取信号机当前状态
*Preconditions & Stubs : GetSignalConfigBufIndex返回值为0,GetSignalSum返回值为5。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_GetSignalStatus_003 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S GetSignalStatus(const UINT16_S) */
void TestSuite_SignalStatusData_c_1522c3a2_test_GetSignalStatus_003()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    {
        /* Tested function call */
        UINT8_S _return  = GetSignalStatus(_signalId);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(0, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_GetSignalStatus_003 */

/*****************************************************************************
*Test Case Description : 获取信号机当前状态
*Preconditions & Stubs : GetSignalConfigBufIndex返回值为0,GetSignalSum返回值为0。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_SetSignalCrossStatus_001 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S SetSignalCrossStatus(const UINT16_S, UINT8_S) */
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalCrossStatus_001()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    /* Initializing argument 2 (crossStatus) */ 
    UINT8_S _crossStatus  = 0;
    {
        /* Tested function call */
        UINT8_S _return  = SetSignalCrossStatus(_signalId, _crossStatus);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_ERROR, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_SetSignalCrossStatus_001 */


/*****************************************************************************
*Test Case Description : 获取信号机当前状态
*Preconditions & Stubs : GetSignalConfigBufIndex返回值为0,GetSignalSum返回值为5,crossStatus返回值为0。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_SetSignalCrossStatus_002 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S SetSignalCrossStatus(const UINT16_S, UINT8_S) */
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalCrossStatus_002()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    /* Initializing argument 2 (crossStatus) */ 
    UINT8_S _crossStatus  = 0;
    {
        /* Tested function call */
        UINT8_S _return  = SetSignalCrossStatus(_signalId, _crossStatus);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_ERROR, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_SetSignalCrossStatus_002 */

/*****************************************************************************
*Test Case Description : 获取信号机当前状态
*Preconditions & Stubs : GetSignalConfigBufIndex返回值为0,GetSignalSum返回值为5,crossStatus返回值为SIGNAL_TRAIN_ALREADY_CROSS。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_SetSignalCrossStatus_003 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S SetSignalCrossStatus(const UINT16_S, UINT8_S) */
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalCrossStatus_003()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    /* Initializing argument 2 (crossStatus) */ 
    UINT8_S _crossStatus  = SIGNAL_TRAIN_ALREADY_CROSS;
    {
        /* Tested function call */
        UINT8_S _return  = SetSignalCrossStatus(_signalId, _crossStatus);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_SUCCESS, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_SetSignalCrossStatus_003 */

/*****************************************************************************
*Test Case Description : 获取信号机当前状态
*Preconditions & Stubs : GetSignalConfigBufIndex返回值为0,GetSignalSum返回值为5,crossStatus返回值为SIGNAL_TRAIN_NOT_CROSS。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_SetSignalCrossStatus_004 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S SetSignalCrossStatus(const UINT16_S, UINT8_S) */
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalCrossStatus_004()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    /* Initializing argument 2 (crossStatus) */ 
    UINT8_S _crossStatus  = SIGNAL_TRAIN_NOT_CROSS;
    {
        /* Tested function call */
        UINT8_S _return  = SetSignalCrossStatus(_signalId, _crossStatus);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_SUCCESS, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_SetSignalCrossStatus_004 */

/*****************************************************************************
*Test Case Description : 获取信号机当前状态
*Preconditions & Stubs : GetSignalConfigBufIndex返回值为0,GetSignalSum返回值为0。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_SetSignalLightOffStatus_001 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S SetSignalLightOffStatus(const UINT16_S, UINT8_S) */
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalLightOffStatus_001()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    /* Initializing argument 2 (lightOffStatus) */ 
    UINT8_S _lightOffStatus  = 0;
    {
        /* Tested function call */
        UINT8_S _return  = SetSignalLightOffStatus(_signalId, _lightOffStatus);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_ERROR, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_SetSignalLightOffStatus_001 */

/*****************************************************************************
*Test Case Description : 获取信号机当前状态
*Preconditions & Stubs : GetSignalConfigBufIndex返回值为0,GetSignalSum返回值为5,lightOffStatus返回值为0。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_SetSignalLightOffStatus_002 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S SetSignalLightOffStatus(const UINT16_S, UINT8_S) */
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalLightOffStatus_002()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    /* Initializing argument 2 (lightOffStatus) */ 
    UINT8_S _lightOffStatus  = 0;
    {
        /* Tested function call */
        UINT8_S _return  = SetSignalLightOffStatus(_signalId, _lightOffStatus);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_ERROR, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_SetSignalLightOffStatus_002 */

/*****************************************************************************
*Test Case Description : 获取信号机当前状态
*Preconditions & Stubs : GetSignalConfigBufIndex返回值为0,GetSignalSum返回值为5,lightOffStatus返回值为SIGNAL_OFF_COMMAND。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_SetSignalLightOffStatus_003 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S SetSignalLightOffStatus(const UINT16_S, UINT8_S) */
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalLightOffStatus_003()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    /* Initializing argument 2 (lightOffStatus) */ 
    UINT8_S _lightOffStatus  = SIGNAL_OFF_COMMAND;
    {
        /* Tested function call */
        UINT8_S _return  = SetSignalLightOffStatus(_signalId, _lightOffStatus);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_SUCCESS, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_SetSignalLightOffStatus_003 */

/*****************************************************************************
*Test Case Description : 获取信号机当前状态
*Preconditions & Stubs : GetSignalConfigBufIndex返回值为0,GetSignalSum返回值为5,lightOffStatus返回值为SIGNAL_LIGHT_COMMAND。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_SetSignalLightOffStatus_004 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S SetSignalLightOffStatus(const UINT16_S, UINT8_S) */
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalLightOffStatus_004()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    /* Initializing argument 2 (lightOffStatus) */ 
    UINT8_S _lightOffStatus  = SIGNAL_LIGHT_COMMAND;
    {
        /* Tested function call */
        UINT8_S _return  = SetSignalLightOffStatus(_signalId, _lightOffStatus);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_SUCCESS, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_SetSignalLightOffStatus_004 */

/*****************************************************************************
*Test Case Description : 获取信号机当前状态
*Preconditions & Stubs : GetSignalConfigBufIndex返回值为0,GetSignalSum返回值为0。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_SetSignalStatus_001 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S SetSignalStatus(const UINT16_S, UINT8_S) */
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalStatus_001()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    /* Initializing argument 2 (signalStatus) */ 
    UINT8_S _signalStatus  = 0;
    {
        /* Tested function call */
        UINT8_S _return  = SetSignalStatus(_signalId, _signalStatus);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_ERROR, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_SetSignalStatus_001 */


/*****************************************************************************
*Test Case Description : 获取信号机当前状态
*Preconditions & Stubs : GetSignalConfigBufIndex返回值为0,GetSignalSum返回值为5,signalStatus返回值为0。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_SetSignalStatus_002 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S SetSignalStatus(const UINT16_S, UINT8_S) */
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalStatus_002()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    /* Initializing argument 2 (signalStatus) */ 
    UINT8_S _signalStatus  = 0;
    {
        /* Tested function call */
        UINT8_S _return  = SetSignalStatus(_signalId, _signalStatus);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_ERROR, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_SetSignalStatus_002 */

/*****************************************************************************
*Test Case Description : 获取信号机当前状态
*Preconditions & Stubs : GetSignalConfigBufIndex返回值为0,GetSignalSum返回值为5,signalStatus返回值为SIGNAL_STATE_PASS。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_SetSignalStatus_003 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S SetSignalStatus(const UINT16_S, UINT8_S) */
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalStatus_003()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    /* Initializing argument 2 (signalStatus) */ 
    UINT8_S _signalStatus  = SIGNAL_STATE_PASS;
    {
        /* Tested function call */
        UINT8_S _return  = SetSignalStatus(_signalId, _signalStatus);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_SUCCESS, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_SetSignalStatus_003 */

/*****************************************************************************
*Test Case Description : 获取信号机当前状态
*Preconditions & Stubs : GetSignalConfigBufIndex返回值为0,GetSignalSum返回值为5,signalStatus返回值为SIGNAL_STATE_STOP。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_SetSignalStatus_004 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S SetSignalStatus(const UINT16_S, UINT8_S) */
void TestSuite_SignalStatusData_c_1522c3a2_test_SetSignalStatus_004()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    /* Initializing argument 2 (signalStatus) */ 
    UINT8_S _signalStatus  = SIGNAL_STATE_STOP;
    {
        /* Tested function call */
        UINT8_S _return  = SetSignalStatus(_signalId, _signalStatus);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_SUCCESS, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_SetSignalStatus_004 */
