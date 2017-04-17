/*----------------------------------------------------------------
// 公司名称: 北京交大微联科技有限公司 
// 
// 产品名称: 
// 
// 创 建 人: zhangheng
// 创建日期: 2014-4-17 16:44:19
// 邮    箱: zhangheng@bjmut.com
// 
// Copyright (C) 北京交大微联科技有限公司 2014，保留所有权利
// 
/*----------------------------------------------------------------*/

#ifndef _MATH_TEST_HH_
#define _MATH_TEST_HH_

//////////////////////////////////////////////////////////////////////////

#include "../Math/Math1.h"

#include <cppunit/extensions/HelperMacros.h>

#ifdef _DEBUG
    #pragma comment(lib, "cppunitd_dll.lib")
    #pragma comment(lib, "testrunnerD.lib")
#else    
    #pragma comment(lib, "cppunit_dll.lib")
    #pragma comment(lib, "testrunner.lib")
#endif
//////////////////////////////////////////////////////////////////////////


/// <summary>
/// 使用简单方法进行测试的一个测试类。
/// 
/// 如果要添加新的测试用例，需要把每个测试用例添加到 TestSuite 中，而且添加
/// 新的 TestFixture 需要把相对应的所有头文件（即每一个测试集合定义所在的头文件）
/// 添加到测试函数所在文件中，比较麻烦。
/// </summary>
class CMathTestSimple : public CPPUNIT_NS::TestFixture
{
private:

	int m_iValue1;
	int m_iValue2;

    // From TestFixture class
public:

	//! \brief Set up context before running a test.
	virtual void setUp() 
	{
		m_iValue1 = 2;
		m_iValue2 = 3;
	}

	//! Clean up after the test run.
	virtual void tearDown() 
	{
	}

public:

	void TestAdd()
	{
        int result = CMath::Add(m_iValue1, m_iValue2);
		CPPUNIT_ASSERT(result == 5);
	}

	void TestMinus()
	{
        int result = CMath::Minus(m_iValue1, m_iValue2);
		CPPUNIT_ASSERT(result == -1);
	}
};

//////////////////////////////////////////////////////////////////////////

/// <summary>
/// 使用TestSuite宏进行测试的一个测试类。
/// 
/// CppUnit 提供了 CppUnit::TestSuiteBuilder，CppUnit::TestFactoryRegistry 
/// 和一堆宏，用来方便地把 TestFixture 和测试用例注册到 TestSuite 中。
/// </summary>
class CMathTestRegistry : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(CMathTestRegistry);
    CPPUNIT_TEST(TestAdd);
    CPPUNIT_TEST(TestMinus);
    CPPUNIT_TEST_SUITE_END();

private:
    
    int m_iValue1;
    int m_iValue2;
    
    // From TestFixture class
public:
    
    //! \brief Set up context before running a test.
    virtual void setUp() 
    {
        m_iValue1 = 2;
        m_iValue2 = 3;
    }
    
    //! Clean up after the test run.
    virtual void tearDown() 
    {
    }
    
public:
    
    void TestAdd()
    {
        int result = m_iValue1 + m_iValue2;
        //CPPUNIT_ASSERT(5 == 5);
    }
    
    void TestMinus()
    {
        int result = m_iValue1 - m_iValue2;
        CPPUNIT_ASSERT(result == -1);
    }
};
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(CMathTestRegistry, "MyTest");



//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////






//////////////////////////////////////////////////////////////////////////
#endif