/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Products.UAC.Domain
{
    /// <summary>
    /// UACģ�������ࡣ
    /// </summary>
    public class UacSettings
    {
        #region "Filed"
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯����
        /// </summary>
        public UacSettings(byte[] adminPwd)
        {
            this.AdminPassword = adminPwd;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ����Ա���롣
        /// </summary>
        public byte[] AdminPassword { get; set; }
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
