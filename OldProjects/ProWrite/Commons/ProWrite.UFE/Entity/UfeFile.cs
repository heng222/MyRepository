using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using System.Web.Script.Serialization;

namespace ProWrite.UFE.Entity
{
    [Serializable]
    public class UfeFile : IdObject
    {
        public FileType Type { get; set; }
        public string Name { get; set; }
        public float Length { get; set; }
        public string CreateTime { get; set; }
        public string ModifyTime { get; set; }
        public bool IsUpdate { get; set; }

        [XmlIgnore]
        [ScriptIgnore]
        public bool HasError;

        public UploadMode UploadMode = UploadMode.Scheduler;

        public string FromFilePath { get; set; }
        public string ToFilePath { get; set; }
        public byte[] Content { get; set; }
        public long Size { get; set; }

       
    }    
}
