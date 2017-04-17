using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Security.Cryptography;
using Org.Mentalis.Security.Cryptography;//.SecurityServices.Cryptography;
using System.IO;
using log4net;

namespace ProWrite.UFE
{
    public interface IUFEEncryption
    {
        byte[] Encrpyt(byte[] source);
        byte[] Decrpyt(byte[] source);
    }

    //public class UFEEncryption : IUFEEncryption
    //{
    //    const string strKey = "!QAZ1qaz@WSX2wsx#EDC3edc$RFV4rfv";
    //    static readonly byte[] key = strKey.GetBytesUTF8();
    //    private static readonly ILog log = LogManager.GetLogger(typeof (UFEEncryption));

    //    public UFEEncryption()
    //    {

    //    }

    //    [Conditional("CanEncryption")]
    //    private static void RC4(Byte[] bytes)
    //    {
    //        try
    //        {
    //            Byte[] s = new Byte[256];
    //            Byte[] k = new Byte[256];
    //            Byte temp;
    //            int i, j;

    //            int keyLength = key.Length;
    //            int bytesLength = bytes.Length;

    //            for (i = 0; i < 256; i++)
    //            {
    //                s[i] = (Byte) i;
    //                k[i] = key[i%keyLength];
    //            }

    //            j = 0;
    //            for (i = 0; i < 256; i++)
    //            {
    //                j = (j + s[i] + k[i])%256;
    //                temp = s[i];
    //                s[i] = s[j];
    //                s[j] = temp;
    //            }

    //            i = j = 0;
    //            for (int x = 0; x < bytesLength; x++)
    //            {
    //                i = (i + 1)%256;
    //                j = (j + s[i])%256;
    //                temp = s[i];
    //                s[i] = s[j];
    //                s[j] = temp;
    //                int t = (s[i] + s[j])%256;
    //                bytes[x] ^= s[t];
    //            }
    //        }
    //        catch(Exception ex)
    //        {
    //            log.Error(ex.Message,ex);
    //        }
    //    }

    //    private byte[] Result;

    //    public byte[] Encrpyt(byte[] byteIn)
    //    {
    //        Result = byteIn;
    //        RC4(Result);
    //        return Result;
    //    }

    //    public byte[] Decrpyt(byte[] byteIn)
    //    {
    //        Result = byteIn;
    //        RC4(Result);
    //        return Result;
    //    }

    //}

    public class UFEEncryption : IUFEEncryption
    {
        const string strKey = "!QAZ1qaz@WSX2wsx#EDC3edc$RFV4rfv";
        static readonly List<byte> key = new List<byte>(strKey.GetBytesUTF8());

        public UFEEncryption()
        {

        }

        private byte[] SymmetricEncrpyt(byte[] byteIn)
        {
            var inData = new List<byte>(byteIn);
            return ProWrite.SSL.RC4SymmetricAlgorithm.RC4(key, inData).ToArray();
        }

        /// <summary>
        /// 对称解密
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        private byte[] SymmetricDecrpyt(byte[] byteIn)
        {
            var inData = new List<byte>(byteIn);
            return ProWrite.SSL.RC4SymmetricAlgorithm.RC4(key, inData).ToArray();
        }

        private byte[] Result;

        public byte[] Encrpyt(byte[] byteIn)
        {
            Result = byteIn;
            DoEncrypt();
            return Result;
        }

        public byte[] Decrpyt(byte[] byteIn)
        {
            Result = byteIn;
            DoDecrpty();
            return Result;
        }

        [Conditional("CanEncryption")]
        private void DoEncrypt()
        {
            Result = SymmetricEncrpyt(Result);
        }

        [Conditional("CanEncryption")]
        private void DoDecrpty()
        {
            Result = SymmetricDecrpyt(Result);
        }
    }

}
