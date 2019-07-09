/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2009，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Products.UAC.Domain
{
    /// <summary>
    /// UAC模块配置类。
    /// </summary>
    public class UacSettings
    {
        #region "Filed"
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数。
        /// </summary>
        public UacSettings(byte[] adminPwd)
        {
            this.AdminPassword = adminPwd;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 管理员密码。
        /// </summary>
        public byte[] AdminPassword { get; set; }
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
