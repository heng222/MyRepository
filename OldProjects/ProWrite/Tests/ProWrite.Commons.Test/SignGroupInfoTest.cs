////---------------------------------------------------------------------
////
//// File: SignGroupInfoTest.cs
////
//// Description:
//// Test mothod of SignGroupInfo class 
////
//// Author: William
////
//// Copyright (C) 2008 by Trans-Lux All rights reserved.
//// 
////---------------------------------------------------------------------


//using NUnit.Framework;
//using System;
//using System.Text;
//using System.Collections.Generic;
//using ProWrite.Core;
//using ProWrite.Entity;
////using ProWrite.UI.Commons;
//using log4net;
//using ProWrite.Entity.Dashboard;

//namespace ProWrite.Commons.Test
//{
//    [TestFixture()]
//    public class SignGroupInfoTest
//    {
        
//        #region Additional test attributes

//        private SignGroupTree _tree;

//        [SetUp()]
//        public void MySetUp()
//        {
//            _tree = new SignGroupTree();
//        }


//        [TearDown()]
//        public void MyTearDown()
//        {
//            _tree.Clear();
//        }


//        #endregion
//        /// <summary>
//        /// Test groups relation
//        /// </summary>
//        [Test]
//        public void ParentGroupTest()
//        {
//            _tree.Clear();
//            SignGroupInfo target = new SignGroupInfo();

//            SignGroupInfo[] group1 = new SignGroupInfo[16];
//            SignGroupInfo[] group2 = new SignGroupInfo[4];

//            for (int i = 0; i < group1.Length; i++)
//            {
//                group1[i] = new SignGroupInfo();
//                group1[i].Name = "test" + i;
//                if (i == 0)
//                    target.AddGroup(group1[i]);
//                else
//                    //group1[i-1].AddGroup(group1[i]);
//                    group1[i].Parent = group1[i - 1];
//            }
//            for (int j = 0; j < group2.Length; j++)
//            {
//                group2[j] = new SignGroupInfo();
//                group2[j].Name = "test" + j + 20;
//                group1[1].AddGroup(group2[j]);

//            }


//            Assert.AreEqual(20, SignGroupInfo.AllGroups.Length);
//            Assert.AreEqual(5, group1[1].Groups.Length);
//            Assert.AreEqual("test0", group1[1].ParentName);
//            Assert.AreEqual("test13", group1[14].ParentName);
//            Assert.AreEqual("test14", group1[15].ParentName);


//        }
//        /// <summary>
//        /// Test of AddGroup
//        /// </summary>
//        [Test()]//william
//        public void AddGroupTest()
//        {
//            _tree.Clear();
//            SignGroupInfo target = new SignGroupInfo();

//            SignGroupInfo group = null;
//            bool expected = false;
//            bool actual;
//            actual = target.AddGroup(group);
//            Assert.AreEqual(expected, actual);
//            Assert.AreEqual(0, target.Groups.Length);
//        }

//        /// <summary>
//        /// Add one new group to the other group
//        /// </summary>
//        [Test()]
//        public void AddGroupTest1()
//        {
//            _tree.Clear();
//            SignGroupInfo target = new SignGroupInfo();

//            SignGroupInfo group1 = new SignGroupInfo();
//            group1.Name = "hello";
//            bool expected = true;
//            bool actual;

//            actual = target.AddGroup(group1);
//            Assert.AreEqual(expected, actual);
//            Assert.AreEqual(1, target.Groups.Length);
//            Assert.AreEqual(1, SignGroupInfo.AllGroups.Length);
//            target.RemoveGroup(group1,true);
//        }

//        /// <summary>
//        /// Add a group to itself
//        /// Allow user to operate it
//        /// </summary>
//        [Test()]
//        public void AddGroupTest2()
//        {
//            _tree.Clear();
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "hello";
//            //group1
//            bool expected = true;
//            bool actual;

