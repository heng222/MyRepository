/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ŀ���ƣ���SIL2��֤�ı�׼��ATS
//
// �� �� �ˣ�zhangheng
// �������ڣ�2018-8-1 13:33:34 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Types;
using Products.Infrastructure.Log;
using Acl.Log;
using Products.Infrastructure.Specification;

namespace Products.Domain
{
    /// <summary>
    /// ATS�ڵ����ù����ࡣ
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
        public static uint LocalNodeCode
        {
            get { return Current.Code; }
        }
        /// <summary>
        /// ��ȡ���ؽڵ�����
        /// </summary>
        public static string LocalNodeName
        {
            get { return Current.Name; }
        }
        /// <summary>
        /// ��ȡ���ؽڵ�����
        /// </summary>
        public static NodeType LocalNodeType
        {
            get { return Current.Type; }
        }

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
