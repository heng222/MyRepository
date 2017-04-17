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
using ProWrite.Core;
using DevExpress.Skins;
using DevExpress.LookAndFeel;
using ProWrite.UI.Controls.Common;
using DevExpress.XtraLayout.Utils;
using Microsoft.Win32;
using System.Text.RegularExpressions;
using DevExpress.UserSkins;

namespace ProWrite.UI.Controls
{
    [LoginForm]
    public partial class LoginForm : XtraForm,ILoginForm
    {
        private AuthenticateService _service;
        public AuthenticateService AuthenticateService
        {
            get { return _service; }
            set
            {
                _service = value;
                SetControlState(true);
            }
        }

        public LoginForm()
        {
            if (!DesignMode)
            {
                InitializeComponent();
                Initialize();
                TopMost = true;
            }
        }

        protected override void OnShown(EventArgs e)
        {
            base.OnShown(e);

            TopMost = false;
            if (Owner != null)
                Owner.Hide();
        }

     
        #region event

        /// <summary>
        ///  Initialize login form
        /// </summary>
        private void Initialize()
        {
            InitStrings();
            InitImages();

        }

        private void SetControlState(bool b)
        {
            if (!string.IsNullOrEmpty(_service.RegisterCode)
                && !string.IsNullOrEmpty(_service.LastedDate))
            {
                if (_service.FailedType == ErrorType.Overdue)
                {
                    MsgBox.Warning(Resource.GetString(Resource.Strings.LoginForm_OverDue));
                }
                else
                {
                    MsgBox.Warning("The Serial Number that you entered is invalid. Please try again");
                }
            }
            SetCtrlState();



            if (!String.IsNullOrEmpty(_service.MachineCode))
            {
                lblRegNumber.Text = _service.MachineCode.Substring(0, 6) + " - "
                                + _service.MachineCode.Substring(6, 6) + " - "
                                + _service.MachineCode.Substring(12, 6) + " - "
                                + _service.MachineCode.Substring(18, 6) + " - "
                                + _service.MachineCode.Substring(24, 6) + " - "
                                + _service.MachineCode.Substring(30, 6) + " - "
                                + _service.MachineCode.Substring(36, 6) + " - "
                                + _service.MachineCode.Substring(42, 6);
            }
            else
                lblRegNumber.Text = "0000";
            if (b)
            {
                if (!string.IsNullOrEmpty(_service.SalesNumber))
                {
                    txtSalesNumber.Text = _service.SalesNumber;
                }
                else
                {
                    txtSalesNumber.Text = "";
                    txtSalesNumber.Enabled = true;
                    btnReSet.Enabled = true;
                    lblRegNumber.Text = "0000";
                }
            }
            if (!String.IsNullOrEmpty(_service.RegisterCode) && _service.RegisterCode.Trim().Length == 16)
            {
            }
            else
            {
                lblErrorMSG.Visibility = LayoutVisibility.Always;
            }
        }

        private void SetCtrlState()
        {
            btnLogin.Visible = true;
            this.layoutControlItem6.Visibility = LayoutVisibility.Always;// "Always";
            this.layoutControlItem7.Visibility = LayoutVisibility.Always;
            btnClose.Visible = true;
            txtRegOne.ReadOnly = false;
            txtRegTwo.ReadOnly = false;
            txtRegThree.ReadOnly = false;
            txtRegFour.ReadOnly = false;
            txtRegOne.Text = "";
            txtRegTwo.Text = "";
            txtRegThree.Text = "";
            txtRegFour.Text = "";
            btnClose.Enabled = true;
            btnLogin.Enabled = true;
            btnReSet.Visible = true;
            lblErrorMSG.Visibility = LayoutVisibility.Always;

        }
        /// <summary>
        ///  Initialize string used in login form from resource file
        /// </summary>
        private void InitStrings()
        {
            lblProWrite.Text = Resource.GetString(Resource.Strings.LoginForm_ProWrite);
            lblVersion.Text = ProductInfo.Version;
            lblHelpDesk.Text = Resource.GetString(Resource.Strings.LoginForm_HelpDesk);
            lblHttp.Text = Resource.GetString(Resource.Strings.LoginForm_http);
            lblErrorMSG.Text = Resource.GetString(Resource.Strings.LoginForm_HaveNoRegisted);
        }

