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
            int len1 = byteArray1 == null ? 0 : byteArray1.Length;
            int len2 = byteArray2 == null ? 0 : byteArray2.Length;

            if (len1 == len2 && len2 == 0) return true;

            if (len1 != len2) return false;

            for (int i = 0; i < byteArray1.Length; i++)
            {
                if (byteArray1[i] != byteArray2[i]) return false;
            }

            return true;
        }

        public static byte[] BuildMd5(string text)
        {
            if (string.IsNullOrEmpty(text)) return null;

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
