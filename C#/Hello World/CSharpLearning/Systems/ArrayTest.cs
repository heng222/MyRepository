using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;


namespace CSharpLearning
{
    [TestFixture]
    class ArrayTest
    {
        [Test, Description("不基于0的数组"), ExpectedException(typeof(IndexOutOfRangeException))]
        public void Test1()
        {
            Array racers = Array.CreateInstance(typeof(int), new int[] { 5 }, new int[] { 1 });

            racers.SetValue(1, 1);
            racers.SetValue(2, 2);
            racers.SetValue(3, 3);
            racers.SetValue(4, 4);
            racers.SetValue(5, 5);
            
            Console.WriteLine(racers.GetValue(0));

        }

        [Test, Description("数组段")]
        public void Test2()
        {
            var source = new int[] { 1, 2, 3, 4, 5 };

            var arraySegment = new ArraySegment<int>(source, 2, 3);

            Assert.AreEqual(arraySegment.Count, 3);
            Assert.AreEqual(arraySegment.Offset, 2);
        }
    }
}
