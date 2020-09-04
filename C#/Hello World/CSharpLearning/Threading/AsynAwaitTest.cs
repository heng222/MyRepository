﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

using NUnit.Framework;

namespace CSharpLearning.Threading
{
    // 参考：https://www.cnblogs.com/zhaoshujie/p/11192036.html

    // await只能出现在已经用async关键字修饰的异步方法中。
    // await 修饰后的对象返回值为 TResult，不再是Task<TResult>。
    // 方法内部必须含有await修饰的方法，如果方法内部没有await关键字修饰的表达式，则调用者用 await 修饰此方法也无法异步等待此方法。
    // await修饰的只能是Task或者Task<TResult>类型，不能是 void 返回类型。即：方法的返回类型必须为：void、Task 或 Task<TResult>。（返回void时，无法使用await等待）

    // A 使用 await 调用 B，类似A 使用 Task.ContinueWait( B 之后的代码）。
    // await/async 语法糖让函数感觉像是同步执行的，但不一样的是当前线程并没有阻塞。
    // async标记的函数如果抛出异常，调用者是可以捕获的。

    [TestFixture]
    class AsynAwaitTest
    {
        [Test]
        public void Test1()
        {
            Console.WriteLine($"Test1 Thread ID is {Thread.CurrentThread.ManagedThreadId}_Before");
            var task = MyReceiveAsync(2); // 此方法异步调用。
            Console.WriteLine($"Test1 Thread ID is {Thread.CurrentThread.ManagedThreadId}_After");
            task.Wait();
        }

        [Test(Description ="模拟按钮单击事件")]
        public async void Test2()
        {
            Console.WriteLine($"Test1 Thread ID is {Thread.CurrentThread.ManagedThreadId}_Before");
            await MyReceiveAsync(2); // 此方法同步调用。
            Console.WriteLine($"Test1 Thread ID is {Thread.CurrentThread.ManagedThreadId}_After");
        }

        private async Task MyReceiveAsync(int mode)
        {
            if (mode == 1)
            {
                await Task.Factory.StartNew(() =>
                {
                    var result = UdpClient_ReceiveAsync() + " + MyReceiveAsync Thread ID is :" + Thread.CurrentThread.ManagedThreadId;
                    Console.WriteLine(result);

                    result = TimeConsumingMethod() + " + MyReceiveAsync Thread ID is :" + Thread.CurrentThread.ManagedThreadId;
                    Console.WriteLine(result);
                });
            }
            else
            {
                var result = await UdpClient_ReceiveAsync();
                Console.WriteLine(result+ " + MyReceiveAsync Thread ID is :" + Thread.CurrentThread.ManagedThreadId);

                result = await TimeConsumingMethod() ;
                Console.WriteLine(result + " + MyReceiveAsync Thread ID is :" + Thread.CurrentThread.ManagedThreadId);

                // 返回值是Task的函数可以不用return
            }
        }

        // 这个函数就是一个耗时函数，可能是IO操作，也可能是cpu密集型工作。
        private async Task<string> UdpClient_ReceiveAsync()
        {
            Console.WriteLine("UdpClient_ReceiveAsyncThread ID is :" + Thread.CurrentThread.ManagedThreadId);
            await Task.Delay(5000);
            Console.WriteLine("UdpClient_ReceiveAsync after Sleep(5000) Thread ID is :" + Thread.CurrentThread.ManagedThreadId);
            return "DataReceived";
        }

        //这个函数就是一个耗时函数，可能是IO操作，也可能是cpu密集型工作。
        private Task<string> TimeConsumingMethod()
        {
            var task = Task.Run(() => {
                Console.WriteLine("Helo I am TimeConsumingMethod. My Thread ID is :" + Thread.CurrentThread.ManagedThreadId);
                Thread.Sleep(5000);
                Console.WriteLine("Helo I am TimeConsumingMethod after Sleep(5000). My Thread ID is :" + Thread.CurrentThread.ManagedThreadId);
                return "Hello I am TimeConsumingMethod";
            });

            return task;
        }
    }
}
