using System;
using System.Threading;

using Acl.Core;
using Acl.Log;

using Products.Infrastructure.Events;
using Products.Infrastructure.Messages;
using Products.Infrastructure.Types;

namespace Products.Domain.Communication
{
    /// <summary>
    /// 表示一个通信终结点。
    /// </summary>
    public abstract class CommEndPoint : Acl.CompositeDisposable
    {
        #region "Filed"
        private DataValidityChecker<string> _commStateChecker = null;

        #endregion

        #region "Constructor"
        /// <summary>
        /// 无参构造函数。
        /// </summary>
        protected CommEndPoint()
        {
            this.StartCommStateChecker();
        }

        /// <summary>
        /// 构造一个One2OneUdpClient对象。
        /// </summary>
        /// <param name="localType">本地节点类型。</param>
        protected CommEndPoint(NodeType localType)
            : this()
        {
            this.LocalType = localType;
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
        public virtual NodeType LocalType { get; protected set; }

        /// <summary>
        /// 是否允许接收数据？
        /// </summary>
        public virtual bool AllowReceive { get { return true; } }

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
        /// 是否在全局总线上发布CommLogCreated消息？
        /// </summary>
        protected virtual bool PublishCommLogCreated { get { return false; } }

        /// <summary>
        /// 一个事件，当与远程节点通信状态改变时引发。
        /// </summary>
        public event EventHandler<CommStateChangedEventArgs> CommStateChanged;
        #endregion

        #region "Abastract methods"
        /// <summary>
        /// 在派生类中重写时，用于获取远程节点的类型。
        /// </summary>
        /// <param name="remoteCode">远程节点编号。</param>
        /// <returns>远程节点的编号。</returns>
        protected abstract NodeType GetRemoteType(uint remoteCode);
        #endregion

        #region "Protected methods"
        /// <summary>
        /// 刷新指定远程节点的通信状态。
        /// </summary>
        /// <param name="localCode">本地节点编号。</param>
        /// <param name="remoteCode">远程节点编号。</param>
        protected void RefreshCommState(uint localCode, uint remoteCode)
        {
            if (_commStateChecker != null)
            {
                var key = string.Format($"{localCode},{remoteCode}");
                _commStateChecker.Refresh(key);
            }
        }

        /// <summary>
        /// 在全局消息总线上发布数据传输事件。
        /// </summary>
        protected void PublishDataTransferEvent(NodeType localType, uint localCode,
            NodeType remoteType, uint remoteCode, 
            bool isIncoming, byte[] data)
        {
            try
            {
                if (isIncoming && this.PublishDataIncoming)
                {
                    var args = new DataIncomingEventArgs(data, localType, localCode, remoteType, remoteCode);
                    GlobalMessageBus.PublishDataIncoming(args, this);
                }
                else if (!isIncoming && this.PublishDataOutgoing)
                {
                    var args = new DataOutgoingEventArgs(data, localType, localCode, remoteType, remoteCode);
                    GlobalMessageBus.PublishDataOutgoing(args, this);
                }
            }
            catch (Exception)
            {
            }
        }

        /// <summary>
        /// 在全局消息总线上发布通信日志产生事件。
        /// </summary>
        protected void PublishCommLogCreateEvent(NodeType localType, uint localCode, 
            NodeType remoteType, 
            uint remoteCode, bool isIncoming, byte[] data)
        {
            try
            {
                if (!this.PublishCommLogCreated) return;

                var args = new CommLogCreatedEventArgs(localType, localCode, remoteType, remoteCode, isIncoming, data);
                GlobalMessageBus.PublishCommLogCreated(args);
            }
            catch (Exception)
            {
            }
        }
        #endregion

        #region "Private methods"
        private void StartCommStateChecker()
        {
            if (this.PublishCommStateChanged && this.RemoteDataExpiredTime > 0 && _commStateChecker == null)
            {
                _commStateChecker = new DataValidityChecker<string>(this.RemoteDataExpiredTime);
                this.AddDisposable(_commStateChecker);
                _commStateChecker.DataValidityChanged += CommStateChecker_DataValidityChanged;

                _commStateChecker.Open();
            }
        }

        private void CommStateChecker_DataValidityChanged(object sender, DataValidityChangedEventArgs<string> e)
        {
            try
            {
                if (this.PublishCommStateChanged)
                {
                    var tmpData = e.Data.ToUInt32Array(10);
                    var localCode = tmpData[0];
                    var remoteCode = tmpData[1];

                    var remoteType = this.GetRemoteType(remoteCode);

                    var args = new CommStateChangedEventArgs(e.Avaliable, this.LocalType, localCode, remoteType, remoteCode);
                    GlobalMessageBus.PublishCommStateChanged(args);

                    if (this.CommStateChanged != null) this.CommStateChanged(this, args);
                }
            }
            catch (Exception /*ex*/)
            {
            }
        }
        #endregion

        #region "public methods"
        #endregion
    }
}
