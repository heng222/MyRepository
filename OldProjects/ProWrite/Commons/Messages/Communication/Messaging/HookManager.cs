using System;
using System.Collections.Generic;
using System.Text;

namespace System.Communication.Messaging
{
    public class HookManager:IDisposable
    {
        Dictionary<HookType, SynList<IHook>> hooks;

        public HookManager()
        {
            hooks = new Dictionary<HookType, SynList<IHook>>(9);

            hooks[HookType.ObserverAdding] = new SynList<IHook>();
            hooks[HookType.ObserverAdded] = new SynList<IHook>();
            hooks[HookType.ObserverRemoving] = new SynList<IHook>();
            hooks[HookType.ObserverRemoved] = new SynList<IHook>();

            hooks[HookType.MessageException] = new SynList<IHook>();
            hooks[HookType.MessageSending] = new SynList<IHook>();
            hooks[HookType.MessageSent] = new SynList<IHook>();
            hooks[HookType.MessageReceiving] = new SynList<IHook>();
            hooks[HookType.MessageReceived] = new SynList<IHook>();
        }
        /// <summary>
        /// Register hook
        /// </summary>
        /// <param name="listner"></param>
        public void RegisterHook(params IHook[] hks)
        {
            if (hks == null || hks.Length < 1)
                return;

            foreach (IHook hook in hks)
            {
                foreach (HookType type in hooks.Keys)
                {
                    if ((hook.HookType & type) == type)
                    {
                        hooks[type].Add(hook);
                    }
                }
            }
        }

        /// <summary>
        /// Remove hook
        /// </summary>
        /// <param name="listner"></param>
        public void UnRegisterHook(params IHook[] hks)
        {
            if (hks == null || hks.Length < 1)
                return;
            foreach (IHook hook in hks)
            {
                foreach (HookType type in hooks.Keys)
                {
                    if ((hook.HookType & type) == type)
                    {
                        hooks[type].Remove(hook);
                    }
                }
            }
        }

        public void OnObserverAdding(object sender, Delegate handler, Type type)
        {
            IHook[] hks = hooks[HookType.ObserverAdding].ToArray();
            if (hks != null && hks.Length > 0)
            {
                foreach (IHook hk in hks)
                    hk.OnObserverAdding(sender, handler,type);
            }
        }

        public void OnObserverAdded(object sender, Delegate handler, Type type)
        {
            IHook[] hks = hooks[HookType.ObserverAdded].ToArray();
            if (hks != null && hks.Length > 0)
            {
                foreach (IHook hk in hks)
                    hk.OnObserverAdded(sender, handler,type);
            }
        }

        public void OnObserverRemoving(object sender, Delegate handler, Type type)
        {
            IHook[] hks = hooks[HookType.ObserverRemoving].ToArray();
            if (hks != null && hks.Length > 0)
            {
                foreach (IHook hk in hks)
                    hk.OnObserverRemoving(sender, handler,type);
            }
        }

        public void OnObserverRemoved(object sender, Delegate handler, Type type)
        {
            IHook[] hks = hooks[HookType.ObserverRemoved].ToArray();
            if (hks != null && hks.Length > 0)
            {
                foreach (IHook hk in hks)
                    hk.OnObserverRemoved(sender, handler, type);
            }
        }

        public void OnMessageSending(object sender, MessagePacket e)
        {
            IHook[] hks = hooks[HookType.MessageSending].ToArray();
            if (hks != null && hks.Length > 0)
            {
                foreach (IHook hk in hks)
                    hk.OnMessageSending(sender, e);
            }
        }

        public void OnMessageSent(object sender, MessagePacket e)
        {
            IHook[] hks = hooks[HookType.MessageSent].ToArray();
            if (hks != null && hks.Length > 0)
            {
                foreach (IHook hk in hks)
                    hk.OnMessageSent(sender, e);
            }
        }

        public void OnMessageReceiving(object sender, MessagePacket e)
        {
            IHook[] hks = hooks[HookType.MessageReceiving].ToArray();
            if (hks != null && hks.Length > 0)
            {
                foreach (IHook hk in hks)
                    hk.OnMessageReceiving(sender, e);
            }
        }

        public void OnMessageReceived(object sender, MessagePacket e)
        {
            IHook[] hks = hooks[HookType.MessageReceived].ToArray();
            if (hks != null && hks.Length > 0)
            {
                foreach (IHook hk in hks)
                    hk.OnMessageReceived(sender, e);
            }
        }

        public void OnMessageReceivedException(object sender, MessagePacket e)
        {
            IHook[] hks = hooks[HookType.MessageException].ToArray();
            if (hks != null && hks.Length > 0)
            {
                foreach (IHook hk in hks)
                    hk.OnMessageReceivedException(sender, e);
            }
       }


       #region IDisposable Members

       public void Dispose()
       {
           hooks.Clear();
           hooks = null;
       }

       #endregion
   }
}
