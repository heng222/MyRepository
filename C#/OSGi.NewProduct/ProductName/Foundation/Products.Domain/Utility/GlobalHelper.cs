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
using System.Linq;
using System.Text;

namespace Products.Domain.Utility
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

    }
}
