/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-2 10:43:04 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
//
//----------------------------------------------------------------*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using Acl.Log;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Log;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Types;

namespace Products.Domain
{
    /// <summary>
    /// �ڵ������Ĺ�������
    /// �˾�̬������������ؽڵ�����ԣ�ͬ���ڵ�������Լ����и������Ӽ������ԡ�
    /// �����ṩһЩ���õľ�̬������
    /// </summary>
    public static class NodeContextManager
    {
        #region "Filed"

        #endregion

        #region "Construct"
        /// <summary>
        /// ���캯����
        /// </summary>
        static NodeContextManager()
        {
            Current = new DefaultNodeContextImpl();
        }
        #endregion

        #region "Property"
        /// <summary>
        /// ��ȡ��ǰ�ڵ���������Ϣ
        /// </summary>
        public static INodeContext Current { get; set; }

        /// <summary>
        /// ��ȡ���ؽڵ�ID
        /// </summary>
        public static uint LocalNodeCode { get { return Current.Code; } }

        /// <summary>
        /// ��ȡ���ؽڵ�����
        /// </summary>
        public static string LocalNodeName { get { return Current.Name; } }

        /// <summary>
        /// ��ȡ���ؽڵ�����
        /// </summary>
        public static NodeType LocalNodeType { get { return Current.Type; } }

        #endregion

        #region "Public methods"
        /// <summary>
        /// ��ʼ��
        /// </summary>
        public static void Initialize()
        {

        }
        #endregion
    }
}
