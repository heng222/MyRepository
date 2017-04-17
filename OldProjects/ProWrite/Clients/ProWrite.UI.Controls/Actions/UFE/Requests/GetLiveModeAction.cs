using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;
using ProWrite.Entity.Dashboard;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;

namespace ProWrite.UI.Controls.Actions.UFE.Requests
{
    public class GetLiveModeAction : RequestActionBase
    {
        public SignInfo Sign
        {
            get;
            set;
        }

        public override void Perform()
        {
            SignInfo sign = ControlService.SignCombo.Current;

            if (Sign != null && Sign != sign)
                sign = Sign;
            sign.Controller.SendAsync(
                       Commands.GetLiveState,
                       h =>
                       {
                           if (h.IsSuccessed)
                           {
                               int i = h.Packet.Content.GetProperty<int>("Mode");
                               LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                                   new MenuCommand{ Command = MenuCommands.GoLive,Enabled = i!=1}
                             }));
                           }

                       }, null);
        }
    }
}
