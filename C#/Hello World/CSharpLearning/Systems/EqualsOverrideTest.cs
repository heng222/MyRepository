/*----------------------------------------------------------------
// Copyright (C) 2007 ��������΢���Ƽ����޹�˾ ��Ȩ����
// 
// �ļ�����
// �ļ�����������
//
// 
// �����ˣ��ź�
// �������ڣ�
//
// �޸ı�ʶ��
// �޸�������
//
//----------------------------------------------------------------*/
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using NUnit.Framework;

namespace CSharpLearning
{
    class MyPoint
    {
        public int X { get; private set; }
        public int Y { get; private set; }

        public MyPoint(int x, int y)  //constructor
        {
            this.X = x;
            this.Y = y;
        }

        public override bool Equals(System.Object obj)
        {
            // If parameter is null return false.
            if (obj == null)
            {
                return false;
            }

            // If parameter cannot be cast to Point return false.
            MyPoint p = obj as MyPoint;
            if ((System.Object)p == null)
            {
                return false;
            }

            // Return true if the fields match:
            return (X == p.X) && (Y == p.Y);
        }

        public bool Equals(MyPoint p)
        {
            // If parameter is null return false:
            //if ((object)p == null)
            //{
            //    return false;
            //}

            //// Return true if the fields match:
            //return (x == p.x) && (y == p.y);
            return this.Equals(p as object);
        }

        public override int GetHashCode()
        {
            return X ^ Y;
        }

        //add this code to class ThreeDPoint as defined previously
        public static bool operator ==(MyPoint a, MyPoint b)
        {
            // If both are null, or both are same instance, return true.
            if (System.Object.ReferenceEquals(a, b))
            {
                return true;
            }

            //// If one is null, but not both, return false.
            //if (((object)a == null) || ((object)b == null))
            //{
            //    return false;
            //}

            //// Return true if the fields match:
            //return a.x == b.x && a.y == b.y;
            return a.Equals(b);
        }

        public static bool operator !=(MyPoint a, MyPoint b)
        {
            return !(a == b);
        }

        public static implicit operator MyPoint(System.Drawing.Point point)
        {
            return new MyPoint(point.X, point.Y);
        }

        public static explicit operator MyPoint(System.Drawing.PointF pointF)
        {
            return new MyPoint((int)pointF.X, (int)pointF.Y);
        }
    }

    [TestFixture, Description("���ں����ز��ԡ�")]
    class EqualsOverrideTest
    {
        [Test, Description("�����Զ������==������")]
        public void TestEqualsSign()
        {
            var p1 = new MyPoint(1, 1);
            var p2 = new MyPoint(1, 2);

            if (p1 == p2)
            {
                Console.WriteLine("p1 == p2");
            }
            else
            {
                Console.WriteLine("p1 != p2");
            }
        }

        [Test, Description("�����Զ������ Equals ����")]
        public void TestObjectEquals()
        {
            var p1 = new MyPoint(1, 1);
            var p2 = new MyPoint(1, 1);

            // ���� TwoDPoint.Equals��
            Assert.AreEqual(true, object.Equals(p1, p2));
            Assert.AreEqual(true, p1.Equals(p2));

            // �����õ��� TwoDPoint.Equals��
            Assert.AreEqual(false, object.ReferenceEquals(p1, p2));
        }

        [Test]
        public void TestImplicit()
        {
            MyPoint myPoint = new Point(100, 100);
            Assert.AreEqual(100, myPoint.X);
            Assert.AreEqual(100, myPoint.Y);
        }

        [Test]
        public void TestExplicit()
        {
            var myPoint = (MyPoint)new PointF(100.1F, 100.2F);
            Assert.AreEqual(100, myPoint.X);
            Assert.AreEqual(100, myPoint.Y);
        }

        [Test, Description("����ϵͳPoint����������������")]
        public void Test2()
        {
            var point1 = new Point(10, 10);
            var point2 = new Point(10, 10);

            var rc = point1.Equals(point2); // true

            rc = point2 == point1; // true

            rc = object.Equals(point2, point1); // true

            rc = object.ReferenceEquals(point2, point1); // false.
        }
    }
}
