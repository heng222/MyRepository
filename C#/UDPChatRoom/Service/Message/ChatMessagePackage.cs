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
using System.IO;
namespace Kingthy.UDPChatRoom.Service.Message
{
    /// <summary>
    /// 消息包
    /// </summary>
    public class ChatMessagePackage
        : MessagePackageBase
    {
        /// <summary>
        /// 构造消息包
        /// </summary>
        /// <param name="time"></param>
        /// <param name="message"></param>
        public ChatMessagePackage(DateTime time,string message) : base(MessageType.Chat)
        {
            this.Time = time;
            this.Message = message;            
        }

        /// <summary>
        /// 字符编码
        /// </summary>
        public static readonly Encoding Charset = Encoding.Default;

        /// <summary>
        /// 获取或返回聊天消息
        /// </summary>
        public string Message
        {
            get;
            private set;
        }

        /// <summary>
        /// 获取或返回消息时间
        /// </summary>
        public DateTime Time
        {
            get;
            private set;
        }

        /// <summary>
        /// 获取消息包
        /// </summary>
        /// <returns></returns>
        public override byte[] GetPackageData()
        {
            //数据包结构: 1字节的消息类型+8字节(消息时间)+?字节(消息内容)
            List<byte> buffer = new List<byte>(100);
            buffer.AddRange(base.GetPackageData());
            buffer.AddRange(BitConverter.GetBytes(this.Time.ToBinary()));
            buffer.AddRange(ChatMessagePackage.Charset.GetBytes(this.Message));

            return buffer.ToArray();
        }

        /// <summary>
        /// 从消息包中获取消息
        /// </summary>
        /// <param name="data"></param>
        /// <returns></returns>
        public static ChatMessagePackage FromPackage(byte[] data)
        {
            //取前8个字节(消息时间)
            try
            {
                byte[] timeBuffer = new byte[8];
                //跳过消息类型(1字节)
                Array.Copy(data, 1, timeBuffer, 0, 8);
                DateTime time = DateTime.FromBinary(BitConverter.ToInt64(timeBuffer, 0));
                string message = ChatMessagePackage.Charset.GetString(data, timeBuffer.Length + 1, data.Length - timeBuffer.Length - 1);
                return new ChatMessagePackage(time, message);
            }
            catch
            {
                return null;
            }
        }
    }
}
