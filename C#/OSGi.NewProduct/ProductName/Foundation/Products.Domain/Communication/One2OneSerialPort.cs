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

using System.IO.Ports;

using Products.Infrastructure.Preference;
using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// 1对1串口通信类。
    /// </summary>
    public abstract class One2OneSerialPort : CommEndPoint
    {
        #region "Field"
        private SerialPortSettings _spSetting;
        private SerialPort _serialPort;
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

        /// <summary>
        /// 构造函数。
        /// </summary>
        /// <param name="spSetting">本地串口配置。</param>
        /// <param name="localType">本地节点类型。</param>
        /// <param name="localCode">本地节点编号。</param>
        protected One2OneSerialPort(SerialPortSettings spSetting,
            NodeType localType, uint localCode)
            : base(localType, localCode)
        {
            _spSetting = spSetting;
        }

        #endregion

        #region "Properties"

        /// <summary>
        /// 获取远程节点类型。
        /// </summary>
        public abstract NodeType RemoteType { get; }
        /// <summary>
        /// 获取远程节点的编号。
        /// </summary>
        public abstract uint RemoteCode { get; }

        /// <summary>
        /// 在派生类中重写时，用于设置串口读取数据超时时间（毫秒）。
        /// </summary>
        protected virtual int ReadTimeout { get { return 2000; } }

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

        ///<inheritdoc/>
        protected override NodeType GetRemoteType(uint remoteCode)
        {
            return this.RemoteType;
        }
        #endregion

        #region "Private methods"

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

                // DataTransfer 消息通知。
                this.PublishDataTransferEvent(this.RemoteType, this.RemoteCode, true, data);

                // CommLogCreated 消息通知。
                this.PublishCommLogCreateEvent(this.RemoteType, this.RemoteCode, true, data);

                // 验证数据是否有效。
                if (!this.VerifyData(data)) return;

                // 在派生类中处理数据。
                this.HandleDataReceived(data);

                // 更新连接时间。
                this.RefreshCommState(this.RemoteCode);
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

            // DataTransfer消息通知。
            this.PublishDataTransferEvent(this.RemoteType, this.RemoteCode, false, data);

            // CommLogCreated 消息通知。
            this.PublishCommLogCreateEvent(this.RemoteType, this.RemoteCode, false, data);

            // 写串口。
            _serialPort.Write(data, 0, data.Length);
        }
        #endregion
    }
}
