namespace ProWrite.UI.Controls.Live.Sessions
{
    partial class SmallButtonControl
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
            this.lblName = new DevExpress.XtraEditors.LabelControl();
            this.lblKeyShortcuts = new DevExpress.XtraEditors.LabelControl();
            this.SuspendLayout();
            // 
            // lblName
            // 
            this.lblName.Appearance.Options.UseTextOptions = true;
            this.lblName.Appearance.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.lblName.Appearance.TextOptions.VAlignment = DevExpress.Utils.VertAlignment.Bottom;
            this.lblName.AutoSizeMode = DevExpress.XtraEditors.LabelAutoSizeMode.None;
            this.lblName.Dock = System.Windows.Forms.DockStyle.Top;
            this.lblName.Location = new System.Drawing.Point(0, 0);
            this.lblName.Name = "lblName";
            this.lblName.Size = new System.Drawing.Size(100, 18);
            this.lblName.TabIndex = 1;
            this.lblName.MouseDown += new System.Windows.Forms.MouseEventHandler(this.lblName_MouseDown);
            // 
            // lblKeyShortcuts
            // 
            this.lblKeyShortcuts.Appearance.Options.UseTextOptions = true;
            this.lblKeyShortcuts.Appearance.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.lblKeyShortcuts.Appearance.TextOptions.VAlignment = DevExpress.Utils.VertAlignment.Top;
            this.lblKeyShortcuts.AutoSizeMode = DevExpress.XtraEditors.LabelAutoSizeMode.None;
            this.lblKeyShortcuts.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.lblKeyShortcuts.LineLocation = DevExpress.XtraEditors.LineLocation.Center;
            this.lblKeyShortcuts.Location = new System.Drawing.Point(0, 22);
            this.lblKeyShortcuts.Name = "lblKeyShortcuts";
            this.lblKeyShortcuts.Size = new System.Drawing.Size(100, 18);
            this.lblKeyShortcuts.TabIndex = 2;
            this.lblKeyShortcuts.MouseDown += new System.Windows.Forms.MouseEventHandler(this.lblKeyShortcuts_MouseDown);
            // 
            // SmallButtonControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Controls.Add(this.lblKeyShortcuts);
            this.Controls.Add(this.lblName);
            this.Name = "SmallButtonControl";
            this.Size = new System.Drawing.Size(100, 40);
            this.ResumeLayout(false);

        }

        #endregion

        private DevExpress.XtraEditors.LabelControl lblName;
        private DevExpress.XtraEditors.LabelControl lblKeyShortcuts;
    }
}
