namespace ProWrite.UI.Controls.Playlist
{
    partial class PlayListTree
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PlayListTree));
            this.btnDelete = new DevExpress.XtraEditors.SimpleButton();
            this.btnSave = new DevExpress.XtraEditors.SimpleButton();
            this.playStopBar = new ProWrite.UI.Controls.PlayStopBar();
            this.repName = new DevExpress.XtraEditors.Repository.RepositoryItemTextEdit();
            this.repType = new DevExpress.XtraEditors.Repository.RepositoryItemTextEdit();
            this.repLength = new DevExpress.XtraEditors.Repository.RepositoryItemTextEdit();
            this.repositoryItemImageEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemImageEdit();
            this.treeListColumnLength = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.treeListColumn2 = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.treeListColumnType = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.treeListColumn4 = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.treeList = new DevExpress.XtraTreeList.TreeList();
            this.xtraTabControl1 = new DevExpress.XtraTab.XtraTabControl();
            this.xtraTabPage1 = new DevExpress.XtraTab.XtraTabPage();
            this.xtraTabPage2 = new DevExpress.XtraTab.XtraTabPage();
            ((System.ComponentModel.ISupportInitialize)(this.repName)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repType)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repLength)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemImageEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.treeList)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.xtraTabControl1)).BeginInit();
            this.xtraTabControl1.SuspendLayout();
            this.xtraTabPage1.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnDelete
            // 
            this.btnDelete.AllowDrop = true;
            this.btnDelete.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnDelete.Image = ((System.Drawing.Image)(resources.GetObject("btnDelete.Image")));
            this.btnDelete.Location = new System.Drawing.Point(67, 397);
            this.btnDelete.Name = "btnDelete";
            this.btnDelete.Size = new System.Drawing.Size(27, 31);
            this.btnDelete.TabIndex = 13;
            this.btnDelete.ToolTip = "Delete";
            this.btnDelete.Click += new System.EventHandler(this.btnDelete_Click);
            this.btnDelete.DragDrop += new System.Windows.Forms.DragEventHandler(this.btnDelete_DragDrop);
            this.btnDelete.DragLeave += new System.EventHandler(this.btnDelete_DragLeave);
            this.btnDelete.DragEnter += new System.Windows.Forms.DragEventHandler(this.btnDelete_DragEnter);
            // 
            // btnSave
            // 
            this.btnSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnSave.Image = ((System.Drawing.Image)(resources.GetObject("btnSave.Image")));
            this.btnSave.Location = new System.Drawing.Point(27, 397);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(25, 31);
            this.btnSave.TabIndex = 12;
            this.btnSave.ToolTip = "Add";
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // playStopBar
            // 
            this.playStopBar.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("playStopBar.BackgroundImage")));
            this.playStopBar.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.playStopBar.IsSupportGlobalization = false;
            this.playStopBar.Location = new System.Drawing.Point(0, 434);
            this.playStopBar.Name = "playStopBar";
            this.playStopBar.Size = new System.Drawing.Size(516, 39);
            this.playStopBar.TabIndex = 14;
            // 
            // repName
            // 
            this.repName.AllowFocused = false;
            this.repName.AutoHeight = false;
            this.repName.Name = "repName";
            // 
            // repType
            // 
            this.repType.AllowFocused = false;
            this.repType.AutoHeight = false;
            this.repType.Name = "repType";
            // 
            // repLength
            // 
            this.repLength.AllowFocused = false;
            this.repLength.AutoHeight = false;
            this.repLength.Name = "repLength";
            // 
            // repositoryItemImageEdit1
            // 
            this.repositoryItemImageEdit1.AllowFocused = false;
            this.repositoryItemImageEdit1.AutoHeight = false;
            this.repositoryItemImageEdit1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.repositoryItemImageEdit1.Name = "repositoryItemImageEdit1";
            this.repositoryItemImageEdit1.PopupStartSize = new System.Drawing.Size(270, 180);
            // 
            // treeListColumnLength
            // 
            this.treeListColumnLength.Caption = "Length";
            this.treeListColumnLength.ColumnEdit = this.repLength;
            this.treeListColumnLength.FieldName = "Length";
            this.treeListColumnLength.Name = "treeListColumnLength";
            this.treeListColumnLength.Visible = true;
            this.treeListColumnLength.VisibleIndex = 2;
            this.treeListColumnLength.Width = 77;
            // 
            // treeListColumn2
            // 
            this.treeListColumn2.Caption = "Name";
            this.treeListColumn2.ColumnEdit = this.repName;
            this.treeListColumn2.FieldName = "Name";
            this.treeListColumn2.Name = "treeListColumn2";
            this.treeListColumn2.Visible = true;
            this.treeListColumn2.VisibleIndex = 0;
            this.treeListColumn2.Width = 132;
            // 
            // treeListColumnType
            // 
            this.treeListColumnType.Caption = "Type";
            this.treeListColumnType.ColumnEdit = this.repType;
            this.treeListColumnType.FieldName = "Type";
            this.treeListColumnType.Name = "treeListColumnType";
            this.treeListColumnType.Visible = true;
            this.treeListColumnType.VisibleIndex = 1;
            this.treeListColumnType.Width = 89;
            // 
            // treeListColumn4
            // 
            this.treeListColumn4.Caption = "Picture";
            this.treeListColumn4.ColumnEdit = this.repositoryItemImageEdit1;
            this.treeListColumn4.FieldName = "Picture";
            this.treeListColumn4.Name = "treeListColumn4";
            this.treeListColumn4.Visible = true;
            this.treeListColumn4.VisibleIndex = 3;
            // 
            // treeList
            // 
            this.treeList.AllowDrop = true;
            this.treeList.Columns.AddRange(new DevExpress.XtraTreeList.Columns.TreeListColumn[] {
            this.treeListColumnLength,
            this.treeListColumn2,
            this.treeListColumnType,
            this.treeListColumn4});
            this.treeList.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeList.Location = new System.Drawing.Point(0, 0);
            this.treeList.Name = "treeList";
            this.treeList.OptionsView.AutoWidth = false;
            this.treeList.RepositoryItems.AddRange(new DevExpress.XtraEditors.Repository.RepositoryItem[] {
            this.repName,
            this.repositoryItemImageEdit1});
            this.treeList.Size = new System.Drawing.Size(481, 382);
            this.treeList.TabIndex = 15;
            // 
            // xtraTabControl1
            // 
            this.xtraTabControl1.Dock = System.Windows.Forms.DockStyle.Top;
            this.xtraTabControl1.HeaderLocation = DevExpress.XtraTab.TabHeaderLocation.Left;
            this.xtraTabControl1.Location = new System.Drawing.Point(0, 0);
            this.xtraTabControl1.Name = "xtraTabControl1";
            this.xtraTabControl1.SelectedTabPage = this.xtraTabPage1;
            this.xtraTabControl1.Size = new System.Drawing.Size(516, 391);
            this.xtraTabControl1.TabIndex = 16;
            this.xtraTabControl1.TabPages.AddRange(new DevExpress.XtraTab.XtraTabPage[] {
            this.xtraTabPage1,
            this.xtraTabPage2});
            // 
            // xtraTabPage1
            // 
            this.xtraTabPage1.Controls.Add(this.treeList);
            this.xtraTabPage1.Name = "xtraTabPage1";
            this.xtraTabPage1.Size = new System.Drawing.Size(481, 382);
            this.xtraTabPage1.Text = "xtraTabPage1";
            // 
            // xtraTabPage2
            // 
            this.xtraTabPage2.Name = "xtraTabPage2";
            this.xtraTabPage2.Size = new System.Drawing.Size(481, 382);
            this.xtraTabPage2.Text = "xtraTabPage2";
            // 
            // PlayListTree
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.xtraTabControl1);
            this.Controls.Add(this.playStopBar);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.btnDelete);
            this.Name = "PlayListTree";
            this.Size = new System.Drawing.Size(516, 473);
            ((System.ComponentModel.ISupportInitialize)(this.repName)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repType)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repLength)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemImageEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.treeList)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.xtraTabControl1)).EndInit();
            this.xtraTabControl1.ResumeLayout(false);
            this.xtraTabPage1.ResumeLayout(false);
            this.ResumeLayout(false);

        }


        #endregion

        private DevExpress.XtraEditors.SimpleButton btnDelete;
        private DevExpress.XtraEditors.SimpleButton btnSave;
        private PlayStopBar playStopBar;
        private DevExpress.XtraEditors.Repository.RepositoryItemTextEdit repName;
        private DevExpress.XtraEditors.Repository.RepositoryItemTextEdit repLength;
        private DevExpress.XtraEditors.Repository.RepositoryItemTextEdit repType;
        //private DevExpress.XtraEditors.Repository.RepositoryItemCheckEdit repositoryItemCheckEdit1;
        //private DevExpress.XtraEditors.Repository.RepositoryItemDateEdit repositoryItemDateEdit1;
        private DevExpress.XtraEditors.Repository.RepositoryItemImageEdit repImage;
        //private DevExpress.XtraEditors.Repository.RepositoryItemMemoExEdit repositoryItemMemoExEdit1;
        private DevExpress.XtraTreeList.Columns.TreeListColumn treeListColumnLength;
        private DevExpress.XtraTreeList.Columns.TreeListColumn treeListColumnName;
        private DevExpress.XtraTreeList.Columns.TreeListColumn treeListColumnType;
        private DevExpress.XtraTreeList.Columns.TreeListColumn treeListColumnImage;
        //private DevExpress.XtraTreeList.Columns.TreeListColumn treeListColumn5;
        //private DevExpress.XtraTreeList.Columns.TreeListColumn treeListColumn6;
        private DevExpress.XtraTreeList.TreeList treeList;
        private DevExpress.XtraEditors.Repository.RepositoryItemImageEdit repositoryItemImageEdit1;
        private DevExpress.XtraTreeList.Columns.TreeListColumn treeListColumn2;
        private DevExpress.XtraTreeList.Columns.TreeListColumn treeListColumn4;
        private DevExpress.XtraTab.XtraTabControl xtraTabControl1;
        private DevExpress.XtraTab.XtraTabPage xtraTabPage1;
        private DevExpress.XtraTab.XtraTabPage xtraTabPage2;
    }
}
