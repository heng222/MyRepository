
using ProWrite.UI.Controls;

namespace ProWrite.UI.Controls.Modules
{
	partial class EditorModuleNew
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
            this.hideContainerRight = new DevExpress.XtraBars.Docking.AutoHideContainer();
            this.dockPanelProperty = new DevExpress.XtraBars.Docking.DockPanel();
            this.dockPanelPropertyGrid_Container = new DevExpress.XtraBars.Docking.ControlContainer();
            this.dockPanelLeft = new DevExpress.XtraBars.Docking.DockPanel();
            this.dockPanelToolBox = new DevExpress.XtraBars.Docking.DockPanel();
            this.dockPanelToolBox_Container = new DevExpress.XtraBars.Docking.ControlContainer();
            this.dockPanelEffect = new DevExpress.XtraBars.Docking.DockPanel();
            this.dockPanelEffect_Container = new DevExpress.XtraBars.Docking.ControlContainer();
            this.dockPanelLibrary = new DevExpress.XtraBars.Docking.DockPanel();
            this.dockPanelLibrary_Container = new DevExpress.XtraBars.Docking.ControlContainer();
            ((System.ComponentModel.ISupportInitialize)(this.dockManager1)).BeginInit();
            this.hideContainerRight.SuspendLayout();
            this.dockPanelProperty.SuspendLayout();
            this.dockPanelLeft.SuspendLayout();
            this.dockPanelToolBox.SuspendLayout();
            this.dockPanelEffect.SuspendLayout();
            this.dockPanelLibrary.SuspendLayout();
            this.SuspendLayout();
            // 
            // dockManager1
            // 
            this.dockManager1.AutoHideContainers.AddRange(new DevExpress.XtraBars.Docking.AutoHideContainer[] {
            this.hideContainerRight});
            this.dockManager1.Form = this;
            this.dockManager1.RootPanels.AddRange(new DevExpress.XtraBars.Docking.DockPanel[] {
            this.dockPanelLeft});
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
            this.hideContainerRight.Location = new System.Drawing.Point(1012, 0);
            this.hideContainerRight.Name = "hideContainerRight";
            this.hideContainerRight.Size = new System.Drawing.Size(19, 634);
            // 
            // dockPanelProperty
            // 
            this.dockPanelProperty.Controls.Add(this.dockPanelPropertyGrid_Container);
            this.dockPanelProperty.Dock = DevExpress.XtraBars.Docking.DockingStyle.Right;
            this.dockPanelProperty.Hint = "Propeties";
            this.dockPanelProperty.ID = new System.Guid("e9b240e4-c399-4c73-a3cd-275845ab2550");
            this.dockPanelProperty.Location = new System.Drawing.Point(0, 0);
            this.dockPanelProperty.Name = "dockPanelProperty";
            this.dockPanelProperty.Options.AllowDockTop = false;
            this.dockPanelProperty.Options.ShowMaximizeButton = false;
            this.dockPanelProperty.SavedDock = DevExpress.XtraBars.Docking.DockingStyle.Right;
            this.dockPanelProperty.SavedIndex = 0;
            this.dockPanelProperty.Size = new System.Drawing.Size(200, 634);
            this.dockPanelProperty.Text = "Propeties";
            this.dockPanelProperty.Visibility = DevExpress.XtraBars.Docking.DockVisibility.AutoHide;
            // 
            // dockPanelPropertyGrid_Container
            // 
            this.dockPanelPropertyGrid_Container.Location = new System.Drawing.Point(3, 25);
            this.dockPanelPropertyGrid_Container.Name = "dockPanelPropertyGrid_Container";
            this.dockPanelPropertyGrid_Container.Size = new System.Drawing.Size(194, 606);
            this.dockPanelPropertyGrid_Container.TabIndex = 0;
            // 
            // dockPanelLeft
            // 
            this.dockPanelLeft.Controls.Add(this.dockPanelToolBox);
            this.dockPanelLeft.Controls.Add(this.dockPanelEffect);
            this.dockPanelLeft.Controls.Add(this.dockPanelLibrary);
            this.dockPanelLeft.Dock = DevExpress.XtraBars.Docking.DockingStyle.Left;
            this.dockPanelLeft.ID = new System.Guid("3b17376d-c393-4dd0-9657-69c61c5e64fb");
            this.dockPanelLeft.Location = new System.Drawing.Point(0, 0);
            this.dockPanelLeft.Name = "dockPanelLeft";
            this.dockPanelLeft.Options.AllowDockTop = false;
            this.dockPanelLeft.Options.ShowMaximizeButton = false;
            this.dockPanelLeft.Size = new System.Drawing.Size(200, 634);
            this.dockPanelLeft.Text = "panelContainer1";
            // 
            // dockPanelToolBox
            // 
            this.dockPanelToolBox.Controls.Add(this.dockPanelToolBox_Container);
            this.dockPanelToolBox.Dock = DevExpress.XtraBars.Docking.DockingStyle.Fill;
            this.dockPanelToolBox.Hint = "ToolBox";
            this.dockPanelToolBox.ID = new System.Guid("e0fc7e4b-dac5-4537-b6aa-ffe4df78e68c");
            this.dockPanelToolBox.Location = new System.Drawing.Point(0, 0);
            this.dockPanelToolBox.Name = "dockPanelToolBox";
            this.dockPanelToolBox.Options.ShowCloseButton = false;
            this.dockPanelToolBox.Options.ShowMaximizeButton = false;
            this.dockPanelToolBox.Size = new System.Drawing.Size(200, 211);
            this.dockPanelToolBox.Text = "ToolBox";
            // 
            // dockPanelToolBox_Container
            // 
            this.dockPanelToolBox_Container.Location = new System.Drawing.Point(3, 25);
            this.dockPanelToolBox_Container.Name = "dockPanelToolBox_Container";
            this.dockPanelToolBox_Container.Size = new System.Drawing.Size(194, 183);
            this.dockPanelToolBox_Container.TabIndex = 0;
            // 
            // dockPanelEffect
            // 
            this.dockPanelEffect.Controls.Add(this.dockPanelEffect_Container);
            this.dockPanelEffect.Dock = DevExpress.XtraBars.Docking.DockingStyle.Fill;
            this.dockPanelEffect.Hint = "Effect";
            this.dockPanelEffect.ID = new System.Guid("59df5597-81ae-420a-be2b-68b2c078889e");
            this.dockPanelEffect.Location = new System.Drawing.Point(0, 211);
            this.dockPanelEffect.Name = "dockPanelEffect";
            this.dockPanelEffect.Options.ShowCloseButton = false;
            this.dockPanelEffect.Options.ShowMaximizeButton = false;
            this.dockPanelEffect.Size = new System.Drawing.Size(200, 211);
            this.dockPanelEffect.Text = "Effect";
            // 
            // dockPanelEffect_Container
            // 
            this.dockPanelEffect_Container.Location = new System.Drawing.Point(3, 25);
            this.dockPanelEffect_Container.Name = "dockPanelEffect_Container";
            this.dockPanelEffect_Container.Size = new System.Drawing.Size(194, 183);
            this.dockPanelEffect_Container.TabIndex = 0;
            // 
            // dockPanelLibrary
            // 
            this.dockPanelLibrary.Controls.Add(this.dockPanelLibrary_Container);
            this.dockPanelLibrary.Dock = DevExpress.XtraBars.Docking.DockingStyle.Fill;
            this.dockPanelLibrary.Hint = "Library";
            this.dockPanelLibrary.ID = new System.Guid("e80e07f4-1aad-4ddd-b4a3-e682fc3ee99c");
            this.dockPanelLibrary.Location = new System.Drawing.Point(0, 422);
            this.dockPanelLibrary.Name = "dockPanelLibrary";
            this.dockPanelLibrary.Options.AllowDockTop = false;
            this.dockPanelLibrary.Options.ShowCloseButton = false;
            this.dockPanelLibrary.Options.ShowMaximizeButton = false;
            this.dockPanelLibrary.Size = new System.Drawing.Size(200, 212);
            this.dockPanelLibrary.Text = "Library";
            // 
            // dockPanelLibrary_Container
            // 
            this.dockPanelLibrary_Container.Location = new System.Drawing.Point(3, 25);
            this.dockPanelLibrary_Container.Name = "dockPanelLibrary_Container";
            this.dockPanelLibrary_Container.Size = new System.Drawing.Size(194, 184);
            this.dockPanelLibrary_Container.TabIndex = 0;
            // 
            // EditorModuleNew
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.dockPanelLeft);
            this.Controls.Add(this.hideContainerRight);
            this.Name = "EditorModuleNew";
            this.Size = new System.Drawing.Size(1031, 634);
            ((System.ComponentModel.ISupportInitialize)(this.dockManager1)).EndInit();
            this.hideContainerRight.ResumeLayout(false);
            this.dockPanelProperty.ResumeLayout(false);
            this.dockPanelLeft.ResumeLayout(false);
            this.dockPanelToolBox.ResumeLayout(false);
            this.dockPanelEffect.ResumeLayout(false);
            this.dockPanelLibrary.ResumeLayout(false);
            this.ResumeLayout(false);

		}

		#endregion

		private DevExpress.XtraBars.Docking.DockManager dockManager1;
        private DevExpress.XtraBars.Docking.DockPanel dockPanelLeft;
		private DevExpress.XtraBars.Docking.DockPanel dockPanelEffect;
		private DevExpress.XtraBars.Docking.ControlContainer dockPanelEffect_Container;
		private DevExpress.XtraBars.Docking.DockPanel dockPanelToolBox;
		private DevExpress.XtraBars.Docking.ControlContainer dockPanelToolBox_Container;
		private DevExpress.XtraBars.Docking.DockPanel dockPanelLibrary;
		private DevExpress.XtraBars.Docking.ControlContainer dockPanelLibrary_Container;
		private DevExpress.XtraBars.Docking.DockPanel dockPanelProperty;
		private DevExpress.XtraBars.Docking.ControlContainer dockPanelPropertyGrid_Container;
		private DevExpress.XtraBars.Docking.AutoHideContainer hideContainerRight;

	}
}