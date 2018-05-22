/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ�ATS
//
// �� �� �ˣ�heng222_z
// �������ڣ�2018/5/22 14:20:17 
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
using Products.Infrastructure.DTO;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Types;
using Products.UAC.Utilities;

namespace Products.UAC.Domain
{
    /// <summary>
    /// ���ص�¼��֤
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

        #region "ILoginVerification ����"
        public void LogOn(string userName, byte[] pwdMd5)
        {
            if (!userName.Equals("admin", StringComparison.OrdinalIgnoreCase))
                throw new Exception("ָ�����û������ڡ�");

            if (!HelperTool.BytesEquals(this.Settings.AdminPassword, pwdMd5))
                throw new Exception("���벻��ȷ��");

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

        #region "IUserAccessControl ����"
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
