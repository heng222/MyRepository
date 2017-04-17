//---------------------------------------------------------------------
//
// File: ControlService.cs
//
// Description:
// The control show the playlist main interface.
//
// Author: Kevin
//
// DateTime:2008-7-
//
// Modify history:
//      Jerry Xu 2008-7-11 Add the property:LibraryTree
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.Xml.Linq;
using DevExpress.XtraEditors;
using DevExpress.XtraVerticalGrid;
using ProWrite.Entity.Library;
using ProWrite.Entity.Shape;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.Dashboard;
using ProWrite.UI.Controls.Editor;
using ProWrite.UI.Controls.Library;
using DevExpress.XtraVerticalGrid.Events;
using ProWrite.UI.Controls.Playlist;
using ProWrite.Entity.Dashboard;
using ProWrite.UI.Texts;
using System.Drawing;
using ProWrite.Core;
using DevExpress.XtraBars.Ribbon;
using DevExpress.XtraBars;
using DevExpress.XtraEditors.Repository;
using System.Configuration;
using System.Threading.Tasks;
using DevExpress.XtraSpellChecker;
using System.Globalization;

namespace ProWrite.UI.Controls
{
    public sealed class ControlService
    {
        static ControlService()
        {
            string appdir = ConfigurationManager.AppSettings["ProWriteFontFile"];
            if (appdir.IndexOf(@":") == -1)
                appdir = Application.StartupPath + @"\" + appdir;
            else
                appdir = ConfigurationManager.AppSettings["ProWriteFontFile"];

            FontManager.Initialize(appdir);
            
            _libraryTree = new LibraryTree();
            _signCombo = new SignRepositoryItemLookUpEdit();
            _propertyGrid = new PropertyGridControl();
            _effectTree = new EffectTreeControl();
            _toolBox = new ToolBoxControl();
            _timeSliceControl = new TimeSliceGroupControl();
            _signImage = new SignImage();
            _signStatus = new SignStatus();

            _barButtonPosition = new BarButtonItem();
            //_barButtonPosition.CategoryGuid = new System.Guid("77795bb7-9bc5-4dd2-a297-cc758682e23d");
            //_barButtonPosition.Id = 0;
            //_barButtonPosition.Name = "siPosition";

            _statusBar = new RibbonStatusBar();
            _currentClip = new CurrentClip();
            _spellChecker = new DevExpress.XtraSpellChecker.SpellChecker();
            _signStorageIndicator = new SignStorageIndicator();

            _pictureBox = new PictureEdit();
            _pictureBox.Properties.ShowMenu = false;
            _pictureBox.Properties.SizeMode = DevExpress.XtraEditors.Controls.PictureSizeMode.Zoom;

            if (_libraryTree != null)
                _libraryTree.Controller.RemoveLibraryItemEvent += new EventHandler<RemoveLibraryEventArgs>(Controller_RemoveLibraryItemEvent);
            _fonts = new List<PWFont>();
            _fontsBitMap = new List<PWFont>();
            _fontsTrueType = new List<PWFont>();

            spellCheckTask = Task.Create((p) =>
                {
                    CultureInfo engCulture = new CultureInfo("En-us");
                    dictionary = new SpellCheckerISpellDictionary(DemoUtils.GetRelativePath("american.xlg"), DemoUtils.GetRelativePath("english.aff"), engCulture);

                    dictionary.AlphabetPath = DemoUtils.GetRelativePath("EnglishAlphabet.txt");
                    customDictorary = new SpellCheckerCustomDictionary();
                    customDictorary.Culture = engCulture;

                    SpellCheckerList.Load();
                    customDictorary.AddWords(ServiceManager.Get<SpellCheckerList>());
                });

        }

        static void Controller_RemoveLibraryItemEvent(object sender, RemoveLibraryEventArgs e)
        {
            if (e.Type == LibraryType.TimeSliceGroup && _timeSliceControl != null)
            {
                _timeSliceControl.LoadGroup();
                _timeSliceControl.EnableEditButtonState();
            }
        }
        private static int enablePlayPoistions = 0;
        private static PropertyGridControl _propertyGrid;
        private static SignRepositoryItemLookUpEdit _signCombo;
        private static RibbonStatusBar _statusBar;
        private static BarButtonItem _barButtonPosition;
        private static LibraryTree _libraryTree;
        private static FontSelectForm _fontSelectForm;
        private static readonly EffectTreeControl _effectTree;
        private static ToolBoxControl _toolBox;
        private static TimeSliceGroupControl _timeSliceControl;
        private static PictureEdit _pictureBox;
        private static SignImage _signImage;
        private static SignStatus _signStatus;
        private static CurrentClip _currentClip;
        private static DevExpress.XtraSpellChecker.SpellChecker _spellChecker;
        private static SignStorageIndicator _signStorageIndicator;
        private static List<PWFont> _fonts;
        private static List<PWFont> _fontsBitMap;
        private static List<PWFont> _fontsTrueType;

