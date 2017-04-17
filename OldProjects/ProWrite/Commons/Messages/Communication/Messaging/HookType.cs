using System;
using System.Collections.Generic;
using System.Text;

namespace System.Communication.Messaging
{
    /// <summary>
    /// Hook type
    /// </summary>
    [Flags]
    [Serializable]
    public enum HookType : ushort
    {
        /// <summary>
        /// 
        /// </summary>
        None = 0,
        /// <summary>
        /// 
        /// </summary>
        MessageException = 1,
        /// <summary>
        /// 
        /// </summary>
        ObserverAdding = 2,
        /// <summary>
        /// 
        /// </summary>
        ObserverRemoving = 4,
        /// <summary>
        /// 
        /// </summary>
        ObserverAdded = 8,
        /// <summary>
        /// 
        /// </summary>
        ObserverRemoved = 16,
        /// <summary>
        /// 
        /// </summary>
        Subscribe = ObserverAdding | ObserverRemoving | ObserverAdded | ObserverRemoved,
        /// <summary>
        /// 
        /// </summary>
        MessageSending = 32,
        /// <summary>
        /// 
        /// </summary>
        MessageSent = 64,
        /// <summary>
        /// 
        /// </summary>
        Send = MessageSending | MessageSent,
        /// <summary>
        /// 
        /// </summary>
        MessageReceiving = 128,
        /// <summary>
        /// 
        /// </summary>
        MessageReceived = 256,
        /// <summary>
        /// 
        /// </summary>
        Receive = MessageReceiving | MessageReceived,
        /// <summary>
        /// 
        /// </summary>
        All = MessageException | Subscribe | Send | Receive
    }
}
