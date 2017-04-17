

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
            return "Id:" + Id + "����:" + Name + "����:" + Age;
        }
    }

    /// <summary>
    /// Lambda���ʽ��ʾ
    /// </summary>
    [NUnit.Framework.TestFixture]
    class LambdaExpressionTest
    {
        [NUnit.Framework.Test(Description = "���Ұ����ַ���'YJingLee'��Ԫ�ء�")]
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

            // ѡ������Ϊ��YJingLee����User��
            var yJingLee = user.Where(p => p.Name == "YJingLee").FirstOrDefault();
            Assert.AreEqual("YJingLee", yJingLee.Name);

            // ѡ������Ϊ��YJingLee����User���������������List��
            var results = user.Where(p => p.Name == "YJingLee").ToList();
            Assert.AreEqual("YJingLee", results[0].Name);


            // ��User�����Ageֵ����ƽ������
            double average = user.Average(p => p.Age);
            Assert.AreEqual(30, average);

        }
    }
}
