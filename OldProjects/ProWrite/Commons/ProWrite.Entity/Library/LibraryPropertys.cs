using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;

namespace ProWrite.Entity.Library
{
    [Serializable]
    public class LibraryPropertys
    {
        private string _Name;
        private int _Length;
        private LibraryType _Type;

        public LibraryPropertys()
        {
        }

        public string Name
        {
            get
            {
                return _Name;
            }
        }

        public int Length
        {
            get
            {
                return _Length;
            }
        }

        public LibraryType Type
        {
            get
            {
                return _Type;
            }
        }

        public LibraryPropertys(MemoryLibraryItem Target)
        {
            if (Target != null)
            {
                this._Type = Target.Type;
                this._Name = Target.Name;
                this._Length = Target.Length;
            }
        }
    }
}
