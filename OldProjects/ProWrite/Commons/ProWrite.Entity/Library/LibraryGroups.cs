using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using ProWrite.Entity.Library;
using ProWrite.Core;

namespace ProWrite.Entity.Library
{
	[Serializable]
	public class LibraryGroups:ListSet<LibraryGroup>
	{
		public bool CanDeleteFileLibrary(FileLibraryItem lib)
		{
			Check.Assert(lib != null);
			foreach(LibraryGroup item in this)
				if (!item.CanDeleteLibrary(lib))
					return false;
			return true;
		}

        public LibraryDeleteItem CanDeleteFileLibraryNew(FileLibraryItem lib)
        {
            LibraryDeleteItem deleteItem = new LibraryDeleteItem();
            
            Check.Assert(lib != null);
            foreach (LibraryGroup item in this)
            {
                deleteItem = item.CanDeleteLibraryNew(lib);

                if (deleteItem.State == LibraryState.Referrence)
                {
                    deleteItem.GroupName = item.Name;
                    return deleteItem;
                }
            }
            return deleteItem;
        }

		public void PopulateRelation()
		{
			foreach (LibraryGroup item in this)
				item.PopulateRelation();
		}

		[OnDeserialized]
		private void Deserialized(StreamingContext ctx)
		{
			AddDefaultItem();
		}

		internal void AddDefaultItem()
		{
			if (Count < 1)
				Add(new LibraryGroup("Library group 1"));
		}
	}
}