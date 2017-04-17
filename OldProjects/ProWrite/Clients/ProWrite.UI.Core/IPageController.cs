using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Entity.Library;

namespace ProWrite.UI.Controls
{
    public interface IPageController
    {
        void AddPage(MemoryLibraryItem model);
        void Save(MemoryLibraryItem model);
        void ClosePage(string pageName);
    }

    public interface ISaveAllController
    {
        void AddItem(IPageController controller, string name, bool isEdit, MemoryLibraryItem tag);
    }



}
