using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using System.Collections;

// Linq必须以Select或Group by结尾

namespace CSharpLearning.Linq
{
    /// <summary>
    /// 参考：https://www.cnblogs.com/liqingwen/p/5801249.html
    /// </summary>
    [TestFixture(Description="Linq语句学习")]
    class LinqTest
    {
        private readonly string[] languages = 
        { "Java", "C#", "C++", "Delphi", "VB.net", "VC.net", "C++ Builder", "Kylix", "Perl", "Python" };

        #region "" 
        #endregion

        [Test(Description = "查询以字符c打头的所有字符串")]
        public void FirstCharIsC_Test()
        {
            var query = from item in languages
                        where (item.First() == 'C')
                        select item;

            foreach (var item in query)
            {
                Console.Write(item + ", ");
            }
        }
    }

}
