//---------------------------------------------------------------------
//
// File: FontSelectForm.cs
//
// Description:
// Font select form class
//
// Author: Jerry Xu 2008-8-18
//
// Modify history:
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using DevExpress.XtraEditors;
using DevExpress.XtraEditors.Controls;
using ProWrite.Core;
using ProWrite.Entity.Shape;
using ProWrite.Resources;

namespace ProWrite.UI.Controls.Editor
{
    public partial class FontSelectForm : XtraForm, ISupportGlobalization
    {
        #region Variant define
        private const int FontCount = 20;
        private const int Max_FontSize = 72;
        private const int Min_FontSize = 6;
        private FontWrapper _myFont = new FontWrapper();
        //Private font array
        //From Com
        static string[] PrivateFonts = new string[]
            {
                "PL 05 Helv Mono Numbers",
                "PL 06 CAPS BOLD",
                "PL 06 Helv CAPS",
                "PL 07 Bernard",
                "PL 07 Caps Monospaced",
                "PL 07 Danielle",
                "PL 07 Donna",
                "PL 07 Draconian",
                "PL 07 Helv Bold Caps",
                "PL 07 Helvetica CAPS",
                "PL 07 Sans",
                "PL 07 Sans FIxed Width",
                "PL 07 Sans Narrow",
                "PL 08 Helv Narrow",
                "PL 08d Helv Bold",
                "PL 11D Helv Bold",
                "PL 11D MonoSpaced",
                "PL Fixed 05 Helv CPS",
                "Trans-Lux Pictorials",
                "Trans-Lux Large Pictorials",
            };
        static FontStyleInfo[] FontStyleArray = new FontStyleInfo[]
            {
                new FontStyleInfo( "Regular", FontStyle.Regular),
                new FontStyleInfo( "Italic", FontStyle.Italic),
                new FontStyleInfo( "Bold", FontStyle.Bold),
                new FontStyleInfo( "Bold Italic", FontStyle.Bold|FontStyle.Italic),
            };
        List<string> ListPrivateFonts = new List<string>();//Private font list
        List<string> ListAllFonts = new List<string>();//All font list
        List<FontStyleInfo> ListFontStyle = new List<FontStyleInfo>();//Font style

        private class FontStyleInfo
        {
            public string Name;
            public FontStyle Style;

            public FontStyleInfo(string name,FontStyle style)
            {
                Name = name;
                Style = style;
            }

            public override string ToString()
            {
                return Name;
            }
        }

        public FontWrapper MyFont
        {
            set { _myFont = value; }
            get { return _myFont; }
        }
        #endregion

        public FontSelectForm()
        {
            InitializeComponent();
            if (!DesignMode)
            {
                InitializeResource();
                Init();
            }
        }

        #region Function define
        /// <summary>
        /// Function: Int info
        /// Author  : Jerry Xu
        /// Date    : 2008-8-19
        /// </summary>
        private void Init()
        {
            //Config spinEdit font size info
            seFontSize.Properties.Mask.EditMask = "f0";
            seFontSize.Properties.MaxValue = 72;
            seFontSize.Properties.MinValue = 1;
            seFontSize.Properties.NullText = "1";

            //Init font info
            InitPrivateFonts();
            InitAllFonts();
            InitFontType();            
            if (_myFont == null)
                _myFont = new FontWrapper();
            //If private font
            if (ListPrivateFonts.Contains(_myFont.Name))
                chkFontType.Checked = true;
            else
                chkFontType.Checked = false;
            LoadFont(chkFontType.Checked,_myFont.Name);
            InitFontStyle();
            LoadFontStyle(_myFont.Style);
            seFontSize.Text = ((int)_myFont.Size).ToString();
        }

        /// <summary>
        /// Init font style
        /// Author  : Jerry Xu
        /// Date    : 2008-8-19
        /// </summary>
        private void InitFontStyle()
        {
            //FontFamily family;
            for (int i = 0; i < FontStyleArray.Length; i++)
            {
                //family = new FontFamily("Fixedsys");
                //family = new FontFamily(PrivateFonts[i]);
                ListFontStyle.Add(FontStyleArray[i]);
            }
            //ListFontStyle.Sort();
        }

        /// <summary>
        /// Load font style
        /// Author  : Jerry Xu
        /// Date    : 2008-8-19
        /// </summary>
        private void LoadFontStyle(FontStyle style)
        {
            //Clear items
            lstFontStyle.Items.Clear();
            //Init items
            lstFontStyle.Items.AddRange(FontStyleArray);

            //Set seleted item
            if (style.ToString() != string.Empty)
            {                
                for (int i = 0; i < FontStyleArray.Length; i++)
                {
                    if(FontStyleArray[i].Style==style)
                        lstFontStyle.SelectedIndex = i;
                }
            }
            
        }

