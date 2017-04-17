using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls.Modules
{
    partial class DashboardModule
    {
        /// <summary> 
        /// Necessary designer variable
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clear up all resource being used
        /// /// </summary>
        /// <param name="disposing">If release trusteeship resource,it is true；or else false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Groupware generator's code

        /// <summary> 
        /// Method that generator support
        /// Use code editor to modify content of the method
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            DataGate.Log.Debug("resources Init start.");
            var resources = new System.ComponentModel.ComponentResourceManager(typeof(DashboardModule));
            DataGate.Log.Debug("resources Init start.");
            this.imageList = new System.Windows.Forms.ImageList(this.components);
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            DataGate.Log.Debug("DashboardTree Init start.");
            this.dashboardTree1 = new ProWrite.UI.Controls.Dashboard.DashboardTree();
            DataGate.Log.Debug("DashboardTree Init end.");
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.dockManager1 = new DevExpress.XtraBars.Docking.DockManager(this.components);
            this.dockPanelSignStatus = new DevExpress.XtraBars.Docking.DockPanel();
            this.dockPanel3_Container = new DevExpress.XtraBars.Docking.ControlContainer();
            this.dockPanelSignStorageIndicator = new DevExpress.XtraBars.Docking.DockPanel();
            this.dockPanel4_Container = new DevExpress.XtraBars.Docking.ControlContainer();
            this.panelContainer1 = new DevExpress.XtraBars.Docking.DockPanel();
            this.dockPanelSignImage = new DevExpress.XtraBars.Docking.DockPanel();
            this.dockPanel1_Container = new DevExpress.XtraBars.Docking.ControlContainer();
            this.dockPanelCurrentClip = new DevExpress.XtraBars.Docking.DockPanel();
            this.dockPanel2_Container = new DevExpress.XtraBars.Docking.ControlContainer();
            ((System.ComponentModel.ISupportInitialize)(this.dockManager1)).BeginInit();
            this.dockPanelSignStatus.SuspendLayout();
            this.dockPanelSignStorageIndicator.SuspendLayout();
            this.panelContainer1.SuspendLayout();
            this.dockPanelSignImage.SuspendLayout();
            this.dockPanelCurrentClip.SuspendLayout();
            this.SuspendLayout();
            DataGate.Log.Debug("SuspendLayout End.");
            // 
            // imageList
            // 
            DataGate.Log.Debug("ImageListStreamer Start.");
            this.imageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList.ImageStream")));
            this.imageList.TransparentColor = System.Drawing.Color.Magenta;
            this.imageList.Images.SetKeyName(0, "");
            this.imageList.Images.SetKeyName(1, "");
            this.imageList.Images.SetKeyName(2, "");
            this.imageList.Images.SetKeyName(3, "");
            this.imageList.Images.SetKeyName(4, "");
            DataGate.Log.Debug("ImageListStreamer End.");
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "dustbin1.png");
            this.imageList1.Images.SetKeyName(1, "dustbin2.png");
            // 
            // dashboardTree1
            // 
            this.dashboardTree1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dashboardTree1.IsSupportGlobalization = false;
            this.dashboardTree1.Location = new System.Drawing.Point(200, 0);
            this.dashboardTree1.Name = "dashboardTree1";
            this.dashboardTree1.Size = new System.Drawing.Size(392, 463);
            this.dashboardTree1.TabIndex = 18;
            // 
            // openFileDialog
            // 
            this.openFileDialog.Filter = "Jpeg File(*.jpg,*.jpeg)|*.jpg;*.jpeg|Gif File(*.gif)|*.gif|Png File(*.png)|*.png|Bmp File(*.bmp)" +
                "|*.bmp|All File(*.*)|*.*";
            this.openFileDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog_FileOk);
            // 
            // dockManager1
            // 
            DataGate.Log.Debug("dockmanger start");
            this.dockManager1.Form = this;
            this.dockManager1.HiddenPanels.AddRange(new DevExpress.XtraBars.Docking.DockPanel[] {
            this.dockPanelSignStatus,
            this.dockPanelSignStorageIndicator});
            this.dockManager1.RootPanels.AddRange(new DevExpress.XtraBars.Docking.DockPanel[] {
            this.panelContainer1});
            this.dockManager1.TopZIndexControls.AddRange(new string[] {
            "DevExpress.XtraBars.BarDockControl",
            "System.Windows.Forms.StatusBar",
            "DevExpress.XtraBars.Ribbon.RibbonStatusBar",
            "DevExpress.XtraBars.Ribbon.RibbonControl"});
            DataGate.Log.Debug("dockmanger End");
            // 
            // dockPanelSignStatus
            // 
            this.dockPanelSignStatus.Controls.Add(this.dockPanel3_Container);
            this.dockPanelSignStatus.Dock = DevExpress.XtraBars.Docking.DockingStyle.Fill;
            this.dockPanelSignStatus.ID = new System.Guid("75d0924d-c70d-4e86-911a-0ae5d2b806e3");
            this.dockPanelSignStatus.Location = new System.Drawing.Point(0, 0);
            this.dockPanelSignStatus.Name = "dockPanelSignStatus";
            this.dockPanelSignStatus.Options.ShowCloseButton = false;
            this.dockPanelSignStatus.Options.ShowMaximizeButton = false;
            this.dockPanelSignStatus.SavedDock = DevExpress.XtraBars.Docking.DockingStyle.Fill;
            this.dockPanelSignStatus.SavedIndex = 0;
            this.dockPanelSignStatus.SavedParent = this.dockPanelSignStorageIndicator;
            this.dockPanelSignStatus.Size = new System.Drawing.Size(129, 231);
            this.dockPanelSignStatus.Text = "Sign Status";
            this.dockPanelSignStatus.Visibility = DevExpress.XtraBars.Docking.DockVisibility.Hidden;
            // 
            // dockPanel3_Container
            // 
            this.dockPanel3_Container.Location = new System.Drawing.Point(3, 25);
            this.dockPanel3_Container.Name = "dockPanel3_Container";
            this.dockPanel3_Container.Size = new System.Drawing.Size(123, 203);
            this.dockPanel3_Container.TabIndex = 0;
            // 
            // dockPanelSignStorageIndicator
            // 
            DataGate.Log.Debug("dockPanelSignStorageIndicator start");

            this.dockPanelSignStorageIndicator.Controls.Add(this.dockPanel4_Container);
            this.dockPanelSignStorageIndicator.Dock = DevExpress.XtraBars.Docking.DockingStyle.Right;
            this.dockPanelSignStorageIndicator.ID = new System.Guid("58bd0bf9-3146-421f-8efd-e06d66579aac");
            this.dockPanelSignStorageIndicator.Location = new System.Drawing.Point(463, 0);
            this.dockPanelSignStorageIndicator.Name = "dockPanelSignStorageIndicator";
            this.dockPanelSignStorageIndicator.Options.ShowCloseButton = false;
            this.dockPanelSignStorageIndicator.Options.ShowMaximizeButton = false;
            this.dockPanelSignStorageIndicator.SavedDock = DevExpress.XtraBars.Docking.DockingStyle.Right;
            this.dockPanelSignStorageIndicator.SavedIndex = 0;
            this.dockPanelSignStorageIndicator.Size = new System.Drawing.Size(129, 463);
            this.dockPanelSignStorageIndicator.Text = "Sign Storage Indicator";
            this.dockPanelSignStorageIndicator.Visibility = DevExpress.XtraBars.Docking.DockVisibility.Hidden;
            DataGate.Log.Debug("dockPanelSignStorageIndicator end");

            // 
            // dockPanel4_Container
            // 
            this.dockPanel4_Container.Location = new System.Drawing.Point(3, 25);
            this.dockPanel4_Container.Name = "dockPanel4_Container";
            this.dockPanel4_Container.Size = new System.Drawing.Size(123, 435);
            this.dockPanel4_Container.TabIndex = 0;
            // 
            // panelContainer1
            // 
            this.panelContainer1.Controls.Add(this.dockPanelSignImage);
            this.panelContainer1.Controls.Add(this.dockPanelCurrentClip);
            this.panelContainer1.Dock = DevExpress.XtraBars.Docking.DockingStyle.Left;
            this.panelContainer1.ID = new System.Guid("20005796-8d16-4497-9532-1e190cc3abca");
            this.panelContainer1.Location = new System.Drawing.Point(0, 0);
            this.panelContainer1.Name = "panelContainer1";
            this.panelContainer1.Size = new System.Drawing.Size(200, 463);
            this.panelContainer1.Text = "panelContainer1";
            // 
            // dockPanelSignImage
            // 
            DataGate.Log.Debug("dockPanelSignImage start");

            this.dockPanelSignImage.Controls.Add(this.dockPanel1_Container);
            this.dockPanelSignImage.Dock = DevExpress.XtraBars.Docking.DockingStyle.Fill;
            this.dockPanelSignImage.ID = new System.Guid("1abcb427-af13-4b92-a24d-82531ff892f6");
            this.dockPanelSignImage.Location = new System.Drawing.Point(0, 0);
            this.dockPanelSignImage.Name = "dockPanelSignImage";
            this.dockPanelSignImage.Options.ShowCloseButton = false;
            this.dockPanelSignImage.Options.ShowMaximizeButton = false;
            this.dockPanelSignImage.Size = new System.Drawing.Size(200, 231);
            this.dockPanelSignImage.Text = "Sign Image";
            this.dockPanelSignImage.Hint = "Sign Image";

            // 
            // dockPanel1_Container
            // 
            this.dockPanel1_Container.Location = new System.Drawing.Point(3, 25);
            this.dockPanel1_Container.Name = "dockPanel1_Container";
            this.dockPanel1_Container.Size = new System.Drawing.Size(194, 203);
            this.dockPanel1_Container.TabIndex = 0;
            // 
            // dockPanelCurrentClip
            // 
            this.dockPanelCurrentClip.Controls.Add(this.dockPanel2_Container);
            this.dockPanelCurrentClip.Dock = DevExpress.XtraBars.Docking.DockingStyle.Fill;
            this.dockPanelCurrentClip.ID = new System.Guid("339879d6-87d1-472c-83fa-3a30e2d40a1c");
            this.dockPanelCurrentClip.Location = new System.Drawing.Point(0, 231);
            this.dockPanelCurrentClip.Name = "dockPanelCurrentClip";
            this.dockPanelCurrentClip.Options.ShowCloseButton = false;
            this.dockPanelCurrentClip.Options.ShowMaximizeButton = false;
            this.dockPanelCurrentClip.Size = new System.Drawing.Size(200, 232);
            this.dockPanelCurrentClip.Text = "Current Clip";
            this.dockPanelCurrentClip.Hint = "Current Clip";
            ////this.dockPanelCurrentClip.Visibility = DevExpress.XtraBars.Docking.DockVisibility.Hidden;
            DataGate.Log.Debug("dockPanelCurrentClip end");

            // 
            // dockPanel2_Container
            // 
            this.dockPanel2_Container.Location = new System.Drawing.Point(3, 25);
            this.dockPanel2_Container.Name = "dockPanel2_Container";
            this.dockPanel2_Container.Size = new System.Drawing.Size(194, 204);
            this.dockPanel2_Container.TabIndex = 0;
            // 
            // DashboardModule
            // 
            DataGate.Log.Debug("DashboardModule start");

            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.dashboardTree1);
            this.Controls.Add(this.panelContainer1);
            this.Name = "DashboardModule";
            this.Size = new System.Drawing.Size(592, 463);
            ((System.ComponentModel.ISupportInitialize)(this.dockManager1)).EndInit();
            this.dockPanelSignStatus.ResumeLayout(false);
            this.dockPanelSignStorageIndicator.ResumeLayout(false);
            this.panelContainer1.ResumeLayout(false);
            this.dockPanelSignImage.ResumeLayout(false);
            this.dockPanelCurrentClip.ResumeLayout(false);
            this.ResumeLayout(false);
            DataGate.Log.Debug("DashboardModule End");

        }

        #endregion

        private System.Windows.Forms.ImageList imageList;
        private System.Windows.Forms.ImageList imageList1;
        private ProWrite.UI.Controls.Dashboard.DashboardTree dashboardTree1;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private DevExpress.XtraBars.Docking.DockManager dockManager1;
        private DevExpress.XtraBars.Docking.DockPanel panelContainer1;
        private DevExpress.XtraBars.Docking.DockPanel dockPanelSignImage;
        private DevExpress.XtraBars.Docking.ControlContainer dockPanel1_Container;
        private DevExpress.XtraBars.Docking.DockPanel dockPanelCurrentClip;
        private DevExpress.XtraBars.Docking.ControlContainer dockPanel2_Container;
        private DevExpress.XtraBars.Docking.DockPanel dockPanelSignStatus;
        private DevExpress.XtraBars.Docking.ControlContainer dockPanel3_Container;
        private DevExpress.XtraBars.Docking.DockPanel dockPanelSignStorageIndicator;
        private DevExpress.XtraBars.Docking.ControlContainer dockPanel4_Container;
    }
}