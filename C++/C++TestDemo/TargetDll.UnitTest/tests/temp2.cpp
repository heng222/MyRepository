#include "cpptest.h"
#include "mute.cpp"

CPPTEST_CONTEXT("C++TestDemo/TargetDll.UnitTest/源文件/dllmain.cpp");

class temp2 : public CppTest_TestSuite
{
    public:
		CPPTEST_TEST_SUITE(temp2);
		CPPTEST_TEST(test_CalcCharacterCount);
        CPPTEST_TEST_SUITE_END();
        
        void setUp();
        void tearDown();

		void test_CalcCharacterCount();
};

CPPTEST_TEST_SUITE_REGISTRATION(temp2);

void temp2::setUp()
{
}

void temp2::tearDown()
{
}

/* CPPTEST_TEST_CASE_BEGIN test_CharacterCount */
/* CPPTEST_TEST_CASE_CONTEXT int CalcCharacterCount(const char *) */
/* CPPTEST_TEST_CASE_DESCRIPTION 正常测试 */
void temp2::test_CalcCharacterCount()
{
	/* Pre-condition initialization */
	/* Initializing argument 1 (string) */ 
	const char * _string  = "Hello";
	/* Tested function call */
	int _return  = ::CalcCharacterCount_Proxy(_string);

	/* Post-condition check */
	CPPTEST_POST_CONDITION_INTEGER("5", ( _return ));
}
/* CPPTEST_TEST_CASE_END test_CharacterCount */


