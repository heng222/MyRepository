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

using System;
using System.Collections.Generic;
using System.Text;

using Products.Infrastructure.Events;

namespace Products.Infrastructure.Protocol.Framework
{
    /// <summary>
    /// һ���۲����ӿڣ����ڴ���Ҫ���͵�Э��֡��
    /// </summary>
    public interface IOutgoingFrameObserver<TProtocol>
        where TProtocol : ProtocolFrame
    {
        /// <summary>
        /// ����Ҫ���͵�Э��֡��
        /// </summary>
        /// <param name="e">OutgoingFrameArgs�¼���������</param>
        void HandleFrame(FrameOutgoingEventArgs<TProtocol> e);
    }
}
