using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

using NUnit.Framework;

namespace CSharpLearning
{
    [TestFixture(Description="线程池学习")]
    internal class ThreadPoolTest
    {
        /// <summary>
        /// 
        /// </summary>
        [Test(Description = "打印线程池中线程个数")]
        public void Test()
        { 
            // 打印最大线程个数
            int workerThreads; 
            int completionPortThreads; 
            ThreadPool.GetMaxThreads(out workerThreads, out completionPortThreads);            
            string info = string.Format("线程池中辅助线程的最大数目 = {0}, 线程池中异步 I/O 线程的最大数目 = {1}",
                workerThreads, completionPortThreads);
            Console.WriteLine(info);

            // 启动辅助线程
            for (int i = 0; i < 10; i++ )
            {
                ThreadPool.QueueUserWorkItem(new WaitCallback(WaitCallbackWorkEntry));

                // 
                ThreadPool.GetAvailableThreads(out workerThreads, out completionPortThreads);
                info = string.Format("可用辅助线程的数目 = {0}, 可用异步 I/O 线程的数目 = {1}",
                    workerThreads, completionPortThreads);
                Console.WriteLine(info);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="waitObject"></param>
        public void Test(WaitHandle waitObject)
        {
            ThreadPool.RegisterWaitForSingleObject(waitObject, new WaitOrTimerCallback(WaitOrTimerCallbackWorkEntry), waitObject, -1, true);
        }

        /// <summary>
        /// 
        /// </summary>
        private void WaitCallbackWorkEntry(object state)
        {
            try
            {
                string info = string.Format("Enter WaitCallbackWorkEntry, ThreadID = {0}, time = {1}", Thread.CurrentThread.ManagedThreadId, DateTime.Now);
                Console.WriteLine(info);

                Thread.Sleep(5000);

                info = string.Format("Leave WaitCallbackWorkEntry, ThreadID = {0}, time = {1}", Thread.CurrentThread.ManagedThreadId, DateTime.Now);
                Console.WriteLine(info);


            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex);
            }
        }

        private void WaitOrTimerCallbackWorkEntry(object state, bool timedOut)
        {
            try
            {
                string info = string.Format("Enter WaitOrTimerCallbackWorkEntry, ThreadID = {0}, time = {1}", Thread.CurrentThread.ManagedThreadId, DateTime.Now);
                Console.WriteLine(info);

                Thread.Sleep(6000);

                info = string.Format("Leave WaitOrTimerCallbackWorkEntry, ThreadID = {0}, time = {1}", Thread.CurrentThread.ManagedThreadId, DateTime.Now);
                Console.WriteLine(info);
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex);
            }
            finally
            {
                WaitHandle waitObject = state as WaitHandle;
                ThreadPool.RegisterWaitForSingleObject(waitObject, new WaitOrTimerCallback(WaitOrTimerCallbackWorkEntry), waitObject, -1, true);
            }
        }
    }
}
