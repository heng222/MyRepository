using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Library
{
    public class RemoveLibraryEventArgs:EventArgs
    {
        public readonly LibraryType Type;

        public RemoveLibraryEventArgs(LibraryType type)
        {
            Type = type;
        }
    }
}