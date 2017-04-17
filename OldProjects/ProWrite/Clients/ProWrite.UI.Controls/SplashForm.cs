using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using Microsoft.Win32;
using DevExpress.XtraBars.Ribbon;
using System.Resources;
using System.Reflection;
using DevExpress.XtraLayout.Utils;
using System.Text.RegularExpressions;
using System.Threading;
using ProWrite.Resources;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;
using System.Diagnostics;
using System.Threading.Tasks;

namespace ProWrite.UI.Controls
{
    public partial class SplashForm : XtraForm
    {
        System.Windows.Forms.Timer time = new System.Windows.Forms.Timer();
        int timeCount = 0;
        public SplashForm(string machineCode, string registerCode, string salesNumber, bool isAbout)
        {
            //System.Console.WriteLine("SplashFormStart :" + System.DateTime.Now.ToString());

            InitializeComponent();
            layoutControlItem1.Visibility = LayoutVisibility.Never;
            
            if (!isAbout)
                layoutControlItem6.Visibility = LayoutVisibility.Never;
            else
                layoutControlItem6.Visibility = LayoutVisibility.Always;
            //layoutControlItem7.Visibility = LayoutVisibility.Never;
            simpleLabelItem1.Text = " ";
            layoutControlItem9.Visibility = LayoutVisibility.Never;
            txtRegOne.ReadOnly = true;
            txtRegTwo.ReadOnly = true;
            txtRegThree.ReadOnly = true;
            txtRegFour.ReadOnly = true;
            InitStrings();
            InitImages();
            lblRegNumber.Text = machineCode.Substring(0, 6) + " - "
                                + machineCode.Substring(6, 6) + " - "
                                + machineCode.Substring(12, 6) + " - "
                                + machineCode.Substring(18, 6) + " - "
                                + machineCode.Substring(24, 6) + " - "
                                + machineCode.Substring(30, 6) + " - "
                                + machineCode.Substring(36, 6) + " - "
                                + machineCode.Substring(42, 6);
            //lblRegNumber.Text = machineCode.Substring(0, 4) + " - "
            //                    + machineCode.Substring(4, 4) + " - "
            //                    + machineCode.Substring(8, 4) + " - "
            //                    + machineCode.Substring(12, 4);
            if (!string.IsNullOrEmpty(salesNumber))
            {
                txtSalesNumber.Text = salesNumber;
                //txtSalesNumber.Enabled = false;
                //btnReSet.Enabled = false;
            }
            txtRegOne.Text = registerCode.Substring(0, 4);
            txtRegTwo.Text = registerCode.Substring(4, 4);
            txtRegThree.Text = registerCode.Substring(8, 4);
            txtRegFour.Text = registerCode.Substring(12, 4);
            btnClose.Focus();
            if (!isAbout)
            {
                time.Interval = 1000;
                time.Tick += new EventHandler(time_Tick);
                time.Start();
            }

            TopMost = true;
            //System.Console.WriteLine("SplashFormInitEnd :" + System.DateTime.Now.ToString());

        }

        void time_Tick(object sender, EventArgs e)
        {
            timeCount++;
            if (timeCount == 3)
            {
                time.Stop();
                time.Dispose();
                Close();
            }

        }

        private void InitStrings()
        {
            lblProWrite.Text = Resource.GetString(Resource.Strings.LoginForm_ProWrite);
            lblVersion.Text = ProductInfo.Version;
            lblHelpDesk.Text = Resource.GetString(Resource.Strings.LoginForm_HelpDesk);
            lblHttp.Text = Resource.GetString(Resource.Strings.LoginForm_http);
            //lblErrorMSG.Text = Resource.GetString(Resource.Strings.LoginForm_HaveNoRegisted);
        }

        /// <summary>
        ///  Initialize images used in login form from resource file
        /// </summary>
        private void InitImages()
        {
            layoutControlGroup1.BackgroundImage = Resource.GetImage(Resource.Images.Welcome);
            //this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.pictureEdit1.EditValue = Resource.GetImage(Resource.Images.TransLuxLog);
            //this.layoutControlGroup1.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("layoutControlGroup1.BackgroundImage")));
        }

        private void layoutControl1_ShowContextMenu(object sender, DevExpress.XtraLayout.LayoutMenuEventArgs e)
        {
            e.Menu.Items.Clear();
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            Close();
        }

    }
}