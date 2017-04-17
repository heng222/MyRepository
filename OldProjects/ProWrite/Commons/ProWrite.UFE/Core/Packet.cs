using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Linq;
using System.Xml.Serialization;
using ProWrite.Core;
using ProWrite.UFE.Entity;
using System.Web.Script.Serialization;
using System.Runtime.Serialization;
using System.Communication;
using log4net;
using ProWrite.UFE.Responses;
using System.Security.Cryptography;
using Org.Mentalis.Security.Cryptography;//.SecurityServices.Cryptography;
using System.Threading;

namespace ProWrite.UFE
{
    public class ActionError
    {
        public int Id { get; set; }
        public string Message { get; set; }

        public override string ToString()
        {
            return Message;
        }
    }

    [Serializable]
    public class UFEPacket : IPacket
    {
        public int Id { get; set; }
        public Commands Command { get; set; }
        public int UserId { get; set; }
        public Role Role { get; set; }
        public object Content { get; set; }
        public string Download { get; set; }

        public ActionError ActionError { get; set; }

        [ScriptIgnore]
        public bool HasError
        {
            get
            {
                return ActionError != null;
            }
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder().AppendLine();
            sb.Append("#################" + Command.ToString() + " Inspection ####################\r\n");
            sb.Append("Id:").Append(Id).AppendLine();
            sb.Append("UserId:").Append(UserId).AppendLine();
            sb.Append("Role:").Append(Role.ToString()).AppendLine();
            if (Content != null)
                sb.Append("Content:").Append(Content.ToJson()).AppendLine();
            if (ActionError != null && !string.IsNullOrEmpty(ActionError.Message))
                sb.Append("Error:").Append(ActionError.Message);
            sb.Append("#################" + Command.ToString() + " Inspection ####################\r\n");
            return sb.ToString();
        }
    }


    public class UFEPacketCoding : JsonSerializer, ICoding<UFEPacket>
    {
        public UFEPacketCoding()
        {
        }

        public byte[] EncodePacket(UFEPacket req)
        {
            string json = Serialize(req);
            json = json.Replace(",\"Content\":null", "").Replace(",\"ActionError\":null", "");
            //log.Info("Send request packet:\t" + json);
            return json.GetBytesUTF8();
        }

        public UFEPacket DecodePacket(byte[] data)
        {
            string json = data.GetStringUTF8();
            var packet = base.Deserialize<UFEPacket>(json);
            //if (packet.HasError)
            //    log.Error("Received string request packet:\t" + json);
            //else
            //    log.Info("Received string request packet:\t" + json);
            return packet;
        }
    }

    public class EncryptionCoding : ICoding<UFEPacket>
    {
        private ICoding<UFEPacket> InnerCoding;
        private IUFEEncryption encry;
        public EncryptionCoding()
        {
            InnerCoding = new UFEPacketCoding();
            encry = new UFEEncryption();
        }

        public byte[] EncodePacket(UFEPacket req)
        {
            return encry.Encrpyt(InnerCoding.EncodePacket(req));
        }

        public UFEPacket DecodePacket(byte[] data)
        {
            return InnerCoding.DecodePacket(encry.Decrpyt(data));
        }
    }
}
