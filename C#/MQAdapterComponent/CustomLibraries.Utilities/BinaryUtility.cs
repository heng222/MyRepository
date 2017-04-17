using System;
using System.Xml;
using System.Text;
using System.Collections.Generic;

namespace CustomLibraries.Utilities
{
    public class BinaryUtility
    {
        public static string ConvertToHexaDecimal(Byte[] stream)
        {
            System.Text.StringBuilder encryptedSB = new System.Text.StringBuilder();
            XmlTextWriter writer = new XmlTextWriter(new System.IO.StringWriter(encryptedSB));
            writer.WriteBinHex(stream, 0, stream.Length);
            writer.Close();

            return encryptedSB.ToString();
        }
    }
}
