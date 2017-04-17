namespace ProWrite.UI.Controls.Editor
{
    partial class ToolBoxControl
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
            this.nbcToolBox = new DevExpress.XtraNavBar.NavBarControl();
            this.grpToolBox = new DevExpress.XtraNavBar.NavBarGroup();
            ((System.ComponentModel.ISupportInitialize)(this.nbcToolBox)).BeginInit();
            this.nbcToolBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // nbcToolBox
            // 
            this.nbcToolBox.AllowDrop = false;
            this.nbcToolBox.Appearance.ButtonHotTracked.Options.UseTextOptions = true;
            this.nbcToolBox.Appearance.ButtonHotTracked.TextOptions.HotkeyPrefix = DevExpress.Utils.HKeyPrefix.None;
            this.nbcToolBox.ContentButtonHint = null;
            this.nbcToolBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.nbcToolBox.Groups.AddRange(new DevExpress.XtraNavBar.NavBarGroup[] {
            this.grpToolBox});
            this.nbcToolBox.HotTrackedItemCursor = System.Windows.Forms.Cursors.Arrow;
            this.nbcToolBox.Location = new System.Drawing.Point(0, 0);
            this.nbcToolBox.Name = "nbcToolBox";
           
            this.nbcToolBox.OptionsNavPane.ExpandedWidth = 140;
            this.nbcToolBox.ShowGroupHint = false;
            this.nbcToolBox.ShowLinkHint = false;
            this.nbcToolBox.Size = new System.Drawing.Size(164, 230);
            this.nbcToolBox.TabIndex = 7;
            this.nbcToolBox.Text = "navBarControl1";
            this.nbcToolBox.View = new DevExpress.XtraNavBar.ViewInfo.SkinExplorerBarViewInfoRegistrator();
            // 
            // grpToolBox
            // 
            this.grpToolBox.Caption = "Media";
            
            this.grpToolBox.Expanded = true;
            this.grpToolBox.GroupStyle = DevExpress.XtraNavBar.NavBarGroupStyle.SmallIconsText;
            this.grpToolBox.Name = "grpToolBox";
            this.grpToolBox.Hint = "Media";
            // 
            // ToolBoxControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.nbcToolBox);
            this.Name = "ToolBoxControl";
            
            this.Size = new System.Drawing.Size(164, 230);
            ((System.ComponentModel.ISupportInitialize)(this.nbcToolBox)).EndInit();
            this.nbcToolBox.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private DevExpress.XtraNavBar.NavBarControl nbcToolBox;
        private DevExpress.XtraNavBar.NavBarGroup grpToolBox;
    }
}
