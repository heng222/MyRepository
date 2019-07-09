/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ�ATS
//
// �� �� �ˣ�heng222_z
// �������ڣ�2018/5/22 14:49:57 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2018 ATS����������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Acl.ServiceManagement;

namespace Products.Infrastructure.Specification
{
    /// <summary>
    /// ȫ�ַ���
    /// </summary>
    public static class GlobalServices
    {
        /// <summary>
        /// ��ȡϵͳ���Խӿڡ�
        /// </summary>
        public static ISystemAttribute SysAttribute
        {
            get { return ServiceManager.Current.GetAll<ISystemAttribute>().FirstOrDefault(); }
        }

        /// <summary>
        /// ��ȡ UAC �ӿڡ�
        /// </summary>
        public static IUserAccessControl UAC 
        {
            get { return ServiceManager.Current.GetAll<IUserAccessControl>().FirstOrDefault(); }
        }

        /// <summary>
        /// ��ȡ IRepository �ӿڡ�
        /// </summary>
        public static IRepository Repository
        {
            get { return ServiceManager.Current.GetAll<IRepository>().FirstOrDefault(); }
        }
    }
}
