using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;
using ProWrite.UFE;
using ProWrite.UFE.Responses;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using System.ComponentModel;
namespace ProWrite.UI.Controls.Actions.UFE.Responses
{
    public abstract class ProxyAction : UFEAction, ISynchronizeInvoke
    {
        public abstract Commands Id { get; }

        private ISynchronizeInvoke HWND
        {
            get
            {
                return FormHelper.ActiveForm;
            }
        }

        #region ISynchronizeInvoke Members

        IAsyncResult ISynchronizeInvoke.BeginInvoke(Delegate method, object[] args)
        {
            if (HWND != null)
                return HWND.BeginInvoke(method, args);
            return null;
        }

        object ISynchronizeInvoke.EndInvoke(IAsyncResult result)
        {
            if (HWND != null)
                return HWND.EndInvoke(result);
            return null;
        }

        object ISynchronizeInvoke.Invoke(Delegate method, object[] args)
        {
            if (HWND != null)
                return HWND.Invoke(method, args);
            return null;
        }

        bool ISynchronizeInvoke.InvokeRequired
        {
            get { return HWND != null && HWND.InvokeRequired; }
        }

        #endregion
    }

    public class LoginAction : ProxyAction
    {
        public override Commands Id
        {
            get { return Commands.Login; }
        }
       
        protected override void HandleResponseSuccess(UFEPacket resp)
        {
            Controller.Connection.User.Status = UserStatus.Online;
            Controller.Connection.User.Id = resp.UserId;
            Controller.Connection.User.Role = resp.Role;

           

            LoginResponseBody body = serializer.ConvertToType<LoginResponseBody>(resp.Content);
            if (body != null)
            {
                Controller.Connection.Users = body.Users;
                Controller.Connection.ServerLibraries = body.Libraries;
            }
            body = null;

            ActionHelper.OnAfterLogin(Controller.Connection.User);
        }

        
        
    }   
}
