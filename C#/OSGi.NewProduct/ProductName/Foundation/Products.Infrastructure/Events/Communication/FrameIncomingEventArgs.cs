/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2013-7-25 14:33:39 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

using System;

using Products.Infrastructure.Protocol.Framework;
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// ���ݵ����¼������ࡣ
    /// </summary>
    public class DataIncomingEventArgs : EventArgs
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// ����һ�����ݵ�����Ϣ���¼�������
        /// </summary>
        /// <param name="data">��������ݡ�</param>
        /// <param name="localType">���ؽڵ����͡�</param>
        /// <param name="localID">���ؽڵ��š�</param>
        /// <param name="remoteType">Զ���豸���͡�</param>
        /// <param name="remoteCode">Զ���豸��š�</param>
        /// <param name="timeDelay">ʱ�ӣ���λ�����룩��</param>
        public DataIncomingEventArgs(byte[] data,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteCode,
            UInt32 timeDelay = 0)
        {
            this.Data = data;
            this.LocalType = localType;
            this.LocalCode = localID;
            this.RemoteType = remoteType;
            this.RemoteCode = remoteCode;
            this.TimeDelay = timeDelay;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡ/���ñ��ؽڵ����͡�
        /// </summary>
        public NodeType LocalType { get; set; }
        /// <summary>
        /// ��ȡ/���ñ����豸ID��
        /// </summary>
        public UInt32 LocalCode { get; set; }

        /// <summary>
        /// ��ȡ/����Զ���豸���͡�
        /// </summary>
        public NodeType RemoteType { get; set; }
        /// <summary>
        /// ��ȡ/���öԷ��豸ID��
        /// </summary>
        public UInt32 RemoteCode { get; set; }

        /// <summary>
        /// ��ȡ/����Э��֡��ʱ�ӣ���λ�����롣
        /// </summary>
        public UInt32 TimeDelay { get; set; }

        /// <summary>
        /// ����/��ȡЭ��֡���������ݡ�
        /// </summary>
        public byte[] Data { get; set; }

        #endregion
    }

    /// <summary>
    /// Э��֡�����¼������ࡣ
    /// </summary>
    public class FrameIncomingEventArgs : DataIncomingEventArgs
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// ����һ��Э��֡������Ϣ���¼�������
        /// </summary>
        /// <param name="data">���յ������ֽ�����</param>
        /// <param name="localType">���ؽڵ����͡�</param>
        /// <param name="localID">���ؽڵ��š�</param>
        /// <param name="remoteType">Զ���豸���͡�</param>
        /// <param name="remoteDeviceId">Э��֡���ͷ����豸ID</param>
        /// <param name="timeDelay">����ʱ��</param>
        public FrameIncomingEventArgs(byte[] data,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteDeviceId,
            UInt32 timeDelay = 0)
            : base(data, localType, localID, remoteType, remoteDeviceId, timeDelay)
        {
        }

        /// <summary>
        /// ����һ��Э��֡������Ϣ���¼�������
        /// </summary>
        /// <param name="frame">Э��֡����</param>
        /// <param name="localType">���ؽڵ����͡�</param>
        /// <param name="localID">���ؽڵ��š�</param>
        /// <param name="bytesStream">Э��֡��Ӧ���ֽ���</param>
        /// <param name="remoteType">Զ���豸���͡�</param>
        /// <param name="remoteDeviceId">Э��֡���ͷ����豸ID</param>
        /// <param name="timeDelay">����ʱ��</param>
        public FrameIncomingEventArgs(ProtocolFrame frame, byte[] bytesStream,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteDeviceId,
            UInt32 timeDelay = 0)
            : this(bytesStream, localType, localID, remoteType, remoteDeviceId, timeDelay)
        {
            this.Frame = frame;
        }
        #endregion

        #region "Properties"

        /// <summary>
        /// ��ȡ/���ý��յ���Э��֡��
        /// </summary>
        public ProtocolFrame Frame { get; set; }

        #endregion
    }

    /// <summary>
    /// Э��֡�����¼������ࡣ
    /// </summary>
    public class FrameIncomingEventArgs<TProtocol> : FrameIncomingEventArgs where TProtocol : ProtocolFrame
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// ����һ��Э��֡������Ϣ���¼�������
        /// </summary>
        /// <param name="data">���յ������ֽ�����</param>
        /// <param name="localType">���ؽڵ����͡�</param>
        /// <param name="localID">���ؽڵ��š�</param>
        /// <param name="remoteType">Զ���豸���͡�</param>
        /// <param name="remoteDeviceId">Э��֡���ͷ����豸ID</param>
        /// <param name="timeDelay">����ʱ��</param>
        public FrameIncomingEventArgs(byte[] data,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteDeviceId,
            UInt32 timeDelay = 0)
            : base(data, localType, localID, remoteType, remoteDeviceId, timeDelay)
        {
        }

        /// <summary>
        /// ����һ��Э��֡������Ϣ���¼�������
        /// </summary>
        /// <param name="frame">Э��֡����</param>
        /// <param name="localType">���ؽڵ����͡�</param>
        /// <param name="localID">���ؽڵ��š�</param>
        /// <param name="bytesStream">Э��֡��Ӧ���ֽ���</param>
        /// <param name="remoteType">Զ���豸���͡�</param>
        /// <param name="remoteDeviceId">Э��֡���ͷ����豸ID</param>
        /// <param name="timeDelay">����ʱ��</param>
        public FrameIncomingEventArgs(TProtocol frame, byte[] bytesStream,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteDeviceId,
            UInt32 timeDelay = 0)
            : this(bytesStream, localType, localID, remoteType, remoteDeviceId, timeDelay)
        {
            this.Frame = frame;
        }
        #endregion

        #region "Properties"

        /// <summary>
        /// ��ȡ/���ý��յ���Э��֡��
        /// </summary>
        public new TProtocol Frame { get; set; }

        #endregion
    }
}
