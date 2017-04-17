using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using ProWrite.SSL;
using System.Runtime.InteropServices;
namespace ProWrite.UFE.Test
{
    [TestFixture]
    public class UFEEncryptionTest
    {
        const string strKey = "!QAZ1qaz@WSX2wsx#EDC3edc$RFV4rfv";
        static readonly byte[] key = strKey.GetBytesUTF8();

        [Test]
        public void Test()
        {
            string expected = "how are you";
            List<byte> expectedBytes = new List<byte>(expected.GetBytesUTF8());

            var actualBytes = RC4SymmetricAlgorithm.RC4(new List<byte>(key), expectedBytes);
            Console.WriteLine(actualBytes.ToArray().GetStringUTF8());
            Assert.AreEqual(expectedBytes, RC4SymmetricAlgorithm.RC4(new List<byte>(key), actualBytes));
        }

        [Test]
        public void Test2()
        {
            var encry = new UFEEncryption();
            string expected = "how are you";
            byte[] expectedBytes = expected.GetBytesUTF8();

            byte[] actualBytes = encry.Encrpyt(expectedBytes);
            Console.WriteLine(actualBytes.GetStringUTF8());
            Assert.AreEqual(expectedBytes, encry.Decrpyt(actualBytes));
        }


        
    }
}
