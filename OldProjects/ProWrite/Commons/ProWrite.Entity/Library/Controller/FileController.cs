using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Serialization;
using System.IO;
using ProWrite.Core;

namespace ProWrite.Entity.Library.Controller
{
    [Serializable]
    public abstract class FileController<T> :SimpleController<T> where T: LibraryItem,new()
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

        public override T GetByName(string name)
        {
            return Find(item => string.Equals(name, item.Name, StringComparison.OrdinalIgnoreCase));
        }

        public override bool Contains(string name)
        {
            return GetByName(name) != null;
        }

        public override bool Contains(T item)
        {
            if (item == null
                || item.IsEmpty) return false;
            return Find(p => string.Equals(p.Name, item.Name, StringComparison.OrdinalIgnoreCase) || p.Id == item.Id) != null;
        }

    }
}
