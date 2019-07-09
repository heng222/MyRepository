/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ĺ�˾����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2016-5-11 8:55:47 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Linq;
using System.Windows.Forms;
using Acl.CommStreamLog;
using Acl.CommStreamLog.Data;
using Products.Domain.Utility;
using Products.Infrastructure.Log;
using Products.Infrastructure.Messages;
using Products.Resource;

namespace Products.Domain.Persistence
{
    /// <summary>
    /// ͨ������־�洢����
    /// </summary>
    public class CommLogStorage : IDisposable
    {
        #region "Filed"

        private bool _disposed = false;

        private IDisposable _observer = null;

        /// <summary>
        /// ��־����
        /// </summary>
        private string _logKey = "";

        /// <summary>
        /// ͨ������־д�ӿ�
        /// </summary>
        private ICommStreamLogWriter _commLogWriter = null;

        /// <summary>
        /// д������
        /// </summary>
        private object _writeSyncLock = new object();
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯����
        /// </summary>
        /// <param name="logKey">ͨ����־�ؼ��֣��ο�LoggerNames����</param>
        /// <param name="ipc">��������������š�</param>
        /// <param name="opc">�������������š�</param>
        /// <param name="expiredDays">ͨ����־�Ĺ���������</param>
        public CommLogStorage(string logKey, CommLogParserCode ipc, CommLogParserCode opc, int expiredDays)
        {
            if (string.IsNullOrWhiteSpace(logKey))
            {
                throw new ArgumentException();
            }

            System.IO.Path.GetInvalidPathChars().ToList().ForEach(p =>
            {
                if (logKey.Contains(p))
                {
                    throw new ArgumentException(string.Format("logKey({0})�а���·���в�����ʹ�õ��ַ�{1}��",
                        logKey, p));
                }
            });

            // 
            _logKey = logKey;
            this.CreateCommStreamLog((uint)ipc, (uint)opc, expiredDays);

            // ���ġ�����ͨ����־�ļ�����Ϣ
            _observer = GlobalMessageBus.SubscribeCommLogRollover(OnRolloverCommLog);
        }

        /// <summary>
        /// �սắ����
        /// </summary>
        ~CommLogStorage()
        {
            this.Dispose(false);
        }
        #endregion

        #region "Properties"
        #endregion

        #region "Virtual methods"
        /// <summary>
        /// ������������дʱ������������������ʹ�õ���Դ��
        /// </summary>
        /// <param name="disposing">�Ƿ��ͷ��й���Դ</param>
        protected virtual void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (disposing)
                {
                    _observer.Dispose();
                }

                _disposed = false;
            }
        }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        private void CreateCommStreamLog(uint ipc, uint opc, int expiredDays)
        {
            var logPath = string.Format("{0}{1}", LogSettings.CommLogBasePath, _logKey);

            var logSettings = LogFileSettings.CreateV11(_logKey, logPath, ipc, opc);
            logSettings.FileNamePrefix = _logKey;
            logSettings.FileNameSuffix = "";
            logSettings.ExpiredDays = expiredDays;
            logSettings.FileDescription = string.Format("��{0}���� {1} ͨ������־", ProductResources.ProjectChsName, _logKey);

            _commLogWriter = CommStreamLogManager.CreateLogWriter(logSettings);
        }

        private void OnRolloverCommLog(object sender, EventArgs e)
        {
            try
            {
                var tip = string.Format("ȷ�Ϲ����������˲������ر��� {0} ��ͨ����־�ļ���", _logKey);

                var rcCode = MessageBox.Show(tip, "��ʾ", MessageBoxButtons.YesNo, MessageBoxIcon.Question);

                if (rcCode == DialogResult.Yes)
                {
                    _commLogWriter.Rollover();
                }
            }
            catch (System.Exception ex)
            {
                LogUtility.Warning(ex.ToString());
            }
        }
        #endregion

        #region "Public methods"
        /// <summary>
        /// ����ͨ������־��
        /// </summary>
        /// <param name="stream">��Ҫ���������</param>
        /// <param name="direction">������</param>
        public void SaveCommLog(byte[] stream, StreamDirection direction)
        {
            lock (_writeSyncLock)
            {
                var record = CommStreamLogFile.NewRecord();
                record.Content = stream;
                record.Header.Direction = direction;
                _commLogWriter.Write(record);
            }
        }

        /// <summary>
        /// �ͷ���Դ��
        /// </summary>
        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }
        #endregion

    }
}
