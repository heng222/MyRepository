using System;
using System.Text;
using System.Collections.Generic;
using NUnit.Framework;

using ProWrite.Entity.Dashboard;

namespace ProWrite.Commons.Test
{
    /// <summary>
    /// Summary description for DashboardItemTest
    /// </summary>
    [TestFixture]
    public class DashboardItemTest
    {


        #region Additional test attributes

        private SignGroupTree tree;
        [SetUp()]
        public void MySetUp()
        {
            tree = new SignGroupTree();
            //SignInfo signn = new SignInfo();
            //signn.Name = "signn";
            //tree.AddSign(signn);
        }


        [TearDown()]
        public void MyTearDown()
        {
            tree.Clear();
        }


        #endregion

       /// <summary>
        /// ²âÊÔGetSignByNameº¯Êý
       /// </summary>
        [Test]
        public void GetSignByNameTest()
        {
            SignInfo newsign = new SignInfo();
            newsign.Name = "test";
            newsign.Parent = tree;

            Assert.IsTrue(Equals(newsign, SignInfo.GetSignByName("test")));
            Assert.IsFalse(Equals(newsign, SignInfo.GetSignByName("test1")));
        }

        [Test]
        public void GetGroupByNameTest()
        {
            SignGroupInfo newsign = new SignGroupInfo();
            newsign.Name = "test";
            newsign.Parent = tree;

            Assert.IsTrue(Equals(newsign, SignGroupInfo.GetGroupByName("test")));
            Assert.IsFalse(Equals(newsign, SignGroupInfo.GetGroupByName("test1")));
        }

		/// <summary>
		/// 
		/// </summary>
        [Test]
        public void ParentNameTest()
        {
            SignGroupInfo newsign = new SignGroupInfo();
            newsign.Name = "test";
            newsign.Parent = tree;
            SignGroupInfo group = new SignGroupInfo();
            group.Name = "group";
            group.Parent = newsign;
            //SignGroupInfo.GetGroupByName("SignGroupTree");
            Assert.IsTrue(Equals("[No Group]", newsign.ParentName));
           // Assert.IsFalse(Equals(newsign, SignGroupInfo.GetGroupByName("test1")));
        }

        
    }
}
