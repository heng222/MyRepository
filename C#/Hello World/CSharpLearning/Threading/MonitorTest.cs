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
                    Monitor.Wait(lockObj, 10000); // 释放锁，等待lockObj状态更改。
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
                    Monitor.Wait(lockObj, 10000); // 释放锁，等待lockObj状态更改。
                    Console.WriteLine(string.Format("{0} wThread2 结束，实际等待{1}秒。", DateTime.Now, sw.Elapsed.TotalSeconds));
                }
            });
            wThread2.Start();

            var eventThread = new Thread(() =>
            {
                lock (lockObj)
                {
                    var sw = Stopwatch.StartNew();
                    Console.WriteLine(string.Format("{0} EventThread does something。", DateTime.Now));
                    Thread.Sleep(5000);
                    Console.WriteLine(string.Format("{0} EventThread finished doing something, 耗时{1}秒。", DateTime.Now, sw.Elapsed.TotalSeconds));

                    //Monitor.PulseAll(lockObj); // 通知所有等待线程，所有线程都从Wait返回。
                    Monitor.Pulse(lockObj); // 通知所有等待线程，但只有一个线程从Wait返回。

                    //Monitor.Wait(lockObj, 5000); // Wait 会释放锁。
                    //Thread.Sleep(5000); // Sleep 会使当前线程继续拥有锁直到Sleep结束。
                }
            });
            eventThread.Start();

            // 等待结束
            wThread1.Join();
            wThread2.Join();
            eventThread.Join();
            Console.WriteLine(string.Format("{0} Wait_Test1执行完毕。", DateTime.Now));
        }

        /// <summary>
        /// 与Event不同的是，Pulse时如果没有线程在等待，则此Pulse不会像Event那样保持激活态，这样之后的线程如果调用 Wait 函数则会处于等待状态。
        /// </summary>
        [TestCase(Description = "测试Pulse方法，模拟生产者-消费者问题（实时取出）。")]
        public void Plulse_Test2()
        {
            int productCount = 1;
            object lockObj = new object();
            int delayTime = 3000;
            // 线程p1、p2放入产品，线程c1取出产品。

            var pool = new ConcurrentQueue<int>();

            // P1放入 productCount 个产品
            var p1 = new Thread(() =>
            {
                for (int i = 0; i < productCount; i++)
                {
                    lock (lockObj)
                    {
                        pool.Enqueue(1);
                        Monitor.Pulse(lockObj);
                        Thread.Sleep(50);
                    }
                }

                Console.WriteLine("线程1放入了{0}个产品", productCount);
            });

            // P2放入 productCount 个产品
            var p2 = new Thread(() =>
            {
                for (int i = 0; i < productCount; i++)
                {
                    lock (lockObj)
                    {
                        pool.Enqueue(2);
                        Monitor.Pulse(lockObj);
                        Thread.Sleep(50);
                    }
                }
                Console.WriteLine("线程2放入了{0}个产品", productCount);
            });

            // P3线程3秒后启动，从缓存中开始取数据。
            int totalNum = 0;
            var p3 = new Thread(() =>
            {
                Thread.Sleep(delayTime);

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

            p3.Join((int)(delayTime * 1.5));

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
