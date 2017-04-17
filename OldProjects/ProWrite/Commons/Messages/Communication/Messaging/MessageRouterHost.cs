using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Remoting;

namespace System.Communication.Messaging
{
    /// <summary>
    /// 消息总线宿主类,该类主要应用在Remoting 服务器端
    /// </summary>
    public class MessageRouterHost
    {
        private static IMessageRouter messageManager = null;
        private static ObjRef objRef = null;

        public static void Configure(string fileName, bool ensureSecurity, string objectUrl)
        {
            MessageRouter msgManager = new MessageRouter();
            msgManager.AsyncMessageMode = AsyncMessageMode.Both;
            RemotingConfiguration.Configure(fileName, false);
            objRef = RemotingServices.Marshal(msgManager, objectUrl);
            messageManager = msgManager;
        }

        public static IMessageRouter MessageManager
        {
            get { return messageManager; }
        }

        public static void Stop()
        {
            RemotingServices.Unmarshal(objRef);
            messageManager = null;
        }
    }
}
