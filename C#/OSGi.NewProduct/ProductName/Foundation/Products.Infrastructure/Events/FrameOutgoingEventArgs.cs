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

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// Э��֡����¼������ࡣ
    /// ���ڷ����������ͼ��˽�Э��֡���͵�Ŀ�ĵء�
    /// </summary>
    public class FrameOutgoingEventArgs<TProtocol> : EventArgs where TProtocol : ProtocolFrame
    {
        #region "Filed"
        /// <summary>
        /// ���ָ����Ŀ�ĵأ����ٸ���·�ɹ������ת����
        /// </summary>
        private List<uint> _destDevices = new List<uint>();
        #endregion

        #region "Constructor"
        /// <summary>
        /// ����һ��Э��֡������Ϣ���¼�������
        /// </summary>
        /// <param name="frame">Э��֡��������ã�����Ϊ��</param>
        public FrameOutgoingEventArgs(TProtocol frame)
        {
            if (frame == null) throw new ArgumentNullException();

            this.Frame = frame;

            this.BytesStream = new byte[0];
            this.ExtraDelay = 0;
            this.ForcedSend = false;
        }
        /// <summary>
        /// ����һ��Э��֡������Ϣ���¼�������
        /// </summary>
        /// <param name="bytesStream">Э��֡��Ӧ���ֽ���</param>
        public FrameOutgoingEventArgs(byte[] bytesStream)
        {
            if (bytesStream == null) throw new ArgumentNullException();

            this.BytesStream = bytesStream;

            this.Frame = null;
            this.ExtraDelay = 0;
            this.ForcedSend = false;
        }
        #endregion

        #region "Properties"
                
        /// <summary>
        /// ��ȡĿ���豸ID�б�
        /// </summary>
        public uint[] DestDeviceIDs
        {
            get { return _destDevices.ToArray(); }
        }

        /// <summary>
        /// ��ȡһ��ֵ�����ڱ�ʾĿ�ĵ��Ƿ�Ϊ�ա�
        /// ���ָ����Ŀ�ĵأ����ٸ���·�ɹ������ת����
        /// </summary>
        public bool IsDestEmpty
        {
            get { return _destDevices.Count == 0; }
        }
        
        /// <summary>
        /// ��ʾ��Ҫ���͵�Э��֡������Ϊ�ա�
        /// </summary>
        public TProtocol Frame { get; set; }

        /// <summary>
        /// ����/��ȡЭ��֡�������ֽ�����Ϊ������ʱ��ʾ�����⹫��Э��֡���ݡ�
        /// </summary>
        public byte[] BytesStream { get; set; }

        /// <summary>
        /// ��ȡ/����һ��ֵ�����ڱ�ʾЭ��֡�ĸ���ʱ�ӡ�
        /// һ������Э��֡ת��ʱ��
        /// </summary>
        public uint ExtraDelay { get; set; }

        /// <summary>
        /// �Ƿ�ǿ�Ʒ��͡�
        /// Ĭ��ֵΪfalse����ʾ�������ڵ�Ϊ����ʱ�ŷ���Э��֡��Ϊtrueʱ����ʾ��������״̬��ǿ�Ʒ��͡�
        /// </summary>
        public bool ForcedSend { get; set; }
        #endregion

        #region "Override methods"
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
}
