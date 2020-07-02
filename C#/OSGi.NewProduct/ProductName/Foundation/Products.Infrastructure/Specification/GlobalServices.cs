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
        public static ISystemProperty SysAttribute
        {
            get { return ServiceManager.Current.Get<ISystemProperty>(); }
        }

        /// <summary>
        /// ��ȡ/����DBConfig�ṩ���ӿڡ�
        /// </summary>
        public static IDbConfigurationProvider DbConfigProvider
        {
            get { return ServiceManager.Current.Get<IDbConfigurationProvider>(); }
        }

        /// <summary>
        /// ��ȡ IRepository �ӿڡ�
        /// </summary>
        public static IRepository Repository
        {
            get { return ServiceManager.Current.Get<IRepository>(); }
        }

        /// <summary>
        /// ��ȡ/���ýڵ������Ľӿڡ�
        /// </summary>
        public static INodeContext NodeContext { get; set; }

        /// <summary>
        /// ��ȡ UAC �ӿڡ�
        /// </summary>
        public static IUserAccessControl UAC
        {
            get { return ServiceManager.Current.Get<IUserAccessControl>(); }
        }

        /// <summary>
        /// ��ȡ ϵͳ�¼����� �ӿ�
        /// </summary>
        public static ISystemEventManage SEM
        {
            get { return ServiceManager.Current.Get<ISystemEventManage>(); }
        }
    }
}
