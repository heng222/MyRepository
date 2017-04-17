//using System;
//using System.Text;
//using System.Collections.Generic;
//using NUnit.Framework;
//using System.IO;
//using ProWrite.UFE.Requests;
//using ProWrite.UFE;
//using System.Threading;
//using System.Diagnostics;
//using ProWrite.Core;
//using System.Reflection;
//using System.Reflection.Emit;
//using System.Linq;

//namespace ProWrite.UFE.Test
//{
//    /// <summary>
//    /// Summary description for UnitTest1
//    /// </summary>
//    [TestFixture]
//    public class RequestPacketTest
//    {
//        public RequestPacketTest()
//        {
//        }

//        [Test]
//        public void DecodePacketTest()
//        {
//            var errorJson = "{****dkfjskdfj {\"Header\":{\"UserId\":1,\"Role\":0,\"Command\":2001,\"Error\":null},\"Body\":\"123\"}";
//            var index = errorJson.IndexOf("{\"Header\":{\"");
//            string json = errorJson.Substring(index);
//            Console.WriteLine(json);
//        }
        
//        [Test]
//        public void Test()
//        {
//            Console.WriteLine("Login Test");
//            LoginTest();
//            Console.WriteLine();

//            Console.WriteLine("Change Password Test");
//            ChangePasswordTest();
//            Console.WriteLine();

//            Console.WriteLine("Create User Test");
//            CreateUserTest();
//            Console.WriteLine();

//            Console.WriteLine("Update User Role Test");
//            UpdateUserRoleTest();
//            Console.WriteLine();

//            Console.WriteLine("Delete User Test");
//            DeleteUserTest();
//            Console.WriteLine();

//            Console.WriteLine("Get User List Test");
//            GetUserListTest();
//            Console.WriteLine();

//            Console.WriteLine("Logoff Test");
//            LogoffTest();
//            Console.WriteLine();
//        }
        
//        private void LoginTest()
//        {
//            string password = "123";
//            DumpPacket(password,Commands.Login);
//        }
//        private void ChangePasswordTest()
//        {
//            string password = "456";
//            DumpPacket(password, Commands.ChangePassword);
//        }
//        private void CreateUserTest()
//        {
//            User user = new User();
//            user.Account = "LiSi";
//            user.Password = "123";
//            user.Role = Role.All;
//            DumpPacket(user, Commands.CreateUser);
//        }
//        private void DeleteUserTest()
//        {
//            DumpPacket("LiSi", Commands.DeleteUser);
//        }
//        private void UpdateUserRoleTest()
//        {
//            User user = new User();
//            user.Account = "ZhangSan";
//            user.Role = Role.Commands;
//            DumpPacket(user, Commands.UpdateUserRole);
//        }
//        private void GetUserListTest()
//        {
//            DumpPacket(Commands.GetUserList);
//        }
//        private void LogoffTest()
//        {
//            DumpPacket(Commands.Logoff);
//        }

//        private void DumpPacket(Commands cmd)
//        {
//            DumpPacket(null, cmd);
//        }

//        private void DumpPacket(object body,Commands cmd)
//        {
//            var req = new UFEPacket();
//            req.UserId = 1;
//            req.Content = body;
//            req.Command = cmd;

//            Console.WriteLine(req.ToJson());

//            string json = req.ToJson();
//            json = json.Replace(",\"Error\":null", "");

//            UFEPacket rs = req.FromJson<UFEPacket>(json);
//            Assert.AreEqual(rs.Command, req.Command);
//            //Assert.AreEqual(rs.Header.SignId, req.Header.SignId);
//            //Assert.AreEqual(rs.Header.Time, req.Header.Time);
//            Assert.AreEqual(rs.UserId, req.UserId);
//        }
//    }

    

//    //[TestFixture]
//    //public class LockTest
//    //{
//    //    private static int _threadCount;
//    //    private static Queue<int> _testQueue1 = new Queue<int>();
//    //    private static Queue<int> _testQueue2 = new Queue<int>();
//    //    private static object _lockObject = new object();
//    //    private static int _done1;
//    //    private static int _done2;

//    //    [Test]
//    //    public  void Test()
//    //    {
//    //        for(int i = 0; i < 10; i ++)
//    //            InnerTest();
//    //    }

//    //    private static void InnerTest()
//    //    {
//    //        const int MaxThreadIterations = 10;
//    //        long time1, time2;
//    //        int count = 0;
//    //        long[] times1 = new long[MaxThreadIterations];
//    //        long[] times2 = new long[MaxThreadIterations];

//    //        for (int i = 20; i <= 80; i += 10)
//    //        {
//    //            _threadCount = i;
//    //            TestLockSpeed(i, out time1, out time2);
//    //            //Console.WriteLine("Threads: " + i.ToString() + ", using class LockManager: " + time1.ToString() + " vs. lock(): " + time2.ToString());
//    //            times1[count] = time1;
//    //            times2[count] = time2;
//    //            count++;
//    //        }

