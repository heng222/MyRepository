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
using System.Collections.Concurrent;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Timers;
using Acl.Log;
using Products.Domain.Utility;
using Products.Infrastructure.Events;
using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// һ��һUdpClient��װ����
    /// </summary>
    public abstract class One2OneUdpClient : Acl.CompositeDisposable
    {
        #region "Field"
        /// <summary>
        /// ���һ�μ��IP��ַ�Ƿ���õ�ʱ�䡣
        /// </summary>
        private DateTime _lastIpCheckTime = DateTime.MinValue;

        /// <summary>
        /// ���һ���յ����ݵ�ʱ�䡣
        /// </summary>
        private DateTime _lastDataReceiveTime = DateTime.MinValue;

        /// <summary>
        /// 1�����ָ����IPEndPoint�Ƿ���á�
        /// 2����鱾�ڵ���Է��ڵ������״̬��
        /// </summary>
        private System.Timers.Timer _checkTimer;
        #endregion

        #region "Constructor"
        /// <summary>
        /// ����һ��One2OneUdpClient����
        /// </summary>
        /// <param name="remoteCode">Զ�̽ڵ��š�</param>
        /// <param name="localEndPoint">�����ս�㡣</param>
        /// <param name="remoteEndPoint">Զ���ս�㡣</param>
        protected One2OneUdpClient(uint remoteCode, IPEndPoint localEndPoint, IPEndPoint remoteEndPoint)
        {
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
        /// ��ȡԶ�̽ڵ����͡�
        /// </summary>
        public abstract NodeType RemoteType { get; }
        /// <summary>
        /// ��ȡԶ�̽ڵ�ı�š�
        /// </summary>
        public uint RemoteCode { get; private set; }

        /// <summary>
        /// ��ȡ����ͨ���ս�㡣
        /// </summary>
        public IPEndPoint LocalEndPoint { get; protected set; }
        /// <summary>
        /// ��ȡԶ��ͨ���ս�㡣
        /// </summary>
        public IPEndPoint RemoteEndPoint { get; protected set; }

        /// <summary>
        /// ��ȡ UdpClient ����
        /// </summary>
        protected UdpClient LocalClient { get; private set; }

        /// <summary>
        /// �Ƿ��������׽��ְ󶨵�����ʹ���еĵ�ַ��
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

        #region "Abstract methods"
        /// <summary>
        /// ������������дʱ�����ڴ�����ʼ���¼���
        /// </summary>
        protected virtual void OnOpen() { }

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
            else if(timeSpan.TotalSeconds >= 30)
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
                // ���Դ�UdpClient
                if (this.LocalClient == null
                    && (DateTime.Now - _lastIpCheckTime).Minutes > 1)
                {
                    _lastIpCheckTime = DateTime.Now;
                    this.OpenUdpClient();
                }

                // �������״̬��
                this.UpdateConnectionState();
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

        private void UpdateConnectionState()
        {
            if (this.RemoteDataExpiredTime <= 0) return;

            if (_lastDataReceiveTime == DateTime.MinValue) return;

            if ((DateTime.Now - _lastDataReceiveTime).TotalSeconds >= this.RemoteDataExpiredTime)
            {
                _lastDataReceiveTime = DateTime.MinValue;

                // ֪ͨ�����жϡ�
                var args = new CommStateChangedEventArgs(false, 0, this.RemoteCode, this.RemoteType);
                this.NotifyCommStateChanged(args);
            }
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
                if (LocalClient != null)
                {
                    IPEndPoint remoteEP = null;
                    var stream = LocalClient.EndReceive(ar, ref remoteEP);

                    // ����RemoteEndPoint
                    if(this.RemoteEndPoint == null) this.RemoteEndPoint = remoteEP;

                    // ��������ʱ�䡣
                    var preConnected = _lastDataReceiveTime == DateTime.MinValue;
                    _lastDataReceiveTime = DateTime.Now;

                    // ֪ͨ����״̬
                    if (!preConnected)
                    {
                        var args = new CommStateChangedEventArgs(true, 0, this.RemoteCode, this.RemoteType);
                        this.NotifyCommStateChanged(args);
                    }

                    // ���������д������ݡ�
                    this.HandleDataReceived(stream, remoteEP);
                }
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

        private void NotifyCommStateChanged(CommStateChangedEventArgs args)
        {
            try
            {
                if (this.CommStateChanged != null) this.CommStateChanged(this, args);
            }
            catch (System.Exception /*ex*/)
            {
            }
        }
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
        }

        /// <summary>
        /// �������ݡ�
        /// </summary>
        /// <param name="data">��Ҫ���͵����ݡ�</param>
        public void Send(byte[] data)
        {
            if (this.LocalClient == null || this.RemoteEndPoint == null) return;

            this.LocalClient.Send(data, data.Length, this.RemoteEndPoint);
        }
        #endregion
    }
}