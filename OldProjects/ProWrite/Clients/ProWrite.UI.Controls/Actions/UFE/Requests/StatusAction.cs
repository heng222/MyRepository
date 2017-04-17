using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Entity.Dashboard;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls.Actions.UFE.Requests
{
    public class StatusAction : RequestActionBase
    {
        
        public SignInfo Sign
        {
            get;
            set;
        }
        private bool IsConfirm = false;

        public StatusAction(bool isConfirm)
        {
            IsConfirm = isConfirm;
        }
        public override void Perform()
        {

            SignInfo sign = ControlService.SignCombo.Current;

            if (Sign != null && Sign != sign)
                sign = Sign;
            sign.Controller.SendAsync(
                       Commands.GetStatus,
                       h =>
                       {
                           //if (h.IsSuccessed)
                           //{
                           try
                           {
                               int freeSize = h.Packet.Content.GetProperty<int>("FreeSize");
                               int totalSize = h.Packet.Content.GetProperty<int>("TotalSize");
                               //object[] obj = h.Packet.Content.GetProperty<object[]>("StatusList");


                               //if (obj != null && obj.Length > 0)
                               //{
                                   //string messageInfo = (obj[0] as Dictionary<string, object>).Values.ToArray()[3].ToString();
                                   //sign.MessageIdInfo = messageInfo;
                                   //ControlService.CurrentClip.UpdateMessageInfo = messageInfo;
                                   //if ((obj[0] as Dictionary<string, object>).Values.Count > 5)
                                   //{
                                   //    ControlService.CurrentClip.UpdateScheduleInfo = (obj[0] as Dictionary<string, object>).Values.ToArray()[5].ToString();

                                   //    ControlService.CurrentClip.UpdatePlaylist = (obj[0] as Dictionary<string, object>).Values.ToArray()[7].ToString();
                                   //}
                               //}
                               sign.FreeMemory = Convert.ToInt32(((float)freeSize / (float)totalSize) * 100);//.ToString();
                               sign.TotalSize = totalSize;
                               ControlService.DashboardTree.PopulateTree();
                           }
                           catch { }
                           //}
                           //else if(IsConfirm)
                           //    MsgBox.Warning("Get status failed,please try again.");
                       }, null);
        }
    }
}