        /// <summary>
        ///  Initialize images used in login form from resource file
        /// </summary>
        private void InitImages()
        {
            layoutControlGroup1.BackgroundImage = Resource.GetImage(Resource.Images.Welcome);
            this.pictureEdit1.EditValue = Resource.GetImage(Resource.Images.TransLuxLog);
        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            string registerCode = txtRegOne.Text.ToUpper()
                + txtRegTwo.Text.ToUpper()
                + txtRegThree.Text.ToUpper()
                + txtRegFour.Text.ToUpper();
            if (_service.Authenticate(registerCode))
            {

                RegistryKey registryKey;
                registryKey = Registry.CurrentUser.OpenSubKey("SOFTWARE\\ProWrite" /*+ ProductInfo.VersionCode.Replace(".","_")*/, true);

                if (chkLaunch.Checked)
                    registryKey.SetValue("StartTutorial", "1");
                else
                    registryKey.SetValue("StartTutorial", "0");

                Close();
            }
            else
            {
                MsgBox.Error("The Serial Number that you entered is invalid. Please generate a new seed key,register again.");
            }
        }


        private void txtRegOne_TextChanged(object sender, EventArgs e)
        {
            if (txtRegOne.Text.Length >= 4)
            {
                this.txtRegTwo.Focus();
            }
        }

        private void txtRegTwo_TextChanged(object sender, EventArgs e)
        {
            if (txtRegTwo.Text.Length >= 4)
            {
                this.txtRegThree.Focus();
            }
        }

        private void txtRegThree_TextChanged(object sender, EventArgs e)
        {
            if (txtRegThree.Text.Length >= 4)
            {
                this.txtRegFour.Focus();
            }
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void txtRegOne_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (Convert.ToInt32(e.KeyChar) == 22)
            {
                e.Handled = false;
                var str = Clipboard.GetText();
                if (str.Length == 16)
                {
                    this.txtRegOne.Text = str.Substring(0, 4);
                    txtRegTwo.Text = str.Substring(4, 4);
                    txtRegThree.Text = str.Substring(8, 4);
                    txtRegFour.Text = str.Substring(12, 4);
                    btnLogin.Focus();
                    return;
                }
                else
                {
                    e.Handled = false;
                    return;
                }
            }
            if ((Convert.ToInt32(e.KeyChar) == 8))
            {
                e.Handled = false;
            }
            else
            {
                //Regex numRegex = new Regex(@"^(-?[0-9]*[.]*[0-9]*)$");
                Regex numRegex = new Regex(@"^([0-9]*)$");
                Match Result = numRegex.Match(Convert.ToString(e.KeyChar));
                if (Result.Success)
                {
                    e.Handled = false;
                    return;
                }
                else
                {
                    bool b = true;
                    int[] s = { 3, 22, 26, 65, 66, 67, 68, 69, 70, 97, 98, 99, 100, 101, 102 };
                    for (int i = 0; i < s.Length; i++)
                    {
                        if (Convert.ToInt32(e.KeyChar) == s[i])
                        {
                            e.Handled = false;
                            return;
                        }
                    }
                    if (b)
                    {
                        e.Handled = true;
                        return;
                    }
                }
            }
        }
        #endregion


        private void layoutControl1_ShowContextMenu(object sender, DevExpress.XtraLayout.LayoutMenuEventArgs e)
        {
            e.Menu.Items.Clear();
        }

        private void btnReSet_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(txtSalesNumber.Text.Trim()))
                return;
            string salesNumber = txtSalesNumber.Text.Trim();
            if (txtSalesNumber.Text.Length < 6)
            {
                salesNumber = convertSalesNoString(txtSalesNumber.Text);
            }
            _service.CreateSubKey(salesNumber);
            SetControlState(false);
            txtRegOne.Text = "";
            txtRegTwo.Text = "";
            txtRegThree.Text = "";
            txtRegFour.Text = "";
        }
        private string convertSalesNoString(string salesNo)
        {
            while (salesNo.Length < 6)
            {
                salesNo = "0" + salesNo;
            }
            return salesNo;
        }

        private void txtSalesNumber_TextChanged(object sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(txtSalesNumber.Text))
            {
                btnReSet.Enabled = true;
            }
            else
                btnReSet.Enabled = false;
        }

        private void txtSalesNumber_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((Convert.ToInt32(e.KeyChar)) == 45)
            {
                e.Handled = true;
                return;
            }
            int v = e.KeyChar;
            TextEdit tb = (TextEdit)sender;
            if ((v >= 48 && v < 58) || v == 8)
            {
                e.Handled = false;
            }
            else
            {
                e.Handled = true;
            }
        }

        private void btnCopy_Click(object sender, EventArgs e)
        {
            Clipboard.SetText(lblRegNumber.Text.Replace(" - ", "").Trim());
        }

        private void btnEmail_Click(object sender, EventArgs e)
        {
            HelpManager.SendEmail(Resources.Resource.GetString(Resources.Resource.Strings.EmailAddress),
                Resources.Resource.GetString(Resources.Resource.Strings.EmailSubject),
                lblRegNumber.Text.Replace(" - ", "").Trim());
        }

        private void chkLaunch_CheckedChanged(object sender, EventArgs e)
        {

        }
    }
}

