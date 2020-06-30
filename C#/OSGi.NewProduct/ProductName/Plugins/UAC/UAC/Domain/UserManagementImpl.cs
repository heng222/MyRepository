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
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Products.Domain;
using Products.Infrastructure;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Specification;
using Products.UAC.Utilities;

namespace Products.UAC.Domain
{
    /// <summary>
    /// �û�����ӿ�ʵ�֡�
    /// </summary>
    class UserManagementImpl : IUserManagement
    {
        #region "Field"
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

        #region "IUserManagement �ӿ�"
        public User GetUser(string name)
        {
            return GlobalServices.Repository.Where<User>()
                .Where(p => string.Equals(p.Name, name, StringComparison.OrdinalIgnoreCase))
                .FirstOrDefault();
        }

        public void ModifyPassword(string userName, string oldPassword, string newPassword)
        {
            if (string.IsNullOrWhiteSpace(userName)) throw new Exception("�û����Ƿ���");

            // �������Ƿ�Ϸ���

            // �������Ƿ���ȷ��
            var theUser = this.GetUser(userName);
            if (theUser == null) throw new Exception("�û������ڡ�");

            var oldPwdMd5 = HelperTool.BuildMd5(oldPassword);
            if (!HelperTool.BytesEquals(oldPwdMd5, theUser.Password))
            {
                throw new Exception("�����벻��ȷ��");
            }

            // �������롣
            var newPwdMd5 = HelperTool.BuildMd5(newPassword);
            GlobalServices.Repository.Update<User>(new { Password = newPwdMd5 }, p => p.Code == theUser.Code);
        }
        #endregion
    }
}
