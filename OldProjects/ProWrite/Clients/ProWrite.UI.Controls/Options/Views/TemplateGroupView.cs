using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Entity.Settings;
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls.Options.Views
{
    public class TemplateGroupView:ViewBase<TemplateGroup>
    {
        private System.Windows.Forms.Label lblName;
        private DevExpress.XtraEditors.TextEdit txtName;

        public TemplateGroupView()
        {
            InitializeComponent();
        }

        protected override void DoBind()
        {
            txtName.Text = _data.Name;
        }

        protected override void DoUpdateData()
        {
            _data.Name = txtName.Text;
        }

        protected override bool ValidateData()
        {
            if (string.IsNullOrEmpty(txtName.Text))
            {
                MsgBox.Warning("Name does not null.");
                return false;
            }

            return true;
        }

        private void InitializeComponent()
        {
            this.lblName = new System.Windows.Forms.Label();
            this.txtName = new DevExpress.XtraEditors.TextEdit();
            this.SuspendLayout();
            // 
            // lblName
            // 
            this.lblName.AutoSize = true;
            this.lblName.Location = new System.Drawing.Point(37, 47);
            this.lblName.Name = "lblName";
            this.lblName.Size = new System.Drawing.Size(38, 13);
            this.lblName.TabIndex = 0;
            this.lblName.Text = "Name:";
            // 
            // txtName
            // 
            this.txtName.Location = new System.Drawing.Point(82, 47);
            this.txtName.Name = "txtName";
            this.txtName.Size = new System.Drawing.Size(159, 20);
            this.txtName.TabIndex = 1;
            // 
            // TemplateGroupView
            // 
            this.Controls.Add(this.txtName);
            this.Controls.Add(this.lblName);
            this.Name = "TemplateGroupView";
            this.Size = new System.Drawing.Size(284, 193);
            this.ResumeLayout(false);
            this.PerformLayout();

        }
    }
}
