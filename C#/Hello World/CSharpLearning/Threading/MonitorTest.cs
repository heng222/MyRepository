using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using System.Threading;
using System.Diagnostics;
using System.Collections.Concurrent;

namespace CSharpLearning.Threading
{
    [TestFixture]
    class MonitorTest
    {
        [TestCase(Description="测试PulseAll方法。")]
        public void PulseAll_Test1()
        {
            var lockObj = new object();

            var wThread1 = new Thread(() =>
            {
                lock (lockObj)
                {
                    var sw = Stopwatch.StartNew();                    
                    Console.WriteLine(string.Format("{0} wThread1 调用Wait，最多等待10秒。", DateTime.Now));
                    Monitor.Wait(lockObj); // 释放锁，等待lockObj状态更改。
                    Console.WriteLine(string.Format("{0} wThread1 结束，实际等待{1}秒。", DateTime.Now, sw.Elapsed.TotalSeconds));
                }
            });
            wThread1.Start();

            var wThread2 = new Thread(() =>
            {
                lock (lockObj)
                {
                    var sw = Stopwatch.StartNew();
                    Console.WriteLine(string.Format("{0} wThread2 调用Wait，最多等待10秒。", DateTime.Now));
                    Monitor.Wait(lockObj); // 释放锁，等待lockObj状态更改。
                    Console.WriteLine(string.Format("{0} wThread2 结束，实际等待{1}秒。", DateTime.Now, sw.Elapsed.TotalSeconds));
                }
            });
            wThread2.Start();

            var thread2 = new Thread(() =>
            {
                lock (lockObj)
                {
                    var sw = Stopwatch.StartNew();      
                    Console.WriteLine(string.Format("{0} Thread2 does something。", DateTime.Now));
                    Thread.Sleep(5000);
                    Console.WriteLine(string.Format("{0} Thread2 finished doing something, 耗时{1}秒。", DateTime.Now, sw.Elapsed.TotalSeconds));

                    Monitor.PulseAll(lockObj); // 通知所有等待线程，lockObj状态更改。
                }
            });
            thread2.Start();

            // 等待结束
            wThread1.Join();
            wThread2.Join();
            thread2.Join();
            Console.WriteLine(string.Format("{0} Wait_Test1执行完毕。", DateTime.Now));
        }

        [TestCase(Description = "测试Pulse方法，模拟生产者-消费者问题（实时取出）。")]
        public void Plulse_Test2()
        {
            object lockObj = new object();
            // 线程p1、p2放入产品，线程c1取出产品。

            var pool = new ConcurrentQueue<int>(); 

            var p1 = new Thread(() =>
            {
                for (int i = 0; i < 100; i++)
                {
                    lock (lockObj)
                    {
                        pool.Enqueue(1);
                        Monitor.Pulse(lockObj);
                        Thread.Sleep(50);
                    }
                }
            });

            var p2 = new Thread(() =>
            {
                for (int i = 0; i < 100; i++)
                {
                    lock (lockObj)
                    {
                        pool.Enqueue(2);
                        Monitor.Pulse(lockObj);
                        Thread.Sleep(50);
                    }
                }
            });

            int totalNum = 0;
            var p3 = new Thread(() =>
            {
                while (true)
                {
                    lock (lockObj)
                    {
                        Monitor.Wait(lockObj);
                        var result = pool.ToArray();

                        int value;
                        while (pool.TryDequeue(out value)) ;

                        if (result.Length == 0)
                        {
                            break;
                        }

                        Console.WriteLine(string.Format("本次取出{0}个：{1}", result.Length, string.Join(",", result)));
                        totalNum += result.Length;
                    }
                }
            });

            p1.Start();
            p2.Start();
            p3.Start();

            p1.Join();
            p2.Join();

            p3.Join(2000);

            Console.WriteLine(string.Format("一共取出{0}个。", totalNum));
        }

        [TestCase(Description = "测试Pulse方法，模拟生产者-消费者问题（周期性取出，500毫秒）。")]
        public void Plulse_Test3()
        {
            var lockObj = new object();
            // 线程p1、p2放入产品，线程c1取出产品。

            var pool = new ConcurrentQueue<int>();

            var p1 = new Thread(() =>
            {
                for (int i = 0; i < 100; i++)
                {
                    lock (lockObj)
                    {
                        pool.Enqueue(1);
                        Thread.Sleep(50);
                    }
                }
            });

            var p2 = new Thread(() =>
            {
                for (int i = 0; i < 100; i++)
                {
                    lock (lockObj)
                    {
                        pool.Enqueue(2);
                        Thread.Sleep(50);
                    }
                }
            });

            int totalNum = 0;
            var p3 = new Thread(() =>
            {
                while (true)
                {
                    lock (lockObj)
                    {
                        Monitor.Wait(lockObj, 1000);
                        var result = pool.ToArray();

                        int value;
                        while (pool.TryDequeue(out value)) ;

                        if (result.Length == 0)
                        {
                            break;
                        }

                        Console.WriteLine(string.Format("本次取出{0}个：{1}", result.Length, string.Join(",", result)));
                        totalNum += result.Length;
                    }
                }
            });

            p3.Start();
            p1.Start();
            p2.Start();

            p1.Join();
            p2.Join();

            p3.Join();

            Console.WriteLine(string.Format("一共取出{0}个。", totalNum));
        }
    }
}
