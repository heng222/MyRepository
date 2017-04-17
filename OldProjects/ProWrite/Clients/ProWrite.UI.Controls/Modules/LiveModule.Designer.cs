namespace ProWrite.UI.Controls.Modules
{
    partial class LiveModule
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
            this.dockManager1 = new DevExpress.XtraBars.Docking.DockManager(this.components);
            this.dockPanelLibrary = new DevExpress.XtraBars.Docking.DockPanel();
            this.categroiesControl = new ProWrite.UI.Controls.Live.Sessions.SessionSetupControl();
            this.tabCategories = new DevExpress.XtraTab.XtraTabControl();
            this.messageQueue = new ProWrite.UI.Controls.Live.Sessions.MessageQueue();
            this.dockPanelLibrary_Container = new DevExpress.XtraBars.Docking.ControlContainer();
            ((System.ComponentModel.ISupportInitialize)(this.dockManager1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tabCategories)).BeginInit();
            this.dockPanelLibrary.SuspendLayout();
            this.tabCategories.SuspendLayout();
            this.SuspendLayout();
            // 
            // dockManager1
            // 
            this.dockManager1.Form = this;
            this.dockManager1.RootPanels.AddRange(new DevExpress.XtraBars.Docking.DockPanel[] {
            this.dockPanelLibrary});
            this.dockManager1.TopZIndexControls.AddRange(new string[] {
            "DevExpress.XtraBars.BarDockControl",
            "System.Windows.Forms.StatusBar",
            "DevExpress.XtraBars.Ribbon.RibbonStatusBar",
            "DevExpress.XtraBars.Ribbon.RibbonControl"});

            // 
            // tabCategories
            // 
            //this.tabCategories.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            //            | System.Windows.Forms.AnchorStyles.Left)
            //            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabCategories.Dock = System.Windows.Forms.DockStyle.Left;
            this.tabCategories.HeaderLocation = DevExpress.XtraTab.TabHeaderLocation.Top;
            this.tabCategories.Location = new System.Drawing.Point(10, 0);
            this.tabCategories.Name = "tabCategories";
            this.tabCategories.Size = new System.Drawing.Size(450, 400);
            this.tabCategories.TabIndex = 0;
            // 
            // dockPanelLibrary
            // 
            this.dockPanelLibrary.Controls.Add(this.dockPanelLibrary_Container);
            this.dockPanelLibrary.Dock = DevExpress.XtraBars.Docking.DockingStyle.Right;
            this.dockPanelLibrary.ID = new System.Guid("989dff65-ba01-4ea1-902c-cf1453333fa7");
            this.dockPanelLibrary.Location = new System.Drawing.Point(0, 0);
            this.dockPanelLibrary.Name = "dockPanelLibrary";
            this.dockPanelLibrary.Size = new System.Drawing.Size(200, 451);
            this.dockPanelLibrary.Text = "Library";
            // 
            // categroiesControl
            // 
            this.categroiesControl.Dock = System.Windows.Forms.DockStyle.None;
            //this.categroiesControl.IsSupportGlobalization = false;
            this.categroiesControl.Location = new System.Drawing.Point(0, 0);
            this.categroiesControl.Name = "dashboardTree1";
            this.categroiesControl.Size = new System.Drawing.Size(500, 750);
            this.categroiesControl.TabIndex = 18;
            // 
            // categroiesControl
            // 
            this.messageQueue.Dock = System.Windows.Forms.DockStyle.Right ;
            //this.categroiesControl.IsSupportGlobalization = false;
            this.messageQueue.Location = new System.Drawing.Point(505, 0);
            this.messageQueue.Name = "dashboardTree1";
            this.messageQueue.Size = new System.Drawing.Size(400, 350);
            this.messageQueue.TabIndex = 18;
            // 
            // dockPanelLibrary_Container
            // 
            this.dockPanelLibrary_Container.Location = new System.Drawing.Point(3, 25);
            this.dockPanelLibrary_Container.Name = "dockPanelLibrary_Container";
            this.dockPanelLibrary_Container.Size = new System.Drawing.Size(194, 423);
            this.dockPanelLibrary_Container.TabIndex = 0;
            // 
            // LiveModule
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.dockPanelLibrary);
            //this.Controls.Add(this.categroiesControl);
            this.Controls.Add(this.messageQueue);
            this.Controls.Add(tabCategories);
            this.Name = "LiveModule";
            this.Size = new System.Drawing.Size(602, 451);
            ((System.ComponentModel.ISupportInitialize)(this.dockManager1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tabCategories)).EndInit();
            this.dockPanelLibrary.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        ProWrite.UI.Controls.Live.Sessions.SessionSetupControl categroiesControl;
        ProWrite.UI.Controls.Live.Sessions.MessageQueue messageQueue;
        private DevExpress.XtraBars.Docking.DockManager dockManager1;
        private DevExpress.XtraBars.Docking.DockPanel dockPanelLibrary;
        private DevExpress.XtraBars.Docking.ControlContainer dockPanelLibrary_Container;
        private DevExpress.XtraTab.XtraTabControl tabCategories;
        
    }
}
