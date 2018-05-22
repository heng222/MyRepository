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
using Products.Infrastructure;
using Products.Infrastructure.Messages;
using Products.Infrastructure.Specification;
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

            // �����û���Ҫ�л��¼���
            GlobalMessageBuses.PublishUserChanging(new EventArgs());

            // �л��û���
            _currentUser.Id = UserInfo.Administrator;
            _currentUser.Name = userName;
            _currentUser.Privileges.Clear();
            _currentUser.Privileges.Add(SystemPrivilege.All);

            // �����û��л��¼���
            GlobalMessageBuses.PublishUserChanged(new EventArgs());       
        }

        public void Logoff()
        {
            // �����û���Ҫ�л��¼���
            GlobalMessageBuses.PublishUserChanging(new EventArgs());

            // �л��û���
            _currentUser.Id = UserInfo.Guest;
            _currentUser.Name = "Guest";
            _currentUser.Privileges.Clear();

            // �����û��л��¼���
            GlobalMessageBuses.PublishUserChanged(new EventArgs());       
        }
        #endregion

        #region "IUserAccessControl ����"
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
