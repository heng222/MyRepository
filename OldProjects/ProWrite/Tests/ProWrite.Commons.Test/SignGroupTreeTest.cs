//---------------------------------------------------------------------
//
// File: SignGroupInfoTest.cs
//
// Description:
// Test mothod of SignGroupInfo class 
//
// Author: William
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// Modify history:   
//  William  2008-6-25 �޸����ݣ�����ע��
// 
//---------------------------------------------------------------------

using System;
using System.Text;
using System.Collections.Generic;
using NUnit.Framework;
using ProWrite.Entity;
using System.IO;
using System.Xml.Serialization;
using ProWrite.Core;
using ProWrite.Entity.Dashboard;
namespace ProWrite.Commons.Test
{
    /// <summary>
    /// Summary description for SignGroupTreeTest
    /// </summary>
    [TestFixture]
    public class SignGroupTreeTest
    {
        

        #region Additional test attributes

        private SignGroupTree tree;
        [SetUp()]
        public void MySetUp()
        {
            tree = new SignGroupTree();
            //SignInfo signn = new SignInfo();
            //signn.Name = "signn";
            //_tree.AddSign(signn);
        }


        [TearDown()]
        public void MyTearDown()
        {
            tree.Clear();
        }

        
        #endregion
       
        /// <summary>
        /// Test "Get" property of Name
        /// </summary>
        /// </summary>
        [Test]
        public void NameTest()
        {

            
            Assert.AreEqual("", tree.Name); 
            
        }



        /// <summary>
        /// Test ToString()
        /// һ��������ֱ�ӵ���ToString����
        /// </summary>
        [Test]
        public void ToStringTest()
        {

            SignGroupTree tree = new SignGroupTree();
            Assert.AreEqual("", tree.ToString());

        }

        /// <summary>
        /// Test PopulateRelation Function
        /// ������������û���κ��ӽڵ�
        /// </summary>
        [Test]
        public void PopulateRelationTest()
        {
            bool flag = false;
            tree.PopulateRelation();
            flag = true;
            Assert.AreEqual(true, flag);

            Assert.AreEqual(0, tree.Signs.Length);
            Assert.AreEqual(0, tree.Groups.Length);

        }

        /// <summary>
        /// Test PopulateRelation Function
        /// ��������������һ�����鲢����������һ��sign
        /// ���Է�����ͨ�����������л���Ȼ�����л�������PopulateRelation�������鿴���Ĺ�ϵ�Ƿ����
        /// </summary>
        [Test]
        public void PopulateRelationTest1()
        {
            SignInfo sign = new SignInfo();
            SignGroupInfo group = new SignGroupInfo();
            group.Name = "group";

            sign.Name = "sign";
            group.Parent = tree;
            sign.Parent = group;
            //_tree.AddSign(sign);
            Serialiser<SignGroupTree> ser = Serialiser<SignGroupTree>.Binaray;
            using (MemoryStream stream = new MemoryStream())
            {
                ser.Serialize(tree, stream);
                
                tree.Clear();
                stream.Position = 0;
                tree = ser.Deserialise(stream);
                stream.Close();

             }

            tree.PopulateRelation();
           // 
            Assert.AreEqual(1, tree.Groups.Length);
            Assert.AreEqual(1, tree.Groups[0].Signs.Length);
            Assert.AreEqual(0, tree.Signs.Length);
            
        }

        /// <summary>
        /// Test PopulateRelation Function
        /// ��������������һ�����鲢����������һ��sign
        /// ���Է�����ͨ�����������л���Ȼ�����л���������PopulateRelation�������鿴���Ĺ�ϵ�Ƿ����
        /// </summary>
        [Test]
        public void PopulateRelationTest4()
        {
            SignInfo sign = new SignInfo();
            SignGroupInfo group = new SignGroupInfo();
            group.Name = "group";

            sign.Name = "sign";
            group.Parent = tree;
            sign.Parent = group;
            //_tree.AddSign(sign);
            //SignGroupTree aa = new SignGroupTree();
            Serialiser<SignGroupTree> ser = Serialiser<SignGroupTree>.Binaray;
            using (MemoryStream stream = new MemoryStream())
            {
                ser.Serialize(tree, stream);

                tree.Clear();
                stream.Position = 0;
                tree = ser.Deserialise(stream);
                stream.Close();

            }

            //_tree.PopulateRelation();
            //Assert.IsTrue(Equals(_tree,aa));
            Assert.AreEqual(1, tree.Groups.Length);
            Assert.AreEqual(1, tree.Groups[0].Signs.Length);
            Assert.AreEqual(0, tree.Signs.Length);
            
        }

