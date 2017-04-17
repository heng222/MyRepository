using System.Windows.Forms;
using ProWrite.UI.Controls;

namespace ProWrite.UI.Clients.Test
{
	partial class MyControlsTestForm
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
			this.simpleButton1 = new System.Windows.Forms.Button();
			this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
			this.SuspendLayout();
			// 
			// simpleButton1
			// 
			this.simpleButton1.Location = new System.Drawing.Point(54, 113);
			this.simpleButton1.Name = "simpleButton1";
			this.simpleButton1.Size = new System.Drawing.Size(75, 23);
			this.simpleButton1.TabIndex = 0;
			this.simpleButton1.Text = "simpleButton1";
			this.simpleButton1.Click += new System.EventHandler(this.simpleButton1_Click);
			// 
			// labelControl1
			// 
			this.labelControl1.Location = new System.Drawing.Point(44, 54);
			this.labelControl1.Name = "labelControl1";
			this.labelControl1.Size = new System.Drawing.Size(63, 13);
			this.labelControl1.TabIndex = 1;
			this.labelControl1.Text = "labelControl1";
			// 
			// MyControlsTestForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(292, 266);
			this.Controls.Add(this.labelControl1);
			this.Controls.Add(this.simpleButton1);
			this.Name = "MyControlsTestForm";
			this.Text = "MyControlsTestForm";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private Button simpleButton1;
		private DevExpress.XtraEditors.LabelControl labelControl1;
	}
}