//            actual = target.AddGroup(target);
//            Assert.AreEqual(expected, actual);
//            Assert.AreEqual(1, target.Groups.Length);
//            Assert.AreEqual(1, SignGroupInfo.AllGroups.Length);
//            target.RemoveGroup(target,true);

//        }

//        /// <summary>
//        /// Add a group that is empty
//        /// </summary>
//        [Test()]
//        public void AddGroupTest3()
//        {
//            //_tree.Clear();
//            SignGroupInfo target = new SignGroupInfo();
//            SignGroupInfo group = new SignGroupInfo();
//            bool expected = false;
//            bool actual;

//            actual = target.AddGroup(group);
//            Assert.AreEqual(expected, actual);
//            Assert.AreEqual(0, target.Groups.Length);
//            Assert.AreEqual(0, SignGroupInfo.AllGroups.Length);

//        }



//        /// <summary>
//        /// AddSign test
//        /// Sign is null
//        /// </summary>
//        [Test()]
//        public void AddSignTest()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            SignInfo sign = null;

//            bool expected = false;
//            bool actual;

//            actual = target.AddSign(sign);

//            Assert.AreEqual(expected, actual);
//            Assert.AreEqual(0, SignGroupInfo.AllSigns.Length);
//            target.RemoveSign(sign);
//        }



//        /// <summary>
//        /// Sign is empty
//        /// </summary>
//        [Test()]
//        public void AddSignTest7()
//        {
//            // _tree.Clear();
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "target";
//            SignInfo sign = new SignInfo();
//            //sign.Name = "test";
//            // target.AddSign(sign);

//            bool expected = false;
//            bool actual;
//            actual = target.AddSign(sign);
//            Assert.AreEqual(0, target.Signs.Length);
//            //Assert.AreEqual(1,SignGroupInfo.AllSigns.Length);
//            Assert.AreEqual(expected, actual);

//            target.RemoveSign(sign);
//        }

//        /// <summary>
//        /// Sign name exist
//        /// </summary>
//        [Test()]
//        public void AddSignTest1()
//        {
//            // _tree.Clear();
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "target";
//            SignInfo sign = new SignInfo();
//            sign.Name = "test";
//            target.AddSign(sign);

//            bool expected = false;
//            bool actual;
//            actual = target.AddSign(sign);
//            Assert.AreEqual(1, target.Signs.Length);
//            //Assert.AreEqual(1,SignGroupInfo.AllSigns.Length);
//            Assert.AreEqual(expected, actual);

//            target.RemoveSign(sign);
//        }

//        /// <summary>
//        /// Sign is not empty,the result is true
//        /// </summary>
//        [Test()]
//        public void AddSignTest2()
//        {
//            SignGroupInfo target = new SignGroupInfo();

//            SignInfo sign = new SignInfo();
//            sign.Name = "test33";
//            //sign.Type = SignType.Green;
//            SignInfo sign1 = new SignInfo();
//            sign1.Name = "test4451";
//            // sign1.Type=SignType.Red;

//            target.AddSign(sign);
//            bool expected = true;
//            bool actual;
//            int kk = 2;
//            actual = target.AddSign(sign1);
//            Assert.AreEqual(kk, target.Signs.Length);
//            Assert.AreEqual(kk, SignInfo.AllSigns.Length);
//            Assert.AreEqual(expected, actual);
//            target.RemoveSign(sign);
//            target.RemoveSign(sign1);

//        }

//        /// <summary>
//        /// Test sign name length
//        /// The layer do not limit to name length
//        /// </summary>
//        [Test()]
//        public void AddSignTest3()
//        {

//            SignGroupInfo target = new SignGroupInfo();
//            SignInfo sign = new SignInfo();
//            sign.Name = "testsdjkajfkhaskldfljkasdf?><<@@##^&&*)(@@~_+)|jasdfkjasdfjksdjfjdsfgjsdjfjsdfgjsdfjk";
//            sign.Type = SignType.RGB;
//            sign.Height = 992;
//            sign.Width = 334;
//            bool expected = true;
//            bool actual;

