using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace System.Communication.Messaging
{
    class MessageSchedule<TMessage> : IDisposable where TMessage : IComparable<TMessage>
    {
        private Thread thread;
        private IPriortyQueue<MessageInfo<TMessage>> MessageQueue;
        private bool IsRuning;
        public MessageSchedule(IPriortyQueue<MessageInfo<TMessage>> queue, IMessageRouter host)
        {
            if (!queue.IsSynchronized)
                MessageQueue = PriorityQueue<MessageInfo<TMessage>>.Synchronized(queue);
            else
                MessageQueue = queue;

            thread = new Thread(delegate()
            {
                IsRuning = true;
                MessageInfo<TMessage> item = null;
                while (true)
                {
                    if (!IsRuning)
                        return;

                    while (MessageQueue.Count > 0)
                    {
                        //Thread.Sleep(MillisecondsTimeout);
                        if ((item = MessageQueue.Pop()) != null)
                            host.Send(item.Sender, item.Message, true);
                        Thread.Sleep(MillisecondsTimeout);
                    }
                }
            });
            thread.IsBackground = true;
            thread.Name = "MessageManager.MessageQueue.Thread";
            thread.Start();
        }
        public int MillisecondsTimeout = 50;

        public void Post(object sender, TMessage msg)
        {
            MessageQueue.Put(new MessageInfo<TMessage>(sender, msg));
        }

        public void Dispose()
        {
            if (thread != null)
            {
                IsRuning = false;
                Thread.Sleep(MillisecondsTimeout);
                thread = null;
            }
            if (MessageQueue != null)
            {
                MessageQueue.Clear();
                MessageQueue = null;
            }
        }
    }
}
