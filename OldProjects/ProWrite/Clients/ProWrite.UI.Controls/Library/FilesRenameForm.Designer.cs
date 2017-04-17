using DevExpress.XtraNavBar;
using DevExpress.XtraEditors;
namespace ProWrite.UI.Controls.Library
{
    partial class FilesRenameForm
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
            this.navRename = new DevExpress.XtraNavBar.NavBarControl();
            this.groupFiles = new DevExpress.XtraNavBar.NavBarGroup();
            this.containerFiles = new DevExpress.XtraNavBar.NavBarGroupControlContainer();
            this.containerMessage = new DevExpress.XtraNavBar.NavBarGroupControlContainer();
            this.groupMessage = new DevExpress.XtraNavBar.NavBarGroup();
            this.sbtnCancel = new DevExpress.XtraEditors.SimpleButton();
            this.sbtnSave = new DevExpress.XtraEditors.SimpleButton();
            ((System.ComponentModel.ISupportInitialize)(this.navRename)).BeginInit();
            this.navRename.SuspendLayout();
            this.SuspendLayout();
            // 
            // navRename
            // 
            this.navRename.ActiveGroup = this.groupFiles;
            this.navRename.ContentButtonHint = null;
            this.navRename.Controls.Add(this.containerFiles);
            this.navRename.Controls.Add(this.containerMessage);
            this.navRename.Dock = System.Windows.Forms.DockStyle.Top;
            this.navRename.Groups.AddRange(new DevExpress.XtraNavBar.NavBarGroup[] {
            this.groupFiles,
            this.groupMessage});
            this.navRename.Location = new System.Drawing.Point(0, 0);
            this.navRename.Name = "navRename";
            this.navRename.OptionsNavPane.ExpandedWidth = 696;
            this.navRename.OptionsNavPane.ShowExpandButton = false;
            this.navRename.Size = new System.Drawing.Size(751, 268);
            this.navRename.SkinExplorerBarViewScrollStyle = DevExpress.XtraNavBar.SkinExplorerBarViewScrollStyle.ScrollBar;
            this.navRename.TabIndex = 21;
            this.navRename.Text = "Rename";
            // 
            // groupFiles
            // 
            this.groupFiles.Caption = "Files rename";
            this.groupFiles.ControlContainer = this.containerFiles;
            this.groupFiles.Expanded = true;
            this.groupFiles.GroupClientHeight = 21;
            this.groupFiles.GroupStyle = DevExpress.XtraNavBar.NavBarGroupStyle.ControlContainer;
            this.groupFiles.Name = "groupFiles";
            // 
            // containerFiles
            // 
            this.containerFiles.AutoScroll = true;
            this.containerFiles.Name = "containerFiles";
            this.containerFiles.Size = new System.Drawing.Size(747, 20);
            this.containerFiles.TabIndex = 0;
            // 
            // containerMessage
            // 
            this.containerMessage.AutoScroll = true;
            this.containerMessage.Name = "containerMessage";
            this.containerMessage.Size = new System.Drawing.Size(747, 20);
            this.containerMessage.TabIndex = 1;
            // 
            // groupMessage
            // 
            this.groupMessage.Caption = "Message rename";
            this.groupMessage.ControlContainer = this.containerMessage;
            this.groupMessage.Expanded = true;
            this.groupMessage.GroupClientHeight = 20;
            this.groupMessage.GroupStyle = DevExpress.XtraNavBar.NavBarGroupStyle.ControlContainer;
            this.groupMessage.Name = "groupMessage";
            // 
            // sbtnCancel
            // 
            this.sbtnCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.sbtnCancel.Location = new System.Drawing.Point(654, 294);
            this.sbtnCancel.Name = "sbtnCancel";
            this.sbtnCancel.Size = new System.Drawing.Size(75, 23);
            this.sbtnCancel.TabIndex = 9;
            this.sbtnCancel.Text = "Cancel";
            this.sbtnCancel.Click += new System.EventHandler(this.sbtnCancel_Click);
            // 
            // sbtnSave
            // 
            this.sbtnSave.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.sbtnSave.Location = new System.Drawing.Point(556, 294);
            this.sbtnSave.Name = "sbtnSave";
            this.sbtnSave.Size = new System.Drawing.Size(92, 23);
            this.sbtnSave.TabIndex = 8;
            this.sbtnSave.Text = "Save";
            this.sbtnSave.Click += new System.EventHandler(this.sbtnSave_Click);
            // 
            // FilesRenameForm
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(751, 329);
            this.Controls.Add(this.navRename);
            this.Controls.Add(this.sbtnCancel);
            this.Controls.Add(this.sbtnSave);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FilesRenameForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Library Files Rename Dialog";
            ((System.ComponentModel.ISupportInitialize)(this.navRename)).EndInit();
            this.navRename.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private DevExpress.XtraNavBar.NavBarControl navRename;
        private DevExpress.XtraEditors.SimpleButton sbtnCancel;
        private DevExpress.XtraEditors.SimpleButton sbtnSave;
        private NavBarGroup groupFiles;
        private NavBarGroup groupMessage;
        private NavBarGroupControlContainer containerFiles;
        private NavBarGroupControlContainer containerMessage;
    }
}