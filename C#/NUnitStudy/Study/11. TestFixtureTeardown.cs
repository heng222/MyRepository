using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using System.Reflection;

namespace NUnitStudy.Study
{
    [TestFixture]
    public class TestFixtureTeardown
    {
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
