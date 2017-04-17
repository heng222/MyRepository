namespace ProWrite.UI.Controls
{
    partial class SaveItem
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.ckbYes = new System.Windows.Forms.CheckBox();
            this.txtNewName = new System.Windows.Forms.RichTextBox();
            this.lblType = new System.Windows.Forms.Label();
            this.sbtnCheck = new DevExpress.XtraEditors.SimpleButton();
            this.SuspendLayout();
            // 
            // ckbYes
            // 
            this.ckbYes.AutoSize = true;
            this.ckbYes.Location = new System.Drawing.Point(402, 5);
            this.ckbYes.Name = "ckbYes";
            this.ckbYes.Size = new System.Drawing.Size(50, 17);
            this.ckbYes.TabIndex = 16;
            this.ckbYes.Text = "Save";
            this.ckbYes.UseVisualStyleBackColor = true;
            this.ckbYes.Click += new System.EventHandler(this.ckbYes_Click);
            // 
            // txtNewName
            // 
            this.txtNewName.AllowDrop = true;
            this.txtNewName.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtNewName.Location = new System.Drawing.Point(111, 3);
            this.txtNewName.Margin = new System.Windows.Forms.Padding(0);
            this.txtNewName.MaxLength = 30;
            this.txtNewName.Name = "txtNewName";
            this.txtNewName.Size = new System.Drawing.Size(192, 27);
            this.txtNewName.TabIndex = 13;
            this.txtNewName.Text = "";
            this.txtNewName.TextChanged += new System.EventHandler(this.txtNewName_TextChanged);
            // 
            // lblType
            // 
            this.lblType.AutoSize = true;
            this.lblType.Location = new System.Drawing.Point(19, 10);
            this.lblType.Name = "lblType";
            this.lblType.Size = new System.Drawing.Size(0, 13);
            this.lblType.TabIndex = 17;
            // 
            // sbtnCheck
            // 
            this.sbtnCheck.Location = new System.Drawing.Point(316, 3);
            this.sbtnCheck.Name = "sbtnCheck";
            this.sbtnCheck.Size = new System.Drawing.Size(75, 23);
            this.sbtnCheck.TabIndex = 18;
            this.sbtnCheck.Text = "Check";
            this.sbtnCheck.Click += new System.EventHandler(this.sbtnCheck_Click);
            // 
            // SaveItem
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.sbtnCheck);
            this.Controls.Add(this.lblType);
            this.Controls.Add(this.ckbYes);
            this.Controls.Add(this.txtNewName);
            this.Name = "SaveItem";
            this.Size = new System.Drawing.Size(455, 33);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RichTextBox txtNewName;
        private System.Windows.Forms.CheckBox ckbYes;
        private System.Windows.Forms.Label lblType;
        private DevExpress.XtraEditors.SimpleButton sbtnCheck;

    }
}