//            actual = target.AddSign(sign);
//            Assert.AreEqual(expected, actual);
//            target.RemoveSign(sign);
//        }


//        /// <summary>
//        /// Test sign height range
//        /// </summary>
//        [Test]
//        //[DeploymentItem("D:\\data.xls")]
//        //[DataSource("System.Data.Odbc", "Dsn=Excel Files;dbq=D:\\data.xls;defaultdir=D:;driverid=790;maxbuffersize=2048;pagetimeout=5", "Sheet1$", DataAccessMethod.Sequential)]
//        public void AddSignTest4()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            SignInfo sign = new SignInfo();
//            sign.Name = "fgjsdfjk";
//            sign.Type = SignType.RGB;
//            sign.Height = 0;
//            sign.Width = 0;
//            bool expected = false;
//            bool actual;

//            actual = target.AddSign(sign);
//            Assert.AreEqual(expected, actual);
//            target.RemoveSign(sign);
//        }

//        /// <summary>
//        /// Test sign width range
//        /// </summary>
//        [Test]
//        public void AddSignTest5()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            SignInfo sign = new SignInfo();
//            sign.Name = "fgjsdfjk";
//            //sign.Type = SignType.Red;
//            sign.Height = 433;
//            sign.Width = -22100;
//            bool expected = false;
//            bool actual;

//            actual = target.AddSign(sign);
//            Assert.AreEqual(expected, actual);
//            target.RemoveSign(sign);

//        }

//        /// <summary>
//        /// Test sign type
//        /// </summary>
//        [Test()]
//        public void AddSignTest6()
//        {
//            _tree.Clear();
//            SignGroupInfo target = new SignGroupInfo();
//            SignInfo sign = new SignInfo();
//            sign.Name = "test";
//            //sign.Type = SignType.Amber;
//            sign.Height = 992;
//            sign.Width = 334;
//            bool expected = true;
//            bool actual;
//            SignInfo sign1 = new SignInfo();
//            sign1.Name = "test1";
//            target.AddSign(sign1);
//            actual = target.AddSign(sign);
//            Assert.AreEqual(expected, actual);
//            Assert.AreEqual(2, SignInfo.AllSigns.Length);
//            target.RemoveSign(sign);
//            target.RemoveSign(sign1);
//        }

//        /// <summary>
//        ///  Contains() test while group is empty
//        /// </summary>

//        [Test()]
//        public void ContainsTest()
//        {
//            SignGroupInfo target = new SignGroupInfo();

//            SignGroupInfo item = null;

//            bool expected = false;
//            bool actual;

//            actual = target.Contains(item);
//            Assert.AreEqual(expected, actual);
//        }

//        /// <summary>
//        ///  Contains() test while group is not empty
//        /// </summary>
//        [Test()]
//        public void ContainsTest1()
//        {
//            SignGroupInfo target = new SignGroupInfo();

//            SignGroupInfo item = new SignGroupInfo(); ;
//            item.Name = "test";
//            bool expected = false;
//            bool actual;

//            actual = target.Contains(item);
//            Assert.AreEqual(expected, actual);
//        }

//        /// <summary>
//        ///  Contains() test while group is not empty and the group exist
//        /// </summary>
//        [Test()]
//        public void ContainsTest3()
//        {
//            SignGroupInfo target = new SignGroupInfo();

//            SignGroupInfo item = new SignGroupInfo(); ;
//            item.Name = "test";
//            target.AddGroup(item);
//            bool expected = true;
//            bool actual;

//            actual = target.Contains(item);
//            Assert.AreEqual(expected, actual);
//            target.RemoveGroup(item,true);
//        }

