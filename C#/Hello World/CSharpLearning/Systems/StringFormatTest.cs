using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;

namespace CSharpLearning
{
    [TestFixture]
    class StringFormatTest
    {
        [Test, Description("数值型数据的格式化")]
        public void Test1()
        {
            var temp = 1000;
            Console.WriteLine("|{0,10}|", temp);
            Console.WriteLine("|{0,-10}|", temp);
            Console.WriteLine("|{0,3}|", temp);
            Console.WriteLine("|{0,10:X4}|", temp);

            var temp2 = 123.456789;
            Console.WriteLine("{0:F3}", temp2);//定点，保留小数位数
            Console.WriteLine("{0:C}", temp2);//表示货币，取决于PC的区域设置
            Console.WriteLine("{0:D10}", 123);//十进制数
            Console.WriteLine("{0:G4}", temp2);//根据说明符保留“数字长度”，最后一位四舍五入
            Console.WriteLine("{0:X}", 123);//转16进制（区分大小写）
            Console.WriteLine("{0:N4}", 1234567, 890123);// 用逗号分隔数字
            Console.WriteLine("{0:P}", temp2);//百分比
            Console.WriteLine("{0:R}", temp2);//
            Console.WriteLine("{0:E3}", temp2);//科学计数法（区分大小写）
        }
    }
}
