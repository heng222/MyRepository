using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Entity.Library;

namespace ProWrite.UI.Controls.Library
{
    public class OpenLibraryEventArgs : EventArgs
    {
        public readonly LibraryItem Item;

        public OpenLibraryEventArgs(LibraryItem item)
        {
            Item = item;
        }
    }

}
