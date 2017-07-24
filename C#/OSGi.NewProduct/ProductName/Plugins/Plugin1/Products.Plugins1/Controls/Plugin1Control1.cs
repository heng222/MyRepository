using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Products.Infrastructure;
using Products.Presentation;
using Products.Plugins1.Properties;

namespace Products.Plugins1.Controls
{
    [ProductPart(ControlType = PresentationControlType.Plugin1Control1)]
    public partial class Plugin1Control1 : UserControl
    {
        public Plugin1Control1()
        {
            InitializeComponent();

            this.TextChanged += new EventHandler(control_TextChanged);
        }

        private void control_TextChanged(object sender, EventArgs e)
        {
            try
            {
                Console.WriteLine(this.Text);
            }
            catch (System.Exception /*ex*/)
            {

            }
        }

        public Icon Icon
        {
            get { return Resources.MyIcon1; }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Hello, world!");
        }
    }
}
