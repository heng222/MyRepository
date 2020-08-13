/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ�ATS
//
// �� �� �ˣ�heng222_z
// �������ڣ�2020/5/26 19:35:28 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2020 ATS����������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Threading.Tasks;

using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// 1��1ͨ�ŵ�TCP�ͻ���ͨ���ࡣ
    /// <para>ע��1��TCP�ͻ���ֻ����1��TCP������ͨ�š�</para>
    /// </summary>
    public abstract class One2OneTcpClient : CommEndPoint
    {
        #region "Filed"

        /// <summary>
        /// ���ջ��档
        /// </summary>
        private byte[] _receiveBuffer = new byte[128];


        #endregion

        #region "Constructor"
        /// <summary>
        /// ����һ��One2OneUdpClient����
        /// </summary>
        /// <param name="localType">���ؽڵ����͡�</param>
        /// <param name="remoteType">Զ�̽ڵ����͡�</param>
        /// <param name="localCode">���ؽڵ��š�</param>
        /// <param name="remoteCode">Զ�̽ڵ��š�</param>
        /// <param name="localEndPoint">�����ս�㡣</param>
        /// <param name="remoteEndPoint">Զ���ս�㡣</param>
        protected One2OneTcpClient(NodeType localType, NodeType remoteType,
            uint localCode, uint remoteCode,
            IPEndPoint localEndPoint, IPEndPoint remoteEndPoint)
            : base(localType)
        {
            this.LocalCode = localCode;
            this.RemoteType = remoteType;
            this.RemoteCode = remoteCode;

            this.LocalEndPoint = localEndPoint;
            this.RemoteEndPoint = remoteEndPoint;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡ���ؽڵ�ı�š�
        /// </summary>
        public virtual uint LocalCode { get; protected set; }

        /// <summary>
        /// ��ȡ UdpClient ����
        /// </summary>
        protected TcpClient TcpClient { get; private set; }

        /// <summary>
        /// ��ȡԶ�̽ڵ����͡�
        /// </summary>
        public NodeType RemoteType { get; private set; }
        /// <summary>
        /// ��ȡԶ�̽ڵ�ı�š�
        /// </summary>
        public uint RemoteCode { get; protected set; }

        /// <summary>
        /// ��ȡ����ͨ���ս�㡣
        /// </summary>
        public IPEndPoint LocalEndPoint { get; protected set; }
        /// <summary>
        /// ��ȡԶ��ͨ���ս�㡣
        /// </summary>
        public IPEndPoint RemoteEndPoint { get; protected set; }
        #endregion

        #region "Abstract/Virtual methods"
        /// <summary>
        /// ������������дʱ�����ڴ����ʼ���¼���
        /// </summary>
        protected virtual void OnOpen() { }

        /// <summary>
        /// ������������дʱ��������֤�����Ƿ���Ч��
        /// </summary>
        /// <param name="data">�յ������ݡ�</param>
        /// <param name="len">���ݵ���Ч���ȡ�</param>
        /// <returns>true��ʾ��������Ч�ģ�false ��ʾ��������Ч�ġ�</returns>
        protected virtual bool VerifyData(byte[] data, int len) { return true; }

        /// <summary>
        /// ������������дʱ�����ڴ����յ������ݡ�
        /// </summary>
        /// <param name="data">�յ������ݡ�</param>
        /// <param name="len">���ݵ���Ч���ȡ�</param>
        protected abstract void HandleDataReceived(byte[] data, int len);
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
                this.CloseTcpClient();
            }

            base.Dispose(disposing);
        }
        #endregion

        #region "Private methods"

        private void CreateTcpClient()
        {
            if (TcpClient == null)
            {
                TcpClient = new TcpClient(this.LocalEndPoint);
            }
        }

        private void CloseTcpClient()
        {
            var client = TcpClient;

            if (TcpClient != null)
            {
                TcpClient = null;

                client.Close();
            }
        }

        private void BeginConnectAsyn(int delay)
        {
            Task.Factory.StartNew(() =>
            {
                Thread.Sleep(delay);
                this.BeginConnect();
            });
        }

        private void BeginConnect()
        {
            try
            {
                if (this.IsDisposed) return;

                this.CloseTcpClient();

                this.CreateTcpClient();

                TcpClient.BeginConnect(this.RemoteEndPoint.Address, this.RemoteEndPoint.Port, ConnectCallBack, null);
            }
            catch (Exception ex)
            {
                this.Log.Error(string.Format("{0}��{1}", this.LocalEndPoint, ex.Message));

                this.BeginConnectAsyn(30000);
            }
        }

        private void ConnectCallBack(IAsyncResult rc)
        {
            try
            {
                if (TcpClient != null) TcpClient.EndConnect(rc);

                // ��������ʱ�䡣
                this.RefreshCommState(this.LocalCode, this.RemoteCode);

                // ���ӳɹ��󣬿�ʼ�������ݡ�
                if (this.AllowReceive)
                {
                    this.BeginReceive();
                }
            }
            catch (Exception ex)
            {
                this.Log.Error(ex);
                this.BeginConnectAsyn(30000);
            }
        }

        private void BeginReceive()
        {
            try
            {
                if (this.IsDisposed) return;

                TcpClient.Client.BeginReceive(_receiveBuffer, 0, _receiveBuffer.Length, SocketFlags.None, ReceiveCallBack, TcpClient);
            }
            catch (Exception /*ex*/)
            {
                Task.Factory.StartNew(() =>
                {
                    Thread.Sleep(3000);
                    this.BeginReceive();
                });
            }
        }

        private void ReceiveCallBack(IAsyncResult rc)
        {
            int count = 0;

            try
            {
                if (this.TcpClient != null) count = TcpClient.Client.EndReceive(rc);

                if (count > 0)
                {
                    // ��Ϣ֪ͨ��
                    if (this.PublishDataIncoming || this.PublishCommLogCreated)
                    {
                        var data = _receiveBuffer.Take(count).ToArray();

                        // DataTransfer��Ϣ֪ͨ��
                        this.PublishDataTransferEvent(this.LocalType, this.LocalCode, this.RemoteType, this.RemoteCode, true, data);

                        // CommLogCreated ��Ϣ֪ͨ��
                        this.PublishCommLogCreateEvent(this.LocalType, this.LocalCode, this.RemoteType, this.RemoteCode, true, data);
                    }

                    // ��֤�����Ƿ���Ч��
                    if (!this.VerifyData(_receiveBuffer, count)) return;

                    // ���������д������ݡ�
                    this.HandleDataReceived(_receiveBuffer, count);

                    // ��������ʱ�䡣
                    this.RefreshCommState(this.LocalCode, this.RemoteCode);
                }
                // �ֽ���Ϊ0��ʾ�����������ر����ӡ�
                else
                {
                    this.BeginConnectAsyn(30000);
                }
            }
            catch (SocketException ex)
            {
                count = 0;
                this.Log.Error(string.Format($"{ex.Message} SocketErrorCode = {ex.SocketErrorCode}"));
                this.BeginConnectAsyn(30000);
            }
            catch (Exception ex)
            {
                this.Log.Error(ex);
            }
            finally
            {
                if (count > 0) this.BeginReceive();
            }
        }

        #endregion

        #region "Public methods"

        /// <summary>
        /// �򿪡�
        /// </summary>
        public void Open()
        {
            this.BeginConnect();

            this.OnOpen();
        }

        /// <summary>
        /// �������ݡ�
        /// </summary>
        public void Send(byte[] buffer)
        {
            // DataTransfer��Ϣ֪ͨ��
            this.PublishDataTransferEvent(this.LocalType, this.LocalCode, this.RemoteType, this.RemoteCode, false, buffer);

            // CommLogCreated ��Ϣ֪ͨ��
            this.PublishCommLogCreateEvent(this.LocalType, this.LocalCode, this.RemoteType, this.RemoteCode, false, buffer);

            // ����Ѿ����ӣ��������ݡ�
            if (this.TcpClient != null && this.TcpClient.Connected)
            {
                var stream = this.TcpClient.GetStream();
                stream.Write(buffer, 0, buffer.Length);
            }
        }

        #endregion
    }
}