        private static Task spellCheckTask;
        private static SpellCheckerISpellDictionary dictionary;
        private static SpellCheckerCustomDictionary customDictorary;

        public static SpellCheckerISpellDictionary SpellDictionary
        {
            get
            {
                if (spellCheckTask != null)
                {
                    if (!spellCheckTask.IsCompleted)
                        spellCheckTask.Wait();
                    spellCheckTask.Dispose();
                }

                return dictionary;
            }
        }

        public static SpellCheckerCustomDictionary SpellCustomDictionary
        {
            get
            {
                if (spellCheckTask != null)
                {
                    if (!spellCheckTask.IsCompleted)
                        spellCheckTask.Wait();
                    spellCheckTask.Dispose();
                }

                return customDictorary;
            }
        }

        public static string ProWriteFontName
        {
            get { return FontManager.GetProWriteFonts()[0]; }
        }

        public static List<PWFont> FontList
        {
            get
            {
                if (_fonts.Count == 0)
                {
                    List<string> names = FontManager.GetSystemFonts();
                    foreach (string name in names)
                    {
                        PWFont font = new PWFont();
                        font.Name = name;
                        font.Size = FontManager.GetSpecifiedFontHeight(name);
                        _fonts.Add(font);
                    }
                }
                return _fonts;
            }
        }

        public static List<PWFont> BitMapFontList
        {
            get
            {
                if (_fontsBitMap.Count == 0)
                {
                    List<string> names = FontManager.GetRasterFonts();
                    foreach (string name in names)
                    {
                        PWFont font = new PWFont();
                        font.Name = name;
                        font.Size = FontManager.GetSpecifiedFontHeight(name);
                        _fontsBitMap.Add(font);
                    }
                }
                return _fontsBitMap;
            }
        }

        public static List<PWFont> TrueTypeFontList
        {
            get
            {
                if (_fontsTrueType.Count == 0)
                {
                    List<string> names = FontManager.GetTrueTypeFonts();
                    foreach (string name in names)
                    {
                        PWFont font = new PWFont();
                        font.Name = name;
                        font.Size = FontManager.GetSpecifiedFontHeight(name);
                        _fontsTrueType.Add(font);
                    }
                }
                return _fontsTrueType;
            }
        }

        public static List<int> GetFontSizes(string name)
        {
            return FontManager.GetSpecifiedFontHeight(name);
        }

        public static ushort GetFontSytleByNameAndSize(string fontName, int fontSize)
        {
            return FontManager.GetFontStyle(fontName, fontSize);
        }

        public static RepositoryItemComboBox FontCombo { get; set; } 

        public static void UpdateFontCombo(SignInfo sign)
        {
            FontCombo.Items.Clear();
            if(sign.Template.Message.TextLayer.BitmapFontOnly)
                FontCombo.Items.AddRange(BitMapFontList);
            else
            {
                FontCombo.Items.AddRange(FontList);
            }
        }

        //public static List<PWFont> FontListBitMap
        //{
        //    get
        //    {
        //        if (SignCombo.Current != null)
        //        {
        //            List<string> names;
        //            if (SignCombo.Current.Template.Message.TextLayer.ShowPWFontsOnly)
        //                names = TextMgr.GetRasterFonts();
        //            else
        //                names = TextMgr.GetSystemFonts();
        //            foreach (string name in names)
        //            {
        //                PWFont font = new PWFont();
        //                font.Name = name;
        //                font.Size = TextMgr.GetSpecifiedFontHeight(name);
        //                _fonts.Add(font);
        //            }
        //        }
        //        return _fonts;
        //    }
        //}

        public static SignImage SignImage
        {
            get { return _signImage; }
        }

        public static SignStatus SignStatus
        {
            get { return _signStatus; }
        }

        public static CurrentClip CurrentClip
        {
            get { return _currentClip; }
        }
        
        public static DevExpress.XtraSpellChecker.SpellChecker SpellChedker
        {
            get 
            { 
                return _spellChecker;
            }
        }

        public static DashboardTree DashboardTree { get; internal set; }

        public static SignStorageIndicator SignStorageIndicator
        {
            get { return _signStorageIndicator; }
        }

