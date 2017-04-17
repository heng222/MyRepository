using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;
using ProWrite.Entity.Dashboard;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UFE.Entity;
using ProWrite.Entity.Live;

namespace ProWrite.UI.Controls.Actions.UFE.Requests
{
    public class GoLiveAction : RequestActionBase
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

            GoLive golive = new GoLive();
            golive.Mode = 1;
            sign.Controller.SendAsync(
                       Commands.GoLive,
                       h =>
                       {
                           int mode = h.Packet.Content.GetProperty<int>("Mode");

                           bool syncEnable = false;
                           var serverLibries = sign.Controller.Connection.ServerLibraries;
                           SessionInfo.Current = DataGate.SessionInfos[2];
                           var session = SessionInfo.Current;
                           int serLibsCount = serverLibries.Count;
                           int proLibraryCount = session.LibraryCategories.Length;
                           if (serLibsCount != proLibraryCount)
                               syncEnable = true;
                           else if (serLibsCount > 0)
                           {
                               syncEnable = session.UpdateLibraryItemStatus(sign);
                               //foreach (ServerLibraryItem library in serverLibries)
                               //{
                               //    foreach (ProWrite.Entity.Live.LiveCategory live in session.SessionCategories)
                               //    {
                               //        foreach (LiveMessageItem message in live.Items)
                               //        {

                               //            if (message.Name == library.Name)
                               //            {
                               //                syncEnable = false;
                               //            }
                               //        }
                               //    }
                               //}

                           }

                           LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                                   new MenuCommand{ Command = MenuCommands.GoLive,Enabled = mode!=1},
                                   new MenuCommand{ Command = MenuCommands.Sync,Enabled = syncEnable}
                             }));

                       }, golive);
        }
    }
}
