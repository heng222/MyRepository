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
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// ϵͳ�ڵ�ʵ�嶨�塣
    /// </summary>
    public class SystemNode : Entity
    {
        #region "DB �ֶ�"
        /// <summary>
        /// ��š�
        /// </summary>
        public ushort Code { get; set; }
        /// <summary>
        /// ���ơ�
        /// </summary>
        public string Name { get; set; }
        /// <summary>
        /// ���͡�
        /// </summary>
        public NodeType Type { get; set; }


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

            sb.AppendFormat("���={0}������={1}��", this.Code, this.Name);

            return sb.ToString();
        }
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
