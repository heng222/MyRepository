/*----------------------------------------------------------------
// 公司名称：北京交大微联科技有限公司
// 
// 项目名称：经SIL2认证的标准版ATS
//
// 创 建 人：zhangheng
// 创建日期：2014-4-8 9:30:22 
// 邮    箱：zhangheng@bjmut.com
//
// Copyright (C) 北京交大微联科技有限公司 2009，保留所有权利
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

        #region IEnumerable<int> 成员

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

        #region IEnumerable 成员

        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }

        #endregion
    }

    [TestFixture(Description="测试yield关键字的使用。")]
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
