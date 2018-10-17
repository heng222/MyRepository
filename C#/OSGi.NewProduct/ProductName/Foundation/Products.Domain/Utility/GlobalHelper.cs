/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：ACL
//
// 创 建 人：heng222_z
// 创建日期：2018/10/17 18:18:08 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2018 ACL，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Products.Domain.Utility
{
    /// <summary>
    /// 全局帮助类。
    /// </summary>
    public static class GlobalHelper
    {
        /// <summary>
        /// 将16进制数组形式的字符串转换为字节数组。
        /// </summary>
        /// <param name="text">例如：“A1 C5 12 2C”</param>
        /// <returns>字符串对应的字节数组。</returns>
        public static byte[] SplitHexText(string text)
        {
            var result = new List<byte>();
            var splitedText = text.Trim().
                Split(new string[] { ",", "，", " ", "\r\n" }, StringSplitOptions.RemoveEmptyEntries);

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

    }
}
