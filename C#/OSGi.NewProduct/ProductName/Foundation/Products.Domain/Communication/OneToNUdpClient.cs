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
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Threading.Tasks;

using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// 1��Nͨ�ŵ�UdpClient�ࡣ
    /// </summary>
    public abstract class OneToNUdpClient : CommEndPoint
    {
        #region "Field"
        private Task _receiveTask;
        #endregion

        #region "Constructor"
        /// <summary>
        /// ����һ�� OneToNUdpClient ����
        /// </summary>
        protected OneToNUdpClient()
        {
        }

        /// <summary>
        /// ����һ��OneToNUdpClient����
        /// </summary>
        /// <param name="localType">���ؽڵ����͡�</param>
        /// <param name="localCode">���ؽڵ��š�</param>
        /// <param name="localEndPoint">�����ս�㡣</param>
        protected OneToNUdpClient(NodeType localType, uint localCode, IPEndPoint localEndPoint)
            : base(localType, localCode)
        {
            this.LocalCode = localCode;
            this.LocalEndPoint = localEndPoint;
        }
        #endregion

        #region "Properties"

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

                if (_receiveTask != null)
                {
                    var tmpTask = _receiveTask;
                    _receiveTask = null;
                    tmpTask.Wait();
                }
            }

            base.Dispose(disposing);
        }
        #endregion

        #region "Private methods"
        private void OpenUdpClient()
        {
            try
            {
                this.LocalClient = new UdpClient();

                if (this.ReuseAddress)
                {
                    this.LocalClient.Client.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, 1);
                }

                this.LocalClient.Client.Bind(this.LocalEndPoint);
                this.LocalEndPoint.Port = ((IPEndPoint)this.LocalClient.Client.LocalEndPoint).Port;

                // ��Զ������ǿ�ȹر���һ�����е�����0x80004005���Ľ��������http://blog.csdn.net/u010851953/article/details/38258977
                uint IOC_IN = 0x80000000, IOC_VENDOR = 0x18000000;
                uint SIO_UDP_CONNRESET = IOC_IN | IOC_VENDOR | 12;
                this.LocalClient.Client.IOControl((int)SIO_UDP_CONNRESET, new byte[] { Convert.ToByte(false) }, null);

                // ��ʼ�첽���ա�
                if (this.AllowReceive)
                {
                    _receiveTask = this.ReceiveAsync();
                }
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

        private async Task ReceiveAsync()
        {
            while (this.LocalClient != null)
            {
                try
                {
#pragma warning disable CA2007 // Consider calling ConfigureAwait on the awaited task
                    var recvResult = await this.LocalClient.ReceiveAsync();
#pragma warning restore CA2007 // Consider calling ConfigureAwait on the awaited task
                    var remoteEP = recvResult.RemoteEndPoint;
                    var remoteCode = this.GetRemoteCode(remoteEP);
                    var remoteType = this.GetRemoteType(remoteCode);

                    // ����Զ���ս�㡣
                    this.HandleRemoteEndPoint(remoteEP);

                    // DataTransfer ��Ϣ֪ͨ��                
                    this.PublishDataTransferEvent(remoteType, remoteCode, true, recvResult.Buffer);

                    // CommLogCreated ��Ϣ֪ͨ��
                    this.PublishCommLogCreateEvent(remoteType, remoteCode, true, recvResult.Buffer);

                    // �����Ƿ���Ч��
                    if (!this.VerifyData(recvResult.Buffer, remoteEP)) continue;

                    // ���������д������ݡ�
                    this.HandleDataReceived(recvResult.Buffer, remoteEP);

                    // ��������ʱ�䡣
                    this.RefreshCommState(remoteCode);
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

            this.OnOpen();

            this.SubscribeNetworkChangedEvent();
        }
        #endregion

    }
}
