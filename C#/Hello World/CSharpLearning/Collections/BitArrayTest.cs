using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using System.Collections;

namespace CSharpLearning.Collections
{
    [TestFixture]
    class BitArrayTest
    {
        [Test]
        public void Test1()
        {
            var bytes = new byte[] { 0xAA, 0x21,  0x13};

            var bitArray = new BitArray(bytes);

            // 0xAA = 1010 1010
            Assert.IsFalse(bitArray.Get(0));
            Assert.IsTrue(bitArray.Get(1));
            Assert.IsFalse(bitArray.Get(2));
            Assert.IsTrue(bitArray.Get(3));
            Assert.IsFalse(bitArray.Get(4));
            Assert.IsTrue(bitArray.Get(5));
            Assert.IsFalse(bitArray.Get(6));
            Assert.IsTrue(bitArray.Get(7));

            // 0x21 = 0010 0001
            Assert.IsTrue(bitArray[8]);
            Assert.IsFalse(bitArray[9]);
            Assert.IsFalse(bitArray[10]);
            Assert.IsFalse(bitArray[11]);
            Assert.IsFalse(bitArray[12]);
            Assert.IsTrue(bitArray[13]);
            Assert.IsFalse(bitArray[14]);
            Assert.IsFalse(bitArray[15]);

            // 0x13 = 0001 0011
            Assert.IsTrue(bitArray[16]);
            Assert.IsTrue(bitArray[17]);
            Assert.IsFalse(bitArray[18]);
            Assert.IsFalse(bitArray[19]);
            Assert.IsTrue(bitArray[20]);
            Assert.IsFalse(bitArray[21]);
            Assert.IsFalse(bitArray[22]);
            Assert.IsFalse(bitArray[23]);
        }

        [Test(Description="将BOOL型数组转换成字节流。")]
        public void Test2()
        {
            var bytes = new byte[2];

            // 0x05
            var bitArray = new BitArray(new bool[] { true, false, true, false });
            bitArray.CopyTo(bytes, 0);
            Assert.AreEqual(5, bytes[0]);

            // 0x55
            bitArray = new BitArray(new bool[] { true, false, true, false, true, false, true, false });
            bitArray.CopyTo(bytes, 0);
            Assert.AreEqual(0x55, bytes[0]);

            // 0xAA
            bitArray = new BitArray(new bool[] { false, true, false, true, false, true, false, true });
            bitArray.CopyTo(bytes, 0);
            Assert.AreEqual(0xAA, bytes[0]);

            // 0x55AA
            bitArray = new BitArray(new bool[] { false, true, false, true, false, true, false, true,
                                                 true, false, true, false, true, false, true, false});
            bitArray.CopyTo(bytes, 0);
            Assert.AreEqual(0xAA, bytes[0]);
            Assert.AreEqual(0x55, bytes[1]);
        }

        [Test(Description = "CI码位解析测试。")]
        public void Test11()
        {
            // 假设一组（1个道岔、一个信号机）码位需要22个比特。
            // 道岔四开在第3（索引号为2）个比特。
            // 假设2个道岔，2个信号机，则至少需要22*2 = 44比特，取整即6个字节。

            var bytes = new byte[] { 0x04, 0x00, 0x00, 0x01, 0x00, 0x00, /* 之前是必须的字节 */
                                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

            var bitArray = new BitArray(bytes);

            // 第一个道岔是否四开？
            Assert.IsTrue(bitArray.Get(0 * 22 + 2));

            // 第二个道岔是否四开？
            Assert.IsTrue(bitArray.Get(1 * 22 + 2));
        }
    }
}
