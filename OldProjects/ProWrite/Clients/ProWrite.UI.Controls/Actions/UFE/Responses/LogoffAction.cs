using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UFE;
using System.Windows.Forms;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Actions.UFE.Responses
{
    public class LogoffAction:ProxyAction
    {
        public override Commands Id
        {
            get { return Commands.Logoff; }
        }

        public override void Perform(ProWrite.UFE.UFEPacket resp)
        {
            Controller.Connection.User.Status = UserStatus.Offline;
            base.Perform(resp);
            //Controller.Connection.Close();
        }

    }
}
