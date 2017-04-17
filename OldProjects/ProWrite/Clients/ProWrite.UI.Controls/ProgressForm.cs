//---------------------------------------------------------------------
//
// File: ProgressForm.cs
//
// Description:
// ProgressForm 
//
// Author: Louis lv 
//
//Modify History:
//      Jerry Xu  2009-1-15 Add method:DrawText
//      Jerry Xu  2009-1-20 Update method:ProgressForm(UploadAction uploadAction),Error(string msg, Exception ex),Success(string msg),Cancel(bool isCancelTask)
//      Jerry Xu  2009-1-20 Add method:Init(UploadAction uploadAction)
//      Jerry Xu  2009-3-4  Add method:CancelFtp(string msg)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraBars.Ribbon;
using DevExpress.XtraEditors;
using ProWrite.UI.Controls.Actions.UFE.Requests;
using ProWrite.UI.Controls.Common;
using System.Communication;
using ProWrite.Resources;
using ProWrite.Core;
using ProWrite.Entity.Dashboard;
using ProWrite.UFE;

namespace ProWrite.UI.Controls
{
    internal partial class ProgressForm : XtraForm
    {

        private Action uploadAction = null;
        private Action cancelAction = () => { };

        private SignInfo sign;

        private Timer timer;
        private System.Threading.Thread thread;
        public string _infoMsg;

        public ProgressForm(Action uploadAction, Action cancelAction,  SignInfo sign)
        {
            InitializeComponent();
            if (!DesignMode)
                Init(uploadAction,cancelAction, sign);
        }

        /// <summary>
        /// Function: Init form info
        /// Author  : Jerry Xu
        /// Date    : 2009-1-20
        /// </summary>
        /// <param name="uploadAction">UploadAction</param>
        private void Init(Action uploadAction, Action cancelAction, SignInfo sign)
        {

            this.uploadAction = uploadAction;
            this.cancelAction = cancelAction;
            this.sign = sign;
            this.ControlBox = false;

            timer = new Timer();
            timer.Tick += new EventHandler(timer_Tick);
            timer.Interval = 200;

            btnCancel.Text = "Cancel";

            thread = new System.Threading.Thread(()=>uploadAction());
            thread.Name = "Upload thread";
            thread.IsBackground = true;
        }

       
        protected override void OnShown(EventArgs e)
        {
            base.OnShown(e);
            timer.Start();
        }

        internal bool EnabledCancelButton
        {
            set
            {
                this.InvokeMethod(() =>
                {
                    btnCancel.Enabled = value;
                });
            }
        }

        private int tickCount = 0;
        void timer_Tick(object sender, EventArgs e)
        {
            tickCount++;
            timer.Stop();
            timer.Tick -= timer_Tick;

            if (tickCount == 1)
                thread.Start();
            DrawText();
        }

        public void Info(string msg)
        {
            _infoMsg = msg;
            if (_infoMsg.Length > 92 && _infoMsg.Contains("successfully uploaded"))
                this.ClientSize = new System.Drawing.Size(352 + (_infoMsg.Length - 92) * 5, 113);// = this.Width + _infoMsg.Length - 92;

            Log.Info(msg);
            SafeDrawText();
        }

        public void Debug(string msg)
        {
            _infoMsg = msg;
            Log.Debug(msg);
#if DEBUG
            SafeDrawText();
#endif
        }

        public void Error(string msg, Exception ex)
        {
            _infoMsg = msg;

            Log.Error(msg, ex);
            SafeDrawText();

            if (sign.Controller.Connection.State == System.Communication.ConnectionState.Opened 
                && sign.Controller.Connection.User.Status == UserStatus.Online)
            {
                sign.Controller.SendAsync(Commands.UploadFileExeption);
                sign.Controller.FileManager.FreeLock();
            }

            DelayClose();
        }

        public void Error(string msg)
        {
            Error(msg, null);
        }

        public void Success(string msg)
        {
            Info(msg);
            if (sign.Controller.Connection.State == System.Communication.ConnectionState.Opened && 
                sign.Controller.Connection.User.Status == UserStatus.Online)
                    sign.Controller.FileManager.FreeLock();

            DelayClose();
        }

        private void DelayClose()
        {
            this.InvokeMethod(() =>
            {
                btnCancel.Enabled = false;
                timer.Interval = 1000;
                int i = 0;
                
                timer.Tick += (s, e) =>
                {
                    i++;
                    DrawText();
                    if (i == 3)
                    {
                        timer.Stop();
                        Close();
                        return;
                    }
                };
                timer.Start();
            });
        }

        public void SafeClose()
        {
            this.InvokeMethod(() => Close());
        }

        public void CancelFtp(string msg)
        {
            _infoMsg = msg;
            Log.Error(msg);

            Cancel();

        }

        internal void Cancel()
        {
            Cancel(true);

            if (thread != null && thread.ThreadState == System.Threading.ThreadState.Running)
            {
                try
                {
                    thread.Abort();
                }
                catch
                {
                }
            }
        }

        internal void Cancel(bool isCancelTask)
        {
            if (isCancelTask)
                cancelAction();

            Log.Info("Cancel upload.");

            this.InvokeMethod(() =>
            {
                btnCancel.Enabled = false;
                _infoMsg = "Cancel upload.";
                DrawText();

                if (sign.Controller.Connection.State == System.Communication.ConnectionState.Opened 
                    && sign.Controller.Connection.User.Status == UserStatus.Online)
                {
                    sign.Controller.SendAsync(Commands.UploadFileExeption, p =>
                    {
                        sign.Controller.FileManager.FreeLock();

                    });

                }


                if (sign.Controller.Connection.State == System.Communication.ConnectionState.Closed)
                {
                    _infoMsg = Resource.GetString(Resource.Strings.UploadFailed);
                }

                DelayClose();
            });
        }

        public void Warning(string msg)
        {           
            _infoMsg = msg;
           
            Log.Warn(msg);
            SafeDrawText();
        }


        void btnCancel_Click(object sender, System.EventArgs e)
        {
            Cancel();
        }

        protected override void OnClosed(EventArgs e)
        {
            timer.Stop();
            base.OnClosed(e);
            if (thread != null)
            {
                try
                {
                    thread.Join();
                }
                catch
                {
                }

                thread = null;
            }
        }

        static readonly Point location = new Point(32, 25);
        /// <summary>
        /// Function: Show upload info
        /// Author  : Jerry Xu
        /// Date    : 2009-1-15
        /// </summary>
        /// <param name="g">Graphics</param>
        private void SafeDrawText()
        {
            this.InvokeMethod(() => DrawText());
        }

        private void DrawText()
        {
            //if (_infoMsg.Length > 92)
            //    this.ClientSize = new System.Drawing.Size(352 + (_infoMsg.Length - 92) * 2, 113);// = this.Width + _infoMsg.Length - 92;
            textBox1.Text = _infoMsg;
            labelControl1.Text = _infoMsg;
            textEdit1.Text = _infoMsg;
            Invalidate();
        }
    }
}