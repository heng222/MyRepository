using System;
using System.Collections.Generic;
using System.Text;
using DevExpress.XtraTab;
using DevExpress.XtraBars.Docking;
using System.Windows.Forms;
using ProWrite.UI.Controls.Editor;
using System.ComponentModel;
using System.Drawing;
using ProWrite.UI.Controls.Dashboard;
using System.IO;

namespace ProWrite.UI.Controls
{
    public sealed class WindowManager 
    {

        private WindowManager()
        {
        }

        public static void ShowPanel(Docks type)
        {
            ModuleControl moduleControl = ModuleManager.CurrentModuleControl as ModuleControl;
            if (moduleControl != null)
                moduleControl.ShowDockPanel(type);
        }
    }

   
    public sealed class DockMap
    {
        public static readonly Dictionary<Docks, string> Dashboard;
        public static readonly Dictionary<Docks, string> Editor;
        public static readonly Dictionary<Docks, string> Playlist;
        public static readonly Dictionary<Docks, string> Schedule;
        public static readonly Dictionary<Docks, string> Live;
        public static readonly Dictionary<Docks, string> MLPlaylist;

        static DockMap()
        {
            Dashboard = new Dictionary<Docks, string>();
            Editor = new Dictionary<Docks, string>();
            Playlist = new Dictionary<Docks, string>();
            Schedule = new Dictionary<Docks, string>();
            Live = new Dictionary<Docks, string>();
            MLPlaylist = new Dictionary<Docks, string>();

            Dashboard[Docks.CurrentClip] = "Current Clip";
            Dashboard[Docks.SignImage] = "Sign Image";
            Dashboard[Docks.SignIndicator] = "Sign Indicator";
            Dashboard[Docks.SignStatus] = "Sign Status";

            Editor[Docks.ToolBox] = "Insert Content";
            Editor[Docks.Effects] = "Effect";
            Editor[Docks.Library] = "Library";
            Editor[Docks.Properties] = "Properties";

            Playlist[Docks.Library] = "Library";
            Playlist[Docks.Properties] = "Properties";
            Playlist[Docks.NailImage] = "Thumb Nail Image";
            Playlist[Docks.TimeSliceGroup] = "Time Slice Group";

            Schedule[Docks.Library] = "Library";
            Schedule[Docks.Properties] = "Properties";
            Schedule[Docks.NailImage] = "Thumb Nail Image";

            Live[Docks.Library] = "Library";
            Live[Docks.Properties] = "Properties";
            Live[Docks.NailImage] = "Thumb Nail Image";

            MLPlaylist[Docks.Library] = "Library";
            MLPlaylist[Docks.Properties] = "Properties";
            MLPlaylist[Docks.NailImage] = "Thumb Nail Image";
            MLPlaylist[Docks.TimeSliceGroup] = "Time Slice Group";

        }


    }

    [Flags]
    public enum Docks
    {
        None = 1
        , Properties= None * 2
        , Library = Properties * 2
        , UfeLibrary = Properties * 2
        , Effects = Library * 2
        , ToolBox = Effects * 2
        , TimeSliceGroup = ToolBox * 2
        , NailImage = TimeSliceGroup * 2
        , SignImage = NailImage * 2
        , CurrentClip = SignImage * 2
        , SignStatus = CurrentClip * 2
        , SignIndicator = SignStatus * 2
    }
}
