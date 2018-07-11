#include "cpptest.h"
#include "..\TargetDll\Exercises.h"

//CPPTEST_CONTEXT("C++TestDemo/TargetDll/源文件/DllExercise1-5.cpp");

CPPTEST_CONTEXT("C++TestDemo/TargetDll/Exercises.cpp");
CPPTEST_TEST_SUITE_INCLUDED_TO("C++TestDemo/TargetDll/Exercises.cpp");

class ExercisesTestSuite : public CppTest_TestSuite
{
    public:
		CPPTEST_TEST_SUITE(ExercisesTestSuite);
		CPPTEST_TEST(test_CalcCharacterCount);
        CPPTEST_TEST_SUITE_END();
        
        void setUp();
        void tearDown();

		void test_CalcCharacterCount();
};

CPPTEST_TEST_SUITE_REGISTRATION(ExercisesTestSuite);

void ExercisesTestSuite::setUp()
{
}

void ExercisesTestSuite::tearDown()
{
}

/* CPPTEST_TEST_CASE_BEGIN test_CharacterCount */
/* CPPTEST_TEST_CASE_CONTEXT int CalcCharacterCount(const char *) */
/* CPPTEST_TEST_CASE_DESCRIPTION 正常测试 */
void ExercisesTestSuite::test_CalcCharacterCount()
{
	/* Pre-condition initialization */
	/* Initializing argument 1 (string) */ 
	const char * _string  = "Hello";
	/* Tested function call */
	int _return  = ::CalcCharacterCount(_string);

	/* Post-condition check */
	CPPTEST_POST_CONDITION_INTEGER("5", ( _return ));
}
/* CPPTEST_TEST_CASE_END test_CharacterCount */
