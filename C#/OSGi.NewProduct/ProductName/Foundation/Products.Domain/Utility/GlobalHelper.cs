/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ�ACL
//
// �� �� �ˣ�heng222_z
// �������ڣ�2018/10/17 18:18:08 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2018 ACL����������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;

namespace Products.Domain
{
    /// <summary>
    /// ȫ�ְ����ࡣ
    /// </summary>
    public static class GlobalHelper
    {
        /// <summary>
        /// ��16����������ʽ���ַ���ת��Ϊ�ֽ����顣
        /// </summary>
        /// <param name="text">���磺��A1 C5 12 2C��</param>
        /// <returns>�ַ�����Ӧ���ֽ����顣</returns>
        public static byte[] SplitHexText(string text)
        {
            var result = new List<byte>();
            var splitedText = text.Trim().
                Split(new string[] { ",", "��", " ", "\r\n" }, StringSplitOptions.RemoveEmptyEntries);

            foreach (var item in splitedText)
            {
                try
                {
                    result.Add(Convert.ToByte(item, 16));
                }
                catch (System.FormatException /*ex*/)
                {
                    throw new Exception(string.Format("�޷����ַ���'{0}'ת��Ϊ��ֵ��", item));
                }
            }

            return result.ToArray();
        }

        /// <summary>
        /// ������㡣
        /// </summary>
        public static byte Xor(byte[] bytes, int startIndex, int count)
        {
            var result = 0;
            for (int i = startIndex; i < startIndex + count; i++)
            {
                result ^= bytes[i];
            }

            return Convert.ToByte(result);
        }

        /// <summary>
        /// ���г�ID��˵�IDת��Ϊ��š�
        /// </summary>
        public static uint BuildCode(ushort trainID, ushort terminalID)
        {
            return Convert.ToUInt32((trainID << 16) + terminalID);
        }

        /// <summary>
        /// ����ŷָ�Ϊ�г�ID��˵�ID��
        /// </summary>
        public static Tuple<ushort, ushort> SplitCode(uint code)
        {
            var trainID = Convert.ToUInt16((code >> 16) & 0xFFFF);
            var terminalID = Convert.ToUInt16(code & 0xFFFF);

            return new Tuple<ushort, ushort>(trainID, terminalID);
        }
    }
}
