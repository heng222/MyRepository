using ProWrite.Resources;
using ProWrite.UI.Controls.Common;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Dashboard
{
    partial class DashboardTree
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
            DataGate.Log.Debug("Container");
			this.components = new System.ComponentModel.Container();
            DataGate.Log.Debug("resources");
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DashboardTree));
            DataGate.Log.Debug("btnDelete");
            this.btnDelete = new DevExpress.XtraEditors.SimpleButton();
            DataGate.Log.Debug("btnAdd");
            this.btnAdd = new DevExpress.XtraEditors.SimpleButton();
            DataGate.Log.Debug("treeList");
            this.treeList = new DevExpress.XtraTreeList.TreeList();
            DataGate.Log.Debug("DashName");
            this.DashName = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            DataGate.Log.Debug("Type");
            this.Type = new DevExpress.XtraTreeList.Columns.TreeListColumn();

            DataGate.Log.Debug("Status");
            this.cStatus = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            DataGate.Log.Debug("FreeMemory");
            this.cFreeMemory = new DevExpress.XtraTreeList.Columns.TreeListColumn();

            this.cTotalSize = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.cTimeLeft = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.cPositionPlay = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.cQueueNumber = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.cMessageId = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.cScheduleId = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.cLogView = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.cSignTypeColor = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.cSignConnectionState = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            this.cMessageStatus = new DevExpress.XtraTreeList.Columns.TreeListColumn();


            DataGate.Log.Debug("Active");
            this.Active = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            DataGate.Log.Debug("SignInfo");
            this.SignInfo = new DevExpress.XtraTreeList.Columns.TreeListColumn();
            DataGate.Log.Debug("repositoryItemCheckEdit1");
            this.repositoryItemCheckEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemCheckEdit();

            this.repositoryItemPictureEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemPictureEdit();
            this.repositoryItemImageComboBox1 = new DevExpress.XtraEditors.Repository.RepositoryItemImageComboBox();

            DataGate.Log.Debug("repositoryItemImageEdit1");
            this.repositoryItemImageEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemImageEdit();
            DataGate.Log.Debug("repositoryItemButtonEdit1");
            this.repositoryItemButtonEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemButtonEdit();
            DataGate.Log.Debug("repositoryItemProgressBar1");
            this.repositoryItemProgressBar1 = new DevExpress.XtraEditors.Repository.RepositoryItemProgressBar();
            this.repositoryItemTextEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemTextEdit();
            DataGate.Log.Debug("imageList");
            this.imageList = new System.Windows.Forms.ImageList(this.components);
            this.imageListStatus = new System.Windows.Forms.ImageList(this.components);
            DataGate.Log.Debug("contextMenuStrip1");
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            DataGate.Log.Debug("newSignToolStripMenuItem");
            this.newSignToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            DataGate.Log.Debug("newSignGroupToolStripMenuItem");
            this.newSignGroupToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            DataGate.Log.Debug("contextMenuStrip2");
            this.contextMenuStrip2 = new System.Windows.Forms.ContextMenuStrip(this.components);
            DataGate.Log.Debug("addSignToolStripMenuItem");
            this.addSignToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            DataGate.Log.Debug("newSignGroupToolStripMenuItem1");
            this.newSignGroupToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            DataGate.Log.Debug("editToolStripMenuItem");
            this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            DataGate.Log.Debug("deleteToolStripMenuItem");
            this.deleteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            DataGate.Log.Debug("disConnectToolStripMenuItem");
            this.disConnectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            DataGate.Log.Debug("ConnectToolStripMenuItem");
            this.ConnectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();

            this.showLogViewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.showStatusSignToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.RefreshSignToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();

            DataGate.Log.Debug("addGroupToolStripMenuItem");
            this.addGroupToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            DataGate.Log.Debug("removeGroupToolStripMenuItem");
            this.removeGroupToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			((System.ComponentModel.ISupportInitialize)(this.treeList)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.repositoryItemCheckEdit1)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.repositoryItemImageEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemProgressBar1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemTextEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemButtonEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemPictureEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemImageComboBox1)).BeginInit();
			this.contextMenuStrip1.SuspendLayout();
			this.contextMenuStrip2.SuspendLayout();
			this.SuspendLayout();
			// 
			// btnDelete
			// 
			this.btnDelete.AllowDrop = true;
			this.btnDelete.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.btnDelete.Image = ((System.Drawing.Image)(resources.GetObject("btnDelete.Image")));
			this.btnDelete.Location = new System.Drawing.Point(34, 418);
			this.btnDelete.Name = "btnDelete";
			this.btnDelete.Size = new System.Drawing.Size(27, 31);
			this.btnDelete.TabIndex = 13;
			this.btnDelete.ToolTip = "Delete";
			this.btnDelete.Click += new System.EventHandler(this.btnDelete_Click);
			this.btnDelete.DragDrop += new System.Windows.Forms.DragEventHandler(this.btnDelete_DragDrop);
			this.btnDelete.DragLeave += new System.EventHandler(this.btnDelete_DragLeave);
			this.btnDelete.DragEnter += new System.Windows.Forms.DragEventHandler(this.btnDelete_DragEnter);
			// 
			// btnAdd
			// 
			this.btnAdd.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.btnAdd.Image = ((System.Drawing.Image)(resources.GetObject("btnAdd.Image")));
			this.btnAdd.Location = new System.Drawing.Point(3, 418);
			this.btnAdd.Name = "btnAdd";
			this.btnAdd.Size = new System.Drawing.Size(25, 31);
			this.btnAdd.TabIndex = 12;
			this.btnAdd.ToolTip = "Add";
			this.btnAdd.MouseUp += new System.Windows.Forms.MouseEventHandler(this.btnAdd_MouseUp);
			// 
			// treeList
			// 
			this.treeList.AllowDrop = true;
			this.treeList.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
						| System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.treeList.Columns.AddRange(new DevExpress.XtraTreeList.Columns.TreeListColumn[] {
            this.DashName,
            this.Type,
            this.cSignTypeColor,
            this.Active,
            this.SignInfo,
            this.cFreeMemory,
            
            this.cSignConnectionState,
            
            //this.cTotalSize,
            //this.cTimeLeft,
            //this.cPositionPlay,
            //this.cQueueNumber,
            this.cMessageId,
            this.cMessageStatus
            //this.cStatus
            //this.cScheduleId,
            //this.cLogView
            });
			this.treeList.FixedLineWidth = 1;
			this.treeList.ImageIndexFieldName = "";
			this.treeList.Location = new System.Drawing.Point(0, -2);
			this.treeList.LookAndFeel.SkinName = "Lilian";
			this.treeList.Name = "treeList";
			this.treeList.OptionsBehavior.AutoChangeParent = false;
			this.treeList.OptionsBehavior.AutoPopulateColumns = false;
			this.treeList.OptionsBehavior.AutoSelectAllInEditor = false;
			this.treeList.OptionsBehavior.DragNodes = true;
			this.treeList.OptionsBehavior.Editable = false;
			this.treeList.OptionsBehavior.EnableFiltering = true;
			this.treeList.OptionsBehavior.ImmediateEditor = false;
			this.treeList.OptionsBehavior.KeepSelectedOnClick = false;
			this.treeList.OptionsBehavior.MoveOnEdit = false;
			this.treeList.OptionsMenu.EnableColumnMenu = false;
			this.treeList.OptionsMenu.EnableFooterMenu = false;
            this.treeList.OptionsSelection.MultiSelect = false;
            this.treeList.OptionsSelection.EnableAppearanceFocusedCell = false;
			this.treeList.RepositoryItems.AddRange(new DevExpress.XtraEditors.Repository.RepositoryItem[] {
            this.repositoryItemCheckEdit1,
            this.repositoryItemImageEdit1,
            this.repositoryItemProgressBar1,
            this.repositoryItemTextEdit1,
            this.repositoryItemButtonEdit1,
            this.repositoryItemPictureEdit1,
            this.repositoryItemImageComboBox1});
			this.treeList.Size = new System.Drawing.Size(415, 414);
			this.treeList.StateImageList = this.imageList;
			this.treeList.TabIndex = 3;
			this.treeList.TreeLineStyle = DevExpress.XtraTreeList.LineStyle.None;
			this.treeList.MouseDown += new System.Windows.Forms.MouseEventHandler(this.treeList_MouseDown);
			this.treeList.DragCancelNode += new System.EventHandler(this.treeList_DragCancelNode);
			this.treeList.GetStateImage += new DevExpress.XtraTreeList.GetStateImageEventHandler(this.treeList_GetStateImage);
			this.treeList.DragObjectStart += new DevExpress.XtraTreeList.DragObjectStartEventHandler(this.treeList_DragObjectStart);
			this.treeList.KeyUp += new System.Windows.Forms.KeyEventHandler(this.treeList_KeyUp);
			this.treeList.DoubleClick += new System.EventHandler(this.treeList_DoubleClick);
			this.treeList.DragDrop += new System.Windows.Forms.DragEventHandler(this.treeList_DragDrop);
			this.treeList.GiveFeedback += new System.Windows.Forms.GiveFeedbackEventHandler(this.treeList_GiveFeedback);
            this.treeList.DragEnter += new System.Windows.Forms.DragEventHandler(treeList_DragEnter);
            this.treeList.CustomNodeCellEdit += new DevExpress.XtraTreeList.GetCustomNodeCellEditEventHandler(treeList_CustomNodeCellEdit);
            
            // 
			// DashName
			// 
			this.DashName.Caption = "Name";
			this.DashName.FieldName = "Name";
			this.DashName.Name = "DashName";
            this.DashName.AppearanceHeader.Options.UseTextOptions = true;
            this.DashName.AppearanceHeader.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
			this.DashName.OptionsColumn.AllowEdit = false;
			this.DashName.Visible = true;
			this.DashName.VisibleIndex = 0;
			this.DashName.Width = 150;
			// 
			// Type
			//  
			this.Type.Caption = "Type";
			this.Type.FieldName = "Type";
			this.Type.Name = "Type";
            this.Type.AppearanceHeader.Options.UseTextOptions = true;
            this.Type.AppearanceHeader.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
			this.Type.OptionsColumn.AllowEdit = false;
			this.Type.Visible = true;
			this.Type.VisibleIndex = 1;

            
            // 
            // cStatus
            //  
            this.cStatus.Caption = "Status";
            this.cStatus.FieldName = "Status";
            this.cStatus.Name = "Status";
            this.cStatus.ColumnEdit = this.repositoryItemImageComboBox1;
            //this.cStatus.AppearanceHeader.Options.UseTextOptions = true;
            //this.cStatus.AppearanceHeader.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.cStatus.OptionsColumn.AllowEdit = true;
            this.cStatus.Visible = true;
            this.cStatus.VisibleIndex = 6;
            // 
            // repositoryItemPictureEdit1
            // 
            this.repositoryItemPictureEdit1.Name = "repositoryItemPictureEdit1";
            // 
            // repositoryItemImageComboBox1
            // 
            //this.repositoryItemImageComboBox1.AllowFocused = false;
            //this.repositoryItemImageComboBox1.AutoHeight = false;
            this.repositoryItemImageComboBox1.SmallImages = this.imageListStatus;
            //this.repositoryItemImageComboBox1.NullText = "";
            this.repositoryItemImageComboBox1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.repositoryItemImageComboBox1.Items.AddRange(new DevExpress.XtraEditors.Controls.ImageComboBoxItem[] {
            new DevExpress.XtraEditors.Controls.ImageComboBoxItem("", SignType.Red.ToString().ToLower(), 0),
            new DevExpress.XtraEditors.Controls.ImageComboBoxItem("", SignType.Green.ToString().ToLower(), 1),
            new DevExpress.XtraEditors.Controls.ImageComboBoxItem("", "yellow", 2),
            });

            this.repositoryItemImageComboBox1.Name = "repositoryItemImageComboBox1";
            this.repositoryItemImageComboBox1.Buttons[0].Visible = false;
            this.repositoryItemImageComboBox1.SelectedIndexChanged += new System.EventHandler(repositoryItemImageComboBox1_SelectedIndexChanged);
            this.repositoryItemImageComboBox1.MouseDown += new System.Windows.Forms.MouseEventHandler(repositoryItemImageComboBox1_MouseDown);
            // 
            // cTotalSize
            //  
            this.cTotalSize.Caption = "Total Size";
            this.cTotalSize.FieldName = "TotalSize";
            this.cTotalSize.Name = "cTotalSize";
            this.cTotalSize.AppearanceHeader.Options.UseTextOptions = true;
            this.cTotalSize.AppearanceHeader.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.cTotalSize.OptionsColumn.AllowEdit = false;
            this.cTotalSize.Visible = true;
            this.cTotalSize.VisibleIndex = 50;
            // 
            // cTimeLeft
            //  
            this.cTimeLeft.Caption = "Time Left";
            this.cTimeLeft.FieldName = "TimeLeft";
            this.cTimeLeft.Name = "cTimeLeft";
            this.cTimeLeft.AppearanceHeader.Options.UseTextOptions = true;
            this.cTimeLeft.AppearanceHeader.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.cTimeLeft.OptionsColumn.AllowEdit = false;
            this.cTimeLeft.Visible = true;
            this.cTimeLeft.VisibleIndex = 50;
            // 
            // cPositionPlay
            //  
            this.cPositionPlay.Caption = "Position";
            this.cPositionPlay.FieldName = "Position";
            this.cPositionPlay.Name = "cPositionPlay";
            this.cPositionPlay.AppearanceHeader.Options.UseTextOptions = true;
            this.cPositionPlay.AppearanceHeader.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.cPositionPlay.OptionsColumn.AllowEdit = false;
            this.cPositionPlay.Visible = true;
            this.cPositionPlay.VisibleIndex = 50;
            // 
            // cQueueNumber
            //  
            this.cQueueNumber.Caption = "Queue Number";
            this.cQueueNumber.FieldName = "QueueNumber";
            this.cQueueNumber.Name = "cQueueNumber";
            this.cQueueNumber.AppearanceHeader.Options.UseTextOptions = true;
            this.cQueueNumber.AppearanceHeader.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.cQueueNumber.OptionsColumn.AllowEdit = false;
            this.cQueueNumber.Visible = true;
            this.cQueueNumber.VisibleIndex = 50;
            // 
            // cMessageId;
            //  
            this.cMessageId.Caption = "Current Message";
            this.cMessageId.FieldName = "MessageIdInfo";
            this.cMessageId.Name = "cMessageId";
            this.cMessageId.AppearanceHeader.Options.UseTextOptions = true;
            this.cMessageId.AppearanceHeader.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.cMessageId.OptionsColumn.AllowEdit = false;
            this.cMessageId.Visible = true;
            this.cMessageId.VisibleIndex = 8;
            // 
            // cMessageStatus;
            //  
            this.cMessageStatus.Caption = "Message Status";
            this.cMessageStatus.FieldName = "MessageStatus";
            this.cMessageStatus.Name = "cMessageStatus";
            this.cMessageStatus.AppearanceHeader.Options.UseTextOptions = true;
            this.cMessageStatus.AppearanceHeader.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.cMessageStatus.OptionsColumn.AllowEdit = false;
            this.cMessageStatus.Visible = true;
            this.cMessageStatus.VisibleIndex = 7;
            // 
            // cScheduleId;
            //  
            this.cScheduleId.Caption = "Message Status";
            this.cScheduleId.FieldName = "MessageStatus";
            this.cScheduleId.Name = "cScheduleId";
            this.cScheduleId.AppearanceHeader.Options.UseTextOptions = true;
            this.cScheduleId.AppearanceHeader.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.cScheduleId.OptionsColumn.AllowEdit = false;
            this.cScheduleId.Visible = true;
            this.cScheduleId.VisibleIndex = 50;
            // 
            // cLogView;
            //  
            this.cLogView.Caption = "LogView";
            this.cLogView.FieldName = "ShowLogView";
            this.cLogView.ColumnEdit = this.repositoryItemButtonEdit1;
            this.cLogView.Name = "cLogView";
            this.cLogView.AppearanceHeader.Options.UseTextOptions = true;
            this.cLogView.AppearanceHeader.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.cLogView.AppearanceCell.Options.UseTextOptions = true;
            this.cLogView.AppearanceCell.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            //this.cLogView.OptionsColumn.AllowEdit = false;
            this.cLogView.Visible = false;
            this.cLogView.VisibleIndex = 50;

            // 
            // cSignTypeColor;
            //  
            this.cSignTypeColor.Caption = "Color";
            this.cSignTypeColor.FieldName = "SignTypeColor";
            this.cSignTypeColor.ColumnEdit = this.repositoryItemButtonEdit1;
            this.cSignTypeColor.Name = "cSignTypeColor";
            this.cSignTypeColor.AppearanceHeader.Options.UseTextOptions = true;
            this.cSignTypeColor.AppearanceHeader.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.cSignTypeColor.AppearanceCell.Options.UseTextOptions = true;
            this.cSignTypeColor.AppearanceCell.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            //this.cLogView.OptionsColumn.AllowEdit = false;
            this.cSignTypeColor.Visible = false;
            this.cSignTypeColor.VisibleIndex = 2;
            // 
            // cSignConnectionState;
            //  
            this.cSignConnectionState.Caption = "Connection";
            this.cSignConnectionState.FieldName = "IsConnected";
            this.cSignConnectionState.ColumnEdit = this.repositoryItemButtonEdit1;
            this.cSignConnectionState.Name = "cSignConnectionState";
            this.cSignConnectionState.AppearanceHeader.Options.UseTextOptions = true;
            this.cSignConnectionState.AppearanceHeader.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.cSignConnectionState.AppearanceCell.Options.UseTextOptions = true;
            this.cSignConnectionState.AppearanceCell.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            //this.cLogView.OptionsColumn.AllowEdit = false;
            this.cSignConnectionState.Visible = false;
            this.cSignConnectionState.VisibleIndex = 4;
            // 
            // DashName
            // 
            this.SignInfo.Caption = "Resolution";
            this.SignInfo.FieldName = "SignInfomation";
            this.SignInfo.Name = "SignInfo";
            this.SignInfo.AppearanceHeader.Options.UseTextOptions = true;
            this.SignInfo.AppearanceHeader.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.SignInfo.OptionsColumn.AllowEdit = false;
            this.SignInfo.Visible = true;
            this.SignInfo.VisibleIndex = 3;
            this.SignInfo.Width = 70;
			// 
			// Active
			// 
			this.Active.Caption = "Active";
			this.Active.ColumnEdit = this.repositoryItemCheckEdit1;
			this.Active.FieldName = "Active";
			this.Active.ImageAlignment = System.Drawing.StringAlignment.Center;
			this.Active.ImageIndex = 0;
			this.Active.Name = "Active";
			this.Active.Visible = true;
			this.Active.VisibleIndex = 5;
			this.Active.Width = 20;
            Active.Visible = false;

            // 
            // FreeMemory
            //  
            this.cFreeMemory.Caption = "Free Memory";
            this.cFreeMemory.ColumnEdit =  this.repositoryItemProgressBar1;
            this.cFreeMemory.FieldName = "FreeMemory";
            this.cFreeMemory.Name = "FreeMemory";
            this.cFreeMemory.AppearanceHeader.Options.UseTextOptions = true;
            this.cFreeMemory.AppearanceHeader.TextOptions.HAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.cFreeMemory.OptionsColumn.AllowEdit = false;
            this.cFreeMemory.Visible = true;
            this.cFreeMemory.VisibleIndex = 5;
			// 
			// repositoryItemCheckEdit1
			// 
			this.repositoryItemCheckEdit1.AutoHeight = false;
			this.repositoryItemCheckEdit1.Name = "repositoryItemCheckEdit1";
			this.repositoryItemCheckEdit1.NullStyle = DevExpress.XtraEditors.Controls.StyleIndeterminate.Unchecked;
            // 
            // repositoryItemProgressBar1
            // 
            //this.repositoryItemProgressBar1.EndColor = System.Drawing.Color.OldLace;
            this.repositoryItemProgressBar1.Name = "repositoryItemProgressBar1";
            this.repositoryItemProgressBar1.ShowTitle = true;
            //this.repositoryItemProgressBar1.StartColor = System.Drawing.Color.DarkKhaki;
            // 
            // repositoryItemTextEdit1
            // 
            this.repositoryItemTextEdit1.AllowFocused = false;
            this.repositoryItemTextEdit1.AutoHeight = false;
            this.repositoryItemTextEdit1.Mask.EditMask = "(999)000-0000";
            this.repositoryItemTextEdit1.Mask.MaskType = DevExpress.XtraEditors.Mask.MaskType.Simple;
            this.repositoryItemTextEdit1.Name = "repositoryItemTextEdit1";
            this.repositoryItemTextEdit1.NullText = "N/A";
            // 
			// repositoryItemImageEdit1
			// 
			this.repositoryItemImageEdit1.AutoHeight = false;
			this.repositoryItemImageEdit1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
			this.repositoryItemImageEdit1.Name = "repositoryItemImageEdit1";

            // 
            // repositoryItemImageEdit1
            // 
            this.repositoryItemButtonEdit1.AutoHeight = false;
            repositoryItemButtonEdit1.Click += new System.EventHandler(repositoryItemButtonEdit1_Click);
            repositoryItemButtonEdit1.TextEditStyle = DevExpress.XtraEditors.Controls.TextEditStyles.Standard;
            repositoryItemButtonEdit1.NullText = "Show Log View";
            //this.repositoryItemButtonEdit1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            //new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.)});
            this.repositoryItemButtonEdit1.Name = "repositoryItemButtonEdit1";
			// 
			// imageList
			// 
            //this.imageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList.ImageStream")));
			this.imageList.TransparentColor = System.Drawing.Color.Magenta;
            imageList.Images.Add(Resources.Resource.GetImage(Resources.Resource.Images.SignGroup));
            imageList.Images.Add(Resources.Resource.GetImage(Resources.Resource.Images.TabPageDashBoard));
            imageList.Images.Add(Resources.Resource.GetImage(Resources.Resource.Images.SignConnectNew));
            //this.imageList.Images.SetKeyName(0, "group.png");
            //this.imageList.Images.SetKeyName(1, "sign.png");
            //this.imageList.Images.SetKeyName(2, "SignConnectNew.png");

            imageListStatus.TransparentColor = System.Drawing.Color.Magenta;
            imageListStatus.Images.Add(Resources.Resource.GetImage(Resources.Resource.Images.RedStatus));
            imageListStatus.Images.Add(Resources.Resource.GetImage(Resources.Resource.Images.GreenStatus));
            imageListStatus.Images.Add(Resources.Resource.GetImage(Resources.Resource.Images.YellowStatus));
			// 
			// contextMenuStrip1
			// 
			this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newSignToolStripMenuItem,
            this.newSignGroupToolStripMenuItem});
			this.contextMenuStrip1.Name = "contextMenuStrip1";
			this.contextMenuStrip1.Size = new System.Drawing.Size(151, 48);
			// 
			// newSignToolStripMenuItem
			// 
			this.newSignToolStripMenuItem.Name = "newSignToolStripMenuItem";
			this.newSignToolStripMenuItem.Size = new System.Drawing.Size(150, 22);
			this.newSignToolStripMenuItem.Text = "New Sign";
			this.newSignToolStripMenuItem.Click += new System.EventHandler(this.newSignToolStripMenuItem_Click);
            this.newSignToolStripMenuItem.Image = Resources.Resource.GetImage(Resources.Resource.Images.NewSign16);
            // 
			// newSignGroupToolStripMenuItem
			// 
			this.newSignGroupToolStripMenuItem.Name = "newSignGroupToolStripMenuItem";
			this.newSignGroupToolStripMenuItem.Size = new System.Drawing.Size(150, 22);
			this.newSignGroupToolStripMenuItem.Text = "New Sign Group";
			this.newSignGroupToolStripMenuItem.Click += new System.EventHandler(this.newSignGroupToolStripMenuItem_Click);
            this.newSignGroupToolStripMenuItem.Image = Resources.Resource.GetImage(Resources.Resource.Images.NewSignGroup16);
            // 
			// contextMenuStrip2
			// 
			this.contextMenuStrip2.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addSignToolStripMenuItem,
            this.newSignGroupToolStripMenuItem1,
            this.editToolStripMenuItem,
            this.deleteToolStripMenuItem,
            this.addGroupToolStripMenuItem,
            this.removeGroupToolStripMenuItem,
            this.disConnectToolStripMenuItem,
            this.ConnectToolStripMenuItem,
            this.RefreshSignToolStripMenuItem,
            this.showStatusSignToolStripMenuItem,
            this.showLogViewToolStripMenuItem});
			this.contextMenuStrip2.Name = "contextMenuStrip2";
			this.contextMenuStrip2.Size = new System.Drawing.Size(190, 136);
			// 
			// addSignToolStripMenuItem
			// 
			this.addSignToolStripMenuItem.Name = "addSignToolStripMenuItem";
			this.addSignToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
			this.addSignToolStripMenuItem.Text = "New Sign";
			this.addSignToolStripMenuItem.Click += new System.EventHandler(this.newSignToolStripMenuItem_Click);
            this.addSignToolStripMenuItem.Image = Resources.Resource.GetImage(Resources.Resource.Images.NewSign16);
            // 
			// newSignGroupToolStripMenuItem1
			// 
			this.newSignGroupToolStripMenuItem1.Name = "newSignGroupToolStripMenuItem1";
			this.newSignGroupToolStripMenuItem1.Size = new System.Drawing.Size(189, 22);
			this.newSignGroupToolStripMenuItem1.Text = "New Sign Group";
			this.newSignGroupToolStripMenuItem1.Click += new System.EventHandler(this.newSignGroupToolStripMenuItem1_Click);
            this.newSignGroupToolStripMenuItem1.Image = Resources.Resource.GetImage(Resources.Resource.Images.NewSignGroup16);
            // 
			// editToolStripMenuItem
			// 
			this.editToolStripMenuItem.Name = "editToolStripMenuItem";
			this.editToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
			this.editToolStripMenuItem.Text = "Edit";
			this.editToolStripMenuItem.Click += new System.EventHandler(this.editToolStripMenuItem_Click);
            this.editToolStripMenuItem.Image = Resources.Resource.GetImage(Resources.Resource.Images.Edit16);
            // 
			// deleteToolStripMenuItem
			// 
            this.disConnectToolStripMenuItem.Name = "disConnectToolStripMenuItem";
            this.disConnectToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
            this.disConnectToolStripMenuItem.Text = "DisConnect";
            this.disConnectToolStripMenuItem.Click += new System.EventHandler(disConnectToolStripMenuItem_Click);
            this.disConnectToolStripMenuItem.Image = Resources.Resource.GetImage(Resources.Resource.Images.Disconnect16);
            // 
            // ConnectToolStripMenuItem
            // 
            this.ConnectToolStripMenuItem.Name = "ConnectToolStripMenuItem";
            this.ConnectToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
            this.ConnectToolStripMenuItem.Text = "Connect";
            this.ConnectToolStripMenuItem.Click += new System.EventHandler(ConnectToolStripMenuItem_Click);
            this.ConnectToolStripMenuItem.Image = Resources.Resource.GetImage(Resources.Resource.Images.Connect16);
            this.ConnectToolStripMenuItem.Visible = false;

            // 
            // showLogViewToolStripMenuItem
            // 
            this.showLogViewToolStripMenuItem.Name = "showLogViewToolStripMenuItem";
            this.showLogViewToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
            this.showLogViewToolStripMenuItem.Text = "Show log view details";
            this.showLogViewToolStripMenuItem.Click += new System.EventHandler(showLogViewToolStripMenuItem_Click);
            this.showLogViewToolStripMenuItem.Image = Resources.Resource.GetImage(Resources.Resource.Images.Connect16);
            this.showLogViewToolStripMenuItem.Visible = false;
            // 
            // showStatusSignToolStripMenuItem
            // 
            this.showStatusSignToolStripMenuItem.Name = "showStatusSignToolStripMenuItem";
            this.showStatusSignToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
            this.showStatusSignToolStripMenuItem.Text = "Show status details";
            this.showStatusSignToolStripMenuItem.Click += new System.EventHandler(showStatusSignToolStripMenuItem_Click);
            this.showStatusSignToolStripMenuItem.Image = Resources.Resource.GetImage(Resources.Resource.Images.Connect16);
            this.showStatusSignToolStripMenuItem.Visible = false;
            // 
            // RefreshSignToolStripMenuItem
            // 
            this.RefreshSignToolStripMenuItem.Name = "RefreshSignToolStripMenuItem";
            this.RefreshSignToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
            this.RefreshSignToolStripMenuItem.Text = "Refresh";
            this.RefreshSignToolStripMenuItem.Click += new System.EventHandler(RefreshSignToolStripMenuItem_Click);
            this.RefreshSignToolStripMenuItem.Image = Resources.Resource.GetImage(Resources.Resource.Images.Connect16);
            this.RefreshSignToolStripMenuItem.Visible = false;

            // 
            // deleteToolStripMenuItem
            // 
            this.deleteToolStripMenuItem.Name = "deleteToolStripMenuItem";
            this.deleteToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
            this.deleteToolStripMenuItem.Text = "Delete";
            this.deleteToolStripMenuItem.Click += new System.EventHandler(this.deleteToolStripMenuItem_Click);
            this.deleteToolStripMenuItem.Image = Resources.Resource.GetImage(Resources.Resource.Images.Delete16);
            // 
			// addGroupToolStripMenuItem
			// 
			this.addGroupToolStripMenuItem.Name = "addGroupToolStripMenuItem";
			this.addGroupToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
			this.addGroupToolStripMenuItem.Text = "Add to group";
			this.addGroupToolStripMenuItem.Click += new System.EventHandler(this.addGroupToolStripMenuItem_Click);
            this.addGroupToolStripMenuItem.Image = Resources.Resource.GetImage(Resources.Resource.Images.AddToGroup);
            // 
			// removeGroupToolStripMenuItem
			// 
			this.removeGroupToolStripMenuItem.Name = "removeGroupToolStripMenuItem";
			this.removeGroupToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
			this.removeGroupToolStripMenuItem.Text = "Remove from this group";
			this.removeGroupToolStripMenuItem.Click += new System.EventHandler(this.removeGroupToolStripMenuItem_Click);
            this.removeGroupToolStripMenuItem.Image = Resources.Resource.GetImage(Resources.Resource.Images.Removefromthisgroup);

			// 
			// DashboardTree
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.treeList);
			this.Controls.Add(this.btnAdd);
			this.Controls.Add(this.btnDelete);
			this.Name = "DashboardTree";
			this.Size = new System.Drawing.Size(415, 452);
			((System.ComponentModel.ISupportInitialize)(this.treeList)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.repositoryItemCheckEdit1)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.repositoryItemImageEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemProgressBar1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemTextEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemPictureEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemImageComboBox1)).EndInit();
			this.contextMenuStrip1.ResumeLayout(false);
			this.contextMenuStrip2.ResumeLayout(false);
			this.ResumeLayout(false);

        }

        void repositoryItemImageComboBox1_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            //throw new System.NotImplementedException();
        }

        void repositoryItemImageComboBox1_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            
        }

        

        

        #endregion

		private DevExpress.XtraEditors.SimpleButton btnDelete;
        private DevExpress.XtraEditors.SimpleButton btnAdd;
        private DevExpress.XtraTreeList.TreeList treeList;
        private DevExpress.XtraTreeList.Columns.TreeListColumn DashName;
        private DevExpress.XtraTreeList.Columns.TreeListColumn Type;
        private DevExpress.XtraTreeList.Columns.TreeListColumn SignInfo;
        private DevExpress.XtraTreeList.Columns.TreeListColumn Active;

        private DevExpress.XtraTreeList.Columns.TreeListColumn cFreeMemory;
        private DevExpress.XtraTreeList.Columns.TreeListColumn cStatus;
        private DevExpress.XtraTreeList.Columns.TreeListColumn cTotalSize;
        private DevExpress.XtraTreeList.Columns.TreeListColumn cTimeLeft;
        private DevExpress.XtraTreeList.Columns.TreeListColumn cPositionPlay;
        private DevExpress.XtraTreeList.Columns.TreeListColumn cQueueNumber;
        private DevExpress.XtraTreeList.Columns.TreeListColumn cMessageId;
        private DevExpress.XtraTreeList.Columns.TreeListColumn cScheduleId;
        private DevExpress.XtraTreeList.Columns.TreeListColumn cLogView;
        private DevExpress.XtraTreeList.Columns.TreeListColumn cSignTypeColor;
        private DevExpress.XtraTreeList.Columns.TreeListColumn cSignConnectionState;
        private DevExpress.XtraTreeList.Columns.TreeListColumn cMessageStatus;

        private DevExpress.XtraEditors.Repository.RepositoryItemProgressBar repositoryItemProgressBar1;
        private DevExpress.XtraEditors.Repository.RepositoryItemCheckEdit repositoryItemCheckEdit1;
        private DevExpress.XtraEditors.Repository.RepositoryItemImageEdit repositoryItemImageEdit1;
        private DevExpress.XtraEditors.Repository.RepositoryItemButtonEdit repositoryItemButtonEdit1;
        private DevExpress.XtraEditors.Repository.RepositoryItemPictureEdit repositoryItemPictureEdit1;
        private DevExpress.XtraEditors.Repository.RepositoryItemImageComboBox repositoryItemImageComboBox1;
        private DevExpress.XtraEditors.Repository.RepositoryItemTextEdit repositoryItemTextEdit1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem newSignToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newSignGroupToolStripMenuItem;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip2;
        private System.Windows.Forms.ToolStripMenuItem addSignToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newSignGroupToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem deleteToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem disConnectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ConnectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem showLogViewToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem RefreshSignToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem showStatusSignToolStripMenuItem;
        private System.Windows.Forms.ImageList imageList;
        private System.Windows.Forms.ImageList imageListStatus;
        private System.Windows.Forms.ToolStripMenuItem addGroupToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem removeGroupToolStripMenuItem;
    }
}
