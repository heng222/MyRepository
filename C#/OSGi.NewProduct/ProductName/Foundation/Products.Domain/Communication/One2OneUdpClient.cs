/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ��й�糵����
//
// �� �� �ˣ�heng222_z
// �������ڣ�2019/11/14 10:50:55 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2019 ̩��˹����������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Net;
using System.Net.Sockets;
using System.Timers;
using Acl.Log;
using Products.Infrastructure.Events;
using Products.Infrastructure.Messages;
using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// һ��һUdpClient��װ����
    /// </summary>
    public abstract class One2OneUdpClient : OneToNUdpClient
    {
        #region "Field"

        #endregion

        #region "Constructor"
        /// <summary>
        /// ����һ��One2OneUdpClient����
        /// </summary>
        protected One2OneUdpClient()
        {
        }

        /// <summary>
        /// ����һ��One2OneUdpClient����
        /// </summary>
        /// <param name="localCode">���ؽڵ��š�</param>
        /// <param name="remoteCode">Զ�̽ڵ��š�</param>
        /// <param name="localEndPoint">�����ս�㡣</param>
        /// <param name="remoteEndPoint">Զ���ս�㡣</param>
        protected One2OneUdpClient(uint localCode, uint remoteCode,
            IPEndPoint localEndPoint, IPEndPoint remoteEndPoint)
            : base(localCode, localEndPoint)
        {
            this.RemoteCode = remoteCode;
            this.RemoteEndPoint = remoteEndPoint;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡԶ�̽ڵ����͡�
        /// </summary>
        public abstract NodeType RemoteType { get; }
        /// <summary>
        /// ��ȡԶ�̽ڵ�ı�š�
        /// </summary>
        public uint RemoteCode { get; protected set; }
        /// <summary>
        /// ��ȡԶ��ͨ���ս�㡣
        /// </summary>
        public IPEndPoint RemoteEndPoint { get; protected set; }

        #endregion

        #region "Abstract/Virtual methods"

        /// <summary>
        /// һ��ģ�巽�������ڷ������ݡ�
        /// </summary>
        /// <param name="data">��Ҫ���͵����ݡ�</param>
        public virtual void Send(byte[] data)
        {
            if (this.LocalClient == null || this.RemoteEndPoint == null) return;

            // ��Ϣ֪ͨ��
            if (this.PublishDataOutgoing)
            {
                var args = new DataOutgoingEventArgs(data, this.LocalType, this.LocalCode, this.RemoteType, this.RemoteCode);
                GlobalMessageBus.PublishDataOutgoing(args, this);
            }

            // ����
            this.LocalClient.Send(data, data.Length, this.RemoteEndPoint);
        }
        #endregion

        #region "Override methods"
        /// <summary>
        /// �ͷ���Դ��
        /// </summary>
        /// <param name="disposing">�Ƿ��ͷ��й���Դ��</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
            }

            base.Dispose(disposing);
        }

        /// <summary>
        /// ������������дʱ�����ڻ�ȡԶ�̽ڵ�ı�š�
        /// </summary>
        /// <param name="remoteEndPoint">Զ�̽ڵ�ʹ�õ�IP�ս�㡣</param>
        /// <returns>Զ�̽ڵ�ı�š�</returns>
        protected override uint GetRemoteCode(IPEndPoint remoteEndPoint)
        {
            return this.RemoteCode;
        }

        /// <summary>
        /// ������������дʱ�����ڻ�ȡԶ�̽ڵ�����͡�
        /// </summary>
        /// <param name="remoteCode">Զ�̽ڵ��š�</param>
        /// <returns>Զ�̽ڵ�ı�š�</returns>
        protected override NodeType GetRemoteType(uint remoteCode)
        {
            return this.RemoteType;
        }

        /// <summary>
        /// ������������дʱ�����ڴ����յ������ݡ�
        /// </summary>
        /// <param name="data">�յ������ݡ�</param>
        /// <param name="remoteEndPoint">Զ���ս�㡣</param>
        protected override void HandleDataReceived(byte[] data, IPEndPoint remoteEndPoint)
        {
            if (this.RemoteEndPoint == null)
            {
                this.RemoteEndPoint = remoteEndPoint;
            }
        }
        #endregion

        #region "Private methods"

        #endregion

        #region "Public methods"
        #endregion
    }
}
