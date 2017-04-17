using ProWrite.UI.Clients.Test.Properties;

namespace ProWrite.UI.Clients.Test.FontSample
{
    partial class frmTreeList
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
            this.components = new System.ComponentModel.Container();
            DevExpress.Utils.SerializableAppearanceObject serializableAppearanceObject1 = new DevExpress.Utils.SerializableAppearanceObject();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmTreeList));
            this.ckEdit = new DevExpress.XtraEditors.Repository.RepositoryItemCheckEdit();
            this.imgEdit = new DevExpress.XtraEditors.Repository.RepositoryItemImageEdit();
            this.repositoryItemCheckEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemCheckEdit();
            this.repositoryItemImageEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemImageEdit();
            this.tlGroup = new DevExpress.XtraTreeList.TreeList();
            this.tlcIsActive = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.tlcName = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.tlcType = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.label1 = new DevExpress.XtraScheduler.UI.RepositoryItemAppointmentLabel();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.tlcLength = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.repositoryItemCheckEdit2 = new DevExpress.XtraEditors.Repository.RepositoryItemCheckEdit();
            this.repositoryItemImageEdit2 = new DevExpress.XtraEditors.Repository.RepositoryItemImageEdit();
            ((System.ComponentModel.ISupportInitialize)(this.ckEdit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.imgEdit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemCheckEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemImageEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tlGroup)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.label1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemCheckEdit2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemImageEdit2)).BeginInit();
            this.SuspendLayout();
            // 
            // ckEdit
            // 
            this.ckEdit.AutoHeight = false;
            this.ckEdit.Name = "ckEdit";
            this.ckEdit.NullStyle = DevExpress.XtraEditors.Controls.StyleIndeterminate.Unchecked;
            // 
            // imgEdit
            // 
            this.imgEdit.AutoHeight = false;
            this.imgEdit.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.imgEdit.Name = "imgEdit";
            // 
            // repositoryItemCheckEdit1
            // 
            this.repositoryItemCheckEdit1.AutoHeight = false;
            this.repositoryItemCheckEdit1.Name = "repositoryItemCheckEdit1";
            this.repositoryItemCheckEdit1.NullStyle = DevExpress.XtraEditors.Controls.StyleIndeterminate.Unchecked;
            // 
            // repositoryItemImageEdit1
            // 
            this.repositoryItemImageEdit1.AutoHeight = false;
            this.repositoryItemImageEdit1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.repositoryItemImageEdit1.Name = "repositoryItemImageEdit1";
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
            this.tlcType,
            this.tlcLength});
            this.tlGroup.CustomizationFormBounds = new System.Drawing.Rectangle(594, 236, 208, 170);
            this.tlGroup.FixedLineWidth = 1;
            this.tlGroup.ImageIndexFieldName = "";
            this.tlGroup.Location = new System.Drawing.Point(38, 3);
			//this.tlGroup.LookAndFeel.SkinName = Resources.Resource.GetString(Resources.Resource.Strings.SkinName);
            this.tlGroup.LookAndFeel.UseDefaultLookAndFeel = false;
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
            this.tlGroup.OptionsBehavior.PopulateServiceColumns = true;
            this.tlGroup.OptionsMenu.EnableColumnMenu = false;
            this.tlGroup.OptionsMenu.EnableFooterMenu = false;
            this.tlGroup.RepositoryItems.AddRange(new DevExpress.XtraEditors.Repository.RepositoryItem[] {
            this.repositoryItemCheckEdit2,
            this.label1});
            this.tlGroup.Size = new System.Drawing.Size(317, 319);
            this.tlGroup.TabIndex = 4;
            this.tlGroup.TreeLineStyle = DevExpress.XtraTreeList.LineStyle.None;
            this.tlGroup.MouseDown += new System.Windows.Forms.MouseEventHandler(this.tlGroup_MouseDown);
            this.tlGroup.FocusedNodeChanged += new DevExpress.XtraTreeList.FocusedNodeChangedEventHandler(this.tlGroup_FocusedNodeChanged);
            // 
            // tlcIsActive
            // 
            this.tlcIsActive.Caption = "ACTIVE";
            this.tlcIsActive.FieldName = "IsActive";
            this.tlcIsActive.ImageAlignment = System.Drawing.StringAlignment.Center;
            this.tlcIsActive.ImageIndex = 0;
            this.tlcIsActive.Name = "tlcIsActive";
            this.tlcIsActive.Visible = true;
            this.tlcIsActive.VisibleIndex = 0;
            this.tlcIsActive.Width = 70;
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
            // tlcType
            // 
            this.tlcType.Caption = "TYPE";
            this.tlcType.ColumnEdit = this.label1;
            this.tlcType.FieldName = "Type";
            this.tlcType.ImageIndex = 0;
            this.tlcType.Name = "tlcType";
            this.tlcType.OptionsColumn.AllowEdit = false;
            this.tlcType.Visible = true;
            this.tlcType.VisibleIndex = 2;
            this.tlcType.Width = 69;
            // 
            // label1
            // 
            //this.label1.Appearance.Image = global::WindowsApplication1.Properties.Resources.PWLogoG;
            this.label1.Appearance.Options.UseImage = true;
            this.label1.Appearance.Options.UseTextOptions = true;
            this.label1.Appearance.TextOptions.VAlignment = DevExpress.Utils.VertAlignment.Center;
            this.label1.AutoHeight = false;
            //serializableAppearanceObject1.Image = global::WindowsApplication1.Properties.Resources.PWLogoG;
            serializableAppearanceObject1.Options.UseImage = true;
            this.label1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo, "", -1, true, true, false, DevExpress.XtraEditors.ImageLocation.MiddleCenter, null, new DevExpress.Utils.KeyShortcut(System.Windows.Forms.Keys.None), serializableAppearanceObject1)});
            this.label1.ExportMode = DevExpress.XtraEditors.Repository.ExportMode.DisplayText;
            this.label1.Name = "label1";
            this.label1.SmallImages = this.imageList1;
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Magenta;
            this.imageList1.Images.SetKeyName(0, "PWLogoG.png");
            // 
            // tlcLength
            // 
            this.tlcLength.Caption = "LENGTH";
            this.tlcLength.FieldName = "LENGTH";
            this.tlcLength.Name = "tlcLength";
            this.tlcLength.SortOrder = System.Windows.Forms.SortOrder.Ascending;
            this.tlcLength.Visible = true;
            this.tlcLength.VisibleIndex = 3;
            this.tlcLength.Width = 69;
            // 
            // repositoryItemCheckEdit2
            // 
            this.repositoryItemCheckEdit2.AutoHeight = false;
            this.repositoryItemCheckEdit2.Name = "repositoryItemCheckEdit2";
            this.repositoryItemCheckEdit2.NullStyle = DevExpress.XtraEditors.Controls.StyleIndeterminate.Unchecked;
            // 
            // repositoryItemImageEdit2
            // 
            this.repositoryItemImageEdit2.AutoHeight = false;
            this.repositoryItemImageEdit2.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.repositoryItemImageEdit2.Name = "repositoryItemImageEdit2";
            // 
            // frmTreeList
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(392, 325);
            this.Controls.Add(this.tlGroup);
            this.Name = "frmTreeList";
            this.Text = "TreeList Sample";
            ((System.ComponentModel.ISupportInitialize)(this.ckEdit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.imgEdit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemCheckEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemImageEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tlGroup)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.label1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemCheckEdit2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemImageEdit2)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private DevExpress.XtraEditors.Repository.RepositoryItemCheckEdit ckEdit;
        private DevExpress.XtraEditors.Repository.RepositoryItemImageEdit imgEdit;
        private DevExpress.XtraEditors.Repository.RepositoryItemCheckEdit repositoryItemCheckEdit1;
        private DevExpress.XtraEditors.Repository.RepositoryItemImageEdit repositoryItemImageEdit1;
        private DevExpress.XtraTreeList.TreeList tlGroup;
        private DevExpress.XtraTreeList.Columns.TreeListColumn tlcIsActive;
        private DevExpress.XtraTreeList.Columns.TreeListColumn tlcName;
        private DevExpress.XtraTreeList.Columns.TreeListColumn tlcType;
        private DevExpress.XtraTreeList.Columns.TreeListColumn tlcLength;
        private DevExpress.XtraEditors.Repository.RepositoryItemCheckEdit repositoryItemCheckEdit2;
        private DevExpress.XtraEditors.Repository.RepositoryItemImageEdit repositoryItemImageEdit2;
        private DevExpress.XtraScheduler.UI.RepositoryItemAppointmentLabel label1;
        private System.Windows.Forms.ImageList imageList1;
    }
}