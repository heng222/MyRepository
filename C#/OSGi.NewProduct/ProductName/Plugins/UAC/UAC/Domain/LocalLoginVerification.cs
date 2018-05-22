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
using System.Security.Cryptography;
using System.Text;
using Products.Infrastructure;
using Products.Infrastructure.DTO;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Types;
using Products.UAC.Utilities;

namespace Products.UAC.Domain
{
    /// <summary>
    /// 本地登录验证
    /// </summary>
    class LocalLoginVerification : ILoginVerification, IUserAccessControl
    {
        #region "Filed"
        private UserInfo _currentUser = new UserInfo();
        #endregion

        #region "Constructor"
        public LocalLoginVerification(UacSettings settings)
        {
            this.Settings = settings;
        }
        #endregion

        #region "Properties"
        public UacSettings Settings { get; private set; }
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
            if (!userName.Equals("admin", StringComparison.OrdinalIgnoreCase))
                throw new Exception("指定的用户不存在。");

            if (!HelperTool.BytesEquals(this.Settings.AdminPassword, pwdMd5))
                throw new Exception("密码不正确。");

            _currentUser.Name = userName;
            _currentUser.Privileges.Clear();
            _currentUser.Privileges.Add(SystemPrivilege.All);            
        }

        public void Logoff()
        {
            _currentUser.Name = "Guest";
            _currentUser.Id = UserInfo.Guest;
            _currentUser.Privileges.Clear();
        }
        #endregion

        #region "IUserAccessControl 方法"
        public string CurrentUserName
        {
            get { return _currentUser.Name; }
        }

        public bool Contains(SystemPrivilege privilege)
        {
            if (_currentUser.Privileges.Contains(SystemPrivilege.All))
            {
                return true;
            }

            return _currentUser.Privileges.Contains(privilege);
        }
        #endregion
    }
}
