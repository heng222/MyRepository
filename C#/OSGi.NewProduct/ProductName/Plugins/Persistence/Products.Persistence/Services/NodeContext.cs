/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-2 10:43:04 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Products.Infrastructure.Entities;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Types;

namespace Products.Persistence.Services
{
    /// <summary>
    /// �ڵ���������Ϣ��
    /// </summary>
    public class NodeContext : INodeContext
    {
        #region "Field"
        #endregion

        #region "Property"
        ///<inheritdoc/>
        public uint Code { get; private set; }
        ///<inheritdoc/>
        public string Name { get; private set; } = "�ڵ�����";
        ///<inheritdoc/>
        public NodeType Type { get; private set; } = NodeType.Default;

        ///<inheritdoc/>
        public IEnumerable<string> Plugins { get; private set; } = Enumerable.Empty<string>();

        /// <inheritdoc/>
        public IEnumerable<string> Controls { get; private set; } = Enumerable.Empty<string>();
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯����
        /// </summary>
        public NodeContext()
        {
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
            var theNode = GlobalServices.Repository.Where<SystemNode>(p => p.Code == nodeCode).FirstOrDefault();
            if (theNode == null)
            {
                throw new Exception(string.Format("ָ���Ľڵ��ţ�{0}����Ч��", nodeCode));
            }

            this.Code = theNode.Code;
            this.Type = theNode.Type;
            this.Name = theNode.Name;

            BuildPluginsConfig();
            LogLocalDeviceInfo();
        }

        private void BuildPluginsConfig()
        {
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

            //if (localPluginCfg.MessageDigest == null)
            //{
            //    throw new Exception("����������ݴ���ǩ��Ϊ�ա�");
            //}

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
            this.Controls = localPluginCfg.GetControls();
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
                strBuilder.AppendFormat("\r\n���ڵ���Ҫ���صĲ��= {0}��", string.Join(", ", this.Plugins));

                // ���ڵ���Ҫ��ʾ�Ŀؼ���
                strBuilder.AppendFormat("\r\n���ڵ���Ҫ��ʾ�Ŀؼ�= {0}��", string.Join(", ", this.Controls));

                LogUtility.Info(strBuilder.ToString());
            }
            catch (Exception /*ex*/)
            {
            }
        }
        #endregion


        #region "INodeContext ��Ա"
        ///<inheritdoc/>
        public bool ContainsPlugin(string pluginID)
        {
            return this.Plugins.Contains(pluginID);
        }

        #endregion
    }
}
