using System;
using System.Collections.Generic;
using System.Text;

namespace System.Communication.Messaging
{
    /// <summary>
    /// Message Hook
    /// </summary>
    public interface IHook
    {
        /// <summary>
        /// Get or set hooktype 
        /// </summary>
        HookType HookType { get; set;}

        #region MessageException
        /// <summary>
        /// Message receive exception
        /// </summary> 
        /// <remarks> </remarks>
        void OnMessageReceivedException(object sender, MessagePacket e);
        #endregion

        #region Subscribe
        /// <summary>
        /// Message adding
        /// </summary>
        /// <remarks> </remarks>
        void OnObserverAdding(object sender, Delegate handler, Type type);
        /// <summary>
        /// Message removing
        /// </summary>
        /// <remarks> </remarks>
        void OnObserverRemoving(object sender, Delegate handler, Type type);
        /// <summary>
        /// Messsage added
        /// </summary>
        /// <remarks> </remarks>
        void OnObserverAdded(object sender, Delegate handler, Type type);
        /// <summary>
        /// Message removed
        /// </summary>
        /// <remarks> </remarks>
        void OnObserverRemoved(object sender, Delegate handler, Type type);
        #endregion

        #region Send
        /// <summary>
        /// Message sending
        /// </summary>
        void OnMessageSending(object sender, MessagePacket e);
        /// <summary>
        /// Message sent
        /// </summary>
        void OnMessageSent(object sender, MessagePacket e);
        #endregion

        #region Receive
        /// <summary>
        /// Message receiving filter
        /// </summary> 
        /// <remarks> </remarks>
        void OnMessageReceiving(object sender, MessagePacket e);
        /// <summary>
        ///Message received
        /// </summary> 
        /// <remarks> </remarks>
        void OnMessageReceived(object sender, MessagePacket e);
        #endregion
    }
}
