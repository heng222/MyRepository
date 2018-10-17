/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 项目名称：Acl Platform Library
//
// 创 建 人：zhangheng
// 创建日期：2017-1-6 12:15:38 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;

namespace Products.Domain.Preferences
{
    /// <summary>
    /// 配置数据的解析器。
    /// </summary>
    public static class SettingsParser
    {
        /// <summary>
        /// 将指定的数据形式的字符串转化为等效的数值。
        /// </summary>
        /// <param name="value">可以是10进制或16进制的字符串。16进制的字符串示例：“0X12”“0xDA”,"10H"。</param>
        /// <returns></returns>
        public static Decimal ParseDecimal(string value)
        {
            if (value.Contains("0x") || value.Contains("0X")
                || value.Contains('H') || value.Contains('h')
                || value.Contains('a') || value.Contains('A')
                || value.Contains('b') || value.Contains('B')
                || value.Contains('c') || value.Contains('C')
                || value.Contains('d') || value.Contains('D')
                || value.Contains('e') || value.Contains('E')
                || value.Contains('f') || value.Contains('F'))
            {
                return Convert.ToUInt64(value.Trim(), 16);
            }
            else
            {
                return Convert.ToDecimal(value.Trim());
            }
        }

        /// <summary>
        /// 将指定的数据形式的字符串转化为等效的数值列表。
        /// </summary>
        /// <param name="value">可以是10进制或16进制的字符串。16进制的字符串示例：“0X12, 10H, 1, 2”。</param>
        /// <param name="separaters">分隔符列表</param>
        /// <returns></returns>
        public static List<Decimal> ParseDecimals(string value, string[] separaters)
        {
            var result = new List<Decimal>();

            var stringSplited = value.Split(separaters, StringSplitOptions.RemoveEmptyEntries).ToList();

            stringSplited.ForEach(p =>
            {
                result.Add(ParseDecimal(p));
            });

            return result;
        }

        /// <summary>
        /// 将指定的数据形式的字符串转化为等效的Boolean值。
        /// </summary>
        /// <param name="value">Boolean的字符串示例，不区分大小写。
        /// 例如“true”、“T”表示true，其它值表示false。</param>
        /// <returns></returns>
        public static Boolean ParseBoolean(string value)
        {
            if (string.Compare(value, "T", true) == 0
                || string.Compare(value, "true", true) == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /// <summary>
        /// 将指定的数据形式的字符串转化为等效的字典对象。
        /// </summary>
        /// <param name="value">例如："1=>2; 2=>4"、"1,2; 2,4"</param>
        /// <param name="itemSeparaters">项的分隔符列表</param>
        /// <param name="keyValueSeparaters">键值的分隔符列表</param>
        /// <returns></returns>
        public static Dictionary<Decimal, Decimal> ParseDictionary(string value, string[] itemSeparaters, string[] keyValueSeparaters)
        {
            var result = new Dictionary<Decimal, Decimal>();

            var itemsSplitedString = value.Split(itemSeparaters, StringSplitOptions.RemoveEmptyEntries).ToList();
            itemsSplitedString.ForEach(p =>
            {
                var keyValueSplited = p.Split(keyValueSeparaters, StringSplitOptions.RemoveEmptyEntries).ToList();
                if (keyValueSplited.Count() != 2)
                {
                    throw new Exception(string.Format("{0}不是有效的键值对。", p));
                }

                var keyValue = ParseDecimals(p, keyValueSeparaters);

                result.Add(keyValue[0], keyValue[1]);
            });

            return result;
        }

        /// <summary>
        /// 将指定格式的IPEndPoint解析为IPEndPoint对象。
        /// 示例：10.0.0.1:3003、10.0.0.1。
        /// </summary>
        /// <param name="text"></param>
        /// <returns></returns>
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
        /// 将指定格式的IPEndPoint解析为IPEndPoint对象。
        /// 示例：10.0.0.1:3003， 10.0.0.1。
        /// </summary>
        /// <returns></returns>
        public static List<IPEndPoint> ParseIPEndPoints(string text, string[] separaters)
        {
            if (string.IsNullOrWhiteSpace(text)) return new List<IPEndPoint>();

            var result = new List<IPEndPoint>();

            var splitedText = text.Trim().Split(separaters, StringSplitOptions.RemoveEmptyEntries).ToList();

            splitedText.ForEach(p =>
            {
                result.Add(ParseIPEndPoint(p));
            });

            return result;
        }

        /// <summary>
        /// 将指定格式的ID与IPEndPoint字符串解析为对象。
        /// 示例：1,10.0.0.1,10.0.1.1 （不指定端口）
        /// 示例：1,10.0.0.1:3003,10.0.1.1:3003 （指定端口）
        /// </summary>
        /// <param name="text"></param>
        /// <returns></returns>
        public static KeyValuePair<uint, List<IPEndPoint>> ParseIdAndEndPoints(string text)
        {
            if (string.IsNullOrWhiteSpace(text)) throw new ArgumentNullException();

            var splitedText = text.Trim().
                Split(new string[] { ",", "，" }, StringSplitOptions.RemoveEmptyEntries);

            var id = uint.Parse(splitedText[0]);

            var eps = new List<IPEndPoint>();
            for (int i = 1; i < splitedText.Length; i++)
            {
                var value = ParseIPEndPoint(splitedText[i]);
                eps.Add(value);
            }

            return new KeyValuePair<uint, List<IPEndPoint>>(id, eps);
        }

        /// <summary>
        /// 将指定格式的字符串解析为可接受的客户端参数。
        /// 格式如下：
        /// 示例1：1;2;3 （只限定ID）
        /// 示例2：1,10.0.0.1;2,10.0.0.2;20.0.0.2 （限定ID与IP）
        /// 示例3：1,10.0.0.1:3003,20.0.0.1:3003 （限定ID、IP与端口）
        /// </summary>
        /// <param name="text"></param>
        /// <returns></returns>
        public static Dictionary<uint, List<IPEndPoint>> ParseAcceptableClients(string text)
        {
            var result = new Dictionary<uint, List<IPEndPoint>>();

            var splitedText = text.Trim().
                Split(new string[] { ";", "；", "\r\n" }, StringSplitOptions.RemoveEmptyEntries);

            foreach (var item in splitedText)
            {
                var client = ParseIdAndEndPoints(item);
                result.Add(client.Key, client.Value);
            }

            return result;
        }

    }
}
