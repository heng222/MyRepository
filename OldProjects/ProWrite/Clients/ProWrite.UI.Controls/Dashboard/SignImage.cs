
//---------------------------------------------------------------------
//
// File: SignImage.cs
//
// Description:
// The control of Current sign shape
//
// Author: Terry
//
// Copyright (C) 2008 by ISoftstone Corporation.  All rights reserved.
// 
// Modify history:   
//---------------------------------------------------------------------
using System;
using System.ComponentModel;
using System.IO;
using System.Reflection;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.Core;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Settings;
using ProWrite.Resources;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.Actions.UFE.Requests;
using System.Net;
using System.Drawing;

namespace ProWrite.UI.Controls.Dashboard
{
    /// <summary>
    /// Current sign shape
    /// </summary>
    public partial class SignImage : XtraUserControl
    {
        private readonly OpenFileDialog _openFileDialog = new OpenFileDialog();

        public SignImage()
        {
            InitializeComponent();
            if (!DesignMode)
            {
                _openFileDialog.Filter = "All supported picture files|*.jpg;*.jpeg;*.gif;*.png;*.bmp|Jpeg File(*.jpg,*.jpeg)|*.jpg;*.jpeg|Gif File(*.gif)|*.gif|Png File(*.png)|*.png|Bmp File(*.bmp)" +
                                         "|*.bmp";
                _openFileDialog.FileOk += openFileDialog_FileOk;
                RegisterHelp();
            }
            //btnRefreshSignImage.Enabled = false;

            //LocalMessageBus.Subject<MenuMessage>().Observers += new System.Communication.Messaging.ObserverHandler<MenuMessage>(MessageControl_Observers);
        }

        //void MessageControl_Observers(object sender, MenuMessage msg)
        //{
        //    if (msg.Commands != null && msg.Commands.Length > 0)
        //    {
        //        foreach (MenuCommand item in msg.Commands)
        //        {
        //            //if (item.Command == MenuCommands.LiveImage)
        //            //    btnRefreshSignImage.Enabled = item.Enabled.Value;

        //        }
        //    }
        //}

        private void RegisterHelp()
        {
            this.SetShowHelp(HelpNavigator.Topic, Resource.Helps.DashboardSignImage);
        }

        public SignInfo SignInsertPhoto { get; set; }

        public PictureEdit PicLiveView
        {
            get { return picLiveView; }
        }

        public string UpdateDate
        {
            set { lblNA.Text = value; }
        }

        private void openFileDialog_FileOk(object sender, CancelEventArgs e)
        {
            string strImageFullName = _openFileDialog.FileName;
            strImageFullName = strImageFullName.Substring(strImageFullName.LastIndexOf("\\") + 1);
            SignInfo sign = ControlService.SignCombo.Current;
            if (sign == null)
            {
                if (SignInsertPhoto == null)
                    return;
                sign = SignInsertPhoto;
            }
            string path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ProWrite\\";
            ////要保存图片的最终路径
            string urlString = path + "Image";
            if (!Directory.Exists(urlString))
            {
                Directory.CreateDirectory(urlString); // File.Create(urlString);
            }
            string[] arrery = Directory.GetFiles(urlString);
            ///判断要上传的图片是否存在，如果存在则不需要再上传
            foreach (string str in arrery)
            {
                if (str.Substring(str.LastIndexOf("\\") + 1) == strImageFullName)
                {
                    if (strImageFullName.Contains(".gif")
                || strImageFullName.Contains(".Gif")
                || strImageFullName.Contains(".GIF"))
                    {
                        strImageFullName = strImageFullName.Substring(0, strImageFullName.IndexOf(".")) + ".jpg";
                    }
                    sign.Image = strImageFullName;
                    return;
                }
            }

            DataGate.Upload(_openFileDialog.FileName);
            if (strImageFullName.Contains(".gif")
                || strImageFullName.Contains(".Gif")
                || strImageFullName.Contains(".GIF"))
            {
                strImageFullName = strImageFullName.Substring(0, strImageFullName.IndexOf(".")) + ".jpg";
            }
            sign.Image = strImageFullName;
        }

