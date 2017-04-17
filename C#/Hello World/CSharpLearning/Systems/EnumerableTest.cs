/*----------------------------------------------------------------
// ��˾���ƣ���������΢���Ƽ����޹�˾
// 
// ��Ŀ���ƣ���SIL2��֤�ı�׼��ATS
//
// �� �� �ˣ�zhangheng
// �������ڣ�2014-4-8 9:30:22 
// ��    �䣺zhangheng@bjmut.com
//
// Copyright (C) ��������΢���Ƽ����޹�˾ 2009����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;
using NUnit.Framework;

namespace CSharpLearning
{
    internal class MyCollection : IEnumerable<int>
    {
        int[] data = { 1, 2, 3 };

        #region IEnumerable<int> ��Ա

        [Test()]
        public IEnumerator<int> GetEnumerator()
        {
            int a = 10;
            //             foreach (var item in data)
            //             {
            //                 a++;
            //                 yield return item;
            //             }

            yield return a++;

            yield return a++;

            yield return a++;

            yield break;
        }

        #endregion

        #region IEnumerable ��Ա

        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }

        #endregion
    }

    [TestFixture(Description="����yield�ؼ��ֵ�ʹ�á�")]
    public class MyCollectionTest
    {

        [Test]
        public void Test()
        {
            var myCollection = new MyCollection();

            //
            foreach (var item in myCollection)
            {
                Console.WriteLine(item);
            }

            //
            IEnumerator<int> enumerator = myCollection.GetEnumerator();
            while (enumerator.MoveNext())
            {
                Console.WriteLine(enumerator.Current);
            }
        }
    }
}
