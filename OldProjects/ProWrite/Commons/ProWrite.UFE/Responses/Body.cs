using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using ProWrite.UFE.Entity;

namespace ProWrite.UFE.Responses
{
    [DataContract]
    public class CxcStatus
    {
        public long FileSystemSize;
        public float FileSystemUsage;
        public string CurrentPlayingMessage;
        public int TimeLeftOnCurrentPlayingMessage;
        public string NextMessage;
        public int? PlayLengthOfNextMessage;
        public DateTime? ScheduleFileSaveDateAndTime;
        public string NextScheduler;
    }


    [DataContract]
    public class ResponseBody { }

    [DataContract]
    public class LoginResponseBody:ResponseBody 
    {
        [DataMember]
        public List<User> Users { get; set; }

        [DataMember]
        public List<ServerLibraryItem> Libraries { get; set; }
    }

}
