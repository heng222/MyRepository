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
    /// 查询在线用户的消息包
    /// </summary>
    public class QueryMessagePackage
        : MessagePackageBase
    {
        /// <summary>
        /// 
        /// </summary>
        public QueryMessagePackage()
            : base(MessageType.Query)
        { }
    }
}
