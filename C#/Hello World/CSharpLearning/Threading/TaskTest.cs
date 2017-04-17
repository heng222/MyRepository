using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using System.Threading.Tasks;
using System.Threading;

namespace CSharpLearning.Threading
{
    [TestFixture]
    class TaskTest
    {
        [Test(Description = "测试Task与CancellationToken如何配合。")]
        public void Test1()
        {
            var cancelTokenSource = new CancellationTokenSource();

            // 创建一个任务，每1秒输出一条文本。
            var task = Task.Factory.StartNew(() =>
            {
                // 方法1（推荐）
                while (!cancelTokenSource.Token.WaitHandle.WaitOne(1000))
                {
                    Console.WriteLine(string.Format("正在执行任务...{0}", DateTime.Now));
                }

                // 方法2
                //while (!cancelTokenSource.IsCancellationRequested)
                //{
                //    Console.WriteLine(string.Format("正在执行任务...{0}", DateTime.Now));
                //    Thread.Sleep(1000);
                //}
            }, cancelTokenSource.Token);

            // register a cancellation delegate
            cancelTokenSource.Token.Register(() =>
            {
                Console.WriteLine(string.Format("任务被取消！{0}", DateTime.Now));
            });

            // 5秒后取消任务。
            Console.WriteLine(string.Format("5秒后取消任务。{0}", DateTime.Now));
            Thread.Sleep(5000);
            cancelTokenSource.Cancel();

            // 等待任务结束。
            var finished = task.Wait(Timeout.Infinite);

            // 检测执行结果。
            Assert.AreEqual(false, task.IsCanceled);
            Assert.AreEqual(true, task.IsCompleted);
            Assert.AreEqual(true, finished);

            // 再创建一个Task，使用先前的Token。
            var task2 = Task.Factory.StartNew(() =>
            {
                Console.WriteLine(string.Format("任务2运行中。{0}", DateTime.Now));
            }, cancelTokenSource.Token);

            try
            {
                task2.Wait(Timeout.Infinite);
            }
            catch (System.Exception /*ex*/)
            {
                Assert.AreEqual(true, task2.IsCanceled);
            }
            Assert.AreEqual(true, task2.IsCompleted);    
        }

        [Test(Description = "获取Task的执行结果。")]
        public void Test2()
        {
            // create the task
            var task1 = new Task<int>(() =>
            {
                int sum = 0;
                for (int i = 0; i < 10; i++)
                {
                    Thread.Sleep(500);
                    sum += i;
                }
                return sum;
            });

            task1.Start();

            // write out the result
            Console.WriteLine("Result = {0}", task1.Result);

            // 注：调用Task.Result会等待Task结束(只有在task执行完成之后，才能获取到Result的值)。
        }

        [Test(Description="ContinueWith")]
        public void Test10()
        {
            var t1 = new Task(FirstTask, TaskCreationOptions.AttachedToParent);

            var t2 = t1.ContinueWith(NextTask);

            var t4 = t2.ContinueWith(TaskOnFaulted, TaskContinuationOptions.OnlyOnFaulted);

            t1.Start();

            t4.Wait();
        }
        private void FirstTask()
        {
            // Step1

            Console.WriteLine("Step1: First Task ID = {0}.", Task.CurrentId);

            for (int i = 0; i < 30; i++)
            {
                Console.WriteLine("do something {0}. Task ID = {1}.", i + 1, Task.CurrentId);
                Thread.Sleep(100);
            }

            Console.WriteLine("First Task({0}) completed.", Task.CurrentId);
        }
        private void NextTask(Task t)
        {
            // Step2

            Console.WriteLine("Step2: Task {0} finished.", t.Id);

            Console.WriteLine("Next Task ID = {0}.", Task.CurrentId);

            //Thread.Sleep(3000);

            Console.WriteLine("Task {0} throw an exception.", Task.CurrentId);
            throw new InvalidOperationException();
        }
        private void TaskOnFaulted(Task t)
        {
            // Step3

            Console.WriteLine("Task {0} faulted.", t.Id);
        }
        private void TaskOnCancelled(Task t)
        {
            // Step3

            Console.WriteLine("Task {0} Cancelled.", t.Id);
        }
    }
}
