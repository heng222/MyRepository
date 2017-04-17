using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Org.Mentalis.Network.ProxySocket;

namespace ProWrite.Entity.Dashboard
{
    [Serializable]
    public class LoginInfo
    {
        public bool CanSave { get; set; }
        public string IpAddress { get; set; }
        public int Port { get; set; }
        public string ConnectionUserName { get; set; }
        public string ConnectionPassword { get; set; }
        public ProxyTypes ProxyType { get; set; }
        public string PorxyAddress { get; set; }
        public int ProxyPort { get; set; }
        public string PorxyUserName { get; set; }
        public string PorxyPassword { get; set; }
        public bool CanSaveLoginInfo { get; set; }
        public string UserName { get; set; }
        public string Password { get; set; }
    }
}
