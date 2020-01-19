/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ĺ�˾����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2016-5-11 13:13:43 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Acl.Data.Annotions;
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// ϵͳ�ڵ�ʵ�嶨�塣
    /// </summary>
    [Acl.Data.Annotions.Table(Name = "ndm_SystemNodes")]
    public class SystemNode : Entity
    {
        #region "DB �ֶ�"
        /// <summary>
        /// ���ơ�
        /// </summary>
        [Column]
        public string Name { get; set; }
        /// <summary>
        /// ���͡�
        /// </summary>
        [Column]
        public NodeType Type { get; set; }

        /// <summary>
        /// ������Ϣ��
        /// </summary>
        [Column]
        public string Description { get; set; }

        #endregion

        #region "Constructor"
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"
        /// <summary>
        /// ��ȡ��ʵ�����׶�����Ϣ��
        /// </summary>
        /// <returns>һ���׶�����Ϣ��</returns>
        public override string ToString()
        {
            var sb = new StringBuilder(64);

            sb.AppendFormat("���={0}������={1}������= {2}, ���� = {3}", this.Code, this.Name, this.Type, this.Description);

            return sb.ToString();
        }
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
