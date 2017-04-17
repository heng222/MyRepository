using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using System.Threading;

namespace CSharpLearning.Systems
{
    [TestFixture]
    class TimerTest
    {
        [Test]
        public void Test1()
        {
            var timer1 = new System.Timers.Timer();
            timer1.Interval = 60000;
            timer1.Elapsed += timer1_Elapsed;
            timer1.Start();

            Console.WriteLine("Now = " + DateTime.Now.ToString());
            Thread.Sleep(1000000);
        }

        private void timer1_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            try
            {
                Console.WriteLine("Now = " + DateTime.Now.ToString());
            }
            catch (System.Exception /*ex*/)
            {
            	
            }
        }
    }
}
