/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�03/02/2012 15:13:23 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���� 2009-2015 ��������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;

namespace Products.Infrastructure.Protocol.Framework
{
    /// <summary>
    /// ͨѶЭ��֡���ඨ��
    /// </summary>
    public abstract class ProtocolFrame
    {
        #region "Filed"
        /// <summary>
        /// Э�������
        /// </summary>
        private ProtocolKind _kind;
        #endregion

        #region "Constructor"
        /// <summary>
        /// ʹ��ָ���Ĳ�����ʼ��һ��Э�鱨��
        /// </summary>
        /// <param name="type">Э������</param>
        protected ProtocolFrame(ProtocolKind type)
        {
            _kind = type;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡЭ�������
        /// </summary>
        public ProtocolKind ProtocolKind
        {
            get { return _kind; }
        }
        #endregion

        #region "Virtual methods"

        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion
    }
}
