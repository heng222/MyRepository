using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

//1. 
using NUnit.Framework;
using System.Diagnostics;

namespace NUnitStudy.Study
{
    //2.
    [TestFixture]
    public class HelloTest
    {
        //3. 测试方法必须是Public 的
        [Test]
        public void Test()
        {
           //4. Assert
            string expected = "hello";
            string actual = "hello";

            Assert.AreEqual(expected, actual);
        }

        [Test]
        public void Error()
        {
            //4. Assert
            string expected = "hello";
            string actual = "hi";

            Console.WriteLine("expected:"+ expected);
            Trace.WriteLine("actual:" + actual);

            Assert.AreEqual(expected, actual);
        }

    }
}
