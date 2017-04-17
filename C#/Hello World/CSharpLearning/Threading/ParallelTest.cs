using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using System.Threading.Tasks;

namespace CSharpLearning.Threading
{
    [TestFixture]
    class ParallelTest
    {
        [Test]
        private void ParallelTest2()
        {
            for (int i = 1; i < 5; i++)
            {
                Console.WriteLine(DoWork(i));
            }

            // 和上面的代码等价，但是是多线程并行执行的，注意这里的结束index不包含5
            var plr = Parallel.For(1, 5, i => Console.WriteLine(DoWork(i)));
        }

        private int DoWork(int num)
        {
            int sum = 0;
            for (int i = 0; i <= num; i++)
            {
                sum += i;
            }
            return sum;
        }

    }
}
