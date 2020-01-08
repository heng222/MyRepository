/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：请输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2010-6-20 15:44:22 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/
using System;
using System.IO;
using Acl.Utility;
using System.Text;
using Products.Infrastructure.Protocol.Framework;
using Products.Infrastructure.Log;

namespace Products.Infrastructure.Protocol
{
    /// <summary>
    /// 内部通讯协议帧定义
    /// </summary>
    public abstract class InternalFrame : ProtocolFrame, IStreamFrame, IStreamFrame<byte>
    {
        /// <summary>
        /// 特殊站码,表示全部车站
        /// </summary>
        public const UInt16 AllStations = 0xFFFF;

        /// <summary>
        /// 帧头长度
        /// </summary>
        public const byte FrameHeadLen = 20;

        /// <summary>
        /// 表示信息的有效期（单位：10毫秒）
        /// </summary>
        public const uint PeriodicFramevalidTime = 300;

        /// <summary>
        /// 控制命令的有效期（单位：10毫秒）
        /// </summary>
        public const uint CommandFrameValidTime = 500;

        #region "Field"

        /// <summary>
        /// 帧头
        /// </summary>
        public const byte FrameHead = 0x44;

        /// <summary>
        /// 获取协议帧的主类型
        /// </summary>
        public InternalFrameType MajorType { get; private set; }

        /// <summary>
        /// 获取协议帧的次类型
        /// </summary>
        public byte MinorType { get; private set; }

        /// <summary>
        /// 获取版本号
        /// </summary>
        public InternalFrameVersion Version { get; set; }

        /// <summary>
        /// 预留
        /// </summary>
        private byte[] _reserved = new byte[4];

        /// <summary>
        /// 获取/设置站码。
        /// 当协议帧由中心发往车站时，此字段表示目的车站编号；当协议帧由车站发往中心时，此字段表示源车站编号。
        /// </summary>
        public UInt16 StationCode { get; set; }

        /// <summary>
        /// 获取/设置协议帧的源设备编号
        /// </summary>
        public UInt32 SourceDeviceCode { get; set; }

        /// <summary>
        /// 获取/设置协议帧的目标设备编号
        /// </summary>
        public UInt32 DestDeviceCode { get; set; }

        /// <summary>
        /// 获取数据域长度
        /// </summary>
        public ushort DataFieldLength { get; private set; }
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="majorType">主类型</param>
        /// <param name="minorType">次类型</param>
        protected InternalFrame(InternalFrameType majorType, byte minorType)
        {
            this.MajorType = majorType;
            this.MinorType = minorType;

            //this.Version = NewestVersion;
        }
        #endregion

        #region "Properties"
        #endregion

        #region "Virtual methods"
        /// <summary>
        /// 得到一个字节流，用于表示数据域。
        /// </summary>
        /// <returns>一个字节Buffer。</returns>
        protected abstract byte[] GetDataFieldBytes();
        /// <summary>
        /// 从指定的数据流中解析数据域
        /// </summary>
        /// <param name="bytes">字节流</param>
        /// <param name="startIndex">数据域字段的起始地址</param>
        protected abstract void ParseDataField(byte[] bytes, int startIndex);
        /// <summary>
        /// 获取内容的字符串描述
        /// </summary>
        public abstract string GetDataFieldDescription();
        #endregion

        #region "Overried methods"
        /// <summary>
        /// 返回表示当前帧的字符串描述。
        /// </summary>
        /// <returns>String型的描述信息。</returns>
        public override string ToString()
        {
            var sb = new StringBuilder(512);

            sb.AppendFormat("\r\n  起始标志 = 0x{0:X2}", FrameHead);
            sb.AppendFormat("\r\n    主类型 = {0}", this.MajorType);
            sb.AppendFormat("\r\n    次类型 = {0}", this.MinorType);
            sb.AppendFormat("\r\n    版本号 = {0}", this.Version);
            sb.AppendFormat("\r\n  车站编号 = {0}", this.StationCode);
            sb.AppendFormat("\r\n消息源编号 = {0}", this.SourceDeviceCode);
            sb.AppendFormat("\r\n目的地编号 = {0}", this.DestDeviceCode);
            sb.AppendFormat("\r\n数据域长度 = {0}", this.DataFieldLength);
            sb.AppendFormat("\r\n数据域描述：{0}", GetDataFieldDescription());

            return sb.ToString();
        }
        #endregion
        
