/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ŀ���ƣ���SIL2��֤�ı�׼��ATS
//
// �� �� �ˣ�zhangheng
// �������ڣ�2018-5-21 15:05:25 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;

using Acl.Data.Annotions;

using Products.Infrastructure.Types;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// ����������á�
    /// </summary>
    [Table(Name = "system_PluginLoadingConfigs")]
    public class PluginLoadingConfig : Entity
    {
        #region "Field"
        private IEnumerable<string> _pluginsID;
        private IEnumerable<string> _controlsID;
        #endregion

        #region DB�ֶ�
        /// <summary>
        /// �ڵ��š�
        /// </summary>
        [Column]
        public UInt32 NodeCode { get; set; }

        /// <summary>
        /// �ڵ����͡�
        /// </summary>
        [Column]
        public NodeType NodeType { get; set; }

        /// <summary>
        /// �ڵ���Ҫ���صĲ����
        /// <para>CSV��ʽ�Ĳ��ID���ϡ�</para>
        /// </summary>
        [Column]
        public string Plugins { get; set; }

        /// <summary>
        /// �ڵ���Ҫ��ʾ�Ŀؼ�����CVS��ʽ��ʾ�Ķ��PresentationControlType��
        /// </summary>
        [Column]
        public string Controls { get; set; }

        /// <summary>
        /// ��������Ϣ��
        /// </summary>
        [Column(Length = 100)]
        public string Description { get; set; }

        /// <summary>
        /// NodeCode+NodeType+Plugins+Controls��MD5ǩ����
        /// </summary>
        [Column(Length = 16)]
        public byte[] MessageDigest { get; set; }
        #endregion

        /// <summary>
        /// �Ƿ����ָ���Ĳ����
        /// </summary>
        /// <param name="pluginID">�����š�</param>
        /// <returns>true��ʾȫ��������false��ʾ��ȫ��������</returns>
        public bool Contains(string pluginID)
        {
            return this.GetPlugins().Contains(pluginID);
        }

        /// <summary>
        /// ��ȡ��Ҫ���صĲ��ID���ϡ�
        /// </summary>
        /// <returns>CSV��ʽ�Ĳ��ID���ϡ�</returns>
        public IEnumerable<string> GetPlugins()
        {
            if (_pluginsID == null)
            {
                _pluginsID = string.IsNullOrWhiteSpace(this.Plugins) ? Enumerable.Empty<string>() : this.Plugins.Split(new char[] { ',', '��' }).ToList();
            }

            return _pluginsID;
        }

        /// <summary>
        /// ��ȡ��Ҫ��ʾ�Ŀؼ���
        /// </summary>
        /// <returns>�ڵ���Ҫ���صĿؼ���</returns>
        public IEnumerable<string> GetControls()
        {
            if (_controlsID == null)
            {
                _controlsID = string.IsNullOrWhiteSpace(this.Controls) ? Enumerable.Empty<string>() : this.Controls.Split(new char[] { ',', '��' }).ToList();
            }

            return _controlsID;
        }
    }
}