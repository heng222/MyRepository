using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using IscsMockInterop;

namespace CShapApp
{
    public partial class Form1 : Form
    {
        private IscsMockClr _iscsMockClr = new IscsMockClr();

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                //_iscsMockClr.ShowQtWindow(this.Handle.ToInt32());

                var hwnd = _iscsMockClr.GetWindowsId();
                var pointer = new IntPtr(hwnd);
                var iscsCtrl = Control.FromHandle(pointer);
                this.Controls.Add(iscsCtrl);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }


    }
}