        /// <summary>
        /// Refresh shape
        /// </summary>
        public void RefreshImage()
        {
            if (ControlService.SignCombo.Current == null)
            {
                SetPicImageNull();
                SetWebCamNull();
                return;
            }
            string strImage = ControlService.SignCombo.Current.Image;
            string strWebCam = ControlService.SignCombo.Current.ImageWebCam;
            try
            {
                
                btnRefreshSignImage.Enabled = ControlService.SignCombo.Current.IsWebCam
                    && ControlService.SignCombo.Current.Controller.Connection.State == System.Communication.ConnectionState.Opened;
                //    && ControlService.SignCombo.Current.Controller.Connection.User.Status == ProWrite.UFE.UserStatus.Online;
                lblNA.Text = ControlService.SignCombo.Current.LastUpdate;
                
                
                //获取当前程序运行目录，以便加载相关图片
                string path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ProWrite\\";

                picLiveView.Image = IOHelper.GetImageFromFile(path + "Image\\" + strImage);
                
                //picWebCam.Image = IOHelper.GetImageFromFile(path + "Image\\" + ControlService.SignCombo.Current.ImageWebCam);

                if (ControlService.SignCombo.SignName == null)
                {
                    SetPicImageNull();
                    SetWebCamNull();
                }
            }
            catch
            {
                SetPicImageNull();
            }
            try
            {
                string path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ProWrite\\";

                picWebCam.Image = IOHelper.GetImageFromFile(path + "Image\\" + ControlService.SignCombo.Current.ImageWebCam);

            }
            catch
            {
                SetWebCamNull();
            }
            if (string.IsNullOrEmpty(strImage))
            {
                if (ControlService.SignCombo.Current.Template == null
                    || string.IsNullOrEmpty(ControlService.SignCombo.Current.Template.Sign.Image))
                {
                    SetPicImageNull();
                }
                strImage = ControlService.SignCombo.Current.Template.Sign.Image;
            }
            if (string.IsNullOrEmpty(strWebCam))
                SetWebCamNull();
        }

        public bool RefreshImageFromCamera(SignInfo sign)
        {
            return RefreshCameraPic(sign);
        }

        public void RefreshImageCamera(SignInfo sign)
        {
            this.InvokeMethod(() => RefreshCameraPic(sign));
        }

        private bool RefreshCameraPic(SignInfo sign)
        {
            try
            {
                string sourceURL = "http://10.10.65.72/axis-cgi/jpg/image.cgi?resolution=640x480";
                if (!string.IsNullOrEmpty(sign.WebCamAddress))
                    sourceURL = "http://" + sign.WebCamAddress + "/axis-cgi/jpg/image.cgi?resolution=640x480";
                byte[] buffer = new byte[100000];

                int read, total = 0;

                // create HTTP request

                HttpWebRequest req = (HttpWebRequest)WebRequest.Create(sourceURL);
                string use = "root";
                string pwd = "root";
                if (!string.IsNullOrEmpty(sign.WebCamUserName))
                    use = sign.WebCamUserName;
                if (!string.IsNullOrEmpty(sign.WebCamPwd))
                    pwd = sign.WebCamPwd;
                req.Credentials = new NetworkCredential(use, pwd);
                // get response
                WebResponse resp = req.GetResponse();
                // get response stream

                Stream stream = resp.GetResponseStream();

                // read data from stream

                while ((read = stream.Read(buffer, total, 1000)) != 0)
                {
                    total += read;
                }
                // get bitmap
                Bitmap bmp = (Bitmap)Bitmap.FromStream(
                              new MemoryStream(buffer, 0, total));

                string path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ProWrite\\Image\\";
                string name = Guid.NewGuid().ToString() + ".jpg";
                string oldName = sign.Image;
                //picLiveView.Image = IOHelper.GetImageFromFile(path + "Image\\" + strImage);
                IOHelper.SetFileAttribute(path + name, FileAttributes.Normal);
                IOHelper.SaveImage(bmp, path + name);
                //bmp.Save(path + name);
                //File.Delete(path + oldName);
                sign.ImageWebCam = name;
                picWebCam.Image = bmp;
                lblNA.Text = DateTime.Now.GetDateTimeFormats()[69];
                sign.LastUpdate = lblNA.Text;

                return true;
            }
            catch { return false; }
        }

        /// <summary>
        /// 设置PicLiveView和picCurrent的初始图片
        /// </summary>
        public void SetPicImageNull()
        {
            string path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ProWrite\\";
            picLiveView.Image = Resources.Resource.GetImage(Resources.Resource.Images.SignImageDefault);// IOHelper.GetImageFromFile(path + "Image\\" + TemplateGroup.Default.Sign.Image);
            
        }
        public void SetWebCamNull()
        {
            string path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ProWrite\\";
            picWebCam.Image = Resources.Resource.GetImage(Resources.Resource.Images.CurrentContent);
            lblNA.Text = "N/A";
        }

        private void picLiveView_DoubleClick(object sender, EventArgs e)
        {
            if (ControlService.SignCombo.Items.Length <= 0)
                return;
            _openFileDialog.ShowModalDialog();
            MessageBus.Send(this, new ActiveChange(ControlService.SignCombo.Current, false));

        }

        private void btnRefreshSignImage_Click(object sender, EventArgs e)
        {
            //LiveImageAction uploadAction = new LiveImageAction();
            //uploadAction.Perform();
            if (!RefreshImageFromCamera(ControlService.SignCombo.Current))
                MsgBox.Error("Connected web camera failed.");

        }
    }
}