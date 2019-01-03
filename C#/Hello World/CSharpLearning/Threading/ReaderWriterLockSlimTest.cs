using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace CSharpLearning.Threading
{
    class ReaderWriterLockSlimTest
    {
        public void Operation()
        {
            Thread.Sleep(3000);
        }

        public void Test1()
        {
            var rwlock = new ReaderWriterLockSlim();

            var task1 = Task.Factory.StartNew(() =>
            {
                var rc = rwlock.TryEnterReadLock(0);
                Console.WriteLine("Task1: 尝试获取Read Lock = {0}", rc);

                Operation();

                Console.WriteLine("1 WaitingReadCount = {0}. WaitingWriteCount = {1}", rwlock.WaitingReadCount, rwlock.WaitingWriteCount);

                if (rc) { rwlock.ExitReadLock(); Console.WriteLine("Task 1 释放锁。"); }
            });

            var task2 = Task.Factory.StartNew(() =>
            {
                var rc = rwlock.TryEnterReadLock(0);
                Console.WriteLine("Task2: 尝试获取Read Lock = {0}.", rc);
                Operation();

                Console.WriteLine("2 WaitingReadCount = {0}. WaitingWriteCount = {1}", rwlock.WaitingReadCount, rwlock.WaitingWriteCount);

                if (rc) { rwlock.ExitReadLock(); Console.WriteLine("Task2 释放锁。"); }
            });

            var task3 = Task.Factory.StartNew(() =>
            {
                rwlock.EnterWriteLock();
                Console.WriteLine("Task3: 获取Write Lock");
                Operation();

                Console.WriteLine("3 WaitingReadCount = {0}. WaitingWriteCount = {1}", rwlock.WaitingReadCount, rwlock.WaitingWriteCount);

                rwlock.ExitWriteLock();
                Console.WriteLine("Task3 释放锁。");
            });

            var task4 = Task.Factory.StartNew(() =>
            {
                rwlock.EnterWriteLock();
                Console.WriteLine("Task4: 获取Write Lock");

                Operation();

                Console.WriteLine("4 WaitingReadCount = {0}. WaitingWriteCount = {1}", rwlock.WaitingReadCount, rwlock.WaitingWriteCount);

                rwlock.ExitWriteLock(); 
                Console.WriteLine("Task5 释放锁。");
            });

            var task5 = Task.Factory.StartNew(() =>
            {
                var rc = rwlock.TryEnterReadLock(0);
                Console.WriteLine("Task5: 尝试获取Read Lock = {0}.", rc);
                Operation();

                Console.WriteLine("5 WaitingReadCount = {0}. WaitingWriteCount = {1}", rwlock.WaitingReadCount, rwlock.WaitingWriteCount);

                if (rc) { rwlock.ExitReadLock(); Console.WriteLine("Task5 释放锁。"); }
            });

            task1.Wait();
            task2.Wait();
            task3.Wait();
            task4.Wait();
            task5.Wait();
        }
    }
}