        /// <summary>
        /// Test PopulateRelation Function
        /// ��������������һ�����鲢����������һ��sign
        /// ���Է�����ͨ��XML���л���Ȼ�����л���������PopulateRelation�������鿴���Ĺ�ϵ�Ƿ����
        /// </summary>
        //[Test]
        public void PopulateRelationTest5()
        {
            SignInfo sign = new SignInfo();
            SignGroupInfo group = new SignGroupInfo();
            group.Name = "group";

            sign.Name = "sign";
            group.Parent = tree;
            sign.Parent = group;
            //_tree.AddSign(sign);
            SignGroupTree aa = new SignGroupTree();
            Serialiser<SignGroupTree> ser = Serialiser<SignGroupTree>.Xml;
            using (MemoryStream stream = new MemoryStream())
            {
                ser.Serialize(tree, stream);

                tree.Clear();
                stream.Position = 0;
                
                aa = ser.Deserialise(stream);
                stream.Close();

            }

            //_tree.PopulateRelation();
          
            Assert.AreEqual(1, aa.Groups.Length);
            Assert.AreEqual(1, aa.Groups[0].Signs.Length);
            Assert.AreEqual(0, aa.Signs.Length);

            
        }

        /// <summary>
        /// Test PopulateRelation Function
        /// ��������������һ�����鲢����������һ��sign
        /// ���Է�����ͨ��XML���л���Ȼ�����л�������PopulateRelation�������鿴���Ĺ�ϵ�Ƿ����
        /// </summary>
        //[Test]
        public void PopulateRelationTest6()
        {
            SignInfo sign = new SignInfo();
            SignGroupInfo group = new SignGroupInfo();
            group.Name = "group";

            sign.Name = "sign";
            group.Parent = tree;
            sign.Parent = group;
            SignGroupTree aa = new SignGroupTree();
            Serialiser<SignGroupTree> ser = Serialiser<SignGroupTree>.Xml;
            using (MemoryStream stream = new MemoryStream())
            {
                ser.Serialize(tree, stream);

                tree.Clear();
                stream.Position = 0;
                aa = ser.Deserialise(stream);
                stream.Close();

            }

            tree.PopulateRelation();
            Assert.AreEqual(1, aa.Groups.Length);
            Assert.AreEqual(1, aa.Groups[0].Signs.Length);
            Assert.AreEqual(0, aa.Signs.Length);

        }

        /// <summary>
        /// Test PopulateRelation Function
        /// ������������ֻ��һ��sign
        /// </summary>
        [Test]
        public void PopulateRelationTest2()
        {
            SignInfo sign = new SignInfo();
            sign.Name = "sign";
            //_tree.AddSign(sign);
            sign.Parent = tree;
            SignGroupTree aa = new SignGroupTree();
            Serialiser<SignGroupTree> ser = Serialiser<SignGroupTree>.Binaray;
            using (MemoryStream stream = new MemoryStream())
            {
                ser.Serialize(tree, stream);

                tree.Clear();
                stream.Position = 0;
                aa = ser.Deserialise(stream);
                stream.Close();
            }

            tree.PopulateRelation();
            Assert.AreEqual(1, aa.Signs.Length);
            Assert.AreEqual(0, aa.Groups.Length);

        }

        /// <summary>
        /// Test PopulateRelation Function
        /// ������������ֻ��һ������
        /// </summary>
        [Test]
        public void PopulateRelationTest3()
        {
            //SignGroupInfo sign = new SignGroupInfo();
            //sign.Name = "sign";
            //_tree.AddSign(sign);
            //sign.Parent = _tree;
            //_tree.PopulateRelation();

            //Assert.AreEqual(1, _tree.Groups.Length);
            //Assert.AreEqual(0, _tree.Signs.Length);

        }

