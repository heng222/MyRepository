/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ĺ�˾����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-5-15 10:50:33 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;
using Products.Infrastructure.Protocol.Framework;

namespace Products.Infrastructure.Events
{
    /// <summary>
    /// Э��֡���ͽ������
    /// </summary>
    public enum FrameSentResult : byte
    {
        /// <summary>
        /// δ֪��
        /// </summary>
        Unknown,
        /// <summary>
        /// ���ͳɹ���
        /// </summary>
        Successful,
        /// <summary>
        /// ����ʧ�ܡ�
        /// </summary>
        Failed,
    }

    /// <summary>
    /// Э��֡��������¼������ࡣ
    /// �����ͼ�����������֪ͨ�������ˡ�
    /// </summary>
    public class FrameSentCompleteEventArgs<TProtocol> : EventArgs where TProtocol : ProtocolFrame
    {
        #region "Field"
        /// <summary>
        /// �¼�������Ŀ�ĵء�
        /// </summary>
        private List<uint> _destDevices = new List<uint>();
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯����
        /// </summary>
        /// <param name="frame">�¼�������Э��֡��</param>
        /// <param name="sentRc">���ͽ����</param>
        /// <param name="dests">�¼�������Ŀ�ĵء�</param>
        public FrameSentCompleteEventArgs(TProtocol frame, FrameSentResult sentRc, IEnumerable<UInt32> dests)
        {
            this.Frame = frame;
            this.SentResult = sentRc;
            this._destDevices.AddRange(dests);
        }
        #endregion

        #region "Properties"

        /// <summary>
        /// ��ȡ�¼�������Э��֡��
        /// </summary>
        public TProtocol Frame { get; private set; }       

        /// <summary>
        /// ���ͽ����
        /// Ĭ��ֵFrameSentResult.Unknown��
        /// </summary>
        public FrameSentResult SentResult { get; set; }

        /// <summary>
        /// ��ȡĿ���豸ID�б�
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
