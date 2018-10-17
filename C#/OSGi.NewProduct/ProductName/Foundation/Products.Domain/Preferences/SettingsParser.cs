/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ŀ���ƣ�Acl Platform Library
//
// �� �� �ˣ�zhangheng
// �������ڣ�2017-1-6 12:15:38 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
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
    /// �������ݵĽ�������
    /// </summary>
    public static class SettingsParser
    {
        /// <summary>
        /// ��ָ����������ʽ���ַ���ת��Ϊ��Ч����ֵ��
        /// </summary>
        /// <param name="value">������10���ƻ�16���Ƶ��ַ�����16���Ƶ��ַ���ʾ������0X12����0xDA��,"10H"��</param>
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
        /// ��ָ����������ʽ���ַ���ת��Ϊ��Ч����ֵ�б�
        /// </summary>
        /// <param name="value">������10���ƻ�16���Ƶ��ַ�����16���Ƶ��ַ���ʾ������0X12, 10H, 1, 2����</param>
        /// <param name="separaters">�ָ����б�</param>
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
        /// ��ָ����������ʽ���ַ���ת��Ϊ��Ч��Booleanֵ��
        /// </summary>
        /// <param name="value">Boolean���ַ���ʾ���������ִ�Сд��
        /// ���硰true������T����ʾtrue������ֵ��ʾfalse��</param>
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
        /// ��ָ����������ʽ���ַ���ת��Ϊ��Ч���ֵ����
        /// </summary>
        /// <param name="value">���磺"1=>2; 2=>4"��"1,2; 2,4"</param>
        /// <param name="itemSeparaters">��ķָ����б�</param>
        /// <param name="keyValueSeparaters">��ֵ�ķָ����б�</param>
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
                    throw new Exception(string.Format("{0}������Ч�ļ�ֵ�ԡ�", p));
                }

                var keyValue = ParseDecimals(p, keyValueSeparaters);

                result.Add(keyValue[0], keyValue[1]);
            });

            return result;
        }

        /// <summary>
        /// ��ָ����ʽ��IPEndPoint����ΪIPEndPoint����
        /// ʾ����10.0.0.1:3003��10.0.0.1��
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
        /// ��ָ����ʽ��IPEndPoint����ΪIPEndPoint����
        /// ʾ����10.0.0.1:3003�� 10.0.0.1��
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
        /// ��ָ����ʽ��ID��IPEndPoint�ַ�������Ϊ����
        /// ʾ����1,10.0.0.1,10.0.1.1 ����ָ���˿ڣ�
        /// ʾ����1,10.0.0.1:3003,10.0.1.1:3003 ��ָ���˿ڣ�
        /// </summary>
        /// <param name="text"></param>
        /// <returns></returns>
        public static KeyValuePair<uint, List<IPEndPoint>> ParseIdAndEndPoints(string text)
        {
            if (string.IsNullOrWhiteSpace(text)) throw new ArgumentNullException();

            var splitedText = text.Trim().
                Split(new string[] { ",", "��" }, StringSplitOptions.RemoveEmptyEntries);

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
        /// ��ָ����ʽ���ַ�������Ϊ�ɽ��ܵĿͻ��˲�����
        /// ��ʽ���£�
        /// ʾ��1��1;2;3 ��ֻ�޶�ID��
        /// ʾ��2��1,10.0.0.1;2,10.0.0.2;20.0.0.2 ���޶�ID��IP��
        /// ʾ��3��1,10.0.0.1:3003,20.0.0.1:3003 ���޶�ID��IP��˿ڣ�
        /// </summary>
        /// <param name="text"></param>
        /// <returns></returns>
        public static Dictionary<uint, List<IPEndPoint>> ParseAcceptableClients(string text)
        {
            var result = new Dictionary<uint, List<IPEndPoint>>();

            var splitedText = text.Trim().
                Split(new string[] { ";", "��", "\r\n" }, StringSplitOptions.RemoveEmptyEntries);

            foreach (var item in splitedText)
            {
                var client = ParseIdAndEndPoints(item);
                result.Add(client.Key, client.Value);
            }

            return result;
        }

    }
}
