namespace ProWrite.UI.Controls.Live.Sessions
{
    partial class HotButtonControl
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
            try
            {
                if (disposing && (components != null))
                {
                    components.Dispose();
                }
                base.Dispose(disposing);
            }
            catch { }
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.hotButtonPanelControl = new ProWrite.UI.Controls.Live.Sessions.HotButtonPanelControl();
            this.barManager = new DevExpress.XtraBars.BarManager(this.components);
            this.barDockControlTop = new DevExpress.XtraBars.BarDockControl();
            this.barDockControlBottom = new DevExpress.XtraBars.BarDockControl();
            this.barDockControlLeft = new DevExpress.XtraBars.BarDockControl();
            this.barDockControlRight = new DevExpress.XtraBars.BarDockControl();
            this.itmLockButton = new DevExpress.XtraBars.BarButtonItem();
            this.itmUnLockButton = new DevExpress.XtraBars.BarButtonItem();
            this.itmAddButton = new DevExpress.XtraBars.BarButtonItem();
            this.itmRemoveButton = new DevExpress.XtraBars.BarButtonItem();
            this.itmEditButton = new DevExpress.XtraBars.BarButtonItem();
            this.panelControl3 = new DevExpress.XtraEditors.PanelControl();
            this.panelControl1 = new DevExpress.XtraEditors.PanelControl();
            this.panelControl2 = new DevExpress.XtraEditors.PanelControl();
            this.btnScale = new DevExpress.XtraEditors.SimpleButton();
            this.scoBar = new DevExpress.XtraEditors.VScrollBar();
            this.labelControl1 = new DevExpress.XtraEditors.LabelControl();
            this.popupMenu = new DevExpress.XtraBars.PopupMenu(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.barManager)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl3)).BeginInit();
            this.panelControl3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl1)).BeginInit();
            this.panelControl1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl2)).BeginInit();
            this.panelControl2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.popupMenu)).BeginInit();
            this.SuspendLayout();
            // 
            // hotButtonPanelControl
            // 
            this.hotButtonPanelControl.AutoSize = true;
            this.hotButtonPanelControl.BackColor = System.Drawing.Color.Transparent;
            this.hotButtonPanelControl.Location = new System.Drawing.Point(3, 3);
            this.hotButtonPanelControl.Lock = true;
            this.hotButtonPanelControl.Name = "hotButtonPanelControl";
            this.hotButtonPanelControl.Size = new System.Drawing.Size(415, 1099);
            this.hotButtonPanelControl.TabIndex = 0;
            // 
            // barManager
            // 
            this.barManager.AllowCustomization = false;
            this.barManager.AllowMoveBarOnToolbar = false;
            this.barManager.AllowQuickCustomization = false;
            this.barManager.AllowShowToolbarsPopup = false;
            this.barManager.DockControls.Add(this.barDockControlTop);
            this.barManager.DockControls.Add(this.barDockControlBottom);
            this.barManager.DockControls.Add(this.barDockControlLeft);
            this.barManager.DockControls.Add(this.barDockControlRight);
            this.barManager.Form = this;
            this.barManager.Items.AddRange(new DevExpress.XtraBars.BarItem[] {
            this.itmLockButton,
            this.itmUnLockButton,
            this.itmAddButton,
            this.itmRemoveButton,
            this.itmEditButton});
            this.barManager.MaxItemId = 5;
            // 
            // itmLockButton
            // 
            this.itmLockButton.Caption = "&Lock";
            this.itmLockButton.Id = 0;
            this.itmLockButton.Name = "itmLockButton";
            this.itmLockButton.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.itmLockButton_ItemClick);
            // 
            // itmUnLockButton
            // 
            this.itmUnLockButton.Caption = "&UnLock";
            this.itmUnLockButton.Id = 1;
            this.itmUnLockButton.Name = "itmUnLockButton";
            this.itmUnLockButton.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.itmUnLockButton_ItemClick);
            // 
            // itmAddButton
            // 
            this.itmAddButton.Caption = "&Add Button";
            this.itmAddButton.Id = 2;
            this.itmAddButton.Name = "itmAddButton";
            this.itmAddButton.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.itmAddButton_ItemClick);
            // 
            // itmRemoveButton
            // 
            this.itmRemoveButton.Caption = "&Remove Button";
            this.itmRemoveButton.Id = 3;
            this.itmRemoveButton.Name = "itmRemoveButton";
            this.itmRemoveButton.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.itmRemoveButton_ItemClick);
            // 
            // itmEditButton
            // 
            this.itmEditButton.Caption = "&Edit Button";
            this.itmEditButton.Id = 4;
            this.itmEditButton.Name = "itmEditButton";
            this.itmEditButton.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.itmEditButton_ItemClick);
            // 
            // panelControl3
            // 
            this.panelControl3.Appearance.BackColor = System.Drawing.Color.Transparent;
            this.panelControl3.Appearance.Options.UseBackColor = true;
            this.panelControl3.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
            this.panelControl3.Controls.Add(this.hotButtonPanelControl);
            this.panelControl3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panelControl3.Location = new System.Drawing.Point(0, 0);
            this.panelControl3.Name = "panelControl3";
            this.panelControl3.Size = new System.Drawing.Size(430, 267);
            this.panelControl3.TabIndex = 2;
            // 
            // panelControl1
            // 
            this.panelControl1.AllowDrop = true;
            this.panelControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.panelControl1.Appearance.BackColor = System.Drawing.Color.Transparent;
            this.panelControl1.Appearance.Options.UseBackColor = true;
            this.panelControl1.BorderStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
            this.panelControl1.Controls.Add(this.panelControl3);
            this.panelControl1.Controls.Add(this.panelControl2);
            this.panelControl1.Location = new System.Drawing.Point(9, 39);
            this.panelControl1.Name = "panelControl1";
            this.panelControl1.Size = new System.Drawing.Size(455, 267);
            this.panelControl1.TabIndex = 6;
            // 
            // panelControl2
            // 
            this.panelControl2.Appearance.ForeColor = System.Drawing.Color.Transparent;
            this.panelControl2.Appearance.Options.UseForeColor = true;
            this.panelControl2.Controls.Add(this.btnScale);
            this.panelControl2.Controls.Add(this.scoBar);
            this.panelControl2.Dock = System.Windows.Forms.DockStyle.Right;
            this.panelControl2.Location = new System.Drawing.Point(430, 0);
            this.panelControl2.Name = "panelControl2";
            this.panelControl2.Size = new System.Drawing.Size(25, 267);
            this.panelControl2.TabIndex = 1;
            // 
            // btnScale
            // 
            this.btnScale.ButtonStyle = DevExpress.XtraEditors.Controls.BorderStyles.NoBorder;
            this.btnScale.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.btnScale.Location = new System.Drawing.Point(2, 242);
            this.btnScale.Name = "btnScale";
            this.btnScale.Size = new System.Drawing.Size(21, 23);
            this.btnScale.TabIndex = 1;
            // 
            // scoBar
            // 
            this.scoBar.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.scoBar.Location = new System.Drawing.Point(2, 2);
            this.scoBar.Name = "scoBar";
            this.scoBar.Size = new System.Drawing.Size(21, 228);
            this.scoBar.TabIndex = 0;
            this.scoBar.Scroll += new System.Windows.Forms.ScrollEventHandler(this.scoBar_Scroll);
            // 
            // labelControl1
            // 
            this.labelControl1.Appearance.Font = new System.Drawing.Font("Arial", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.World);
            this.labelControl1.Appearance.Options.UseFont = true;
            this.labelControl1.Location = new System.Drawing.Point(15, 15);
            this.labelControl1.Name = "labelControl1";
            this.labelControl1.Size = new System.Drawing.Size(110, 18);
            this.labelControl1.TabIndex = 4;
            this.labelControl1.Text = "HOT BUTTONS";
            // 
            // popupMenu
            // 
            this.popupMenu.LinksPersistInfo.AddRange(new DevExpress.XtraBars.LinkPersistInfo[] {
            new DevExpress.XtraBars.LinkPersistInfo(this.itmLockButton),
            new DevExpress.XtraBars.LinkPersistInfo(this.itmUnLockButton),
            new DevExpress.XtraBars.LinkPersistInfo(this.itmAddButton),
            new DevExpress.XtraBars.LinkPersistInfo(this.itmRemoveButton),
            new DevExpress.XtraBars.LinkPersistInfo(this.itmEditButton)});
            this.popupMenu.Manager = this.barManager;
            this.popupMenu.Name = "popupMenu";
            // 
            // HotButtonControl
            // 
            this.Appearance.BackColor = System.Drawing.Color.Transparent;
            this.Appearance.Options.UseBackColor = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.panelControl1);
            this.Controls.Add(this.labelControl1);
            this.Controls.Add(this.barDockControlLeft);
            this.Controls.Add(this.barDockControlRight);
            this.Controls.Add(this.barDockControlBottom);
            this.Controls.Add(this.barDockControlTop);
            this.Name = "HotButtonControl";
            this.Size = new System.Drawing.Size(473, 312);
            ((System.ComponentModel.ISupportInitialize)(this.barManager)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl3)).EndInit();
            this.panelControl3.ResumeLayout(false);
            this.panelControl3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl1)).EndInit();
            this.panelControl1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.panelControl2)).EndInit();
            this.panelControl2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.popupMenu)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private HotButtonPanelControl hotButtonPanelControl;
        private DevExpress.XtraBars.BarManager barManager;
        private DevExpress.XtraBars.BarDockControl barDockControlTop;
        private DevExpress.XtraBars.BarDockControl barDockControlBottom;
        private DevExpress.XtraBars.BarDockControl barDockControlLeft;
        private DevExpress.XtraBars.BarDockControl barDockControlRight;
        private DevExpress.XtraBars.BarButtonItem itmLockButton;
        private DevExpress.XtraBars.BarButtonItem itmUnLockButton;
        private DevExpress.XtraBars.BarButtonItem itmAddButton;
        private DevExpress.XtraBars.BarButtonItem itmRemoveButton;
        private DevExpress.XtraBars.BarButtonItem itmEditButton;
        private DevExpress.XtraEditors.PanelControl panelControl3;
        private DevExpress.XtraEditors.PanelControl panelControl1;
        private DevExpress.XtraEditors.PanelControl panelControl2;
        private DevExpress.XtraEditors.SimpleButton btnScale;
        private DevExpress.XtraEditors.VScrollBar scoBar;
        private DevExpress.XtraEditors.LabelControl labelControl1;
        private DevExpress.XtraBars.PopupMenu popupMenu;
    }
}
