using DevExpress.XtraGrid.Views.Grid;
namespace ProWrite.UI.Controls.Live.Sessions
{
    partial class MessageGridControl
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
            DevExpress.XtraGrid.StyleFormatCondition styleFormatCondition1 = new DevExpress.XtraGrid.StyleFormatCondition();
            this.gridControl = new DevExpress.XtraGrid.GridControl();
            this.gridView = new DevExpress.XtraGrid.Views.Grid.GridView();
            this.gvName = new DevExpress.XtraGrid.Columns.GridColumn();
            this.gvTimeLength = new DevExpress.XtraGrid.Columns.GridColumn();
            this.gvImage = new DevExpress.XtraGrid.Columns.GridColumn();
            this.repositoryItemImageEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemImageEdit();
            this.repositoryItemImageComboBox1 = new DevExpress.XtraEditors.Repository.RepositoryItemImageComboBox();
            this.repositoryItemMemoExEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemMemoExEdit();
            this.repositoryItemHyperLinkEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemHyperLinkEdit();
            this.repositoryItemPictureEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemPictureEdit();
            this.repositoryItemSpinEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemSpinEdit();
            this.repositoryItemDateEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemDateEdit();
            this.cvName = new DevExpress.XtraGrid.Columns.GridColumn();
            this.cvImage = new DevExpress.XtraGrid.Columns.GridColumn();
            this.cvTimeLength = new DevExpress.XtraGrid.Columns.GridColumn();
            cardView = new DevExpress.XtraGrid.Views.Card.CardView();
            ((System.ComponentModel.ISupportInitialize)(this.gridControl)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemImageEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemImageComboBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemMemoExEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemHyperLinkEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemPictureEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemSpinEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemDateEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemDateEdit1.VistaTimeProperties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(cardView)).BeginInit();
            this.SuspendLayout();
            // 
            // gridControl
            // 
            this.gridControl.AllowDrop = true;
            this.gridControl.AllowRestoreSelectionAndFocusedRow = DevExpress.Utils.DefaultBoolean.True;
            this.gridControl.Cursor = System.Windows.Forms.Cursors.Default;
            this.gridControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gridControl.Location = new System.Drawing.Point(0, 0);
            this.gridControl.MainView = this.gridView;
            this.gridControl.Name = "gridControl";
            this.gridControl.RepositoryItems.AddRange(new DevExpress.XtraEditors.Repository.RepositoryItem[] {
            this.repositoryItemImageComboBox1,
            this.repositoryItemMemoExEdit1,
            this.repositoryItemHyperLinkEdit1,
            this.repositoryItemPictureEdit1,
            this.repositoryItemImageEdit1,
            this.repositoryItemSpinEdit1,
            this.repositoryItemDateEdit1});
            this.gridControl.Size = new System.Drawing.Size(536, 378);
            this.gridControl.TabIndex = 9;
            this.gridControl.ViewCollection.AddRange(new DevExpress.XtraGrid.Views.Base.BaseView[] {
            this.gridView,
            cardView});
            this.gridControl.DragDrop += new System.Windows.Forms.DragEventHandler(this.gridControl_DragDrop);
            this.gridControl.DragEnter += new System.Windows.Forms.DragEventHandler(this.gridControl_DragEnter);
            this.gridControl.MouseDown += new System.Windows.Forms.MouseEventHandler(gridControl_MouseDown);
            this.gridControl.MouseMove += new System.Windows.Forms.MouseEventHandler(gridControl_MouseMove);
            // 
            // gridView
            // 
            this.gridView.Columns.AddRange(new DevExpress.XtraGrid.Columns.GridColumn[] {
            this.gvName,
            this.gvTimeLength,
            this.gvImage});
            this.gridView.FocusRectStyle = DevExpress.XtraGrid.Views.Grid.DrawFocusRectStyle.RowFocus;
            this.gridView.GridControl = this.gridControl;
            this.gridView.GroupSummary.AddRange(new DevExpress.XtraGrid.GridSummaryItem[] {
            new DevExpress.XtraGrid.GridGroupSummaryItem(DevExpress.Data.SummaryItemType.Count, "OrderID", null, "")});
            this.gridView.Name = "gridView";
            this.gridView.OptionsBehavior.AllowAddRows = DevExpress.Utils.DefaultBoolean.False;
            this.gridView.OptionsBehavior.AllowDeleteRows = DevExpress.Utils.DefaultBoolean.False;
            this.gridView.OptionsCustomization.AllowColumnMoving = false;
            this.gridView.OptionsCustomization.AllowColumnResizing = false;
            this.gridView.OptionsCustomization.AllowFilter = false;
            this.gridView.OptionsCustomization.AllowGroup = false;
            this.gridView.OptionsCustomization.AllowQuickHideColumns = false;
            this.gridView.OptionsCustomization.AllowSort = false;
            this.gridView.OptionsMenu.EnableColumnMenu = false;
            this.gridView.OptionsMenu.EnableFooterMenu = false;
            this.gridView.OptionsMenu.EnableGroupPanelMenu = false;
            this.gridView.OptionsMenu.ShowGroupSortSummaryItems = false;
            this.gridView.OptionsSelection.MultiSelect = true;
            this.gridView.OptionsBehavior.Editable = false;
            this.gridView.OptionsSelection.MultiSelectMode = DevExpress.XtraGrid.Views.Grid.GridMultiSelectMode.CellSelect;
            gridView.FocusedColumnChanged += new DevExpress.XtraGrid.Views.Base.FocusedColumnChangedEventHandler(gridView_FocusedColumnChanged);
            this.gridView.ShowButtonMode = DevExpress.XtraGrid.Views.Base.ShowButtonModeEnum.Default;
            gridView.FocusedRowChanged += new DevExpress.XtraGrid.Views.Base.FocusedRowChangedEventHandler(gridView_FocusedRowChanged);
            // 
            // gvName
            // 
            this.gvName.Caption = "Name";
            this.gvName.FieldName = "Name";
            this.gvName.Name = "gvName";
            this.gvName.Visible = true;
            this.gvName.VisibleIndex = 0;
            // 
            // gvTimeLength
            // 
            this.gvTimeLength.Caption = "Length";
            this.gvTimeLength.FieldName = "LengthText";
            this.gvTimeLength.Name = "gvTimeLength";
            this.gvTimeLength.Visible = true;
            this.gvTimeLength.VisibleIndex = 1;
            // 
            // gvImage
            // 
            this.gvImage.Caption = "Image";
            this.gvImage.ColumnEdit = this.repositoryItemImageEdit1;
            this.gvImage.FieldName = "Image";
            this.gvImage.Name = "gvImage";
            this.gvImage.Visible = true;
            this.gvImage.VisibleIndex = 2;
            // 
            // repositoryItemImageEdit1
            // 
            this.repositoryItemImageEdit1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.repositoryItemImageEdit1.Name = "repositoryItemImageEdit1";
            this.repositoryItemImageEdit1.PopupFormSize = new System.Drawing.Size(280, 200);
            // 
            // repositoryItemImageComboBox1
            // 
            this.repositoryItemImageComboBox1.Appearance.ForeColor = System.Drawing.Color.Blue;
            this.repositoryItemImageComboBox1.Appearance.Options.UseForeColor = true;
            this.repositoryItemImageComboBox1.AutoHeight = false;
            this.repositoryItemImageComboBox1.Items.AddRange(new DevExpress.XtraEditors.Controls.ImageComboBoxItem[] {
            new DevExpress.XtraEditors.Controls.ImageComboBoxItem("              2", 32, 2),
            new DevExpress.XtraEditors.Controls.ImageComboBoxItem("              4", 44, 0),
            new DevExpress.XtraEditors.Controls.ImageComboBoxItem("              5", 42, 1)});
            this.repositoryItemImageComboBox1.Name = "repositoryItemImageComboBox1";
            this.repositoryItemImageComboBox1.ReadOnly = true;
            this.repositoryItemImageComboBox1.ShowDropDown = DevExpress.XtraEditors.Controls.ShowDropDown.Never;
            // 
            // repositoryItemMemoExEdit1
            // 
            this.repositoryItemMemoExEdit1.AutoHeight = false;
            this.repositoryItemMemoExEdit1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.repositoryItemMemoExEdit1.Name = "repositoryItemMemoExEdit1";
            this.repositoryItemMemoExEdit1.PopupFormSize = new System.Drawing.Size(350, 150);
            // 
            // repositoryItemHyperLinkEdit1
            // 
            this.repositoryItemHyperLinkEdit1.AutoHeight = false;
            this.repositoryItemHyperLinkEdit1.Name = "repositoryItemHyperLinkEdit1";
            // 
            // repositoryItemPictureEdit1
            // 
            this.repositoryItemPictureEdit1.Appearance.BackColor = System.Drawing.Color.Black;
            this.repositoryItemPictureEdit1.Appearance.BackColor2 = System.Drawing.Color.White;
            this.repositoryItemPictureEdit1.Appearance.Options.UseBackColor = true;
            this.repositoryItemPictureEdit1.CustomHeight = 30;
            this.repositoryItemPictureEdit1.Name = "repositoryItemPictureEdit1";
            this.repositoryItemPictureEdit1.PictureStoreMode = DevExpress.XtraEditors.Controls.PictureStoreMode.Image;
            this.repositoryItemPictureEdit1.SizeMode = DevExpress.XtraEditors.Controls.PictureSizeMode.Zoom;
            // 
            // repositoryItemSpinEdit1
            // 
            this.repositoryItemSpinEdit1.AutoHeight = false;
            this.repositoryItemSpinEdit1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.repositoryItemSpinEdit1.Mask.EditMask = "\\$###########,0.00";
            this.repositoryItemSpinEdit1.Name = "repositoryItemSpinEdit1";
            // 
            // repositoryItemDateEdit1
            // 
            this.repositoryItemDateEdit1.AutoHeight = false;
            this.repositoryItemDateEdit1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.repositoryItemDateEdit1.Name = "repositoryItemDateEdit1";
            this.repositoryItemDateEdit1.ShowWeekNumbers = true;
            this.repositoryItemDateEdit1.VistaTimeProperties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            // 
            // cardView
            // 
            cardView.Appearance.CardCaption.BackColor = System.Drawing.Color.Transparent;
            cardView.Appearance.CardCaption.Options.UseBackColor = true;
            cardView.Appearance.CardCaption.Options.UseTextOptions = true;
            cardView.Appearance.CardCaption.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            cardView.CardCaptionFormat = "{1}";
            cardView.CardWidth = 60;
            cardView.Columns.AddRange(new DevExpress.XtraGrid.Columns.GridColumn[] {
            this.cvName,
            this.cvImage,
            this.cvTimeLength});
            cardView.DetailHeight = 50;
            cardView.FocusedCardTopFieldIndex = 0;
            styleFormatCondition1.Appearance.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Strikeout);
            styleFormatCondition1.Appearance.ForeColor = System.Drawing.SystemColors.ControlDark;
            styleFormatCondition1.Appearance.Options.UseFont = true;
            styleFormatCondition1.Appearance.Options.UseForeColor = true;
            styleFormatCondition1.ApplyToRow = true;
            styleFormatCondition1.Condition = DevExpress.XtraGrid.FormatConditionEnum.Equal;
            styleFormatCondition1.Value1 = false;
            cardView.FormatConditions.AddRange(new DevExpress.XtraGrid.StyleFormatCondition[] {
            styleFormatCondition1});
            cardView.GridControl = this.gridControl;
            cardView.Name = "cardView";
            cardView.OptionsBehavior.AllowAddRows = DevExpress.Utils.DefaultBoolean.False;
            cardView.OptionsBehavior.AllowDeleteRows = DevExpress.Utils.DefaultBoolean.False;
            cardView.OptionsBehavior.Editable = false;
            cardView.OptionsBehavior.FieldAutoHeight = true;
            cardView.OptionsBehavior.FocusLeaveOnTab = true;
            cardView.OptionsPrint.AutoHorzWidth = true;
            cardView.OptionsSelection.MultiSelect = true;
            cardView.OptionsView.ShowCardExpandButton = false;
            cardView.OptionsView.ShowEmptyFields = false;
            cardView.OptionsView.ShowFieldCaptions = false;
            cardView.OptionsView.ShowLines = false;
            cardView.OptionsView.ShowQuickCustomizeButton = false;
            cardView.ShowButtonMode = DevExpress.XtraGrid.Views.Base.ShowButtonModeEnum.ShowOnlyInEditor;
            cardView.VertScrollVisibility = DevExpress.XtraGrid.Views.Base.ScrollVisibility.Auto;
            cardView.SelectionChanged += new DevExpress.Data.SelectionChangedEventHandler(cardView_SelectionChanged);
            // 
            // cvName
            // 
            this.cvName.AppearanceCell.Options.UseTextOptions = true;
            this.cvName.AppearanceCell.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.cvName.Caption = "Name";
            this.cvName.FieldName = "Name";
            this.cvName.Name = "cvName";
            // 
            // cvImage
            // 
            this.cvImage.Caption = "Image";
            this.cvImage.ColumnEdit = this.repositoryItemPictureEdit1;
            this.cvImage.FieldName = "Image";
            this.cvImage.Name = "cvImage";
            this.cvImage.Visible = true;
            this.cvImage.VisibleIndex = 0;
            // 
            // cvTimeLength
            // 
            this.cvTimeLength.AppearanceCell.Options.UseTextOptions = true;
            this.cvTimeLength.AppearanceCell.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.cvTimeLength.Caption = "Time Length";
            this.cvTimeLength.DisplayFormat.FormatString = "D";
            this.cvTimeLength.DisplayFormat.FormatType = DevExpress.Utils.FormatType.DateTime;
            this.cvTimeLength.FieldName = "LengthText";
            this.cvTimeLength.Name = "cvTimeLength";
            this.cvTimeLength.Visible = true;
            this.cvTimeLength.VisibleIndex = 1;
            // 
            // MessageGridControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.gridControl);
            this.Name = "MessageGridControl";
            this.Size = new System.Drawing.Size(536, 378);
            this.Load += new System.EventHandler(MessageGridControl_Load);
            ((System.ComponentModel.ISupportInitialize)(this.gridControl)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemImageEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemImageComboBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemMemoExEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemHyperLinkEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemPictureEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemSpinEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemDateEdit1.VistaTimeProperties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemDateEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(cardView)).EndInit();
            this.ResumeLayout(false);

        }


        #endregion
        DevExpress.XtraGrid.Views.Card.CardView cardView;
        private DevExpress.XtraGrid.Views.Grid.GridView gridView;
        private DevExpress.XtraGrid.GridControl gridControl;
        private DevExpress.XtraEditors.Repository.RepositoryItemPictureEdit repositoryItemPictureEdit1;
        private DevExpress.XtraEditors.Repository.RepositoryItemImageEdit repositoryItemImageEdit1;
        private DevExpress.XtraEditors.Repository.RepositoryItemSpinEdit repositoryItemSpinEdit1;
        private DevExpress.XtraEditors.Repository.RepositoryItemDateEdit repositoryItemDateEdit1;
        private DevExpress.XtraEditors.Repository.RepositoryItemImageComboBox repositoryItemImageComboBox1;
        private DevExpress.XtraEditors.Repository.RepositoryItemMemoExEdit repositoryItemMemoExEdit1;
        private DevExpress.XtraEditors.Repository.RepositoryItemHyperLinkEdit repositoryItemHyperLinkEdit1;
        private DevExpress.XtraGrid.Columns.GridColumn cvImage;
        private DevExpress.XtraGrid.Columns.GridColumn gvName;
        private DevExpress.XtraGrid.Columns.GridColumn gvTimeLength;
        private DevExpress.XtraGrid.Columns.GridColumn gvImage;
        private DevExpress.XtraGrid.Columns.GridColumn cvName;
        private DevExpress.XtraGrid.Columns.GridColumn cvTimeLength;

    }
}
