/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ĺ�˾����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2014-6-23 14:24:19 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
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
    /// ��������¼������ࡣ
    /// </summary>
    public class DataOutgoingEventArgs : EventArgs
    {
        #region "Field"
        /// <summary>
        /// Ŀ�ĵء�
        /// </summary>
        private List<uint> _destDevices = new List<uint>();
        #endregion

        #region "Constructor"
        /// <summary>
        /// ����һ��Э��֡������Ϣ���¼�������
        /// </summary>
        public DataOutgoingEventArgs(byte[] data,
            NodeType localType, uint localID,
            NodeType remoteType)
        {
            if (data == null) throw new ArgumentNullException();

            this.ExtraDelay = 0;

            this.Data = data;
            this.LocalType = localType;
            this.LocalCode = localID;
            this.RemoteType = remoteType;
        }

        /// <summary>
        /// ����һ��Э��֡������Ϣ���¼�������
        /// </summary>
        public DataOutgoingEventArgs(byte[] data,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteCode)
            : this(data, localType, localID, remoteType)
        {
            _destDevices.Add(remoteCode);
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡ���ؽڵ����͡�
        /// </summary>
        public NodeType LocalType { get; set; }
        /// <summary>
        /// �����豸ID��
        /// </summary>
        public uint LocalCode { get; set; }

        /// <summary>
        /// ��ȡ/����Ŀ���豸���͡�
        /// </summary>
        public NodeType RemoteType { get; set; }
        /// <summary>
        /// ��ȡĿ���豸ID�б�
        /// </summary>
        public IEnumerable<uint> RemoteCodes { get { return _destDevices; } }

        /// <summary>
        /// ��ȡһ��ֵ�����ڱ�ʾĿ�ĵ��Ƿ�Ϊ�ա�
        /// ���ָ����Ŀ�ĵأ����ٸ���·�ɹ������ת����
        /// </summary>
        public bool IsDestEmpty { get { return _destDevices.Count == 0; } }

        /// <summary>
        /// ����/��ȡЭ��֡�������ֽ�����
        /// </summary>
        public byte[] Data { get; set; }

        /// <summary>
        /// ��ȡ/����һ��ֵ�����ڱ�ʾЭ��֡�ĸ���ʱ�ӣ���λ�����룩��
        /// </summary>
        public uint ExtraDelay { get; set; }

        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        /// <summary>
        /// ���һ��Ŀ�ĵ�
        /// </summary>
        /// <param name="destId"></param>
        public void AddDest(uint destId)
        {
            if (!_destDevices.Contains(destId))
            {
                _destDevices.Add(destId);
            }
        }

        /// <summary>
        /// ����Ŀ�ĵ�ַ
        /// </summary>
        /// <param name="destID"></param>
        public void SetDest(uint destID)
        {
            this.ClearDest();
            _destDevices.Add(destID);
        }

        /// <summary>
        /// ���Ŀ�ĵ�
        /// </summary>
        public void ClearDest()
        {
            _destDevices.Clear();
        }
        #endregion

    }

    /// <summary>
    /// Э��֡����¼������ࡣ
    /// </summary>
    public class FrameOutgoingEventArgs : DataOutgoingEventArgs
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯����
        /// </summary>
        public FrameOutgoingEventArgs(byte[] data,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteCode)
            : base(data, localType, localID, remoteType, remoteCode)
        {

        }

        /// <summary>
        /// ���캯����
        /// </summary>
        public FrameOutgoingEventArgs(ProtocolFrame frame, byte[] data,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteCode)
            : base(data, localType, localID, remoteType, remoteCode)
        {
            this.Frame = frame;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡ��Ҫ���͵�Э��֡������Ϊ�ա�
        /// </summary>
        public ProtocolFrame Frame { get; set; }
        #endregion
    }

    /// <summary>
    /// Э��֡����¼������ࡣ
    /// </summary>
    public class FrameOutgoingEventArgs<TProtocol> : FrameOutgoingEventArgs where TProtocol : ProtocolFrame
    {
        #region "Field"
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯����
        /// </summary>
        public FrameOutgoingEventArgs(byte[] data,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteCode)
            : base(data, localType, localID, remoteType, remoteCode)
        {

        }

        /// <summary>
        /// ���캯����
        /// </summary>
        public FrameOutgoingEventArgs(TProtocol frame, byte[] data,
            NodeType localType, uint localID,
            NodeType remoteType, UInt32 remoteCode)
            : base(data, localType, localID, remoteType, remoteCode)
        {
            this.Frame = frame;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡ��Ҫ���͵�Э��֡������Ϊ�ա�
        /// </summary>
        public new TProtocol Frame { get; set; }
        #endregion
    }
}
