/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ĺ�˾����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2016-5-11 13:13:43 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
//
//----------------------------------------------------------------*/

using System;

namespace Products.Infrastructure.Messages
{
    /// <summary>
    /// ��ʾ������Ϣ��������߽ӿڡ�
    /// </summary>
    /// <typeparam name="TEventArgs"></typeparam>
    public interface ISingleTopicMessageBus<TEventArgs> where TEventArgs : EventArgs
    {
        /// <summary>
        /// ��ȡ��Ϣ���߹��������⡣
        /// </summary>
        string Topic { get; }

        /// <summary>
        /// ������Ϣ��
        /// </summary>
        void Publish(TEventArgs args, object sender = null);

        /// <summary>
        /// ������Ϣ��
        /// </summary>
        /// <returns>һ����ȡ�����ĵĽӿڡ�</returns>
        IDisposable Subscribe(Action<object, TEventArgs> handler);
    }
}
