/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ�ATS
//
// �� �� �ˣ�heng222_z
// �������ڣ�2018/5/22 15:41:16 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2018 ATS����������Ȩ����
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