//        /// <summary>
//        ///  Contains() test while sign is empty
//        /// </summary>
//        [Test()]
//        public void ContainsTest2()
//        {
//            SignGroupInfo target = new SignGroupInfo();

//            SignInfo item = null;

//            bool expected = false;
//            bool actual;

//            actual = target.Contains(item);
//            Assert.AreEqual(expected, actual);
//        }

//        /// <summary>
//        ///  Contains() test while sign is not empty
//        /// </summary>
//        [Test()]
//        public void ContainsTest4()
//        {
//            SignGroupInfo target = new SignGroupInfo();

//            SignInfo item = new SignInfo();
//            item.Name = "she";
//            bool expected = false;
//            bool actual;

//            actual = target.Contains(item);
//            Assert.AreEqual(expected, actual);
//        }

//        /// <summary>
//        ///  Contains() test while sign is not empty and the sign exist
//        /// </summary>
//        [Test()]
//        public void ContainsTest5()
//        {
//            SignGroupInfo target = new SignGroupInfo();

//            SignInfo item = new SignInfo();
//            item.Name = "you";
//            target.AddSign(item);
//            bool expected = true;
//            bool actual;

//            actual = target.Contains(item);
//            Assert.AreEqual(expected, actual);
//            target.RemoveSign(item);
//        }

//        [Test()]
//        public void ContainsGroupTest()
//        {
//            SignGroupInfo target = new SignGroupInfo();

//            SignGroupInfo group = null;

//            //bool expected = false;
//            bool actual;

//            actual = target.ContainsGroup(group);
//        }

//        /// <summary>
//        /// A test of ClearGroups()  
//        /// </summary>
//        [Test()]
//        public void ClearGroupsTest()
//        {
//            SignGroupInfo target = new SignGroupInfo();

//            target.Name = "hdsgf";
//            _tree.AddGroup(target);
//            SignGroupInfo[] group = new SignGroupInfo[15];
//            for (int i = 0; i < group.Length; i++)
//            {
//                group[i] = new SignGroupInfo();
//                group[i].Name = "test" + i;
//                target.AddGroup(group[i]);


//            }
//            target.ClearGroups();
//            int expected = 0;
//            // int actual;


//            Assert.AreEqual(expected, target.Groups.Length);
//        }

//        /// <summary>
//        /// A test of ClearGroups() 
//        /// Group is empty
//        /// </summary>
//        [Test()]
//        public void ClearGroupsTest1()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "SS";
//            Assert.AreEqual(0, target.Groups.Length);
//            target.ClearGroups();
//            int expected = 0;
//            Assert.AreEqual(expected, target.Groups.Length);
//        }

//        /// <summary>
//        /// A test of ClearGroups() 
//        /// Including some groups in Group
//        /// </summary>
//        [Test()]
//        public void ClearGroupsTest2()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "hj";
//            SignGroupInfo[] group = new SignGroupInfo[15];

//            for (int i = 0; i < group.Length; i++)
//            {
//                group[i] = new SignGroupInfo();
//                group[i].Name = "test" + i;

//                if (i != 0)
//                    group[i].Parent = group[i - 1];

//                target.AddGroup(group[i]);
//                SignInfo newSign = new SignInfo();
//                newSign.Name = "hh" + i;
//                group[i].AddSign(newSign);

//            }

//            int expected = 0;
//            int kk = 15;

//            Assert.AreEqual(1, target.Groups.Length);
//            Assert.AreEqual(0, target.Signs.Length);
//            Assert.AreEqual(kk, SignInfo.AllSigns.Length);
//            target.ClearGroups();
//            Assert.AreEqual(expected, target.Groups.Length);
//        }



//        /// <summary>
//        /// A test of ClearGroups() 
//        /// Including some signs and groups in Group
//        /// </summary>
//        [Test()]
//        public void ClearGroupsTest3()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            SignGroupInfo[] group = new SignGroupInfo[15];

