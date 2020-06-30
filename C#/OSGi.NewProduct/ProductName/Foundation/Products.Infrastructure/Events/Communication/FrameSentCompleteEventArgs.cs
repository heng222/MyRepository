/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-5-15 10:50:33 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;

using Products.Infrastructure.Protocol.Framework;
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// 协议帧发送完成事件参数类。
    /// 用于送件人完成任务后通知给发件人。
    /// </summary>
    public class FrameSentCompleteEventArgs<TProtocol> : EventArgs where TProtocol : ProtocolFrame
    {
        #region "Field"
        /// <summary>
        /// 事件关联的目的地。
        /// </summary>
        private List<uint> _destDevices = new List<uint>();
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数。
        /// </summary>
        /// <param name="frame">事件关联的协议帧。</param>
        /// <param name="sentRc">发送结果。</param>
        /// <param name="dests">事件关联的目的地。</param>
        public FrameSentCompleteEventArgs(TProtocol frame, FrameSentResult sentRc, IEnumerable<UInt32> dests)
        {
            this.Frame = frame;
            this.SentResult = sentRc;
            this._destDevices.AddRange(dests);
        }
        #endregion

        #region "Properties"

        /// <summary>
        /// 获取事件关联的协议帧。
        /// </summary>
        public TProtocol Frame { get; private set; }

        /// <summary>
        /// 发送结果。
        /// 默认值FrameSentResult.Unknown。
        /// </summary>
        public FrameSentResult SentResult { get; set; }

        /// <summary>
        /// 获取目的设备ID列表
        /// </summary>
        public IEnumerable<UInt32> DestsCode { get { return _destDevices; } }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

    }
}