        public static void RefreshPropertyGrid(object o)
        {
            if (_propertyGrid.SelectedObject != null && o == _propertyGrid.SelectedObject)
            {
                using (MemoryStream st = new MemoryStream())
                {
                    _propertyGrid.SaveLayoutToStream(st);
                    st.Seek(0, SeekOrigin.Begin);

                    _propertyGrid.SelectedObject = null;
                    _propertyGrid.SelectedObject = o;

                    //_propertyGrid.SetFontRepositoryItem();
                    _propertyGrid.RestoreLayoutFromStream(st);
                }
            }
            else
            {
                _propertyGrid.SelectedObject = null;
                _propertyGrid.SelectedObject = o;
            }

        }

        public static PictureEdit NailImageBox
        {
            get { return _pictureBox; }
        }

        public static SignRepositoryItemLookUpEdit SignCombo
        {
            get { return _signCombo; }
        }

        public static RibbonStatusBar StatusBar
        {
            get { return _statusBar; }
        }

        public static BarButtonItem BarButton
        {
            get { return _barButtonPosition; }
        }
        public static LibraryTree LibraryTree
        {
            get { return _libraryTree; }
        }

        public static EffectTreeControl EffectTree
        {
            get { return _effectTree; }
        }

        public static ToolBoxControl ToolBox
        {
            get { return _toolBox; }
        }

        public static TimeSliceGroupControl TimeSliceControl
        {
            get { return _timeSliceControl; }
        }

        public static void SetEditorLibraryTree()
        {
            _libraryTree.Controller.Type = LibraryGroup.EditorFilter;
        }

        public static void SetPlaylistLibraryTree()
        {
            _libraryTree.Controller.Type = LibraryGroup.PlayListFilter;
        }

        public static void SetScheduleLibraryTree()
        {
            _libraryTree.Controller.Type = LibraryGroup.SchedulerFilter;
        }

        public static PropertyGridControl PropertyGrid
        {
            get { return _propertyGrid; }
        }

        public static void EnableCopyMenu(bool enabled)
        {
            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                new MenuCommand(MenuCommands.Copy,enabled)
                , new MenuCommand(MenuCommands.Delete, enabled)
                }));
        }

        public static void EnableZoom(MenuCommands command, bool enable)
        {
            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand(command,enable)));
        }

        public static void CancelPoistions()
        {
            enablePlayPoistions++;
        }
        public static void RestorePoistions()
        {
            enablePlayPoistions--;
        }
        public static bool IsCancelPositions
        {
            get { return enablePlayPoistions == 0; }
        }
        #region Live
        //public static SignInfo SignCombo.Current {get;set;}
        //public static UFE.Live1.LibraryTree LiveTree { get; set; }
        #endregion
        public static void Dispose()
        {
            _propertyGrid.Dispose();
            _libraryTree.Dispose();
            _signCombo.Dispose();
            FontManager.Release();
        }

        public static Color MouseOverColor = Color.FromArgb(255, 216, 83);
        public static Color MouseDownColor = Color.FromArgb(247, 148, 73);
        public static Color MouseLeaveColor = Color.FromArgb(238, 238, 238);

        private class FontInfo
        {
            public string Name;
            public FontStyle Style;
            public int Size;
            public bool AutoFont;
            public string FileName;
        }

        private static XElement _xele = null;
        private static XElement XElement
        {
            get
            {
                if (_xele == null)
                {
                    _xele = XElement.Load(Constance.PWFontConfigFile);

                }

                return _xele;
            }
        }

        public static bool CanPWFontBold(int PWFontSize)
        {
            IEnumerable<XElement> tests =
                from el in XElement.Elements("Package").Elements("Font")
                where (int)el.Element("Size") == PWFontSize && (string)el.Element("Style") == "Bold"
                select el;
            if (tests.Count() != 0)
                return true;
            else
            {
                return false;
            }
        }

        public static bool CanPWFontBoldItalic(int PWFontSize)
        {
            IEnumerable<XElement> tests =
                from el in XElement.Elements("Package").Elements("Font")
                where (int)el.Element("Size") == PWFontSize && (string)el.Element("Style") == "BoldItalic"
                select el;
            if (tests.Count() != 0)
                return true;
            else
            {
                return false;
            }
        }

        public static bool CanPWFontItalic(int PWFontSize)
        {
            IEnumerable<XElement> tests =
                from el in XElement.Elements("Package").Elements("Font")
                where (int)el.Element("Size") == PWFontSize && (string)el.Element("Style") == "Italic"
                select el;
            if (tests.Count() != 0)
                return true;
            else
            {
                return false;
            }
        }
    }
}
