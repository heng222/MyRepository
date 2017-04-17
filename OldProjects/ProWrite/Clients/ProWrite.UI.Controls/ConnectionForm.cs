using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.UFE;
using ProWrite.UFE.Responses;
using ProWrite.Entity.Dashboard;
using ProWrite.UI.Controls.Common;
using DevExpress.XtraEditors;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.Actions.UFE.Requests;

namespace ProWrite.UI.Controls
{
    public partial class ConnectionForm : XtraForm
    {
        //bool isClosed = false;
        public ConnectionForm()
        {
        }

        protected virtual void CreateConnection() { }
        protected virtual void SubscribeEvent()
        {
            SignInfo sign = ControlService.SignCombo.Current;
            if (sign.Controller.Connection != null)
            {
                sign.Controller.Connection.ExceptionFired += new EventHandler<EventArgs<Exception>>(OnConnectionExceptionFired);
                //sign.Controller.UserManager.LoginSuccessed += OnLoginSuccessed;
                //sign.Controller.UserManager.LoginFailed += OnLoginFailed;

            }
        }

        protected virtual void OnConnectionExceptionFired(object sender, EventArgs<Exception> e)
        {
            //isClosed = true;
            Cursor = Cursors.Default;
            var action = new ConnectionExceptionAction(e.First);
            action.Perform();
        }
        protected void UnsubscribeEvent()
        {
            SignInfo sign = ControlService.SignCombo.Current;
            if (sign.Controller.Connection != null)
            {
                sign.Controller.Connection.ExceptionFired -= OnConnectionExceptionFired;
                //sign.Controller.UserManager.LoginSuccessed -= OnLoginSuccessed;
                //sign.Controller.UserManager.LoginFailed -= OnLoginFailed;

            }
        }

        protected override void OnLoad(EventArgs e)
        {
            SubscribeEvent();
            base.OnLoad(e);
        }

        protected override void OnClosed(EventArgs e)
        {
            UnsubscribeEvent();
            //CloseConnection();
            base.OnClosed(e);
        }

        //protected void CloseConnection()
        //{
        //    var controller = ControlService.SignCombo.Current.Controller;
        //    if (controller.Connection.State == System.Communication.ConnectionState.Closed)
        //        return;

        //    if (controller.Connection.User.Status != UserStatus.Online)
        //    {
        //        controller.Connection.Close();
        //        while (controller.Connection.State != System.Communication.ConnectionState.Closed)
        //            System.Threading.Thread.Sleep(50);

        //    }
        //}

        protected virtual void OnLoginSuccessed(UFEPacket resp)
        {
            Cursor = Cursors.Default;
            Close();
        }

        protected virtual void OnLoginFailed(UFEPacket resp)
        {
            Cursor = Cursors.Default;
            //CloseConnection();
            const string ftpError = "Auth fail";
            if(resp.ActionError.Message.Contains(ftpError))
            {
                MsgBox.Warning("SSH server auth fail. Disconnect the connection.");
                Close();
            }
            else
            {
                MsgBox.Warning(resp.ActionError.Message + " Please try again.");
            }
        }
    }
}
