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
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Net;
using Kingthy.UDPChatRoom.Service;
using Kingthy.UDPChatRoom.Service.Message;
namespace Kingthy.UDPChatRoom
{
    public partial class RoomForm : Form
    {
        public RoomForm()
        {
            //初始化聊天室数据
            this.Server = new ChatServer();
            this.Client = new ChatClient();

            this.Server.DataReceive += Server_DataReceive;
            //启动服务
            this.Server.Start();

            InitializeComponent();
            this.FormClosing += new FormClosingEventHandler(RoomForm_FormClosing);
            this.MessageText.KeyDown += new KeyEventHandler(MessageText_KeyDown);

            //登录在线状态
            this.Client.Online();
            //查询用户列表
            this.Client.Query();
        }

        #region 窗体事件
        /// <summary>
        /// 窗体关闭
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void RoomForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            //注销
            this.Client.Offline();

            this.Server.Dispose();
            this.Client.Dispose();
        }
        /// <summary>
        /// 处理CTRL + Enter键
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MessageText_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Control && e.KeyCode == Keys.Enter)
            {
                BtnSend_Click(null, e);
                //不处理Enter键
                e.SuppressKeyPress = true;
            }
        }
        /// <summary>
        /// 发送聊天内容
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BtnSend_Click(object sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(this.MessageText.Text))
                this.Client.SendMessage(this.MessageText.Text);
            this.MessageText.Text = string.Empty;
        }
        #endregion

        #region 属性定义
        private ChatServer Server;
        /// <summary>
        /// 
        /// </summary>
        private ChatClient Client;
        #endregion

        #region 聊天服务
        /// <summary> 
        /// 聊天服务的数据接收
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Server_DataReceive(object sender, ChatServerDataReceiveEventArgs e)
        {
            switch (e.MessageType)
            {
                case MessageType.Query:
                    //查询状态,则发送自己的身份
                    this.Client.SendIdentity();
                    break;
                case MessageType.Identity:
                    //客户端表明身份状态,则加入到客户端列表
                    AddClientIP(e.RemoteEP.Address.ToString());
                    break;
                case MessageType.Online:
                    //有某个客户端上线,则加入到客户端列表
                    AddClientIP(e.RemoteEP.Address.ToString());
                    AddMessage(string.Format("## 客户机{0}已上线...", e.RemoteEP.Address.ToString()));
                    break;
                case MessageType.Offline:
                    //某个客户端下线
                    RemoveClientIP(e.RemoteEP.Address.ToString());
                    AddMessage(string.Format("## 客户机{0}已下线...", e.RemoteEP.Address.ToString()));
                    break;
                case MessageType.Chat:
                    //消息
                    ChatMessagePackage package = ChatMessagePackage.FromPackage(e.Data);
                    AddMessage(string.Format("--------------------------------------------------------------\r\n>> {0} 于 {1} 说:\r\n{2}\r\n", 
                        e.RemoteEP.Address.ToString(),
                        package.Time.ToString("yyyy-MM-dd HH:mm:ss"),
                        package.Message
                        ));
                    break;
            }
        }
        
        /// <summary>
        /// 添加IP到客户列表
        /// </summary>
        /// <param name="e"></param>
        private void AddClientIP(string ip)
        {
            if (this.ClientList.InvokeRequired)
            {
                this.ClientList.Invoke(new Action<string>(AddClientIP), ip);
            }
            else
            {
                if (!this.ClientList.Items.Contains(ip))
                {
                    this.ClientList.Items.Add(ip);                    
                }
            }
        }
        /// <summary>
        /// 删除某个客户列表
        /// </summary>
        /// <param name="ip"></param>
        private void RemoveClientIP(string ip)
        {
            if (this.ClientList.InvokeRequired)
            {
                this.ClientList.Invoke(new Action<string>(RemoveClientIP), ip);
            }
            else
            {
                if (this.ClientList.Items.Contains(ip))
                {
                    this.ClientList.Items.Remove(ip);
                }
            }
        }
        /// <summary>
        /// 添加消息
        /// </summary>
        /// <param name="text"></param>
        private void AddMessage(string text)
        {
            if (this.MessageOutput.InvokeRequired)
            {
                this.MessageOutput.Invoke(new Action<string>(AddMessage), text);
            }
            else
            {
                if (this.MessageOutput.Text.Length > 0)
                {
                    this.MessageOutput.AppendText("\r\n");
                }
                this.MessageOutput.AppendText(text);
            }
        }
        #endregion
    }
}
