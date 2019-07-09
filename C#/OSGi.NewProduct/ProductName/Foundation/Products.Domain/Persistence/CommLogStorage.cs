/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入你的公司名称
//
// 创 建 人：zhangheng
// 创建日期：2016-5-11 8:55:47 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称 2009，保留所有权利
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
    /// 通信流日志存储器。
    /// </summary>
    public class CommLogStorage : IDisposable
    {
        #region "Filed"

        private bool _disposed = false;

        private IDisposable _observer = null;

        /// <summary>
        /// 日志键。
        /// </summary>
        private string _logKey = "";

        /// <summary>
        /// 通信流日志写接口
        /// </summary>
        private ICommStreamLogWriter _commLogWriter = null;

        /// <summary>
        /// 写入锁。
        /// </summary>
        private object _writeSyncLock = new object();
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数。
        /// </summary>
        /// <param name="logKey">通信日志关键字（参考LoggerNames）。</param>
        /// <param name="ipc">输入流解析器编号。</param>
        /// <param name="opc">输出流解析器编号。</param>
        /// <param name="expiredDays">通信日志的过期天数。</param>
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
                    throw new ArgumentException(string.Format("logKey({0})中包含路径中不可以使用的字符{1}。",
                        logKey, p));
                }
            });

            // 
            _logKey = logKey;
            this.CreateCommStreamLog((uint)ipc, (uint)opc, expiredDays);

            // 订阅“滚动通信日志文件”消息
            _observer = GlobalMessageBus.SubscribeCommLogRollover(OnRolloverCommLog);
        }

        /// <summary>
        /// 终结函数。
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
        /// 在派生类中重写时，用于清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">是否释放托管资源</param>
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
            logSettings.FileDescription = string.Format("【{0}】与 {1} 通信流日志", ProductResources.ProjectChsName, _logKey);

            _commLogWriter = CommStreamLogManager.CreateLogWriter(logSettings);
        }

        private void OnRolloverCommLog(object sender, EventArgs e)
        {
            try
            {
                var tip = string.Format("确认滚动操作？此操作将关闭与 {0} 的通信日志文件。", _logKey);

                var rcCode = MessageBox.Show(tip, "提示", MessageBoxButtons.YesNo, MessageBoxIcon.Question);

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
        /// 保存通信流日志。
        /// </summary>
        /// <param name="stream">将要保存的流。</param>
        /// <param name="direction">流方向。</param>
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
        /// 释放资源。
        /// </summary>
        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }
        #endregion

    }
}
