//---------------------------------------------------------------------
//
// File: CurrentClip.cs
//
// Description:
// The control of CurrentClip
//
// Author: Terry
//
// Copyright (C) 2008 by ISoftstone Corporation.  All rights reserved.
// 
// Modify history:   
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.Resources;
using ProWrite.UI.Controls.Actions.UFE.Requests;
using ProWrite.Entity.Dashboard;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;
using ProWrite.UFE;

namespace ProWrite.UI.Controls.Dashboard
{
    /// <summary>
    /// Current sign clip
    /// </summary>
    public partial class CurrentClip : DevExpress.XtraEditors.XtraUserControl
    {
        public CurrentClip()
        {
            InitializeComponent();
            txtSchedule.Enabled = false;
            txtPlaylist.Enabled = false;
            txtMessage.Enabled = false;
            MessageBus.Subject<PlayComplete>().Observers += new System.Communication.Messaging.ObserverHandler<PlayComplete>(CurrentClip_Observers);
            this.SetShowHelp(HelpNavigator.Topic, Resource.Helps.DashboardCurrentClip);
        }

        void CurrentClip_Observers(object sender, PlayComplete msg)
        {
            var conn = sender as IUFEConnection;
            if(conn != null && conn.Sign == ControlService.SignCombo.Current)
                this.InvokeMethod(() => UpdateUI(msg));
        }

        private void UpdateUI(PlayComplete msg)
        {
            string messageId = msg.MessageId;
            string messageInfo = msg.MessageInfo;
            string scheduleInfo = msg.ScheduleInfo;
            string plsylistInfo = msg.PlsylistInfo;
            string endTime = msg.EndTime;
            string toFilePath = DataGate.Provider.Path + "\\Library\\Upload\\Message\\" + messageId + ".png";
            string fromFilePath = "/mnt/sdcard/.ufe/data/messages/" + messageId + "/" + messageId + ".png";


            UpdateMessageInfo = messageInfo;

            ControlService.SignCombo.Current.MessageIdInfo = messageInfo;
            ControlService.DashboardTree.PopulateTree();
            UpdateScheduleInfo = scheduleInfo;

            UpdatePlaylist = plsylistInfo;
            UpdateDate = DateTime.Parse(msg.EndTime).GetDateTimeFormats()[69];
            //MessageInfo msg = LibraryGroup.Current.Messages.GetById(messageId);

            Image desImg = IOHelper.GetImageFromFile(toFilePath);
            if (desImg != null)
                ControlService.CurrentClip.PicCurrent.Image = desImg;
            else
            {
                ControlService.SignCombo.Current.Controller.Connection.FtpManager.DownLoad(fromFilePath, toFilePath);

                desImg = IOHelper.GetImageFromFile(toFilePath);
                ControlService.CurrentClip.PicCurrent.Image = desImg;
            }
        }

        public PictureEdit PicCurrent
        {
            get { return picCurrent; }
        }

        public bool IsEnable
        {
            set
            {
                lblNA.Enabled = value;
                lblLastUpdate.Enabled = value;
                btnRefresh.Enabled = value;
            }
        }

        public string UpdateDate
        {
            set 
            {                
                //lblNA.Enabled = true;
                lblNA.Text = value; 
            }
        }

        public string UpdateMessageInfo
        {
            set { this.txtMessage.Text = value; }
        }

        public string UpdateScheduleInfo
        {
            set { txtSchedule.Text = value; }
        }

        public string UpdatePlaylist
        {
            set { txtPlaylist.Text = value; }
        }

        private void btnRefresh_Click(object sender, EventArgs e)
        {
            LiveImageAction action = new LiveImageAction(true);
            action.Perform();
            StatusAction status = new StatusAction(true);
            status.Perform();
        }

        public void RefreshStatus()
        {
            var sign = ControlService.SignCombo.Current;
            if (sign.DashboardType == DashboardType.Sign
                && sign.Controller.Connection != null
                && sign.Controller.Connection.State == System.Communication.ConnectionState.Opened)
            {
                LiveImageAction action = new LiveImageAction(false);
                action.Perform();
                StatusAction status = new StatusAction(false);
                status.Perform();
            }
        }

        public void RefreshClip()
        {
            try
            {
                
                if (ControlService.SignCombo.Current == null||ServiceManager.Get<bool>())
                {
                    SetPicImageNull();
                    return;
                }
                btnRefresh.Enabled = ControlService.SignCombo.Current.Controller.Connection.State == System.Communication.ConnectionState.Opened;
                //    && ControlService.SignCombo.Current.Controller.Connection.User.Status == ProWrite.UFE.UserStatus.Online;
                lblNA.Text = ControlService.SignCombo.Current.LastUpdateClip;
                string strImage = ControlService.SignCombo.Current.ImageCurrentClip;
                if (string.IsNullOrEmpty(strImage))
                {
                    //if (ControlService.SignCombo.Current.Template == null
                    //    || string.IsNullOrEmpty(ControlService.SignCombo.Current.Template.Sign.Image))
                    //{
                    SetPicImageNull();
                    return;
                    //}
                    ////else

                    //strImage = ControlService.SignCombo.Current.Template.Sign.Image;
                }
                //获取当前程序运行目录，以便加载相关图片
                string path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ProWrite\\";

                picCurrent.Image = IOHelper.GetImageFromFile(path + "Image\\" + strImage);

                if (ControlService.SignCombo.SignName == null)
                {
                    SetPicImageNull();
                }
            }
            catch
            {
                SetPicImageNull();
            }
        }
        public void SetPicImageNull()
        {
            txtMessage.Text = "N/A";
            txtPlaylist.Text = "N/A";
            txtSchedule.Text = "N/A";
            string path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ProWrite\\";
            picCurrent.Image = Resources.Resource.GetImage(Resources.Resource.Images.CurrentContent);// IOHelper.GetImageFromFile(path + "Image\\" + TemplateGroup.Default.Sign.Image);
        }
    }
}
