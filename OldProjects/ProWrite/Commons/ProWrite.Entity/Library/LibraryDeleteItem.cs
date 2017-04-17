using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;

namespace ProWrite.Entity.Library
{
    public class LibraryDeleteItem
    {
        public string GroupName;
        public LibraryItem ReferrenceItem;
        public LibraryState State = LibraryState.None;
    }
}
