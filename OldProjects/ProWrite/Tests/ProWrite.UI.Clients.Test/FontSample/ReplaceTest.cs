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
    public partial class ReplaceTest : Form
    {
        public ReplaceTest()
        {
            InitializeComponent();
        }

        private void ReplaceTest_Load(object sender, EventArgs e)
        {
            //textBox1.Text.Replace("aa", "cc");

            string errString = "This docment uses 3 other docments to docment the docmentation";

            

            // Correct the spelling of "document".

            string correctString = errString.Replace("docment", "document");

            string test = "aabbbbb";
            string testReplace = test.Replace("aa", "test");
            textBox1.Text = testReplace;

        }

        private void ReplaceTest_MouseEnter(object sender, EventArgs e)
        {
            //TODO:
            //透明度修改为1
            this.Opacity = 1;
        }

        private void ReplaceTest_MouseLeave(object sender, EventArgs e)
        {
            //Rectangle bounds = this.RectangleToScreen(this.ClientRectangle);
            //if (!bounds.Contains(Cursor.Position))
            //{
            //    this.Opacity = 0.5;
            //}

            //if (this.FindForm() != this)
            //    this.Opacity = 0.5;

            //Point pt =  this.PointToClient(Cursor.Position);
            //int b = Cursor.Position.X;
            //TODO:
            string a = "b";
            //if (Controls.GetChildIndex(sender as Control) > 0)
            //    return;
            //设置透明度变为0.5

            if (Cursor.Position.X > this.Location.X && Cursor.Position.Y > this.Location.Y && Cursor.Position.X < this.Location.X + this.Width && Cursor.Position.Y < this.Location.Y + this.Height)
                this.Opacity = 1;
            else
                this.Opacity = 0.5;
        }

        private void ReplaceTest_Leave(object sender, EventArgs e)
        {
            //TODO:
            string a = "b";
            //if (Controls.GetChildIndex(sender as Control) > 0)
            //    return;
            //设置透明度变为0.5
        }
    }
}
