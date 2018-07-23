/*****************************************************************************
 *Tested Component Name :   SignalLogicManager
 *Copyright             :   Beijing Sammode Technology Co.,Ltd. All Rights Reserved.
 *Author                :   MaChang
 *Create Date           :   2016/08/23
 *Preconditions         :   ��
 *Remarks               :   ��
****************************************************************************/

#include "cpptest.h"

CPPTEST_CONTEXT("LineDataManagerUnitTest/Signal.UnitTest/Դ�ļ�/SignalInitManager.c");
CPPTEST_TEST_SUITE_INCLUDED_TO("LineDataManagerUnitTest/Signal.UnitTest/Դ�ļ�/SignalInitManager.c");

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
*Test Case Description : ��ʼ�����ع�����źŻ���ѹ��Ϣ
*Preconditions & Stubs : GetMaskOfSignalCorssNum����ֵΪ0��
*Test Techniques       : ��
*Remarks               : ��
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
*Test Case Description : ��ʼ�����ع�����źŻ���ѹ��Ϣ
*Preconditions & Stubs : GetMaskOfSignalCorssNum����ֵΪ9,GetMaskOfSignalCorssIdBuff����ֵΪ0.
*Test Techniques       : ��
*Remarks               : ��
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
*Test Case Description : ��ʼ�����ع�����źŻ���ѹ��Ϣ
*Preconditions & Stubs : GetMaskOfSignalCorssNum����ֵΪ9,GetMaskOfSignalCorssIdBuff����ֵΪRETURN_SUCCESS��signalCrossIdBuff����ֵΪ10,_signalId����ֵΪ1.
*Test Techniques       : ��
*Remarks               : ��
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
*Test Case Description : ��ʼ�����ع�����źŻ���ѹ��Ϣ
*Preconditions & Stubs : GetMaskOfSignalCorssNum����ֵΪ9,GetMaskOfSignalCorssIdBuff����ֵΪRETURN_SUCCESS��signalCrossIdBuff����ֵΪ����ֵΪ10,_signalId����ֵΪ10.
*Test Techniques       : ��
*Remarks               : ��
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
*Test Case Description :  ��ʼ�����ع�����źŻ���ʼ��Ϣ
*Preconditions & Stubs : ��
*Test Techniques       : ��
*Remarks               : ��
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
*Test Case Description : ��ʼ�����ع�����źŻ���ʼ��Ϣ
*Preconditions & Stubs : GetMaskOfSignalLightOffNum����ֵΪ0��
*Test Techniques       : ��
*Remarks               : ��
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
*Test Case Description : ��ʼ�����ع�����źŻ���ʼ��Ϣ
*Preconditions & Stubs : GetMaskOfSignalLightOffNum����ֵΪ5,GetMaskOfSignalLightOffIdBuff����ֵΪ0
*Test Techniques       : ��
*Remarks               : ��
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
*Test Case Description : ��ʼ�����ع�����źŻ���ʼ��Ϣ
*Preconditions & Stubs : GetMaskOfSignalLightOffNum����ֵΪ5,GetMaskOfSignalLightOffIdBuff����ֵΪRETURN_SUCCESS��signalLightOffIdBuff����ֵΪ10��
*Test Techniques       : ��
*Remarks               : ��
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
*Test Case Description : ��ʼ�����ع�����źŻ���ʼ��Ϣ
*Preconditions & Stubs : GetMaskOfSignalLightOffNum����ֵΪ5,GetMaskOfSignalLightOffIdBuff����ֵΪRETURN_SUCCESS��signalLightOffIdBuff����ֵΪ10��
*Test Techniques       : ��
*Remarks               : ��
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
*Test Case Description : ��ʼ�����ع�����źŻ���ʼ��Ϣ
*Preconditions & Stubs : GetLineSignalMaxId����ֵΪ520��
*Test Techniques       : ��
*Remarks               : ��
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
*Test Case Description : ��ʼ�����ع�����źŻ���ʼ��Ϣ
*Preconditions & Stubs : GetLineSignalMaxId����ֵΪ20,GetLineSignalBelongZcId����ֵΪ11,localZcId����ֵΪ12,GetAppointObsInChangeArea����ֵΪ5��
*Test Techniques       : ��
*Remarks               : ��
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
*Test Case Description : ��ʼ�����ع�����źŻ���ʼ��Ϣ
*Preconditions & Stubs : GetLineSignalMaxId����ֵΪ20,GetLineSignalBelongZcId����ֵΪ25,localZcId����ֵΪ25,GetAppointObsInChangeArea����ֵΪ1,GetLocalZcId����ֵΪ1,GetZcSignInfoDataStrulightFlag����ֵΪ0x00U��
*Test Techniques       : ��
*Remarks               : ��
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
*Test Case Description : ��ʼ�����ع�����źŻ���ʼ��Ϣ
*Preconditions & Stubs : GetLineSignalMaxId����ֵΪ20,GetLineSignalBelongZcId����ֵΪ21,localZcId����ֵΪ25,GetAppointObsInChangeArea����ֵΪRETURN_SUCCESS,GetLocalZcId����ֵΪ21,GetZcSignInfoDataStrulightFlag����ֵΪ0x01U��
*Test Techniques       : ��
*Remarks               : ��
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
*Test Case Description : ��ʼ�����ع�����źŻ���ʼ��Ϣ
*Preconditions & Stubs : GetLineSignalMaxId����ֵΪ20,GetLineSignalBelongZcId����ֵΪ25,GetAppointObsInChangeArea����ֵΪRETURN_SUCCESS,GetLocalZcId����ֵΪ21,GetZcSignInfoDataStrulightFlag����ֵΪ0x02U��
*Test Techniques       : ��
*Remarks               : ��
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
*Test Case Description : ��ʼ�����ع�����źŻ���ʼ��Ϣ
*Preconditions & Stubs : GetLineSignalMaxId����ֵΪ20,GetLineSignalBelongZcId����ֵΪ25,GetAppointObsInChangeArea����ֵΪRETURN_SUCCESS,GetLocalZcId����ֵΪ25,GetZcSignInfoDataStrulightFlag����ֵΪ0x03U��
*Test Techniques       : ��
*Remarks               : ��
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
*Test Case Description : ��ʼ�����ع�����źŻ���ʼ��Ϣ
*Preconditions & Stubs : GetLineSignalMaxId����ֵΪ20,GetLineSignalBelongZcId����ֵΪ25,GetAppointObsInChangeArea����ֵΪRETURN_SUCCESS,GetLocalZcId����ֵΪ21,GetZcSignInfoDataStrulightFlag����ֵΪ0��
*Test Techniques       : ��
*Remarks               : ��
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
