using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Core;
using System.Globalization;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmFontColor : Form
    {
        public frmFontColor()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Color color = Color.Blue;
            UInt32 intColor = UInt32.Parse(ColorToString(color, NumberType.Hex),NumberStyles.HexNumber);
        }

        public static string ColorToString(Color _color, NumberType type)
        {
            string str = "";

            str += _color.A.ToString("X").Length > 1 ? _color.A.ToString("X") : "0" + _color.A.ToString("X");
            str += _color.B.ToString("X").Length > 1 ? _color.B.ToString("X") : "0" + _color.B.ToString("X");
            str += _color.G.ToString("X").Length > 1 ? _color.G.ToString("X") : "0" + _color.G.ToString("X");
            str += _color.R.ToString("X").Length > 1 ? _color.R.ToString("X") : "0" + _color.R.ToString("X");

            if (type == NumberType.Hex)
                return "0x"+str;

            UInt32 b = UInt32.Parse(str, NumberStyles.HexNumber);
            return b.ToString();
        }    
    }
}
