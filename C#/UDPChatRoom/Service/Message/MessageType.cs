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
    /// 联天消息类型
    /// </summary>
    public enum MessageType
        : byte
    {
        /// <summary>
        /// 未知类型
        /// </summary>
        Unknown = 0x0,
        /// <summary>
        /// 普通的联天消息
        /// </summary>
        Chat = 0x64,    //100
        /// <summary>
        /// 查询在线用户
        /// </summary>
        Query = 0x0A,    //10
        /// <summary>
        /// 表明身份(用于回答Query消息)
        /// </summary>
        Identity = 0x0B, //11
        /// <summary>
        /// 用户上线
        /// </summary>
        Online = 0x14,  //20
        /// <summary>
        /// 用户下线
        /// </summary>
        Offline = 0x25  //21
    }
}
