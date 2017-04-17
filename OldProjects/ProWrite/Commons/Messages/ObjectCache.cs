using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.ComponentModel;

namespace System
{
   
    /// <summary>
    /// Object cache class
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public class ObjectCache<T> : IDisposable
    {

        private Delegate m_loader;
        private object[] m_args;
        private T m_item = default(T);
        private bool m_state = false;
        private readonly ManualResetEvent m_resetEvent;

        public ObjectCache(Delegate loader, params object[] args)
        {
            Check.Require(loader != null);

            this.m_loader = loader;
            m_args = args;
            m_resetEvent = new ManualResetEvent(false);
        }

        public T Item
        {
            get
            {
                DoLoad();
                m_resetEvent.WaitOne();
                return m_item;
            }
        }

        public bool IsCompleted
        {
            get { return m_state; }
        }


        private void DoLoad()
        {
            m_item = default(T);
            m_state = false;
            ThreadPool.QueueUserWorkItem(delegate(object o)
            {
                ISynchronizeInvoke hwnd = m_loader.Target as ISynchronizeInvoke;
                if (hwnd != null && hwnd.InvokeRequired)
                {
                    m_item = (T)hwnd.Invoke(m_loader, m_args);
                }
                else
                {
                    try
                    {
                        m_item = (T)m_loader.DynamicInvoke(m_args);
                    }
                    catch
                    { }
                }
                m_resetEvent.Set();
                m_state = true;
            });
        }

        public void Dispose()
        {
            if (m_resetEvent != null)
                m_resetEvent.Close();
        }
    }
}
