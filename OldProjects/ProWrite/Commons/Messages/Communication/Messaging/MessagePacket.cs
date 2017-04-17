using System;
using System.Collections.Generic;
using System.Text;

namespace System.Communication.Messaging
{
    [Serializable]
    /// <summary>
    /// Message event arguments,the class is only used in server
    /// </summary>
    public class MessagePacket 
    {
        private object sender;
        public object Message;
        private WeakReference<Delegate> handler = new WeakReference<Delegate>();
        public bool Canceled;
        private Exception error;
        /// <summary>
        /// Message sender
        /// </summary>
        public object Sender
        {
            get { return sender; }
            set { sender = value; }
        }

        /// <summary>
        /// Callback function of message processing
        /// </summary>
        public Delegate Handler
        {
            get { return handler.Target; }
            set { handler.Target = value; }
        }

        /// <summary>
        /// Exception information
        /// </summary>
        public Exception Error
        {
            get { return error; }
            set { error = value; }
        }

        public MessagePacket(object msg)
        {
            this.Message = msg;
        }

        public MessagePacket(object msg, Delegate handler, Exception error)
        {
            this.Message = msg;
            this.handler.Target = handler;
            this.error = error;
        }

        public MessagePacket(object sender, object msg, Delegate handler)
        {
            this.Message = msg;
            this.handler.Target = handler;
            this.sender = sender;
        }

        
        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();

            if (Sender != null)
                sb.AppendFormat("Sender:[{0}].\r\n",SupportClass.GetTypeName(Sender));

            sb.AppendFormat("Message:[{0}]\r\n", SupportClass.GetTypeName(Message));

            if (Handler != null)
            {
                sb.AppendFormat("Observers:[{0}].\r\n", SupportClass.GetTypeName(Handler))
                    .AppendFormat("\tTarget:[{0}].\r\n", SupportClass.GetTypeName(Handler.Target))
                    .AppendFormat("\tMethod:[{0}].\r\n", Handler.Method.Name);
            }

            if (Error != null)
            {
                SupportClass.BuildErrorInfo(sb,Error);
            }

            return sb.ToString();
        }

        
    }

    public class MessageInfo<TMessage> : IComparable<MessageInfo<TMessage>> where TMessage : IComparable<TMessage>
    {
        public readonly object Sender;
        public readonly TMessage Message;
        public MessageInfo(object sender, TMessage message) { Sender = sender; Message = message; }

        public int CompareTo(MessageInfo<TMessage> other)
        {
            if (other == null) return 1;
            return Message.CompareTo(other.Message);
        }
    }
}