//            for (int i = 0; i < group.Length; i++)
//            {
//                group[i] = new SignGroupInfo();

//                group[i].Name = "test" + i;
//                //if (i != 0)
//                //    group[i].Parent = group[i - 1];



//                target.AddGroup(group[i]);
//                SignInfo newSign = new SignInfo();
//                newSign.Name = "hh1" + i;
//                group[i].AddSign(newSign);

//            }
//            int expected = 0;
//            //int kk = 15;

//            // Assert.AreEqual(kk, target.Signs.Length);
//            target.ClearGroups();

//            Assert.AreEqual(expected, target.Groups.Length);


//        }

//        /// <summary>
//        /// Test ClearGroups
//        /// While delete top group, all subgroup should be deleted
//        /// </summary>
//        [Test]
//        public void ClearGroupsTest4()
//        {

//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "target";
//            SignGroupInfo[] group1 = new SignGroupInfo[16];


//            for (int i = 0; i < group1.Length; i++)
//            {
//                group1[i] = new SignGroupInfo();
//                group1[i].Name = "test" + i;
//                if (i == 0)
//                    target.AddGroup(group1[i]);
//                else
//                    //group1[i-1].AddGroup(group1[i]);
//                    group1[i].Parent = group1[i - 1];
//            }
//            int actual = (SignGroupInfo.FindAllGroups(target)).Length;

//            Assert.AreEqual(16, actual);
//            target.ClearGroups();

//            Assert.AreEqual(0, group1[1].Groups.Length);


//        }


//        /// <summary>
//        /// Test Parent Group
//        /// </summary>
//        /// <summary>
//        /// Test that a group include numbers of group
//        /// </summary>
//        [Test]
//        public void GroupNumberTest()
//        {
//            _tree.Clear();
//            //  Assert.AreEqual(12, SignGroupInfo.AllGroups.Length);
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "target";
//            _tree.AddGroup(target);
//            SignGroupInfo[] group1 = new SignGroupInfo[16];


//            for (int i = 0; i < group1.Length; i++)
//            {
//                group1[i] = new SignGroupInfo();
//                group1[i].Name = "test" + i;
//                if (i == 0)
//                    target.AddGroup(group1[i]);
//                else
//                    //group1[i-1].AddGroup(group1[i]);
//                    group1[i].Parent = group1[i - 1];
//            }

//            int actual = (SignGroupInfo.FindAllGroups(target)).Length;

//            Assert.AreEqual(16, actual);
//            Assert.AreEqual(17, SignGroupInfo.AllGroups.Length);
//            //Assert.AreEqual(0, group1[1].Groups.Length);


//        }

//        /// <summary>
//        /// Test the total number of group
//        /// </summary>
//        [Test]
//        public void TotalGroupTest()
//        {
//            //_tree.Clear();
//            Assert.AreEqual(0, SignGroupInfo.AllGroups.Length);
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "target";
//            _tree.AddGroup(target);
//            SignGroupInfo[] group1 = new SignGroupInfo[16];


//            for (int i = 0; i < group1.Length; i++)
//            {
//                group1[i] = new SignGroupInfo();
//                group1[i].Name = "test" + i;
//                if (i == 0)
//                    target.AddGroup(group1[i]);
//                else
//                    //group1[i-1].AddGroup(group1[i]);
//                    group1[i].Parent = group1[i - 1];
//            }

//            int actual = (SignGroupInfo.FindAllGroups(target)).Length;

//            Assert.AreEqual(16, actual);
//            Assert.AreEqual(17, SignGroupInfo.AllGroups.Length);
//            //Assert.AreEqual(0, group1[1].Groups.Length);


//        }
//        [Test()]
//        public void ContainsSignTest()
//        {
//            SignGroupInfo target = new SignGroupInfo();

//            SignInfo sign = null;
//            //bool expected = false;
//            bool actual;

//            actual = target.ContainsSign(sign);
//        }

