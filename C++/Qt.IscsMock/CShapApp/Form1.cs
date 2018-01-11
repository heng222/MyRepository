using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using IscsMockInterop;
using System.Runtime.InteropServices;

namespace CShapApp
{
    public partial class Form1 : Form
    {
        [DllImport("user32.dll")]
        public static extern IntPtr FindWindow(string lpClassName, string lpWindowName);
        //var ptr = FindWindow(null, "MyWidget");

        private IscsMockClr _iscsMockClr = new IscsMockClr();

        public Form1()
        {
            InitializeComponent();

            QtDllNative.InitializeQtLib();
        }

        #region "private methods"

        #endregion

        private void ShowPscada_Click(object sender, EventArgs e)
        {
            try
            {
                //ShowQtDialog();

                //_iscsMockClr.Initialize(this.Handle);
                //_iscsMockClr.ShowWindow();
                QtDllNative.ShowScadaWindow(this.tabPagePscada.Handle);
                
                //var pointer = QtDllNative.GetScadaWindow();
                //var ctrol = Control.FromChildHandle(pointer);

                //if (ctrol != null)
                //{
                //    tabPageBas.Controls.Add(ctrol.Controls[0]);
                //}
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void btnShowBasView_Click(object sender, EventArgs e)
        {
            try
            {
                QtDllNative.ShowBasWindow(this.tabPageBas.Handle);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }


    public class QtDllNative
    {
        [DllImport("qtdialog.dll", EntryPoint = "Initialize", CallingConvention = CallingConvention.Cdecl)]
        public static extern int InitializeQtLib();

        [DllImport("qtdialog.dll", EntryPoint = "ShowScadaWindow", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ShowScadaWindow(IntPtr hwnd);
        [DllImport("qtdialog.dll", EntryPoint = "GetScadaWindow", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetScadaWindow();

        [DllImport("qtdialog.dll", EntryPoint = "ShowBasWindow", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ShowBasWindow(IntPtr hwnd);
    }
}
