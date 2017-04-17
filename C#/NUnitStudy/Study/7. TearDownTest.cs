using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using System.Reflection;

namespace NUnitStudy.Study
{
    public class TearDownTest
    {
        [TearDown]
        public void TearDown()
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
