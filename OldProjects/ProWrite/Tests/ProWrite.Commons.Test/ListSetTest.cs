using System;
using System.Text;
using System.Collections.Generic;
using NUnit.Framework;
using ProWrite.Core;
using ProWrite.Entity.Dashboard;

namespace ProWrite.Commons.Test
{
    /// <summary>
    /// Summary description for ListSetTest
    /// </summary>
    [TestFixture]
    public class ListSetTest 
    {
        public ListSetTest()
        {
            //
            // TODO: Add constructor logic here
            //
        }

        private const int SignCount = 10;
        [Test]
        public void AddTest()
        {
            ListSet<SignInfo> signs = GetSigns();

            Assert.AreEqual(10, signs.Count);

            Console.WriteLine(signs.Count);
        }

        private static ListSet<SignInfo> GetSigns()
        {
            ListSet<SignInfo> signs = new ListSet<SignInfo>();
            for (int i = 0; i < SignCount ; i++)
            {
                SignInfo sign = new SignInfo();
                sign.Name = "Sign" + i.ToString();
                signs.Add(sign);
            }
            return signs;
        }

        [Test]
        public void EqualsTest()
        {
            ListSet<SignInfo> first = GetSigns();
            ListSet<SignInfo> second = GetSigns();

            Assert.IsTrue(first.Equals(second));
            Assert.IsTrue(first == second);
            Assert.AreEqual(first, second);
            Assert.AreEqual(first, second);
            

            second.Remove(second[0]);
            Assert.IsFalse(first == second);
            Assert.AreNotEqual(first, second);
            Assert.AreNotEqual(first, second);
        }

        [Test]
        public void EditTest()
        {
            ListSet<SignInfo> signs = GetSigns();
            signs[0].Name = "Sign2";
            Assert.AreEqual("Sign0", signs[0].Name);

            signs[0].Name = "aaa";
            Assert.AreEqual("aaa", signs[0].Name);
        }

        [Test]
        public void DeleteTest()
        {
            ListSet<SignInfo> signs = GetSigns();
            SignInfo[] array = signs.ToArray();

            foreach (SignInfo item in array)
            {
                signs.Remove(item);
            }

            Assert.AreEqual(0, signs.Count);
        }
    }
}