//        /// <summary>
//        /// Group is empty ,the result is false.
//        /// </summary>
//        [Test()]
//        public void RemoveGroupTest()
//        {
//            SignGroupInfo target = new SignGroupInfo();

//            SignGroupInfo group = null;

//            bool expected = false;
//            bool actual;

//            actual = target.RemoveGroup(group,true);
//            Assert.AreEqual(expected, actual);
//        }

//        /// <summary>
//        /// Group is not empty ,the result is true.
//        /// </summary>
//        [Test()]
//        public void RemoveGroupTest1()
//        {
//            SignGroupInfo target = new SignGroupInfo();

//            SignGroupInfo group = new SignGroupInfo();
//            group.Name = "test";
//            target.AddGroup(group);
//            bool expected = true;
//            bool actual;

//            actual = target.RemoveGroup(group,true);
//            Assert.AreEqual(expected, actual);
//            //target.AddGroup(group);

//        }

//        /// <summary>
//        /// Sign is empty, the result is false
//        /// </summary>
//        [Test()]
//        public void RemoveSignTest()
//        {
//            SignGroupInfo target = new SignGroupInfo();

//            SignInfo sign = null;

//            bool expected = false;
//            bool actual;

//            actual = target.RemoveSign(sign);
//            Assert.AreEqual(expected, actual);
//        }

//        /// <summary>
//        /// Sign is not empty, the result is true
//        /// </summary>
//        [Test()]
//        public void RemoveSignTest1()
//        {
//            SignGroupInfo target = new SignGroupInfo();

//            SignInfo sign = new SignInfo();
//            sign.Name = "test1";
//            target.AddSign(sign);
//            bool expected = true;
//            bool actual;

//            actual = target.RemoveSign(sign);
//            Assert.AreEqual(expected, actual);

//        }

//        /// <summary>
//        /// Test remove()
//        /// While DashboardItem is null
//        /// </summary>
//        [Test()]
//        public void RemoveTest()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "target";
//            DashboardItem item = null;
       
//            bool expected = false;
//            bool actual = target.Remove(item);
                            
//            Assert.AreEqual(expected, actual);
           

//        }

//        /// <summary>
//        /// Test remove()
//        /// While DashboardItem is group
//        /// </summary>
//        [Test()]
//        public void RemoveTest1()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "target";
//            SignGroupInfo group = new SignGroupInfo();
//            group.Name = "group";
//            group.Parent = target;
//            bool expected = true;

//            bool actual = target.Remove(group);
//            Assert.AreEqual(expected, actual);
//        }

//        /// <summary>
//        /// Test remove()
//        /// While DashboardItem is sign
//        /// </summary>
//        [Test()]
//        public void RemoveTest2()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "target";
//            SignInfo sign = new SignInfo();
//            sign.Name = "sign";
//            sign.Parent = target;
//            bool expected = true;

//            bool actual = target.Remove(sign);
//            Assert.AreEqual(expected, actual);
//        }

//        /// <summary>
//        /// Test remove()
//        /// While DashboardItem is sign
//        /// </summary>
//        [Test()]
//        public void AddTest()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "target";
//            SignInfo sign = null;
           
//            bool expected = false;

//            bool actual = target.Add(sign);
//            Assert.AreEqual(expected, actual);
//        }

//        /// <summary>
//        /// Test IsEmpty()
//        /// Value of _isEmpty is true
//        /// </summary>
//        [Test()]
//        public void IsEmptyTest()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "target";
//            //SignInfo sign = null;SignGroupInfo.Empty

//            int expected = 0;
            
//            int actual = SignGroupInfo.FindAllGroups(SignGroupInfo.Empty).Length;
//            Assert.AreEqual(expected, actual);
//        }

//        /// <summary>
//        /// Test  return valule of GetHashCode()
//        /// </summary>
//        [Test()]
//        public void GetHashCodeTest()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "target";
//            bool actual = false;
           
