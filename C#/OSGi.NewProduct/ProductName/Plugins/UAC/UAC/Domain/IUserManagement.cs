/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Products.Infrastructure.Entities;

namespace Products.UAC.Domain
{
    /// <summary>
    /// �û�����ӿڡ�
    /// </summary>
    interface IUserManagement
    {
        /// <summary>
        /// �����û�����ѯ�û���¼��
        /// </summary>
        User GetUser(string name);

        /// <summary>
        /// �޸����롣
        /// </summary>
        void ModifyPassword(string userName, string oldPassword, string newPassword);
    }
}
