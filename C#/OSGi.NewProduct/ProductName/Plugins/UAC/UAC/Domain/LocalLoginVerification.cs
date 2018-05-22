/*----------------------------------------------------------------
// 公司名称：公司名称
// 
// 产品名称：ATS
//
// 创 建 人：heng222_z
// 创建日期：2018/5/22 14:20:17 
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
    /// 本地登录验证
    /// </summary>
    class LocalLoginVerification : ILoginVerification
    {
        #region "Filed"
        #endregion

        #region "Constructor"
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

        #region "ILoginVerification 方法"
        public void LogOn(string userName, byte[] pwdMd5)
        {
            throw new NotImplementedException();
        }

        public void Logoff(string userName)
        {
            throw new NotImplementedException();
        }
        #endregion
    }
}
