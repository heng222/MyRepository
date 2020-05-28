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
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

using Acl.Core;
using Acl.Log;

using Products.Infrastructure;
using Products.Infrastructure.Events;
using Products.Infrastructure.Messages;
using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// 1��1ͨ�ŵ�TCP�ͻ���ͨ���ࡣ
    /// <para>ע��1��TCP�ͻ���ֻ����1��TCP������ͨ�š�</para>
    /// </summary>
    public abstract class One2OneTcpClient : Acl.CompositeDisposable
    {
        #region "Filed"
        private DataValidityChecker<uint> _commStateChecker = null;

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
        {
            this.LocalType = localType;
            this.RemoteType = remoteType;

            this.LocalCode = localCode;
            this.RemoteCode = remoteCode;

            this.LocalEndPoint = localEndPoint;
            this.RemoteEndPoint = remoteEndPoint;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡ��־�ӿڡ�
        /// </summary>
        protected abstract ILog Log { get; }

        /// <summary>
        /// ��ȡ UdpClient ����
        /// </summary>
        protected TcpClient TcpClient { get; private set; }

        /// <summary>
        /// ��ȡ���ؽڵ����͡�
        /// </summary>
        public NodeType LocalType { get; private set; }
        /// <summary>
        /// ��ȡԶ�̽ڵ����͡�
        /// </summary>
        public NodeType RemoteType { get; private set; }
        /// <summary>
        /// ��ȡ���ؽڵ�ı�š�
        /// </summary>
        public uint LocalCode { get; protected set; }
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

        /// <summary>
        /// ��ȡԶ�����ݵ���Ч��N���룩����N��û���յ�Զ������ʱ��ͨ���жϡ�
        /// С�ڵ���0ʱ��ʾ����顣
        /// </summary>
        protected virtual int RemoteDataExpiredTime { get { return Timeout.Infinite; } }

        /// <summary>
        /// �Ƿ���ȫ�������Ϸ���CommStateChanged��Ϣ��
        /// </summary>
        protected virtual bool PublishCommStateChanged { get { return true; } }
        /// <summary>
        /// �Ƿ���ȫ�������Ϸ���DataIncoming��Ϣ��
        /// </summary>
        protected virtual bool PublishDataIncoming { get { return true; } }
        /// <summary>
        /// �Ƿ���ȫ�������Ϸ���DataOutgoing��Ϣ��
        /// </summary>
        protected virtual bool PublishDataOutgoing { get { return true; } }

        /// <summary>
        /// һ���¼�������Զ�̽ڵ�ͨ��״̬�ı�ʱ������
        /// </summary>
        public event EventHandler<CommStateChangedEventArgs> CommStateChanged;
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

        private void StartCommStateChecker()
        {
            if (this.RemoteDataExpiredTime > 0 && _commStateChecker == null)
            {
                _commStateChecker = new DataValidityChecker<uint>(this.RemoteDataExpiredTime);
                this.AddDisposable(_commStateChecker);
                _commStateChecker.DataValidityChanged += CommStateChecker_DataValidityChanged;

                _commStateChecker.Open();
            }
        }

        private void CommStateChecker_DataValidityChanged(object sender, DataValidityChangedEventArgs<uint> e)
        {
            if (this.PublishCommStateChanged)
            {
                try
                {
                    Task.Factory.StartNew(() =>
                    {
                        var args = new CommStateChangedEventArgs(e.Avaliable, this.LocalType, this.LocalCode, this.RemoteType, e.Data);
                        GlobalMessageBus.PublishCommStateChanged(args);

                        if (this.CommStateChanged != null) this.CommStateChanged(this, args);
                    });
                }
                catch (System.Exception /*ex*/)
                {
                }
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
                if (_commStateChecker != null) _commStateChecker.Refresh(this.RemoteCode);

                // ���ӳɹ��󣬿�ʼ�������ݡ�
                this.BeginReceive();
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
            catch (Exception ex)
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
                    if (this.PublishDataIncoming)
                    {
                        var args = new DataIncomingEventArgs(_receiveBuffer.Take(count).ToArray(),
                            this.LocalType, this.LocalCode, this.RemoteType, this.RemoteCode);
                        GlobalMessageBus.PublishDataIncoming(args, this);
                    }

                    // ��֤�����Ƿ���Ч��
                    if (!this.VerifyData(_receiveBuffer, count)) return;

                    // ���������д������ݡ�
                    this.HandleDataReceived(_receiveBuffer, count);

                    // ��������ʱ�䡣
                    if (_commStateChecker != null) _commStateChecker.Refresh(this.RemoteCode);
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

            this.StartCommStateChecker();

            this.OnOpen();
        }

        /// <summary>
        /// �������ݡ�
        /// </summary>
        public void Send(byte[] buffer)
        {
            // ��Ϣ֪ͨ�� 
            if (this.PublishDataOutgoing)
            {
                var args = new DataOutgoingEventArgs(buffer, this.LocalType, this.LocalCode, this.RemoteType, this.RemoteCode);
                GlobalMessageBus.PublishDataOutgoing(args, this);
            }

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
