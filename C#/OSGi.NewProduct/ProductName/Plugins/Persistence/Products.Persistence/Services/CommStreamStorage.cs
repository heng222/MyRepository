/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ŀ���ƣ���SIL2��֤�ı�׼��ATS
//
// �� �� �ˣ�zhangheng
// �������ڣ�2018-1-5 16:11:11 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Concurrent;
using System.Linq;
using System.Windows.Forms;

using Acl.Collections;
using Acl.CommStreamLog;
using Acl.CommStreamLog.Data;
using Acl.MessageBus;

using Products.Infrastructure.Entities;
using Products.Infrastructure.Events;
using Products.Infrastructure.Log;
using Products.Infrastructure.Messages;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Types;
using Products.Persistence;
using Products.Resource;

namespace Products.Persistence.Services
{
    /// <summary>
    /// ͨ�����洢��������
    /// </summary>
    class CommStreamStorage : Acl.CompositeDisposable
    {
        #region "Field"
        /// <summary>
        /// Key = RemoteType+Remote device ID
        /// </summary>
        private ConcurrentDictionary<string, ICommStreamLogWriter> _commLogWriters =
            new ConcurrentDictionary<string, ICommStreamLogWriter>();
        
        /// <summary>
        /// һ������أ����ڴ�Ž�Ҫ��������ݡ�
        /// </summary>
        private ProductCache<CommLogCreatedEventArgs> _logCache = new ProductCache<CommLogCreatedEventArgs>(3000);
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯����
        /// </summary>
        public CommStreamStorage(ushort logExpiredDays = 10)
        {
            this.LogExpiredDays = logExpiredDays;

            // ��ʼ������ء�
            _logCache.ProductCreated += OnProductCreated;
            _logCache.Open();

            // ���Ĳ˵�����Ϣ 
            GlobalMessageBus.SubscribeCommLogRollover(OnRolloverCommLog);
            GlobalMessageBus.SubscribeCommLogCreated(OnCommStreamCreated);
        }

        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡ/������־��Ч������
        /// </summary>
        public ushort LogExpiredDays { get; private set; }
        #endregion

        #region "Override methods"
        protected override void Dispose(bool disposing)
        {
            if (_logCache != null)
            {
                if (disposing)
                {
                    _logCache.Close();
                }

                _logCache = null;
            }

            base.Dispose(disposing);
        }
        #endregion

        #region "Private methods"
        private void OnCommStreamCreated(object sender, CommLogCreatedEventArgs args)
        {
            try
            {
                // ��黺�����Ԫ�صĸ�����������ֵ���¼��
                if (_logCache.Count > 500)
                {
                    LogUtility.Warning(string.Format("ͨ������־����صĸ����Ѵﵽ {0} ����", _logCache.Count));
                }

                _logCache.AddProduct(args);
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }

        private void OnProductCreated(object sender, ProductCreatedEventArgs<CommLogCreatedEventArgs> e)
        {
            try
            {
                e.Products.ToList().ForEach(p =>
                {
                    ICommStreamLogWriter writer = null;
                    var logKey = string.Format("{0}{1}-{2}{3}", p.LocalNodeType, p.LocalNodeCode, p.RemoteNodeType, p.RemoteNodeCode);

                    try
                    {
                        if (!_commLogWriters.TryGetValue(logKey, out writer))
                        {
                            writer = CreateStreamLogWriter(p);
                            _commLogWriters.GetOrAdd(logKey, writer);
                        }

                        // build a new record and write it to IO.
                        var record = CommStreamLogFile.NewRecord();
                        record.Content = p.Data;
                        record.Header.Direction = p.IsIncomingData ? StreamDirection.Input : StreamDirection.Output;

                        writer.Write(record);
                    }
                    catch (System.Exception ex)
                    {
                        LogUtility.Error(string.Format("����ͨ������־ʱ�� {0}�������쳣��{1}��\r\n ִ��Rollover������", logKey, ex));

                        if (writer != null) writer.Rollover();
                    }
                });
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(string.Format("����ATSͨ����־ʱ�����쳣��{0}", ex));
            }
        }

        private ICommStreamLogWriter CreateStreamLogWriter(CommLogCreatedEventArgs args)
        {
            var localNodeName = this.GetDeviceName(args.LocalNodeType, args.LocalNodeCode);
            var remoteNodeName = this.GetDeviceName(args.RemoteNodeType, args.RemoteNodeCode);

            var logPath = string.Format(@"{0}\L{1}.{2}_R{3}.{4}", LogSettings.CommLogBasePath, args.LocalNodeCode, localNodeName, args.RemoteNodeCode, remoteNodeName);
            var logKey = string.Format("{0}{1}-{2}{3}", args.LocalNodeType, args.LocalNodeCode, args.RemoteNodeType, args.RemoteNodeCode);

            // 
            var ipc =  CommLogHelper.GetParserCode(args.LocalNodeType, args.RemoteNodeType, true);
            var opc = CommLogHelper.GetParserCode(args.LocalNodeType, args.RemoteNodeType, false);

            // 
            var logSettings = LogFileSettings.CreateV11(logKey, logPath, ipc, opc);
            logSettings.FileNamePrefix = GetFileNamePrefix(args.LocalNodeCode, localNodeName, args.RemoteNodeCode, remoteNodeName);
            logSettings.FileNameSuffix = "";
            logSettings.ExpiredDays = this.LogExpiredDays;
            logSettings.FileDescription = GetFileDescription(localNodeName, remoteNodeName);

            // 
            return CommStreamLogManager.CreateLogWriter(logSettings);
        }
        
        private void OnRolloverCommLog(object sender, EventArgs e)
        {
            try
            {
                _commLogWriters.Values.ForEach(p => p.Rollover());
                LogUtility.Info("����ͨ������־��Rollover��");
            }
            catch (System.Exception ex)
            {
                LogUtility.Warning(ex.ToString());
            }
        }        

        private string GetFileNamePrefix(uint localNodeCode, string localNodeName, uint remoteNodeCode, string remoteNodeName)
        {
            return string.Format("L{0}.{1}_R{2}.{3}",
                localNodeCode, remoteNodeName,
                remoteNodeCode, remoteNodeName);
        }

        private string GetDeviceName(NodeType nodeType, uint nodeCode)
        {
            var theNode = GlobalServices.Repository.Where<SystemNode>(p => p.Code == nodeCode).FirstOrDefault();
            if(theNode == null)
            {
                return nodeType.ToString();
            }
            else
            {
                return theNode.Name;
            }
        }

        private string GetFileDescription(string localNodeName, string remoteNodeName)
        {
            var desciption = string.Format("��{0}��{1} �� {2} ͨ������־", 
                ProductResources.ProjectChsName, localNodeName, remoteNodeName);

            return desciption;
        }
        
        /// <summary>
        /// ��ATP���ת��Ϊ�׶������ơ�
        /// </summary>
        public string ConvertVobcCodeToName(uint vobcCode)
        {
            var localCode = (byte)(vobcCode & 0xFF);

            var quotient = (localCode + 1) / 2;
            var remainder = localCode % 2;

            return string.Format("Vobc{0}��.{1}��", quotient, remainder != 0 ? "1" : "2");
        }
        #endregion

        #region "Public methods"
        #endregion

    }
}
