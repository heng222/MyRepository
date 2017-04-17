/*
 * 名称: 基于UDP广播的小型聊天室
 * 作者: kingthy
 * MSN : kingthy@gmail.com
 * 博客: http://kingthy.cnblogs.com
 * 说明: 你可以对代码进行任意的修改.如果你对程序进行了功能扩充,希望您能发一份新代码给我.谢谢:)
 * 
 * */

using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;
using Kingthy.UDPChatRoom.Service.Message;
namespace Kingthy.UDPChatRoom.Service
{
    /// <summary>
    /// 聊天的客户端,用于发送消息
    /// </summary>
    public class ChatClient
        : IDisposable
    {
        /// <summary>
        /// 服务器的地址
        /// </summary>
        private readonly static IPEndPoint ServerAddress = new IPEndPoint(ChatServer.MulticastAddress, ChatServer.ReceivePort);

        /// <summary>
        /// 
        /// </summary>
        public ChatClient()
        {
            this.Client = new UdpClient(new IPEndPoint(ChatServer.LocalAddress, 0));
            //this.Client.MulticastLoopback = false;
        }
        /// <summary>
        /// UdpClient
        /// </summary>
        private UdpClient Client;

        #region 消息发送
        /// <summary>
        /// 发送查询用户在线的消息
        /// </summary>
        public void Query()
        {
            this.SendMessage(new QueryMessagePackage());
        }

        /// <summary>
        /// 发送表明用户身份的消息
        /// </summary>
        public void SendIdentity()
        {
            this.SendMessage(new IdentityMessagePackage());
        }
        /// <summary>
        /// 发送用户上线的消息
        /// </summary>
        public void Online()
        {
            this.SendMessage(new OnlineMessagePackage());
        }
        /// <summary>
        /// 发送用户下线的消息
        /// </summary>
        public void Offline()
        {
            this.SendMessage(new OfflineMessagePackage());
        }
        /// <summary>
        /// 发送消息广播
        /// </summary>
        /// <param name="message"></param>
        public void SendMessage(string message)
        {
            this.SendMessage(new ChatMessagePackage(DateTime.Now, message));
        }
        /// <summary>
        /// 发送消息广播
        /// </summary>
        /// <param name="message"></param>
        /// <returns></returns>
        private void SendMessage(MessagePackageBase message)
        {
            byte[] data = message.GetPackageData();
            this.Client.Send(data, data.Length, ChatClient.ServerAddress);
        }
        #endregion

        #region IDisposable 成员
        /// <summary>
        /// 释放内存
        /// </summary>
        public void Dispose()
        {
            this.Client.Close();
            this.Client = null;
        }

        #endregion
    }
}

