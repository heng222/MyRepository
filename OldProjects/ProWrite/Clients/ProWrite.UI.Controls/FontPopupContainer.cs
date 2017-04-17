using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.Entity.Shape;

namespace ProWrite.UI.Controls
{
    public partial class FontPopupContainer : DevExpress.XtraEditors.PopupContainerControl
    {
        private List<PWFont> _trueTypeFonts;
        private List<PWFont> _bitMapFonts;
        private ImageList _fontImageList;

        public FontPopupContainer()
        {
            InitializeComponent();
            this.imgLstfonts.SelectedValueChanged += new EventHandler(imgLstfonts_SelectedValueChanged);
        }

        void imgLstfonts_SelectedValueChanged(object sender, EventArgs e)
        {
            OnFontSelectChanged();
        }

        private EventHandler _fontSelectChanged = null;
        public event EventHandler FontSelectChanged
        {
            add { _fontSelectChanged += value; }
            remove { _fontSelectChanged -= value; }
        }

        private void OnFontSelectChanged()
        {
            if (_fontSelectChanged != null)
                _fontSelectChanged(this, EventArgs.Empty);
        }

        public FontPopupContainer(List<PWFont> trueTypeFonts, List<PWFont> bitMapFonts)
            : this()
        {
            _trueTypeFonts = trueTypeFonts;
            _bitMapFonts = bitMapFonts;
            

            int imageWidth = 16;
            int imageHeight = 16;
            _fontImageList = new ImageList();
            _fontImageList.ImageSize = new Size(imageWidth, imageHeight);
            _fontImageList.Images.Add(Resources.Resource.GetImage(Resources.Resource.Images.BitMap16));
            _fontImageList.Images.Add(Resources.Resource.GetImage(Resources.Resource.Images.TrueType16));
            imgLstfonts.ImageList = _fontImageList;
            string oldValue = string.Empty;
            ckEditBitmapFontOnly.Checked = true;
            //UpdateFontList(true);
        }

        private void UpdateFontList(bool isShowBitmapFontOnly)
        {
            //imgLstfonts.BeginUpdate();
            try
            {
                imgLstfonts.Items.Clear();
                foreach (PWFont font in _trueTypeFonts)
                {
                    imgLstfonts.Items.Add(font.Name, 0);
                }
                if(isShowBitmapFontOnly)
                    return;
                foreach (PWFont font in _bitMapFonts)
                {
                    imgLstfonts.Items.Add(font.Name, 1);
                }
            }
            finally
            {
                imgLstfonts.Invalidate();
                //imgLstfonts.CancelUpdate(); ;
            }
        }

        void ClosePopup()
        {
            if (OwnerEdit != null)
                OwnerEdit.ClosePopup();
        }

        void ckEditBitmapFontOnly_CheckedChanged(object sender, System.EventArgs e)
        {
            UpdateFontList(ckEditBitmapFontOnly.Checked);
        }


        void imgLstfonts_DoubleClick(object sender, System.EventArgs e)
        {
            ClosePopup();
        }

        void imgLstfonts_KeyDown(object sender, System.Windows.Forms.KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                if (FindForm() != null)
                    FindForm().Validate();
                ClosePopup();
            }
        }

        public string SelectedFont
        {
            get { return imgLstfonts.SelectedValue as string;}
            set
            {
                int index = imgLstfonts.FindString(value);
                imgLstfonts.SelectedIndex = index;
//                imgLstfonts.SelectedItem = value;
            }
        }

        public bool IsShowBitmapFontOnly
        {
            get { return this.ckEditBitmapFontOnly.Checked; }
            set { this.ckEditBitmapFontOnly.Checked = value; }
        }

    }
}
