using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.UI.Controls.Library
{
    public class LibraryMessageCheckEventArgs:EventArgs
    {
        public LibraryMessageItem Item;
        public LibraryMessageCheckEventArgs(LibraryMessageItem item)
        {
            Item = item;
        }
    }
}
