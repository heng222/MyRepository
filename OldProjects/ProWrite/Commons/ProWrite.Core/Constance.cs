//---------------------------------------------------------------------
//
// File: Constance.cs
//
// Description:
// Restore all system constance 
//
// Author: Kevin
// 
// Modify History:
//      Jerry Xu 2008-7-9 move some const to this file: PlaylistsUsableWidth,MinZoomLength,
//          MaxZoomLength,UnitWidth,Tick,MaxZoom,MinZoom,TimeDefaultText
//      Jerry Xu 2009-3-9 Update Filter class member:ImportExport
//      Jerry Xu 2009-4-20 Add FileFilter const ImportExportMessage
//                                              ImportExportTimeSliceGroup
//                                              ImportExportPlaylist 
//                                              ImportExportSchedule 
//      Jerry Xu 2009-5-7 Update method:MaxZoom
//      Jerry Xu 2009-5-21 Add const:SmallChange,LargeChange
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//--------------------------------------------------------------------/-
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Drawing;
using System.Reflection;

namespace ProWrite.Core
{
    public static class ProductInfo
    {
        public static readonly string Version;
        public static readonly string VersionCode;
        public static readonly string Name;
        internal static string DataPath
        {
            get 
            {
                string path = Config.GetAppSettingValueBytKey("ProFilePath");
                if (!string.IsNullOrEmpty(path))
                    return path;
               
                return Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "ProWrite"/* + VersionCode*/); 
            }
        }

