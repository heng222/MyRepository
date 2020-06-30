/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�01/15/2013 15:02:55 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;

using Products.Infrastructure.Events;

namespace Products.Infrastructure.Protocol.Framework
{
    /// <summary>
    /// һ���۲����ӿڣ����ڴ�����յ���Э��֡��
    /// </summary>
    public interface IIncomingFrameObserver<TProtocol>
        where TProtocol : ProtocolFrame
    {
        /// <summary>
        /// Э��֡������ں���
        /// </summary>
        /// <param name="e">�¼���������</param>
        void HandleFrame(FrameIncomingEventArgs<TProtocol> e);
    }
}
