/*****************************************************************************
 *Tested Component Name :   SignalLogicManager
 *Copyright             :   Beijing Sammode Technology Co.,Ltd. All Rights Reserved.
 *Author                :   MaChang
 *Create Date           :   2016/08/23
 *Preconditions         :   无
 *Remarks               :   无
****************************************************************************/

#include "cpptest.h"

CPPTEST_CONTEXT("LineDataManagerUnitTest/Signal.UnitTest/源文件/SignalInitManager.c");
CPPTEST_TEST_SUITE_INCLUDED_TO("LineDataManagerUnitTest/Signal.UnitTest/源文件/SignalInitManager.c");

CPPTEST_TEST_SUITE(TestSuite_SignalInitManager_c_85c7e225);
CPPTEST_TEST(TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalCorssType_001);
CPPTEST_TEST(TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalCorssType_002);
CPPTEST_TEST(TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalCorssType_003);
CPPTEST_TEST(TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalCorssType_004);
CPPTEST_TEST(TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalInitializationData_001);
CPPTEST_TEST(TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLightOffType_001);
CPPTEST_TEST(TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLightOffType_002);
CPPTEST_TEST(TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLightOffType_003);
CPPTEST_TEST(TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLightOffType_004);
CPPTEST_TEST(TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_001);
CPPTEST_TEST(TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_002);
CPPTEST_TEST(TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_003);
CPPTEST_TEST(TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_004);
CPPTEST_TEST(TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_005);
CPPTEST_TEST(TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_006);
CPPTEST_TEST(TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_007);
CPPTEST_TEST_SUITE_END();
        

void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalCorssType_001();
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalCorssType_002();
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalCorssType_003();
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalCorssType_004();
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalInitializationData_001();
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLightOffType_001();
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLightOffType_002();
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLightOffType_003();
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLightOffType_004();
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_001();
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_002();
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_003();
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_004();
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_005();
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_006();
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_007();
CPPTEST_TEST_SUITE_REGISTRATION(TestSuite_SignalInitManager_c_85c7e225);

void TestSuite_SignalInitManager_c_85c7e225_setUp()
{
}

void TestSuite_SignalInitManager_c_85c7e225_tearDown()
{
}


