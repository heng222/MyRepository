using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.UI.Controls.Library
{
    public class LibraryFileCheckEventArgs:EventArgs
    {
        public LibraryFileItem Item;
        public LibraryFileCheckEventArgs( LibraryFileItem item)
        {
            Item = item;
        }

    }
}
