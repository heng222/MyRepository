using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Reflection;

namespace ZlgCanDemo
{
    class HelperTools
    {
        public static List<IPAddress> LocalIpAddress
        {
            get
            {
                var ipHostInfo = Dns.GetHostEntry(Dns.GetHostName());
                var result = new List<IPAddress>();

                IPAddress temp;
                string ip;
                for (int i = 0; i < ipHostInfo.AddressList.Length; i++)
                {
                    ip = ipHostInfo.AddressList[i].ToString();
                    if (IPAddress.TryParse(ip, out temp))
                    {
                        result.Add(temp);
                    }
                }

                return result.OrderBy(p=>p.AddressFamily).ToList();
            }
        }

        /// <summary>
        /// 将指定的数据形式的字符串转化为等效的数值。
        /// </summary>
        /// <param name="value">可以是10进制或16进制的字符串。16进制的字符串示例：“0X12”“0xDA”,"10H"。</param>
        /// <returns></returns>
        public static Decimal ParseDecimal(string value)
        {
            if (value.Contains("0x") || value.Contains("0X")
                || value.Contains("H") || value.Contains("h"))
            {
                return Convert.ToUInt64(value.Trim(), 16);
            }
            else
            {
                return Convert.ToDecimal(value.Trim());
            }
        }

        public static byte[] SplitHexText(string text)
        {
            var result = new List<byte>();
            var splitedText = text.Trim().
                Split(new string[] { "," , "，", " ", "\r\n" }, StringSplitOptions.RemoveEmptyEntries);

            foreach (var item in splitedText)
            {
                try
                {
                    result.Add(Convert.ToByte(item, 16));
                }
                catch (System.FormatException /*ex*/)
                {
                    throw new Exception(string.Format("无法将字符串'{0}'转化为数值。", item));
                }
            }

            return result.ToArray();
        }


        public static IPEndPoint ParseIPEndPoint(string text)
        {
            if (string.IsNullOrWhiteSpace(text)) return null;

            var splitedText = text.Trim().
                Split(new string[] { ":" }, StringSplitOptions.RemoveEmptyEntries);
            
            var ip = IPAddress.Parse(splitedText[0]);
            int port = 0;
            if (splitedText.Length > 1)
            {
                port = int.Parse(splitedText[1]);
            }

            return new IPEndPoint(ip, port);
        }


        /// <summary>
        /// 添加自定义目录到.NET程序探测路径中
        /// </summary>
        public static void AppendCustomPrivatePath()
        {
            // VC运行时目录（“\x86”或“\x64”）
            string privatePath = string.Format(@"x86");
            if (Environment.Is64BitOperatingSystem)
            {
                privatePath = string.Format(@"x64");
            }

            AppendPrivatePath(privatePath);
        }

        /// <summary>
        /// AppendPrivatePath
        /// </summary>
        private static void AppendPrivatePath(string appendPath)
        {
            string privatePath = AppDomain.CurrentDomain.SetupInformation.PrivateBinPath + ";" + appendPath;

            AppDomain.CurrentDomain.SetData("PRIVATE_BINPATH", privatePath);
            AppDomain.CurrentDomain.SetData("BINPATH_PROBE_ONLY", privatePath);
            var m = typeof(AppDomainSetup).GetMethod("UpdateContextProperty", BindingFlags.NonPublic | BindingFlags.Static);
            var funsion = typeof(AppDomain).GetMethod("GetFusionContext", BindingFlags.NonPublic | BindingFlags.Instance);
            m.Invoke(null, new object[] { funsion.Invoke(AppDomain.CurrentDomain, null), "PRIVATE_BINPATH", privatePath });
        }

    }
}
