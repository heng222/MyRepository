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
    public partial class frmButtonBackColor : Form
    {
        public static Color MouseOverColor = Color.FromArgb(10199664);
        public static Color MouseDownColor = Color.FromArgb(12369084);
        public static Color MouseLeaveColor = Color.FromArgb(15658734);
        public frmButtonBackColor()
        {
            InitializeComponent();
            Button button;
            button = new Button();
            button.Location = new Point(50, 50);
            button.Text = "test";
            button.MouseDown += new MouseEventHandler(button_MouseDown);
            button.MouseHover += new EventHandler(button_MouseHover);
            button.MouseLeave += new EventHandler(button_MouseLeave);
            //button.BackColor = MouseDownColor;
            Controls.Add(button);
            //button = new Button();
            //button.BackColor = MouseOverColor;
            //Controls.Add(button);
            //button = new Button();
            //button.BackColor = MouseLeaveColor;
            //Controls.Add(button);
        }

        void button_MouseLeave(object sender, EventArgs e)
        {
            Button button = sender as Button;
            button.BackColor = button.BackColor == MouseDownColor ? MouseDownColor : MouseLeaveColor;
        }

        void button_MouseHover(object sender, EventArgs e)
        {
            Button button = sender as Button;
            button.BackColor = button.BackColor == MouseDownColor ? MouseDownColor : MouseOverColor;
        }

        void button_MouseDown(object sender, MouseEventArgs e)
        {
            Button button = sender as Button;
            button.BackColor = MouseDownColor;
            //button.ba
        }
    }
}
