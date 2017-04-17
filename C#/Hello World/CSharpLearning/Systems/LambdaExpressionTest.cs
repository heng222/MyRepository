

using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;
using System.Linq;
using NUnit.Framework;

namespace CSharpLearning
{
    public class User
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public int Age { get; set; }
        public string Read()
        {
            return "Id:" + Id + "姓名:" + Name + "年龄:" + Age;
        }
    }

    /// <summary>
    /// Lambda表达式演示
    /// </summary>
    [NUnit.Framework.TestFixture]
    class LambdaExpressionTest
    {
        [NUnit.Framework.Test(Description = "查找包含字符串'YJingLee'的元素。")]
        public void General_Test()
        {
            var list = new List<string> { "YJingLee", "YJingLee1", "YJingLee2" , "YJing"};
            var inString = list.FindAll(s => s.IndexOf("YJingLee") >= 0);
        }

        [NUnit.Framework.Test(Description = "General test1.")]
        public void General_Test1()
        {
            List<User> user = new List<User>{
                    new User{Id=1,Name="YJingLee",Age=20},
                    new User{Id=2,Name="XieQing",Age=40},
                };

            // 选择姓名为“YJingLee”的User。
            var yJingLee = user.Where(p => p.Name == "YJingLee").FirstOrDefault();
            Assert.AreEqual("YJingLee", yJingLee.Name);

            // 选择姓名为“YJingLee”的User，并将结果保存在List中
            var results = user.Where(p => p.Name == "YJingLee").ToList();
            Assert.AreEqual("YJingLee", results[0].Name);


            // 用User对象的Age值计算平均年龄
            double average = user.Average(p => p.Age);
            Assert.AreEqual(30, average);

        }
    }
}
