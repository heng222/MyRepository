namespace ProWrite.UI.Controls.Live.Sessions
{
    partial class CategoriesControl
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
            this.btnNew = new DevExpress.XtraEditors.SimpleButton();
            this.cmbView = new DevExpress.XtraEditors.ComboBoxEdit();
            this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
            this.labelControl2 = new DevExpress.XtraEditors.LabelControl();
            this.tabPageControl = new DevExpress.XtraTab.XtraTabControl();
            this.mnuControl = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.mnuItemClose = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuItemSave = new System.Windows.Forms.ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)(this.cmbView.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tabPageControl)).BeginInit();
            this.mnuControl.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnNew
            // 
            this.btnNew.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnNew.Location = new System.Drawing.Point(0, 347);
            this.btnNew.Name = "btnNew";
            this.btnNew.Size = new System.Drawing.Size(51, 23);
            this.btnNew.TabIndex = 9;
            this.btnNew.Text = "&New";
            this.btnNew.ToolTip = "Create a new category";
            this.btnNew.Click += new System.EventHandler(this.btnNew_Click);
            // 
            // cmbView
            // 
            this.cmbView.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cmbView.EditValue = "List";
            this.cmbView.Location = new System.Drawing.Point(116, 349);
            this.cmbView.Name = "cmbView";
            this.cmbView.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.cmbView.Properties.Items.AddRange(new object[] {
            "List",
            "Thumbnails"});
            this.cmbView.Size = new System.Drawing.Size(106, 20);
            this.cmbView.TabIndex = 14;
            this.cmbView.SelectedIndexChanged += new System.EventHandler(this.cmbView_SelectedIndexChanged);
            // 
            // labelControl1
            // 
            this.labelControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.labelControl1.Location = new System.Drawing.Point(83, 352);
            this.labelControl1.Name = "labelControl1";
            this.labelControl1.Size = new System.Drawing.Size(26, 13);
            this.labelControl1.TabIndex = 13;
            this.labelControl1.Text = "View:";
            // 
            // labelControl2
            // 
            this.labelControl2.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.labelControl2.Location = new System.Drawing.Point(51, 9);
            this.labelControl2.Name = "labelControl2";
            this.labelControl2.Size = new System.Drawing.Size(120, 13);
            this.labelControl2.TabIndex = 15;
            this.labelControl2.Text = "Session Open Categories";
            // 
            // tabPageControl
            // 
            this.tabPageControl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tabPageControl.ClosePageButtonShowMode = DevExpress.XtraTab.ClosePageButtonShowMode.InActiveTabPageHeader;
            this.tabPageControl.Location = new System.Drawing.Point(0, 28);
            this.tabPageControl.MultiLine = DevExpress.Utils.DefaultBoolean.True;
            this.tabPageControl.Name = "tabPageControl";
            this.tabPageControl.Size = new System.Drawing.Size(222, 318);
            this.tabPageControl.TabIndex = 16;
            this.tabPageControl.SelectedPageChanged += new DevExpress.XtraTab.TabPageChangedEventHandler(this.tabPageControl_SelectedPageChanged);
            this.tabPageControl.CloseButtonClick += new System.EventHandler(this.tabPageControl_CloseButtonClick);
            // 
            // mnuControl
            // 
            this.mnuControl.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuItemClose,
            this.mnuItemSave});
            this.mnuControl.Name = "mnuControl";
            this.mnuControl.Size = new System.Drawing.Size(120, 48);
            // 
            // mnuItemClose
            // 
            this.mnuItemClose.Name = "mnuItemClose";
            this.mnuItemClose.Size = new System.Drawing.Size(119, 22);
            this.mnuItemClose.Text = "Close(&C)";
            // 
            // mnuItemSave
            // 
            this.mnuItemSave.Name = "mnuItemSave";
            this.mnuItemSave.Size = new System.Drawing.Size(119, 22);
            this.mnuItemSave.Text = "Save(&S)";
            // 
            // CategoriesControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tabPageControl);
            this.Controls.Add(this.labelControl2);
            this.Controls.Add(this.cmbView);
            this.Controls.Add(this.labelControl1);
            this.Controls.Add(this.btnNew);
            this.Name = "CategoriesControl";
            this.Size = new System.Drawing.Size(222, 370);
            ((System.ComponentModel.ISupportInitialize)(this.cmbView.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tabPageControl)).EndInit();
            this.mnuControl.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private DevExpress.XtraEditors.SimpleButton btnNew;
        private DevExpress.XtraEditors.ComboBoxEdit cmbView;
        private DevExpress.XtraEditors.LabelControl labelControl1;
        private DevExpress.XtraEditors.LabelControl labelControl2;
        private DevExpress.XtraTab.XtraTabControl tabPageControl;
        private System.Windows.Forms.ContextMenuStrip mnuControl;
        private System.Windows.Forms.ToolStripMenuItem mnuItemClose;
        private System.Windows.Forms.ToolStripMenuItem mnuItemSave;

    }
}
