//---------------------------------------------------------------------
//
// File: MessageBus.cs
//
// Description:
// 
//
// Author: Kevin
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using ProWrite.Core;
using log4net;
using System.Communication.Messaging;

namespace ProWrite.Core
{
    public class MessageBus
    {
        private static LogHook hook;
        protected static MessageRouter<PWMessage> InnerBus;

        static MessageBus()
        {
			
            InnerBus = new MessageRouter<PWMessage>();
            hook = new LogHook();
            InnerBus.RegisterHook(hook);
        }

        public static void Send(object sender, PWMessage msg)
        {
            if (msg != null)
            {
                msg.Sender = sender;
                InnerBus.Send(sender, msg);
            }
        }

        public static Subject<TMessage> Subject<TMessage>() where TMessage : PWMessage
        {
            return InnerBus.Subject<TMessage>();
        }

        public static void Dispose()
        {
            InnerBus.Dispose();
        }

        private class LogHook : HookAdapter
        {
            private static readonly ILog _log = LogManager.GetLogger("MessageBus");
            public LogHook()
            {
                HookType = HookType.MessageException;
            }

            public override void OnMessageReceivedException(object sender, MessagePacket e)
            {
                Trace.WriteLine("\tMessage received exception£º" + e.Message.ToString());
                _log.Error("Message received exception", e.Error);
            }

        }
    }
}
