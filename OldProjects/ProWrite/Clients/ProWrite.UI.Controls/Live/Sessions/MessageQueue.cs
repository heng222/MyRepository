//---------------------------------------------------------------------
//
// File: MessageQueue.cs
//
// Description:
// The control of MessageQueue
//
// Author: terry
//
// Copyright (C) 2008 by ISoftstone Corporation.  All rights reserved.
// 
// Modify history:   
// Terry   2009-12-07   Create
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraGrid.Views.Grid.ViewInfo;
using DevExpress.XtraEditors;
using ProWrite.Entity.Live;
using ProWrite.UI.Controls.Common;
using ProWrite.Entity.Dashboard;
using ProWrite.UFE.Entity;
using ProWrite.Core;
using ProWrite.UI.Controls.Actions.UFE.Requests;
using ProWrite.Entity.Library;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public partial class MessageQueue : UserControl
    {
        private DevExpress.XtraGrid.Views.Grid.GridView gridView1;
        public MessageQueue()
        {
            InitializeComponent();
            gridView1 = new DevExpress.XtraGrid.Views.Grid.GridView();
            InitSignInfo();
        }
        SignInfo CurrentSign;
        private const string messagePath = "/mnt/sdcard/.ufe/data/messages/";// + messageId + "/" + messageId + ".png";
        private void InitSignInfo()
        {
            if (DataGate.SessionInfos.Count > 0)
            {
                foreach (SessionInfo session in DataGate.SessionInfos)
                {
                    foreach (LiveSign sign in session.SignItems)
                    {
                        //Button btn = new Button();
                        //btn.Text = sign.Name;
                        //btn.Location = new Point(1,1);
                        //btn.Size = btnSign1.Size;
                        //btn.Click += new EventHandler(btn_Click);
                        //btnSign1.Name = "btn2";


                        //Controls.Add(btn);
                        btnSign1.Text = sign.Name;
                        CurrentSign = DashboardItem.GetSignByName(sign.Name);
                    }
                }
            }
        }

        void btn_Click(object sender, EventArgs e)
        {
            string signName = (sender as Button).Text;
            this.CurrentSign = DashboardItem.GetSignByName(signName);
        }

        private void lbcMessageQueue_DragDrop(object sender, DragEventArgs e)
        {
            LiveMessageItem liveMessageItem = GetDragObject(sender, e.Data);
            if (liveMessageItem == null)
                return;
            string messageName = liveMessageItem.Name;
            string messageId = liveMessageItem.Id;
            string serverPath = messagePath + messageId + "/" + messageId + ".xml";
            string dragString = messageName + "       " + liveMessageItem.LengthText;
            if (cmbMessageQueue.Text.Trim() == "" && lbcMessageQueue.ItemCount <= 0)
            {
                cmbMessageQueue.Text = dragString;
                PlayActionPerform(serverPath, 1);
                return;
            }
            ListBoxControl lb = sender as ListBoxControl;

            int ind = lb.IndexFromPoint(lb.PointToClient(new System.Drawing.Point(e.X, e.Y)));
            if (ind == -1)
            {
                lb.Items.Add(dragString);
                lbcMessageQueue.SelectedIndex = lbcMessageQueue.ItemCount - 1;
                PlayActionPerform(serverPath, lbcMessageQueue.ItemCount + 1);
            }
            else
            {
                lb.Items.Insert(ind, dragString);
                this.lbcMessageQueue.SelectedIndex = ind;
                PlayActionPerform(serverPath, ind + 2);
            }
        }

        private void PlayActionPerform(string path, int position)
        {
            if (CurrentSign == null)
                return;
            PlayMessageQueue messageQueue = new PlayMessageQueue();
            messageQueue.MessagePath = path;
            messageQueue.QueuePosition = position;

            SignInfo sign = CurrentSign;
            sign.Controller.SendAsync(
                       Commands.Play,
                       h =>
                       {
                           if (h.IsSuccessed)
                           {

                           }
                       }, messageQueue);
        }

        private void SkipMessagequeActionPerform(string id, int position)
        {

            if (CurrentSign == null)
                return;
            SkipMessageQueue skipMessageQueue = new SkipMessageQueue();
            skipMessageQueue.UUID = id;
            skipMessageQueue.Position = position;

            SignInfo sign = CurrentSign;
            sign.Controller.SendAsync(
                       Commands.SkipQueueMessage,
                       h =>
                       {
                           if (h.IsSuccessed)
                           {

                           }
                       }, skipMessageQueue);
        }
        private LiveMessageItem GetDragObject(object sender, IDataObject data)
        {
            object[] obj = data.GetData(typeof(object[])) as object[];
            var item = obj[1] as LiveMessageItem;

            if (item != null)
                return item;
            else
                return null;
            /*
            string result = "";
            string name=item.Name;
            string length = item.LengthText;
            result = name;
            if (!string.IsNullOrEmpty(result))
                return result;
            else
                return "";*/
        }

        private void lbcMessageQueue_DragEnter(object sender, DragEventArgs e)
        {
            e.Effect = DragDropEffects.Copy;
        }

        private void btnUp_Click(object sender, EventArgs e)
        {
            int index = 0;
            object item1 = null;
            if (lbcMessageQueue.SelectedItems != null)
            {
                for (int i = 0; i < lbcMessageQueue.SelectedItems.Count; i++)
                {
                    if (lbcMessageQueue.SelectedIndices[i] != 0)
                    {
                        index = lbcMessageQueue.SelectedIndices[i];// lbcMessageQueue.Items.IndexOf(lbcMessageQueue.SelectedItems[i]);


                        item1 = lbcMessageQueue.Items[index];

                        string lbcItem = item1.ToString();
                        string msgId = GetLiveMessageIdByName(lbcItem.Substring(0, lbcItem.IndexOf("       ")));
                        if (msgId != "")
                            SkipMessagequeActionPerform(msgId, index + 1);

                        lbcMessageQueue.Items.RemoveAt(index);
                    }
                }
                if (item1 != null)// && index > 0)
                {
                    lbcMessageQueue.Items.Insert(index - 1, item1);
                    lbcMessageQueue.SelectedIndex = index - 1;
                    string messageId = GetLiveMessageIdByName(item1.ToString().Substring(0, item1.ToString().IndexOf("       ")));
                    string serverPath = messagePath + messageId + "/" + messageId + ".xml";
                    PlayActionPerform(serverPath, index + 1);
                }
            }
        }

        private void btnDown_Click(object sender, EventArgs e)
        {
            int index = 0;
            object item1 = null;
            if (lbcMessageQueue.SelectedItems != null)
            {
                for (int i = 0; i < lbcMessageQueue.SelectedItems.Count; i++)
                {
                    if (lbcMessageQueue.SelectedIndices[i] != lbcMessageQueue.Items.Count - 1)
                    {
                        index = index = lbcMessageQueue.SelectedIndices[i];// lbcMessageQueue.Items.IndexOf(lbcMessageQueue.SelectedItems[i]);

                        item1 = lbcMessageQueue.Items[index];

                        string lbcItem = item1.ToString();
                        string msgId = GetLiveMessageIdByName(lbcItem.Substring(0, lbcItem.IndexOf("       ")));
                        if (msgId != "")
                            SkipMessagequeActionPerform(msgId, index + 2);
                        lbcMessageQueue.Items.RemoveAt(index);
                    }
                }
                if (item1 != null)
                {

                    lbcMessageQueue.Items.Insert(index + 1, item1);
                    lbcMessageQueue.SelectedIndex = index + 1;

                    string messageId = GetLiveMessageIdByName(item1.ToString().Substring(0, item1.ToString().IndexOf("       ")));
                    string serverPath = messagePath + messageId + "/" + messageId + ".xml";
                    PlayActionPerform(serverPath, index + 3);
                }
            }
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < lbcMessageQueue.SelectedIndices.Count; i++)
            {
                string lbcItem =lbcMessageQueue.Items[lbcMessageQueue.SelectedIndices[i]].ToString();
                string msgId = GetLiveMessageIdByName(lbcItem.Substring(0, lbcItem.IndexOf("       ")));
                if (msgId != "")
                    SkipMessagequeActionPerform(msgId, i + 2);
                lbcMessageQueue.Items.RemoveAt(lbcMessageQueue.SelectedIndices[i]);
               
            }
        }

        private string GetLiveMessageIdByName(string name)
        {
            foreach (MemoryLibraryItem item in SessionInfo.Current.MemoryLibraries)
            {
                if (item.Name == name)
                    return item.Id;
            }
            return "";
        }
        private void btnRefresh_Click(object sender, EventArgs e)
        {

        }

        private void lbcMessageQueue_SelectedIndexChanged(object sender, EventArgs e)
        {
            btnDelete.Enabled = lbcMessageQueue.SelectedItem != null;
            btnUp.Enabled = lbcMessageQueue.SelectedIndex > 0;
            btnDown.Enabled = lbcMessageQueue.SelectedIndex != lbcMessageQueue.ItemCount - 1;
            //cmbMessageQueue.Text = lbcMessageQueue.Items[0].ToString();
        }

        private void btnSign1_Click(object sender, EventArgs e)
        {
            GetLiveModeAction action = new GetLiveModeAction();
            action.Sign = CurrentSign;
            action.Perform();
        }

        private void btnEject_Click(object sender, EventArgs e)
        {
            string lbcItem = this.cmbMessageQueue.Text.ToString();
            string msgId = GetLiveMessageIdByName(lbcItem.Substring(0, lbcItem.IndexOf("       ")));
            if (msgId != "")
                SkipMessagequeActionPerform(msgId, 1);
            cmbMessageQueue.Text = "";
            if (lbcMessageQueue.Items.Count > 0)
            {
                cmbMessageQueue.Text = lbcMessageQueue.Items[0].ToString();
                lbcMessageQueue.Items.RemoveAt(0);
            }
        }
    }
}