//    //        long total1 = 0, total2 = 0;

//    //        for (int n = 0; n < MaxThreadIterations; n++)
//    //        {
//    //            total1 += times1[n];
//    //            total2 += times2[n];
//    //        }

//    //        Console.WriteLine("Total time using class LockManager: " + total1.ToString() + " vs. Lock(): " + total2.ToString());
//    //    }

//    //    private static void DoLockManagerEnqueue(int n)
//    //    {
//    //        LockManager.Lock();
//    //        _testQueue1.Enqueue(n);
//    //        LockManager.UnLock();
//    //    }

//    //    private static void DoLockManagerDequeue()
//    //    {
//    //        int o;

//    //        LockManager.Lock();
//    //        if (_testQueue1.Count > 0) 
//    //            o = _testQueue1.Dequeue();
//    //        LockManager.UnLock();
//    //    }

//    //    private static void DoLockEnqueue(int n)
//    //    {
//    //        //using(new Lock())
//    //        FastLock.Lock();
//    //        {
//    //            _testQueue2.Enqueue(n);
//    //        }
//    //        FastLock.UnLock();
//    //    }

//    //    private static void DoLockDequeue()
//    //    {
//    //        int o;

//    //        //using (new Lock())
//    //        FastLock.Lock();
//    //        {
//    //            if (_testQueue2.Count > 0) 
//    //                o = _testQueue2.Dequeue();
//    //        }
//    //        FastLock.UnLock();
//    //    }

//    //    public static void EnqueueWithLockable()
//    //    {
//    //        for (int n = 0; n < 1000; n++)
//    //        {
//    //            for (int i = 0; i < 20; i++)
//    //                DoLockManagerEnqueue(i + n);

//    //            Thread.Sleep(0);
//    //        }
//    //        Interlocked.Increment(ref _done1);
//    //    }

//    //    public static void DequeueWithLockManager()
//    //    {
//    //        for (int n = 0; n < 1000; n++)
//    //        {
//    //            while (_testQueue1.Count > 0)
//    //                DoLockManagerDequeue();
//    //        }
//    //        Interlocked.Increment(ref _done1);
//    //    }

//    //    public static void EnqueueWithLock()
//    //    {
//    //        for (int n = 0; n < 1000; n++)
//    //        {
//    //            for (int i = 0; i < 20; i++)
//    //                DoLockEnqueue(i + n);

//    //            Thread.Sleep(0);
//    //        }
//    //        Interlocked.Increment(ref _done2);
//    //    }

//    //    public static void DequeueWithLock()
//    //    {
//    //        for (int n = 0; n < 1000; n++)
//    //        {
//    //            while (_testQueue2.Count > 0)
//    //                DoLockDequeue();
//    //        }

//    //        Interlocked.Increment(ref _done2);
//    //    }

//    //    public static void TestLockSpeed(int ThreadCount, out long time1, out long time2)
//    //    {
//    //        _testQueue1.Clear(); _testQueue2.Clear();
//    //        _done1 = 0; _done2 = 0;
//    //        ThreadStart[] tss1 = new ThreadStart[ThreadCount];
//    //        ThreadStart[] tss2 = new ThreadStart[ThreadCount];
//    //        Thread[] threads1 = new Thread[ThreadCount];
//    //        Thread[] threads2 = new Thread[ThreadCount];

//    //        for (int n = 0; n < ThreadCount; n++)
//    //        {
//    //            if (n % 2 == 0)
//    //            {
//    //                tss1[n] = new ThreadStart(EnqueueWithLockable);
//    //                threads1[n] = new Thread( tss1[n]);
//    //                tss2[n] = new ThreadStart(EnqueueWithLock);
//    //                threads2[n] = new Thread( tss2[n]);
//    //            }
//    //            else
//    //            {
//    //                tss1[n] = new ThreadStart(DequeueWithLockManager);
//    //                threads1[n] = new Thread( tss1[n]);
//    //                tss2[n] = new ThreadStart(DequeueWithLock);
//    //                threads2[n] = new Thread( tss2[n]);
//    //            }
//    //        }

//    //        Stopwatch watch = new Stopwatch();
//    //        watch.Reset();

//    //        watch.Start();
//    //        for (int n = 0; n < ThreadCount; n++)
//    //        {
//    //            threads1[n].Start();
//    //        }

//    //        while (_done1 != ThreadCount)
//    //        {
//    //            Thread.Sleep(10);
//    //        }
//    //        watch.Stop();

//    //        time1 = watch.ElapsedMilliseconds;

//    //        watch.Reset();

//    //        watch.Start();
//    //        for (int n = 0; n < ThreadCount; n++)
//    //        {
//    //            threads2[n].Start();
//    //        }

//    //        while (_done2 != ThreadCount)
//    //        {
//    //            Thread.Sleep(10);
//    //        }
//    //        watch.Stop();

//    //        time2 = watch.ElapsedMilliseconds;
//    //    }

//    //}
//}
