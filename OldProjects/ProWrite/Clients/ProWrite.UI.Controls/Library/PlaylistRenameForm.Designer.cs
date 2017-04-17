using DevExpress.XtraNavBar;
using DevExpress.XtraEditors;
namespace ProWrite.UI.Controls.Library
{
    partial class PlaylistRenameForm
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
            this.navRename = new NavBarControl();
            this.sbtnCancel = new SimpleButton();
            this.sbtnSave = new SimpleButton();
            //navRename = new NavBarControl();
            this.groupFiles = new NavBarGroup();
            this.groupMessage = new NavBarGroup();
            this.groupTimeSliceGroup = new NavBarGroup();
            this.groupPlaylist = new NavBarGroup();
            this.containerFiles = new NavBarGroupControlContainer();
            this.containerMessage = new NavBarGroupControlContainer();
            this.containerTimeSliceGroup = new NavBarGroupControlContainer();
            this.containerPlaylist = new NavBarGroupControlContainer();
            

            ((System.ComponentModel.ISupportInitialize)(this.navRename)).BeginInit();
            this.SuspendLayout();
            // 
            // containerFiles
            // 
            this.containerFiles.Name = "containerFiles";
            this.containerFiles.Size = new System.Drawing.Size(100, 20);
            this.containerFiles.TabIndex = 0;
            containerFiles.AutoScroll = true;

            // 
            // containerMessage
            // 
            this.containerMessage.Name = "containerMessage";
            this.containerMessage.Size = new System.Drawing.Size(100, 20);
            this.containerMessage.TabIndex = 1;
            containerMessage.AutoScroll = true;
            // 
            // containerTimeSliceGroup
            // 
            this.containerTimeSliceGroup.Name = "containerTimeSliceGroup";
            this.containerTimeSliceGroup.Size = new System.Drawing.Size(100, 20);
            this.containerTimeSliceGroup.TabIndex = 2;
            containerTimeSliceGroup.AutoScroll = true;
            // 
            // containerPlaylist
            // 
            this.containerPlaylist.Name = "containerPlaylist";
            this.containerPlaylist.Size = new System.Drawing.Size(100, 20);
            this.containerPlaylist.TabIndex = 2;
            containerPlaylist.AutoScroll = true;

            // 
            // groupFiles
            // 
            this.groupFiles.Caption = "Files rename";
            this.groupFiles.ControlContainer = this.containerFiles;
            this.groupFiles.GroupClientHeight = 20;
            this.groupFiles.GroupStyle = DevExpress.XtraNavBar.NavBarGroupStyle.ControlContainer;
            this.groupFiles.Name = "groupFiles";

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
            // groupTimeSliceGroup
            // 
            this.groupTimeSliceGroup.Caption = "TimeSliceGroup rename";
            this.groupTimeSliceGroup.ControlContainer = this.containerTimeSliceGroup;
            this.groupTimeSliceGroup.Expanded = true;
            this.groupTimeSliceGroup.GroupClientHeight = 20;
            this.groupTimeSliceGroup.GroupStyle = DevExpress.XtraNavBar.NavBarGroupStyle.ControlContainer;
            this.groupTimeSliceGroup.Name = "groupTimeSliceGroup";

            // 
            // groupPlaylist
            // 
            this.groupPlaylist.Caption = "Playlist rename";
            this.groupPlaylist.ControlContainer = this.containerPlaylist;
            this.groupPlaylist.Expanded = true;
            this.groupPlaylist.GroupClientHeight = 20;
            this.groupPlaylist.GroupStyle = DevExpress.XtraNavBar.NavBarGroupStyle.ControlContainer;
            this.groupPlaylist.Name = "groupPlaylist";

            // navRename
            // 
            this.navRename.ActiveGroup = this.groupFiles;
            this.navRename.ContentButtonHint = null;
            this.navRename.Controls.Add(this.containerFiles);
            this.navRename.Controls.Add(this.containerMessage);
            this.navRename.Controls.Add(this.containerTimeSliceGroup);
            this.navRename.Controls.Add(this.containerPlaylist);
            this.navRename.Dock = System.Windows.Forms.DockStyle.Top;
            this.navRename.Groups.AddRange(new DevExpress.XtraNavBar.NavBarGroup[] {
            this.groupFiles,
            this.groupMessage,
            this.groupTimeSliceGroup,
            this.groupPlaylist
            });
            this.navRename.Location = new System.Drawing.Point(0, 46);
            this.navRename.Name = "navRename";
            this.navRename.OptionsNavPane.ExpandedWidth = 696;
            this.navRename.Size = new System.Drawing.Size(719, 268);
            this.navRename.SkinExplorerBarViewScrollStyle = DevExpress.XtraNavBar.SkinExplorerBarViewScrollStyle.ScrollBar;
            this.navRename.TabIndex = 21;
            this.navRename.Text = "Rename";
            // 
            // sbtnCancel
            // 
            this.sbtnCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.sbtnCancel.Location = new System.Drawing.Point(641, 294);
            this.sbtnCancel.Name = "sbtnCancel";
            this.sbtnCancel.Size = new System.Drawing.Size(75, 23);
            this.sbtnCancel.TabIndex = 9;
            this.sbtnCancel.Text = "Cancel";
            this.sbtnCancel.Click += new System.EventHandler(sbtnCancel_Click);
            // 
            // sbtnSave
            // 
            this.sbtnSave.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.sbtnSave.Location = new System.Drawing.Point(556, 294);
            this.sbtnSave.Name = "sbtnSave";
            this.sbtnSave.Size = new System.Drawing.Size(79, 23);
            this.sbtnSave.TabIndex = 8;
            this.sbtnSave.Text = "Save";
            this.sbtnSave.Click += new System.EventHandler(sbtnSave_Click);

            // 
            // TimeSlieceGroupRenameForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(738, 329);
            this.Controls.Add(this.sbtnCancel);
            this.Controls.Add(this.sbtnSave);
            this.Controls.Add(this.navRename);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Name = "PlaylistRenameForm";
            this.Text = "Playlist Files Rename Dialog";
            ((System.ComponentModel.ISupportInitialize)(this.navRename)).EndInit();
            this.ResumeLayout(false);
            //this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(TimeSlieceGroupRenameForm_FormClosed);

        }

        #endregion

        private DevExpress.XtraNavBar.NavBarControl navRename;
        private DevExpress.XtraEditors.SimpleButton sbtnCancel;
        private DevExpress.XtraEditors.SimpleButton sbtnSave;
        private NavBarGroup groupFiles;
        private NavBarGroup groupMessage;
        private NavBarGroup groupTimeSliceGroup;
        private NavBarGroup groupPlaylist;
        private NavBarGroupControlContainer containerFiles;
        private NavBarGroupControlContainer containerMessage;
        private NavBarGroupControlContainer containerTimeSliceGroup;
        private NavBarGroupControlContainer containerPlaylist;

    }
}