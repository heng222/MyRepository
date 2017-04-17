using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core;
using ProWrite.UI.Controls.Playlist;

namespace ProWrite.UI.Controls.UndoRedo.Action
{
    public class PlaylistItemInsertAction : UndoAction
    {
        private IPlaylistItemService _dragDropControl;
        private PlaylistItemControl _btn;
        private int _index;
        public PlaylistItemInsertAction(IPlaylistItemService dragDropControl, PlaylistItemControl btn, int index)
        {
            this._dragDropControl = dragDropControl;
            this._btn = btn;
            this._index = index;
            Name = "Insert Message to playlist";
        }

        public override void Undo()
        {
            _dragDropControl.RemoveAt(_index);
            //_dragDropControl.OnPaint();
        }

        public override void Redo()
        {
            _dragDropControl.Insert(_btn, _index, true);
            //_dragDropControl.OnPaint();
        }
    }

    public class PlaylistItemMoveAction : UndoAction
    {
        private IPlaylistItemService _dragDropControl;
        private int _sourceIndex;
        private int _destIndex;
        public PlaylistItemMoveAction(IPlaylistItemService pDragDropControl, int sourceIndex, int destIndex)
        {
            this._dragDropControl = pDragDropControl;
            this._sourceIndex = sourceIndex;
            this._destIndex = destIndex;
            Name = "Move message in playlist";
        }

        public override void Undo()
        {
            int source;
            int dest;
            //Move forward
            if (_sourceIndex > _destIndex)
            {
                source = _destIndex;
                dest = _sourceIndex + 1;
            }
            else //Move backward
            {
                source = _destIndex - 1;
                dest = _sourceIndex;
            }

            _dragDropControl.MoveItem(source, dest);
        }

        public override void Redo()
        {
            _dragDropControl.MoveItem(_sourceIndex, _destIndex);
        }
    }

    public class PlaylistItemRemoveAtAction : UndoAction
    {
        private IPlaylistItemService _dragDropControl;
        private PlaylistItemControl _btn;
        private int _index;
        public PlaylistItemRemoveAtAction(IPlaylistItemService dragDropControl, PlaylistItemControl btn, int index)
        {
            this._dragDropControl = dragDropControl;
            this._btn = btn;
            this._index = index;
            Name = "Delete message from playlist";
        }

        public override void Undo()
        {
            _dragDropControl.Insert(_btn, _index, true);
        }

        public override void Redo()
        {
            _dragDropControl.RemoveAt(_index);
        }
    }
}
