using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using System.Threading;

namespace CSharpLearning.Threading
{
    [TestFixture]
    class ThreadTest
    {
        [Test]
        public void Test1()
        {
            var t1 = new Thread(state =>
            {
                Console.WriteLine("Parameter State = {0}", state);
            }) { IsBackground = true };

            t1.Start("Hello, world!");

            Console.WriteLine("Thread State = {0}", t1.ThreadState);            

            t1.Join();
        }
    }
}
