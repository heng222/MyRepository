using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.UFE.Entity
{
    [Serializable]
    public class LogViewGet
    {
        public int Mode { get; set; }
        public string SQL { get; set; }
        public int Type { get; set; }
        //public string SQLCount { get; set; }
        public string DateTime { get; set; }
    }
}
