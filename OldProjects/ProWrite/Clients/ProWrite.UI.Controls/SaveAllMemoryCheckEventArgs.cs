using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.UI.Controls
{
    public class SaveAllMemoryCheckEventArgs:EventArgs
    {
        public SaveItem Item;
        public SaveAllMemoryCheckEventArgs(SaveItem item)
        {
            Item = item;
        }
    }
}
