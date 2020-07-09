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

using System.IO.Ports;

using Products.Infrastructure.Preference;
using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// 1��1����ͨ���ࡣ
    /// </summary>
    public abstract class One2OneSerialPort : CommEndPoint
    {
        #region "Field"
        private SerialPortSettings _spSetting;
        private SerialPort _serialPort;
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯����
        /// </summary>
        /// <param name="spSetting">���ش������á�</param>
        protected One2OneSerialPort(SerialPortSettings spSetting)
        {
            _spSetting = spSetting;
        }

        /// <summary>
        /// ���캯����
        /// </summary>
        /// <param name="spSetting">���ش������á�</param>
        /// <param name="localType">���ؽڵ����͡�</param>
        /// <param name="localCode">���ؽڵ��š�</param>
        protected One2OneSerialPort(SerialPortSettings spSetting,
            NodeType localType, uint localCode)
            : base(localType, localCode)
        {
            _spSetting = spSetting;
        }

        #endregion

        #region "Properties"

        /// <summary>
        /// ��ȡԶ�̽ڵ����͡�
        /// </summary>
        public abstract NodeType RemoteType { get; }
        /// <summary>
        /// ��ȡԶ�̽ڵ�ı�š�
        /// </summary>
        public abstract uint RemoteCode { get; }

        /// <summary>
        /// ������������дʱ���������ô��ڶ�ȡ���ݳ�ʱʱ�䣨���룩��
        /// </summary>
        protected virtual int ReadTimeout { get { return 2000; } }

        #endregion

        #region "Abstract methods"
        /// <summary>
        /// ������������дʱ��������֤�����Ƿ���Ч��
        /// </summary>
        /// <param name="data">�յ������ݡ�</param>
        /// <returns>true��ʾ��������Ч�ģ�false ��ʾ��������Ч�ġ�</returns>
        protected virtual bool VerifyData(byte[] data) { return true; }

        /// <summary>
        /// ������������дʱ�����ڴ����յ������ݡ�
        /// </summary>
        /// <param name="data">�յ������ݡ�</param>
        protected abstract void HandleDataReceived(byte[] data);
        #endregion

        #region "Override methods"
        /// <summary>
        /// ������������дʱ�������ͷ���Դ��
        /// </summary>
        /// <param name="disposing">�ͷ��Ƿ��й���Դ��</param>
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
                // ��ȡ���ݡ�
                var count = _serialPort.BytesToRead;
                if (count <= 0) return;

                // ��ȡ�������ݡ�
                var data = new byte[count];
                _serialPort.Read(data, 0, count);

                // DataTransfer ��Ϣ֪ͨ��
                this.PublishDataTransferEvent(this.RemoteType, this.RemoteCode, true, data);

                // CommLogCreated ��Ϣ֪ͨ��
                this.PublishCommLogCreateEvent(this.RemoteType, this.RemoteCode, true, data);

                // ��֤�����Ƿ���Ч��
                if (!this.VerifyData(data)) return;

                // ���������д������ݡ�
                this.HandleDataReceived(data);

                // ��������ʱ�䡣
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
        /// �򿪡�
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
                this.Log.Error(string.Format($"��{_spSetting.Name}ʧ�ܣ�{ex.Message}"));
            }
        }

        /// <summary>
        /// �������ݡ�
        /// </summary>
        /// <param name="data">��Ҫ���͵����ݡ�</param>
        public virtual void Send(byte[] data)
        {
            if (_serialPort == null || !_serialPort.IsOpen) return;

            // DataTransfer��Ϣ֪ͨ��
            this.PublishDataTransferEvent(this.RemoteType, this.RemoteCode, false, data);

            // CommLogCreated ��Ϣ֪ͨ��
            this.PublishCommLogCreateEvent(this.RemoteType, this.RemoteCode, false, data);

            // д���ڡ�
            _serialPort.Write(data, 0, data.Length);
        }
        #endregion
    }
}
