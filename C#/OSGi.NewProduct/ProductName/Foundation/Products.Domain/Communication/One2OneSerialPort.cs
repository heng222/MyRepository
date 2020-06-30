/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-2 10:43:04 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.IO.Ports;
using System.Threading;
using System.Threading.Tasks;

using Acl;
using Acl.Core;
using Acl.Log;

using Products.Infrastructure.Events;
using Products.Infrastructure.Messages;
using Products.Infrastructure.Preference;
using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// 1对1串口通信类。
    /// </summary>
    public abstract class One2OneSerialPort : CompositeDisposable
    {
        #region "Field"
        private SerialPortSettings _spSetting;
        private SerialPort _serialPort;

        private DataValidityChecker<uint> _commStateChecker = null;
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数。
        /// </summary>
        /// <param name="spSetting">本地串口配置。</param>
        protected One2OneSerialPort(SerialPortSettings spSetting)
        {
            _spSetting = spSetting;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取日志接口。
        /// </summary>
        protected abstract ILog Log { get; }

        /// <summary>
        /// 获取本地节点类型。
        /// </summary>
        public abstract NodeType LocalType { get; }
        /// <summary>
        /// 获取本地节点的编号。
        /// </summary>
        public abstract uint LocalCode { get; }

        /// <summary>
        /// 获取远程节点类型。
        /// </summary>
        public abstract NodeType RemoteType { get; }
        /// <summary>
        /// 获取远程节点的编号。
        /// </summary>
        public abstract uint RemoteCode { get; }

        /// <summary>
        /// 获取远程数据的有效期N（秒），当N秒没有收到远程数据时，通信中断。
        /// 小于等于0时表示不检查。
        /// </summary>
        protected virtual int RemoteDataExpiredTime { get { return Timeout.Infinite; } }

        /// <summary>
        /// 是否在全局总线上发布CommStateChanged消息？
        /// </summary>
        protected virtual bool PublishCommStateChanged { get { return true; } }
        /// <summary>
        /// 是否在全局总线上发布DataIncoming消息？
        /// </summary>
        protected virtual bool PublishDataIncoming { get { return true; } }
        /// <summary>
        /// 是否在全局总线上发布DataOutgoing消息？
        /// </summary>
        protected virtual bool PublishDataOutgoing { get { return true; } }

        /// <summary>
        /// 在派生类中重写时，用于设置串口读取数据超时时间（毫秒）。
        /// </summary>
        protected virtual int ReadTimeout { get { return 2000; } }

        /// <summary>
        /// 一个事件，当与远程节点通信状态改变时引发。
        /// </summary>
        public event EventHandler<CommStateChangedEventArgs> CommStateChanged;
        #endregion

        #region "Abstract methods"
        /// <summary>
        /// 在派生类中重写时，用于验证数据是否有效。
        /// </summary>
        /// <param name="data">收到的数据。</param>
        /// <returns>true表示数据是有效的，false 表示数据是无效的。</returns>
        protected virtual bool VerifyData(byte[] data) { return true; }

        /// <summary>
        /// 在派生类中重写时，用于处理收到的数据。
        /// </summary>
        /// <param name="data">收到的数据。</param>
        protected abstract void HandleDataReceived(byte[] data);
        #endregion

        #region "Override methods"
        /// <summary>
        /// 在派生类中重写时，用于释放资源。
        /// </summary>
        /// <param name="disposing">释放是否托管资源？</param>
        protected override void Dispose(bool disposing)
        {
            this.CloseSerialPort();

            base.Dispose(disposing);
        }
        #endregion

        #region "Private methods"

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
                    var args = new CommStateChangedEventArgs(e.Avaliable, this.LocalType, this.LocalCode, this.RemoteType, e.Data);
                    GlobalMessageBus.PublishCommStateChanged(args);

                    if (this.CommStateChanged != null) this.CommStateChanged(this, args);
                }
            }
            catch (System.Exception /*ex*/)
            {
            }
        }

        private SerialPort CreateSerialPort(SerialPortSettings spSettings)
        {
            SerialPort serialPort = null;

            try
            {
                // create a SerialPort object
                serialPort = new SerialPort(spSettings.Name,
                    spSettings.BaudRate, spSettings.Parity,
                    spSettings.Databits, spSettings.Stopbits);

                serialPort.ReadTimeout = this.ReadTimeout;
            }
            catch (System.Exception /*ex*/)
            {
                if (serialPort != null) serialPort.Dispose();
                throw;
            }

            return serialPort;
        }

        private void CloseSerialPort()
        {
            if (_serialPort != null)
            {
                var tempSerialPort = _serialPort;
                _serialPort = null;
                tempSerialPort.Close();
            }
        }

        private void OnSerialPortDataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                // 读取数据。
                var count = _serialPort.BytesToRead;
                if (count <= 0) return;

                // 读取串口数据。
                var data = new byte[count];
                _serialPort.Read(data, 0, count);

                // 消息通知。
                if (this.PublishDataIncoming)
                {
                    var args = new DataIncomingEventArgs(data, this.LocalType, this.LocalCode, this.RemoteType, this.RemoteCode);
                    GlobalMessageBus.PublishDataIncoming(args, this);
                }

                // 验证数据是否有效。
                if (!this.VerifyData(data)) return;

                // 在派生类中处理数据。
                this.HandleDataReceived(data);

                // 更新连接时间。
                if (_commStateChecker != null)
                {
                    _commStateChecker.Refresh(this.RemoteCode);
                }
            }
            catch (System.Exception ex)
            {
                this.Log.Error(ex);
            }
        }
        #endregion

        #region "Public methods"
        /// <summary>
        /// 打开。
        /// </summary>
        public void Open()
        {
            try
            {
                _serialPort = this.CreateSerialPort(_spSetting);

                _serialPort.DataReceived += OnSerialPortDataReceived;
                _serialPort.Open();

                this.StartCommStateChecker();
            }
            catch (System.Exception ex)
            {
                this.CloseSerialPort();
                this.Log.Error(string.Format($"打开{_spSetting.Name}失败，{ex.Message}"));
            }
        }

        /// <summary>
        /// 发送数据。
        /// </summary>
        /// <param name="data">将要发送的数据。</param>
        public virtual void Send(byte[] data)
        {
            if (_serialPort == null || !_serialPort.IsOpen) return;

            // 消息通知。
            if (this.PublishDataOutgoing)
            {
                var args = new DataOutgoingEventArgs(data, this.LocalType, this.LocalCode, this.RemoteType, this.RemoteCode);
                GlobalMessageBus.PublishDataOutgoing(args, this);
            }

            // 写串口。
            _serialPort.Write(data, 0, data.Length);
        }
        #endregion
    }
}
