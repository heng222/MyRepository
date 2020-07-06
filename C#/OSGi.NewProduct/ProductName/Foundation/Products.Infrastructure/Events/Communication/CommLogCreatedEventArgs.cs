/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ�ATS
//
// �� �� �ˣ�heng222_z
// �������ڣ�2020/4/9 16:54:57 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2020 ATS����������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Products.Infrastructure.Types;

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// һ���¼������࣬�ڲ����µ�ͨ����־�¼���ʹ�á�
    /// </summary>
    public class CommLogCreatedEventArgs : EventArgs
    {
        #region "Field"
        #endregion

        #region "Constructor"

        /// <summary>
        /// ���캯����
        /// </summary>
        /// <param name="localType">���ؽڵ����͡�</param>
        /// <param name="localCode">���ؽڵ��š�</param>
        /// <param name="remoteType">�Է��ڵ����͡�</param>
        /// <param name="remoteCode">�Է��ڵ��š�</param>
        /// <param name="isIncoming">�Ƿ�Ϊ��������</param>
        /// <param name="data">��������</param>
        public CommLogCreatedEventArgs(NodeType localType, uint localCode,
            NodeType remoteType, uint remoteCode, bool isIncoming, byte[] data)
        {
            this.Timestamp = DateTime.Now;
            this.LocalNodeType = localType;
            this.LocalNodeCode = localCode;
            this.RemoteNodeType = remoteType;
            this.RemoteNodeCode = remoteCode;
            this.IsIncomingData = isIncoming;
            this.Data = data;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ���ؽڵ����͡�
        /// </summary>
        public NodeType LocalNodeType { get; private set; }
        /// <summary>
        /// ���ؽڵ��š�
        /// </summary>
        public uint LocalNodeCode { get; private set; }

        /// <summary>
        /// �Է��ڵ����͡�
        /// </summary>
        public NodeType RemoteNodeType { get; private set; }
        /// <summary>
        /// �Է��ڵ��š�
        /// </summary>
        public uint RemoteNodeCode { get; private set; }

        /// <summary>
        /// �Ƿ�Ϊ������������
        /// true��ʾ������������fasle��ʾ�����������
        /// </summary>
        public bool IsIncomingData { get; private set; }

        /// <summary>
        /// �²�������������
        /// </summary>
        public byte[] Data { get; private set; }

        /// <summary>
        /// ��ȡ��־�Ĳ���ʱ�䡣
        /// </summary>
        public DateTime Timestamp { get; private set; }

        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
