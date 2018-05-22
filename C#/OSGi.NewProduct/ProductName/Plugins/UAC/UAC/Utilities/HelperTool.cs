using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Products.UAC.Utilities
{
    static class HelperTool
    {
        public static bool BytesEquals(byte[] byteArray1, byte[] byteArray2)
        {
            if (byteArray1.Length != byteArray2.Length) return false;

            for (int i = 0; i < byteArray1.Length; i++)
            {
                if (byteArray1[i] != byteArray2[i]) return false;
            }
                
            return true;
        }

        public static byte[] BuildMd5(string text)
        {
            using (var md5 = System.Security.Cryptography.MD5.Create())
            {
                var pwdBytes = Encoding.ASCII.GetBytes(text);
                var actualPwd = md5.ComputeHash(pwdBytes);

                //Console.WriteLine(string.Join(" ", actualPwd.Select(p => string.Format("{0:X2}", p))));
                return actualPwd;
            }
        }
    }
}
