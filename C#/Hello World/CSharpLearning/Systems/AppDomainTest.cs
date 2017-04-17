using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Threading;
using NUnit.Framework;

namespace CSharpLearning
{
    /// <summary>
    /// 静态变量在不同的域中有不同的空间，即它们之间的修改互不影响。
    /// </summary>
    internal class RemoteObject : MarshalByRefObject
    {
        public static int StaticValue { get; private set; }

        public int NonStaticValue { get; set; }

        public void IncreaseNum()
        {
            var message = string.Format("  CurrentThreadID is:{0}。 \t AppDomainID is:{1}",
                Thread.CurrentThread.ManagedThreadId, AppDomain.CurrentDomain.Id);

            Trace.WriteLine(message);

            StaticValue++; 
        }

        public int GetNum() { return StaticValue; }

        public void StartProcess(string fileName, bool useShellExecute = true)
        {
            Process.Start(new ProcessStartInfo()
            {
                FileName = fileName,
                UseShellExecute = useShellExecute,
            });
        }
    }

    [TestFixture]
    class AppDomainTest
    {
        [Test, Description("静态变量在不同域中是独立的。")]
        public void Test1()
        {
            var exeAssemblyName = Path.GetFileName(Assembly.GetExecutingAssembly().Location);

            // create domain1
            AppDomain domain1 = AppDomain.CreateDomain("Domain1");

            // 在Domain1中创建一个RemoteObject对象
            var remoteObj1 = (RemoteObject)domain1.CreateInstanceFromAndUnwrap(exeAssemblyName,
                typeof(RemoteObject).FullName);
            remoteObj1.IncreaseNum();
            remoteObj1.NonStaticValue++;

            var domain1NonStaticValue = remoteObj1.NonStaticValue;
            var domain1StaticValue = remoteObj1.GetNum();
            var currentDomainStaticValue = RemoteObject.StaticValue;

            Assert.AreEqual(domain1NonStaticValue, 1);
            Assert.AreEqual(domain1StaticValue, 1);
            Assert.AreEqual(0, currentDomainStaticValue);

            // Create Domain2
            AppDomain domain2 = AppDomain.CreateDomain("Domain1");
            // 在Domain2中创建一个RemoteObject对象
            var remoteObj2 = (RemoteObject)domain2.CreateInstanceFromAndUnwrap(exeAssemblyName,
                typeof(RemoteObject).FullName);
            remoteObj2.IncreaseNum();

            var domain2StaticValue = remoteObj2.GetNum();
            currentDomainStaticValue = RemoteObject.StaticValue;

            Assert.AreEqual(domain2StaticValue, 1);
            Assert.AreEqual(0, RemoteObject.StaticValue);


            //
            AppDomain.Unload(domain1);
            AppDomain.Unload(domain2);
        }

        [Test]
        public void Test2()
        {
            Point p = new Point(x: 1, y: 1);
            Console.WriteLine(p); // 1

            p.Change(x: 2, y: 2); // 2
            Console.WriteLine(p);

            Object o = p;
            Console.WriteLine(o); // 2

            ((Point)o).Change(x: 3, y: 3); 
            //这个执行结果是多少？为什么？
            Console.WriteLine(o);// 2
        }

        internal struct Point
        {
            private int _x, _y;

            public Point(int x = 0, int y = 0)
            {
                _x = x;
                _y = y;
            }

            public void Change(int x = 0, int y = 0)
            {
                _x = x;
                _y = y;
            }

            public override string ToString()
            {
                return string.Format("{0},{1}", _x, _y);
            }
        }
    }
}
