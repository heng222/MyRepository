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
        /// �ڵ���Ҫ���صĲ�����͡�
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
        /// �Ƿ����ָ���Ĳ�����͡�
        /// </summary>
        /// <param name="type">ָ���Ĳ�����ͣ�����ʹ��λ���ʾ���������͡�</param>
        /// <returns>true��ʾȫ��������false��ʾ��ȫ��������</returns>
        public bool Contains(PluginTypes type)
        {
            return this.GetPlugins().HasFlag(type);
        }

        /// <summary>
        /// ��ȡ��Ҫ���صĲ����
        /// </summary>
        /// <returns></returns>
        public PluginTypes GetPlugins()
        {
            if (this.Plugins == "-1")
            {
                return PluginTypes.All;
            }
            else
            {
                return (PluginTypes)UInt64.Parse(this.Plugins);
            }
        }

        /// <summary>
        /// ������Ҫ��ʾ�Ŀؼ����͡�
        /// </summary>
        /// <param name="controls">��Ҫ���õ�ֵ��</param>
        public void SetControlTypes(IEnumerable<string> controls)
        {
            if (controls == null || !controls.Any())
            {
                this.Controls = string.Empty;
            }
            else
            {
                this.Controls = string.Join(",", controls);
            }
        }

        /// <summary>
        /// ��ȡ��Ҫ��ʾ�Ŀؼ������б�
        /// </summary>
        /// <returns>�ڵ���Ҫ���صĿؼ����͡�</returns>
        public IEnumerable<string> GetControlTypes()
        {
            if (!string.IsNullOrWhiteSpace(this.Controls))
            {
                return this.Controls.Split(',');
            }
            else
            {
                return Enumerable.Empty<string>();
            }
        }
    }
}