using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsApplication
{
    public partial class CtrlPropertyGridDemo : UserControl
    {
        class PropertyElement
        {
            public List<PlatformID> PID { get; set; }
            public Color BackColor { get; set; }
            public string Name { get; set; }

            public PropertyElement()
            {
                this.PID = new List<PlatformID> { PlatformID.Win32NT, PlatformID.Unix };
                this.BackColor = Color.AliceBlue;
                this.Name = "user";
            }
        }

        public CtrlPropertyGridDemo()
        {
            InitializeComponent();

            InitializePropertyGrade();
        }

        private void InitializePropertyGrade()
        {
            this.propertyGrid1.Dock = DockStyle.Fill;

            this.propertyGrid1.SelectedObject = (new PropertyElement());
        }
    }
}
