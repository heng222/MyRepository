using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using System.Threading;
using System.Diagnostics;

namespace CSharpLearning.Threading
{
    [TestFixture]
    class MonitorTest
    {
        [TestCase(Description="测试PulseAll方法。")]
        public void PulseAll_Test1()
        {
            var lockObj = new object();

            var thread1 = new Thread(() =>
            {
                lock (lockObj)
                {
                    var sw = Stopwatch.StartNew();                    
                    Console.WriteLine(string.Format("{0} Thread1 调用Wait，最多等待10秒。", DateTime.Now));
                    Monitor.Wait(lockObj); // 释放锁，等待lockObj状态更改。
                    Console.WriteLine(string.Format("{0} Thread1 结束，实际等待{1}秒。", DateTime.Now, sw.Elapsed.TotalSeconds));
                }
            });
            thread1.Start();

            var thread2 = new Thread(() =>
            {
                lock (lockObj)
                {
                    var sw = Stopwatch.StartNew();      
                    Console.WriteLine(string.Format("{0} Thread2 does something。", DateTime.Now));
                    Thread.Sleep(500);
                    Console.WriteLine(string.Format("{0} Thread2 finished doing something, 耗时{1}秒。", DateTime.Now, sw.Elapsed.TotalSeconds));

                    Monitor.PulseAll(lockObj); // 通知所有等待线程，lockObj状态更改。
                }
            });
            thread2.Start();

            // 等待结束
            thread1.Join();
            thread2.Join();
            Console.WriteLine(string.Format("{0} Wait_Test1执行完毕。", DateTime.Now));
        }
    }
}
