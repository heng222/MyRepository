using System;
using System.Collections.Generic;
using System.Text;

namespace ProWrite.UI.Controls.Playlist
{
    public interface IPlaylistItemService
    {
        void RemoveAt(int index);
        void Insert(PlaylistItemControl item, int index, bool isNew);
        void MoveItem(int sourceIndex, int destIndex);
        //void OnPaint();
    }
}
