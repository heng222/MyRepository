using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using NUnitStudy.Framework;

namespace NUnitStudy.Specs.Adder
{
    [TestFixture]
    public class AdderTest
    {
        [Test]
        public void NormalTest()
        {
            //Given: 创建一个新的加法器
            var adder = new Adder();

            var testTable = Table.Parse(@"Specs\Adder\Adder.txt");

            foreach (var row in testTable)
            {
                int a;
                int b;

                if (!int.TryParse(row["a"], out a))
                {
                    throw new FormatException("无效参数数据:" + row);
                }

                if (!int.TryParse(row["b"], out b))
                {
                    throw new FormatException("无效参数数据:" + row);
                }

                //When : 当向加法器的加法方法中传入两个参数

                var strExpected = row["result"].Trim();

                //Then ：那么加法器应当自动正确的计算出这两个数的和并返回
                var actual = adder.Add(a, b);

                var expected = int.Parse(row[2]);

                Assert.AreEqual(expected, actual);
                
            }
        }

        [Test]
        [TestCase(@"Specs\Adder\Overflow.txt")]
        public void Overflow_test(string test_data_file)
        {
            //Given: 创建一个新的加法器
            var testTable = Table.Parse(test_data_file);
            var adder = new Adder();


            foreach (var row in testTable)
            {
                int a;
                int b;

                if (!int.TryParse(row["a"], out a))
                {
                    throw new FormatException("无效参数数据:" + row);
                }

                if (!int.TryParse(row["b"], out b))
                {
                    throw new FormatException("无效参数数据:" + row);
                }

                Assert.Throws(typeof(OverflowException), () => adder.Add(a, b));
            }

        }

        class Adder
        {
            public int Add(int a, int b)
            {
                return a + b;
            }
        }
    }
}
