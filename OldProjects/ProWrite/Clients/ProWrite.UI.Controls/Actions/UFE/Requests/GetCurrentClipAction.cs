using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Entity.Dashboard;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls.Actions.UFE.Requests
{
    public class GetCurrentClipAction:RequestActionBase
    {
        public SignInfo sign
        {
            get;
            set;
        }
        public override void Perform()
        {
            string path = "";
            sign.Controller.SendAsync(
                       Commands.LiveImage,
                       h =>
                       {
                           if (h.IsSuccessed)
                           {
                               path = h.Packet.Content.GetProperty<string>("Path");
                               if (path != null && path != "")
                               {
                                   string toFilePath = Constance.AppPath + sign.Name + ".xml";
                                   sign.Controller.Connection.FtpManager.DownLoad(path, toFilePath);

                                   var status = Serialiser<StatusInfo>.Xml.Deserialise(toFilePath);
                                   if (status != null && status.Count > 0)
                                   {
                                       sign.Status = status[0].StatusValue.ToLower();
                                       LocalMessageBus.Send(this, new SetPWLogo(sign.Status));
                                       ControlService.DashboardTree.PopulateTree();
                                       ControlService.DashboardTree.SetTreeFocusedNode(sign);
                                   }
                               }
                           }
                       }, null);


        }
    }
}
