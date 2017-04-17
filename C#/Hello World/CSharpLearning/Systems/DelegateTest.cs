using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using System.Threading;

namespace CSharpLearning.Systems
{
    [TestFixture(Description="委托测试")]
    class DelegateTest
    {
        delegate int TakesAwhileDelegate(int data, int timeout);

        /// <summary>
        /// 此函数被异步调用。
        /// </summary>
        private int TakesAWhile(int data, int timeout)
        {
            Console.WriteLine(string.Format("Step2: TakesAWhile thread ID = {0}", Thread.CurrentThread.ManagedThreadId));

            Console.WriteLine(string.Format("Step3: {0}, TakesAWhile started.", DateTime.Now));

            Thread.Sleep(timeout);

            Console.WriteLine(string.Format("Step4: {0}, TakesAWhile completed.", DateTime.Now));
            return ++data;
        }

        [Test]
        public void Test1()
        {
            Console.WriteLine(string.Format("Step1: {0}, Test1 thread ID = {1}", 
                DateTime.Now,
                Thread.CurrentThread.ManagedThreadId));

            TakesAwhileDelegate d1 = TakesAWhile;

            var ar = d1.BeginInvoke(1, 3000, null, null);

            ar.AsyncWaitHandle.WaitOne();

            var result = d1.EndInvoke(ar);

            Console.WriteLine(string.Format("Step5: {0}, Result = {1}", DateTime.Now, result));
        }


        [Test]
        public void Test2()
        {
            Console.WriteLine(string.Format("Step1: {0}, Test1 thread ID = {1}",
                DateTime.Now,
                Thread.CurrentThread.ManagedThreadId));

            TakesAwhileDelegate d1 = TakesAWhile;

            // 使用Lambda表达式
            var ar = d1.BeginInvoke(1, 3000,
                p =>
                {
                    var result = d1.EndInvoke(p);
                    Console.WriteLine(string.Format("Step5: {0}, Result = {1}", DateTime.Now, result));
                },
                null);

            ar.AsyncWaitHandle.WaitOne();
        }


        /// <summary>
        /// 此函数被异步调用。
        /// </summary>
        private void MethodWithException()
        {
            throw new ApplicationException("MethodWithException");
        }

        /// <summary>
        /// 可以用APM来执行任何方法，我们只需要定义一个与方法签名一致的delegate，
        /// delegate编译后会生成一个BeginInvoke和EndInvoke方法来支持APM操作。
        /// </summary>
        [Test]
        public void Test3()
        {

            Action d1 = MethodWithException;

            var ar = d1.BeginInvoke(p =>
            {
                try
                {
                    d1.EndInvoke(p);
                }
                catch (System.Exception ex)
                {
                    Console.WriteLine(ex);
                }
            }, null);

            ar.AsyncWaitHandle.WaitOne();
        }
    }
}
