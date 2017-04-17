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

namespace Kingthy.UDPChatRoom.Service
{
    /// <summary>
    /// 聊天服务器端,用于接收消息
    /// </summary>
    public class ChatServer
        : IDisposable
    {
        /// <summary>
        /// 本地IP
        /// </summary>
        //public static readonly IPAddress LocalAddress = IPAddress.Parse("192.168.3.111");
        public static readonly IPAddress LocalAddress = IPAddress.Parse("3.8.210.66");
        /// <summary>
        /// 多播地址
        /// </summary>
        public static readonly IPAddress MulticastAddress = IPAddress.Parse("224.0.0.1");
        /// <summary>
        /// 接收端口定义
        /// </summary>
        public static readonly int ReceivePort = 50001;


        #region 属性定义
        /// <summary>
        /// UdpClient
        /// </summary>
        private UdpClient Server;
        /// <summary>
        /// 服务是否已启动
        /// </summary>
        private bool IsStarting;
        #endregion

        /// <summary>
        /// 
        /// </summary>
        public ChatServer()
        {
            this.IsStarting = false;
            this.Server = new UdpClient(new IPEndPoint(ChatServer.LocalAddress, ReceivePort));
            this.OnDataReceiveCallBack = new AsyncCallback(OnDataReceive);
        }
        /// <summary>
        /// 启动服务
        /// </summary>
        public void Start()
        {
            if (IsStarting) return;
            this.Server.JoinMulticastGroup(MulticastAddress);
            this.Server.BeginReceive(this.OnDataReceiveCallBack, this.Server);
            IsStarting = true;
        }
        /// <summary>
        /// 停止服务
        /// </summary>
        public void Stop()
        {
            if (!IsStarting) return;
            IsStarting = false;
            this.Server.DropMulticastGroup(MulticastAddress);
            this.Server.Close();
        }

        #region IDisposable 成员
        /// <summary>
        /// 释放内存
        /// </summary>
        public void Dispose()
        {
            this.Stop();
            this.Server = null;
        }
        #endregion

        #region 事件
        /// <summary>
        /// 
        /// </summary>
        private AsyncCallback OnDataReceiveCallBack;
        /// <summary>
        /// 接收到数据时的激发的事件
        /// </summary>
        public event EventHandler<ChatServerDataReceiveEventArgs> DataReceive;
        /// <summary>
        /// 接收数据的事件
        /// </summary>
        /// <param name="async"></param>
        private void OnDataReceive(IAsyncResult async)
        {
            if (!this.IsStarting) return;   //已关闭服务

            UdpClient server = null;
            try
            {
                server = (UdpClient)async.AsyncState;
                IPEndPoint remoteEP = new IPEndPoint(IPAddress.Any, 0);
                byte[] buffer = server.EndReceive(async, ref remoteEP);

                //通知上一层
                EventHandler<ChatServerDataReceiveEventArgs> handler = this.DataReceive;
                if (handler != null) handler(server, new ChatServerDataReceiveEventArgs(remoteEP, buffer));
            }
            catch (ObjectDisposedException)
            {
                //已被释放了资源数据
                server = null;
            }
            catch { }
            finally
            {
                //继续接收数据
                if (this.IsStarting && server != null)
                    server.BeginReceive(this.OnDataReceiveCallBack, server);
            }
        }
        #endregion
    }
}
