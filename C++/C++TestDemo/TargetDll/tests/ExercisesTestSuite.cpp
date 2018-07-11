#include "cpptest.h"
#include "Exercises.h"

CPPTEST_CONTEXT("C++TestDemo/TargetDll/Ô´ÎÄ¼þ/Exercises.cpp");

class ExercisesTestSuite : public CppTest_TestSuite
{
    public:
        CPPTEST_TEST_SUITE(ExercisesTestSuite);
        CPPTEST_TEST(test_CalcGreatestCommonDivisor_1);
        CPPTEST_TEST(test_CalcGreatestCommonDivisor_2);
        CPPTEST_TEST(test_CalcCharacterCount_1);
        CPPTEST_TEST_SUITE_END();
        
        void setUp();
        void tearDown();

        void test_CalcGreatestCommonDivisor_1();
        void test_CalcGreatestCommonDivisor_2();
        void test_CalcCharacterCount_1();
};

CPPTEST_TEST_SUITE_REGISTRATION(ExercisesTestSuite);

void ExercisesTestSuite::setUp()
{
}

void ExercisesTestSuite::tearDown()
{
}

void ExercisesTestSuite::test_CalcGreatestCommonDivisor_1()
{
	/* Pre-condition initialization */
	/* Initializing argument 1 (number1) */ 
	int _number1  = 12;
	/* Initializing argument 2 (number2) */ 
	int _number2  = 3;
	/* Tested function call */
	int _return  = ::CalcGreatestCommonDivisor(_number1, _number2);

	/* Post-condition check */
	CPPTEST_POST_CONDITION_INTEGER(" _return", _return);

	CPPTEST_ASSERT_INTEGER_EQUAL(3, _return);
}

/* CPPTEST_TEST_CASE_BEGIN test_CalcGreatestCommonDivisor_2 */
/* CPPTEST_TEST_CASE_CONTEXT int CalcGreatestCommonDivisor(int, int) */
void ExercisesTestSuite::test_CalcGreatestCommonDivisor_2()
{
	/* Pre-condition initialization */
	/* Initializing argument 1 (number1) */ 
	int _number1  = 4;
	/* Initializing argument 2 (number2) */ 
	int _number2  = 10;
	/* Tested function call */
	int _return  = ::CalcGreatestCommonDivisor(_number1, _number2);

	/* Post-condition check */
	CPPTEST_POST_CONDITION_INTEGER(" _return", _return);

	CPPTEST_ASSERT_INTEGER_EQUAL(2, _return);
}

/* CPPTEST_TEST_CASE_END test_CalcGreatestCommonDivisor_2 */

/* CPPTEST_TEST_CASE_BEGIN test_CalcCharacterCount_1 */
/* CPPTEST_TEST_CASE_CONTEXT int CalcCharacterCount(const char *) */
void ExercisesTestSuite::test_CalcCharacterCount_1()
{
    /* Pre-condition initialization */
    /* Initializing argument 1 (string) */ 
    const char * _string  = "a1b2c3";
    /* Tested function call */
    int _return  = ::CalcCharacterCount(_string);
    /* Post-condition check */
    CPPTEST_POST_CONDITION_INTEGER(" _return", ( _return ));
}
/* CPPTEST_TEST_CASE_END test_CalcCharacterCount_1 */
