/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：03/02/2018 15:13:41 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称 2019-2015 保留所有权利
//
//----------------------------------------------------------------*/
using System;
using System.Linq;

namespace Products.Domain.Utility
{
    /// <summary>
    /// 序号管理器
    /// </summary>
    public sealed class SeqNoManager
    {
        #region "Field"

        #endregion

        #region "Constructor"
        /// <summary>
        /// 带参数的构造函数
        /// </summary>
        /// <param name="minSeqNo">最小发送序号。</param>
        /// <param name="maxSeqNo">最大发送序号。</param>
        /// <param name="seqNoThreshold">序号检查阈值。</param>
        public SeqNoManager(uint minSeqNo, uint maxSeqNo, byte seqNoThreshold)
        {
            if (seqNoThreshold == 0)
            {
                throw new ArgumentException("序号窗口必须大于0。");
            }

            if (maxSeqNo == 0)
            {
                throw new ApplicationException("最大发送序号不能为零。");
            }

            this.SendSeqSyncLock = new object();
            this.AckSeqSyncLock = new object();

            this.MinSendSeqNo = minSeqNo;
            this.MaxSendSeq = maxSeqNo;
            this.SeqNoThreshold = seqNoThreshold;
            this.Initlialize();
        }

        #endregion

        #region "Properties"

        /// <summary>
        /// 获取可用的最小发送序号。
        /// </summary>
        public uint MinSendSeqNo { get; private set; }
        /// <summary>
        /// 获取可用的最大发送序号
        /// </summary>
        public uint MaxSendSeq { get; private set; }
        /// <summary>
        /// 获取/设置一个值，用于表示消息序列检查参数N。N-1是代表允许丢失消息的数量。
        /// 需要配置N值，N值等于或大于1。
        /// </summary>
        public byte SeqNoThreshold { get; private set; }

        /// <summary>
        /// 获取发送序号的版本
        /// </summary>
        public uint SendSeqVersion { get; private set; }
        /// <summary>
        /// 获取当前的发送序号
        /// </summary>
        public uint SendSeqNo { get; set; }
        /// <summary>
        /// 获取发送序号的同步锁。
        /// </summary>
        public object SendSeqSyncLock { get; private set; }
        /// <summary>
        /// 获取上一个发送序号。
        /// </summary>
        public uint LastSendSeqNo { get; private set; }

        /// <summary>
        /// 获取当前的确认序号版本
        /// </summary>
        public uint AckSeqVersion { get; private set; }
        /// <summary>
        /// 获取当前的确认序号
        /// </summary>
        public uint AckSeqNo { get; private set; }
        /// <summary>
        /// 获取确认序号的同步锁。
        /// </summary>
        public object AckSeqSyncLock { get; private set; }

        #endregion


        #region "Private methods"
        private uint NextValue(uint currentValue)
        {
            if (currentValue >= this.MaxSendSeq)
            {
                currentValue = this.MinSendSeqNo;
            }
            else
            {
                currentValue++;
            }

            return currentValue;
        }

        private uint[] NextRange(uint currentValue, byte range)
        {
            var result = new uint[range];

            for (int i = 0; i < result.Length; i++)
            {
                result[i] = this.NextValue(currentValue);
                currentValue = result[i];
            }

            return result;
        }
        #endregion

        #region "Public methods"
        /// <summary>
        /// 初始化
        /// </summary>
        public void Initlialize()
        {
            ResetSendSeq();
            ResetAckSeq(0, 0);
        }

        /// <summary>
        /// 重置发送序号
        /// </summary>
        public void ResetSendSeq()
        {
            lock (this.SendSeqSyncLock)
            {
                this.SendSeqVersion = (uint)Environment.TickCount;

                this.SendSeqNo = this.MinSendSeqNo;
                this.LastSendSeqNo = this.MinSendSeqNo;
            }
        }

        /// <summary>
        /// 使用指定的值重置确认序号版本与确认序号
        /// </summary>
        /// <param name="seqVersion">确认序号版本</param>
        /// <param name="seqNo">确认序号</param>
        public void ResetAckSeq(uint seqVersion, uint seqNo)
        {
            lock (this.AckSeqSyncLock)
            {
                this.AckSeqVersion = seqVersion;
                this.AckSeqNo = seqNo;
            }
        }

        /// <summary>
        /// 返回并更新当前的发送序号。
        /// </summary>
        /// <returns>更新前的发送序号。</returns>
        public uint GetAndUpdateSendSeq()
        {
            lock (this.SendSeqSyncLock)
            {
                this.LastSendSeqNo = this.SendSeqNo;

                this.SendSeqNo = this.NextValue(this.LastSendSeqNo);

                return this.LastSendSeqNo;
            }
        }

        /// <summary>
        /// 使用指定的值更新确认序号
        /// </summary>
        /// <param name="newSeq">新的确认序号</param>
        public void UpdateAckSeq(uint newSeq)
        {
            lock (this.AckSeqSyncLock)
            {
                this.AckSeqNo = newSeq;
            }
        }

        /// <summary>
        /// 判断指定的发送序号版本是否有效。
        /// </summary>
        /// <returns>true表示有效</returns>
        public bool IsSeqVersionValid(uint seqVer)
        {
            return (seqVer != 0 && seqVer == this.AckSeqVersion);
        }

        /// <summary>
        /// 判断指定的发送序号是否为期待的值。
        /// </summary>
        /// <param name="latestSeqNo">最新的发送序号</param>
        /// <returns>true表示为期待的值</returns>
        public bool IsExpected(uint latestSeqNo)
        {
            lock (this.AckSeqSyncLock)
            {
                var expectedRange = this.NextRange(this.AckSeqNo, this.SeqNoThreshold);

                return expectedRange.Contains(latestSeqNo);
            }
        }

        ///// <summary>
        ///// 判断指定的发送序号是否已超过容许的范围。
        ///// </summary>
        ///// <param name="latestSeqNo">最新的发送序号</param>
        ///// <returns>true超过容许的范围，false表示没有超过容许的范围。</returns>
        //public bool IsBeyondRange(uint latestSeqNo)
        //{
        //    lock (this.AckSeqSyncLock)
        //    {
        //        if (latestSeqNo > this.AckSeq)
        //        {
        //            return (latestSeqNo - this.AckSeq) > this.SeqNoThreshold;
        //        }
        //        else
        //        {
        //            var delta = Math.Abs((long)latestSeqNo - (long)this.AckSeq);
        //            var referValue = this.MaxSendSeq / 2;

        //            if (delta > referValue)
        //            {
        //                // 表示收到的序号大于“消息序列检查参数N”。
        //                return ((this.MaxSendSeq - this.AckSeq) + latestSeqNo + 1) > this.SeqNoThreshold;
        //            }
        //            else
        //            {
        //                // 表示收到的序号是一个旧值，丢弃即可。
        //                return false;
        //            }
        //        }
        //    }
        //}
        #endregion

    }
}