//            target.GetHashCode();
//            actual = true;
//            Assert.AreEqual(true, actual);
//        }

//        /// <summary>
//        /// Test Signs property
//        /// Assign signs to target.Signs ;
//        /// </summary>
//        [Test()]
//        public void SignsTest()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "target";
//            int expected = 4;
//            SignInfo[] signs = new SignInfo[4];
//            for (int i = 0; i < 4; i++)
//            {
//                signs[i] = new SignInfo();
//                signs[i].Name = "i" + i;
//            }

//            target.Signs = signs;



//            Assert.AreEqual(expected, target.Signs.Length);
//        }

//        /// <summary>
//        /// Test Signs property
//        /// target.Signs is  null;
//        /// </summary>
//        [Test()]
//        public void SignsTest1()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "target";
//            int expected = 0;
//            target.Signs = null;
//            Assert.AreEqual(expected, target.Signs.Length);
//        }


//        /// <summary>
//        /// Test Groups property
//        /// Assign  groups to target.Groups ;
//        /// </summary>
//        [Test()]
//        public void GroupsPropertyTest()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "target";
//            int expected = 4;
//            SignGroupInfo[] groups = new SignGroupInfo[4];
//            for (int i = 0; i < 4; i++)
//            {
//                groups[i] = new SignGroupInfo();
//                groups[i].Name = "i" + i;
//            }

//            target.Groups = groups;
//            Assert.AreEqual(expected, target.Groups.Length);
//        }

//        /// <summary>
//        /// Test Groups property
//        /// Assign  null to target.Groups ;
//        /// </summary>
//        [Test()]
//        public void GroupsPropertyTest1()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "target";
//            int expected = 0;
          
//            target.Groups = null;



//            Assert.AreEqual(expected, target.Groups.Length);
//        }
        
//        /// <summary>
//        /// While a group is not root group,test GetRootGroup() by IsSignCountValid()
//        /// </summary>
//        [Test()]
//        public void GetRootGroupTest()
//        {
//            SignGroupInfo target = new SignGroupInfo();

//            target.Name = "target";
//            _tree.AddGroup(target);
//            SignGroupInfo group = new SignGroupInfo();
//            group.Name = "group";
//            group.Parent = target;

//            bool actual = SignGroupInfo.IsSignCountValid(group);


//            Assert.AreEqual(false, actual);

//        }

//        /// <summary>
//        /// While a group is not root group,test GetRootGroup() by IsSignCountValid()
//        /// </summary>
//        [Test()]
//        public void GetRootGroupTest1()
//        {
//            SignGroupInfo target = new SignGroupInfo();

//            target.Name = "target";
//            _tree.AddGroup(target);
//            SignGroupInfo group = new SignGroupInfo();
//            group.Name = "group";
//            group.Parent = target;

//            bool actual = SignGroupInfo.IsSignCountValid(target);
            
//            Assert.AreEqual(false, actual);

//        }
        

//        /// <summary>
//        /// 测试IsSignCountValid（）函数
//        /// 条件是存在25 sign 并且group组是树的子组
//        /// 结果应该是true
//        /// </summary>
//        [Test]
//        public void IsSignCountValidTest()
//        {


//            SignGroupInfo group = new SignGroupInfo();
//            group.Name = "group";
//            _tree.AddGroup(group);
//            //_tree =DataGate.Instance.GroupTree;
//            //int expected = 20;

//            for (int i = 0; i < 25; i++)
//            {
//                SignGroupInfo subNode = new SignGroupInfo();
//                subNode.Name = "SubNode" + i;
//                group.AddGroup(subNode);

//                SignInfo sign = new SignInfo();
//                sign.Name = "Sign" + i.ToString();

//                group.AddSign(sign);
//            }


//            bool actual = SignGroupInfo.IsSignCountValid(group);


//            Assert.AreEqual(true, actual);

//        }

