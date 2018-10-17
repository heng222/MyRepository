/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ�ACL
//
// �� �� �ˣ�heng222_z
// �������ڣ�2018/10/17 13:49:00 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2018 ACL����������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// һ���¼������࣬�����̽�Ҫ�˳�ʱʹ�á�
    /// </summary>
    public class ProcessExitingEventArgs : EventArgs
    {
        #region "Filed"
        #endregion

        #region "Constructor"
        /// <summary>
        /// ����һ�����������˳�ʱʹ�õĶ���
        /// </summary>
        public ProcessExitingEventArgs()
        {
            this.IsNormal = true;
            this.InnerException = null;
        }

        /// <summary>
        /// ����һ�����̷������˳�ʱʹ�õĶ���
        /// </summary>
        /// <param name="ex">�������˳�ʱ���쳣��Ϣ��</param>
        public ProcessExitingEventArgs(Exception ex)
        {
            this.IsNormal = false;
            this.InnerException = ex;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// �Ƿ�������������
        /// </summary>
        public bool IsNormal { get; private set; }

        /// <summary>
        /// �ڲ��쳣
        /// </summary>
        public Exception InnerException { get; set; }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
