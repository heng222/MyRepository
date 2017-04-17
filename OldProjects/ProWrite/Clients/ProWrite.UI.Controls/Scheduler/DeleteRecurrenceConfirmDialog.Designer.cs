namespace ProWrite.UI.Controls.Scheduler
{
    partial class DeleteRecurrenceConfirmDialog
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
            this.rbtnDelete = new System.Windows.Forms.RadioButton();
            this.rbtnUpdate = new System.Windows.Forms.RadioButton();
            this.btnOk = new DevExpress.XtraEditors.SimpleButton();
            this.btnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.SuspendLayout();
            // 
            // rbtnDelete
            // 
            this.rbtnDelete.AutoSize = true;
            this.rbtnDelete.Location = new System.Drawing.Point(12, 47);
            this.rbtnDelete.Name = "rbtnDelete";
            this.rbtnDelete.Size = new System.Drawing.Size(326, 17);
            this.rbtnDelete.TabIndex = 0;
            this.rbtnDelete.Text = "Delete all recurrences and only update this occurrence of item.";
            this.rbtnDelete.UseVisualStyleBackColor = true;
            this.rbtnDelete.CheckedChanged += new System.EventHandler(this.rbtnDelete_CheckedChanged);
            // 
            // rbtnUpdate
            // 
            this.rbtnUpdate.AutoSize = true;
            this.rbtnUpdate.Checked = true;
            this.rbtnUpdate.Location = new System.Drawing.Point(12, 12);
            this.rbtnUpdate.Name = "rbtnUpdate";
            this.rbtnUpdate.Size = new System.Drawing.Size(193, 17);
            this.rbtnUpdate.TabIndex = 1;
            this.rbtnUpdate.TabStop = true;
            this.rbtnUpdate.Text = "Update all recurrences of this item.";
            this.rbtnUpdate.UseVisualStyleBackColor = true;
            this.rbtnUpdate.CheckedChanged += new System.EventHandler(this.rbtnUpdate_CheckedChanged);
            // 
            // btnOk
            // 
            this.btnOk.Location = new System.Drawing.Point(232, 80);
            this.btnOk.Name = "btnOk";
            this.btnOk.Size = new System.Drawing.Size(50, 23);
            this.btnOk.TabIndex = 2;
            this.btnOk.Text = "OK";
            this.btnOk.Click += new System.EventHandler(this.btnOk_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.Location = new System.Drawing.Point(302, 80);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(62, 23);
            this.btnCancel.TabIndex = 3;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // DeleteRecurrenceConfirmDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(378, 115);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnOk);
            this.Controls.Add(this.rbtnUpdate);
            this.Controls.Add(this.rbtnDelete);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "DeleteRecurrenceConfirmDialog";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton rbtnDelete;
        private System.Windows.Forms.RadioButton rbtnUpdate;
        private DevExpress.XtraEditors.SimpleButton btnOk;
        private DevExpress.XtraEditors.SimpleButton btnCancel;
    }
}