using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web.Script.Serialization;
using System.Xml.Serialization;
using ProWrite.Core;

namespace ProWrite.UFE.Entity
{

    [XmlRoot("user")]
    [Serializable]
    public class User
    {
        private string _password;
        private string _securityPwd;

        [XmlElement("name")]
        public string Account { get; set; }
        [XmlElement("password")]
        public string Password
        {
            get { return _securityPwd; }
            set
            {
                if (value != _password)
                {
                    _password = value;
                    _securityPwd = Safe.MD5Encrpyt(_password);
                }
            }
        }

        [ScriptIgnore]
        public string NoSecurityPWD
        {
            get { return _password; }
            set { _password = value; }
        }
        public int Id { get; set; }
        public Role Role { get; set; }

        private UserStatus status;
        public UserStatus Status
        {
            get { return status; }
            set
            {
                status = value;
            }
        }

        [ScriptIgnore]
        public bool IsCommandRole
        {
            get
            {
                return Role >= Role.Commands;
            }
        }

        [ScriptIgnore]
        public bool IsFtpRole
        {
            get { return Role == Role.FileTransfer || Role >= Role.All; }
        }


        [ScriptIgnore]
        public bool IsAdminRole
        {
            get { return Role >= Role.Administrator; }
        }

    }

}
