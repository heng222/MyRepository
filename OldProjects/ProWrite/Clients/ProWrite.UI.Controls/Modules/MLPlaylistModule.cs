using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Library;
using ProWrite.UI.Controls.MLPlaylist;
using ProWrite.UI.Controls.CopyPaste;
using ProWrite.UI.Controls.Common;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Modules
{
    public partial class MLPlaylistModule : ModuleControl<MLPlaylistInfo,MLPlaylistTabControl,MLPlaylistControl,MLPlaylistCopyAction>
    {
        public MLPlaylistModule()
        {
            DataGate.Log.Debug("MLPlaylistModule Initialize Start.");
            InitializeComponent();
            DataGate.Log.Debug("MLPlaylistModule Initialize End.");
        }

        public override string ModuleName
        {
            get
            {
                return ModuleNames.MLPlaylist;
            }
        }

        public override LibraryType ModelType
        {
            get
            {
                return LibraryType.MLPlaylist;
            }
        }

        public override Dictionary<Docks, string> DockMap
        {
            get
            {
                return ProWrite.UI.Controls.DockMap.MLPlaylist;
            }
        }

        protected override DevExpress.XtraBars.Docking.DockManager DockManager
        {
            get
            {
                return null;
            }
        }

        protected override void ModuleShown()
        {
            base.ModuleShown();
            ControlService.LibraryTree.Controller.Type = LibraryGroup.MLPlaylistFilter;
        }

    }
}
