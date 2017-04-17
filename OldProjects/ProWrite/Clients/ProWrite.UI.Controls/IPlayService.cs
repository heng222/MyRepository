using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.UI.Controls.Editor;
using System.Windows.Forms;
using System.Drawing;
using ProWrite.Entity.DES;

namespace ProWrite.UI.Controls
{
    public enum PlayMode:byte
    {
        Editor,
        Playlist,
    }

    public interface IPlayService
    {
        string PlayName { get; }
        PlayMode Mode { get;}
        Control PlayPanel { get; }
        VideoLayerCollection[] OnPlay();
        void OnPlaying();
        void OnPlayCompleted();
    }
}
