/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ�ATS
//
// �� �� �ˣ�heng222_z
// �������ڣ�2018/10/26 13:06:27 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2018 ATS����������Ȩ����
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
    /// һ�������࣬������Ϣǩ����֤��
    /// </summary>
    public static class AuthenticationHelper
    {
        /// <summary>
        /// �������������MD5ֵ��
        /// </summary>
        /// <param name="plaintextPwd">ָ�����������롣</param>
        /// <returns>���������Ӧ��MD5ֵ��</returns>
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
        /// �������������õ�MD5ֵ��
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
