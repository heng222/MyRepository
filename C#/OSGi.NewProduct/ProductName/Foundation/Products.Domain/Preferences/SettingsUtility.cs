/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
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
    /// ��������ʵ�ù�����
    /// </summary>
    public static class SettingsUtility
    {
        /// <summary>
        /// ��ָ�������ýӿ��л�ȡ����ֵ��
        /// </summary>
        /// <param name="settings">���ýӿ�</param>
        /// <param name="key">��������</param>
        /// <param name="defaultValue">����ֵ����������ʱ���ص�Ĭ��ֵ</param>
        /// <returns>ָ���������ƶ�Ӧ�Ĳ���ֵ���������ֵ������Ҫ���򷵻�ָ����Ĭ��ֵ��</returns>
        public static string GetString(IDictionary<string, string> settings, string key, string defaultValue = "")
        {
            Guard.NotNull(settings, "settings");
            Guard.NotNullOrEmpty(key, "key");

            if (!settings.ContainsKey(key))
                return defaultValue;
            return settings[key];
        }

        /// <summary>
        /// ��ָ�������ýӿ��л�ȡ����ֵ��
        /// </summary>
        /// <param name="settings">���ýӿ�</param>
        /// <param name="key">��������</param>
        /// <param name="maxValue">����������ֵ</param>
        /// <param name="minValue">�������С��ֵ</param>
        /// <param name="defaultValue">����ֵ����������ʱ���ص�Ĭ��ֵ��</param>
        /// <returns>ָ���������ƶ�Ӧ�Ĳ���ֵ���������ֵ������Ҫ���򷵻�ָ����Ĭ��ֵ��</returns>
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
        /// ��ָ�������ýӿ��л�ȡ����ֵ��
        /// </summary>
        /// <param name="settings">���ýӿ�</param>
        /// <param name="key">��������</param>
        /// <param name="defaultValue">����ֵ����������ʱ���ص�Ĭ��ֵ</param>
        /// <returns>ָ���������ƶ�Ӧ�Ĳ���ֵ���������ֵ������Ҫ���򷵻�ָ����Ĭ��ֵ��</returns>
        public static bool GetBoolean(IDictionary<string, string> settings, string key, bool defaultValue = false)
        {
            var text = GetString(settings, key);
            bool flag;
            if (!bool.TryParse(text, out flag))
                flag = defaultValue;

            return flag;
        }

        /// <summary>
        /// ��ָ�������ýӿ��л�ȡ�ֽ����顣
        /// </summary>
        public static byte[] GetByteArray(IDictionary<string, string> settings, string key)
        {
            var text = GetString(settings, key);

            var result = new List<byte>();
            var splitedText = text.Trim().
                Split(new string[] { ";", "��", ",", "��", " ", "\r\n" }, StringSplitOptions.RemoveEmptyEntries);

            foreach (var item in splitedText)
            {
                try
                {
                    var value = SettingsParser.ParseDecimal(item);
                    result.Add(Convert.ToByte(value));
                }
                catch (System.FormatException /*ex*/)
                {
                    throw new Exception(string.Format("�޷����ַ���'{0}'ת��Ϊ��ֵ��", item));
                }
            }

            return result.ToArray();
        }

        /// <summary>
        /// ��ָ�������ýӿ��л�ȡIPEndPoint�б�
        /// </summary>
        public static List<IPEndPoint> GetIPEndPoint(IDictionary<string, string> settings, string key)
        {
            var text = GetString(settings, key);


            if (string.IsNullOrWhiteSpace(text)) return null;

            var value = text.Trim().Split(new string[] { ";", "��", ",", "��", "��" }, StringSplitOptions.RemoveEmptyEntries);

            var result = new List<IPEndPoint>();
            foreach (var item in value)
            {
                var ep = SettingsParser.ParseIPEndPoint(item);
                result.Add(ep);
            }

            return result;
        }

        /// <summary>
        /// ��ָ�������ýӿ��л�ȡ�ɽ��ܵĿͻ����б�
        /// </summary>
        public static Dictionary<uint, List<IPEndPoint>> GetAcceptableClients(IDictionary<string, string> settings, string key)
        {
            var text = GetString(settings, key);

            if (string.IsNullOrWhiteSpace(text)) return null;

            return SettingsParser.ParseAcceptableClients(text);
        }
    }
}
