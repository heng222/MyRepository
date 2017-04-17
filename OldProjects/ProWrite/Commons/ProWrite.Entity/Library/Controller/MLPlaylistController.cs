using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.Entity.Library.Controller
{
    [Serializable]
    public class MLPlaylistController : FileController<MLPlaylistInfo>
    {
        public override bool Add(MLPlaylistInfo item)
        {
            if (item == null || Contains(item.Name))
                return false;

            bool flag = base.Add(item);

            OnAddCompleted(item);
            return flag;
        }

        public override LibraryItem AddFile(string file)
        {
            return null;
        }
    }
}
