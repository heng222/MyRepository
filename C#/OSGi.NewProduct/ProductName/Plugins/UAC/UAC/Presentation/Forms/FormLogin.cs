using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Products.Resource;
using Products.UAC.Domain;

namespace Products.UAC.Presentation.Forms
{
    partial class FormLogin : Form
    {
        #region "Filed"
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
            this.Icon = ProductResources.ApplicationIcon;
            this.picLogo.Image = ProductResources.CompanyLogoImage;
        }
    }
}
