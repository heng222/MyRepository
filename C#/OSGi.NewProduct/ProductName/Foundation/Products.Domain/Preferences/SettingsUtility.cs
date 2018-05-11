/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-27 10:38:06 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
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
        public static string GetString(ISettings settings, string key, string defaultValue = "")
        {
            try
            {
                return settings.Get<string>(key, defaultValue);
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
        /// <param name="maxValue">����������ֵ</param>
        /// <param name="minValue">�������С��ֵ</param>
        /// <param name="defaultValue">����ֵ����������ʱ���ص�Ĭ��ֵ��</param>
        /// <returns>ָ���������ƶ�Ӧ�Ĳ���ֵ���������ֵ������Ҫ���򷵻�ָ����Ĭ��ֵ��</returns>
        public static Decimal GetDecimal(ISettings settings, string key, 
            Decimal minValue = Decimal.MinValue, 
            Decimal maxValue = Decimal.MaxValue, 
            Decimal defaultValue = 0)
        {
            if (string.IsNullOrEmpty(key)) throw new ArgumentException();

            try
            {
                var text = settings.Get<string>(key);

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
        public static bool GetBoolean(ISettings settings, string key, bool defaultValue = false)
        {
            if (string.IsNullOrEmpty(key)) throw new ArgumentException();

            try
            {
                return settings.Get<bool>(key, defaultValue);
            }
            catch (System.Exception /*ex*/)
            {
                return defaultValue;
            }
        }

        /// <summary>
        /// ��ָ�������ýӿ��л�ȡ�ֽ����顣
        /// </summary>
        public static byte[] GetByteArray(ISettings settings, string key)
        {
            if (string.IsNullOrEmpty(key)) throw new ArgumentException();

            var text = settings.Get<string>(key);

            var result = new List<byte>();
            var splitedText = text.Trim().
                Split(new string[] {";", "��", ",", "��", " ", "\r\n" }, StringSplitOptions.RemoveEmptyEntries);

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
        public static List<IPEndPoint> GetIPEndPoint(ISettings settings, string key)
        {
            if (string.IsNullOrEmpty(key)) throw new ArgumentException();

            var text = settings.Get<string>(key);

            if (string.IsNullOrWhiteSpace(text)) return null;

            var value = text.Trim().Split(new string[] { ";", "��", ",", "��" }, StringSplitOptions.RemoveEmptyEntries);

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
        public static Dictionary<uint, List<IPEndPoint>> GetAcceptableClients(ISettings settings, string key)
        {
            if (string.IsNullOrEmpty(key)) throw new ArgumentException();

            var text = settings.Get<string>(key);

            if (string.IsNullOrWhiteSpace(text)) return null;

            return SettingsParser.ParseAcceptableClients(text);
        }
    }
}
