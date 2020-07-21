/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Linq;

using Products.Infrastructure;
using Products.Infrastructure.Messages;
using Products.Infrastructure.Specification;
using Products.UAC.Utilities;

namespace Products.UAC.Domain
{
    /// <summary>
    /// 本地登录验证
    /// </summary>
    class LocalLoginVerification : ILoginVerification, IUserAccessControl
    {
        #region "Field"
        private readonly IUserManagement _userMgr;
        private readonly UserInfo _currentUser = new UserInfo();
        #endregion

        #region "Constructor"
        public LocalLoginVerification(UacSettings settings, IUserManagement usrMgr)
        {
            this.Settings = settings;
            _userMgr = usrMgr;
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
        public void LogOn(string userName, byte[] pwdActual)
        {
            if (string.Equals(userName, _currentUser.Name, StringComparison.OrdinalIgnoreCase))
            {
                throw new Exception("用户名相同，无需切换。");
            }

            // 
            var theUser = _userMgr.GetUser(userName);
            if (theUser == null) throw new Exception("指定的用户不存在。");
            
            if (!HelperTool.BytesEquals(theUser.Password, pwdActual))
                throw new Exception("密码不正确。");

            // 发布用户将要切换事件。
            GlobalMessageBus.PublishUserChanging(new EventArgs());

            // 更新用户。
            _currentUser.Id = theUser.Code;
            _currentUser.Name = theUser.Name;
            if (theUser.Privileges != null)
            {
                _currentUser.Privileges = theUser.Privileges.ToList();
            }
            else
            {
                _currentUser.Privileges.Clear();
            }

            // 发布用户切换事件。
            GlobalMessageBus.PublishUserChanged(new EventArgs());     
        }

        public void Logoff()
        {
            if (_currentUser.Id == UserInfo.Guest) throw new Exception("无法注销Guest用户。");

            // 发布用户将要切换事件。
            GlobalMessageBus.PublishUserChanging(new EventArgs());

            // 切换用户。
            _currentUser.Name = "Guest";
            _currentUser.Id = UserInfo.Guest;
            _currentUser.Privileges.Clear();

            // 发布用户切换事件。
            GlobalMessageBus.PublishUserChanged(new EventArgs());
        }
        #endregion

        #region "IUserAccessControl 方法"
        public uint CurrentUserCode { get { return _currentUser.Id; } }

        public string CurrentUserName { get { return _currentUser.Name; } }

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
