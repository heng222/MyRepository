#include "cpptest.h"

extern int CalcCharacterCount_Proxy(const char*);

CPPTEST_CONTEXT("C++TestDemo/TargetDll.UnitTest/tests/Mute.cpp");

class MuteTestSuite : public CppTest_TestSuite
{
    public:
        CPPTEST_TEST_SUITE(MuteTestSuite);
        CPPTEST_TEST(test_CalcCharacterCount_Proxy);
        CPPTEST_TEST_SUITE_END();
        
        void setUp();
        void tearDown();

        void test_CalcCharacterCount_Proxy();
};

CPPTEST_TEST_SUITE_REGISTRATION(MuteTestSuite);

void MuteTestSuite::setUp()
{
}

void MuteTestSuite::tearDown()
{
}

/* CPPTEST_TEST_CASE_BEGIN test_CalcCharacterCount_Proxy */
/* CPPTEST_TEST_CASE_CONTEXT int CalcCharacterCount_Proxy(const char *) */
void MuteTestSuite::test_CalcCharacterCount_Proxy()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (value) */ 
    const char * _value  = "Hello";
    /* Tested function call */
    int _return  = ::CalcCharacterCount_Proxy(_value);
    /* Post-condition check */
    CPPTEST_POST_CONDITION_INTEGER(" _return", ( _return ));
}
/* CPPTEST_TEST_CASE_END test_CalcCharacterCount_Proxy */
