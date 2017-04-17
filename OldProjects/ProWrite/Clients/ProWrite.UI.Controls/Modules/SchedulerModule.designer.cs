using ProWrite.UI.Controls;

namespace ProWrite.UI.Controls.Modules
{
	partial class SchedulerModule
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
			this.schedulerStorage1 = new DevExpress.XtraScheduler.SchedulerStorage(this.components);
			this.dockManager1 = new DevExpress.XtraBars.Docking.DockManager(this.components);
			this.hideContainerRight = new DevExpress.XtraBars.Docking.AutoHideContainer();
			this.dockPanelProperty = new DevExpress.XtraBars.Docking.DockPanel();
			this.dockPanel1_Container = new DevExpress.XtraBars.Docking.ControlContainer();
			this.panelContainer1 = new DevExpress.XtraBars.Docking.DockPanel();
			this.dockPanelNailImage = new DevExpress.XtraBars.Docking.DockPanel();
			this.controlContainer1 = new DevExpress.XtraBars.Docking.ControlContainer();
			this.dockPanLibrary = new DevExpress.XtraBars.Docking.DockPanel();
			this.ctrContainerLibrary = new DevExpress.XtraBars.Docking.ControlContainer();
			this.ctrContainerPropertyGrid = new DevExpress.XtraBars.Docking.ControlContainer();
			this.dockPanel3 = new DevExpress.XtraBars.Docking.DockPanel();
			this.dockPanel3_Container = new DevExpress.XtraBars.Docking.ControlContainer();
			this.dockPanel4 = new DevExpress.XtraBars.Docking.DockPanel();
			this.dockPanel4_Container = new DevExpress.XtraBars.Docking.ControlContainer();
			this.panelContainer3 = new DevExpress.XtraBars.Docking.DockPanel();
			this.dkpLibrary = new DevExpress.XtraBars.Docking.DockPanel();
			((System.ComponentModel.ISupportInitialize)(this.schedulerStorage1)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.dockManager1)).BeginInit();
			this.hideContainerRight.SuspendLayout();
			this.dockPanelProperty.SuspendLayout();
			this.panelContainer1.SuspendLayout();
			this.dockPanelNailImage.SuspendLayout();
			this.dockPanLibrary.SuspendLayout();
			this.dockPanel3.SuspendLayout();
			this.dockPanel4.SuspendLayout();
			this.dkpLibrary.SuspendLayout();
			this.SuspendLayout();
			// 
			// schedulerStorage1
			// 
			this.schedulerStorage1.Resources.AutoReload = false;
			// 
			// dockManager1
			// 
			this.dockManager1.AutoHideContainers.AddRange(new DevExpress.XtraBars.Docking.AutoHideContainer[] {
            this.hideContainerRight});
			this.dockManager1.Form = this;
			this.dockManager1.RootPanels.AddRange(new DevExpress.XtraBars.Docking.DockPanel[] {
            this.panelContainer1});
			this.dockManager1.TopZIndexControls.AddRange(new string[] {
            "DevExpress.XtraBars.BarDockControl",
            "System.Windows.Forms.StatusBar",
            "DevExpress.XtraBars.Ribbon.RibbonStatusBar",
            "DevExpress.XtraBars.Ribbon.RibbonControl"});
			// 
			// hideContainerRight
			// 
			this.hideContainerRight.Controls.Add(this.dockPanelProperty);
			this.hideContainerRight.Dock = System.Windows.Forms.DockStyle.Right;
			this.hideContainerRight.Location = new System.Drawing.Point(753, 0);
			this.hideContainerRight.Name = "hideContainerRight";
			this.hideContainerRight.Size = new System.Drawing.Size(19, 551);
			// 
			// dockPanelProperty
			// 
			this.dockPanelProperty.Controls.Add(this.dockPanel1_Container);
			this.dockPanelProperty.Dock = DevExpress.XtraBars.Docking.DockingStyle.Right;
			this.dockPanelProperty.FloatVertical = true;
			this.dockPanelProperty.ID = new System.Guid("fbefa99a-5ec0-413f-8cdc-d8e2b316f532");
			this.dockPanelProperty.Location = new System.Drawing.Point(0, 0);
			this.dockPanelProperty.Name = "dockPanelProperty";
			this.dockPanelProperty.Options.AllowDockTop = false;
			this.dockPanelProperty.Options.ShowCloseButton = false;
			this.dockPanelProperty.Options.ShowMaximizeButton = false;
			this.dockPanelProperty.SavedDock = DevExpress.XtraBars.Docking.DockingStyle.Right;
			this.dockPanelProperty.SavedIndex = 0;
			this.dockPanelProperty.Size = new System.Drawing.Size(200, 551);
			this.dockPanelProperty.Text = "Properties";
            this.dockPanelProperty.Hint = "Properties";
			this.dockPanelProperty.Visibility = DevExpress.XtraBars.Docking.DockVisibility.AutoHide;
			// 
			// dockPanel1_Container
			// 
			this.dockPanel1_Container.Location = new System.Drawing.Point(3, 25);
			this.dockPanel1_Container.Name = "dockPanel1_Container";
			this.dockPanel1_Container.Size = new System.Drawing.Size(194, 523);
			this.dockPanel1_Container.TabIndex = 0;
			// 
			// panelContainer1
			// 
			this.panelContainer1.Controls.Add(this.dockPanelNailImage);
			this.panelContainer1.Controls.Add(this.dockPanLibrary);
			this.panelContainer1.Dock = DevExpress.XtraBars.Docking.DockingStyle.Left;
			this.panelContainer1.ID = new System.Guid("77784ba9-a8bd-4e7f-b3ba-57b43e4aa396");
			this.panelContainer1.Location = new System.Drawing.Point(0, 0);
			this.panelContainer1.Name = "panelContainer1";
			this.panelContainer1.Size = new System.Drawing.Size(250, 551);
			this.panelContainer1.Text = "panelContainer1";
			// 
			// dockPanelNailImage
			// 
			this.dockPanelNailImage.Controls.Add(this.controlContainer1);
			this.dockPanelNailImage.Dock = DevExpress.XtraBars.Docking.DockingStyle.Fill;
			this.dockPanelNailImage.ID = new System.Guid("f822a864-2837-4aae-acb1-7ac824f0afc8");
			this.dockPanelNailImage.Location = new System.Drawing.Point(0, 0);
			this.dockPanelNailImage.Name = "dockPanelNailImage";
			this.dockPanelNailImage.Options.AllowDockTop = false;
			this.dockPanelNailImage.Options.ShowCloseButton = false;
			this.dockPanelNailImage.Options.ShowMaximizeButton = false;
			this.dockPanelNailImage.Size = new System.Drawing.Size(200, 275);
			this.dockPanelNailImage.Text = "Thumb Nail Image ";
            this.dockPanelNailImage.Hint = "Thumb Nail Image ";
			// 
			// controlContainer1
			// 
			this.controlContainer1.Location = new System.Drawing.Point(3, 25);
			this.controlContainer1.Name = "controlContainer1";
			this.controlContainer1.Size = new System.Drawing.Size(194, 247);
			this.controlContainer1.TabIndex = 0;
			// 
			// dockPanLibrary
			// 
			this.dockPanLibrary.Controls.Add(this.ctrContainerLibrary);
			this.dockPanLibrary.Dock = DevExpress.XtraBars.Docking.DockingStyle.Fill;
			this.dockPanLibrary.ID = new System.Guid("f16f1df5-9d68-47b8-988d-701a88261c12");
			this.dockPanLibrary.Location = new System.Drawing.Point(0, 275);
			this.dockPanLibrary.Name = "dockPanLibrary";
			this.dockPanLibrary.Options.AllowDockTop = false;
			this.dockPanLibrary.Options.ShowCloseButton = false;
			this.dockPanLibrary.Options.ShowMaximizeButton = false;
			this.dockPanLibrary.Size = new System.Drawing.Size(230, 276);
			this.dockPanLibrary.Text = "Library";
            this.dockPanLibrary.Hint = "Library";
			// 
			// ctrContainerLibrary
			// 
			this.ctrContainerLibrary.Location = new System.Drawing.Point(3, 25);
			this.ctrContainerLibrary.Name = "ctrContainerLibrary";
			this.ctrContainerLibrary.Size = new System.Drawing.Size(194, 248);
			this.ctrContainerLibrary.TabIndex = 0;
			// 
			// ctrContainerPropertyGrid
			// 
			this.ctrContainerPropertyGrid.Location = new System.Drawing.Point(0, 0);
			this.ctrContainerPropertyGrid.Name = "ctrContainerPropertyGrid";
			this.ctrContainerPropertyGrid.Size = new System.Drawing.Size(194, 203);
			this.ctrContainerPropertyGrid.TabIndex = 0;
			// 
			// dockPanel3
			// 
			this.dockPanel3.Controls.Add(this.dockPanel3_Container);
			this.dockPanel3.Dock = DevExpress.XtraBars.Docking.DockingStyle.Fill;
			this.dockPanel3.FloatVertical = true;
			this.dockPanel3.ID = new System.Guid("08077d83-e73e-4785-a2ea-f6498db25a93");
			this.dockPanel3.Location = new System.Drawing.Point(3, 25);
			this.dockPanel3.Name = "dockPanel3";
			this.dockPanel3.Size = new System.Drawing.Size(194, 204);
			this.dockPanel3.Text = "dockPanel3";
			// 
			// dockPanel3_Container
			// 
			this.dockPanel3_Container.Location = new System.Drawing.Point(0, 0);
			this.dockPanel3_Container.Name = "dockPanel3_Container";
			this.dockPanel3_Container.Size = new System.Drawing.Size(194, 204);
			this.dockPanel3_Container.TabIndex = 0;
			// 
			// dockPanel4
			// 
			this.dockPanel4.Controls.Add(this.dockPanel4_Container);
			this.dockPanel4.Dock = DevExpress.XtraBars.Docking.DockingStyle.Fill;
			this.dockPanel4.ID = new System.Guid("1ea37629-93a8-48a6-abc5-b2986b46244f");
			this.dockPanel4.Location = new System.Drawing.Point(3, 25);
			this.dockPanel4.Name = "dockPanel4";
			this.dockPanel4.Size = new System.Drawing.Size(194, 204);
			this.dockPanel4.Text = "dockPanel4";
			// 
			// dockPanel4_Container
			// 
			this.dockPanel4_Container.Location = new System.Drawing.Point(0, 0);
			this.dockPanel4_Container.Name = "dockPanel4_Container";
			this.dockPanel4_Container.Size = new System.Drawing.Size(194, 204);
			this.dockPanel4_Container.TabIndex = 0;
			// 
			// panelContainer3
			// 
			this.panelContainer3.Dock = DevExpress.XtraBars.Docking.DockingStyle.Bottom;
			this.panelContainer3.ID = new System.Guid("694afc00-773c-4419-8ce1-b3d36d967083");
			this.panelContainer3.Location = new System.Drawing.Point(0, 0);
			this.panelContainer3.Name = "panelContainer3";
			this.panelContainer3.Size = new System.Drawing.Size(200, 509);
			// 
			// dkpLibrary
			// 
			this.dkpLibrary.ActiveChild = this.dockPanel4;
			this.dkpLibrary.Controls.Add(this.dockPanel4);
			this.dkpLibrary.Controls.Add(this.dockPanel3);
			this.dkpLibrary.Dock = DevExpress.XtraBars.Docking.DockingStyle.Bottom;
			this.dkpLibrary.ID = new System.Guid("ed859838-d3c8-4328-aa44-6dcbd40aa0bc");
			this.dkpLibrary.Location = new System.Drawing.Point(0, 254);
			this.dkpLibrary.Name = "dkpLibrary";
			this.dkpLibrary.Size = new System.Drawing.Size(200, 255);
			this.dkpLibrary.Tabbed = true;
			this.dkpLibrary.Text = "Library";
			// 
			// SchedulerModule
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.panelContainer1);
			this.Controls.Add(this.hideContainerRight);
			this.Name = "SchedulerModule";
			this.Size = new System.Drawing.Size(772, 551);
			((System.ComponentModel.ISupportInitialize)(this.schedulerStorage1)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.dockManager1)).EndInit();
			this.hideContainerRight.ResumeLayout(false);
			this.dockPanelProperty.ResumeLayout(false);
			this.panelContainer1.ResumeLayout(false);
			this.dockPanelNailImage.ResumeLayout(false);
			this.dockPanLibrary.ResumeLayout(false);
			this.dockPanel3.ResumeLayout(false);
			this.dockPanel4.ResumeLayout(false);
			this.dkpLibrary.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion


		private DevExpress.XtraScheduler.SchedulerStorage schedulerStorage1;
		private DevExpress.XtraBars.Docking.DockManager dockManager1;
		private DevExpress.XtraBars.Docking.ControlContainer ctrContainerPropertyGrid;
		private DevExpress.XtraBars.Docking.DockPanel dockPanel3;
		private DevExpress.XtraBars.Docking.ControlContainer dockPanel3_Container;
		private DevExpress.XtraBars.Docking.DockPanel dockPanel4;
		private DevExpress.XtraBars.Docking.ControlContainer dockPanel4_Container;
		private DevExpress.XtraBars.Docking.DockPanel panelContainer3;
		private DevExpress.XtraBars.Docking.DockPanel dkpLibrary;
		private DevExpress.XtraBars.Docking.DockPanel dockPanLibrary;
		private DevExpress.XtraBars.Docking.ControlContainer ctrContainerLibrary;
		private DevExpress.XtraBars.Docking.DockPanel dockPanelProperty;
		private DevExpress.XtraBars.Docking.ControlContainer dockPanel1_Container;
		private DevExpress.XtraBars.Docking.AutoHideContainer hideContainerRight;
		private DevExpress.XtraBars.Docking.DockPanel panelContainer1;
		private DevExpress.XtraBars.Docking.DockPanel dockPanelNailImage;
		private DevExpress.XtraBars.Docking.ControlContainer controlContainer1;
	}
}