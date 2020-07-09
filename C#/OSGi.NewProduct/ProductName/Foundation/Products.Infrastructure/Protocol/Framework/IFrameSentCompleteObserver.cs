/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2014-6-23 14:27:02 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

using Products.Infrastructure.Events;

namespace Products.Infrastructure.Protocol.Framework
{
    /// <summary>
    /// һ���۲����ӿڣ����ڴ���Э��֡��������¼���
    /// </summary>
    public interface IFrameSentCompleteObserver<TProtocol>
        where TProtocol : ProtocolFrame
    {
        /// <summary>
        /// ����Ҫ���͵�Э��֡��
        /// </summary>
        /// <param name="e">OutgoingFrameArgs�¼���������</param>
        void HandleFrame(FrameSentCompleteEventArgs<TProtocol> e);
    }
}
