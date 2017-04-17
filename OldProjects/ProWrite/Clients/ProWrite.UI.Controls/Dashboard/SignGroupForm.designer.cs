using SignGroupInfo=ProWrite.Entity.Dashboard.SignGroupInfo;

namespace ProWrite.UI.Controls.Dashboard
{
    partial class SignGroupForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.grpPanel = new DevExpress.XtraEditors.PanelControl();
            this.txtGroupName = new DevExpress.XtraEditors.TextEdit();
            this.bindingSource1 = new System.Windows.Forms.BindingSource(this.components);
            this.lblParent = new System.Windows.Forms.Label();
            this.lblGroupName = new System.Windows.Forms.Label();
            this.ddlParent = new DevExpress.XtraEditors.ComboBoxEdit();
            //this.btnCancel = new DevExpress.XtraEditors.SimpleButton();
            //this.btnSave = new DevExpress.XtraEditors.SimpleButton();
            ((System.ComponentModel.ISupportInitialize)(this.grpPanel)).BeginInit();
            this.grpPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.txtGroupName.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bindingSource1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlParent.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // grpPanel
            // 
            this.grpPanel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowOnly;
            this.grpPanel.Controls.Add(this.txtGroupName);
            this.grpPanel.Controls.Add(this.lblParent);
            this.grpPanel.Controls.Add(this.lblGroupName);
            this.grpPanel.Controls.Add(this.ddlParent);
            this.grpPanel.Location = new System.Drawing.Point(6, 5);
            this.grpPanel.Name = "grpPanel";
            this.grpPanel.Size = new System.Drawing.Size(241, 71);
            this.grpPanel.TabIndex = 9;
            // 
            // txtGroupName
            // 
            //this.txtGroupName.DataBindings.Add(new System.Windows.Forms.Binding("Text", this.bindingSource1, "Name", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
            this.txtGroupName.Location = new System.Drawing.Point(90, 10);
            this.txtGroupName.Name = "txtGroupName";
            this.txtGroupName.Properties.MaxLength = 60;
            this.txtGroupName.Size = new System.Drawing.Size(140, 21);
            this.txtGroupName.TabIndex = 2;
            // 
            // bindingSource1
            // 
            this.bindingSource1.DataSource = typeof(SignGroupInfo);
            // 
            // lblParent
            // 
            this.lblParent.AutoSize = true;
            this.lblParent.Location = new System.Drawing.Point(9, 45);
            this.lblParent.Name = "lblParent";
            this.lblParent.Size = new System.Drawing.Size(84, 14);
            this.lblParent.TabIndex = 0;

            // 
            // lblGroupName
            // 
            this.lblGroupName.AutoSize = true;
            this.lblGroupName.Location = new System.Drawing.Point(14, 13);
            this.lblGroupName.Name = "lblGroupName";
            this.lblGroupName.Size = new System.Drawing.Size(79, 14);
            this.lblGroupName.TabIndex = 0;

            // 
            // ddlParent
            // 
            this.ddlParent.Location = new System.Drawing.Point(90, 40);
            this.ddlParent.Name = "ddlParent";
            this.ddlParent.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.ddlParent.Properties.TextEditStyle = DevExpress.XtraEditors.Controls.TextEditStyles.DisableTextEditor;
            this.ddlParent.Size = new System.Drawing.Size(140, 21);
            this.ddlParent.TabIndex = 3;
            ddlParent.CausesValidation = false;
            // 
            // btnCancel
            // 
            this.btnCancel.CausesValidation = false;
            this.btnCancel.ImageLocation = DevExpress.XtraEditors.ImageLocation.MiddleLeft;
            this.btnCancel.Location = new System.Drawing.Point(174, 91);
            //this.btnCancel.Name = "btnCancel";
            //this.btnCancel.Size = new System.Drawing.Size(72, 22);
            //this.btnCancel.TabIndex = 11;
            //this.btnCancel.Text = "Cancel";
            //this.btnCancel.ToolTip = "Save";
            //this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnSave
            // 
            this.btnSave.ImageLocation = DevExpress.XtraEditors.ImageLocation.MiddleLeft;
            this.btnSave.Location = new System.Drawing.Point(101, 91);
            //this.btnSave.Name = "btnSave";
            //this.btnSave.Size = new System.Drawing.Size(67, 22);
            //this.btnSave.TabIndex = 10;
            //this.btnSave.Text = "Save";
            //this.btnSave.ToolTip = "Save";
            //this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // SignGroupForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(252, 120);
            //this.Controls.Add(this.btnCancel);
            //this.Controls.Add(this.btnSave);
            this.Controls.Add(this.grpPanel);
            this.Name = "SignGroupForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "SignGroupForm";
            ((System.ComponentModel.ISupportInitialize)(this.grpPanel)).EndInit();
            this.grpPanel.ResumeLayout(false);
            this.grpPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.txtGroupName.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bindingSource1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ddlParent.Properties)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private DevExpress.XtraEditors.PanelControl grpPanel;
        private DevExpress.XtraEditors.TextEdit txtGroupName;
        private System.Windows.Forms.Label lblParent;
        private System.Windows.Forms.Label lblGroupName;
        private DevExpress.XtraEditors.ComboBoxEdit ddlParent;
        //private DevExpress.XtraEditors.SimpleButton btnCancel;
        //private DevExpress.XtraEditors.SimpleButton btnSave;
        private System.Windows.Forms.BindingSource bindingSource1;

    }
}