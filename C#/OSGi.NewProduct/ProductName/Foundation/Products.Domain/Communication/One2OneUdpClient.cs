/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-2 10:43:04 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
//
//----------------------------------------------------------------*/

using System.Net;

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
            this.RemoteType = NodeType.None;
        }

        /// <summary>
        /// ����һ��One2OneUdpClient����
        /// </summary>
        /// <param name="localType">���ؽڵ����͡�</param>
        /// <param name="localCode">���ؽڵ��š�</param>
        /// <param name="remoteType">Զ�̽ڵ����͡�</param>
        /// <param name="remoteCode">Զ�̽ڵ��š�</param>
        /// <param name="localEndPoint">�����ս�㡣</param>
        /// <param name="remoteEndPoint">Զ���ս�㡣</param>
        protected One2OneUdpClient(NodeType localType, uint localCode,
            NodeType remoteType, uint remoteCode,
            IPEndPoint localEndPoint, IPEndPoint remoteEndPoint)
            : base(localType, localCode, localEndPoint)
        {
            this.RemoteType = remoteType;
            this.RemoteCode = remoteCode;
            this.RemoteEndPoint = remoteEndPoint;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡԶ�̽ڵ����͡�
        /// </summary>
        public NodeType RemoteType { get; }
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

            // DataTransfer ��Ϣ֪ͨ��
            this.PublishDataTransferEvent(this.RemoteType, this.RemoteCode, false, data);

            // CommLogCreated ��Ϣ֪ͨ��
            this.PublishCommLogCreateEvent(this.RemoteType, this.RemoteCode, false, data);

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
        protected sealed override uint GetRemoteCode(IPEndPoint remoteEndPoint)
        {
            return this.RemoteCode;
        }

        /// <summary>
        /// ������������дʱ�����ڻ�ȡԶ�̽ڵ�����͡�
        /// </summary>
        /// <param name="remoteCode">Զ�̽ڵ��š�</param>
        /// <returns>Զ�̽ڵ�ı�š�</returns>
        protected sealed override NodeType GetRemoteType(uint remoteCode)
        {
            return this.RemoteType;
        }

        /// <summary>
        /// ������������дʱ�����ڴ���Զ���ս�㡣
        /// </summary>
        /// <param name="remoteEndPoint">Զ���ս�㡣</param>
        protected sealed override void HandleRemoteEndPoint(IPEndPoint remoteEndPoint)
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
