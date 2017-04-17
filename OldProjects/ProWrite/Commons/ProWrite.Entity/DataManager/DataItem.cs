using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;

namespace ProWrite.Entity.DataManager
{
    [Serializable]
    public class DataItem:KeyInfo
    {
        public string Source { get; set; }
        public bool PassThrough { get; set; }
        public string Note { get; set; }

        public SourceProvider SourceProvider { get; set; }
    }

    [Serializable]
    public abstract class SourceProvider
    {
       public abstract object Content { get; }

       public DataSourceType Type { get; set; }

       public override string ToString()
       {
           if (Content != null)
               return Content.ToString();
           return base.ToString();
       }
    }

    [Serializable]
    public class DateTimeProvider : SourceProvider
    {
        public string Format { get; set; }

        public override object Content
        {
            get { return DateTime.Now.ToString(Format); }
        }
    }

    [Serializable]
    public enum DataSourceType
    {
        None,
        Tcp,
        RS232,
        COM1,
        COM2,
        Modem,
    }
}