        /// <summary>
        /// Init font type : private or all
        /// Author  : Jerry Xu
        /// Date    : 2008-8-19
        /// </summary>
        private void InitFontType()
        {
            chkFontType.Checked = true;
            //cbxFontType.Items.Clear();
            //cbxFontType.Items.AddRange(new string[] { "Private", "Public" });
            //cbxFontType.SelectedIndex = 0;
        }

        /// <summary>
        /// Init private font list
        /// Author  : Jerry Xu
        /// Date    : 2008-8-19
        /// </summary>
        private void InitPrivateFonts()
        {
            //Init private fonts
            //FontFamily family;
            for (int i = 0; i < PrivateFonts.Length; i++)
            {
                //family = new FontFamily("Fixedsys");
                //family = new FontFamily(PrivateFonts[i]);
                ListPrivateFonts.Add(PrivateFonts[i]);
            }
            ListPrivateFonts.Sort();
        }

        /// <summary>
        /// Init all font list
        /// Author  : Jerry Xu
        /// Date    : 2008-8-19
        /// </summary>
        private void InitAllFonts()
        {
            //Init list all fonts
            string[] familyArray = new string[ListPrivateFonts.Count + FontFamily.Families.Length];

            ListPrivateFonts.CopyTo(familyArray);
            //FontFamily.Families.CopyTo(familyArray,20);
            Array.ConvertAll<FontFamily, string>(FontFamily.Families, delegate(FontFamily item) { return item.Name; }).CopyTo(familyArray, 20);
            ListAllFonts.AddRange(familyArray);
            //Re sort items
            ListAllFonts.Sort();
        }

        /// <summary>
        /// Load font name into lstFontName
        /// Author  : Jerry Xu
        /// Date    : 2008-8-19
        /// </summary>
        /// <param name="isProWriteFont">bool</param>
        /// <param name="fontName">string</param>
        private void LoadFont(bool isProWriteFont,string fontName)
        {
            //Clear items
            lstFontName.Items.Clear();
            //Init items
            if (isProWriteFont)
                lstFontName.Items.AddRange(ListPrivateFonts.ToArray());
            else
                lstFontName.Items.AddRange(ListAllFonts.ToArray());
            //Set selected item
            if(fontName!=string.Empty)
                lstFontName.SelectedIndex = lstFontName.Items.IndexOf(fontName);
        }

        #region ISupportGlobalization Members
        private bool _isSupportGlobalization;

        /// <summary>
        /// Get or set whether it support internationalization function
        /// </summary>
        public bool IsSupportGlobalization
        {
            get
            {
                return _isSupportGlobalization;
            }
            set
            {
                _isSupportGlobalization = value;
            }
        }

        /// <summary>
        /// Initialize resource information
        /// </summary>
        public void InitializeResource()
        {
            chkFontType.Text = Resource.GetString(Resource.Strings.EditerFontSelectFormFontTypeText);
            lblFontName.Text = Resource.GetString(Resource.Strings.EditerFontSelectFormFontText);
            lblFontStyle.Text = Resource.GetString(Resource.Strings.EditerFontSelectFormFontStyleText);
            lblFontSize.Text = Resource.GetString(Resource.Strings.EditerFontSelectFormFontSizeText);
            sbtnOK.Text = Resource.GetString(Resource.Strings.OK);
            sbtnCancel.Text = Resource.GetString(Resource.Strings.Cancel);
        }

        /// <summary>
        /// Refresh the resource if it support internationalization ,otherwise don't refresh
        /// </summary>
        public void RefreshResource()
        {
            if (IsSupportGlobalization)
                InitializeResource();
        }
        #endregion //ISupportGlobalization Members
        #endregion

        #region Event define
        private void chkFontType_CheckedChanged(object sender, EventArgs e)
        {
            //Change font type (Private or ALL)
            if(lstFontName.SelectedValue==null)
                LoadFont(chkFontType.Checked, _myFont.Name);
            else
                LoadFont(chkFontType.Checked,lstFontName.SelectedValue.ToString());
        }

        private void sbtnCancel_Click(object sender, EventArgs e)
        {
			DialogResult = DialogResult.Cancel;
			this.Close();
        }

        private void sbtnOK_Click(object sender, EventArgs e)
        {
            //Set font wrapper value
            MyFont.Name = lstFontName.Items[lstFontName.SelectedIndex].ToString();
            MyFont.Style = (lstFontStyle.SelectedItem as FontStyleInfo).Style;
            MyFont.Size = int.Parse(seFontSize.Text);
			DialogResult = DialogResult.OK;
			this.Close();
        }
        #endregion

       
    }
}