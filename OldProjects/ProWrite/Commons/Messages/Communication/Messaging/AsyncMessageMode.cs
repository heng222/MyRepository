using System;
using System.Collections.Generic;
using System.Text;

namespace System.Communication.Messaging
{

    /// <summary>
    /// Asynchronous message send/receive mode
    /// </summary>
    [Serializable]
    public enum AsyncMessageMode : byte
    {
        /// <summary>
        /// Message sending and receiving are all synchronous
        /// </summary>
        None = 0,
        /// <summary>
        /// Message sending is asynchronous, receiving is synchronous
        /// </summary>
        Send = 1,
        /// <summary>
        /// Message sending is synchronous, receiving is asynchronous
        /// </summary>
        Receive = 2,
        /// <summary>
        /// Message sending and receiving are all asynchronous
        /// </summary>
        Both = 4
    }

}
