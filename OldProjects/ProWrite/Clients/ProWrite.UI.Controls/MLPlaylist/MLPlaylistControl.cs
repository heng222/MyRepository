using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Library;

namespace ProWrite.UI.Controls.MLPlaylist
{
    public partial class MLPlaylistControl : ControlPanel<MLPlaylistInfo,MLPlaylistControl>
    {
        public MLPlaylistControl()
        {
            InitializeComponent();
        }

        protected override void DoPopulate()
        {
            base.DoPopulate();
        }

        public override void InsertLibrary(params MemoryLibraryItem[] items)
        {
            base.InsertLibrary(items);
        }

        public override void LoadModelInfo()
        {
            base.LoadModelInfo();
        }

    }
}
