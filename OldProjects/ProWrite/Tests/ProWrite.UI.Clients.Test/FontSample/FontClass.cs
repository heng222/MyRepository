using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public class FontClass
    {
        private string _fontFamilyName = "Arial";
        private FontStyle _fontStyle = FontStyle.Regular;
        private float _fontSize = 10f;

        public string FontFamilyName
        {
            set { _fontFamilyName = value; }
            get { return _fontFamilyName; }
        }

        public FontStyle FontStyle
        {
            set { _fontStyle = value; }
            get { return _fontStyle; }
        }

        public float FontSize
        {
            set { _fontSize = value; }
            get { return _fontSize; }
        }
        
    }
}
