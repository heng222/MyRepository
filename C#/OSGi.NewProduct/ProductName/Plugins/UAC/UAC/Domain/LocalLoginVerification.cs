/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
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
    /// ���ص�¼��֤
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

        #region "ILoginVerification ����"
        public void LogOn(string userName, byte[] pwdActual)
        {
            if (string.Equals(userName, _currentUser.Name, StringComparison.OrdinalIgnoreCase))
            {
                throw new Exception("�û�����ͬ�������л���");
            }

            // 
            var theUser = _userMgr.GetUser(userName);
            if (theUser == null) throw new Exception("ָ�����û������ڡ�");
            
            if (!HelperTool.BytesEquals(theUser.Password, pwdActual))
                throw new Exception("���벻��ȷ��");

            // �����û���Ҫ�л��¼���
            GlobalMessageBus.PublishUserChanging(new EventArgs());

            // �����û���
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

            // �����û��л��¼���
            GlobalMessageBus.PublishUserChanged(new EventArgs());     
        }

        public void Logoff()
        {
            if (_currentUser.Id == UserInfo.Guest) throw new Exception("�޷�ע��Guest�û���");

            // �����û���Ҫ�л��¼���
            GlobalMessageBus.PublishUserChanging(new EventArgs());

            // �л��û���
            _currentUser.Name = "Guest";
            _currentUser.Id = UserInfo.Guest;
            _currentUser.Privileges.Clear();

            // �����û��л��¼���
            GlobalMessageBus.PublishUserChanged(new EventArgs());
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
