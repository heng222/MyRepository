/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Products.Infrastructure.Entities;

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// һ���¼������࣬���µ�ϵͳ�¼�����ʱʹ�á�
    /// </summary>
    public class NewSystemEventArgs : EventArgs
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯����
        /// </summary>
        /// <param name="value">��ʾϵͳ�¼�����</param>
        public NewSystemEventArgs(SysEventLog value)
        {
            this.Value = value;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡ/����ϵͳ�¼�����
        /// </summary>
        public SysEventLog Value { get; set; }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
