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

    /// <summary>
    /// 
    /// </summary>
    class TwoDPoint
    {
        public readonly int x, y;

        public TwoDPoint(int x, int y)  //constructor
        {
            this.x = x;
            this.y = y;
        }

        public override bool Equals(System.Object obj)
        {
            // If parameter is null return false.
            if (obj == null)
            {
                return false;
            }

            // If parameter cannot be cast to Point return false.
            TwoDPoint p = obj as TwoDPoint;
            if ((System.Object)p == null)
            {
                return false;
            }

            // Return true if the fields match:
            return (x == p.x) && (y == p.y);
        }

        public bool Equals(TwoDPoint p)
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
            return x ^ y;
        }

        //add this code to class ThreeDPoint as defined previously
        public static bool operator ==(TwoDPoint a, TwoDPoint b)
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

        public static bool operator !=(TwoDPoint a, TwoDPoint b)
        {
            return !(a == b);
        }
    }

    [TestFixture, Description("���ں����ز��ԡ�")]
    class EqualsOverrideTest
    {
        [Test, Description("�����Զ������==������")]
        public void Test1()
        {
            var p1 = new TwoDPoint(1, 1);
            var p2 = new TwoDPoint(1, 2);

            if (p1 == p2)
            {
                Console.WriteLine("p1 == p2");
            }
            else
            {
                Console.WriteLine("p1 != p2");
            }
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
