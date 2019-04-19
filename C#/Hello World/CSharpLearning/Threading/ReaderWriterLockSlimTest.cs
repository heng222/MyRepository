using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using NUnit.Framework;

namespace CSharpLearning.Threading
{
    class ReaderWriterLockSlimTest
    {
        ReaderWriterLockSlim _rwSlim1 = new ReaderWriterLockSlim(LockRecursionPolicy.NoRecursion);
        ReaderWriterLockSlim _rwSlim2 = new ReaderWriterLockSlim(LockRecursionPolicy.SupportsRecursion);

        public void Operation()
        {
            Thread.Sleep(3000);
        }

        [Test(Description = "构造函数使用LockRecursionPolicy.NoRecursion时，不允许递归调用。")]
        [TestCase(1)]
        [ExpectedException(typeof(LockRecursionException))]
        public void TestLockRecursionPolicy1(int count)
        {
            if(count<=0) return;

            var rc = _rwSlim1.TryEnterReadLock(0);
            Console.WriteLine("尝试获取Read Lock = {0}", rc);

            rc = _rwSlim1.TryEnterReadLock(0);
            Console.WriteLine("尝试获取Read Lock = {0}", rc);
        }


        [Test(Description = "同一个线程可以多次进入读模式，没有退出读模式时无法进入写模式。")]
        public void TestEnterReadLock1()
        {
            var rc = _rwSlim2.TryEnterReadLock(0);
            Console.WriteLine("第1次尝试获取Read Lock = {0}", rc);

            rc = _rwSlim2.TryEnterReadLock(0);
            Console.WriteLine("第2次尝试获取Read Lock = {0}", rc);

            _rwSlim2.ExitReadLock();
            _rwSlim2.ExitReadLock();

            rc = _rwSlim2.TryEnterWriteLock(0);
            Console.WriteLine("第2次尝试获取Read Lock = {0}", rc);
        }

        [Test(Description = "调用TryEnterUpgradeableReadLock，在没有退出本模式时可以进入读写模式。")]
        public void TestTryEnterUpgradeableReadLock1()
        {
            var rc = _rwSlim2.TryEnterUpgradeableReadLock(0);
            Console.WriteLine("第1次尝试获取UpgradeableRead Lock = {0}", rc);

            rc = _rwSlim2.TryEnterWriteLock(0);
            Console.WriteLine("第2次尝试获取Writer Lock = {0}", rc);
            _rwSlim2.ExitWriteLock();

            rc = _rwSlim2.TryEnterReadLock(0);
            Console.WriteLine("第3次尝试获取Read Lock = {0}", rc);

            rc = _rwSlim2.TryEnterWriteLock(0);
            Console.WriteLine("第4次尝试获取Writer Lock = {0}", rc);

            _rwSlim2.ExitUpgradeableReadLock();
        }

        public void Test1()
        {
            var rwlock = new ReaderWriterLockSlim();

            var taskReader1 = Task.Factory.StartNew(() =>
            {
                var rc = rwlock.TryEnterReadLock(0);
                Console.WriteLine("Task1: 尝试获取Read Lock = {0}", rc);

                Operation();

                Console.WriteLine("1 WaitingReadCount = {0}. WaitingWriteCount = {1}", rwlock.WaitingReadCount, rwlock.WaitingWriteCount);

                if (rc) { rwlock.ExitReadLock(); Console.WriteLine("Task 1 释放锁。"); }
            });

            var taskReader2 = Task.Factory.StartNew(() =>
            {
                var rc = rwlock.TryEnterReadLock(0);
                Console.WriteLine("Task2: 尝试获取Read Lock = {0}.", rc);
                Operation();

                Console.WriteLine("2 WaitingReadCount = {0}. WaitingWriteCount = {1}", rwlock.WaitingReadCount, rwlock.WaitingWriteCount);

                if (rc) { rwlock.ExitReadLock(); Console.WriteLine("Task2 释放锁。"); }
            });

            var taskReader3 = Task.Factory.StartNew(() =>
            {
                rwlock.EnterWriteLock();
                Console.WriteLine("Task3: 获取Write Lock");
                Operation();

                Console.WriteLine("3 WaitingReadCount = {0}. WaitingWriteCount = {1}", rwlock.WaitingReadCount, rwlock.WaitingWriteCount);

                rwlock.ExitWriteLock();
                Console.WriteLine("Task3 释放锁。");
            });

            var taskWriter4 = Task.Factory.StartNew(() =>
            {
                rwlock.EnterWriteLock();
                Console.WriteLine("TaskWriter4: 获取Write Lock");

                Operation();

                Console.WriteLine("4 WaitingReadCount = {0}. WaitingWriteCount = {1}", rwlock.WaitingReadCount, rwlock.WaitingWriteCount);

                rwlock.ExitWriteLock(); 
                Console.WriteLine("Task4 释放锁。");
            });

            var taskReader5 = Task.Factory.StartNew(() =>
            {
                var rc = rwlock.TryEnterReadLock(0);
                Console.WriteLine("TaskReader5: 尝试获取Read Lock = {0}.", rc);
                Operation();

                Console.WriteLine("5 WaitingReadCount = {0}. WaitingWriteCount = {1}", rwlock.WaitingReadCount, rwlock.WaitingWriteCount);

                if (rc) { rwlock.ExitReadLock(); Console.WriteLine("Task5 释放锁。"); }
            });

            taskReader1.Wait();
            taskReader2.Wait();
            taskReader3.Wait();
            taskWriter4.Wait();
            taskReader5.Wait();
        }
    }
}
