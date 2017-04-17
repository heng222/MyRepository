using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using System.Reflection;

namespace NUnitStudy.Study
{
    [TestFixture]
    public class TestFixtureSetup_TearDownTest
    {
        [SetUp]
        public void SetUp()
        {
            Console.WriteLine(MethodInfo.GetCurrentMethod().Name);
        }
        [TearDown]
        public void TearDown()
        {
            Console.WriteLine(MethodInfo.GetCurrentMethod().Name);
        }

        [TestFixtureSetUp]
        public void TestFixtureSetUp()
        {
            Console.WriteLine(MethodInfo.GetCurrentMethod().Name);
        }

        [TestFixtureTearDown]
        public void TestFixtureTearDown()
        {
            Console.WriteLine(MethodInfo.GetCurrentMethod().Name);
        }

        [Test]
        public void Test1()
        {
            Console.WriteLine(MethodInfo.GetCurrentMethod().Name);
        }

        [Test]
        public void Test2()
        {
            Console.WriteLine(MethodInfo.GetCurrentMethod().Name);
        }
    }
}