        static ProductInfo()
        {
            AssemblyName asmName = Assembly.GetEntryAssembly().GetName();
            Version ver = asmName.Version;
            string minor, build;
            minor = ver.Minor > 10 ? ver.Minor.ToString() : "0" + ver.Minor.ToString();
            build = ver.Build > 10 ? ver.Build.ToString() : "0" + ver.Build.ToString();

            VersionCode = string.Format("{0}.{1}{2}", ver.Major, minor, build);
            Version = "Version :1.51215 ";// +VersionCode;//release version1.0621
            Name = asmName.Name;
            //DataPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "ProWrite"/* + VersionCode*/);
        }

    }

    /// <summary>
    /// System constance
    /// </summary>
    public class Constance
    {
        /// <summary>
        /// Data file path
        /// </summary>
        public static string DataPath 
        {
            get { return ProductInfo.DataPath; }
        }//Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "ProWrite");
        /// <summary>
        /// Application path
        /// </summary>
        public static readonly string AppPath = AppDomain.CurrentDomain.BaseDirectory;

        public static readonly char DirectorySeparator = Path.DirectorySeparatorChar;

        /// <summary>
        /// Image temp path
        /// </summary>
        public static readonly string ImageTempDir = Path.Combine(DataPath, "imagetemp" + DirectorySeparator);
        public static readonly string LibraryDir = Path.Combine(DataPath, "Library" + DirectorySeparator);
        public static readonly string LibraryImageDir = Path.Combine(LibraryDir, "Image" + DirectorySeparator);
        public static readonly string LibraryVideoDir = Path.Combine(LibraryDir, "Video" + DirectorySeparator);
        public static readonly string LibraryTextDir = Path.Combine(LibraryDir, "Text" + DirectorySeparator);
        public static readonly string LibraryNailImageDir = Path.Combine(LibraryDir, "NailImage" + DirectorySeparator);
        public static readonly string EffectDataDir = Path.Combine(AppPath, "Effect" + DirectorySeparator);
        public static readonly string SignImageDir = Path.Combine(DataPath, "Image" + DirectorySeparator);
        //**Upload file
        public static readonly string LibraryUploadDir = Path.Combine(LibraryDir, "Upload" + DirectorySeparator);
        //Message        
        public static readonly string LibraryUploadMessageDir = Path.Combine(LibraryUploadDir, "Message" + DirectorySeparator);
        public static readonly string LibraryUploadLayerDir = Path.Combine(LibraryUploadMessageDir, "Layer" + DirectorySeparator);
        public static readonly string LibraryUploadEffectDir = Path.Combine(LibraryUploadMessageDir, "Effect" + DirectorySeparator);
        public static readonly string LibraryUploadImageDir = Path.Combine(LibraryUploadMessageDir, "Image" + DirectorySeparator);
        public static readonly string LibraryUploadVideoDir = Path.Combine(LibraryUploadMessageDir, "Video" + DirectorySeparator);
        public static readonly string LibraryUploadTextDir = Path.Combine(LibraryUploadMessageDir, "Text" + DirectorySeparator);
        public static readonly string LibraryUploadPaintDir = Path.Combine(LibraryUploadMessageDir, "Paint" + DirectorySeparator);
        //Playlist
        public static readonly string LibraryUploadPlaylistDir = Path.Combine(LibraryUploadDir, "Playlist" + DirectorySeparator);

        public static readonly string XmlDataFile = Path.Combine(DataPath, "data.xml");
        public static readonly string BinaryDataFile = Path.Combine(DataPath, "data.binary");
        public static readonly string MapingFile = Path.Combine(DataPath, "mapingFile.txt");

        public static readonly string LayoutDir = Path.Combine(DataPath, "Layout" + Constance.DirectorySeparator);

        public static readonly string PWFontConfigFile = Path.Combine(AppPath, "FontPackage.xml");

        public class Designers
        {
            public const string EntryEffect = "ProWrite.UI.Controls.Designer.EntryEffectEditor,ProWrite.UI.Controls";
            public const string EmphasisEffect = "ProWrite.UI.Controls.Designer.EmphasisEffectEditor,ProWrite.UI.Controls";
            public const string ExitEffect = "ProWrite.UI.Controls.Designer.ExitEffectEditor,ProWrite.UI.Controls";

            public const string MessageEmphasisEffect = "ProWrite.UI.Controls.Designer.MessageEmphasisEffectEditor,ProWrite.UI.Controls";

            public const string Video = "ProWrite.UI.Controls.Designer.VideoEditor,ProWrite.UI.Controls";

            public const string Image = "ProWrite.UI.Controls.Designer.SignImageEditor,ProWrite.UI.Controls";
            public const string Font = "ProWrite.UI.Controls.Designer.FontEditor,ProWrite.UI.Controls";

            public const string NoneCollection = "ProWrite.UI.Controls.Designer.NoneCollectionEditor,ProWrite.UI.Controls";
            public const string None = "ProWrite.UI.Controls.Designer.NoneEditor,ProWrite.UI.Controls";
            public const string ReadOnlyImage = "ProWrite.UI.Controls.Designer.ReadOnlyImageEditor,ProWrite.UI.Controls";

            public const string Enum = "ProWrite.UI.Controls.Designer.EnumTypeEditor,ProWrite.UI.Controls";


        }

        public class FileFilter
        {
            public const string Video = "All supported media files|*.avi;*.wmv;*.mpeg|avi file(*.avi)|*.avi|wmv file(*.wmv)|*.wmv|MPEG-2 file(*.mpeg)|*.mpeg";
            public const string Image = "All supported picture files|*.jpg;*.jpeg;*.gif;*.png;*.bmp;*.Tif;*.Tiff|Jpeg File(*.jpg,*.jpeg)|*.jpg;*.jpeg|Gif File(*.gif)|*.gif|Png File(*.png)|*.png|Bmp File(*.bmp)" +
                "|*.bmp|Tiff File(*.Tif,*.Tiff)|*.Tif;*.Tiff";
            public const string ImageDot = "*.jpg*.jpeg|*.gif|*.png|*.bmp|*.Tif;*.tiff";
            public const string ImagePoint = "*.jpg,*.gif,*.png,*.bmp,*.tif,*.tiff";
            public const string ImagePoint1 = "*.jpg;*.jpeg;*.gif;*.png;*.bmp;*.tif;*.tiff";
            public const string BatchLoad = "Picture Files(*.BMP;*.JPG;*.JPEG;*.GIF;*.PNG;*.TIF,*.TIFF)|*.BMP;*.JPG;*.JPEG;*.GIF;*.PNG;*.TIF;*.TIFF";//|avi file(*.avi)|*.avi|wmv file(*.wmv)|*.wmv|MPEG-2 file(*.mpeg)|*.mpeg";
            //public const string ImportExport = "Message file(*.mes)|*.mes|Time Slice Group file(*.grp)|*.grp|Playlist file(*.lst)|*.lst|Schedule file(*.sche)|*.sche|All File(*.*)|*.*";

            public const string ImportExport = "Message file(*.pme)|*.pme";
            public const string ImportExportMessage = "Message file(*.pme)|*.pme";
            public const string ImportExportTimeSliceGroup = "Time slice Group file(*.ptg)|*.ptg";
            public const string ImportExportPlaylist = "Playlist file(*.ppl)|*.ppl";
            public const string ImportExportSchedule = "Schedule file(*.psc)|*.psc";
        }

        public class FileExtensionName
        {
            public const string AVI = ".avi";
            public const string Mpeg_2 = ".mpeg";
            public const string Wmv = ".wmv";
            public const string Jpg = ".jpg";
            public const string Jpeg = ".jpeg";
            public const string Bmp = ".bmp";
            public const string Gif = ".gif";
            public const string Png = ".png";
            public const string Tif = ".tif";
            public const string Tiff = ".tiff";
            public const string Message = ".pme";
            public const string Scheduler = ".psc";
            public const string TimeSliceGroup = ".ptg";
            public const string Playlist = ".ppl";
            public const string NailImage = ".jpg";

            public const string AVI_All = "*.avi";
            public const string Mpeg_2_All = "*.mpeg";
            public const string Wmv_All = "*.wmv";
            public const string Jpg_All = "*.jpg";
            public const string Jpeg_All = "*.jpeg";
            public const string Bmp_All = "*.bmp";
            public const string Gif_All = "*.gif";
            public const string Png_All = "*.png";
            public const string Tif_All = "*.tif";
            public const string Tiff_All = "*.tiff";
            public const string Message_All = "*.pme";
            public const string Scheduler_All = "*.psc";
            public const string TimeSliceGroup_All = "*.ptg";
            public const string Playlist_All = "*.ppl";
        }

        public const int PlaylistsUsableWidth = 1000; //PlayList DragdropLayoutControl usable width by Jerry
        public const int MinZoomLength = 1000;//PlayList Zoom In width limit by Jerry
        public const int MaxZoomLength = 10000;//PlayList Zoom Out width limit by Jerry
        public const int MaxZoom = 5; //PlayList Max Zoom Out diploid limit by Jerry
        public const int MinZoom = 0; //PlayList Min Zoom In diploid limit by Jerry
        public const int MaxZoomOffset = 16;
        public const int MinZoomOffset = 1;
        public const string TimeDefaultText = "00:00:00";
        public const string TimeSeparator = ":";
        public const int ShapeOffset = 5; //add by Michael,用于判断SHAPE是否越界的边界值
        public const int ImportNameMaxLength = 60; //Import name max length limit

        public class TrackBar
        {
            public const int SmallChange = 5;
            public const int LargeChange = 5;
            public const int UnitWidth = 8;
            public const int Tick = 60;
        }

        public class Effect
        {
            public const int PlaceHolderWidth = 0;
            public const int UnitWidth = TrackBar.UnitWidth;
            public const int HalfUnitWidt = UnitWidth / 2;
            public const int SplitterWidth = 4;
        }

    }


}
