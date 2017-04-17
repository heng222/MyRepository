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
            var bytes = new byte[] { 0xAA };

            var bitArray = new BitArray(bytes);


            Assert.IsFalse(bitArray.Get(0));
            Assert.IsTrue(bitArray.Get(1));
            Assert.IsFalse(bitArray.Get(2));
            Assert.IsTrue(bitArray.Get(3));

            Assert.IsFalse(bitArray.Get(4));
            Assert.IsTrue(bitArray.Get(5));
            Assert.IsFalse(bitArray.Get(6));
            Assert.IsTrue(bitArray.Get(7));
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
    }
}
