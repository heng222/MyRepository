using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;

namespace ProWrite.Entity.Library
{
    public class LibraryFile
    {
        public string Id { get; set; }
        public string FileName { get; set; }
        public string LibraryFileName { get; set; }
        public LibraryType Type { get; set; }
        public bool IsValid { get; set; }
    }
}
