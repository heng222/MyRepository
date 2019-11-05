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
using System.Text;
using Acl.Utility;
using Products.Domain.Utility;
using Products.Infrastructure.Entities;
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
        public IEnumerable<PresentationControlType> ControlTypes { get; private set; }
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯����
        /// </summary>
        public NodeContextImpl()
        {
            //this.Name = "�ڵ�����";
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
            BuildPluginsConfig();
            LogLocalDeviceInfo();
        }

        private void BuildPluginsConfig()
        {
            this.Plugins = PluginType.None;

            // 
            var allRecords = GlobalServices.Repository.Where<PluginLoadingConfig>().ToList();
            var localPluginCfg = allRecords.Where(p => p.NodeCode == this.Code).FirstOrDefault();

            if (localPluginCfg == null)
            {
                localPluginCfg = allRecords.Where(p => p.NodeType == this.Type).
                    FirstOrDefault();
            }

            if (localPluginCfg == null)
            {
                throw new Exception("û���ҵ����ʵĲ���������ݡ�");
            }

            if (localPluginCfg.MessageDigest == null)
            {
                throw new Exception("����������ݴ���ǩ��Ϊ�ա�");
            }

            // �������ǩ����
            //using (var md5 = MD5.Create())
            //{
            //    var expectedMd5 = AuthenticationHelper.CalculatePluginConfigMD5(localPluginCfg);

            //    var isEqual = expectedMd5.SequenceEqual(localPluginCfg.MessageDigest);
            //    if (!isEqual)
            //    {
            //        throw new Exception("����������ݴ���ǩ����ƥ�䡣");
            //    }
            //}

            // 
            this.Plugins = localPluginCfg.GetPlugins();
            this.ControlTypes = localPluginCfg.GetControlTypes();
        }

        /// <summary>
        /// ��¼�����־��
        /// </summary>
        private void LogLocalDeviceInfo()
        {
            try
            {
                // ��¼���ڵ����Ϣ
                var strBuilder = new StringBuilder(128);
                strBuilder.AppendFormat("\r\n���ڵ���Ϣ��ID= {0}, Name= {1}",
                    this.Code, this.Name);

                // ���ڵ���Ҫ���صĲ����
                strBuilder.AppendFormat("\r\n���ڵ���Ҫ���صĲ��= {0}��",
                    EnumUtility.GetDescription<PluginType>(this.Plugins));

                // ���ڵ���Ҫ��ʾ�Ŀؼ���
                strBuilder.AppendFormat("\r\n���ڵ���Ҫ��ʾ�Ŀؼ�= {0}��",
                    string.Join(",", this.ControlTypes.Select(p => string.Format("{0}", p))));
                
                LogUtility.Info(strBuilder.ToString());
            }
            catch (System.Exception /*ex*/)
            {
            }
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
