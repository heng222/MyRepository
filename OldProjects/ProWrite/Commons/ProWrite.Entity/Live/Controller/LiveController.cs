using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using ProWrite.Entity.Library;
using ProWrite.Entity.Library.Controller;

namespace ProWrite.Entity.Live.Controller
{
    [Serializable]
    public abstract class LiveController
    {
        [NonSerialized]
        [XmlIgnore]
        private EventHandler<LibraryEventArgs> _addCompleted;
        public event EventHandler<LibraryEventArgs> AddCompleted
        {
            add { _addCompleted += value; }
            remove { _addCompleted -= value; }
        }

        protected virtual void OnAddCompleted(LibraryItem item)
        {
            MemoryLibraryItem lib = item as MemoryLibraryItem;
            if (lib != null)
                ProjectInfo.Current.Recents.Add(lib);

            if (_addCompleted != null)
                _addCompleted(this, new LibraryEventArgs(item));
        }


        public abstract LibraryItem AddFile(string file);

    }
}
