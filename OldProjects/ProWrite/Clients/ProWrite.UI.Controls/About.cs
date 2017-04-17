using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.Resources;
using DevExpress.XtraLayout.Utils;
using Microsoft.Win32;
using ProWrite.Core;

namespace ProWrite.UI.Controls
{
    public partial class About : XtraForm
    {
        private Cryptographer encry = new Cryptographer();
        public About()
        {

            InitializeComponent();

            RegistryKey registryKey;
            registryKey = Registry.CurrentUser.OpenSubKey("SOFTWARE\\ProWrite" /*+ ProductInfo.VersionCode.Replace(".","_")*/, true);
            var registerCode = registryKey.GetValue("RegisterCode", "").ToString().Trim();
            string salesNumber = registryKey.GetValue("SalesNumber", "").ToString().Trim();
            //if (string.IsNullOrEmpty(salesNumber))
            //    return false;


            var SalesNumber = Decrpyt(salesNumber);
            var machineCode = registryKey.GetValue("MachineCode", "").ToString().Trim();

            string dateLasted = registryKey.GetValue("EndDate", "").ToString().Trim();

            DateTime dtLasted;

            if (!string.IsNullOrEmpty(dateLasted)&&DateTime.TryParse(this.Decrpyt(dateLasted), out dtLasted))
            {
                DateTime dtNow = DateTime.Now;
                //DateTime dtLasted = DateTime.Parse(dateLasted);
                TimeSpan tUsedCount = dtLasted - dtNow;

                this.txtTimeLeft.Text = Convert.ToInt32(tUsedCount.TotalDays).ToString();
            }
            else
                this.txtTimeLeft.Text = "Unlimited";

            //layoutControlItem1.Visibility = LayoutVisibility.Never;

            layoutControlItem6.Visibility = LayoutVisibility.Always;
            //layoutControlItem7.Visibility = LayoutVisibility.Never;
            //simpleLabelItem1.Text = " ";
            //layoutControlItem9.Visibility = LayoutVisibility.Never;
            txtRegOne.ReadOnly = true;
            txtRegTwo.ReadOnly = true;
            txtRegThree.ReadOnly = true;
            txtRegFour.ReadOnly = true;
            InitStrings();
            InitImages();
            //lblRegNumber.Text = machineCode.Substring(0, 6) + " - "
            //                    + machineCode.Substring(6, 6) + " - "
            //                    + machineCode.Substring(12, 6) + " - "
            //                    + machineCode.Substring(18, 6) + " - "
            //                    + machineCode.Substring(24, 6) + " - "
            //                    + machineCode.Substring(30, 6) + " - "
            //                    + machineCode.Substring(36, 6) + " - "
            //                    + machineCode.Substring(42, 6);
            //lblRegNumber.Text = machineCode.Substring(0, 4) + " - "
            //                    + machineCode.Substring(4, 4) + " - "
            //                    + machineCode.Substring(8, 4) + " - "
            //                    + machineCode.Substring(12, 4);
            if (!string.IsNullOrEmpty(SalesNumber))
            {
                txtSalesNumber.Text = SalesNumber;
                //txtSalesNumber.Enabled = false;
                //btnReSet.Enabled = false;
            }
            txtRegOne.Text = registerCode.Substring(0, 4);
            txtRegTwo.Text = registerCode.Substring(4, 4);
            txtRegThree.Text = registerCode.Substring(8, 4);
            txtRegFour.Text = registerCode.Substring(12, 4);
            btnClose.Focus();

            TopMost = true;
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

        private void btnClose_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void layoutControl1_ShowContextMenu(object sender, DevExpress.XtraLayout.LayoutMenuEventArgs e)
        {
            e.Menu.Items.Clear();
        }

        void simpleButton1_Click(object sender, System.EventArgs e)
        {
            ShowAgreement show = new ShowAgreement();
            show.ShowModalDialog();
        }

        private string Decrpyt(string source)
        {
            try
            {
                return encry.SymmetricDecrpyt(source);
            }
            catch
            {
                //log.Error(e.Message, e);
                return source;
            }
        }
    }
}
