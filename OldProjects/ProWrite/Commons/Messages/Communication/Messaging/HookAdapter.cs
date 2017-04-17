using System;
using System.Collections.Generic;
using System.Text;

namespace System.Communication.Messaging
{
    /// <summary>
    ///Message hook adapter
    /// </summary>
    public class HookAdapter:IHook 
    {
        public HookAdapter() { }
        public HookAdapter(HookType hookType)
        {
            this.HookType = hookType;
        }

        private HookType hookType = HookType.None;
        public virtual HookType HookType
        {
            get { return hookType; }
            set { hookType = value; }
        }
        public virtual void OnMessageReceivedException(object sender, MessagePacket e) { }
        public virtual void OnObserverAdding(object sender, Delegate handler, Type type) { }
        public virtual void OnObserverRemoving(object sender, Delegate handler, Type type) { }
        public virtual void OnObserverAdded(object sender, Delegate handler, Type type) { }
        public virtual void OnObserverRemoved(object sender, Delegate handler, Type type) { }
        public virtual void OnMessageSending(object sender, MessagePacket e) { }
        public virtual void OnMessageSent(object sender, MessagePacket e) { }
        public virtual void OnMessageReceiving(object sender, MessagePacket e) { }
        public virtual void OnMessageReceived(object sender, MessagePacket e) { }
    }
}
