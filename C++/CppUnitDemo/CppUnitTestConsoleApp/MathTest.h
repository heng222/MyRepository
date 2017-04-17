/*----------------------------------------------------------------
// ��˾����: ��������΢���Ƽ����޹�˾ 
// 
// ��Ʒ����: 
// 
// �� �� ��: zhangheng
// ��������: 2014-4-17 16:44:19
// ��    ��: zhangheng@bjmut.com
// 
// Copyright (C) ��������΢���Ƽ����޹�˾ 2014����������Ȩ��
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
/// ʹ�ü򵥷������в��Ե�һ�������ࡣ
/// 
/// ���Ҫ����µĲ�����������Ҫ��ÿ������������ӵ� TestSuite �У��������
/// �µ� TestFixture ��Ҫ�����Ӧ������ͷ�ļ�����ÿһ�����Լ��϶������ڵ�ͷ�ļ���
/// ��ӵ����Ժ��������ļ��У��Ƚ��鷳��
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
/// ʹ��TestSuite����в��Ե�һ�������ࡣ
/// 
/// CppUnit �ṩ�� CppUnit::TestSuiteBuilder��CppUnit::TestFactoryRegistry 
/// ��һ�Ѻ꣬��������ذ� TestFixture �Ͳ�������ע�ᵽ TestSuite �С�
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