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
using System.Management;
using System.Net;
using System.Security.Cryptography;
using System.Text;
using Acl.Log;
using Acl.Utility;
using Products.Infrastructure.Log;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Types;

namespace Products.Domain
{
    /// <summary>
    /// �ڵ���������Ϣ��
    /// </summary>
    public class NodeContextImpl : INodeContext
    {
        #region "Filed"
        private List<PresentationControlType> _controlTypes = new List<PresentationControlType>();
        #endregion

        #region "Property"
        /// <summary>
        /// ��ȡ���ؽڵ�ID��
        /// </summary>
        public uint Code { get; private set; }
        /// <summary>
        /// ��ȡ���ؽڵ����ơ�
        /// </summary>
        public string Name { get; private set; }
        /// <summary>
        /// ��ȡ���ؽڵ����͡�
        /// </summary>
        public NodeType Type { get; private set; }


        /// <summary>
        /// ��ȡ��ǰ�ڵ���Ҫ���صĲ����
        /// </summary>
        public PluginType Plugins { get; private set; }

        /// <summary>
        /// ��ȡ��ǰ�ڵ���Ҫ���صĿؼ����͡�
        /// </summary>
        public IEnumerable<PresentationControlType> ControlTypes { get { return _controlTypes; } }
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯����
        /// </summary>
        public NodeContextImpl()
        {
            this.Name = string.Empty;
            this.Type = NodeType.Default;
            this.Plugins = PluginType.All;
        }
        #endregion

        #region "Public methods"
        /// <summary>
        /// ��ʼ�����ؽڵ������Ϣ��
        /// Ĭ�Ϸ�ʽ�½����ݱ���IP�����ݿ��в��Ҷ�Ӧ�Ľڵ���Ϣ��
        /// </summary>
        public void Initialize()
        {

        }

        /// <summary>
        /// ��ʼ���ڵ������ġ�
        /// </summary>
        /// <param name="nodeCode"></param>
        public void Initialize(uint nodeCode)
        {

        }
        #endregion


        #region "INodeContext ��Ա"
        /// <summary>
        /// ��ǰ�ڵ��Ƿ����ָ���Ĳ����
        /// </summary>
        /// <param name="pluginType">ָ���Ĳ�����͡�</param>
        /// <returns>true��ʾ��Ҫ����ָ���Ĳ����false��ʾ����Ҫ���ء�</returns>
        public bool ContainsPlugin(PluginType pluginType)
        {
            return this.Plugins.HasFlag(pluginType);
        }

        #endregion
    }
}
