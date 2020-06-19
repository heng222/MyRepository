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


using System;
using System.Collections.Concurrent;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Threading;
using System.Threading.Tasks;
using System.Timers;

using Acl.Core;
using Acl.Log;

using Products.Infrastructure.Events;
using Products.Infrastructure.Messages;
using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// 1��Nͨ�ŵ�UdpClient�ࡣ
    /// </summary>
    public abstract class OneToNUdpClient : Acl.CompositeDisposable
    {
        #region "Field"
        private Task _receiveTask;
        private DataValidityChecker<uint> _commStateChecker = null;
        #endregion

        #region "Constructor"
        /// <summary>
        /// ����һ�� OneToNUdpClient ����
        /// </summary>
        protected OneToNUdpClient()
        {
            this.LocalType = NodeType.None;
        }

        /// <summary>
        /// ����һ��OneToNUdpClient����
        /// </summary>
        /// <param name="localType">���ؽڵ����͡�</param>
        /// <param name="localCode">���ؽڵ��š�</param>
        /// <param name="localEndPoint">�����ս�㡣</param>
        protected OneToNUdpClient(NodeType localType, uint localCode, IPEndPoint localEndPoint)
        {
            this.LocalType = localType;
            this.LocalCode = localCode;
            this.LocalEndPoint = localEndPoint;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡ��־�ӿڡ�
        /// </summary>
        protected abstract ILog Log { get; }

        /// <summary>
        /// ��ȡ���ؽڵ����͡�
        /// </summary>
        public NodeType LocalType { get; }
        /// <summary>
        /// ��ȡ���ؽڵ�ı�š�
        /// </summary>
        public uint LocalCode { get; protected set; }
        /// <summary>
        /// ��ȡ����ͨ���ս�㡣
        /// </summary>
        public IPEndPoint LocalEndPoint { get; protected set; }

        /// <summary>
        /// ��ȡ UdpClient ����
        /// </summary>
        protected UdpClient LocalClient { get; private set; }

        /// <summary>
        /// �Ƿ������׽��ְ󶨵�����ʹ���еĵ�ַ��
        /// </summary>
        protected abstract bool ReuseAddress { get; }

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
        /// ������������дʱ�����ڻ�ȡԶ�̽ڵ�ı�š�
        /// </summary>
        /// <param name="remoteEndPoint">Զ�̽ڵ�ʹ�õ�IP�ս�㡣</param>
        /// <returns>Զ�̽ڵ�ı�š�</returns>
        protected abstract uint GetRemoteCode(IPEndPoint remoteEndPoint);
        /// <summary>
        /// ������������дʱ�����ڻ�ȡԶ�̽ڵ�����͡�
        /// </summary>
        /// <param name="remoteCode">Զ�̽ڵ��š�</param>
        /// <returns>Զ�̽ڵ�ı�š�</returns>
        protected abstract NodeType GetRemoteType(uint remoteCode);

        /// <summary>
        /// ������������дʱ�����ڴ���Զ���ս�㡣
        /// </summary>
        /// <param name="remoteEndPoint">Զ���ս�㡣</param>
        protected virtual void HandleRemoteEndPoint(IPEndPoint remoteEndPoint) { }

        /// <summary>
        /// ������������дʱ��������֤�����Ƿ���Ч��
        /// </summary>
        /// <param name="data">�յ������ݡ�</param>
        /// <param name="remoteEndPoint">Զ���ս�㡣</param>
        /// <returns>true��ʾ��������Ч�ģ�false ��ʾ��������Ч�ġ�</returns>
        protected virtual bool VerifyData(byte[] data, IPEndPoint remoteEndPoint) { return true; }

        /// <summary>
        /// ������������дʱ�����ڴ����յ������ݡ�
        /// </summary>
        /// <param name="data">�յ������ݡ�</param>
        /// <param name="remoteEndPoint">Զ���ս�㡣</param>
        protected abstract void HandleDataReceived(byte[] data, IPEndPoint remoteEndPoint);
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
                this.CloseUdpClient();
                _receiveTask.Wait();
            }

            base.Dispose(disposing);
        }
        #endregion

        #region "Private methods"
        private void OpenUdpClient()
        {
            try
            {
                LocalClient = new UdpClient();

                if (this.ReuseAddress)
                {
                    LocalClient.Client.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, 1);
                }

                LocalClient.Client.Bind(this.LocalEndPoint);
                this.LocalEndPoint.Port = ((IPEndPoint)this.LocalClient.Client.LocalEndPoint).Port;

                // ��Զ������ǿ�ȹر���һ�����е�����0x80004005���Ľ��������http://blog.csdn.net/u010851953/article/details/38258977
                uint IOC_IN = 0x80000000, IOC_VENDOR = 0x18000000;
                uint SIO_UDP_CONNRESET = IOC_IN | IOC_VENDOR | 12;
                LocalClient.Client.IOControl((int)SIO_UDP_CONNRESET, new byte[] { Convert.ToByte(false) }, null);

                // ��ʼ�첽���ա�
                _receiveTask = this.ReceiveAsync();
            }
            catch (System.Exception ex)
            {
                CloseUdpClient();
                this.Log.Error(string.Format("��UdpClient��{0}������{1}", this.LocalEndPoint, ex.Message));
            }
        }

        private void CloseUdpClient()
        {
            var client = LocalClient;

            if (LocalClient != null)
            {
                LocalClient = null;

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
            try
            {
                if (this.PublishCommStateChanged)
                {
                    var remoteType = this.GetRemoteType(e.Data);

                    var args = new CommStateChangedEventArgs(e.Avaliable, this.LocalType, this.LocalCode, remoteType, e.Data);
                    GlobalMessageBus.PublishCommStateChanged(args);

                    if (this.CommStateChanged != null) this.CommStateChanged(this, args);
                }
            }
            catch (System.Exception /*ex*/)
            {
            }
        }

        private async Task ReceiveAsync()
        {
            while (this.LocalClient != null)
            {
                try
                {
                    var recvResult = await this.LocalClient.ReceiveAsync();
                    var remoteEP = recvResult.RemoteEndPoint;

                    // ����Զ���ս�㡣
                    this.HandleRemoteEndPoint(remoteEP);

                    // ��Ϣ֪ͨ��
                    var remoteCode = this.GetRemoteCode(remoteEP);
                    if (this.PublishDataIncoming)
                    {
                        var remoteType = this.GetRemoteType(remoteCode);
                        var args = new DataIncomingEventArgs(recvResult.Buffer, this.LocalType, this.LocalCode, remoteType, remoteCode);
                        GlobalMessageBus.PublishDataIncoming(args, this);
                    }

                    // ��֤�����Ƿ���Ч��
                    if (!this.VerifyData(recvResult.Buffer, remoteEP)) return;

                    // ���������д������ݡ�
                    this.HandleDataReceived(recvResult.Buffer, remoteEP);

                    // ��������ʱ�䡣
                    if (_commStateChecker != null)
                    {
                        _commStateChecker.Refresh(remoteCode);
                    }
                }
                catch (System.Exception ex)
                {
                    if (this.LocalClient != null) this.Log.Error(ex.Message);
                }
            }   
        }
        
        private void CheckUdpClient(NetworkAvailabilityEventArgs args)
        {
            try
            {
                if (this.LocalClient == null)
                {
                    this.OpenUdpClient();
                }
            }
            catch (System.Exception ex)
            {
                this.Log.Error(ex.ToString());
            }
        }

        private void SubscribeNetworkChangedEvent()
        {
            NetworkChange.NetworkAvailabilityChanged += (sender, args) => CheckUdpClient(args);
            NetworkChange.NetworkAddressChanged += (sender, args) => CheckUdpClient(null);
        }
        #endregion

        #region "Protected methods"
        #endregion

        #region "Public methods"
        /// <summary>
        /// �򿪡�
        /// </summary>
        public void Open()
        {
            this.OpenUdpClient();

            this.StartCommStateChecker();

            this.OnOpen();

            this.SubscribeNetworkChangedEvent();
        }
        #endregion

    }
}
