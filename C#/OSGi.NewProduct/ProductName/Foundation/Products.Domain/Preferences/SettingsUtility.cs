/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Net;
using System.Text;

using Acl;
using Acl.Configuration;

namespace Products.Domain.Preferences
{
    /// <summary>
    /// 参数配置实用工具类
    /// </summary>
    public static class SettingsUtility
    {
        /// <summary>
        /// 从指定的配置接口中获取参数值。
        /// </summary>
        /// <param name="settings">配置接口</param>
        /// <param name="key">参数名称</param>
        /// <param name="defaultValue">参数值不符合条件时返回的默认值</param>
        /// <returns>指定参数名称对应的参数值，如果参数值不符合要求，则返回指定的默认值。</returns>
        public static string GetString(IDictionary<string, string> settings, string key, string defaultValue = "")
        {
            Guard.NotNull(settings, "settings");
            Guard.NotNullOrEmpty(key, "key");

            if (!settings.ContainsKey(key))
                return defaultValue;
            return settings[key];
        }

        /// <summary>
        /// 从指定的配置接口中获取参数值。
        /// </summary>
        /// <param name="settings">配置接口</param>
        /// <param name="key">参数名称</param>
        /// <param name="maxValue">允许的最大数值</param>
        /// <param name="minValue">允许的最小数值</param>
        /// <param name="defaultValue">参数值不符合条件时返回的默认值。</param>
        /// <returns>指定参数名称对应的参数值，如果参数值不符合要求，则返回指定的默认值。</returns>
        public static Decimal GetDecimal(IDictionary<string, string> settings, string key,
            Decimal minValue = Decimal.MinValue,
            Decimal maxValue = Decimal.MaxValue,
            Decimal defaultValue = 0)
        {

            var text = GetString(settings, key);

            try
            {
                var result = SettingsParser.ParseDecimal(text);

                if (result >= minValue && result <= maxValue)
                {
                    return result;
                }
                else
                {
                    return defaultValue;
                }
            }
            catch (System.Exception /*ex*/)
            {
                return defaultValue;
            }
        }

        /// <summary>
        /// 从指定的配置接口中获取参数值。
        /// </summary>
        /// <param name="settings">配置接口</param>
        /// <param name="key">参数名称</param>
        /// <param name="defaultValue">参数值不符合条件时返回的默认值</param>
        /// <returns>指定参数名称对应的参数值，如果参数值不符合要求，则返回指定的默认值。</returns>
        public static bool GetBoolean(IDictionary<string, string> settings, string key, bool defaultValue = false)
        {
            var text = GetString(settings, key);
            bool flag;
            if (!bool.TryParse(text, out flag))
                flag = defaultValue;

            return flag;
        }

        /// <summary>
        /// 从指定的配置接口中获取字节数组。
        /// </summary>
        public static byte[] GetByteArray(IDictionary<string, string> settings, string key)
        {
            var text = GetString(settings, key);

            var result = new List<byte>();
            var splitedText = text.Trim().
                Split(new string[] { ";", "；", ",", "，", " ", "\r\n" }, StringSplitOptions.RemoveEmptyEntries);

            foreach (var item in splitedText)
            {
                try
                {
                    var value = SettingsParser.ParseDecimal(item);
                    result.Add(Convert.ToByte(value));
                }
                catch (System.FormatException /*ex*/)
                {
                    throw new Exception(string.Format("无法将字符串'{0}'转化为数值。", item));
                }
            }

            return result.ToArray();
        }

        /// <summary>
        /// 从指定的配置接口中获取IPEndPoint列表。
        /// </summary>
        public static List<IPEndPoint> GetIPEndPoint(IDictionary<string, string> settings, string key)
        {
            var text = GetString(settings, key);


            if (string.IsNullOrWhiteSpace(text)) return null;

            var value = text.Trim().Split(new string[] { ";", "；", ",", "，", "、" }, StringSplitOptions.RemoveEmptyEntries);

            var result = new List<IPEndPoint>();
            foreach (var item in value)
            {
                var ep = SettingsParser.ParseIPEndPoint(item);
                result.Add(ep);
            }

            return result;
        }

        /// <summary>
        /// 从指定的配置接口中获取可接受的客户端列表。
        /// </summary>
        public static Dictionary<uint, List<IPEndPoint>> GetAcceptableClients(IDictionary<string, string> settings, string key)
        {
            var text = GetString(settings, key);

            if (string.IsNullOrWhiteSpace(text)) return null;

            return SettingsParser.ParseAcceptableClients(text);
        }
    }
}
