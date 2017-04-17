using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using System.Reflection;

namespace NUnitStudy.Study
{
    [TestFixture]
    public class SetUpTest
    {
        private int i;

        [SetUp]
        public void SetUp()
        {
            i++;
            Console.WriteLine(MethodInfo.GetCurrentMethod().Name);
        }

        [Test]
        public void Test1()
        {
            Console.WriteLine(i);
            Console.WriteLine(MethodInfo.GetCurrentMethod().Name);
        }

        [Test]
        public void Test2()
        {
            Console.WriteLine(i);
            Console.WriteLine(MethodInfo.GetCurrentMethod().Name);
        }
    }
}
