/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：ATS
//
// 创 建 人：heng222_z
// 创建日期：2018/10/26 13:06:27 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2018 ATS，保留所有权利。
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using Products.Infrastructure;
using Products.Infrastructure.Entities;

namespace Products.Domain.Utility
{
    /// <summary>
    /// 一个帮助类，用于消息签名验证。
    /// </summary>
    public static class AuthenticationHelper
    {
        /// <summary>
        /// 计算明文密码的MD5值。
        /// </summary>
        /// <param name="plaintextPwd">指定的明文密码。</param>
        /// <returns>明文密码对应的MD5值。</returns>
        public static byte[] CalculatePasswordMD5(string plaintextPwd)
        {
            if (plaintextPwd == null) throw new ArgumentNullException();

            using (var md5 = MD5.Create())
            {
                byte[] pwdBytes = Encoding.Unicode.GetBytes(plaintextPwd);

                return md5.ComputeHash(pwdBytes);
            }
        }

        /// <summary>
        /// 计算插件加载配置的MD5值。
        /// </summary>
        /// <param name="cfg"></param>
        /// <returns></returns>
        public static byte[] CalculatePluginConfigMD5(PluginLoadingConfig cfg)
        {
            using (var md5 = System.Security.Cryptography.MD5.Create())
            {
                var inputString = string.Format("{0}-{1}-{2}-{3}", cfg.NodeCode,
                    (int)cfg.NodeType, cfg.Plugins, cfg.Controls);

                byte[] inputBytes = System.Text.Encoding.Unicode.GetBytes(inputString);

                return md5.ComputeHash(inputBytes);
            }
        }
    }
}
