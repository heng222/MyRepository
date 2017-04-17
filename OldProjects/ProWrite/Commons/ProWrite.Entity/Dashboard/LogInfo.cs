using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.Entity.Dashboard
{
    [Serializable]
    public class LogInfo
    {
        public LogInfo()
        { 
        }

        private string _version;
        public string Version
        {
            get { return _version; }
            set 
            {
                _version = value;
            }
        }

        private string _date;
        public string Date
        {
            get { return _date; }
            set { _date = value; }
        }

        private string _level;
        public string Level
        {
            get { return _level; }
            set { _level = value; }
        }

        private string _content;
        public string Content
        {
            get { return _content; }
            set { _content = value; }
        }
    }
}
