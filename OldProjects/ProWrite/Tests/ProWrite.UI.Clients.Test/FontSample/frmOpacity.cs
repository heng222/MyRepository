using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmOpacity : Form
    {
        private double _in = 1;//in form color
        private double _out = 0.5;//leave form color
        public frmOpacity()
        {
            InitializeComponent();
        }

        private void frmOpacity_MouseEnter(object sender, EventArgs e)
        {
            this.Opacity = _in;
        }

        private void frmOpacity_MouseLeave(object sender, EventArgs e)
        {
            if (Cursor.Position.X > this.Location.X && Cursor.Position.Y > this.Location.Y && Cursor.Position.X < this.Location.X + this.Width && Cursor.Position.Y < this.Location.Y + this.Height)
                this.Opacity = _in;
            else
                this.Opacity = _out;
        }
    }
}
