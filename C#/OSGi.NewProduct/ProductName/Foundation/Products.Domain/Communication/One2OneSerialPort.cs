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
    /// 1��1����ͨ���ࡣ
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
        /// ���캯����
        /// </summary>
        /// <param name="spSetting">���ش������á�</param>
        protected One2OneSerialPort(SerialPortSettings spSetting)
        {
            _spSetting = spSetting;
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
        public abstract uint LocalCode { get; }

        /// <summary>
        /// ��ȡԶ�̽ڵ����͡�
        /// </summary>
        public abstract NodeType RemoteType { get; }
        /// <summary>
        /// ��ȡԶ�̽ڵ�ı�š�
        /// </summary>
        public abstract uint RemoteCode { get; }

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
        /// ������������дʱ���������ô��ڶ�ȡ���ݳ�ʱʱ�䣨���룩��
        /// </summary>
        protected virtual int ReadTimeout { get { return 2000; } }

        /// <summary>
        /// һ���¼�������Զ�̽ڵ�ͨ��״̬�ı�ʱ������
        /// </summary>
        public event EventHandler<CommStateChangedEventArgs> CommStateChanged;
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
                // ��ȡ���ݡ�
                var count = _serialPort.BytesToRead;
                if (count <= 0) return;

                // ��ȡ�������ݡ�
                var data = new byte[count];
                _serialPort.Read(data, 0, count);

                // ��Ϣ֪ͨ��
                if (this.PublishDataIncoming)
                {
                    var args = new DataIncomingEventArgs(data, this.LocalType, this.LocalCode, this.RemoteType, this.RemoteCode);
                    GlobalMessageBus.PublishDataIncoming(args, this);
                }

                // ��֤�����Ƿ���Ч��
                if (!this.VerifyData(data)) return;

                // ���������д������ݡ�
                this.HandleDataReceived(data);

                // ��������ʱ�䡣
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
        /// �򿪡�
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

            // ��Ϣ֪ͨ��
            if (this.PublishDataOutgoing)
            {
                var args = new DataOutgoingEventArgs(data, this.LocalType, this.LocalCode, this.RemoteType, this.RemoteCode);
                GlobalMessageBus.PublishDataOutgoing(args, this);
            }

            // д���ڡ�
            _serialPort.Write(data, 0, data.Length);
        }
        #endregion
    }
}