//        /// <summary>
//        /// 测试IsSignCountValid（）函数
//        /// 条件是存在19 sign 并且group组是树的子组
//        /// 结果应该是false
//        /// </summary>
//        [Test]
//        public void IsSignCountValidTest1()
//        {


//            SignGroupInfo group = new SignGroupInfo();
//            group.Name = "group";
//            _tree.AddGroup(group);
//            //_tree =DataGate.Instance.GroupTree;
//            int expected = 20;

//            for (int i = 0; i < 19; i++)
//            {
//                SignGroupInfo subNode = new SignGroupInfo();
//                subNode.Name = "SubNode" + i;
//                group.AddGroup(subNode);

//                SignInfo sign = new SignInfo();
//                sign.Name = "Sign" + i.ToString();

//                group.AddSign(sign);
//            }


//            bool actual = SignGroupInfo.IsSignCountValid(group);


//            Assert.AreEqual(false, actual);
//            Assert.AreEqual(19,SignInfo.AllSigns.Length);

//        }

//        /// <summary>
//        /// 测试IsSignCountValid（）函数
//        /// 条件是存在20 sign 并且group组是树的子组
//        /// 结果应该是false
//        /// </summary>
//        [Test]
//        public void IsSignCountValidTest2()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "target";
//            _tree.AddGroup(target);
//            SignGroupInfo[] group = new SignGroupInfo[20];

//            for (int i = 0; i < group.Length; i++)
//            {
//                group[i] = new SignGroupInfo();
//                group[i].Name = "test" + i;

//                if (i == 0)
//                    group[i].Parent = target;
//                else
//                    group[i].Parent = group[i - 1];

//                target.AddGroup(group[i]);
//                SignInfo newSign = new SignInfo();
//                newSign.Name = "hh" + i;
//                group[i].AddSign(newSign);
//            }
//            bool actual = SignGroupInfo.IsSignCountValid(target);
//            Assert.AreEqual(false, actual, "Sign Count Valid testing error");
//        }

//        /// <summary>
//        /// 测试Equals（）函数
//        /// Test (target =target)
//        /// The result is true
//        /// </summary>
//        [Test]
//        public void EqualsTest()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name="target";
//            //_tree.AddGroup(target);
//            bool actual= target.Equals(target);
//            Assert.AreEqual(true,actual);

//        }

//        /// <summary>
//        /// 测试Equals（）函数
//        /// Test (target =group)
//        /// The result is false
//        /// </summary>
//        [Test]
//        public void EqualsTest1()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "target";
//            SignGroupInfo group = new SignGroupInfo();
//            group.Name = "group";
//            //_tree.AddGroup(target);
//            bool actual = target.Equals(group);
//            Assert.AreEqual(false, actual);

//        }

//        /// <summary>
//        /// 测试Equals（）函数
//        /// While group is null,if target equale group
//        /// The result is false
//        /// </summary>
//        [Test]
//        public void EqualsTest2()
//        {
//            SignGroupInfo target = new SignGroupInfo();
//            target.Name = "target";
//            SignGroupInfo group = null;
//            //group.Name = "group";
//            //_tree.AddGroup(target);
//            bool actual = target.Equals(group);
//            Assert.AreEqual(false, actual);

//        }

      


//        //[Test()]
//        //public void ContainsTest()
//        //{
//        //    SignGroupTree target = new SignGroupTree();

//        //    SignGroupInfo item = null; // TODO: Initialize to an appropriate value

//        //    bool expected = false;
//        //    bool actual;

//        //    actual = target.Contains(item);
//        //}

//        //[Test()]
//        //public void ContainsTest1()
//        //{
//        //    SignGroupTree target = new SignGroupTree();

//        //    SignInfo item = null; // TODO: Initialize to an appropriate value

//        //    bool expected = false;
//        //    bool actual;

//        //    actual = target.Contains(item);
//        //}



//    }

//}
