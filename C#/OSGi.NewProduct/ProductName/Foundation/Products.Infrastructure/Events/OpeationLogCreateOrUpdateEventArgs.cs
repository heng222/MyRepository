/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2014-9-9 9:59:01 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Products.Infrastructure.Entities;
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// һ���¼������࣬��������¼���������ʱʹ�á�
    /// </summary>
    public class OpeationLogCreateOrUpdateEventArgs : EventArgs
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯����
        /// </summary>
        /// <param name="value">��ʾһ��������¼����</param>
        public OpeationLogCreateOrUpdateEventArgs(OperationLog value)
        {
            this.Value = value;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡ/���ò�����¼����
        /// </summary>
        public OperationLog Value { get; set; }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
