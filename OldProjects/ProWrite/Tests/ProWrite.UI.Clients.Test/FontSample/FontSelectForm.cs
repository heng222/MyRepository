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
using ProWrite.Entity.Shape;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class FontSelectForm : XtraForm
    {
        #region Variant define
        private const int FontCount = 20;
        private FontWrapper _myFont = new FontWrapper();
        //Private font array
        //From Com
        string[] PrivateFonts = new string[]
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
        string[] FontStyleArray = new string[]
            {
                "Regular",
                "Italic",
                "Bold",
                "BoldItalic",
            };
        List<string> ListPrivateFonts = new List<string>();//Private font list
        List<string> ListAllFonts = new List<string>();//All font list
        List<string> ListFontStyle = new List<string>();//Font style

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
                Init();
        }

        #region Function define
        /// <summary>
        /// Int info
        /// </summary>
        private void Init()
        {
            InitPrivateFonts();
            InitAllFonts();
            InitFontType();
            InitFontStyle();
            LoadFont(chkFontType.Checked);
        }

        /// <summary>
        /// Init font style
        /// </summary>
        private void InitFontStyle()
        {
            lstFontStyle.Items.Clear();
            lstFontStyle.Items.AddRange(FontStyleArray);            
        }

        /// <summary>
        /// Init font type : private or all
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
        /// </summary>
        private void InitPrivateFonts()
        {
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
        /// </summary>
        private void InitAllFonts()
        {
            string[] familyArray = new string[ListPrivateFonts.Count + FontFamily.Families.Length];

            ListPrivateFonts.CopyTo(familyArray);
            //FontFamily.Families.CopyTo(familyArray,20);
            Array.ConvertAll<FontFamily, string>(FontFamily.Families, delegate(FontFamily item) { return item.Name; }).CopyTo(familyArray, 20);
            ListAllFonts.AddRange(familyArray);

            ListAllFonts.Sort();
        }

        /// <summary>
        /// Load font name into lstFontName
        /// </summary>
        /// <param name="isProWriteFont">bool</param>
        private void LoadFont(bool isProWriteFont)
        {
            lstFontName.Items.Clear();
            if (isProWriteFont)
                lstFontName.Items.AddRange(ListPrivateFonts.ToArray());
            else
                lstFontName.Items.AddRange(ListAllFonts.ToArray());
        }
        #endregion

        #region Event define
        private void chkFontType_CheckedChanged(object sender, EventArgs e)
        {
            LoadFont(chkFontType.Checked);
        }
        #endregion

        private void sbtnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void sbtnOK_Click(object sender, EventArgs e)
        {
            MyFont.Name = lstFontName.Items[lstFontName.SelectedIndex].ToString();
            string fontstyle = lstFontStyle.Items[lstFontStyle.SelectedIndex].ToString();
            MyFont.Style = (FontStyle)Enum.Parse(typeof(FontStyle), fontstyle);
            MyFont.Size = int.Parse(txteFontSize.Text);
            this.Close();
        }
    }
}