using System;
using ProWrite.UI.Controls.Common;
namespace ProWrite.UI.Controls.Scheduler
{
    partial class ScheduleControl
    {
        /// <summary> 
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
        	ControlService.LibraryTree.Controller.LibraryColorChanged -= Controller_LibraryColorChanged;
            if (_uploadAction != null)
                _uploadAction.UnsubscribeFtpEvent();
 
            //LocalMessageBus.Subject<LibraryRenameMessage>().Observers -= OnLibraryRename;
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            DevExpress.XtraScheduler.TimeRuler timeRuler1 = new DevExpress.XtraScheduler.TimeRuler();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ScheduleControl));
            this.schedulerStorage1 = new ProWrite.UI.Controls.Scheduler.SchedulerStorageDecorator(this.components);
            this.schedulerControl1 = new DevExpress.XtraScheduler.SchedulerControl();
            this.panelControl1 = new DevExpress.XtraEditors.PanelControl();
            this.cbView = new DevExpress.XtraEditors.ImageComboBoxEdit();
            this.labelControl2 = new DevExpress.XtraEditors.LabelControl();
            this.dateLbl = new DevExpress.XtraEditors.LabelControl();
            this.todayBtn = new DevExpress.XtraEditors.SimpleButton();
            this.nextBtn = new DevExpress.XtraEditors.SimpleButton();
            this.previousBtn = new DevExpress.XtraEditors.SimpleButton();

            this.barManager1 = new DevExpress.XtraBars.BarManager(this.components);
            this.bar3 = new DevExpress.XtraBars.Bar();
            this.viewSelectorBar1 = new DevExpress.XtraScheduler.UI.ViewSelectorBar();
            this.viewSelectorItem1 = new DevExpress.XtraScheduler.UI.ViewSelectorItem();
            this.viewSelectorItem2 = new DevExpress.XtraScheduler.UI.ViewSelectorItem();
            this.viewSelectorItem3 = new DevExpress.XtraScheduler.UI.ViewSelectorItem();
            this.viewSelectorItem4 = new DevExpress.XtraScheduler.UI.ViewSelectorItem();
            this.viewSelectorItem5 = new DevExpress.XtraScheduler.UI.ViewSelectorItem();
            this.viewNavigatorBar1 = new DevExpress.XtraScheduler.UI.ViewNavigatorBar();
            this.viewNavigatorBackwardItem1 = new DevExpress.XtraScheduler.UI.ViewNavigatorBackwardItem();
            this.viewNavigatorForwardItem1 = new DevExpress.XtraScheduler.UI.ViewNavigatorForwardItem();
            this.viewNavigatorTodayItem1 = new DevExpress.XtraScheduler.UI.ViewNavigatorTodayItem();
            this.viewNavigatorZoomInItem1 = new DevExpress.XtraScheduler.UI.ViewNavigatorZoomInItem();
            this.viewNavigatorZoomOutItem1 = new DevExpress.XtraScheduler.UI.ViewNavigatorZoomOutItem();
            this.barDockControlTop = new DevExpress.XtraBars.BarDockControl();
            this.barDockControlBottom = new DevExpress.XtraBars.BarDockControl();
            this.barDockControlLeft = new DevExpress.XtraBars.BarDockControl();
            this.barDockControlRight = new DevExpress.XtraBars.BarDockControl();
            this.viewSelector1 = new DevExpress.XtraScheduler.UI.ViewSelector(this.components);
            this.viewNavigator1 = new DevExpress.XtraScheduler.UI.ViewNavigator(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.barManager1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.viewSelector1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.viewNavigator1)).BeginInit();


            ((System.ComponentModel.ISupportInitialize)(this.schedulerStorage1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.schedulerControl1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl1)).BeginInit();
            this.panelControl1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.cbView.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // schedulerStorage1
            // 
            this.schedulerStorage1.Resources.AutoReload = false;
            this.schedulerStorage1.AppointmentsChanged += new DevExpress.XtraScheduler.PersistentObjectsEventHandler(this.schedulerStorage1_AppointmentsChanged);
            // 
            // schedulerControl1
            // 
            this.schedulerControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.schedulerControl1.Location = new System.Drawing.Point(0, 26);
            this.schedulerControl1.Name = "schedulerControl1";
            this.schedulerControl1.Size = new System.Drawing.Size(566, 528);
            this.schedulerControl1.Start = new System.DateTime(2008, 5, 12, 0, 0, 0, 0);
            this.schedulerControl1.Storage = this.schedulerStorage1;
            this.schedulerControl1.TabIndex = 3;
            this.schedulerControl1.Text = "schedulerControl1";
            this.schedulerControl1.Views.DayView.TimeRulers.Add(timeRuler1);
            this.schedulerControl1.Views.TimelineView.Enabled = false;
            this.schedulerControl1.Views.WorkWeekView.Enabled = false;
            this.schedulerControl1.DayView.WorkTime.Start = System.TimeSpan.Parse("06:00:00");
            this.schedulerControl1.OptionsView.HideSelection = true;
            this.schedulerControl1.OptionsCustomization.AllowAppointmentDelete = DevExpress.XtraScheduler.UsedAppointmentType.None;
            this.schedulerControl1.ActiveViewChanged += new System.EventHandler(this.schedulerControl1_ActiveViewChanged);
            this.schedulerControl1.DragEnter += new System.Windows.Forms.DragEventHandler(this.schedulerControl1_DragEnter);
            this.schedulerControl1.CustomDrawDayViewAllDayArea += new DevExpress.XtraScheduler.CustomDrawObjectEventHandler(schedulerControl1_CustomDrawDayViewAllDayArea);
            this.schedulerControl1.PreparePopupMenu += new DevExpress.XtraScheduler.PreparePopupMenuEventHandler(this.schedulerControl1_PreparePopupMenu);
            this.schedulerControl1.EditAppointmentFormShowing += new DevExpress.XtraScheduler.AppointmentFormEventHandler(this.schedulerControl1_EditAppointmentFormShowing);
            schedulerControl1.MonthView.CompressWeekend = false;
            this.schedulerControl1.SelectionChanged += new System.EventHandler(this.schedulerControl1_SelectionChanged);
            this.schedulerControl1.AppointmentDrop += new DevExpress.XtraScheduler.AppointmentDragEventHandler(this.schedulerControl1_AppointmentDrop);
            this.schedulerControl1.DragLeave += new System.EventHandler(this.schedulerControl1_DragLeave);
            this.schedulerControl1.OptionsCustomization.AllowAppointmentEdit = DevExpress.XtraScheduler.UsedAppointmentType.Custom;
            this.schedulerControl1.KeyDown += new System.Windows.Forms.KeyEventHandler(schedulerControl1_KeyDown);
            //this.schedulerControl1.OptionsCustomization.AllowAppointmentDelete =  DevExpress.XtraScheduler.UsedAppointmentType.None;
            //this.schedulerControl1.OptionsCustomization.AllowAppointmentResize = DevExpress.XtraScheduler.UsedAppointmentType.None;
            this.schedulerControl1.MouseDown += new System.Windows.Forms.MouseEventHandler(schedulerControl1_MouseDown);
            this.schedulerControl1.MouseMove += new System.Windows.Forms.MouseEventHandler(schedulerControl1_MouseMove);
            this.schedulerControl1.AppointmentResized += new DevExpress.XtraScheduler.AppointmentResizeEventHandler(schedulerControl1_AppointmentResized);
            this.schedulerControl1.OptionsBehavior.RecurrentAppointmentDeleteAction = DevExpress.XtraScheduler.RecurrentAppointmentAction.Series;
            this.schedulerControl1.OptionsBehavior.RecurrentAppointmentEditAction = DevExpress.XtraScheduler.RecurrentAppointmentAction.Series;

            // 
            // barManager1
            // 
            this.barManager1.AllowCustomization = false;
            this.barManager1.AllowMoveBarOnToolbar = false;
            this.barManager1.AllowQuickCustomization = false;
            this.barManager1.AllowShowToolbarsPopup = false;
            this.barManager1.Bars.AddRange(new DevExpress.XtraBars.Bar[] {
            this.bar3,
            this.viewSelectorBar1,
            this.viewNavigatorBar1});
            this.barManager1.DockControls.Add(this.barDockControlTop);
            this.barManager1.DockControls.Add(this.barDockControlBottom);
            this.barManager1.DockControls.Add(this.barDockControlLeft);
            this.barManager1.DockControls.Add(this.barDockControlRight);
            this.barManager1.Form = this;
            this.barManager1.Items.AddRange(new DevExpress.XtraBars.BarItem[] {
            this.viewSelectorItem1,
            this.viewSelectorItem2,
            this.viewSelectorItem3,
            this.viewSelectorItem4,
            this.viewSelectorItem5,
            this.viewNavigatorBackwardItem1,
            this.viewNavigatorForwardItem1,
            this.viewNavigatorTodayItem1,
            this.viewNavigatorZoomInItem1,
            this.viewNavigatorZoomOutItem1});
            this.barManager1.MaxItemId = 15;
            this.barManager1.StatusBar = this.bar3;
            // 
            // bar3
            // 
            this.bar3.BarName = "Status bar";
            this.bar3.CanDockStyle = DevExpress.XtraBars.BarCanDockStyle.Bottom;
            this.bar3.DockCol = 0;
            this.bar3.DockRow = 0;
            this.bar3.DockStyle = DevExpress.XtraBars.BarDockStyle.Bottom;
            this.bar3.OptionsBar.AllowQuickCustomization = false;
            this.bar3.OptionsBar.DrawDragBorder = false;
            this.bar3.OptionsBar.UseWholeRow = true;
            this.bar3.Text = "Status bar";
            // 
            // viewSelectorBar1
            // 
            this.viewSelectorBar1.DockCol = 1;
            this.viewSelectorBar1.DockRow = 0;
            this.viewSelectorBar1.DockStyle = DevExpress.XtraBars.BarDockStyle.Top;
            this.viewSelectorBar1.LinksPersistInfo.AddRange(new DevExpress.XtraBars.LinkPersistInfo[] {
            new DevExpress.XtraBars.LinkPersistInfo(this.viewSelectorItem1),
            new DevExpress.XtraBars.LinkPersistInfo(this.viewSelectorItem2),
            new DevExpress.XtraBars.LinkPersistInfo(this.viewSelectorItem3),
            new DevExpress.XtraBars.LinkPersistInfo(this.viewSelectorItem4),
            new DevExpress.XtraBars.LinkPersistInfo(this.viewSelectorItem5)});
            // 
            // viewSelectorItem1
            // 
            this.viewSelectorItem1.Checked = true;
            this.viewSelectorItem1.Glyph = ((System.Drawing.Image)(resources.GetObject("viewSelectorItem1.Glyph")));
            this.viewSelectorItem1.GroupIndex = 1;
            this.viewSelectorItem1.Id = 0;
            this.viewSelectorItem1.ItemShortcut = new DevExpress.XtraBars.BarShortcut(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Alt)
                            | System.Windows.Forms.Keys.D1));
            this.viewSelectorItem1.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("viewSelectorItem1.LargeGlyph")));
            this.viewSelectorItem1.Name = "viewSelectorItem1";
            this.viewSelectorItem1.SchedulerViewType = DevExpress.XtraScheduler.SchedulerViewType.Day;
            // 
            // viewSelectorItem2
            // 
            this.viewSelectorItem2.Glyph = ((System.Drawing.Image)(resources.GetObject("viewSelectorItem2.Glyph")));
            this.viewSelectorItem2.GroupIndex = 1;
            this.viewSelectorItem2.Id = 1;
            this.viewSelectorItem2.ItemShortcut = new DevExpress.XtraBars.BarShortcut(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Alt)
                            | System.Windows.Forms.Keys.D2));
            this.viewSelectorItem2.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("viewSelectorItem2.LargeGlyph")));
            this.viewSelectorItem2.Name = "viewSelectorItem2";
            this.viewSelectorItem2.SchedulerViewType = DevExpress.XtraScheduler.SchedulerViewType.WorkWeek;
            // 
            // viewSelectorItem3
            // 
            this.viewSelectorItem3.Glyph = ((System.Drawing.Image)(resources.GetObject("viewSelectorItem3.Glyph")));
            this.viewSelectorItem3.GroupIndex = 1;
            this.viewSelectorItem3.Id = 2;
            this.viewSelectorItem3.ItemShortcut = new DevExpress.XtraBars.BarShortcut(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Alt)
                            | System.Windows.Forms.Keys.D3));
            this.viewSelectorItem3.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("viewSelectorItem3.LargeGlyph")));
            this.viewSelectorItem3.Name = "viewSelectorItem3";
            this.viewSelectorItem3.SchedulerViewType = DevExpress.XtraScheduler.SchedulerViewType.Week;
            // 
            // viewSelectorItem4
            // 
            this.viewSelectorItem4.Glyph = ((System.Drawing.Image)(resources.GetObject("viewSelectorItem4.Glyph")));
            this.viewSelectorItem4.GroupIndex = 1;
            this.viewSelectorItem4.Id = 3;
            this.viewSelectorItem4.ItemShortcut = new DevExpress.XtraBars.BarShortcut(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Alt)
                            | System.Windows.Forms.Keys.D4));
            this.viewSelectorItem4.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("viewSelectorItem4.LargeGlyph")));
            this.viewSelectorItem4.Name = "viewSelectorItem4";
            this.viewSelectorItem4.SchedulerViewType = DevExpress.XtraScheduler.SchedulerViewType.Month;
            // 
            // viewSelectorItem5
            // 
            this.viewSelectorItem5.Glyph = ((System.Drawing.Image)(resources.GetObject("viewSelectorItem5.Glyph")));
            this.viewSelectorItem5.GroupIndex = 1;
            this.viewSelectorItem5.Id = 4;
            this.viewSelectorItem5.ItemShortcut = new DevExpress.XtraBars.BarShortcut(((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Alt)
                            | System.Windows.Forms.Keys.D5));
            this.viewSelectorItem5.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("viewSelectorItem5.LargeGlyph")));
            this.viewSelectorItem5.Name = "viewSelectorItem5";
            this.viewSelectorItem5.SchedulerViewType = DevExpress.XtraScheduler.SchedulerViewType.Timeline;
            // 
            // viewNavigatorBar1
            // 
            this.viewNavigatorBar1.DockCol = 0;
            this.viewNavigatorBar1.DockRow = 0;
            this.viewNavigatorBar1.DockStyle = DevExpress.XtraBars.BarDockStyle.Top;
            this.viewNavigatorBar1.LinksPersistInfo.AddRange(new DevExpress.XtraBars.LinkPersistInfo[] {
            new DevExpress.XtraBars.LinkPersistInfo(this.viewNavigatorBackwardItem1),
            new DevExpress.XtraBars.LinkPersistInfo(this.viewNavigatorForwardItem1),
            new DevExpress.XtraBars.LinkPersistInfo(this.viewNavigatorTodayItem1),
            new DevExpress.XtraBars.LinkPersistInfo(this.viewNavigatorZoomInItem1),
            new DevExpress.XtraBars.LinkPersistInfo(this.viewNavigatorZoomOutItem1)});
            this.viewNavigatorBar1.Offset = 1;
            // 
            // viewNavigatorBackwardItem1
            // 
            this.viewNavigatorBackwardItem1.Glyph = ((System.Drawing.Image)(resources.GetObject("viewNavigatorBackwardItem1.Glyph")));
            this.viewNavigatorBackwardItem1.GroupIndex = 1;
            this.viewNavigatorBackwardItem1.Id = 10;
            this.viewNavigatorBackwardItem1.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("viewNavigatorBackwardItem1.LargeGlyph")));
            this.viewNavigatorBackwardItem1.Name = "viewNavigatorBackwardItem1";
            // 
            // viewNavigatorForwardItem1
            // 
            this.viewNavigatorForwardItem1.Glyph = ((System.Drawing.Image)(resources.GetObject("viewNavigatorForwardItem1.Glyph")));
            this.viewNavigatorForwardItem1.GroupIndex = 1;
            this.viewNavigatorForwardItem1.Id = 11;
            this.viewNavigatorForwardItem1.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("viewNavigatorForwardItem1.LargeGlyph")));
            this.viewNavigatorForwardItem1.Name = "viewNavigatorForwardItem1";
            // 
            // viewNavigatorTodayItem1
            // 
            this.viewNavigatorTodayItem1.Glyph = ((System.Drawing.Image)(resources.GetObject("viewNavigatorTodayItem1.Glyph")));
            this.viewNavigatorTodayItem1.GroupIndex = 1;
            this.viewNavigatorTodayItem1.Id = 12;
            this.viewNavigatorTodayItem1.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("viewNavigatorTodayItem1.LargeGlyph")));
            this.viewNavigatorTodayItem1.Name = "viewNavigatorTodayItem1";
            // 
            // viewNavigatorZoomInItem1
            // 
            this.viewNavigatorZoomInItem1.Glyph = ((System.Drawing.Image)(resources.GetObject("viewNavigatorZoomInItem1.Glyph")));
            this.viewNavigatorZoomInItem1.GroupIndex = 1;
            this.viewNavigatorZoomInItem1.Id = 13;
            this.viewNavigatorZoomInItem1.ItemShortcut = new DevExpress.XtraBars.BarShortcut((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Add));
            this.viewNavigatorZoomInItem1.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("viewNavigatorZoomInItem1.LargeGlyph")));
            this.viewNavigatorZoomInItem1.Name = "viewNavigatorZoomInItem1";
            // 
            // viewNavigatorZoomOutItem1
            // 
            this.viewNavigatorZoomOutItem1.Glyph = ((System.Drawing.Image)(resources.GetObject("viewNavigatorZoomOutItem1.Glyph")));
            this.viewNavigatorZoomOutItem1.GroupIndex = 1;
            this.viewNavigatorZoomOutItem1.Id = 14;
            this.viewNavigatorZoomOutItem1.ItemShortcut = new DevExpress.XtraBars.BarShortcut((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Subtract));
            this.viewNavigatorZoomOutItem1.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("viewNavigatorZoomOutItem1.LargeGlyph")));
            this.viewNavigatorZoomOutItem1.Name = "viewNavigatorZoomOutItem1";
            // 
            // viewSelector1
            // 
            this.viewSelector1.BarManager = this.barManager1;
            this.viewSelector1.SchedulerControl = this.schedulerControl1;
            // 
            // viewNavigator1
            // 
            this.viewNavigator1.BarManager = this.barManager1;
            this.viewNavigator1.SchedulerControl = this.schedulerControl1;
            
            
            // 
            // panelControl1
            // 
            this.panelControl1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowOnly;
            //this.panelControl1.Controls.Add(this.cbView);
            //this.panelControl1.Controls.Add(this.labelControl2);
            //this.panelControl1.Controls.Add(this.dateLbl);
            //this.panelControl1.Controls.Add(this.todayBtn);
            //this.panelControl1.Controls.Add(this.nextBtn);
            //this.panelControl1.Controls.Add(this.previousBtn);

            this.panelControl1.Controls.Add(this.barDockControlLeft);
            this.panelControl1.Controls.Add(this.barDockControlRight);
            this.panelControl1.Controls.Add(this.barDockControlBottom);
            this.panelControl1.Controls.Add(this.barDockControlTop);

            this.panelControl1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panelControl1.Location = new System.Drawing.Point(0, 0);
            this.panelControl1.Name = "panelControl1";
            this.panelControl1.Size = new System.Drawing.Size(566, 0);
            this.panelControl1.TabIndex = 2;
            // 
            // cbView
            // 
            this.cbView.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.cbView.EditValue = DevExpress.XtraScheduler.SchedulerViewType.Day;
            this.cbView.Location = new System.Drawing.Point(446, 3);
            this.cbView.Name = "cbView";
            this.cbView.Properties.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.cbView.Properties.Items.AddRange(new DevExpress.XtraEditors.Controls.ImageComboBoxItem[] {
            new DevExpress.XtraEditors.Controls.ImageComboBoxItem("Day View", DevExpress.XtraScheduler.SchedulerViewType.Day, -1),
            new DevExpress.XtraEditors.Controls.ImageComboBoxItem("Week View", DevExpress.XtraScheduler.SchedulerViewType.Week, -1),
            new DevExpress.XtraEditors.Controls.ImageComboBoxItem("Month View", DevExpress.XtraScheduler.SchedulerViewType.Month, -1)});
            this.cbView.Size = new System.Drawing.Size(98, 20);
            this.cbView.TabIndex = 32;
            this.cbView.SelectedIndexChanged += new System.EventHandler(this.cbView_SelectedIndexChanged);
            // 
            // labelControl2
            // 
            this.labelControl2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.labelControl2.Location = new System.Drawing.Point(409, 7);
            this.labelControl2.Name = "labelControl2";
            this.labelControl2.Size = new System.Drawing.Size(26, 13);
            this.labelControl2.TabIndex = 4;
            this.labelControl2.Text = "View:";
            // 
            // dateLbl
            // 
            this.dateLbl.Location = new System.Drawing.Point(112, 8);
            this.dateLbl.Name = "dateLbl";
            this.dateLbl.Size = new System.Drawing.Size(63, 13);
            this.dateLbl.TabIndex = 3;
            this.dateLbl.Text = "labelControl1";
            // 
            // todayBtn
            // 
            this.todayBtn.Location = new System.Drawing.Point(58, 4);
            this.todayBtn.Name = "todayBtn";
            this.todayBtn.Size = new System.Drawing.Size(47, 23);
            this.todayBtn.TabIndex = 2;
            this.todayBtn.Text = "Today";
            this.todayBtn.Click += new System.EventHandler(this.todayBtn_Click);
            // 
            // nextBtn
            // 
            this.nextBtn.Location = new System.Drawing.Point(32, 4);
            this.nextBtn.Name = "nextBtn";
            this.nextBtn.Size = new System.Drawing.Size(20, 23);
            this.nextBtn.TabIndex = 1;
            this.nextBtn.Text = ">";
            this.nextBtn.Click += new System.EventHandler(this.nextBtn_Click);
            // 
            // previousBtn
            // 
            this.previousBtn.Location = new System.Drawing.Point(6, 4);
            this.previousBtn.Name = "previousBtn";
            this.previousBtn.Size = new System.Drawing.Size(20, 23);
            this.previousBtn.TabIndex = 0;
            this.previousBtn.Text = "<";
            this.previousBtn.Click += new System.EventHandler(this.priviousBtn_Click);
            // 
            // ScheduleControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.schedulerControl1);
            this.Controls.Add(this.panelControl1);
            this.Name = "ScheduleControl";
            this.Size = new System.Drawing.Size(566, 554);
            ((System.ComponentModel.ISupportInitialize)(this.schedulerStorage1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.schedulerControl1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.panelControl1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.barManager1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.viewSelector1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.viewNavigator1)).EndInit();
            this.panelControl1.ResumeLayout(false);
            this.panelControl1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.cbView.Properties)).EndInit();
            this.ResumeLayout(false);

        }


        
        #endregion

        private DevExpress.XtraScheduler.SchedulerControl schedulerControl1;
        private DevExpress.XtraEditors.PanelControl panelControl1;
        private DevExpress.XtraEditors.ImageComboBoxEdit cbView;
        private DevExpress.XtraEditors.LabelControl labelControl2;
        private DevExpress.XtraEditors.LabelControl dateLbl;
        private DevExpress.XtraEditors.SimpleButton todayBtn;
        private DevExpress.XtraEditors.SimpleButton nextBtn;
        private DevExpress.XtraEditors.SimpleButton previousBtn;
        private SchedulerStorageDecorator schedulerStorage1;

        private DevExpress.XtraBars.BarDockControl barDockControlLeft;
        private DevExpress.XtraBars.BarDockControl barDockControlRight;
        private DevExpress.XtraBars.BarDockControl barDockControlBottom;
        private DevExpress.XtraBars.BarDockControl barDockControlTop;
        private DevExpress.XtraBars.BarManager barManager1;
        private DevExpress.XtraBars.Bar bar3;
        private DevExpress.XtraScheduler.UI.ViewSelectorBar viewSelectorBar1;
        private DevExpress.XtraScheduler.UI.ViewSelectorItem viewSelectorItem1;
        private DevExpress.XtraScheduler.UI.ViewSelectorItem viewSelectorItem2;
        private DevExpress.XtraScheduler.UI.ViewSelectorItem viewSelectorItem3;
        private DevExpress.XtraScheduler.UI.ViewSelectorItem viewSelectorItem4;
        private DevExpress.XtraScheduler.UI.ViewSelectorItem viewSelectorItem5;
        private DevExpress.XtraScheduler.UI.ViewSelector viewSelector1;
        private DevExpress.XtraScheduler.UI.ViewNavigator viewNavigator1;
        private DevExpress.XtraScheduler.UI.ViewNavigatorBar viewNavigatorBar1;
        private DevExpress.XtraScheduler.UI.ViewNavigatorBackwardItem viewNavigatorBackwardItem1;
        private DevExpress.XtraScheduler.UI.ViewNavigatorForwardItem viewNavigatorForwardItem1;
        private DevExpress.XtraScheduler.UI.ViewNavigatorTodayItem viewNavigatorTodayItem1;
        private DevExpress.XtraScheduler.UI.ViewNavigatorZoomInItem viewNavigatorZoomInItem1;
        private DevExpress.XtraScheduler.UI.ViewNavigatorZoomOutItem viewNavigatorZoomOutItem1;

    }
}
