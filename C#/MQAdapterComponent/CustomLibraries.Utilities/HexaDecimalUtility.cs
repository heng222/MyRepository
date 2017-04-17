using System;
using System.Text;
using System.Collections.Generic;

namespace CustomLibraries.Utilities
{
    public class HexaDecimalUtility
    {
        public static Byte[] ConvertToBinary(string newString)
        {
            int byteLength = newString.Length / 2;
            byte[] bytes = new byte[byteLength];
            string hex;
            int j = 0;
            for (int i = 0; i < bytes.Length; i++)
            {
                hex = new String(new Char[] {newString[j],
												newString[j+1]});
                bytes[i] = byte.Parse(hex,
                    System.Globalization.NumberStyles.HexNumber);
                j = j + 2;
            }
            return bytes;
        }

    }
}
