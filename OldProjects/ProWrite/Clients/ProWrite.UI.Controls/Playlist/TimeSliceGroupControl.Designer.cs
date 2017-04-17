using ProWrite.Resources;
namespace ProWrite.UI.Controls.Playlist
{
    partial class TimeSliceGroupControl
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
            this.components = new System.ComponentModel.Container();
            this.btneEdit = new DevExpress.XtraEditors.ButtonEdit();
            this.tlGroup = new DevExpress.XtraTreeList.TreeList();
            this.tlcIsActive = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.ckEdit = new DevExpress.XtraEditors.Repository.RepositoryItemCheckEdit();
            this.tlcName = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.tlcLength = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.imgEdit = new DevExpress.XtraEditors.Repository.RepositoryItemImageEdit();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.cbeGroup = new DevExpress.XtraEditors.ComboBoxEdit();
            this.sbtnSave = new DevExpress.XtraEditors.SimpleButton();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.tsmiDelete = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.setDefaultImagetoolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.tsmiNewTimeSliceGroup = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmiEditTimeSliceGroup = new System.Windows.Forms.ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)(this.btneEdit.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tlGroup)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ckEdit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.imgEdit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.cbeGroup.Properties)).BeginInit();
            this.contextMenuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // btneEdit
            // 
            this.btneEdit.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btneEdit.Location = new System.Drawing.Point(161, 1);
            this.btneEdit.Name = "btneEdit";
            this.btneEdit.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Ellipsis, "Edit"),
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Plus, "Add New"),
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Close, "Delete")});
            this.btneEdit.Properties.TextEditStyle = DevExpress.XtraEditors.Controls.TextEditStyles.HideTextEditor;
            this.btneEdit.Size = new System.Drawing.Size(57, 21);
            this.btneEdit.TabIndex = 4;
            this.btneEdit.ButtonClick += new DevExpress.XtraEditors.Controls.ButtonPressedEventHandler(this.btneEdit_ButtonClick);
            // 
            // tlGroup
            // 
            this.tlGroup.AllowDrop = true;
            this.tlGroup.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tlGroup.Columns.AddRange(new DevExpress.XtraTreeList.Columns.TreeListColumn[] {
            this.tlcIsActive,
            this.tlcName,
            this.tlcLength});
            this.tlGroup.FixedLineWidth = 1;
            this.tlGroup.ImageIndexFieldName = "";
            this.tlGroup.Location = new System.Drawing.Point(2, 22);
            this.tlGroup.Name = "tlGroup";
            this.tlGroup.OptionsBehavior.AutoChangeParent = false;
            this.tlGroup.OptionsBehavior.AutoPopulateColumns = false;
            this.tlGroup.OptionsBehavior.AutoSelectAllInEditor = false;
            this.tlGroup.OptionsBehavior.DragNodes = true;
            this.tlGroup.OptionsBehavior.Editable = false;
            this.tlGroup.OptionsBehavior.EnableFiltering = true;
            this.tlGroup.OptionsBehavior.ImmediateEditor = false;
            this.tlGroup.OptionsBehavior.KeepSelectedOnClick = false;
            this.tlGroup.OptionsBehavior.MoveOnEdit = false;
            this.tlGroup.OptionsMenu.EnableColumnMenu = false;
            this.tlGroup.OptionsMenu.EnableFooterMenu = false;
            this.tlGroup.OptionsSelection.EnableAppearanceFocusedCell = false;
            this.tlGroup.OptionsView.ShowIndicator = false;
            this.tlGroup.OptionsView.ShowRoot = false;
            this.tlGroup.RepositoryItems.AddRange(new DevExpress.XtraEditors.Repository.RepositoryItem[] {
            this.ckEdit,
            this.imgEdit});
            this.tlGroup.Size = new System.Drawing.Size(217, 260);
            this.tlGroup.TabIndex = 3;
            this.tlGroup.TreeLineStyle = DevExpress.XtraTreeList.LineStyle.None;
            this.tlGroup.AfterDragNode += new DevExpress.XtraTreeList.NodeEventHandler(this.tlGroup_AfterDragNode);
            this.tlGroup.MouseDown += new System.Windows.Forms.MouseEventHandler(this.tlGroup_MouseDown);
            this.tlGroup.MouseUp += new System.Windows.Forms.MouseEventHandler(this.tlGroup_MouseUp);
            this.tlGroup.GetStateImage += new DevExpress.XtraTreeList.GetStateImageEventHandler(this.tlGroup_GetStateImage);
            this.tlGroup.DragObjectStart += new DevExpress.XtraTreeList.DragObjectStartEventHandler(this.tlGroup_DragObjectStart);
            this.tlGroup.KeyUp += new System.Windows.Forms.KeyEventHandler(this.tlGroup_KeyUp);
            this.tlGroup.DragDrop += new System.Windows.Forms.DragEventHandler(this.tlGroup_DragDrop);
            this.tlGroup.GiveFeedback += new System.Windows.Forms.GiveFeedbackEventHandler(this.tlGroup_GiveFeedback);
            this.tlGroup.DragEnter += new System.Windows.Forms.DragEventHandler(this.tlGroup_DragEnter);
            // 
            // tlcIsActive
            // 
            this.tlcIsActive.Caption = "ACTIVE";
            this.tlcIsActive.ColumnEdit = this.ckEdit;
            this.tlcIsActive.FieldName = "IsActive";
            this.tlcIsActive.ImageAlignment = System.Drawing.StringAlignment.Center;
            this.tlcIsActive.ImageIndex = 0;
            this.tlcIsActive.Name = "tlcIsActive";
            this.tlcIsActive.Visible = true;
            this.tlcIsActive.VisibleIndex = 0;
            this.tlcIsActive.Width = 70;
            // 
            // ckEdit
            // 
            this.ckEdit.AutoHeight = false;
            this.ckEdit.Name = "ckEdit";
            this.ckEdit.NullStyle = DevExpress.XtraEditors.Controls.StyleIndeterminate.Unchecked;
            // 
            // tlcName
            // 
            this.tlcName.Caption = "NAME";
            this.tlcName.FieldName = "Name";
            this.tlcName.ImageIndex = 1;
            this.tlcName.Name = "tlcName";
            this.tlcName.OptionsColumn.AllowEdit = false;
            this.tlcName.Visible = true;
            this.tlcName.VisibleIndex = 1;
            this.tlcName.Width = 69;
            // 
            // tlcLength
            // 
            this.tlcLength.Caption = "LENGTH";
            this.tlcLength.FieldName = "LENGTH";
            this.tlcLength.Name = "tlcLength";
            this.tlcLength.Visible = true;
            this.tlcLength.VisibleIndex = 2;
            this.tlcLength.Width = 69;
            // 
            // imgEdit
            // 
            this.imgEdit.AutoHeight = false;
            this.imgEdit.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.imgEdit.Name = "imgEdit";
            // 
            // imageList1
            // 
            this.imageList1.ColorDepth = System.Windows.Forms.ColorDepth.Depth8Bit;
            this.imageList1.ImageSize = new System.Drawing.Size(16, 16);
            this.imageList1.TransparentColor = System.Drawing.Color.Magenta;
            // 
            // cbeGroup
            // 
            this.cbeGroup.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.cbeGroup.EditValue = "";
            this.cbeGroup.Location = new System.Drawing.Point(1, 1);
            this.cbeGroup.Name = "cbeGroup";
            this.cbeGroup.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.cbeGroup.Properties.Items.AddRange(new object[] {
            "New year"});
            this.cbeGroup.Properties.TextEditStyle = DevExpress.XtraEditors.Controls.TextEditStyles.DisableTextEditor;
            this.cbeGroup.Size = new System.Drawing.Size(161, 20);
            this.cbeGroup.TabIndex = 1;
            this.cbeGroup.SelectedIndexChanged += new System.EventHandler(this.cbeGroup_SelectedIndexChanged);
            // 
            // sbtnSave
            // 
            this.sbtnSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.sbtnSave.ImageLocation = DevExpress.XtraEditors.ImageLocation.MiddleLeft;
            this.sbtnSave.Location = new System.Drawing.Point(146, 288);
            this.sbtnSave.Name = "sbtnSave";
            this.sbtnSave.Size = new System.Drawing.Size(67, 24);
            this.sbtnSave.TabIndex = 9;
            this.sbtnSave.ToolTip = "Save";
            this.sbtnSave.Visible = false;
            this.sbtnSave.Click += new System.EventHandler(this.sbtnSave_Click);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsmiDelete,
            this.toolStripSeparator1,
            this.setDefaultImagetoolStripMenuItem,
            this.toolStripSeparator2,
            this.tsmiNewTimeSliceGroup,
            this.tsmiEditTimeSliceGroup});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(204, 126);
            // 
            // tsmiDelete
            // 
            this.tsmiDelete.Name = "tsmiDelete";
            this.tsmiDelete.Size = new System.Drawing.Size(203, 22);
            this.tsmiDelete.Text = "Delete Message";
            this.tsmiDelete.Click += new System.EventHandler(this.deleteToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(200, 6);
            // 
            // setDefaultImagetoolStripMenuItem
            // 
            this.setDefaultImagetoolStripMenuItem.Name = "setDefaultImagetoolStripMenuItem";
            this.setDefaultImagetoolStripMenuItem.Size = new System.Drawing.Size(203, 22);
            this.setDefaultImagetoolStripMenuItem.Text = "SetDefaultImage";
            this.setDefaultImagetoolStripMenuItem.Click += new System.EventHandler(this.setDefaultImagetoolStripMenuItem_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(200, 6);
            // 
            // tsmiNewTimeSliceGroup
            // 
            this.tsmiNewTimeSliceGroup.Name = "tsmiNewTimeSliceGroup";
            this.tsmiNewTimeSliceGroup.Size = new System.Drawing.Size(203, 22);
            this.tsmiNewTimeSliceGroup.Text = "New Time Slice Group";
            this.tsmiNewTimeSliceGroup.Click += new System.EventHandler(this.tsmiNewTimeSliceGroup_Click);
            // 
            // tsmiEditTimeSliceGroup
            // 
            this.tsmiEditTimeSliceGroup.Name = "tsmiEditTimeSliceGroup";
            this.tsmiEditTimeSliceGroup.Size = new System.Drawing.Size(203, 22);
            this.tsmiEditTimeSliceGroup.Text = "Edit Time Slice Group";
            this.tsmiEditTimeSliceGroup.Click += new System.EventHandler(this.tsmiEditTimeSliceGroup_Click);
            // 
            // TimeSliceGroupControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.sbtnSave);
            this.Controls.Add(this.tlGroup);
            this.Controls.Add(this.btneEdit);
            this.Controls.Add(this.cbeGroup);
            this.Name = "TimeSliceGroupControl";
            this.Size = new System.Drawing.Size(219, 316);
            ((System.ComponentModel.ISupportInitialize)(this.btneEdit.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tlGroup)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ckEdit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.imgEdit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.cbeGroup.Properties)).EndInit();
            this.contextMenuStrip1.ResumeLayout(false);
            this.ResumeLayout(false);

        }


        #endregion

        private DevExpress.XtraEditors.ComboBoxEdit cbeGroup;
        private DevExpress.XtraTreeList.TreeList tlGroup;
        private DevExpress.XtraTreeList.Columns.TreeListColumn tlcName;
        private DevExpress.XtraTreeList.Columns.TreeListColumn tlcLength;
        private DevExpress.XtraTreeList.Columns.TreeListColumn tlcIsActive;
        private DevExpress.XtraEditors.Repository.RepositoryItemCheckEdit ckEdit;
        private DevExpress.XtraEditors.Repository.RepositoryItemImageEdit imgEdit;
        private System.Windows.Forms.ImageList imageList1;
        private DevExpress.XtraEditors.ButtonEdit btneEdit;
        private DevExpress.XtraEditors.SimpleButton sbtnSave;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem tsmiDelete;
        private System.Windows.Forms.ToolStripMenuItem setDefaultImagetoolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem tsmiNewTimeSliceGroup;
        private System.Windows.Forms.ToolStripMenuItem tsmiEditTimeSliceGroup;
    }
}
