namespace ProWrite.UI.Controls.Live.Sessions
{
    partial class LibraryCategoryControl
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
            this.tabCategories = new DevExpress.XtraTab.XtraTabControl();
            this.tabPageLibrary = new DevExpress.XtraTab.XtraTabPage();
            this.tabPageCategory = new DevExpress.XtraTab.XtraTabPage();
            this.gridExistCategory = new DevExpress.XtraGrid.GridControl();
            this.gridView = new DevExpress.XtraGrid.Views.Grid.GridView();
            this.gvDisplay = new DevExpress.XtraGrid.Columns.GridColumn();
            this.repositoryItemCheckEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemCheckEdit();
            this.gvName = new DevExpress.XtraGrid.Columns.GridColumn();
            this.btnDeleteCategory = new DevExpress.XtraEditors.SimpleButton();
            this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
            ((System.ComponentModel.ISupportInitialize)(this.tabCategories)).BeginInit();
            this.tabCategories.SuspendLayout();
            this.tabPageCategory.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.gridExistCategory)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemCheckEdit1)).BeginInit();
            this.SuspendLayout();
            // 
            // tabCategories
            // 
            this.tabCategories.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tabCategories.HeaderLocation = DevExpress.XtraTab.TabHeaderLocation.Bottom;
            this.tabCategories.Location = new System.Drawing.Point(0, 28);
            this.tabCategories.Name = "tabCategories";
            this.tabCategories.SelectedTabPage = this.tabPageLibrary;
            this.tabCategories.Size = new System.Drawing.Size(223, 295);
            this.tabCategories.TabIndex = 0;
            this.tabCategories.TabPages.AddRange(new DevExpress.XtraTab.XtraTabPage[] {
            this.tabPageLibrary,
            this.tabPageCategory});
            this.tabCategories.SelectedPageChanged += new DevExpress.XtraTab.TabPageChangedEventHandler(this.tabCategories_SelectedPageChanged);
            // 
            // tabPageLibrary
            // 
            this.tabPageLibrary.Enabled = true;
            this.tabPageLibrary.Name = "tabPageLibrary";
            this.tabPageLibrary.Size = new System.Drawing.Size(214, 264);
            this.tabPageLibrary.Text = "Library";
            // 
            // tabPageCategory
            // 
            this.tabPageCategory.Controls.Add(this.gridExistCategory);
            this.tabPageCategory.Enabled = true;
            this.tabPageCategory.Name = "tabPageCategory";
            this.tabPageCategory.Size = new System.Drawing.Size(214, 264);
            this.tabPageCategory.Text = "All Categories";
            // 
            // gridExistCategory
            // 
            this.gridExistCategory.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gridExistCategory.Location = new System.Drawing.Point(0, 0);
            this.gridExistCategory.MainView = this.gridView;
            this.gridExistCategory.Name = "gridExistCategory";
            this.gridExistCategory.RepositoryItems.AddRange(new DevExpress.XtraEditors.Repository.RepositoryItem[] {
            this.repositoryItemCheckEdit1});
            this.gridExistCategory.Size = new System.Drawing.Size(214, 264);
            this.gridExistCategory.TabIndex = 1;
            this.gridExistCategory.ViewCollection.AddRange(new DevExpress.XtraGrid.Views.Base.BaseView[] {
            this.gridView});
            // 
            // gridView
            // 
            this.gridView.Columns.AddRange(new DevExpress.XtraGrid.Columns.GridColumn[] {
            this.gvDisplay,
            this.gvName});
            this.gridView.FocusRectStyle = DevExpress.XtraGrid.Views.Grid.DrawFocusRectStyle.RowFocus;
            this.gridView.GridControl = this.gridExistCategory;
            this.gridView.Name = "gridView";
            this.gridView.OptionsMenu.EnableColumnMenu = false;
            this.gridView.OptionsMenu.EnableFooterMenu = false;
            this.gridView.OptionsMenu.EnableGroupPanelMenu = false;
            this.gridView.OptionsMenu.ShowGroupSortSummaryItems = false;
            this.gridView.OptionsSelection.MultiSelect = true;
            this.gridView.CustomRowCellEditForEditing += new DevExpress.XtraGrid.Views.Grid.CustomRowCellEditEventHandler(this.gridView_CustomRowCellEditForEditing);
            // 
            // gvDisplay
            // 
            this.gvDisplay.Caption = "Show";
            this.gvDisplay.ColumnEdit = this.repositoryItemCheckEdit1;
            this.gvDisplay.FieldName = "CheckedState";
            this.gvDisplay.Name = "gvDisplay";
            this.gvDisplay.Visible = true;
            this.gvDisplay.VisibleIndex = 0;
            this.gvDisplay.Width = 50;
            // 
            // repositoryItemCheckEdit1
            // 
            this.repositoryItemCheckEdit1.AutoHeight = false;
            this.repositoryItemCheckEdit1.Name = "repositoryItemCheckEdit1";
            // 
            // gvName
            // 
            this.gvName.Caption = "Name";
            this.gvName.FieldName = "Name";
            this.gvName.Name = "gvName";
            this.gvName.Visible = true;
            this.gvName.VisibleIndex = 1;
            this.gvName.Width = 143;
            this.gvName.RealColumnEdit.ReadOnly = true;
            // 
            // btnDeleteCategory
            // 
            this.btnDeleteCategory.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnDeleteCategory.Location = new System.Drawing.Point(153, 300);
            this.btnDeleteCategory.Name = "btnDeleteCategory";
            this.btnDeleteCategory.Size = new System.Drawing.Size(68, 24);
            this.btnDeleteCategory.TabIndex = 1;
            this.btnDeleteCategory.Text = "&Delete";
            this.btnDeleteCategory.ToolTip = "Delete Category";
            this.btnDeleteCategory.Click += new System.EventHandler(this.btnDeleteCategory_Click);
            // 
            // labelControl1
            // 
            this.labelControl1.Location = new System.Drawing.Point(95, 8);
            this.labelControl1.Name = "labelControl1";
            this.labelControl1.Size = new System.Drawing.Size(33, 13);
            this.labelControl1.TabIndex = 2;
            this.labelControl1.Text = "Library";
            // 
            // LibraryCategoryControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.labelControl1);
            this.Controls.Add(this.btnDeleteCategory);
            this.Controls.Add(this.tabCategories);
            this.Name = "LibraryCategoryControl";
            this.Size = new System.Drawing.Size(222, 327);
            this.Load += new System.EventHandler(this.LibraryCategoryControl_Load);
            ((System.ComponentModel.ISupportInitialize)(this.tabCategories)).EndInit();
            this.tabCategories.ResumeLayout(false);
            this.tabPageCategory.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.gridExistCategory)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemCheckEdit1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }


        #endregion

        private DevExpress.XtraTab.XtraTabControl tabCategories;
        private DevExpress.XtraEditors.SimpleButton btnDeleteCategory;
        private DevExpress.XtraEditors.LabelControl labelControl1;
        private DevExpress.XtraTab.XtraTabPage tabPageLibrary;
        private DevExpress.XtraTab.XtraTabPage tabPageCategory;
        private DevExpress.XtraGrid.GridControl gridExistCategory;
        private DevExpress.XtraGrid.Views.Grid.GridView gridView;
        private DevExpress.XtraGrid.Columns.GridColumn gvDisplay;
        private DevExpress.XtraEditors.Repository.RepositoryItemCheckEdit repositoryItemCheckEdit1;
        private DevExpress.XtraGrid.Columns.GridColumn gvName;
    }
}
