/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2010-6-20 15:44:22 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
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
    /// �ڲ�ͨѶЭ��֡����
    /// </summary>
    public abstract class InternalFrame : ProtocolFrame, IStreamFrame, IStreamFrame<byte>
    {
        /// <summary>
        /// ����վ��,��ʾȫ����վ
        /// </summary>
        public const UInt16 AllStations = 0xFFFF;

        /// <summary>
        /// ֡ͷ����
        /// </summary>
        public const byte FrameHeadLen = 20;

        /// <summary>
        /// ��ʾ��Ϣ����Ч�ڣ���λ��10���룩
        /// </summary>
        public const uint PeriodicFramevalidTime = 300;

        /// <summary>
        /// �����������Ч�ڣ���λ��10���룩
        /// </summary>
        public const uint CommandFrameValidTime = 500;

        #region "Field"

        /// <summary>
        /// ֡ͷ
        /// </summary>
        public const byte FrameHead = 0x44;

        /// <summary>
        /// ��ȡЭ��֡��������
        /// </summary>
        public InternalFrameType MajorType { get; private set; }

        /// <summary>
        /// ��ȡЭ��֡�Ĵ�����
        /// </summary>
        public byte MinorType { get; private set; }

        /// <summary>
        /// ��ȡ�汾��
        /// </summary>
        public InternalFrameVersion Version { get; set; }

        /// <summary>
        /// Ԥ��
        /// </summary>
        private byte[] _reserved = new byte[4];

        /// <summary>
        /// ��ȡ/����վ�롣
        /// ��Э��֡�����ķ�����վʱ�����ֶα�ʾĿ�ĳ�վ��ţ���Э��֡�ɳ�վ��������ʱ�����ֶα�ʾԴ��վ��š�
        /// </summary>
        public UInt16 StationCode { get; set; }

        /// <summary>
        /// ��ȡ/����Э��֡��Դ�豸���
        /// </summary>
        public UInt32 SourceDeviceCode { get; set; }

        /// <summary>
        /// ��ȡ/����Э��֡��Ŀ���豸���
        /// </summary>
        public UInt32 DestDeviceCode { get; set; }

        /// <summary>
        /// ��ȡ�����򳤶�
        /// </summary>
        public ushort DataFieldLength { get; private set; }
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯��
        /// </summary>
        /// <param name="majorType">������</param>
        /// <param name="minorType">������</param>
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
        /// �õ�һ���ֽ��������ڱ�ʾ������
        /// </summary>
        /// <returns>һ���ֽ�Buffer��</returns>
        protected abstract byte[] GetDataFieldBytes();
        /// <summary>
        /// ��ָ�����������н���������
        /// </summary>
        /// <param name="bytes">�ֽ���</param>
        /// <param name="startIndex">�������ֶε���ʼ��ַ</param>
        protected abstract void ParseDataField(byte[] bytes, int startIndex);
        /// <summary>
        /// ��ȡ���ݵ��ַ�������
        /// </summary>
        public abstract string GetDataFieldDescription();
        #endregion

        #region "Overried methods"
        /// <summary>
        /// ���ر�ʾ��ǰ֡���ַ���������
        /// </summary>
        /// <returns>String�͵�������Ϣ��</returns>
        public override string ToString()
        {
            var sb = new StringBuilder(512);

            sb.AppendFormat("\r\n  ��ʼ��־ = 0x{0:X2}", FrameHead);
            sb.AppendFormat("\r\n    ������ = {0}", this.MajorType);
            sb.AppendFormat("\r\n    ������ = {0}", this.MinorType);
            sb.AppendFormat("\r\n    �汾�� = {0}", this.Version);
            sb.AppendFormat("\r\n  ��վ��� = {0}", this.StationCode);
            sb.AppendFormat("\r\n��ϢԴ��� = {0}", this.SourceDeviceCode);
            sb.AppendFormat("\r\nĿ�ĵر�� = {0}", this.DestDeviceCode);
            sb.AppendFormat("\r\n�����򳤶� = {0}", this.DataFieldLength);
            sb.AppendFormat("\r\n������������{0}", GetDataFieldDescription());

            return sb.ToString();
        }
        #endregion
        
        #region "Public methods"
        #endregion

        #region IStreamFrame ��Ա
        /// <summary>
        /// �õ��ڲ�����֡��Ӧ���ֽ���
        /// </summary>
        /// <returns>Э��֡��Ӧ������������</returns>
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

                //// վ��
                //binWriter.Write(AtsFrameEncoding.ToNetUInt16(StationCode));

                //// Դ�豸ID
                //binWriter.Write(AtsFrameEncoding.ToNetInt32((int)SourceDeviceCode));

                //// Ŀ��ID
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
        /// ����ָ���İ���Э��֡����������
        /// </summary>
        /// <param name="stream">������</param>
        /// <param name="startIndex">Э��֡ͷ�����ڵ�λ��</param>
        public void ParseStream(byte[] stream, int startIndex)
        {
            if (stream.Length < InternalFrame.FrameHeadLen)
            {
                throw new ArgumentException("ָ�������������Ȳ�����");
            }

            // Head
            if (stream[startIndex] != FrameHead)
            {
                throw new Exception("ָ�����ֽ������ڲ�Э��֡");
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
            //    throw new InvalidOperationException(string.Format("�޷������ĸ߰汾Э��,��ǰ�汾��{0},��������֡�汾��{1}",
            //        NewestVersion, this.Version));
            //}

            // reserved
            startIndex += _reserved.Length;

            //// վ��
            //this.StationCode = (ushort)AtsFrameEncoding.ToHostInt16(stream, startIndex);
            //startIndex += 2;

            //// Դ�豸ID
            //this.SourceDeviceCode = (uint)AtsFrameEncoding.ToHostInt32(stream, startIndex);
            //startIndex += 4;

            //// Ŀ��ID
            //this.DestDeviceCode = (uint)AtsFrameEncoding.ToHostInt32(stream, startIndex);
            //startIndex += 4;

            //// Data field length
            //this.DataFieldLength = (ushort)AtsFrameEncoding.ToHostInt16(stream, startIndex);
            //startIndex += 2;

            // Data field
            ParseDataField(stream, startIndex);
        }

        /// <summary>
        /// ��ȡ��Ϣ��Ӧ����������
        /// </summary>
        /// <returns>Э���Ӧ��������</returns>
        Array IStreamFrame.GetStream()
        {
            return this.GetStream();
        }

        /// <summary>
        /// ����ָ������������
        /// </summary>
        /// <param name="stream">������</param>
        /// <param name="startIndex">Э���������������е���ʼ��ַ</param>
        void IStreamFrame.ParseStream(Array stream, int startIndex)
        {
            this.ParseStream(stream as byte[], startIndex);
        }

        #endregion
    }
}
