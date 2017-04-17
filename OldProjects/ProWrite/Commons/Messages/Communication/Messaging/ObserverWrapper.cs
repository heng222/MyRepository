using System;
using System.Collections.Generic;
using System.Text;

namespace System.Communication.Messaging
{
    /// <summary>
    /// ��Ϣ��װ�������˿ͻ��˺ͷ�����������Ϣ·�ɵ���������
    /// </summary>
    /// <typeparam name="TMessage"></typeparam>
    [Serializable]
    public class ObserverWrapper<TMessage>:MarshalByRefObject
    {
        private WeakReference<ObserverHandler<TMessage>> localHandler;
        public ObserverWrapper()
        {
            localHandler = new WeakReference<ObserverHandler<TMessage>>();
        }

        public event ObserverHandler<TMessage> LocalHandler
        {
            add { localHandler.Target += value; }
            remove { localHandler.Target -= value; }
        }

        public void Register(object sender,TMessage e) 
        {
            if (localHandler != null)
                localHandler.Target.call(sender, e);
        }

        public override object InitializeLifetimeService()
        {
            return null;
        }
    }
}
