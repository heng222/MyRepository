using System;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;
using NUnit.Framework;

namespace CSharpLearning.Threading
{
    [TestFixture]
    class TaskCompletionSourceTest
    {
        [Test]
        public void Test1()
        {
            Console.WriteLine("Main thread ID =" + Thread.CurrentThread.ManagedThreadId);

            var tcs1 = new TaskCompletionSource<object>();

            // Start a background task that will complete tcs1.Task
            var task2 = Task.Factory.StartNew(() =>
             {
                  Thread.Sleep(2000);
                  tcs1.SetResult(15);
                  Console.WriteLine("Task2, ThreadID = " + Thread.CurrentThread.ManagedThreadId);
             });

            // The attempt to get the result of t1 BLOCKS the current thread until the completion source gets signaled.
            // It should be a wait of ~2000 ms.
            var sw = Stopwatch.StartNew();
            var result = tcs1.Task.Result;
            sw.Stop();

            Console.WriteLine("(ElapsedTime={0}): t1.Result={1} (expected 15) ", sw.ElapsedMilliseconds, result);
        }

        public void Test2()
        {
            // Alternatively, an exception can be manually set on a TaskCompletionSource.Task
            TaskCompletionSource<int> tcs2 = new TaskCompletionSource<int>();
            Task<int> t2 = tcs2.Task;

            // Start a background Task that will complete tcs2.Task with an exception
            Task.Factory.StartNew(() =>
             {
                  Thread.Sleep(1000);
                  tcs2.SetException(new Exception[] { new ArgumentException(), new InvalidOperationException() });
                  Console.WriteLine("第二个Task.Thread ID = " + Thread.CurrentThread.ManagedThreadId);
             });

            // The attempt to get the result of t2 blocks the current thread until the completion source gets signaled with either a result or an exception.
            // In either case it should be a wait of ~1000 ms.
            var sw = Stopwatch.StartNew();
            try
            {
                var result = t2.Result;

                Console.WriteLine("t2.Result succeeded. THIS WAS NOT EXPECTED.");
            }
            catch (AggregateException e)
            {
                Console.Write("(ElapsedTime={0}): ", sw.ElapsedMilliseconds);
                Console.WriteLine("The following exceptions have been thrown by t2.Result: (THIS WAS EXPECTED)");
                for (int j = 0; j < e.InnerExceptions.Count; j++)
                {
                    Console.WriteLine("\n-------------------------------------------------\n{0}", e.InnerExceptions[j].ToString());
                }

            }

            Console.WriteLine("主2:" + Thread.CurrentThread.ManagedThreadId);
        }
    }
}
