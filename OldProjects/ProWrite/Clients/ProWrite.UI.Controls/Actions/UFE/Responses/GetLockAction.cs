using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.Scheduler;
using ProWrite.Resources;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Actions.UFE.Responses
{
    abstract class LockAction : ProxyAction
    {
        protected bool IsCurrentUser;

        public override void Perform(UFEPacket resp)
        {
            IsCurrentUser = false;
            //Controller.Connection.Locked = false;
            Controller.Connection.CanLock = false;

            int userId = resp.Content.GetProperty<int>("OwnerId");
            IsCurrentUser 
                = userId == Controller.Connection.User.Id;

            //Controller.Connection.Locked = IsCurrentUser;

            var user = Controller.Connection.User;
            if (user.IsFtpRole)
                Controller.Connection.CanLock = !IsCurrentUser;

            base.Perform(resp);

            if (IsCurrentUser)
                SetMenuItems(true);
        }

        private static void SetMenuItems(bool enabled)
        {
            //LocalMessageBus.Send(null, new MenuMessage(
            //                         new MenuCommand
            //                         {
            //                             Command = MenuCommands.SendToSign,
            //                             Enabled = enabled
            //                                && ScheduleControl.Current != null
            //                                && ControlService.LibraryTree.Controller.GetNode(ScheduleControl.Current.Model) != null
            //                         }));
        }
    }

    class GetLockAction : LockAction
    {
        public override Commands Id
        {
            get { return Commands.GetLock; }
        }
    }
}
