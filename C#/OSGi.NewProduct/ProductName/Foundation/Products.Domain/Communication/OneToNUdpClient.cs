/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ�ACL
//
// �� �� �ˣ�heng2
// �������ڣ�2019/11/26 16:37:03 
// ��    �䣺heng2@163.com
//
// Copyright (C) 2019 ACL����������Ȩ����
//
//----------------------------------------------------------------*/


using System;
using System.Collections.Concurrent;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Timers;
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
        /// <summary>
        /// 1�����ָ����IPEndPoint�Ƿ���á�
        /// 2����鱾�ڵ���Է��ڵ������״̬��
        /// </summary>
        private System.Timers.Timer _checkTimer;

        /// <summary>
        /// Key = Remote Node Code.
        /// Value = ���һ���յ������ݵ�ʱ�䡣
        /// </summary>
        private ConcurrentDictionary<uint, DateTime> _dataTimestamp = new ConcurrentDictionary<uint, DateTime>();
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
        /// <param name="localCode">���ؽڵ��š�</param>
        /// <param name="localEndPoint">�����ս�㡣</param>
        protected OneToNUdpClient(uint localCode, IPEndPoint localEndPoint)
        {
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
        public abstract NodeType LocalType { get; }
        /// <summary>
        /// ��ȡ���ؽڵ�ı�š�
        /// </summary>
        public uint LocalCode { get; private set; }
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
        /// ��ȡԶ�����ݵ���Ч��N���룩����N��û���յ�Զ������ʱ��֪ͨ�����жϡ�
        /// С�ڵ���0ʱ��ʾ����顣
        /// </summary>
        protected virtual int RemoteDataExpiredTime { get { return -1; } }

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
                this.CloseTimer();
                this.CloseUdpClient();
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
                LocalClient.BeginReceive(ReceiveDataAsync, null);
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

        private int GetTimerInterval()
        {
            var timeSpan = TimeSpan.FromSeconds(this.RemoteDataExpiredTime);
            if (timeSpan.TotalMinutes > 1)
            {
                return 60000; // 60 ��
            }
            else if (timeSpan.TotalSeconds >= 30)
            {
                return 5000; // 5��
            }
            else
            {
                return 1000; // 1 ��
            }
        }

        private void StartCheckTimer()
        {
            if (this.RemoteDataExpiredTime > 0)
            {
                var interval = GetTimerInterval();
                _checkTimer = new System.Timers.Timer(interval);
                _checkTimer.AutoReset = false;
                _checkTimer.Elapsed += OnCheckTimerElapsed;
                _checkTimer.Start();
            }
        }

        private void OnCheckTimerElapsed(object sender, ElapsedEventArgs e)
        {
            try
            {
                // ���ͨ��״̬��
                this.CheckCommState();
            }
            catch (System.Exception ex)
            {
                this.Log.Error(ex);
            }
            finally
            {
                if (_checkTimer != null) _checkTimer.Start();
            }
        }

        private void NotifyCommStateChanged(CommStateChangedEventArgs args)
        {
            try
            {
                GlobalMessageBus.PublishCommStateChanged(args);

                if (this.CommStateChanged != null) this.CommStateChanged(this, args);
            }
            catch (System.Exception /*ex*/)
            {
            }
        }

        private void CheckCommState()
        {
            if (this.RemoteDataExpiredTime <= 0) return;

            _dataTimestamp.ToList().ForEach(p =>
            {
                if ((DateTime.Now - p.Value).TotalSeconds >= this.RemoteDataExpiredTime)
                {
                    DateTime value;
                    _dataTimestamp.TryRemove(p.Key, out value);

                    var remoteType = this.GetRemoteType(p.Key);

                    // ֪ͨ�����жϡ�
                    var args = new CommStateChangedEventArgs(false, this.LocalType, this.LocalCode, remoteType, p.Key);
                    this.NotifyCommStateChanged(args);
                }
            });
        }

        private void CloseTimer()
        {
            var tmpTimer = _checkTimer;
            _checkTimer = null;

            if (tmpTimer != null)
            {
                tmpTimer.Close();
            }
        }

        private void BeginReceive()
        {
            try
            {
                if (LocalClient != null)
                {
                    LocalClient.BeginReceive(ReceiveDataAsync, null);
                }
            }
            catch (System.Exception ex)
            {
                this.Log.Error(string.Format("IPEndPoint = {0}��\r\n {1}", LocalClient, ex));
            }
        }

        private void ReceiveDataAsync(IAsyncResult ar)
        {
            try
            {
                if (this.LocalClient == null) return;

                // End Receive.
                IPEndPoint remoteEP = null;
                var data = LocalClient.EndReceive(ar, ref remoteEP);

                // ��֤�����Ƿ���Ч��
                if (!this.VerifyData(data, remoteEP)) return;

                // ��ȡԶ�̱�š�
                var remoteCode = this.GetRemoteCode(remoteEP);
                var remoteType = this.GetRemoteType(remoteCode);

                // ��������ʱ�䡣
                var existed = _dataTimestamp.ContainsKey(remoteCode);
                _dataTimestamp.AddOrUpdate(remoteCode, DateTime.Now, (key, oldValue) => DateTime.Now);

                // ֪ͨ����״̬
                if (!existed)
                {
                    var args = new CommStateChangedEventArgs(true, this.LocalType, this.LocalCode, remoteType, remoteCode);
                    this.NotifyCommStateChanged(args);
                }

                // ���������д������ݡ�
                this.HandleDataReceived(data, remoteEP);
            }
            catch (System.Exception ex)
            {
                this.Log.Error(ex.Message);
            }
            finally
            {
                this.BeginReceive();
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

            this.StartCheckTimer();

            this.OnOpen();

            this.SubscribeNetworkChangedEvent();
        }
        #endregion

    }
}
