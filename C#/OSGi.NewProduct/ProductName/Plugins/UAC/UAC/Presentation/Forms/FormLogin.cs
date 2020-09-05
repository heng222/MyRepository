using System;
using System.Windows.Forms;

using Products.Infrastructure;
using Products.Resource;
using Products.UAC.Domain;
using Products.UAC.Utilities;

namespace Products.UAC.Presentation.Forms
{
    partial class FormLogin : Form, IUserLogOn
    {
        #region "Field"
        /// <summary>
        /// 已经尝试的次数。
        /// </summary>
        private int _retryTimes = 0;
        #endregion

        #region "Properties"
        public ILoginVerification Verification { get; private set; }
        #endregion

        /// <summary>
        /// 构造函数
        /// </summary>
        public FormLogin(ILoginVerification verify)
        {
            if (verify == null) throw new ArgumentException("登录验证接口不能为空引用。");

            this.Verification = verify;

            InitializeComponent();

            this.Initialize();
        }

        private void Initialize()
        {
            this.txtUserName.Focus();
            this.Icon = ProductResources.ApplicationIcon;
            this.picLogo.Image = ProductResources.CompanyLogoImage;
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            try
            {
                var actualPwd = HelperTool.BuildMd5(txtPassword.Text);
                this.Verification.LogOn(txtUserName.Text, actualPwd);

                this.Close();

                _retryTimes = 0;

                this.DialogResult = DialogResult.OK;
            }
            catch (Exception ex)
            {
                if (++_retryTimes > 2)
                {
                    this.DialogResult = DialogResult.No;
                }
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        #region IUserLogOn 成员

        public UserLogOnResult ShowLogOnDialog()
        {
            var rc = this.ShowDialog();

            if (rc == DialogResult.OK)
            {
                return UserLogOnResult.Successful;
            }
            else if (rc == DialogResult.Cancel)
            {
                return UserLogOnResult.Canceled;
            }
            else
            {
                return UserLogOnResult.Failure;
            }
        }

        #endregion
    }
}