/*****************************************************************************
*Test Case Description : 初始化本地管理的信号机跨压信息
*Preconditions & Stubs : GetMaskOfSignalCorssNum返回值为0。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_InitSignalCorssType_001 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S InitSignalCorssType(const UINT16_S) */
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalCorssType_001()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    {
        /* Tested function call */
        UINT8_S _return  = InitSignalCorssType(_signalId);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_ERROR, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_InitSignalCorssType_001 */

/*****************************************************************************
*Test Case Description : 初始化本地管理的信号机跨压信息
*Preconditions & Stubs : GetMaskOfSignalCorssNum返回值为9,GetMaskOfSignalCorssIdBuff返回值为0.
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_InitSignalCorssType_002 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S InitSignalCorssType(const UINT16_S) */
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalCorssType_002()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    {
        /* Tested function call */
        UINT8_S _return  = InitSignalCorssType(_signalId);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_ERROR, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_InitSignalCorssType_002 */

/*****************************************************************************
*Test Case Description : 初始化本地管理的信号机跨压信息
*Preconditions & Stubs : GetMaskOfSignalCorssNum返回值为9,GetMaskOfSignalCorssIdBuff返回值为RETURN_SUCCESS，signalCrossIdBuff返回值为10,_signalId返回值为1.
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_InitSignalCorssType_003 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S InitSignalCorssType(const UINT16_S) */
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalCorssType_003()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 1u;
    {
        /* Tested function call */
        UINT8_S _return  = InitSignalCorssType(_signalId);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(FLAG_UNSET, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_InitSignalCorssType_003 */

/*****************************************************************************
*Test Case Description : 初始化本地管理的信号机跨压信息
*Preconditions & Stubs : GetMaskOfSignalCorssNum返回值为9,GetMaskOfSignalCorssIdBuff返回值为RETURN_SUCCESS，signalCrossIdBuff返回值为返回值为10,_signalId返回值为10.
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_InitSignalCorssType_004 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S InitSignalCorssType(const UINT16_S) */
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalCorssType_004()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 10u;
    {
        /* Tested function call */
        UINT8_S _return  = InitSignalCorssType(_signalId);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(FLAG_SET, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_InitSignalCorssType_004 */

/*****************************************************************************
*Test Case Description :  初始化本地管理的信号机初始信息
*Preconditions & Stubs : 无
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_InitSignalInitializationData_001 */
/* CPPTEST_TEST_CASE_CONTEXT void InitSignalInitializationData(void) */
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalInitializationData_001()
{
    /* Pre-condition initialization */
    /* Initializing global variable gSignalCurSum */ 
    {
         gSignalCurSum  = 0u;
    }
    {
        /* Tested function call */
        InitSignalInitializationData();
        /* Post-condition check */
    }
}
/* CPPTEST_TEST_CASE_END test_InitSignalInitializationData_001 */


/*****************************************************************************
*Test Case Description : 初始化本地管理的信号机初始信息
*Preconditions & Stubs : GetMaskOfSignalLightOffNum返回值为0。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_InitSignalLightOffType_001 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S InitSignalLightOffType(const UINT16_S) */
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLightOffType_001()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    {
        /* Tested function call */
        UINT8_S _return  = InitSignalLightOffType(_signalId);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_ERROR, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_InitSignalLightOffType_001 */

/*****************************************************************************
*Test Case Description : 初始化本地管理的信号机初始信息
*Preconditions & Stubs : GetMaskOfSignalLightOffNum返回值为5,GetMaskOfSignalLightOffIdBuff返回值为0
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_InitSignalLightOffType_002 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S InitSignalLightOffType(const UINT16_S) */
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLightOffType_002()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 0u;
    {
        /* Tested function call */
        UINT8_S _return  = InitSignalLightOffType(_signalId);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_ERROR, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_InitSignalLightOffType_002 */

/*****************************************************************************
*Test Case Description : 初始化本地管理的信号机初始信息
*Preconditions & Stubs : GetMaskOfSignalLightOffNum返回值为5,GetMaskOfSignalLightOffIdBuff返回值为RETURN_SUCCESS，signalLightOffIdBuff返回值为10。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_InitSignalLightOffType_003 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S InitSignalLightOffType(const UINT16_S) */
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLightOffType_003()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 1u;
    {
        /* Tested function call */
        UINT8_S _return  = InitSignalLightOffType(_signalId);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(FLAG_UNSET, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_InitSignalLightOffType_003 */

/*****************************************************************************
*Test Case Description : 初始化本地管理的信号机初始信息
*Preconditions & Stubs : GetMaskOfSignalLightOffNum返回值为5,GetMaskOfSignalLightOffIdBuff返回值为RETURN_SUCCESS，signalLightOffIdBuff返回值为10。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_InitSignalLightOffType_004 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S InitSignalLightOffType(const UINT16_S) */
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLightOffType_004()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (signalId) */ 
    UINT16_S _signalId  = 10u;
    {
        /* Tested function call */
        UINT8_S _return  = InitSignalLightOffType(_signalId);
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(FLAG_SET, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_InitSignalLightOffType_004 */

/*****************************************************************************
*Test Case Description : 初始化本地管理的信号机初始信息
*Preconditions & Stubs : GetLineSignalMaxId返回值为520。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_InitSignalLocalInfo_001 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S InitSignalLocalInfo(void) */
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_001()
{
    /* Pre-condition initialization */
    /* Initializing global variable gSignalCurSum */ 
    {
         gSignalCurSum  = 0u;
    }
    {
        /* Tested function call */
        UINT8_S _return  = InitSignalLocalInfo();
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_ERROR, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_InitSignalLocalInfo_001 */

/*****************************************************************************
*Test Case Description : 初始化本地管理的信号机初始信息
*Preconditions & Stubs : GetLineSignalMaxId返回值为20,GetLineSignalBelongZcId返回值为11,localZcId返回值为12,GetAppointObsInChangeArea返回值为5。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_InitSignalLocalInfo_002 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S InitSignalLocalInfo(void) */
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_002()
{
    /* Pre-condition initialization */
    /* Initializing global variable gSignalCurSum */ 
    {
         gSignalCurSum  = 0u;
    }
    {
        /* Tested function call */
        UINT8_S _return  = InitSignalLocalInfo();
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_SUCCESS, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_InitSignalLocalInfo_002 */

/*****************************************************************************
*Test Case Description : 初始化本地管理的信号机初始信息
*Preconditions & Stubs : GetLineSignalMaxId返回值为20,GetLineSignalBelongZcId返回值为25,localZcId返回值为25,GetAppointObsInChangeArea返回值为1,GetLocalZcId返回值为1,GetZcSignInfoDataStrulightFlag返回值为0x00U。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_InitSignalLocalInfo_003 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S InitSignalLocalInfo(void) */
UINT8_S ID;
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_003()
{
    /* Pre-condition initialization */
    /* Initializing global variable gSignalCurSum */ 
	ID = 1 ;
    {
         gSignalCurSum  = 0u;
    }
    {
        /* Tested function call */
        UINT8_S _return  = InitSignalLocalInfo();
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_SUCCESS, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_InitSignalLocalInfo_003 */

/*****************************************************************************
*Test Case Description : 初始化本地管理的信号机初始信息
*Preconditions & Stubs : GetLineSignalMaxId返回值为20,GetLineSignalBelongZcId返回值为21,localZcId返回值为25,GetAppointObsInChangeArea返回值为RETURN_SUCCESS,GetLocalZcId返回值为21,GetZcSignInfoDataStrulightFlag返回值为0x01U。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_InitSignalLocalInfo_004 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S InitSignalLocalInfo(void) */
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_004()
{
    /* Pre-condition initialization */
    /* Initializing global variable gSignalCurSum */ 
    {
         gSignalCurSum  = 0u;
    }
    {
        /* Tested function call */
        UINT8_S _return  = InitSignalLocalInfo();
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_SUCCESS, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_InitSignalLocalInfo_004 */

/*****************************************************************************
*Test Case Description : 初始化本地管理的信号机初始信息
*Preconditions & Stubs : GetLineSignalMaxId返回值为20,GetLineSignalBelongZcId返回值为25,GetAppointObsInChangeArea返回值为RETURN_SUCCESS,GetLocalZcId返回值为21,GetZcSignInfoDataStrulightFlag返回值为0x02U。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_InitSignalLocalInfo_005 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S InitSignalLocalInfo(void) */
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_005()
{
    /* Pre-condition initialization */
    /* Initializing global variable gSignalCurSum */ 
    {
         gSignalCurSum  = 0u;
    }
    {
        /* Tested function call */
        UINT8_S _return  = InitSignalLocalInfo();
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_SUCCESS, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_InitSignalLocalInfo_005 */

/*****************************************************************************
*Test Case Description : 初始化本地管理的信号机初始信息
*Preconditions & Stubs : GetLineSignalMaxId返回值为20,GetLineSignalBelongZcId返回值为25,GetAppointObsInChangeArea返回值为RETURN_SUCCESS,GetLocalZcId返回值为25,GetZcSignInfoDataStrulightFlag返回值为0x03U。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_InitSignalLocalInfo_006 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S InitSignalLocalInfo(void) */
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_006()
{
    /* Pre-condition initialization */
    /* Initializing global variable gSignalCurSum */ 
    {
         gSignalCurSum  = 0u;
    }
    {
        /* Tested function call */
        UINT8_S _return  = InitSignalLocalInfo();
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_SUCCESS, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_InitSignalLocalInfo_006 */

/*****************************************************************************
*Test Case Description : 初始化本地管理的信号机初始信息
*Preconditions & Stubs : GetLineSignalMaxId返回值为20,GetLineSignalBelongZcId返回值为25,GetAppointObsInChangeArea返回值为RETURN_SUCCESS,GetLocalZcId返回值为21,GetZcSignInfoDataStrulightFlag返回值为0。
*Test Techniques       : 无
*Remarks               : 无
******************************************************************************/
/* CPPTEST_TEST_CASE_BEGIN test_InitSignalLocalInfo_007 */
/* CPPTEST_TEST_CASE_CONTEXT UINT8_S InitSignalLocalInfo(void) */
void TestSuite_SignalInitManager_c_5b12d5c_test_InitSignalLocalInfo_007()
{
    /* Pre-condition initialization */
    /* Initializing global variable gSignalCurSum */ 
    {
         gSignalCurSum  = 0u;
    }
    {
        /* Tested function call */
        UINT8_S _return  = InitSignalLocalInfo();
        /* Post-condition check */
        CPPTEST_ASSERT_EQUAL(RETURN_SUCCESS, ( _return ));
    }
}
/* CPPTEST_TEST_CASE_END test_InitSignalLocalInfo_007 */
