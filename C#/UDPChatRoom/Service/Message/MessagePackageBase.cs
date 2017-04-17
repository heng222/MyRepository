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

namespace Kingthy.UDPChatRoom.Service.Message
{
    /// <summary>
    /// 消息包的基类
    /// </summary>
    public abstract class MessagePackageBase
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="type"></param>
        protected MessagePackageBase(MessageType type)
        {
            this.Type = type;
        }

        /// <summary>
        /// 消息类型
        /// </summary>
        public MessageType Type
        {
            get;
            private set;
        }

        /// <summary>
        /// 获取消息包数据
        /// </summary>
        /// <returns></returns>
        public virtual byte[] GetPackageData()
        {
            return new byte[] { (byte)this.Type };
        }

        /// <summary>
        /// 从数据包中获取消息的类型
        /// </summary>
        /// <param name="data"></param>
        /// <returns></returns>
        internal static MessageType GetMessageType(byte[] data)
        {
            if (data == null || data.Length == 0) return MessageType.Unknown;

            return (MessageType)data[0];
        }
    }
}
