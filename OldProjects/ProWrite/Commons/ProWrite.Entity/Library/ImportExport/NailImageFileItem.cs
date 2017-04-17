using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;

namespace ProWrite.Entity.Library.ImportExport
{
    [Serializable]
    public class NailImageFileItem
    {
        public string MemoryName;
        public string Name;
        public LibraryType Type;
        public byte[] Content;        
    }
}