        /// <summary>
        /// Test HasChanged Function
        /// ����������Only there is a group in the _tree
        /// </summary>
        [Test]
        public void HasChangedTest()
        {
            SignGroupInfo group = new SignGroupInfo();
            group.Name = "group";
            //_tree.AddSign(sign);
            group.Parent = tree;
            Assert.AreEqual(true, tree.IsChanged);

        }

        /// <summary>
        /// Test HasChanged Function
        /// ����������Only there is a sign in the _tree
        /// </summary>
        [Test]
        public void HasChangedTest1()
        {
            SignInfo sign = new SignInfo();
            sign.Name = "sign";
            //_tree.AddSign(sign);
            sign.Parent = tree;
            Assert.AreEqual(true, tree.IsChanged);

        }

        /// <summary>
        /// Test HasChanged Function
        /// ������������û���κ��ӽڵ�
        /// </summary>
        [Test]
        public void HasChangedTest2()
        {
            
            Assert.AreEqual(false, tree.IsChanged);

        }

        /// <summary>
        /// Test HasChanged Function
        /// ����������there are a group and sign in the _tree
        /// </summary>
        [Test]
        public void HasChangedTest3()
        {
            Assert.AreEqual(false, tree.IsChanged);

            SignInfo sign = new SignInfo();
            SignGroupInfo group = new SignGroupInfo();
            group.Name = "group";

            sign.Name = "sign";
            group.Parent = tree;
            sign.Parent = group;
            Assert.AreEqual(true, tree.IsChanged);

        }

        /// <summary>
        /// Test HasChanged Function
        /// ����������һ��sign���鸳��tree.Signs.
        /// �������ἤ��HasChanged����
        /// </summary>
        [Test]
        public void HasChangedTest4()
        {

            SignInfo[] signs=new SignInfo[4];
            for(int i=0;i<signs.Length;i++)
            {
                signs[i]=new SignInfo();
                signs[i].Name="name"+i;
                            
            }

            tree.Signs = signs;

            Assert.AreEqual(false, tree.IsChanged);

        }

       
        /// <summary>
        /// Test AcceptChanges Function
        /// ����������Add a group to the _tree,check HasChanged value 
        /// </summary>
        [Test]
        public void AcceptChangesTest()
        {

            
            SignGroupInfo group = new SignGroupInfo();
            group.Name = "group";
           // group.Parent = _tree;
            tree.AddGroup(group);
            Assert.AreEqual(true,tree.IsChanged);
            tree.AcceptChanges();
            Assert.AreEqual(false, tree.IsChanged);

            

            
        }

        /// <summary>
        /// Test AcceptChanges Function
        /// ����������Add a sign to the _tree,check HasChanged value 
        /// </summary>
        [Test]
        public void AcceptChangesTest1()
        {

            SignInfo sign = new SignInfo();
            sign.Name = "sign";
           
            sign.Parent = tree;
            Assert.AreEqual(true, tree.IsChanged);
            tree.AcceptChanges();
            Assert.AreEqual(false, tree.IsChanged);




        }

        /// <summary>
        /// Test AcceptChanges Function
        /// ����������Nonthing is added,check HasChanged value 
        /// </summary>
        [Test]
        public void AcceptChangesTest2()
        {

            
            Assert.AreEqual(false, tree.IsChanged);
            tree.AcceptChanges();
            Assert.AreEqual(false, tree.IsChanged);

        }


        /// <summary>
        /// Test AcceptChanges Function
        /// ����������circle to added signs and groups,check HasChanged value 
        /// </summary>
        [Test]
        public void AcceptChangesTest3()
        {
            SignGroupInfo[] group = new SignGroupInfo[14];
            for (int i = 0; i < group.Length; i++)
            { 
               group[i]=new SignGroupInfo();
               group[i].Name = "group" + i;

               SignInfo newsign = new SignInfo();
               newsign.Name="sing"+i;
               if (i == 0)
               {
                   group[i].Parent = tree;

               }

               else
               {
                   group[i].Parent = group[i - 1];
                   newsign.Parent = group[i];
               
               }
      
            }

            Assert.AreEqual(true, tree.IsChanged);
            tree.AcceptChanges();
            Assert.AreEqual(false, tree.IsChanged);




        }
        
        
        
    }
}
