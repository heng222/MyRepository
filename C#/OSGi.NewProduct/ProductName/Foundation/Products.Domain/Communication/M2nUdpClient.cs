/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ�FAO.ATS
//
// �� �� �ˣ�heng222_z
// �������ڣ�2020/8/13 15:46:27 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2020 FAO.ATS����������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Threading.Tasks;

using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// ����һ�� UDPClient �� M:N ͨ���ࡣ
    /// </summary>
    public abstract class M2nUdpClient : CommEndPoint
    {
        #region "Field"
        private Task _receiveTask;

        #endregion

        #region "Constructor"
        /// <summary>
        /// ����һ��<seealso cref="M2nUdpClient"/>����
        /// </summary>
        protected M2nUdpClient()
        {
        }

        /// <summary>
        /// ����һ��<seealso cref="M2nUdpClient"/>����
        /// </summary>
        /// <param name="localType">���ؽڵ����͡�</param>
        /// <param name="localEndPoint">�����ս�㡣</param>
        protected M2nUdpClient(NodeType localType, IPEndPoint localEndPoint)
            : base(localType)
        {
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
        /// ������������дʱ�����ڻ�ȡ���ؽڵ�ı�š�
        /// </summary>
        /// <param name="remoteCode">Զ�̽ڵ��š�</param>
        /// <param name="remoteEndPoint">Զ�̽ڵ�ʹ�õ�IP�ս�㡣</param>
        /// <param name="dataReceived">�յ������ݡ�</param>
        /// <returns>���ؽڵ��š�</returns>
        protected abstract uint GetLocalCode(uint remoteCode, IPEndPoint remoteEndPoint, byte[] dataReceived);

        /// <summary>
        /// ������������дʱ�����ڻ�ȡԶ�̽ڵ�ı�š�
        /// </summary>
        /// <param name="remoteEndPoint">Զ�̽ڵ�ʹ�õ�IP�ս�㡣</param>
        /// <returns>Զ�̽ڵ�ı�š�</returns>
        protected abstract uint GetRemoteCode(IPEndPoint remoteEndPoint);

        /// <summary>
        /// ������������дʱ�����ڻ�ȡԶ�̽ڵ��IP�ս�㡣
        /// </summary>
        /// <param name="remoteCode">Զ�̽ڵ��š�</param>
        /// <returns>Զ�̽ڵ��IP�ս�㡣</returns>
        protected abstract IEnumerable<IPEndPoint> GetRemoteEndPoints(uint remoteCode);

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
        ///<inheritdoc/>
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
            catch (Exception ex)
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
                    var recvResult = await this.LocalClient.ReceiveAsync().ConfigureAwait(false);

                    var remoteEP = recvResult.RemoteEndPoint;
                    var data = recvResult.Buffer;

                    var remoteCode = this.GetRemoteCode(remoteEP);
                    var remoteType = this.GetRemoteType(remoteCode);
                    var localCode = this.GetLocalCode(remoteCode, remoteEP, data);

                    // ����Զ���ս�㡣
                    this.HandleRemoteEndPoint(remoteEP);

                    // DataTransfer ��Ϣ֪ͨ��                
                    this.PublishDataTransferEvent(this.LocalType, localCode, remoteType, remoteCode, true, data);

                    // CommLogCreated ��Ϣ֪ͨ��
                    this.PublishCommLogCreateEvent(this.LocalType, localCode, remoteType, remoteCode, true, data);

                    // �����Ƿ���Ч��
                    if (!this.VerifyData(data, remoteEP)) continue;

                    // ���������д������ݡ�
                    this.HandleDataReceived(data, remoteEP);

                    // ��������ʱ�䡣
                    this.RefreshCommState(localCode, remoteCode);
                }
                catch (Exception ex)
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
            catch (Exception ex)
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

        /// <summary>
        /// �������ݡ�
        /// </summary>
        /// <param name="data">��Ҫ���͵����ݡ�</param>
        /// <param name="localCode">���ؽڵ��š�</param>
        /// <param name="remoteEndPoint">Զ���ս�㡣</param>
        public void Send(byte[] data, uint localCode, IPEndPoint remoteEndPoint)
        {
            if (this.LocalClient == null) return;

            var remoteID = this.GetRemoteCode(remoteEndPoint);
            var remoteType = this.GetRemoteType(remoteID);

            // DataTransfer ��Ϣ֪ͨ��
            this.PublishDataTransferEvent(this.LocalType, localCode, remoteType, remoteID, false, data);

            // CommLogCreated ��Ϣ֪ͨ��
            this.PublishCommLogCreateEvent(this.LocalType, localCode, remoteType, remoteID, false, data);

            // ����
            this.LocalClient.Send(data, data.Length, remoteEndPoint);
        }

        /// <summary>
        /// ��ָ�������ݷ��͵�Զ�̽ڵ㡣
        /// </summary>
        /// <param name="data">��Ҫ���͵����ݡ�</param>
        /// <param name="localCode">���ؽڵ��š�</param>
        /// <param name="remoteCode">Զ�̽ڵ��š�</param>
        public void Send(byte[] data, uint localCode, uint remoteCode)
        {
            var remoteEndPoints = this.GetRemoteEndPoints(remoteCode);

            remoteEndPoints.ForEach(p =>
            {
                this.Send(data, localCode, p);
            });
        }
        #endregion

    }
}
