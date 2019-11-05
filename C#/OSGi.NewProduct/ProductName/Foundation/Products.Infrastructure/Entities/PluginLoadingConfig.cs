/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ŀ���ƣ���SIL2��֤�ı�׼��ATS
//
// �� �� �ˣ�zhangheng
// �������ڣ�2018-5-21 15:05:25 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// ����������á�
    /// </summary>
    public class PluginLoadingConfig : Entity
    {
        #region DB�ֶ�
        /// <summary>
        /// �ڵ��š�
        /// </summary>
        public UInt32 NodeCode { get; set; }

        /// <summary>
        /// �ڵ����͡�
        /// </summary>
        public NodeType NodeType { get; set; }

        /// <summary>
        /// �ڵ���Ҫ���صĲ�����͡�
        /// </summary>
        public string Plugins { get; set; }

        /// <summary>
        /// �ڵ���Ҫ��ʾ�Ŀؼ�����CVS��ʽ��ʾ�Ķ��PresentationControlType��
        /// </summary>
        public string Controls { get; set; }

        /// <summary>
        /// ��������Ϣ��
        /// </summary>
        public string Description { get; set; }

        /// <summary>
        /// NodeCode+NodeType+Plugins+Controls��MD5ǩ����
        /// </summary>
        public byte[] MessageDigest { get; set; }
        #endregion

        /// <summary>
        /// �Ƿ����ָ���Ĳ�����͡�
        /// </summary>
        /// <param name="type">ָ���Ĳ�����ͣ�����ʹ��λ���ʾ���������͡�</param>
        /// <returns>true��ʾȫ��������false��ʾ��ȫ��������</returns>
        public bool Contains(PluginType type)
        {
            return this.GetPlugins().HasFlag(type);
        }

        /// <summary>
        /// ��ȡ��Ҫ���صĲ����
        /// </summary>
        /// <returns></returns>
        public PluginType GetPlugins()
        {
            return (PluginType)UInt64.Parse(this.Plugins);
        }

        /// <summary>
        /// ������Ҫ��ʾ�Ŀؼ����͡�
        /// </summary>
        /// <param name="controls">��Ҫ���õ�ֵ��</param>
        public void SetControlTypes(IEnumerable<PresentationControlType> controls)
        {
            if (controls == null || controls.Count() == 0)
            {
                this.Controls = string.Empty;
            }
            else
            {
                this.Controls = string.Join(",", controls.Select(p => ((int)p).ToString()));
            }
        }

        /// <summary>
        /// ��ȡ��Ҫ��ʾ�Ŀؼ������б�
        /// </summary>
        /// <returns>�ڵ���Ҫ���صĿؼ����͡�</returns>
        public IEnumerable<PresentationControlType> GetControlTypes()
        {
            if (!string.IsNullOrWhiteSpace(this.Controls))
            {
                return this.Controls.Split(',').Select(p => (PresentationControlType)int.Parse(p));
            }
            else
            {
                return new List<PresentationControlType>();
            }
        }
    }
}