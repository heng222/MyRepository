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

#ifndef _TESTRUNNER_TEST_HH_
#define _TESTRUNNER_TEST_HH_

#include "MathTest.h"

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/mfc/TestRunner.h>
#include <cppunit/ui/text/TestRunner.h>


/// <summary>
/// TestRunner演示类
/// </summary>
class CTestRunnerDemo
{
public:


public:

    /// <summary>
    /// 简单的TextUi Runner
    /// </summary>
    static void TextUiRunner_Simple()
    {
		CPPUNIT_NS::TextUi::TestRunner runner;
        CPPUNIT_NS::TestSuite* pTestSuite = new CPPUNIT_NS::TestSuite();
        
        pTestSuite->addTest(new CPPUNIT_NS::TestCaller<CMathTestSimple>("加法测试", &CMathTestSimple::TestAdd));
        pTestSuite->addTest(new CPPUNIT_NS::TestCaller<CMathTestSimple>("减法测试", &CMathTestSimple::TestMinus));
        
        runner.addTest(pTestSuite);
        
        runner.run("", true);
    }

    
    /// <summary>
    /// 使用注册机制的TextUi Runner
    /// </summary>
    static void TextUiRunner_Registry()
    {
        CPPUNIT_NS::TextUi::TestRunner runner;
        CPPUNIT_NS::TestFactoryRegistry &registry = CPPUNIT_NS::TestFactoryRegistry::getRegistry("MyTest");
       
        runner.addTest(registry.makeTest());
        
        runner.run("", true);
    }

    
    /// <summary>
    /// 使用注册机制的MfcUi Runner
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