        #region "Public methods"
        #endregion

        #region IStreamFrame 成员
        /// <summary>
        /// 得到内部数据帧对应的字节流
        /// </summary>
        /// <returns>协议帧对应的网络数据流</returns>
        public byte[] GetStream()
        {
            var stream = new MemoryStream(1000);
            using (var binWriter = new BinaryWriter(stream))
            {
                // Head
                binWriter.Write(FrameHead);

                // message type
                binWriter.Write((byte)this.MajorType);

                // sub type
                binWriter.Write(this.MinorType);

                // version
                binWriter.Write((byte)this.Version);

                // reserved
                binWriter.Write(_reserved);

                //// 站码
                //binWriter.Write(AtsFrameEncoding.ToNetUInt16(StationCode));

                //// 源设备ID
                //binWriter.Write(AtsFrameEncoding.ToNetInt32((int)SourceDeviceCode));

                //// 目的ID
                //binWriter.Write(AtsFrameEncoding.ToNetInt32((int)DestDeviceCode));

                //// GET DATA FIELD
                //byte[] dataField = GetDataFieldBytes();

                //// data field length
                //if (dataField == null)
                //{
                //    this.DataFieldLength = 0;
                //}
                //else
                //{
                //    this.DataFieldLength = (ushort)dataField.Length;
                //}
                //binWriter.Write(AtsFrameEncoding.ToNetInt16((short)this.DataFieldLength));

                //// data field.
                //if (dataField != null)
                //{
                //    binWriter.Write(dataField);
                //}

                return stream.ToArray();
            }
        }

        /// <summary>
        /// 解析指定的包含协议帧的数据流。
        /// </summary>
        /// <param name="stream">数据流</param>
        /// <param name="startIndex">协议帧头部所在的位置</param>
        public void ParseStream(byte[] stream, int startIndex)
        {
            if (stream.Length < InternalFrame.FrameHeadLen)
            {
                throw new ArgumentException("指定的数据流长度不够。");
            }

            // Head
            if (stream[startIndex] != FrameHead)
            {
                throw new Exception("指定的字节流非内部协议帧");
            }
            startIndex++;

            // message type
            this.MajorType = (InternalFrameType)(stream[startIndex++]);

            // sub type
            this.MinorType = stream[startIndex++];

            // version
            this.Version = (InternalFrameVersion)(stream[startIndex++]);
            //if (this.Version > InternalFrameVersion.First)
            //{
            //    throw new InvalidOperationException(string.Format("无法解析的高版本协议,当前版本号{0},接收数据帧版本号{1}",
            //        NewestVersion, this.Version));
            //}

            // reserved
            startIndex += _reserved.Length;

            //// 站码
            //this.StationCode = (ushort)AtsFrameEncoding.ToHostInt16(stream, startIndex);
            //startIndex += 2;

            //// 源设备ID
            //this.SourceDeviceCode = (uint)AtsFrameEncoding.ToHostInt32(stream, startIndex);
            //startIndex += 4;

            //// 目的ID
            //this.DestDeviceCode = (uint)AtsFrameEncoding.ToHostInt32(stream, startIndex);
            //startIndex += 4;

            //// Data field length
            //this.DataFieldLength = (ushort)AtsFrameEncoding.ToHostInt16(stream, startIndex);
            //startIndex += 2;

            // Data field
            ParseDataField(stream, startIndex);
        }

        /// <summary>
        /// 获取消息对应的数据流。
        /// </summary>
        /// <returns>协议对应的数据流</returns>
        Array IStreamFrame.GetStream()
        {
            return this.GetStream();
        }

        /// <summary>
        /// 解析指定的数据流。
        /// </summary>
        /// <param name="stream">数据流</param>
        /// <param name="startIndex">协议数据在数据流中的起始地址</param>
        void IStreamFrame.ParseStream(Array stream, int startIndex)
        {
            this.ParseStream(stream as byte[], startIndex);
        }

        #endregion
    }
}
