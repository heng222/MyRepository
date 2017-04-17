namespace ProWrite.UI.Controls.Dashboard
{
	partial class SignStatus
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SignStatus));
			this.lblMaintenceRequired = new DevExpress.XtraEditors.LabelControl();
			this.pictureEdit3 = new DevExpress.XtraEditors.PictureEdit();
			this.memoEdit1 = new DevExpress.XtraEditors.MemoEdit();
			((System.ComponentModel.ISupportInitialize)(this.pictureEdit3.Properties)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.memoEdit1.Properties)).BeginInit();
			this.SuspendLayout();
			// 
			// lblMaintenceRequired
			// 
			this.lblMaintenceRequired.Appearance.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Bold);
			this.lblMaintenceRequired.Appearance.Options.UseFont = true;
			this.lblMaintenceRequired.Location = new System.Drawing.Point(39, 10);
			this.lblMaintenceRequired.Name = "lblMaintenceRequired";
			this.lblMaintenceRequired.Size = new System.Drawing.Size(137, 14);
			this.lblMaintenceRequired.TabIndex = 4;
			this.lblMaintenceRequired.Text = "Maintenance Required";
			// 
			// pictureEdit3
			// 
			this.pictureEdit3.EditValue = ((object)(resources.GetObject("pictureEdit3.EditValue")));
			this.pictureEdit3.Location = new System.Drawing.Point(3, 3);
			this.pictureEdit3.Name = "pictureEdit3";
			this.pictureEdit3.Properties.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
			this.pictureEdit3.Properties.PictureStoreMode = DevExpress.XtraEditors.Controls.PictureStoreMode.Image;
			this.pictureEdit3.Properties.ReadOnly = true;
			this.pictureEdit3.Properties.ShowMenu = false;
			this.pictureEdit3.Size = new System.Drawing.Size(29, 30);
			this.pictureEdit3.TabIndex = 3;
			// 
			// memoEdit1
			// 
			this.memoEdit1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
						| System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.memoEdit1.EditValue = "- Electrical Mis-configuration\r\n- Web cam Faulty\r\n- Housing Market Down\r\n- etc .." +
				".";
			this.memoEdit1.Location = new System.Drawing.Point(1, 38);
			this.memoEdit1.Name = "memoEdit1";
			this.memoEdit1.Size = new System.Drawing.Size(245, 267);
			this.memoEdit1.TabIndex = 5;
			// 
			// SignStatus
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.memoEdit1);
			this.Controls.Add(this.lblMaintenceRequired);
			this.Controls.Add(this.pictureEdit3);
			this.Name = "SignStatus";
			this.Size = new System.Drawing.Size(246, 306);
			((System.ComponentModel.ISupportInitialize)(this.pictureEdit3.Properties)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.memoEdit1.Properties)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private DevExpress.XtraEditors.LabelControl lblMaintenceRequired;
		private DevExpress.XtraEditors.PictureEdit pictureEdit3;
		private DevExpress.XtraEditors.MemoEdit memoEdit1;
	}
}
