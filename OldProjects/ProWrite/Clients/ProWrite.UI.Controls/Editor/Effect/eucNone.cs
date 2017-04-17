using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.DES;
using ProWrite.Entity.DES.Effect;

namespace ProWrite.UI.Controls.Editor.Effect
{
    public partial class eucNone : eucBase
    {
        public eucNone()
        {
            InitializeComponent();
            this.lblTitle.Top = this.Height / 2 - this.lblTitle.Height / 2;
            this.lblTitle.Left = this.Width / 2 - this.lblTitle.Width / 2;
        }
    }
}
