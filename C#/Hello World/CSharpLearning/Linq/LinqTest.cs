using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using System.Collections;

// Linq必须以Select或Group by结尾

namespace CSharpLearning.Linq
{
    [TestFixture(Description="Linq语句学习")]
    class LinqTest
    {
        private readonly string[] languages = 
        { "Java", "C#", "C++", "Delphi", "VB.net", "VC.net", "C++ Builder", "Kylix", "Perl", "Python" };


        [Test]
        public void General_Test()
        {

            var query = from item in languages orderby item
                        group item by item.Length;// into lengthGroups;
                        //order by lengthGroups.Key descending  select lengthGroups;

            foreach (var item in query)
            {
                Console.Write(item.Key + ": ");
                foreach (var val in item)
                {
                    Console.Write(val+", ");
                }
                Console.WriteLine();
            }
        }

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
