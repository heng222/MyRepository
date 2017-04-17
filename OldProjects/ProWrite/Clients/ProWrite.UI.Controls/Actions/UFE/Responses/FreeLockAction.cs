using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Actions.UFE.Responses
{
    class FreeLockAction : ProxyAction
    {
        public override Commands Id
        {
            get { return Commands.FreeLock; }
        }

        protected override void HandleResponseFail(UFEPacket resp)
        {
            OnHandle();
        }

        protected override void HandleResponseSuccess(UFEPacket resp)
        {
            OnHandle();
        }

        private void OnHandle()
        {
            //Controller.Connection.Locked = false;
            //Controller.Connection.CanLock = false;

            var user = Controller.Connection.User;
            if (user.IsFtpRole && user.Status == UserStatus.Online)
            {
                Controller.Connection.CanLock = true;
                //LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                //new MenuCommand{ Command= MenuCommands.SendToSign, Enabled = false }
                //}));
            }
           
        }
    }
}
