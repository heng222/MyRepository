/*----------------------------------------------------------------
// Copyright (C) 2007 北京交大微联科技有限公司 版权所有
// 
// 文件名：
// 文件功能描述：
//
// 
// 创建人：张恒
// 创建日期：
//
// 修改标识：
// 修改描述：
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

        public static implicit operator MyPoint(Point point)
        {
            return new MyPoint(point.X, point.Y);
        }
        public static implicit operator Point(MyPoint point)
        {
            return new Point(point.X, point.Y);
        }

        public static explicit operator MyPoint(System.Drawing.PointF pointF)
        {
            return new MyPoint((int)pointF.X, (int)pointF.Y);
        }
    }

    [TestFixture, Description("等于号重载测试。")]
    class EqualsOverrideTest
    {
        [Test, Description("测试自定义类的==操作符")]
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

        [Test, Description("测试自定义类的 Equals 重载")]
        public void TestObjectEquals()
        {
            var p1 = new MyPoint(1, 1);
            var p2 = new MyPoint(1, 1);

            // 调用 TwoDPoint.Equals。
            Assert.AreEqual(true, object.Equals(p1, p2));
            Assert.AreEqual(true, p1.Equals(p2));

            // 不调用调用 TwoDPoint.Equals。
            Assert.AreEqual(false, object.ReferenceEquals(p1, p2));
        }

        [Test]
        public void TestImplicit()
        {
            // 调用 public static implicit operator MyPoint(System.Drawing.Point point)
            MyPoint myPoint = new Point(100, 100);
            Assert.AreEqual(100, myPoint.X);
            Assert.AreEqual(100, myPoint.Y);

            // 调用 public static implicit operator Point(MyPoint point)
            Point otherPoint = myPoint;
            Assert.AreEqual(100, otherPoint.X);
            Assert.AreEqual(100, otherPoint.Y);
        }

        [Test]
        public void TestExplicit()
        {
            var myPoint = (MyPoint)new PointF(100.1F, 100.2F);
            Assert.AreEqual(100, myPoint.X);
            Assert.AreEqual(100, myPoint.Y);
        }

        [Test, Description("测试系统Point操作符操作符重载")]
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
