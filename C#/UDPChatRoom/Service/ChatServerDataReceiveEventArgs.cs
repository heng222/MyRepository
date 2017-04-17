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
using Kingthy.UDPChatRoom.Service.Message;
namespace Kingthy.UDPChatRoom.Service
{
    /// <summary>
    /// 数据消息事件
    /// </summary>
    public class ChatServerDataReceiveEventArgs
        : EventArgs
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="remoteEP"></param>
        /// <param name="data"></param>
        public ChatServerDataReceiveEventArgs(IPEndPoint remoteEP, byte[] data)
        {
            this.RemoteEP = remoteEP;
            this.Data = data;
            this.MessageType = MessagePackageBase.GetMessageType(data);
        }

        /// <summary>
        /// 远程客户端
        /// </summary>
        public IPEndPoint RemoteEP
        {
            get;
            private set;
        }
        /// <summary>
        /// 接收到的数据包
        /// </summary>
        public byte[] Data
        {
            get;
            private set;
        }

        /// <summary>
        /// 消息类型
        /// </summary>
        public MessageType MessageType
        {
            get;
            private set;
        }
    }
}
