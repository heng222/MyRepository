/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：ATS
//
// 创 建 人：heng222_z
// 创建日期：2018/5/22 15:41:16 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 2018 ATS，保留所有权利。
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
