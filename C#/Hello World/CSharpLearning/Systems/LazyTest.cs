using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;

namespace CSharpLearning.Systems
{
    [TestFixture]
    class LazyTest
    {
        public class Singleton
        {
            private static Singleton _instance;
            private string _message = " Testing";

            private Singleton(int data)
            {
                _message = " Start " + _message + " " + data;
            }

            public static Singleton GetInstance(int data)
            {
                if (_instance == null)   _instance = new Singleton(data);

                return _instance;
            }

            public static Singleton GetObject()
            {
                return _instance;
            }

            public string GetMessage()
            {
                return _message;
            }
        }

        [Test, Description("基本用法")]
        public void Test1()
        {
            var lazy = new Lazy<Singleton>(() => 
            { 
                return Singleton.GetInstance(100); 
            });

            // 取得Singleton
            Singleton tObject = Singleton.GetObject();
            Assert.IsNull(tObject);

            // 访问Value属性将引发对Singleton.GetInstance调用。
            Assert.NotNull(lazy.Value);

            // 重新取得Singleton
            tObject = Singleton.GetObject();
            Assert.NotNull(tObject);

            Console.WriteLine(tObject.GetMessage()); 
        }
    }
}
