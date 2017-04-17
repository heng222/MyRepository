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

#ifndef _TESTRUNNER_TEST_HH_
#define _TESTRUNNER_TEST_HH_

#include "MathTest.h"

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/mfc/TestRunner.h>
#include <cppunit/ui/text/TestRunner.h>


/// <summary>
/// TestRunner��ʾ��
/// </summary>
class CTestRunnerDemo
{
public:


public:

    /// <summary>
    /// �򵥵�TextUi Runner
    /// </summary>
    static void TextUiRunner_Simple()
    {
		CPPUNIT_NS::TextUi::TestRunner runner;
        CPPUNIT_NS::TestSuite* pTestSuite = new CPPUNIT_NS::TestSuite();
        
        pTestSuite->addTest(new CPPUNIT_NS::TestCaller<CMathTestSimple>("�ӷ�����", &CMathTestSimple::TestAdd));
        pTestSuite->addTest(new CPPUNIT_NS::TestCaller<CMathTestSimple>("��������", &CMathTestSimple::TestMinus));
        
        runner.addTest(pTestSuite);
        
        runner.run("", true);
    }

    
    /// <summary>
    /// ʹ��ע����Ƶ�TextUi Runner
    /// </summary>
    static void TextUiRunner_Registry()
    {
        CPPUNIT_NS::TextUi::TestRunner runner;
        CPPUNIT_NS::TestFactoryRegistry &registry = CPPUNIT_NS::TestFactoryRegistry::getRegistry("MyTest");
       
        runner.addTest(registry.makeTest());
        
        runner.run("", true);
    }

    
    /// <summary>
    /// ʹ��ע����Ƶ�MfcUi Runner
    /// </summary>
    static void MfcUiRunner_Registry()
    {
        CPPUNIT_NS::MfcUi::TestRunner runner;
        CPPUNIT_NS::TestFactoryRegistry &registry = CPPUNIT_NS::TestFactoryRegistry::getRegistry("MyTest");
        
        runner.addTest(registry.makeTest());
        
        runner.run();
    }
};

//////////////////////////////////////////////////////////////////////////
#endif