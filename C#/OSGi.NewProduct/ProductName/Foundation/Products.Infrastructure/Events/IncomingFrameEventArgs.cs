/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2013-7-25 14:33:39 
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
    /// Э��֡�����¼������ࡣ
    /// ��ʾ�ռ����յ�Э��֡��
    /// </summary>
    public class IncomingFrameEventArgs<TProtocol> : EventArgs where TProtocol : ProtocolFrame
    {
        #region "Filed"
        #endregion

        #region "Constructor"
        /// <summary>
        /// ����һ��Э��֡������Ϣ���¼�������
        /// </summary>
        /// <param name="frame">Э��֡��������ã�����Ϊ��</param>
        /// <param name="bytesStream">Э��֡��Ӧ���ֽ���</param>
        /// <param name="remoteDeviceId">Э��֡���ͷ����豸ID</param>
        /// <param name="timeDelay">����ʱ��</param>
        public IncomingFrameEventArgs(TProtocol frame,
            byte[] bytesStream,
            UInt32 remoteDeviceId,
            UInt32 timeDelay = 0)
        {
            this.Frame = frame;
            this.BytesStream = bytesStream;
            this.RemoteDeviceID = remoteDeviceId;
            this.TimeDelay = timeDelay;
        }
        /// <summary>
        /// ����һ��Э��֡������Ϣ���¼�������
        /// </summary>
        /// <param name="bytesStream">Э��֡��Ӧ���ֽ���</param>
        /// <param name="remoteDeviceId">Э��֡���ͷ����豸ID</param>
        /// <param name="timeDelay">����ʱ��</param>
        public IncomingFrameEventArgs(byte[] bytesStream,
            UInt32 remoteDeviceId,
            UInt32 timeDelay = 0)
        {
            this.BytesStream = bytesStream;
            this.RemoteDeviceID = remoteDeviceId;
            this.TimeDelay = timeDelay;
        }
        #endregion

        #region "Properties"
        
        /// <summary>
        /// �Է��豸ID����Э��֡���ͷ���ID��
        /// </summary>
        public UInt32 RemoteDeviceID { get; set; }

        /// <summary>
        /// ��ʾЭ��֡��ʱ�ӣ���λ��10���롣
        /// </summary>
        public UInt32 TimeDelay { get; set; }

        /// <summary>
        /// ��ʾ���յ���Э��֡������Ϊ�գ�
        /// </summary>
        public TProtocol Frame { get; set; }

        /// <summary>
        /// ����/��ȡЭ��֡�������ֽ�����Ϊ������ʱ��ʾ�����⹫��Э��֡���ݡ�
        /// </summary>
        public byte[] BytesStream { get; set; }

        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion


    }
}
