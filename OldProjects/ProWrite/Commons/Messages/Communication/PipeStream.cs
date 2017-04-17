using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace System.Communication
{
    public sealed class ThreadAffinity
    {
        private readonly int m_threadId;

        public ThreadAffinity()
        {
            m_threadId = Thread.CurrentThread.ManagedThreadId;
        }

        public void Check()
        {
            if (Thread.CurrentThread.ManagedThreadId != m_threadId)
            {
                var msg = String.Format(
                    "Call to class with affinity to thread {0} detected from thread {1}.",
                    m_threadId,
                    Thread.CurrentThread.ManagedThreadId);
                throw new InvalidOperationException(msg);
            }
        }
    }

    public class PipeStream<T>:DisposableObject
    {
        private readonly ThreadAffinity m_affinity = new ThreadAffinity();
        private readonly Queue<T> m_queue = new Queue<T>();
        private readonly AutoResetEvent m_event = new AutoResetEvent(false);
        private readonly object m_lock = new object();
        private bool m_inputClosed;


        protected override void Dispose(bool disposing)
        {
            lock (m_lock)
            {
                m_inputClosed = true;
            }

            m_event.Close();
            base.Dispose(disposing);
        }

        public T Read()
        {
            m_affinity.Check();
            lock (m_lock)
            {
                if (m_queue.Count > 0)
                {
                    return m_queue.Dequeue();
                }
            }

            T data;
            do
            {
                m_event.WaitOne();
            } while (!TryRead(out data));

            return data;
        }

        public bool TryRead(out T value)
        {
            m_affinity.Check();
            lock (m_lock)
            {
                if (m_queue.Count == 0)
                {
                    value = default(T);
                    return false;
                }

                value = m_queue.Dequeue();
                return true;
            }
        }



        public void Write(T data)
        {
            lock (m_lock)
            {
                if (m_inputClosed)
                {
                    throw new InvalidOperationException("Input end of channel is closed");
                }

                m_queue.Enqueue(data);
            }

            m_event.Set();
        }

        public void Close()
        {
            Dispose();
        }
    }
}
