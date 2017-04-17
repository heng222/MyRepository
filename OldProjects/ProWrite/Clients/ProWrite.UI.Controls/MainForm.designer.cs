using System.Drawing;
using DevExpress.XtraBars;
using DevExpress.XtraBars.Ribbon;
using ProWrite.Resources;
using DevExpress.XtraBars.Docking;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.Editor;
using System;

//using ProWrite.Resources;

namespace ProWrite.UI.Controls
{
	partial class MainForm
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;


		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.ribbonControl1 = new DevExpress.XtraBars.Ribbon.RibbonControl();
            this.popupMenuMain = new DevExpress.XtraBars.PopupMenu(this.components);
            this.btnSave = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnSaveAs = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnAbout= new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnHelp = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnTestCommand = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnProfaneWord = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnBatchLoad = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnImport = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnExport = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnExit = new ProWrite.UI.Controls.BarButtonItemEx();
            this.skinsBli = new DevExpress.XtraBars.BarListItem();
            this.btnEditorNewMessage = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnPlayListNew = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnNewSchedule = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnNewLibrary = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnNewTimeSliceGroup = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnDashboardEdit = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnNew = new ProWrite.UI.Controls.BarButtonItemEx();
            this.newPopDashboardMenu = new DevExpress.XtraBars.PopupMenu(this.components);
            this.newPopEditorMenu = new DevExpress.XtraBars.PopupMenu(this.components);
            this.newPopPlaylistMenu = new DevExpress.XtraBars.PopupMenu(this.components);
            this.newPopSchedulerMenu = new DevExpress.XtraBars.PopupMenu(this.components);
            this.btnDashbaordNewSign = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnDashboardNewSignGroup = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnConnect = new ProWrite.UI.Controls.BarButtonItemEx();
            //this.btnSessionLoad = new ProWrite.UI.Controls.BarButtonItemEx();
            //this.btnSessionSave = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnBlankSignSet = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnUnBlankSignSet = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnSignProperties = new ProWrite.UI.Controls.BarButtonItemEx();
            this.mnuProperties = new DevExpress.XtraBars.PopupMenu(this.components);
            this.btnSignStatus = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnChangePwd = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnSetDateTime = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnStartStopRender = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnSkipQ = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnClearQ = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnReboot = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnTimeZone = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnFactoryReset = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnBlankSign = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnTestPattern = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnDisplayMsg = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnDelete = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnEditPicture = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnDashBoardTools = new ProWrite.UI.Controls.BarButtonItemEx();
            this.toolsPopMenu = new DevExpress.XtraBars.PopupMenu(this.components);
            this.btnDimming = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnTempOffset = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnSetTime = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnViewLog = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnLiveView = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnSignPhotoView = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnRefreshView = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnDisplay = new ProWrite.UI.Controls.BarButtonItemEx();
            this.displayPopMenu = new DevExpress.XtraBars.PopupMenu(this.components);
            this.btnInsertImage = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnInsertVideo = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnInsertText = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnInsertVariableText = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnInsertTime = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnInsertTemperature = new ProWrite.UI.Controls.BarButtonItemEx();
            this.replacePopMenu = new DevExpress.XtraBars.PopupMenu(this.components);
            this.barButtonItem21 = new ProWrite.UI.Controls.BarButtonItemEx();
            this.barButtonItem22 = new ProWrite.UI.Controls.BarButtonItemEx();
            this.barButtonItem23 = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnDrawing = new ProWrite.UI.Controls.BarButtonItemEx();
            this.drawingPopMenu = new DevExpress.XtraBars.PopupMenu(this.components);
            this.btnRectangle = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnEllipse = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnArrowUp = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnArrowDown = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnArrowRight = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnArrowLeft = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnFill = new ProWrite.UI.Controls.ColorBarItem();
            this.btnLinecolor = new ProWrite.UI.Controls.ColorBarItem();
            this.btnPen = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnEraser = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnSendInEditor = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnSendInPlaylist = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnSendInScheduler = new ProWrite.UI.Controls.BarButtonItemEx();
            this.sendPopMenuEditor = new DevExpress.XtraBars.PopupMenu(this.components);
            this.sendPopMenuPlaylist = new DevExpress.XtraBars.PopupMenu(this.components);
            this.sendPopMenuScheduler = new DevExpress.XtraBars.PopupMenu(this.components);
            this.btnSendSign = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnSendMessagetoSign = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnSendPlayListtoSign = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnSendPlaylist = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnSendSchedule = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnSendLive = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnProperties = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnInsertPlayList = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnInsertMessage = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnInsertTimeSliceGrp = new ProWrite.UI.Controls.BarButtonItemEx();
            this.barButtonItem58 = new ProWrite.UI.Controls.BarButtonItemEx();
            this.barButtonItem59 = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnScheduleInsertPlaylist = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnScheduleInsertMessage = new ProWrite.UI.Controls.BarButtonItemEx();
            this.barButtonItem63 = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnSystemInit = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnSystemDefault = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnUserManager = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnRedo = new ProWrite.UI.Controls.BarButtonItemEx();
            this.mnuRedoActionList = new DevExpress.XtraBars.PopupMenu(this.components);
            this.btnUndo = new ProWrite.UI.Controls.BarButtonItemEx();
            this.mnuUndoActionList = new DevExpress.XtraBars.PopupMenu(this.components);
            this.btnCopy = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnPaste = new ProWrite.UI.Controls.BarButtonItemEx();
            this.cmbSign = new ProWrite.UI.Controls.BarEditItemEx();
            this.cmbSession = new ProWrite.UI.Controls.BarEditItemEx();
            this.btnBold = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnItalic = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnAlignLeft = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnCenter = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnAlignRight = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnFontColor = new ProWrite.UI.Controls.ColorBarItem();
            this.btnBackGroundColor = new ProWrite.UI.Controls.ColorBarItem();
            this.btnTextFrameFixed = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnFontSizeFixed = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnWindows = new ProWrite.UI.Controls.BarButtonItemEx();
            this.windowsList = new DevExpress.XtraBars.PopupMenu(this.components);
            this.barBtnGrpTextColor = new DevExpress.XtraBars.BarButtonGroup();
            this.barBtnGrpTextAlign = new DevExpress.XtraBars.BarButtonGroup();
            this.barBtnGrpTextFixed = new DevExpress.XtraBars.BarButtonGroup();
            this.btnTextFontName = new ProWrite.UI.Controls.BarEditItemEx();
            this.cmbTextFontName = new DevExpress.XtraEditors.Repository.RepositoryItemComboBox();
            this.textNameSuperTip = new DevExpress.Utils.SuperToolTip();
            this.textNameTipTitle = new DevExpress.Utils.ToolTipTitleItem();
            this.textNameTipItem = new DevExpress.Utils.ToolTipItem();
            this.textSizeSuperTip = new DevExpress.Utils.SuperToolTip();
            this.textSizeTipTitle = new DevExpress.Utils.ToolTipTitleItem();
            this.textSizeTipItem = new DevExpress.Utils.ToolTipItem();
            this.btnTextFontSize = new ProWrite.UI.Controls.BarEditItemEx();
            this.cmbTextFontSize = new DevExpress.XtraEditors.Repository.RepositoryItemComboBox();
            this.btnLine = new ProWrite.UI.Controls.BarButtonItemEx();
            this.barBtnGrpPaintLine = new DevExpress.XtraBars.BarButtonGroup();
            this.btnPointer = new ProWrite.UI.Controls.BarButtonItemEx();
            this.barBtnGrpPaintShape = new DevExpress.XtraBars.BarButtonGroup();
            this.barEditTextEffect = new ProWrite.UI.Controls.BarEditItemEx();
            this.repositoryItemTextEffectEdit = new ProWrite.UI.Controls.Editor.RepositoryItemTextEffectEdit();
            this.barBtnGrpTextBoldItalic = new DevExpress.XtraBars.BarButtonGroup();
            this.btnOpen = new ProWrite.UI.Controls.BarButtonItemEx();
            this.mnuOpen = new DevExpress.XtraBars.PopupMenu(this.components);
            this.btnOpenFile = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnOpenLibrary = new ProWrite.UI.Controls.BarButtonItemEx();
            this.barBtnGrpNew = new DevExpress.XtraBars.BarButtonGroup();
            this.btnView = new ProWrite.UI.Controls.BarButtonItemEx();
            this.mnuView = new DevExpress.XtraBars.PopupMenu(this.components);
            this.barCheckItem1 = new DevExpress.XtraBars.BarCheckItem();
            this.btnInsert = new ProWrite.UI.Controls.BarButtonItemEx();
            this.mnuInsert = new DevExpress.XtraBars.PopupMenu(this.components);
            this.btnInsertVariableVideo = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnDropDownPlaylistInsert = new ProWrite.UI.Controls.BarButtonItemEx();
            this.mnuPlaylistInsert = new DevExpress.XtraBars.PopupMenu(this.components);
            this.btnDropDownSchedulerInsert = new ProWrite.UI.Controls.BarButtonItemEx();
            this.mnuSchedulerInsert = new DevExpress.XtraBars.PopupMenu(this.components);
            this.btnClearCXCLog = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnTextKern = new ProWrite.UI.Controls.BarEditItemEx();
            this.repositoryItemKernEdit = new DevExpress.XtraEditors.Repository.RepositoryItemSpinEdit();
            this.btnTextLead = new ProWrite.UI.Controls.BarEditItemEx();
            this.repositoryItemLeadEdit = new DevExpress.XtraEditors.Repository.RepositoryItemSpinEdit();
            this.btnLiveCategoryAdd = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnLiveCategoryRemove = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnLiveCategoryRename = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnLiveItemAdd = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnLiveItemRemove = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnLiveItemRename = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnLiveCXCResourceLibrary = new ProWrite.UI.Controls.BarButtonItemEx();
            this.barButtonGroup1 = new DevExpress.XtraBars.BarButtonGroup();
            this.btnZoomIn = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnZoomOut = new ProWrite.UI.Controls.BarButtonItemEx();
            this.barLineWidth = new ProWrite.UI.Controls.BarEditItemEx();
            this.btnTestPatternExitTest = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnTestPatternHRamp = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnTestPatternVRamp = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnTestPatternCross = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnTestPatternDiagonal = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnTestPatternVertical = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnTestPatternColorBar = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnTestPatternColorGrid = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnTestPatternSolidColorRed = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnTestPatternSolidColorGreen = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnTestPatternSolidColorBlue = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnTestPatternSolidColorWhite = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnTestPatternSolidColorAmber = new ProWrite.UI.Controls.BarButtonItemEx();
            this.btnTestPatternSolidColor = new ProWrite.UI.Controls.BarButtonItemEx();
            this.popupMenu2 = new DevExpress.XtraBars.PopupMenu(this.components);
            this.popupMenu1 = new DevExpress.XtraBars.PopupMenu(this.components);

            this.InnerLineWidthSpinEdit = new DevExpress.XtraEditors.Repository.RepositoryItemSpinEdit();
            this.ribbonPageDashBoard = new RibbonPageEx();
            this.ribbonPageGroupDashBoardSystem = new PageGroupEx();
            this.ribbonPageGroupDashBoardDisplay = new PageGroupEx();
            this.ribbonPageGroupDashBoardConnect = new PageGroupEx();
            this.ribbonPageGroupDashBoardLive = new PageGroupEx();
            //this.ribbonPageGroupDashBoardTools = new PageGroupEx();
            this.ribbonPageEditor = new RibbonPageEx();
            this.ribbonPageGroupEditorSystem = new PageGroupEx();
            this.ribbonPageGroup5 = new PageGroupEx();
            this.ribbonPageGroup6 = new PageGroupEx();
            this.ribbonPageGroupEditorDrawing = new PageGroupEx();
            this.ribbonPageGroupEditorPicture = new PageGroupEx();
            this.ribbonPageGroup1 = new PageGroupEx();
            this.ribbonPageGroup3 = new PageGroupEx();
            this.ribbonPageGroupZoom = new PageGroupEx();
            this.ribbonPagePlayLists = new RibbonPageEx();
            this.ribbonPageGroupPlaylistSystem = new PageGroupEx();
            this.ribbonPageGroupPlaylistCopy = new PageGroupEx();
            this.ribbonPageGroupPlaylistSend = new PageGroupEx();
            this.ribbonPageGroup4 = new PageGroupEx();
            this.ribbonPageSchedule = new RibbonPageEx();
            this.ribbonPageGroupSchedulerSystem = new PageGroupEx();
            this.ribbonPageGroupSchedulerCopy = new PageGroupEx();
            this.ribbonPageGroup7 = new PageGroupEx();
            this.ribbonPageGroup19 = new PageGroupEx();
            //this.ribbonPageManager = new DevExpress.XtraBars.Ribbon.RibbonPage();
            //this.ribbonPageGroupManagerSystem = new PageGroupEx();
            this.ribbonPageGroup20 = new PageGroupEx();
            //this.ribbonPageLive = new DevExpress.XtraBars.Ribbon.RibbonPage();
            //this.ribbonPageGroupLiveSession = new PageGroupEx();
            //this.ribbonPageGroupLiveSystem = new PageGroupEx();
            this.ribbonPageGroupLiveCategory = new PageGroupEx();
            this.ribbonPageGroupLiveHotBtn = new PageGroupEx();
            this.ribbonPageGroupLiveLibrary = new PageGroupEx();
            this.repositoryItemTextEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemTextEdit();
            this.repositoryItemFontEdit1 = new ProWrite.UI.Controls.Editor.RepositoryItemFontEdit();
            this.repositoryItemButtonEdit2 = new DevExpress.XtraEditors.Repository.RepositoryItemButtonEdit();
            this.fontEffectListComBox = new DevExpress.XtraEditors.Repository.RepositoryItemComboBox();
            this.repositoryItemColorEdit1 = new DevExpress.XtraEditors.Repository.RepositoryItemColorEdit();
            this.ribbonStatusBar1 = new DevExpress.XtraBars.Ribbon.RibbonStatusBar();
            this.panelContainer1 = new DevExpress.XtraBars.Docking.DockPanel();
            this.barButtonGroup2 = new DevExpress.XtraBars.BarButtonGroup();
            this.barButtonGroup3 = new DevExpress.XtraBars.BarButtonGroup();
            this.repositoryItemPopupContainerEdit3 = new DevExpress.XtraEditors.Repository.RepositoryItemPopupContainerEdit();
            this.popupContainerControl1 = new FontPopupContainer(ControlService.BitMapFontList, ControlService.TrueTypeFontList);

            #region Live
            this.ribbonPageLive = new DevExpress.XtraBars.Ribbon.RibbonPage();
            this.ribbonPageGroupLiveSession = new DevExpress.XtraBars.Ribbon.RibbonPageGroup();
            this.cmbSession = new DevExpress.XtraBars.BarEditItem();
            this.repositoryItemComboBox1 = new DevExpress.XtraEditors.Repository.RepositoryItemComboBox();
            this.txtCurrentSession = new DevExpress.XtraBars.BarStaticItem();
            this.barMdiChildrenListItem1 = new DevExpress.XtraBars.BarMdiChildrenListItem();
            this.btnSessionLoad = new DevExpress.XtraBars.BarButtonItem();
            this.btnSessionSave = new DevExpress.XtraBars.BarButtonItem();
            this.btnGroup = new DevExpress.XtraBars.BarButtonGroup();
            this.btnGoLive = new BarButtonItemEx();
            this.btnSync = new BarButtonItemEx();
            this.btnSessionSetup = new BarButtonItemEx();
            this.ribbonPageGroupLibrary = new DevExpress.XtraBars.Ribbon.RibbonPageGroup();
            this.btnLibraryNew = new DevExpress.XtraBars.BarButtonItem();
            this.btnLibraryOpen = new DevExpress.XtraBars.BarButtonItem();
            this.ribbonPageGroupModify = new DevExpress.XtraBars.Ribbon.RibbonPageGroup();
            this.btnLiveProperties = new DevExpress.XtraBars.BarButtonItem();
            #endregion

            ((System.ComponentModel.ISupportInitialize)(this.popupMenuMain)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.newPopDashboardMenu)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.newPopEditorMenu)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.newPopPlaylistMenu)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.newPopSchedulerMenu)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mnuProperties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.toolsPopMenu)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.displayPopMenu)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.replacePopMenu)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.drawingPopMenu)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.sendPopMenuEditor)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.sendPopMenuPlaylist)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.sendPopMenuScheduler)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mnuRedoActionList)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mnuUndoActionList)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.windowsList)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.cmbTextFontName)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.cmbTextFontSize)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemTextEffectEdit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mnuOpen)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mnuView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mnuInsert)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mnuPlaylistInsert)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mnuSchedulerInsert)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemKernEdit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemLeadEdit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.InnerLineWidthSpinEdit)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemTextEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemFontEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemButtonEdit2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.fontEffectListComBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemColorEdit1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.popupMenu2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.popupMenu1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.popupContainerControl1)).BeginInit();
            this.popupContainerControl1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemPopupContainerEdit3)).BeginInit();

            this.SuspendLayout();
            // 
            // ribbonControl1
            // 
            this.ribbonControl1.ApplicationButtonDropDownControl = this.popupMenuMain;
            this.ribbonControl1.ApplicationButtonKeyTip = "";
		    this.ribbonControl1.ApplicationIcon = (System.Drawing.Bitmap) Resource.GetImage(Resource.Images.PWLogoG);
            this.ribbonControl1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.ribbonControl1.Categories.AddRange(new DevExpress.XtraBars.BarManagerCategory[] {
            new DevExpress.XtraBars.BarManagerCategory("Connect", new System.Guid("1178063b-26a0-4149-a78d-9904d1e12197"))});
            this.ribbonControl1.Items.AddRange(new DevExpress.XtraBars.BarItem[] {
            this.skinsBli,
            this.btnEditorNewMessage,
            this.btnPlayListNew,
            this.btnNewSchedule,
            this.btnNewLibrary,
            this.btnNewTimeSliceGroup,
            this.btnDashboardEdit,
            this.btnNew,
            this.btnExit,
            this.btnDashbaordNewSign,
            this.btnDashboardNewSignGroup,
            this.btnConnect,
            this.cmbSession,
            this.txtCurrentSession,
            this.barMdiChildrenListItem1,
            
            this.btnGroup,
            this.btnGoLive,
            this.btnSync,
            this.btnSessionSetup,
            this.btnLibraryNew,
            this.btnLibraryOpen,
            this.btnLiveProperties,
            this.btnSignProperties,
            this.btnBlankSign,
            this.btnTestPattern,
            this.btnDisplayMsg,
            this.btnDelete,
            this.btnEditPicture,
            this.btnDashBoardTools,
            this.btnDimming,
            this.btnTempOffset,
            this.btnSetTime,
            this.btnViewLog,
            this.btnLiveView,
            this.btnSignPhotoView,
            this.btnRefreshView,
            this.btnDisplay,
            this.btnBlankSignSet,
            this.btnUnBlankSignSet,
            this.btnInsertImage,
            this.btnInsertVideo,
            this.btnInsertText,
            this.btnInsertVariableText,
            this.btnInsertTime,
            this.btnInsertTemperature,
            this.barButtonItem21,
            this.barButtonItem22,
            this.barButtonItem23,
            this.btnDrawing,
            this.btnRectangle,
            this.btnEllipse,
            this.btnArrowUp,
            this.btnArrowDown,
            this.btnArrowRight,
            this.btnArrowLeft,
            this.btnFill,
            this.btnLinecolor,
            this.btnPen,
            this.btnEraser,
            this.btnSendInEditor,
            this.btnSendInPlaylist,
            this.btnSendInScheduler,
            this.btnSendLive,
            this.btnSendSign,
            this.btnSendPlaylist,
            this.btnSendSchedule,
            this.btnSendMessagetoSign,
            this.btnSendPlayListtoSign,
            this.btnProperties,
            this.btnInsertPlayList,
            this.btnInsertMessage,
            this.btnInsertTimeSliceGrp,
            this.barButtonItem58,
            this.barButtonItem59,
            this.btnScheduleInsertPlaylist,
            this.btnScheduleInsertMessage,
            this.barButtonItem63,
            this.btnSave,
            this.btnSystemInit,
            this.btnSystemDefault,
            this.btnUserManager,
            this.btnRedo,
            this.btnUndo,
            this.btnCopy,
            this.btnPaste,
            this.cmbSign,
            this.cmbSession,
            this.btnSaveAs,
            this.btnBatchLoad,
            this.btnAbout,
            this.btnHelp,
            this.btnTestCommand,
            this.btnProfaneWord,
            this.btnBold,
            this.btnItalic,
            this.btnAlignLeft,
            this.btnCenter,
            this.btnAlignRight,
            this.btnFontColor,
            this.btnBackGroundColor,
            this.btnTextFrameFixed,
            this.btnFontSizeFixed,
            this.btnWindows,
            this.barBtnGrpTextColor,
            this.barBtnGrpTextAlign,
            this.barBtnGrpTextFixed,
            this.btnTextFontName,
            this.btnTextFontSize,
            this.btnLine,
            this.barBtnGrpPaintLine,
            this.barBtnGrpPaintShape,
            this.barEditTextEffect,
            this.barBtnGrpTextBoldItalic,
            this.btnOpen,
            this.barBtnGrpNew,
            this.btnImport,
            this.btnExport,
            this.btnView,
            this.barCheckItem1,
            this.btnInsert,
            this.btnDropDownPlaylistInsert,
            this.btnDropDownSchedulerInsert,
            this.btnSignStatus,
            this.btnChangePwd,
            this.btnReboot,
            this.btnTimeZone,
            this.btnSetDateTime,
            this.btnFactoryReset,
            this.btnSkipQ,
            this.btnClearQ,
            this.btnStartStopRender,
            this.btnClearCXCLog,
            this.btnTextKern,
            this.btnTextLead,
            this.btnTestPatternExitTest,
            this.btnTestPatternHRamp,
            this.btnTestPatternVRamp,
            this.btnTestPatternCross,
            this.btnTestPatternDiagonal,
            this.btnTestPatternVertical,
            this.btnTestPatternColorBar,
            this.btnTestPatternColorGrid,
            this.btnTestPatternSolidColorRed,
            this.btnTestPatternSolidColorGreen,
            this.btnTestPatternSolidColorBlue,
            this.btnTestPatternSolidColorWhite,
            this.btnTestPatternSolidColorAmber,
            this.btnTestPatternSolidColor,
            this.btnLiveCategoryAdd,
            this.btnLiveCategoryRemove,
            this.btnLiveCategoryRename,
            this.btnLiveItemAdd,
            this.btnLiveItemRemove,
            this.btnLiveItemRename,
            this.btnLiveCXCResourceLibrary,
            this.btnInsertVariableVideo,
            this.btnOpenFile,
            this.btnOpenLibrary,
            this.barButtonGroup1,
            this.btnZoomIn,
            this.btnZoomOut,
            this.btnPointer,
            this.barLineWidth,
            this.barButtonGroup2,
            this.barButtonGroup3});
            this.ribbonControl1.ItemsVertAlign = DevExpress.Utils.VertAlignment.Center;
            this.ribbonControl1.MaxItemId = 183;
            this.ribbonControl1.Name = "ribbonControl1";
            this.ribbonControl1.Pages.AddRange(new DevExpress.XtraBars.Ribbon.RibbonPage[] {
            this.ribbonPageDashBoard,
            this.ribbonPageEditor,
            this.ribbonPagePlayLists,
            this.ribbonPageSchedule,
            //this.ribbonPageManager,
            this.ribbonPageLive});
            this.ribbonControl1.RepositoryItems.AddRange(new DevExpress.XtraEditors.Repository.RepositoryItem[] {
            this.repositoryItemTextEdit1,
            this.repositoryItemFontEdit1,
            this.repositoryItemButtonEdit2,
            this.cmbTextFontSize,
            this.repositoryItemTextEffectEdit,
            this.fontEffectListComBox,
            this.repositoryItemColorEdit1,
            this.cmbTextFontName,
            this.repositoryItemKernEdit,
            this.repositoryItemLeadEdit,
            this.repositoryItemPopupContainerEdit3,
            this.InnerLineWidthSpinEdit});
            this.ribbonControl1.SelectedPage = this.ribbonPageEditor;
            this.ribbonControl1.Size = new System.Drawing.Size(1067, 144);
            this.ribbonControl1.StatusBar = this.ribbonStatusBar1;
            this.ribbonControl1.Toolbar.ItemLinks.Add(this.btnSave);
            this.ribbonControl1.Toolbar.ItemLinks.Add(this.btnUndo);
            this.ribbonControl1.Toolbar.ItemLinks.Add(this.btnRedo);
            // 
            // popupMenuMain
            // 
            this.popupMenuMain.ItemLinks.Add(this.btnSave);
            this.popupMenuMain.ItemLinks.Add(this.btnSaveAs);
            this.popupMenuMain.ItemLinks.Add(this.btnBatchLoad);
            this.popupMenuMain.ItemLinks.Add(this.btnAbout);
            this.popupMenuMain.ItemLinks.Add(this.btnHelp);
            this.popupMenuMain.ItemLinks.Add(this.btnProfaneWord);
            this.popupMenuMain.ItemLinks.Add(this.btnImport);
            this.popupMenuMain.ItemLinks.Add(this.btnExport);
            this.popupMenuMain.ItemLinks.Add(this.btnExit, true);
//#if DEBUG
            this.popupMenuMain.ItemLinks.Add(this.btnTestCommand);
//#endif
            this.popupMenuMain.MenuDrawMode = DevExpress.XtraBars.MenuDrawMode.LargeImagesText;
            this.popupMenuMain.Name = "popupMenuMain";
            this.popupMenuMain.Ribbon = this.ribbonControl1;
            // 
            // btnSave
            // 
            this.btnSave.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnSaveCaption);
            this.btnSave.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnSave.Glyph = ((System.Drawing.Image)(resources.GetObject("btnSave.Glyph")));
            this.btnSave.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnSaveHint);
            this.btnSave.Id = 107;
            this.btnSave.ItemShortcut = new DevExpress.XtraBars.BarShortcut((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S));
            this.btnSave.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnSave.LargeGlyph")));
            this.btnSave.Name = "btnSave";
            this.btnSave.RibbonStyle = DevExpress.XtraBars.Ribbon.RibbonItemStyles.Large;
            this.btnSave.SourcePropertyName = null;
            this.btnSave.TargetPropertyName = null;
            // 
            // btnSaveAs
            // 
            this.btnSaveAs.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnSaveAsCaption);
            this.btnSaveAs.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnSaveAs.Glyph = ((System.Drawing.Image)(resources.GetObject("btnSaveAs.Glyph")));
            this.btnSaveAs.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnSaveAsHint);
            this.btnSaveAs.Id = 121;
            this.btnSaveAs.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnSaveAs.LargeGlyph")));
            this.btnSaveAs.Name = "btnSaveAs";
            this.btnSaveAs.RibbonStyle = DevExpress.XtraBars.Ribbon.RibbonItemStyles.SmallWithText;
            this.btnSaveAs.SourcePropertyName = null;
            this.btnSaveAs.TargetPropertyName = null;

            // 
            // btnAbout
            // 
            this.btnAbout.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnAboutCaption);
            this.btnAbout.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnAbout.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.About);
            this.btnAbout.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnAboutHint);
            this.btnAbout.Id = 121;
            this.btnAbout.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.About);
            this.btnAbout.Name = "btnAbout";
            this.btnAbout.RibbonStyle = DevExpress.XtraBars.Ribbon.RibbonItemStyles.SmallWithText;
            this.btnAbout.SourcePropertyName = null;
            this.btnAbout.TargetPropertyName = null;
            this.btnAbout.ItemClick += new ItemClickEventHandler(btnAbout_ItemClick);
            // 
            // btnHelp
            // 
		    this.btnHelp.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnHelpCaption);
            this.btnHelp.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnHelp.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.Help);
            this.btnHelp.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnHelpHint);
            this.btnHelp.Id = 121;
            this.btnHelp.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.Help);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.RibbonStyle = DevExpress.XtraBars.Ribbon.RibbonItemStyles.SmallWithText;
            this.btnHelp.SourcePropertyName = null;
            this.btnHelp.TargetPropertyName = null;
            // 
            // btnTestCommand
            // 
            this.btnTestCommand.Caption = "Test Command";
            this.btnTestCommand.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnTestCommand.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.Help);
            this.btnTestCommand.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnHelpHint);
            this.btnTestCommand.Id = 121;
            this.btnTestCommand.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.Help);
            this.btnTestCommand.Name = "btnTestCommand";
            this.btnTestCommand.RibbonStyle = DevExpress.XtraBars.Ribbon.RibbonItemStyles.SmallWithText;
            this.btnTestCommand.SourcePropertyName = null;
            this.btnTestCommand.TargetPropertyName = null;
            this.btnTestCommand.ItemClick += new ItemClickEventHandler(btnTestCommand_ItemClick);
            // 
            // btnProfaneWordbtnProfaneWord
            // 
            this.btnProfaneWord.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnProfaneWordsCaption);
            this.btnProfaneWord.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnProfaneWord.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.Edit);
            this.btnProfaneWord.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnProfaneWordsHint);
            this.btnProfaneWord.Id = 121;
            this.btnProfaneWord.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.Edit);
            this.btnProfaneWord.Name = "btnProfaneWord";
            this.btnProfaneWord.RibbonStyle = DevExpress.XtraBars.Ribbon.RibbonItemStyles.SmallWithText;
            this.btnProfaneWord.SourcePropertyName = null;
            this.btnProfaneWord.TargetPropertyName = null;
            this.btnProfaneWord.ItemClick += new ItemClickEventHandler(btnProfaneWord_ItemClick);
            // 
            // btnBatchLoad
            // 
            this.btnBatchLoad.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnBatchLoadCaption);
            this.btnBatchLoad.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnBatchLoad.Glyph = ((System.Drawing.Image)(resources.GetObject("btnBatchLoad.Glyph")));
            this.btnBatchLoad.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnBatchLoadHint);
            this.btnBatchLoad.Id = 122;
            this.btnBatchLoad.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnBatchLoad.LargeGlyph")));
            this.btnBatchLoad.Name = "btnBatchLoad";
            this.btnBatchLoad.SourcePropertyName = null;
            this.btnBatchLoad.TargetPropertyName = null;
            // 
            // btnImport
            // 
            this.btnImport.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnImportCaption);
            this.btnImport.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnImport.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.Import16); 
            this.btnImport.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.Import);
            this.btnImport.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnImportHint);
            this.btnImport.Id = 146;
            this.btnImport.Name = "btnImport";
            this.btnImport.SourcePropertyName = null;
            this.btnImport.TargetPropertyName = null;
            this.btnImport.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;
            // 
            // btnExport
            // 
            this.btnExport.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnExportCaption);
            this.btnExport.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnExport.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.Export16);
            this.btnExport.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnExportHint);
            this.btnExport.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.Export); 
            this.btnExport.Id = 147;
            this.btnExport.Name = "btnExport";
            this.btnExport.SourcePropertyName = null;
            this.btnExport.TargetPropertyName = null;
            this.btnExport.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;
            // 
            // btnExit
            // 
            this.btnExit.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnExitCaption);
            this.btnExit.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnExit.Glyph = ((System.Drawing.Image)(resources.GetObject("btnExit.Glyph")));
            this.btnExit.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnExitHint);
            this.btnExit.Id = 31;
            this.btnExit.ImageIndex = 2;
            this.btnExit.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnExit.LargeGlyph")));
            this.btnExit.LargeImageIndex = 8;
            this.btnExit.Name = "btnExit";
            this.btnExit.SourcePropertyName = null;
            this.btnExit.TargetPropertyName = null;
            // 
            // skinsBli
            // 
            this.skinsBli.Caption = "Skins";
            this.skinsBli.Id = 21;
            this.skinsBli.Name = "skinsBli";
            this.skinsBli.RibbonStyle = DevExpress.XtraBars.Ribbon.RibbonItemStyles.SmallWithText;
            // 
            // btnEditorNewMessage
            // 
            this.btnEditorNewMessage.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnNewMessageCaption);
            this.btnEditorNewMessage.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnEditorNewMessage.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.NewMessage16);
            this.btnEditorNewMessage.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnNewMessageHint);
            this.btnEditorNewMessage.Id = 25;
            this.btnEditorNewMessage.ImageIndex = 4;
            this.btnEditorNewMessage.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.NewMessage);
            this.btnEditorNewMessage.LargeImageIndex = 6;
            this.btnEditorNewMessage.Name = "btnEditorNewMessage";
            this.btnEditorNewMessage.SourcePropertyName = null;
            this.btnEditorNewMessage.TargetPropertyName = null;
            // 
            // btnPlayListNew
            // 
            this.btnPlayListNew.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnNewPlaylistCaption);
            this.btnPlayListNew.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnPlayListNew.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.NewPlaylist16);
            this.btnPlayListNew.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnNewPlaylistHint);
            this.btnPlayListNew.Id = 26;
            this.btnPlayListNew.ImageIndex = 6;
            this.btnPlayListNew.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.NewPlaylist);
            this.btnPlayListNew.LargeImageIndex = 4;
            this.btnPlayListNew.Name = "btnPlayListNew";
            this.btnPlayListNew.SourcePropertyName = null;
            this.btnPlayListNew.TargetPropertyName = null;
            // 
            // btnNewSchedule
            // 
            this.btnNewSchedule.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnNewSchedulerCaption);
            this.btnNewSchedule.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnNewSchedule.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.NewSchedule16);
            this.btnNewSchedule.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnNewSchedulerHint);
            this.btnNewSchedule.Id = 27;
            this.btnNewSchedule.ImageIndex = 7;
            this.btnNewSchedule.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.NewSchedule);
            this.btnNewSchedule.LargeImageIndex = 14;
            this.btnNewSchedule.Name = "btnNewSchedule";
            this.btnNewSchedule.SourcePropertyName = null;
            this.btnNewSchedule.TargetPropertyName = null;
            // 
            // btnNewLibrary
            // 
            this.btnNewLibrary.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnNewLibraryCaption);
            this.btnNewLibrary.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnNewLibrary.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.NewLibrary16);
            this.btnNewLibrary.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnNewLibraryHint);
            this.btnNewLibrary.Id = 28;
            this.btnNewLibrary.ImageIndex = 3;
            this.btnNewLibrary.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.NewLibrary);
            this.btnNewLibrary.LargeImageIndex = 7;
            this.btnNewLibrary.Name = "btnNewLibrary";
            this.btnNewLibrary.SourcePropertyName = null;
            this.btnNewLibrary.TargetPropertyName = null;
            // 
            // btnNewLibrary
            // 
            this.btnNewTimeSliceGroup.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnNewTimeSliceGroupCaption);
            this.btnNewTimeSliceGroup.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnNewTimeSliceGroup.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.Time16);
            this.btnNewTimeSliceGroup.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnNewTimeSliceGroupHint);
            this.btnNewTimeSliceGroup.Id = 28;
            this.btnNewTimeSliceGroup.ImageIndex = 3;
            this.btnNewTimeSliceGroup.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.Time);
            this.btnNewTimeSliceGroup.LargeImageIndex = 7;
            this.btnNewTimeSliceGroup.Name = "btnNewLibrary";
            this.btnNewTimeSliceGroup.SourcePropertyName = null;
            this.btnNewTimeSliceGroup.TargetPropertyName = null;
            // 
            // btnDashboardEdit
            // 
            this.btnDashboardEdit.Caption = "Insert Sign Photo";
            this.btnDashboardEdit.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnDashboardEdit.Glyph = ((System.Drawing.Image)(resources.GetObject("btnDashboardEdit.Glyph")));
            this.btnDashboardEdit.Hint = "Allows the user to place a photo for each sign/group";
            this.btnDashboardEdit.Id = 29;
            this.btnDashboardEdit.ImageIndex = 0;
            this.btnDashboardEdit.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnDashboardEdit.LargeGlyph")));
            this.btnDashboardEdit.LargeImageIndex = 1;
            this.btnDashboardEdit.Name = "btnDashboardEdit";
            this.btnDashboardEdit.SourcePropertyName = null;
            this.btnDashboardEdit.TargetPropertyName = null;
            // 
            // btnNew
            // 
            this.btnNew.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnNew.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnNewCaption);
            this.btnNew.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            //this.btnNew.DropDownControl = this.newPopDashboardMenu;
            this.btnNew.Glyph = ((System.Drawing.Image)(resources.GetObject("btnNew.Glyph")));
            this.btnNew.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnNewHint);
            this.btnNew.Id = 30;
            this.btnNew.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnNew.LargeGlyph")));
            this.btnNew.Name = "btnNew";
            this.btnNew.RibbonStyle = DevExpress.XtraBars.Ribbon.RibbonItemStyles.SmallWithText;
            this.btnNew.SourcePropertyName = null;
            this.btnNew.TargetPropertyName = null;
            // 
            // newPopDashboardMenu
            // 
            this.newPopDashboardMenu.ItemLinks.Add(this.btnDashbaordNewSign);
            this.newPopDashboardMenu.ItemLinks.Add(this.btnDashboardNewSignGroup);
            this.newPopDashboardMenu.ItemLinks.Add(this.btnEditorNewMessage, true);
            this.newPopDashboardMenu.ItemLinks.Add(this.btnPlayListNew);
            this.newPopDashboardMenu.ItemLinks.Add(this.btnNewTimeSliceGroup);
            this.newPopDashboardMenu.ItemLinks.Add(this.btnNewSchedule);
            this.newPopDashboardMenu.ItemLinks.Add(this.btnNewLibrary);
            this.newPopDashboardMenu.Name = "newPopDashboardMenu";
            this.newPopDashboardMenu.Ribbon = this.ribbonControl1;
            this.newPopDashboardMenu.MenuDrawMode = MenuDrawMode.LargeImagesText;
            // 
            // newPopEditorMenu
            // 
            this.newPopEditorMenu.ItemLinks.Add(this.btnEditorNewMessage);
            this.newPopEditorMenu.ItemLinks.Add(this.btnDashbaordNewSign, true);
            this.newPopEditorMenu.ItemLinks.Add(this.btnDashboardNewSignGroup);
            this.newPopEditorMenu.ItemLinks.Add(this.btnPlayListNew);
            this.newPopEditorMenu.ItemLinks.Add(this.btnNewTimeSliceGroup);
            this.newPopEditorMenu.ItemLinks.Add(this.btnNewSchedule);
            this.newPopEditorMenu.ItemLinks.Add(this.btnNewLibrary);
            this.newPopEditorMenu.Name = "newPopEditorMenu";
            this.newPopEditorMenu.Ribbon = this.ribbonControl1;
            this.newPopEditorMenu.MenuDrawMode = MenuDrawMode.LargeImagesText;
            // 
            // newPopPlaylistMenu
            // 
            this.newPopPlaylistMenu.ItemLinks.Add(this.btnPlayListNew);
            this.newPopPlaylistMenu.ItemLinks.Add(this.btnNewTimeSliceGroup);
            this.newPopPlaylistMenu.ItemLinks.Add(this.btnDashbaordNewSign, true);
            this.newPopPlaylistMenu.ItemLinks.Add(this.btnDashboardNewSignGroup);
            this.newPopPlaylistMenu.ItemLinks.Add(this.btnEditorNewMessage);
            this.newPopPlaylistMenu.ItemLinks.Add(this.btnNewSchedule);
            this.newPopPlaylistMenu.ItemLinks.Add(this.btnNewLibrary);
            this.newPopPlaylistMenu.Name = "newPopPlaylistMenu";
            this.newPopPlaylistMenu.Ribbon = this.ribbonControl1;
            this.newPopPlaylistMenu.MenuDrawMode = MenuDrawMode.LargeImagesText;
            // 
            // newPopSchedulerMenu
            // 
            this.newPopSchedulerMenu.ItemLinks.Add(this.btnNewSchedule);
            this.newPopSchedulerMenu.ItemLinks.Add(this.btnDashbaordNewSign, true);
            this.newPopSchedulerMenu.ItemLinks.Add(this.btnDashboardNewSignGroup);
            this.newPopSchedulerMenu.ItemLinks.Add(this.btnEditorNewMessage);
            this.newPopSchedulerMenu.ItemLinks.Add(this.btnPlayListNew);
            this.newPopSchedulerMenu.ItemLinks.Add(this.btnNewTimeSliceGroup);
            this.newPopSchedulerMenu.ItemLinks.Add(this.btnNewLibrary);
            this.newPopSchedulerMenu.Name = "newPopSchedulerMenu";
            this.newPopSchedulerMenu.Ribbon = this.ribbonControl1;
            this.newPopSchedulerMenu.MenuDrawMode = MenuDrawMode.LargeImagesText;
            // 
            // btnDashbaordNewSign
            // 
            this.btnDashbaordNewSign.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnNewSignCaption);
            this.btnDashbaordNewSign.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnDashbaordNewSign.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.NewSign16);
            this.btnDashbaordNewSign.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnNewSignHint);
            this.btnDashbaordNewSign.Description = Resource.GetString(Resource.Strings.RibbonBarbtnNewSignHint);
            this.btnDashbaordNewSign.Id = 32;
            this.btnDashbaordNewSign.ImageIndex = 8;
            this.btnDashbaordNewSign.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.NewSign);
            this.btnDashbaordNewSign.LargeImageIndex = 2;
            this.btnDashbaordNewSign.Name = "btnDashbaordNewSign";
            this.btnDashbaordNewSign.SourcePropertyName = null;
            this.btnDashbaordNewSign.TargetPropertyName = null;
            // 
            // btnDashboardNewSignGroup
            // 
            this.btnDashboardNewSignGroup.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnNewSignGroupCaption);
            this.btnDashboardNewSignGroup.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnDashboardNewSignGroup.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.NewSignGroup16);
            this.btnDashboardNewSignGroup.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnNewSignGroupHint);
            this.btnDashboardNewSignGroup.Id = 33;
            this.btnDashboardNewSignGroup.ImageIndex = 0;
            this.btnDashboardNewSignGroup.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.NewSignGroup);
            this.btnDashboardNewSignGroup.LargeImageIndex = 1;
            this.btnDashboardNewSignGroup.Name = "btnDashboardNewSignGroup";
            this.btnDashboardNewSignGroup.SourcePropertyName = null;
            this.btnDashboardNewSignGroup.TargetPropertyName = null;
            // 
            // btnConnect
            // 
            this.btnConnect.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            this.btnConnect.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnLoginCaption);
            this.btnConnect.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnConnect.Glyph = ((System.Drawing.Image)(resources.GetObject("btnConnect.Glyph")));
            this.btnConnect.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnLoginHint);
            this.btnConnect.Id = 35;
            this.btnConnect.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnConnect.LargeGlyph")));
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.SourcePropertyName = null;
            this.btnConnect.TargetPropertyName = null;

            //// 
            //// btnSessionLoad
            //// 
            //this.btnSessionLoad.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            //this.btnSessionLoad.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnLoginCaption);
            //this.btnSessionLoad.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            //this.btnSessionLoad.Glyph = ((System.Drawing.Image)(resources.GetObject("btnConnect.Glyph")));
            //this.btnSessionLoad.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnLoginHint);
            //this.btnSessionLoad.Id = 35;
            //this.btnSessionLoad.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnConnect.LargeGlyph")));
            //this.btnSessionLoad.Name = "btnSessionLoad";
            //this.btnSessionLoad.SourcePropertyName = null;
            //this.btnSessionLoad.TargetPropertyName = null;

            //// 
            //// btnSessionSave
            //// 
            //this.btnSessionSave.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            //this.btnSessionSave.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnLoginCaption);
            //this.btnSessionSave.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            //this.btnSessionSave.Glyph = ((System.Drawing.Image)(resources.GetObject("btnConnect.Glyph")));
            //this.btnSessionSave.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnLoginHint);
            //this.btnSessionSave.Id = 35;
            //this.btnSessionSave.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnConnect.LargeGlyph")));
            //this.btnSessionSave.Name = "btnSessionSave";
            //this.btnSessionSave.SourcePropertyName = null;
            //this.btnSessionSave.TargetPropertyName = null;
            // 
            // btnBlankSignSet
            // 
            this.btnBlankSignSet.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            this.btnBlankSignSet.Caption = "Stop";//Resource.GetString(Resource.Strings.RibbonBarbtnBlankSignCaption);
            this.btnBlankSignSet.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnBlankSignSet.Glyph = ((System.Drawing.Image)(resources.GetObject("btnConnect.Glyph")));
            //this.btnBlankSignSet.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnLoginHint);
            this.btnBlankSignSet.Id = 35;
            this.btnBlankSignSet.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.Stop);
            this.btnBlankSignSet.Name = "btnBlankSignSet";
            this.btnBlankSignSet.SourcePropertyName = null;
            this.btnBlankSignSet.TargetPropertyName = null;
            // 
            // btnUnBlankSignSet
            // 
            this.btnUnBlankSignSet.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            this.btnUnBlankSignSet.Caption = "Play";//Resource.GetString(Resource.Strings.RibbonBarbtnBlankSignCaption);
            //this.btnUnBlankSignSet.Hint = "Preview";
            this.btnUnBlankSignSet.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnUnBlankSignSet.Glyph = ((System.Drawing.Image)(resources.GetObject("btnConnect.Glyph")));
            this.btnUnBlankSignSet.Id = 35;
            this.btnUnBlankSignSet.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.PlaySign);
            this.btnUnBlankSignSet.Name = "btnUnBlankSignSet";
            this.btnUnBlankSignSet.SourcePropertyName = null;
            this.btnUnBlankSignSet.TargetPropertyName = null;
            // 
            // btnSignProperties
            // 
            this.btnSignProperties.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            this.btnSignProperties.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnPropertiesCaption);
            this.btnSignProperties.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnSignProperties.DropDownControl = this.mnuProperties;
            this.btnSignProperties.Glyph = ((System.Drawing.Image)(resources.GetObject("btnSignProperties.Glyph")));
            this.btnSignProperties.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnPropertiesHint);
            this.btnSignProperties.Id = 36;
            this.btnSignProperties.Name = "btnSignProperties";
            this.btnSignProperties.SourcePropertyName = null;
            this.btnSignProperties.TargetPropertyName = null;
            // 
            // mnuProperties
            // 
            this.mnuProperties.ItemLinks.Add(this.btnSignStatus);
            this.mnuProperties.ItemLinks.Add(this.btnChangePwd, true);
            this.mnuProperties.ItemLinks.Add(this.btnSetDateTime);
            this.mnuProperties.ItemLinks.Add(this.btnStartStopRender, true);
            this.mnuProperties.ItemLinks.Add(this.btnSkipQ);
            this.mnuProperties.ItemLinks.Add(this.btnClearQ);
            this.mnuProperties.ItemLinks.Add(this.btnReboot, true);
            this.mnuProperties.ItemLinks.Add(this.btnTimeZone, true);
            this.mnuProperties.ItemLinks.Add(this.btnFactoryReset);
            this.mnuProperties.Name = "mnuProperties";
            this.mnuProperties.Ribbon = this.ribbonControl1;
            // 
            // btnSignStatus
            // 
            this.btnSignStatus.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnSignStatusCaption);
            this.btnSignStatus.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnSignStatus.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnSignStatusHint);
            this.btnSignStatus.Id = 154;
            this.btnSignStatus.Name = "btnSignStatus";
            this.btnSignStatus.SourcePropertyName = null;
            this.btnSignStatus.TargetPropertyName = null;
            // 
            // btnChangePwd
            // 
            this.btnChangePwd.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnChangePSWCaption);
            this.btnChangePwd.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnChangePwd.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnChangePSWHint);
            this.btnChangePwd.Id = 155;
            this.btnChangePwd.Name = "btnChangePwd";
            this.btnChangePwd.SourcePropertyName = null;
            this.btnChangePwd.TargetPropertyName = null;
            // 
            // btnSetDateTime
            // 
            this.btnSetDateTime.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnSetDateTimeCaption);
            this.btnSetDateTime.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnSetDateTime.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnSetDateTimeHint);
            this.btnSetDateTime.Id = 157;
            this.btnSetDateTime.Name = "btnSetDateTime";
            this.btnSetDateTime.SourcePropertyName = null;
            this.btnSetDateTime.TargetPropertyName = null;
            // 
            // btnStartStopRender
            // 
            this.btnStartStopRender.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            this.btnStartStopRender.Caption = "Start Render";
            this.btnStartStopRender.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnStartStopRender.Id = 161;
            this.btnStartStopRender.Name = "btnStartStopRender";
            this.btnStartStopRender.SourcePropertyName = null;
            this.btnStartStopRender.TargetPropertyName = null;
            // 
            // btnSkipQ
            // 
            this.btnSkipQ.Caption = "Skip CXC Queue Message";
            this.btnSkipQ.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnSkipQ.Id = 159;
            this.btnSkipQ.Name = "btnSkipQ";
            this.btnSkipQ.SourcePropertyName = null;
            this.btnSkipQ.TargetPropertyName = null;
            // 
            // btnClearQ
            // 
            this.btnClearQ.Caption = "clear CXC Queue Message";
            this.btnClearQ.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnClearQ.Id = 160;
            this.btnClearQ.Name = "btnClearQ";
            this.btnClearQ.SourcePropertyName = null;
            this.btnClearQ.TargetPropertyName = null;
            // 
            // btnReboot
            // 
            this.btnReboot.Caption = "Reboot CXC";
            this.btnReboot.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnReboot.Id = 156;
            this.btnReboot.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.Reboot);
            this.btnReboot.Name = "btnReboot";
            this.btnReboot.SourcePropertyName = null;
            this.btnReboot.TargetPropertyName = null;
            // 
            // btnTimeZone
            // 
            this.btnTimeZone.Caption = "Time Zone";
            this.btnTimeZone.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnTimeZone.Id = 156;
            this.btnTimeZone.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.TimeZone);
            this.btnTimeZone.Name = "btnTimeZone";
            this.btnTimeZone.SourcePropertyName = null;
            this.btnTimeZone.TargetPropertyName = null;
            // 
            // btnFactoryReset
            // 
            this.btnFactoryReset.Caption = "CXC Factory Reset";
            this.btnFactoryReset.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnFactoryReset.Id = 158;
            this.btnFactoryReset.Name = "btnFactoryReset";
            this.btnFactoryReset.SourcePropertyName = null;
            this.btnFactoryReset.TargetPropertyName = null;
            // 
            // btnBlankSign
            // 
            this.btnBlankSign.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnBlankSignCaption);
            this.btnBlankSign.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnBlankSign.Glyph = ((System.Drawing.Image)(resources.GetObject("btnBlankSign.Glyph")));
            this.btnBlankSign.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnBlankSignHint);
            this.btnBlankSign.Id = 37;
            this.btnBlankSign.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnBlankSign.LargeGlyph")));
            this.btnBlankSign.Name = "btnBlankSign";
            this.btnBlankSign.SourcePropertyName = null;
            this.btnBlankSign.TargetPropertyName = null;
            // 
            // btnTestPattern
            // 
            this.btnTestPattern.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnTestPatternCaption);
            this.btnTestPattern.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnTestPattern.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnTestPattern.Glyph = ((System.Drawing.Image)(resources.GetObject("btnTestPattern.Glyph")));
            this.btnTestPattern.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnTestPatternHint);
            this.btnTestPattern.DropDownControl = this.popupMenu1;
            this.btnTestPattern.Id = 38;
            this.btnTestPattern.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnTestPattern.LargeGlyph")));
            this.btnTestPattern.Name = "btnTestPattern";
            this.btnTestPattern.SourcePropertyName = null;
            this.btnTestPattern.TargetPropertyName = null;
            //btnTestPattern.Visibility = BarItemVisibility.Never;
            // 
            // btnDisplayMsg
            // 
            this.btnDisplayMsg.Caption = "Display Message";
            this.btnDisplayMsg.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnDisplayMsg.Glyph = ((System.Drawing.Image)(resources.GetObject("btnDisplayMsg.Glyph")));
            this.btnDisplayMsg.Hint = "Instruct the current selected sign to display a preformatted message \"Frame Objec" +
                "t\"";
            this.btnDisplayMsg.Id = 39;
            this.btnDisplayMsg.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnDisplayMsg.LargeGlyph")));
            this.btnDisplayMsg.Name = "btnDisplayMsg";
            this.btnDisplayMsg.SourcePropertyName = null;
            this.btnDisplayMsg.TargetPropertyName = null;
            // 
            // btnDelete
            // 
            this.btnDelete.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnDeleteCaption);
            this.btnDelete.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnDelete.Glyph = ((System.Drawing.Image)(resources.GetObject("btnDelete.Glyph")));
            this.btnDelete.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnDeleteHint);
            this.btnDelete.Id = 40;
            this.btnDelete.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnDelete.LargeGlyph")));
            this.btnDelete.Name = "btnDelete";
            this.btnDelete.SourcePropertyName = null;
            this.btnDelete.TargetPropertyName = null;
            // 
            // btnEditPicture
            // 
            this.btnEditPicture.Caption = "Edit";
            //this.btnEditPicture.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnEditPicture.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.Edit16);
            this.btnEditPicture.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnDeleteHint);
            this.btnEditPicture.Id = 40;
            this.btnEditPicture.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.Edit);
            this.btnEditPicture.Name = "btnEditPicture";
            this.btnEditPicture.SourcePropertyName = null;
            this.btnEditPicture.TargetPropertyName = null;
            this.btnEditPicture.Visibility = BarItemVisibility.Never;
            this.btnEditPicture.ItemClick += new ItemClickEventHandler(btnEditPicture_ItemClick);
            // 
            // btnDashBoardTools
            // 
            this.btnDashBoardTools.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnDashBoardTools.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnSetupCaption);
            this.btnDashBoardTools.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnDashBoardTools.DropDownControl = this.toolsPopMenu;
		    this.btnDashBoardTools.Glyph = Resource.GetImage(Resource.Images.Setup16);
            this.btnDashBoardTools.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnSetupHint);
            this.btnDashBoardTools.Id = 41;
            //this.btnDashBoardTools.LargeGlyph = Resource.GetImage(Resource.Images.Setup); ;
            this.btnDashBoardTools.Name = "btnDashBoardTools";
            this.btnDashBoardTools.SourcePropertyName = null;
            this.btnDashBoardTools.TargetPropertyName = null;
		    this.btnDashBoardTools.RibbonStyle = DevExpress.XtraBars.Ribbon.RibbonItemStyles.SmallWithText;
            // 
            // toolsPopMenu
            // 
            this.toolsPopMenu.ItemLinks.Add(this.btnDimming);
            //this.toolsPopMenu.ItemLinks.Add(this.btnTempOffset);
            this.toolsPopMenu.ItemLinks.Add(this.btnSetTime);
            this.toolsPopMenu.ItemLinks.Add(this.btnReboot);
            this.toolsPopMenu.ItemLinks.Add(this.btnTimeZone);
            this.toolsPopMenu.Name = "toolsPopMenu";
            this.toolsPopMenu.Ribbon = this.ribbonControl1;
            // 
            // btnDimming
            // 
            this.btnDimming.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnDimmingCaption);
            //this.btnDimming.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Dimming;
            this.btnDimming.Enabled = false;
            this.btnDimming.Glyph = ((System.Drawing.Image)(resources.GetObject("btnDimming.Glyph")));
            this.btnDimming.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnDimmingHint);
            this.btnDimming.Id = 42;
            this.btnDimming.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnDimming.LargeGlyph")));
            this.btnDimming.Name = "btnDimming";
            this.btnDimming.SourcePropertyName = null;
            this.btnDimming.TargetPropertyName = null;
            // 
            // btnTempOffset
            // 
            this.btnTempOffset.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnTempOffsetCaption);
            //this.btnTempOffset.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.TempOffset;
            this.btnTempOffset.Enabled = false;
            this.btnTempOffset.Glyph = ((System.Drawing.Image)(resources.GetObject("btnTempOffset.Glyph")));
            this.btnTempOffset.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnTempOffsetHint);
            this.btnTempOffset.Id = 43;
            //this.btnTempOffset.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnTempOffset.LargeGlyph")));
            this.btnTempOffset.Name = "btnTempOffset";
            this.btnTempOffset.SourcePropertyName = null;
            this.btnTempOffset.TargetPropertyName = null;
            // 
            // btnSetTime
            // 
            this.btnSetTime.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnSetDateTimeCaption);
            //this.btnSetTime.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.ResetTime;
            this.btnSetTime.Enabled = false;
            this.btnSetTime.Glyph = ((System.Drawing.Image)(resources.GetObject("btnSetTime.Glyph")));
            this.btnSetTime.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnSetDateTimeHint);
            this.btnSetTime.Id = 44;
            this.btnSetTime.Name = "btnSetTime";
            this.btnSetTime.SourcePropertyName = null;
            this.btnSetTime.TargetPropertyName = null;
            // 
            // btnViewLog
            // 
            this.btnViewLog.Caption = "View Logs";
            this.btnViewLog.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnViewLog.Glyph = ((System.Drawing.Image)(resources.GetObject("btnViewLog.Glyph")));
            this.btnViewLog.Hint = "Retrieve logs of the current selected sign";
            this.btnViewLog.Id = 45;
            this.btnViewLog.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnViewLog.LargeGlyph")));
            this.btnViewLog.Name = "btnViewLog";
            this.btnViewLog.SourcePropertyName = null;
            this.btnViewLog.TargetPropertyName = null;
            // 
            // btnLiveView
            // 
            this.btnLiveView.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            this.btnLiveView.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnLiveViewCaption);
            this.btnLiveView.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnLiveView.Glyph = ((System.Drawing.Image)(resources.GetObject("btnLiveView.Glyph")));
            this.btnLiveView.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnLiveViewHint);
            this.btnLiveView.Id = 46;
            this.btnLiveView.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnLiveView.LargeGlyph")));
            this.btnLiveView.Name = "btnLiveView";
            this.btnLiveView.SourcePropertyName = null;
            this.btnLiveView.TargetPropertyName = null;
            // 
            // btnSignPhotoView
            // 
            this.btnSignPhotoView.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            this.btnSignPhotoView.Caption = "Sign Photo View";
            this.btnSignPhotoView.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnSignPhotoView.Glyph = ((System.Drawing.Image)(resources.GetObject("btnSignPhotoView.Glyph")));
            this.btnSignPhotoView.Hint = "Toggle the \"Live View\" shape to display the static saved sign photo";
            this.btnSignPhotoView.Id = 47;
            this.btnSignPhotoView.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnSignPhotoView.LargeGlyph")));
            this.btnSignPhotoView.Name = "btnSignPhotoView";
            this.btnSignPhotoView.SourcePropertyName = null;
            this.btnSignPhotoView.TargetPropertyName = null;
            // 
            // btnRefreshView
            // 
            this.btnRefreshView.Caption = "Refresh View";
            this.btnRefreshView.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnRefreshView.Glyph = ((System.Drawing.Image)(resources.GetObject("btnRefreshView.Glyph")));
            this.btnRefreshView.Hint = "Refresh the Live View";
            this.btnRefreshView.Id = 48;
            this.btnRefreshView.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnRefreshView.LargeGlyph")));
            this.btnRefreshView.Name = "btnRefreshView";
            this.btnRefreshView.SourcePropertyName = null;
            this.btnRefreshView.TargetPropertyName = null;
            // 
            // btnDisplay
            // 
            this.btnDisplay.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnDisplay.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnDisplayCaption);
            this.btnDisplay.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnDisplay.DropDownControl = this.displayPopMenu;
            this.btnDisplay.Glyph = ((System.Drawing.Image)(resources.GetObject("btnDisplay.Glyph")));
            this.btnDisplay.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnDisplayHint);
            this.btnDisplay.Id = 49;
            this.btnDisplay.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnDisplay.LargeGlyph")));
            this.btnDisplay.Name = "btnDisplay";
            this.btnDisplay.SourcePropertyName = null;
            this.btnDisplay.TargetPropertyName = null;
            // 
            // displayPopMenu
            // 
            this.displayPopMenu.ItemLinks.Add(this.btnBlankSign);
            this.displayPopMenu.ItemLinks.Add(this.btnTestPattern);
            this.displayPopMenu.Name = "displayPopMenu";
            this.displayPopMenu.Ribbon = this.ribbonControl1;
            // 
            // btnInsertImage
            // 
            this.btnInsertImage.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnInsertImageCaption);
            this.btnInsertImage.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnInsertImage.Enabled = false;
            this.btnInsertImage.Glyph = ((System.Drawing.Image)(resources.GetObject("btnInsertImage.Glyph")));
            this.btnInsertImage.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnInsertImageHint);
            this.btnInsertImage.Id = 53;
            this.btnInsertImage.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnInsertImage.LargeGlyph")));
            this.btnInsertImage.Name = "btnInsertImage";
            this.btnInsertImage.SourcePropertyName = null;
            this.btnInsertImage.TargetPropertyName = null;
            this.btnInsertImage.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;
            // 
            // btnInsertVideo
            // 
            this.btnInsertVideo.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnInsertVideoCaption);
            this.btnInsertVideo.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnInsertVideo.Enabled = false;
            this.btnInsertVideo.Glyph = ((System.Drawing.Image)(resources.GetObject("btnInsertVideo.Glyph")));
            this.btnInsertVideo.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnInsertVideoHint);
            this.btnInsertVideo.Id = 52;
            this.btnInsertVideo.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnInsertVideo.LargeGlyph")));
            this.btnInsertVideo.Name = "btnInsertVideo";
            this.btnInsertVideo.SourcePropertyName = null;
            this.btnInsertVideo.TargetPropertyName = null;
            this.btnInsertVideo.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;
            // 
            // btnInsertText
            // 
            this.btnInsertText.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnInsertTextCaption);
            this.btnInsertText.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnInsertText.Enabled = false;
            this.btnInsertText.Glyph = ((System.Drawing.Image)(resources.GetObject("btnInsertText.Glyph")));
            this.btnInsertText.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnInsertTextHint);
            this.btnInsertText.Id = 51;
            this.btnInsertText.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnInsertText.LargeGlyph")));
            this.btnInsertText.Name = "btnInsertText";
            this.btnInsertText.SourcePropertyName = null;
            this.btnInsertText.TargetPropertyName = null;
            this.btnInsertText.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;
            // 
            // btnInsertVariableText
            // 
            this.btnInsertVariableText.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnInsertVariableTextCaption);
            this.btnInsertVariableText.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnInsertVariableText.DropDownControl = this.replacePopMenu;
            this.btnInsertVariableText.Enabled = false;
            this.btnInsertVariableText.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.ScrollText16);//((System.Drawing.Image)(resources.GetObject("btnInsertVariableText.Glyph")));
            this.btnInsertVariableText.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnInsertVariableTextHint);
            this.btnInsertVariableText.Id = 54;
            this.btnInsertVariableText.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnInsertVariableText.LargeGlyph")));
            this.btnInsertVariableText.Name = "btnInsertVariableText";
            this.btnInsertVariableText.SourcePropertyName = null;
            this.btnInsertVariableText.TargetPropertyName = null;
            this.btnInsertVariableText.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;
            //this.btnInsertVariableText. = Resources.Resource.GetImage(Resources.Resource.Images.ScrollText16);
            // 
            // btnInsertTime
            // 
            this.btnInsertTime.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnInsertTimeCaption);
            this.btnInsertTime.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnInsertTime.DropDownControl = this.replacePopMenu;
            this.btnInsertTime.Enabled = false;
            this.btnInsertTime.Glyph = (Resource.GetImage(Resource.Images.Time16));
            this.btnInsertTime.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnInsertTimeHint);
            this.btnInsertTime.Id = 1000;
            this.btnInsertTime.LargeGlyph = Resource.GetImage(Resource.Images.Time30);
            this.btnInsertTime.Name = "btnInsertTime";
            this.btnInsertTime.SourcePropertyName = null;
            this.btnInsertTime.TargetPropertyName = null;
            //this.btnInsertTime.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;
            // 
            // btnInsertTemperature
            // 
            this.btnInsertTemperature.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnInsertTemperatureCaption);
            this.btnInsertTemperature.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnInsertTemperature.DropDownControl = this.replacePopMenu;
            this.btnInsertTemperature.Enabled = false;
            this.btnInsertTemperature.Glyph = (Resource.GetImage(Resource.Images.Temp16));
            this.btnInsertTemperature.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnInsertTemperatureHint);
            this.btnInsertTemperature.Id = 1001;
            this.btnInsertTemperature.LargeGlyph = Resource.GetImage(Resource.Images.Temp30);
            this.btnInsertTemperature.Name = "btnInsertTemperature";
            this.btnInsertTemperature.SourcePropertyName = null;
            this.btnInsertTemperature.TargetPropertyName = null;
            this.btnInsertTemperature.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;

            // 
            // replacePopMenu
            // 
            this.replacePopMenu.ItemLinks.Add(this.barButtonItem21);
            this.replacePopMenu.ItemLinks.Add(this.barButtonItem22);
            this.replacePopMenu.ItemLinks.Add(this.barButtonItem23);
            this.replacePopMenu.Name = "replacePopMenu";
            this.replacePopMenu.Ribbon = this.ribbonControl1;
            // 
            // barButtonItem21
            // 
            this.barButtonItem21.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnInsertTemperatureCaption);
            this.barButtonItem21.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.barButtonItem21.Glyph = ((System.Drawing.Image)(resources.GetObject("barButtonItem21.Glyph")));
            this.barButtonItem21.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnInsertTemperatureHint);
            this.barButtonItem21.Id = 55;
            this.barButtonItem21.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("barButtonItem21.LargeGlyph")));
            this.barButtonItem21.Name = "barButtonItem21";
            this.barButtonItem21.SourcePropertyName = null;
            this.barButtonItem21.TargetPropertyName = null;
            // 
            // barButtonItem22
            // 
            this.barButtonItem22.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnInsertTemperatureCaption);
            this.barButtonItem22.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.barButtonItem22.Glyph = ((System.Drawing.Image)(resources.GetObject("barButtonItem22.Glyph")));
            this.barButtonItem22.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnInsertTemperatureHint);
            this.barButtonItem22.Id = 56;
            this.barButtonItem22.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("barButtonItem22.LargeGlyph")));
            this.barButtonItem22.Name = "barButtonItem22";
            this.barButtonItem22.SourcePropertyName = null;
            this.barButtonItem22.TargetPropertyName = null;
            // 
            // barButtonItem23
            // 
            this.barButtonItem23.Caption = "Other";
            this.barButtonItem23.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.barButtonItem23.Glyph = ((System.Drawing.Image)(resources.GetObject("barButtonItem23.Glyph")));
            this.barButtonItem23.Id = 57;
            this.barButtonItem23.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("barButtonItem23.LargeGlyph")));
            this.barButtonItem23.Name = "barButtonItem23";
            this.barButtonItem23.SourcePropertyName = null;
            this.barButtonItem23.TargetPropertyName = null;
            // 
            // btnDrawing
            // 
            this.btnDrawing.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnDrawing.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnDrawingCaption);
            this.btnDrawing.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnDrawing.DropDownControl = this.drawingPopMenu;
            this.btnDrawing.Glyph = ((System.Drawing.Image)(resources.GetObject("btnDrawing.Glyph")));
            this.btnDrawing.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnDrawingHint);
            this.btnDrawing.Id = 58;
            this.btnDrawing.ImageIndex = 16;
            this.btnDrawing.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnDrawing.LargeGlyph")));
            this.btnDrawing.LargeImageIndex = 42;
            this.btnDrawing.Name = "btnDrawing";
            this.btnDrawing.SourcePropertyName = null;
            this.btnDrawing.TargetPropertyName = null;
            // 
            // drawingPopMenu
            // 
            this.drawingPopMenu.ItemLinks.Add(this.btnRectangle);
            this.drawingPopMenu.ItemLinks.Add(this.btnEllipse);
            this.drawingPopMenu.ItemLinks.Add(this.btnArrowUp);
            this.drawingPopMenu.ItemLinks.Add(this.btnArrowDown);
            this.drawingPopMenu.ItemLinks.Add(this.btnArrowRight);
            this.drawingPopMenu.ItemLinks.Add(this.btnArrowLeft);
            this.drawingPopMenu.Name = "drawingPopMenu";
            this.drawingPopMenu.Ribbon = this.ribbonControl1;
            // 
            // btnRectangle
            // 
            this.btnRectangle.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnRectangleCaption);
            this.btnRectangle.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnRectangle.Glyph = ((System.Drawing.Image)(resources.GetObject("btnRectangle.Glyph")));
            this.btnRectangle.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnRectangleHint);
            this.btnRectangle.Id = 59;
            this.btnRectangle.ImageIndex = 38;
            this.btnRectangle.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnRectangle.LargeGlyph")));
            this.btnRectangle.LargeImageIndex = 20;
            this.btnRectangle.Name = "btnRectangle";
            this.btnRectangle.SourcePropertyName = null;
            this.btnRectangle.TargetPropertyName = null;
            // 
            // btnEllipse
            // 
            this.btnEllipse.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnEllipseCaption);
            this.btnEllipse.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnEllipse.Glyph = ((System.Drawing.Image)(resources.GetObject("btnEllipse.Glyph")));
            this.btnEllipse.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnEllipseHint);
            this.btnEllipse.Id = 61;
            this.btnEllipse.ImageIndex = 17;
            this.btnEllipse.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnEllipse.LargeGlyph")));
            this.btnEllipse.LargeImageIndex = 41;
            this.btnEllipse.Name = "btnEllipse";
            this.btnEllipse.SourcePropertyName = null;
            this.btnEllipse.TargetPropertyName = null;
            // 
            // btnArrowUp
            // 
            this.btnArrowUp.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnArrowUpCaption);
            this.btnArrowUp.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnArrowUp.Glyph = ((System.Drawing.Image)(resources.GetObject("btnArrowUp.Glyph")));
            this.btnArrowUp.Hint = Resource.GetString(Resource.Strings.RibbonBabtnArrowUpHint);
            this.btnArrowUp.Id = 63;
            this.btnArrowUp.ImageIndex = 13;
            this.btnArrowUp.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnArrowUp.LargeGlyph")));
            this.btnArrowUp.LargeImageIndex = 45;
            this.btnArrowUp.Name = "btnArrowUp";
            this.btnArrowUp.SourcePropertyName = null;
            this.btnArrowUp.TargetPropertyName = null;
            // 
            // btnArrowDown
            // 
            this.btnArrowDown.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnbtnArrowDownCaption);
            this.btnArrowDown.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnArrowDown.Glyph = ((System.Drawing.Image)(resources.GetObject("btnArrowDown.Glyph")));
            this.btnArrowDown.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnbtnArrowDownHint);
            this.btnArrowDown.Id = 65;
            this.btnArrowDown.ImageIndex = 10;
            this.btnArrowDown.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnArrowDown.LargeGlyph")));
            this.btnArrowDown.LargeImageIndex = 9;
            this.btnArrowDown.Name = "btnArrowDown";
            this.btnArrowDown.SourcePropertyName = null;
            this.btnArrowDown.TargetPropertyName = null;
            // 
            // btnArrowRight
            // 
            this.btnArrowRight.Caption = "Arrow Right";
            this.btnArrowRight.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnArrowRight.Glyph = ((System.Drawing.Image)(resources.GetObject("btnArrowRight.Glyph")));
            this.btnArrowRight.Hint = "Draws an Arrow Right of the Line stroke color and Line Thickness";
            this.btnArrowRight.Id = 67;
            this.btnArrowRight.ImageIndex = 11;
            this.btnArrowRight.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnArrowRight.LargeGlyph")));
            this.btnArrowRight.LargeImageIndex = 47;
            this.btnArrowRight.Name = "btnArrowRight";
            this.btnArrowRight.SourcePropertyName = null;
            this.btnArrowRight.TargetPropertyName = null;
            // 
            // btnArrowLeft
            // 
            this.btnArrowLeft.Caption = "Arrow Left";
            this.btnArrowLeft.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnArrowLeft.Glyph = ((System.Drawing.Image)(resources.GetObject("btnArrowLeft.Glyph")));
            this.btnArrowLeft.Hint = "Draws an Arrow Left of the Line stroke color and Line Thickness";
            this.btnArrowLeft.Id = 69;
            this.btnArrowLeft.ImageIndex = 11;
            this.btnArrowLeft.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnArrowLeft.LargeGlyph")));
            this.btnArrowLeft.LargeImageIndex = 47;
            this.btnArrowLeft.Name = "btnArrowLeft";
            this.btnArrowLeft.SourcePropertyName = null;
            this.btnArrowLeft.TargetPropertyName = null;
            // 
            // btnFill
            // 
            this.btnFill.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnFill.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnFillCaption);
            this.btnFill.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnFill.Glyph = ((System.Drawing.Image)(resources.GetObject("btnFill.Glyph")));
            this.btnFill.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnFillDownHint);
            this.btnFill.Id = 71;
            this.btnFill.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnFill.LargeGlyph")));
            this.btnFill.LargeImageIndex = 39;
            this.btnFill.Name = "btnFill";
            this.btnFill.SelectedColor = System.Drawing.Color.Empty;
            this.btnFill.SourcePropertyName = null;
            this.btnFill.TargetPropertyName = null;
            // 
            // btnLinecolor
            // 
            this.btnLinecolor.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnLinecolor.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnLinecolorCaption);
            this.btnLinecolor.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnLinecolor.Glyph = ((System.Drawing.Image)(resources.GetObject("btnLinecolor.Glyph")));
            this.btnLinecolor.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnLinecolorDownHint);
            this.btnLinecolor.Id = 72;
            this.btnLinecolor.Name = "btnLinecolor";
            this.btnLinecolor.SelectedColor = System.Drawing.Color.Empty;
            this.btnLinecolor.SourcePropertyName = null;
            this.btnLinecolor.TargetPropertyName = null;
            // 
            // btnPen
            // 
            this.btnPen.Caption = "Pen";
            this.btnPen.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnPen.Glyph = ((System.Drawing.Image)(resources.GetObject("btnPen.Glyph")));
            this.btnPen.Hint = "Draw using the current line color, pixel by pixel";
            this.btnPen.Id = 74;
            this.btnPen.ImageIndex = 35;
            this.btnPen.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnPen.LargeGlyph")));
            this.btnPen.LargeImageIndex = 23;
            this.btnPen.Name = "btnPen";
            this.btnPen.SourcePropertyName = null;
            this.btnPen.TargetPropertyName = null;
            // 
            // btnEraser
            // 
            this.btnEraser.Caption = "Eraser";
            this.btnEraser.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnEraser.Glyph = ((System.Drawing.Image)(resources.GetObject("btnEraser.Glyph")));
            this.btnEraser.Hint = "Changes cursor to the eraser which deletes the pixel beneath the eraser when left" +
                " mouse clicked";
            this.btnEraser.Id = 75;
            this.btnEraser.ImageIndex = 18;
            this.btnEraser.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnEraser.LargeGlyph")));
            this.btnEraser.LargeImageIndex = 40;
            this.btnEraser.Name = "btnEraser";
            this.btnEraser.SourcePropertyName = null;
            this.btnEraser.TargetPropertyName = null;
            // 
            // btnSendEditor
            // 
            this.btnSendInEditor.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnSendInEditor.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnSendInEditorCaption);
            this.btnSendInEditor.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnSendInEditor.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnSendInEditorHint);
            this.btnSendInEditor.DropDownControl = this.sendPopMenuEditor;
            this.btnSendInEditor.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.SendInEditor);
            this.btnSendInEditor.Id = 82;
            this.btnSendInEditor.ImageIndex = 44;
            this.btnSendInEditor.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.SendInEditor);
            this.btnSendInEditor.LargeImageIndex = 13;
            this.btnSendInEditor.Name = "btnSendSignInEdit";
            this.btnSendInEditor.SourcePropertyName = null;
            this.btnSendInEditor.TargetPropertyName = null;
            // 
            // btnSendPlaylist
            // 
            this.btnSendInPlaylist.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnSendInPlaylist.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnSendInPlaylistCaption);
            this.btnSendInPlaylist.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnSendInPlaylist.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnSendInPlaylistHint);
            this.btnSendInPlaylist.DropDownControl = this.sendPopMenuPlaylist;
            this.btnSendInPlaylist.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.SendInPlaylist);
            this.btnSendInPlaylist.Id = 82;
            this.btnSendInPlaylist.ImageIndex = 44;
            this.btnSendInPlaylist.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.SendInPlaylist);
            this.btnSendInPlaylist.LargeImageIndex = 13;
            this.btnSendInPlaylist.Name = "btnSendInPlaylist";
            this.btnSendInPlaylist.SourcePropertyName = null;
            this.btnSendInPlaylist.TargetPropertyName = null;
            // 
            // btnSendScheduler
            // 
            this.btnSendInScheduler.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnSendInScheduler.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnSendInSchedulerCaption);
            this.btnSendInScheduler.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnSendInScheduler.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnSendInSchedulerHint);
            this.btnSendInScheduler.DropDownControl = this.sendPopMenuScheduler;
            this.btnSendInScheduler.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.SendInScheduler);
            this.btnSendInScheduler.Id = 82;
            this.btnSendInScheduler.ImageIndex = 44;
            this.btnSendInScheduler.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.SendInScheduler);
            this.btnSendInScheduler.LargeImageIndex = 13;
            this.btnSendInScheduler.Name = "btnSendInScheduler";
            this.btnSendInScheduler.SourcePropertyName = null;
            this.btnSendInScheduler.TargetPropertyName = null;
            // 
            // sendPopMenuEditor
            // 
            this.sendPopMenuEditor.ItemLinks.Add(this.btnSendPlaylist);
            this.sendPopMenuEditor.ItemLinks.Add(this.btnSendSchedule);
            //this.sendPopMenuEditor.ItemLinks.Add(this.btnSendMessagetoSign);
            this.sendPopMenuEditor.Name = "sendPopMenuEditor";
            this.sendPopMenuEditor.Ribbon = this.ribbonControl1;
            // 
            // sendPopMenuPlaylist
            // 
            this.sendPopMenuPlaylist.ItemLinks.Add(this.btnSendSchedule);
            this.sendPopMenuPlaylist.Name = "sendPopMenuPlaylist";
            this.sendPopMenuPlaylist.Ribbon = this.ribbonControl1;
            // 
            // sendPopMenuScheduler
            // 
            this.sendPopMenuScheduler.ItemLinks.Add(this.btnSendSign);
            this.sendPopMenuScheduler.Name = "sendPopMenu";
            this.sendPopMenuScheduler.Ribbon = this.ribbonControl1;
            // 
            // btnSendSign
            // 
            this.btnSendSign.Caption = "Sign";
            this.btnSendSign.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnSendSign.Enabled = false;
            this.btnSendSign.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.TabPageDashBoard);
            this.btnSendSign.Hint = "Store the current Frame Object on the sign, and then play immediately with \"HOT\" " +
                "immediacy";
            this.btnSendSign.Id = 84;
            this.btnSendSign.ImageIndex = 45;
            this.btnSendSign.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnSendSign.LargeGlyph")));
            this.btnSendSign.LargeImageIndex = 12;
            this.btnSendSign.Name = "btnSendSign";
            this.btnSendSign.SourcePropertyName = null;
            this.btnSendSign.TargetPropertyName = null;
            this.btnSendSign.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;
            // 
            // btnSendPlaylist
            // 
            this.btnSendPlaylist.Caption = "Playlist";
            this.btnSendPlaylist.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnSendPlaylist.Enabled = false;
            this.btnSendPlaylist.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.PlaylistIcon16x16);
            this.btnSendPlaylist.Hint = "Send the current Frame Object to the end either a new playlist or a choice of cur" +
                "rent open playlist";
            this.btnSendPlaylist.Id = 85;
            this.btnSendPlaylist.ImageIndex = 36;
            this.btnSendPlaylist.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnSendPlaylist.LargeGlyph")));
            this.btnSendPlaylist.LargeImageIndex = 22;
            this.btnSendPlaylist.Name = "btnSendPlaylist";
            this.btnSendPlaylist.SourcePropertyName = null;
            this.btnSendPlaylist.TargetPropertyName = null;
            this.btnSendPlaylist.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;
            // 
            // btnSendSchedule
            // 
            this.btnSendSchedule.Caption = "Schedule";
            this.btnSendSchedule.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnSendSchedule.Enabled = false;
            this.btnSendSchedule.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.SchedulerIcon16x16);
            this.btnSendSchedule.Hint = "Send the current Frame Object to either a new schedule or a choice of currently o" +
                "pen schedules";
            this.btnSendSchedule.Id = 86;
            this.btnSendSchedule.ImageIndex = 7;
            this.btnSendSchedule.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnSendSchedule.LargeGlyph")));
            this.btnSendSchedule.LargeImageIndex = 3;
            this.btnSendSchedule.Name = "btnSendSchedule";
            this.btnSendSchedule.SourcePropertyName = null;
            this.btnSendSchedule.TargetPropertyName = null;
            this.btnSendSchedule.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;
            // 
            // btnSendSign
            // 
            this.btnSendMessagetoSign.Caption = "Play Now";
            this.btnSendMessagetoSign.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnSendMessagetoSign.Enabled = false;
            this.btnSendMessagetoSign.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.PlayNowIcon32);
            this.btnSendMessagetoSign.Hint = "Play content of Message continuously on sign, with no end date.";
            this.btnSendMessagetoSign.Id = 222;
            this.btnSendMessagetoSign.ImageIndex = 45;
            this.btnSendMessagetoSign.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.PlayNowIcon32);
            this.btnSendMessagetoSign.LargeImageIndex = 12;
            this.btnSendMessagetoSign.Name = "btnSendMessagetoSign";
            this.btnSendMessagetoSign.SourcePropertyName = null;
            this.btnSendMessagetoSign.TargetPropertyName = null;
            // 
            // btnSendPlayListtoSign
            // 
            this.btnSendPlayListtoSign.Caption = "Play Now";
            this.btnSendPlayListtoSign.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnSendPlayListtoSign.Enabled = false;
            this.btnSendPlayListtoSign.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.PlayNowIcon32);
            this.btnSendPlayListtoSign.Hint = "Play content of Playlist continuously on sign, with no end date.";
            this.btnSendPlayListtoSign.Id = 222;
            this.btnSendPlayListtoSign.ImageIndex = 45;
            this.btnSendPlayListtoSign.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.PlayNowIcon32);
            this.btnSendPlayListtoSign.LargeImageIndex = 12;
            this.btnSendPlayListtoSign.Name = "btnSendPlayListtoSign";
            this.btnSendPlayListtoSign.SourcePropertyName = null;
            this.btnSendPlayListtoSign.TargetPropertyName = null;

            // 
            // btnSendLive
            // 
            this.btnSendLive.Caption = "Live Storage";
            this.btnSendLive.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnSendLive.Enabled = false;
            this.btnSendLive.Glyph = ((System.Drawing.Image)(resources.GetObject("btnSendLive.Glyph")));
            this.btnSendLive.Hint = "Stores the current Frame Object on the sign";
            this.btnSendLive.Id = 83;
            this.btnSendLive.ImageIndex = 32;
            this.btnSendLive.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnSendLive.LargeGlyph")));
            this.btnSendLive.LargeImageIndex = 26;
            this.btnSendLive.Name = "btnSendLive";
            this.btnSendLive.SourcePropertyName = null;
            this.btnSendLive.TargetPropertyName = null;
            this.btnSendLive.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;
            // 
            // btnProperties
            // 
		    this.btnProperties.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Default;
            this.btnProperties.Caption = "Properties";
            this.btnProperties.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnProperties.Glyph = ((System.Drawing.Image)(resources.GetObject("btnProperties.Glyph")));
            this.btnProperties.Hint = "Configure a Sign; change Passwords, change parameters, etc...";
            this.btnProperties.Id = 87;
            this.btnProperties.ImageIndex = 37;
            this.btnProperties.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnProperties.LargeGlyph")));
            this.btnProperties.LargeImageIndex = 21;
            this.btnProperties.Name = "btnProperties";
            this.btnProperties.SourcePropertyName = null;
            this.btnProperties.TargetPropertyName = null;
            // 
            // btnInsertPlayList
            // 
            this.btnInsertPlayList.Caption = "Insert Playlist";
            this.btnInsertPlayList.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnInsertPlayList.Enabled = false;
            this.btnInsertPlayList.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.PlaylistIcon16x16);
            this.btnInsertPlayList.Hint = "Insert a Playlist into the current playlist at the current pointer location";
            this.btnInsertPlayList.Id = 88;
            this.btnInsertPlayList.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnInsertPlayList.LargeGlyph")));
            this.btnInsertPlayList.Name = "btnInsertPlayList";
            this.btnInsertPlayList.SourcePropertyName = null;
            this.btnInsertPlayList.TargetPropertyName = null;
            this.btnInsertPlayList.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;
            // 
            // btnInsertMessage
            // 
            this.btnInsertMessage.Caption = "Insert Message";
            this.btnInsertMessage.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnInsertMessage.Enabled = false;
            this.btnInsertMessage.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.MessageIcon16x16);
            this.btnInsertMessage.Hint = "Insert a Frame Object ¡°Message\" into the current playlist at the current pointer " +
                "location";
            this.btnInsertMessage.Id = 89;
            this.btnInsertMessage.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnInsertMessage.LargeGlyph")));
            this.btnInsertMessage.Name = "btnInsertMessage";
            this.btnInsertMessage.SourcePropertyName = null;
            this.btnInsertMessage.TargetPropertyName = null;
            this.btnInsertMessage.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;
            // 
            // btnInsertTimeSliceGrp
            // 
            this.btnInsertTimeSliceGrp.Caption = "Insert Time Slice Group";
            this.btnInsertTimeSliceGrp.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnInsertTimeSliceGrp.Enabled = false;
            this.btnInsertTimeSliceGrp.Glyph = ((System.Drawing.Image)(resources.GetObject("btnInsertTimeSliceGrp.Glyph")));
            this.btnInsertTimeSliceGrp.Hint = "Insert a Time Slice Group into the current playlist at the current pointer locati" +
                "on";
            this.btnInsertTimeSliceGrp.Id = 90;
            this.btnInsertTimeSliceGrp.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnInsertTimeSliceGrp.LargeGlyph")));
            this.btnInsertTimeSliceGrp.Name = "btnInsertTimeSliceGrp";
            this.btnInsertTimeSliceGrp.SourcePropertyName = null;
            this.btnInsertTimeSliceGrp.TargetPropertyName = null;
            this.btnInsertTimeSliceGrp.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;
            // 
            // barButtonItem58
            // 
            this.barButtonItem58.Caption = "Properties";
            this.barButtonItem58.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.barButtonItem58.Glyph = ((System.Drawing.Image)(resources.GetObject("barButtonItem58.Glyph")));
            this.barButtonItem58.Hint = "Edit the properties of the current playlist";
            this.barButtonItem58.Id = 92;
            this.barButtonItem58.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("barButtonItem58.LargeGlyph")));
            this.barButtonItem58.Name = "barButtonItem58";
            this.barButtonItem58.SourcePropertyName = null;
            this.barButtonItem58.TargetPropertyName = null;
            // 
            // barButtonItem59
            // 
            this.barButtonItem59.Caption = "Edit";
            this.barButtonItem59.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.barButtonItem59.Glyph = ((System.Drawing.Image)(resources.GetObject("barButtonItem59.Glyph")));
            this.barButtonItem59.Hint = "Send the current selected Frame Object in the Playlist to the Editor to be edited" +
                "";
            this.barButtonItem59.Id = 93;
            this.barButtonItem59.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("barButtonItem59.LargeGlyph")));
            this.barButtonItem59.Name = "barButtonItem59";
            this.barButtonItem59.SourcePropertyName = null;
            this.barButtonItem59.TargetPropertyName = null;
            // 
            // btnScheduleInsertPlaylist
            // 
            this.btnScheduleInsertPlaylist.Caption = "Insert Playlist";
            this.btnScheduleInsertPlaylist.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnScheduleInsertPlaylist.Glyph = ((System.Drawing.Image)(resources.GetObject("btnScheduleInsertPlaylist.Glyph")));
            this.btnScheduleInsertPlaylist.Id = 94;
            this.btnScheduleInsertPlaylist.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnScheduleInsertPlaylist.LargeGlyph")));
            this.btnScheduleInsertPlaylist.Name = "btnScheduleInsertPlaylist";
            this.btnScheduleInsertPlaylist.SourcePropertyName = null;
            this.btnScheduleInsertPlaylist.TargetPropertyName = null;
            // 
            // btnScheduleInsertMessage
            // 
            this.btnScheduleInsertMessage.Caption = "Insert Message";
            this.btnScheduleInsertMessage.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnScheduleInsertMessage.Glyph = ((System.Drawing.Image)(resources.GetObject("btnScheduleInsertMessage.Glyph")));
            this.btnScheduleInsertMessage.Id = 95;
            this.btnScheduleInsertMessage.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnScheduleInsertMessage.LargeGlyph")));
            this.btnScheduleInsertMessage.Name = "btnScheduleInsertMessage";
            this.btnScheduleInsertMessage.SourcePropertyName = null;
            this.btnScheduleInsertMessage.TargetPropertyName = null;
            // 
            // barButtonItem63
            // 
            this.barButtonItem63.Caption = "Properties";
            this.barButtonItem63.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.barButtonItem63.Glyph = ((System.Drawing.Image)(resources.GetObject("barButtonItem63.Glyph")));
            this.barButtonItem63.Id = 97;
            this.barButtonItem63.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("barButtonItem63.LargeGlyph")));
            this.barButtonItem63.Name = "barButtonItem63";
            this.barButtonItem63.SourcePropertyName = null;
            this.barButtonItem63.TargetPropertyName = null;
            // 
            // btnSystemInit
            // 
            this.btnSystemInit.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnSystemInitCaption);
            this.btnSystemInit.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnSystemInit.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnSystemInitHint);
            this.btnSystemInit.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.ProWriteInit16);
            this.btnSystemInit.Id = 108;
            this.btnSystemInit.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.ProWriteInit);
            this.btnSystemInit.Name = "btnSystemInit";
            this.btnSystemInit.SourcePropertyName = null;
            this.btnSystemInit.TargetPropertyName = null;
            // 
            // btnSystemDefault
            // 
            this.btnSystemDefault.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnSystemDefaultCaption);
            this.btnSystemDefault.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnSystemDefault.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnSystemDefaultHint);
            this.btnSystemDefault.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.SystemDefault16);
            this.btnSystemDefault.Id = 109;
            this.btnSystemDefault.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.SystemDefault);
            this.btnSystemDefault.Name = "btnSystemDefault";
            this.btnSystemDefault.SourcePropertyName = null;
            this.btnSystemDefault.TargetPropertyName = null;
            // 
            // btnUserManager
            // 
            this.btnUserManager.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnUserManagerCaption);
            this.btnUserManager.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnUserManager.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnUserManagerHint);
            this.btnUserManager.Enabled = false;
            this.btnUserManager.Glyph = Resources.Resource.GetImage(Resources.Resource.Images.UserManager16);
            this.btnUserManager.Id = 109;

            this.btnUserManager.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.UserManager);
            this.btnUserManager.Name = "btnUserManager";
            this.btnUserManager.SourcePropertyName = null;
            this.btnUserManager.TargetPropertyName = null;
            // 
            // btnRedo
            // 
            this.btnRedo.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnRedo.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnRedoCaption);
            this.btnRedo.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnRedo.DropDownControl = this.mnuRedoActionList;
            this.btnRedo.Glyph = ((System.Drawing.Image)(resources.GetObject("btnRedo.Glyph")));
            this.btnRedo.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnRedoHint);
            this.btnRedo.Id = 109;
            this.btnRedo.ItemShortcut = new DevExpress.XtraBars.BarShortcut((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Y));
            this.btnRedo.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnRedo.LargeGlyph")));
            this.btnRedo.Name = "btnRedo";
            this.btnRedo.SourcePropertyName = null;
            this.btnRedo.TargetPropertyName = null;
            // 
            // mnuRedoActionList
            // 
            this.mnuRedoActionList.Name = "mnuRedoActionList";
            this.mnuRedoActionList.Ribbon = this.ribbonControl1;
            // 
            // btnUndo
            // 
            this.btnUndo.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnUndo.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnUndoCaption);
            this.btnUndo.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnUndo.DropDownControl = this.mnuUndoActionList;
            this.btnUndo.Glyph = ((System.Drawing.Image)(resources.GetObject("btnUndo.Glyph")));
            this.btnUndo.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnUndoHint);
            this.btnUndo.Id = 110;
            this.btnUndo.ItemShortcut = new DevExpress.XtraBars.BarShortcut((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Z));
            this.btnUndo.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnUndo.LargeGlyph")));
            this.btnUndo.Name = "btnUndo";
            this.btnUndo.SourcePropertyName = null;
            this.btnUndo.TargetPropertyName = null;
            // 
            // mnuUndoActionList
            // 
            this.mnuUndoActionList.Name = "mnuUndoActionList";
            this.mnuUndoActionList.Ribbon = this.ribbonControl1;
            // 
            // btnCopy
            // 
            this.btnCopy.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnCopyCaption);
            this.btnCopy.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnCopy.Glyph = ((System.Drawing.Image)(resources.GetObject("btnCopy.Glyph")));
            this.btnCopy.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnCopyHint);
            this.btnCopy.Id = 112;
            this.btnCopy.ItemShortcut = new DevExpress.XtraBars.BarShortcut((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C));
            this.btnCopy.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnCopy.LargeGlyph")));
            this.btnCopy.Name = "btnCopy";
            this.btnCopy.RibbonStyle = DevExpress.XtraBars.Ribbon.RibbonItemStyles.SmallWithText;
            this.btnCopy.SourcePropertyName = null;
            this.btnCopy.TargetPropertyName = null;
            // 
            // btnPaste
            // 
            this.btnPaste.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnPasteCaption);
            this.btnPaste.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnPaste.Glyph = ((System.Drawing.Image)(resources.GetObject("btnPaste.Glyph")));
            this.btnPaste.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnPasteHint);
            this.btnPaste.Id = 113;
            this.btnPaste.ItemShortcut = new DevExpress.XtraBars.BarShortcut((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.V));
            this.btnPaste.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnPaste.LargeGlyph")));
            this.btnPaste.Name = "btnPaste";
            this.btnPaste.RibbonStyle = DevExpress.XtraBars.Ribbon.RibbonItemStyles.SmallWithText;
            this.btnPaste.SourcePropertyName = null;
            this.btnPaste.TargetPropertyName = null;
            // 
            // cmbSign
            // 
            this.cmbSign.Caption = Resource.GetString(Resource.Strings.RibbonBarcmbSignCaption);
            this.cmbSign.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.cmbSign.Edit = null;
            this.cmbSign.Hint = Resource.GetString(Resource.Strings.RibbonBarcmbSignHint);
            this.cmbSign.Id = 120;
            this.cmbSign.Name = "cmbSign";
            this.cmbSign.RibbonStyle = DevExpress.XtraBars.Ribbon.RibbonItemStyles.SmallWithoutText;
            this.cmbSign.SourcePropertyName = null;
            this.cmbSign.TargetPropertyName = null;
		    this.cmbSign.RibbonStyle = RibbonItemStyles.SmallWithoutText;

            // 
            // cmbSession
            // 
            this.cmbSession.Caption = Resource.GetString(Resource.Strings.RibbonBarcmbSignCaption);
            //this.cmbSession.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.cmbSession.Edit = null;
            this.cmbSession.Hint = Resource.GetString(Resource.Strings.RibbonBarcmbSignHint);
            this.cmbSession.Id = 35;
            this.cmbSession.Name = "cmbSession";
            this.cmbSession.RibbonStyle = DevExpress.XtraBars.Ribbon.RibbonItemStyles.SmallWithoutText;
            //this.cmbSession.SourcePropertyName = null;
            //this.cmbSession.TargetPropertyName = null;
            this.cmbSession.RibbonStyle = RibbonItemStyles.SmallWithoutText;
            // 
            // btnBold
            // 
            this.btnBold.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            this.btnBold.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnBoldCaption);
            this.btnBold.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnBold.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnBoldHint);
            this.btnBold.Glyph = ((System.Drawing.Image)(resources.GetObject("btnBold.Glyph")));
            this.btnBold.Id = 123;
            this.btnBold.Name = "btnBold";
            this.btnBold.SourcePropertyName = null;
            this.btnBold.TargetPropertyName = null;
            // 
            // btnItalic
            // 
            this.btnItalic.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            this.btnItalic.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnItalicCaption);
            this.btnItalic.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnItalic.Glyph = ((System.Drawing.Image)(resources.GetObject("btnItalic.Glyph")));
            this.btnItalic.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnItalicHint);
            this.btnItalic.Id = 124;
            this.btnItalic.Name = "btnItalic";
            this.btnItalic.SourcePropertyName = null;
            this.btnItalic.TargetPropertyName = null;
            // 
            // btnAlignLeft
            // 
            this.btnAlignLeft.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            this.btnAlignLeft.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnAlignLeftCaption);
            this.btnAlignLeft.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnAlignLeft.Glyph = ((System.Drawing.Image)(resources.GetObject("btnAlignLeft.Glyph")));
            this.btnAlignLeft.GroupIndex = 1;
            this.btnAlignLeft.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnAlignLeftHint);
            this.btnAlignLeft.Id = 125;
            this.btnAlignLeft.Name = "btnAlignLeft";
            this.btnAlignLeft.SourcePropertyName = null;
            this.btnAlignLeft.TargetPropertyName = null;
            // 
            // btnCenter
            // 
            this.btnCenter.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            this.btnCenter.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnCenterCaption);
            this.btnCenter.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnCenter.Glyph = ((System.Drawing.Image)(resources.GetObject("btnCenter.Glyph")));
            this.btnCenter.GroupIndex = 1;
            this.btnCenter.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnCenterHint);
            this.btnCenter.Id = 126;
            this.btnCenter.Name = "btnCenter";
            this.btnCenter.SourcePropertyName = null;
            this.btnCenter.TargetPropertyName = null;
            // 
            // btnAlignRight
            // 
            this.btnAlignRight.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            this.btnAlignRight.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnAlignRightCaption);
            this.btnAlignRight.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnAlignRight.Glyph = ((System.Drawing.Image)(resources.GetObject("btnAlignRight.Glyph")));
            this.btnAlignRight.GroupIndex = 1;
            this.btnAlignRight.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnAlignRightHint);
            this.btnAlignRight.Id = 127;
            this.btnAlignRight.Name = "btnAlignRight";
            this.btnAlignRight.SourcePropertyName = null;
            this.btnAlignRight.TargetPropertyName = null;
            // 
            // btnFontColor
            // 
            this.btnFontColor.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnFontColor.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnFontColorCaption);
            this.btnFontColor.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnFontColor.Glyph = ((System.Drawing.Image)(resources.GetObject("btnFontColor.Glyph")));
            this.btnFontColor.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnFontColorHint);
            this.btnFontColor.Id = 128;
            this.btnFontColor.Name = "btnFontColor";
            this.btnFontColor.SelectedColor = System.Drawing.Color.Empty;
            this.btnFontColor.SourcePropertyName = null;
            this.btnFontColor.TargetPropertyName = null;
            // 
            // btnBackGroundColor
            // 
            this.btnBackGroundColor.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnBackGroundColor.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnBackGroundColorCaption);
            this.btnBackGroundColor.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnBackGroundColor.Glyph = ((System.Drawing.Image)(resources.GetObject("btnBackGroundColor.Glyph")));
            this.btnBackGroundColor.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnBackGroundColorHint);
            this.btnBackGroundColor.Id = 129;
            this.btnBackGroundColor.Name = "btnBackGroundColor";
            this.btnBackGroundColor.SelectedColor = System.Drawing.Color.Empty;
            this.btnBackGroundColor.SourcePropertyName = null;
            this.btnBackGroundColor.TargetPropertyName = null;
            // 
            // btnTextFrameFixed
            // 
            this.btnTextFrameFixed.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            this.btnTextFrameFixed.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnTextFrameFixedCaption);
            this.btnTextFrameFixed.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnTextFrameFixed.Description = "Text font size can be changed automaticaly.";
		    this.btnTextFrameFixed.Glyph = Resource.GetImage(Resource.Images.FrameFixedTrue16);
            this.btnTextFrameFixed.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnTextFrameFixedHint);
            this.btnTextFrameFixed.Id = 130;
            this.btnTextFrameFixed.Name = "btnTextFrameFixed";
            this.btnTextFrameFixed.SourcePropertyName = null;
            this.btnTextFrameFixed.TargetPropertyName = null;
		    this.btnTextFrameFixed.Down = true;
            // 
            // btnFontSizeFixed
            // 
            this.btnFontSizeFixed.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            this.btnFontSizeFixed.Caption = "Font Sizes Fixed";
            this.btnFontSizeFixed.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnFontSizeFixed.Description = "Text size can not be changed.";
            this.btnFontSizeFixed.Glyph = ((System.Drawing.Image)(resources.GetObject("btnFontSizeFixed.Glyph")));
            this.btnFontSizeFixed.Hint = "Font Sizes Fixed";
            this.btnFontSizeFixed.Id = 131;
            this.btnFontSizeFixed.Name = "btnFontSizeFixed";
            this.btnFontSizeFixed.SourcePropertyName = null;
            this.btnFontSizeFixed.TargetPropertyName = null;
            // 
            // btnWindows
            // 
            this.btnWindows.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnWindows.Caption = "Windows";
            this.btnWindows.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnWindows.Description = "Show or hide the windows.";
            this.btnWindows.DropDownControl = this.windowsList;
            this.btnWindows.Glyph = ((System.Drawing.Image)(resources.GetObject("btnWindows.Glyph")));
            this.btnWindows.Id = 132;
            this.btnWindows.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnWindows.LargeGlyph")));
            this.btnWindows.Name = "btnWindows";
            this.btnWindows.SourcePropertyName = null;
            this.btnWindows.TargetPropertyName = null;
            // 
            // windowsList
            // 
            this.windowsList.Name = "windowsList";
            this.windowsList.Ribbon = this.ribbonControl1;
            // 
            // barBtnGrpTextColor
            // 
            this.barBtnGrpTextColor.Id = 134;
            this.barBtnGrpTextColor.ItemLinks.Add(this.btnBackGroundColor);
            this.barBtnGrpTextColor.ItemLinks.Add(this.btnFontColor);
            this.barBtnGrpTextColor.Name = "barBtnGrpTextColor";
            // 
            // barBtnGrpTextAlign
            // 
            this.barBtnGrpTextAlign.Id = 135;
            this.barBtnGrpTextAlign.ItemLinks.Add(this.btnAlignLeft);
            this.barBtnGrpTextAlign.ItemLinks.Add(this.btnCenter);
            this.barBtnGrpTextAlign.ItemLinks.Add(this.btnAlignRight);
            this.barBtnGrpTextAlign.Name = "barBtnGrpTextAlign";
            // 
            // barBtnGrpTextFixed
            // 
            this.barBtnGrpTextFixed.Id = 136;
            this.barBtnGrpTextFixed.ItemLinks.Add(this.btnTextFrameFixed);
            //this.barBtnGrpTextFixed.ItemLinks.Add(this.btnFontSizeFixed);
            this.barBtnGrpTextFixed.Name = "barBtnGrpTextFixed";
            // 
            // btnTextFontName
            // 
		    this.btnTextFontName.Caption = "";// Resource.GetString(Resource.Strings.RibbonBarbtnTextFontNameCaption);
            this.btnTextFontName.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnTextFontName.Description = "Change text font.";
            this.btnTextFontName.Edit = this.repositoryItemPopupContainerEdit3;
            //this.btnTextFontName.Edit = this.cmbTextFontName;
            //this.btnTextFontName.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnTextFontNameHint);
            this.btnTextFontName.Id = 137;
            this.btnTextFontName.Name = "btnTextFontName";
            this.btnTextFontName.SourcePropertyName = null;
            this.btnTextFontName.TargetPropertyName = null;
            this.textNameTipTitle.Text = Resource.GetString(Resource.Strings.RibbonBarbtnTextFontNameCaption);
            this.textNameTipItem.LeftIndent = 6;
            this.textNameTipItem.Text = Resource.GetString(Resource.Strings.RibbonBarbtnTextFontNameHint);
            this.textNameSuperTip.Items.Add(textNameTipTitle);
            this.textNameSuperTip.Items.Add(textNameTipItem);
		    this.btnTextFontName.SuperTip = textNameSuperTip;
            // 
            // cmbTextFontName
            // 
            this.cmbTextFontName.AutoHeight = false;
            this.cmbTextFontName.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.cmbTextFontName.Name = "cmbTextFontName";
            // 
            // btnTextFontSize
            // 
		    this.btnTextFontSize.Caption = "";// Resource.GetString(Resource.Strings.RibbonBarbtnTextFontSizeCaption);
            this.btnTextFontSize.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnTextFontSize.Description = "Change text size.";
            this.btnTextFontSize.Edit = this.cmbTextFontSize;
            //this.btnTextFontSize.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnTextFontSizeHint);
            this.btnTextFontSize.Id = 138;
            this.btnTextFontSize.Name = "btnTextFontSize";
            this.btnTextFontSize.SourcePropertyName = null;
            this.btnTextFontSize.TargetPropertyName = null;
            this.textSizeTipTitle.Text = Resource.GetString(Resource.Strings.RibbonBarbtnTextFontSizeCaption);
            this.textSizeTipItem.LeftIndent = 6;
            this.textSizeTipItem.Text = Resource.GetString(Resource.Strings.RibbonBarbtnTextFontSizeHint);
            this.textSizeSuperTip.Items.Add(textSizeTipTitle);
            this.textSizeSuperTip.Items.Add(textSizeTipItem);
            this.btnTextFontSize.SuperTip = textSizeSuperTip;            // 
            // cmbTextFontSize
            // 
            this.cmbTextFontSize.AutoHeight = false;
            this.cmbTextFontSize.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.cmbTextFontSize.DisplayFormat.FormatType = DevExpress.Utils.FormatType.Numeric;
            this.cmbTextFontSize.EditFormat.FormatType = DevExpress.Utils.FormatType.Numeric;
            this.cmbTextFontSize.Name = "cmbTextFontSize";
		    this.cmbTextFontSize.Enabled = false;
            this.cmbTextFontSize.TextEditStyle = DevExpress.XtraEditors.Controls.TextEditStyles.DisableTextEditor;
            // 
            // btnLine
            // 
            this.btnLine.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnLineCaption);
            this.btnLine.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnLine.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnLineHint);
            this.btnLine.Glyph = ((System.Drawing.Image)(resources.GetObject("btnLine.Glyph")));
            this.btnLine.Id = 139;
            this.btnLine.Name = "btnLine";
            this.btnLine.SourcePropertyName = null;
            this.btnLine.TargetPropertyName = null;
            // 
            // barBtnGrpPaintLine
            // 
            this.barBtnGrpPaintLine.Id = 140;
            this.barBtnGrpPaintLine.ItemLinks.Add(this.btnPointer);
            this.barBtnGrpPaintLine.ItemLinks.Add(this.btnLine);
            this.barBtnGrpPaintLine.ItemLinks.Add(this.btnLinecolor);
            this.barBtnGrpPaintLine.Name = "barBtnGrpPaintLine";
            // 
            // btnPointer
            // 
            this.btnPointer.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnPointerCaption);
            this.btnPointer.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnPointer.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnPointerHint);
            this.btnPointer.Glyph = ((System.Drawing.Image)(resources.GetObject("btnPointer.Glyph")));
            this.btnPointer.Id = 179;
            this.btnPointer.Name = "btnPointer";
            this.btnPointer.SourcePropertyName = null;
            this.btnPointer.TargetPropertyName = null;
            // 
            // barBtnGrpPaintShape
            // 
            this.barBtnGrpPaintShape.Id = 141;
            this.barBtnGrpPaintShape.ItemLinks.Add(this.btnDrawing);
            this.barBtnGrpPaintShape.ItemLinks.Add(this.btnFill);
            this.barBtnGrpPaintShape.Name = "barBtnGrpPaintShape";
            // 
            // barEditTextEffect
            // 
            this.barEditTextEffect.Caption = Resource.GetString(Resource.Strings.RibbonBarbarEditTextEffectCaption);
            this.barEditTextEffect.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.barEditTextEffect.Description = "Change text display.";
            this.barEditTextEffect.Edit = this.repositoryItemTextEffectEdit;
            this.barEditTextEffect.Hint = Resource.GetString(Resource.Strings.RibbonBarbarEditTextEffectHint);
            this.barEditTextEffect.Id = 142;
            this.barEditTextEffect.Name = "barEditTextEffect";
            this.barEditTextEffect.SourcePropertyName = null;
            this.barEditTextEffect.TargetPropertyName = null;
		    this.barEditTextEffect.RibbonStyle = RibbonItemStyles.SmallWithoutText;
            // 
            // repositoryItemTextEffectEdit
            // 
            this.repositoryItemTextEffectEdit.AutoHeight = false;
            this.repositoryItemTextEffectEdit.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.repositoryItemTextEffectEdit.Name = "repositoryItemTextEffectEdit";
            // 
            // barBtnGrpTextBoldItalic
            // 
            this.barBtnGrpTextBoldItalic.Id = 143;
            this.barBtnGrpTextBoldItalic.ItemLinks.Add(this.btnBold);
            this.barBtnGrpTextBoldItalic.ItemLinks.Add(this.btnItalic);
            this.barBtnGrpTextBoldItalic.Name = "barBtnGrpTextBoldItalic";
            // 
            // btnOpen
            // 
            this.btnOpen.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnOpen.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnOpenCaption);
            this.btnOpen.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnOpen.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnOpenHint);
            this.btnOpen.DropDownControl = this.mnuOpen;
            this.btnOpen.Glyph = ((System.Drawing.Image)(resources.GetObject("btnOpen.Glyph")));
            this.btnOpen.Id = 144;
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.RibbonStyle = DevExpress.XtraBars.Ribbon.RibbonItemStyles.SmallWithText;
            this.btnOpen.SourcePropertyName = null;
            this.btnOpen.TargetPropertyName = null;
            // 
            // mnuOpen
            // 
            //this.mnuOpen.ItemLinks.Add(this.btnOpenFile);
            this.mnuOpen.ItemLinks.Add(this.btnOpenLibrary);
            this.mnuOpen.Name = "mnuOpen";
            this.mnuOpen.Ribbon = this.ribbonControl1;
            // 
            // btnOpenFile
            // 
            this.btnOpenFile.Caption = "PW File";
            this.btnOpenFile.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnOpenFile.Id = 174;
            this.btnOpenFile.Name = "btnOpenFile";
            this.btnOpenFile.SourcePropertyName = null;
            this.btnOpenFile.TargetPropertyName = null;
            // 
            // btnOpenLibrary
            // 
            this.btnOpenLibrary.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnOpenLibraryCaption);
            this.btnOpenLibrary.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnOpenLibrary.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnOpenLibraryHint);
            this.btnOpenLibrary.Id = 175;
		    this.btnOpenLibrary.Glyph = Resource.GetImage(Resource.Images.NewLibrary16);
            this.btnOpenLibrary.Name = "btnOpenLibrary";
            this.btnOpenLibrary.SourcePropertyName = null;
            this.btnOpenLibrary.TargetPropertyName = null;
            // 
            // barBtnGrpNew
            // 
            this.barBtnGrpNew.Id = 145;
            this.barBtnGrpNew.ItemLinks.Add(this.btnNew);
            this.barBtnGrpNew.Name = "barBtnGrpNew";
            // 
            // btnView
            // 
            this.btnView.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnView.Caption = "View";
            this.btnView.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnView.DropDownControl = this.mnuView;
            this.btnView.Id = 148;
            this.btnView.Name = "btnView";
            this.btnView.SourcePropertyName = null;
            this.btnView.TargetPropertyName = null;
            // 
            // mnuView
            // 
            this.mnuView.ItemLinks.Add(this.barCheckItem1);
            this.mnuView.Name = "mnuView";
            this.mnuView.Ribbon = this.ribbonControl1;
            // 
            // barCheckItem1
            // 
            this.barCheckItem1.Caption = "Test1";
            this.barCheckItem1.Id = 149;
            this.barCheckItem1.Name = "barCheckItem1";
            // 
            // btnInsert
            // 
            this.btnInsert.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnInsert.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnInsertCaption);
            this.btnInsert.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnInsert.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnInsertHint);
            this.btnInsert.DropDownControl = this.mnuInsert;
            this.btnInsert.Id = 150;
            this.btnInsert.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnInsert.LargeGlyph")));
            this.btnInsert.Name = "btnInsert";
            this.btnInsert.SourcePropertyName = null;
            this.btnInsert.TargetPropertyName = null;
            // 
            // mnuInsert
            // 
            this.mnuInsert.ItemLinks.Add(this.btnInsertText);
            this.mnuInsert.ItemLinks.Add(this.btnInsertImage);
            this.mnuInsert.ItemLinks.Add(this.btnInsertVideo);
            
            //this.mnuInsert.ItemLinks.Add(this.btnInsertVariableText);
            this.mnuInsert.ItemLinks.Add(this.btnInsertTime);
            this.mnuInsert.ItemLinks.Add(this.btnInsertTemperature);
            this.mnuInsert.ItemLinks.Add(this.btnInsertVariableVideo);
            this.mnuInsert.ItemLinks.Add(this.btnInsertMessage);
            this.mnuInsert.ItemLinks.Add(this.btnInsertTimeSliceGrp);
            this.mnuInsert.ItemLinks.Add(this.btnInsertPlayList);
            this.mnuInsert.Name = "mnuInsert";
            this.mnuInsert.Ribbon = this.ribbonControl1;
            // 
            // btnInsertVariableVideo
            // 
            this.btnInsertVariableVideo.Caption = "Insert Variable Video";
            this.btnInsertVariableVideo.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnInsertVariableVideo.Enabled = false;
            this.btnInsertVariableVideo.Id = 173;
            this.btnInsertVariableVideo.Name = "btnInsertVariableVideo";
            this.btnInsertVariableVideo.SourcePropertyName = null;
            this.btnInsertVariableVideo.TargetPropertyName = null;
            this.btnInsertVariableVideo.Visibility = DevExpress.XtraBars.BarItemVisibility.Never;
            // 
            // btnDropDownPlaylistInsert
            // 
            this.btnDropDownPlaylistInsert.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnDropDownPlaylistInsert.Caption = "Insert";
            this.btnDropDownPlaylistInsert.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnDropDownPlaylistInsert.DropDownControl = this.mnuPlaylistInsert;
            this.btnDropDownPlaylistInsert.Id = 151;
            this.btnDropDownPlaylistInsert.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnDropDownPlaylistInsert.LargeGlyph")));
            this.btnDropDownPlaylistInsert.Name = "btnDropDownPlaylistInsert";
            this.btnDropDownPlaylistInsert.SourcePropertyName = null;
            this.btnDropDownPlaylistInsert.TargetPropertyName = null;
            // 
            // mnuPlaylistInsert
            // 
            this.mnuPlaylistInsert.ItemLinks.Add(this.btnInsertMessage);
            this.mnuPlaylistInsert.ItemLinks.Add(this.btnInsertTimeSliceGrp);
            this.mnuPlaylistInsert.ItemLinks.Add(this.btnInsertPlayList);
            this.mnuPlaylistInsert.Name = "mnuPlaylistInsert";
            this.mnuPlaylistInsert.Ribbon = this.ribbonControl1;
            // 
            // btnDropDownSchedulerInsert
            // 
            this.btnDropDownSchedulerInsert.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnDropDownSchedulerInsert.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnInsertCaption);
            this.btnDropDownSchedulerInsert.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnDropDownSchedulerInsert.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnInsertHint);
            this.btnDropDownSchedulerInsert.DropDownControl = this.mnuSchedulerInsert;
            this.btnDropDownSchedulerInsert.Id = 152;
            this.btnDropDownSchedulerInsert.LargeGlyph = ((System.Drawing.Image)(resources.GetObject("btnDropDownSchedulerInsert.LargeGlyph")));
            this.btnDropDownSchedulerInsert.Name = "btnDropDownSchedulerInsert";
            this.btnDropDownSchedulerInsert.SourcePropertyName = null;
            this.btnDropDownSchedulerInsert.TargetPropertyName = null;
            // 
            // mnuSchedulerInsert
            // 
            this.mnuSchedulerInsert.ItemLinks.Add(this.btnScheduleInsertMessage);
            this.mnuSchedulerInsert.ItemLinks.Add(this.btnScheduleInsertPlaylist);
            this.mnuSchedulerInsert.Name = "mnuSchedulerInsert";
            this.mnuSchedulerInsert.Ribbon = this.ribbonControl1;
            // 
            // btnClearCXCLog
            // 
            this.btnClearCXCLog.Caption = "Clear CXC Log Files";
            this.btnClearCXCLog.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnClearCXCLog.Glyph = ((System.Drawing.Image)(resources.GetObject("btnClearCXCLog.Glyph")));
            this.btnClearCXCLog.Id = 162;
            this.btnClearCXCLog.Name = "btnClearCXCLog";
            this.btnClearCXCLog.SourcePropertyName = null;
            this.btnClearCXCLog.TargetPropertyName = null;
            // 
            // btnTextKern
            // 
            this.btnTextKern.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnTextKernCaption);
            this.btnTextKern.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnTextKern.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnTextKernHint);
            this.btnTextKern.Edit = this.repositoryItemKernEdit;
            this.btnTextKern.Id = 164;
            this.btnTextKern.Name = "btnTextKern";
            this.btnTextKern.RibbonStyle = DevExpress.XtraBars.Ribbon.RibbonItemStyles.SmallWithText;
            this.btnTextKern.SourcePropertyName = null;
            this.btnTextKern.TargetPropertyName = null;
            // 
            // repositoryItemKernEdit
            // 
            this.repositoryItemKernEdit.AllowNullInput = DevExpress.Utils.DefaultBoolean.False;
            this.repositoryItemKernEdit.AutoHeight = false;
            this.repositoryItemKernEdit.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.repositoryItemKernEdit.EditFormat.FormatType = DevExpress.Utils.FormatType.Numeric;
            this.repositoryItemKernEdit.IsFloatValue = false;
            this.repositoryItemKernEdit.Mask.EditMask = "N00";
            this.repositoryItemKernEdit.MaxValue = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.repositoryItemKernEdit.Name = "repositoryItemKernEdit";
            this.repositoryItemKernEdit.NullText = "0";
            // 
            // btnTextLead
            // 
            this.btnTextLead.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnTextLeadCaption);
            this.btnTextLead.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnTextLead.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnTextLeadHint);
            this.btnTextLead.Edit = this.repositoryItemLeadEdit;
            this.btnTextLead.Id = 165;
            this.btnTextLead.Name = "btnTextLead";
            this.btnTextLead.RibbonStyle = DevExpress.XtraBars.Ribbon.RibbonItemStyles.SmallWithText;
            this.btnTextLead.SourcePropertyName = null;
            this.btnTextLead.TargetPropertyName = null;
            // 
            // repositoryItemLeadEdit
            // 
            this.repositoryItemLeadEdit.AllowNullInput = DevExpress.Utils.DefaultBoolean.False;
            this.repositoryItemLeadEdit.AutoHeight = false;
            this.repositoryItemLeadEdit.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.repositoryItemLeadEdit.EditFormat.FormatType = DevExpress.Utils.FormatType.Numeric;
            this.repositoryItemLeadEdit.IsFloatValue = false;
            this.repositoryItemLeadEdit.Mask.EditMask = "N00";
            this.repositoryItemLeadEdit.MaxValue = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.repositoryItemLeadEdit.Name = "repositoryItemLeadEdit";
            this.repositoryItemLeadEdit.NullText = "0";
            // 
            // btnTestPatternExitTest
            // 
            this.btnTestPatternExitTest.Caption = "Exit Test";
            this.btnTestPatternExitTest.Id = 190;
            this.btnTestPatternExitTest.Name = "btnTestPatternExitTest";
            // 
            // btnTestPatternHRamp
            // 
            this.btnTestPatternHRamp.Caption = "H Ramp";
            this.btnTestPatternHRamp.Id = 192;
            this.btnTestPatternHRamp.Name = "btnTestPatternHRamp";
            // 
            // btnTestPatternVRamp
            // 
            this.btnTestPatternVRamp.Caption = "V Ramp";
            this.btnTestPatternVRamp.Id = 193;
            this.btnTestPatternVRamp.Name = "btnTestPatternVRamp";
            // 
            // btnTestPatternCross
            // 
            this.btnTestPatternCross.Caption = "Cross";
            this.btnTestPatternCross.Id = 194;
            this.btnTestPatternCross.Name = "btnTestPatternCross";
            // 
            // btnTestPatternDiagonal
            // 
            this.btnTestPatternDiagonal.Caption = "Diagonal";
            this.btnTestPatternDiagonal.Id = 195;
            this.btnTestPatternDiagonal.Name = "btnTestPatternDiagonal";
            // 
            // btnTestPatternVertical
            // 
            this.btnTestPatternVertical.Caption = "Vertical";
            this.btnTestPatternVertical.Id = 196;
            this.btnTestPatternVertical.Name = "btnTestPatternVertical";
            // 
            // btnTestPatternColorBar
            // 
            this.btnTestPatternColorBar.Caption = "Color Bar";
            this.btnTestPatternColorBar.Id = 197;
            this.btnTestPatternColorBar.Name = "btnTestPatternColorBar";
            // 
            // btnTestPatternColorGrid
            // 
            this.btnTestPatternColorGrid.Caption = "Color Grid";
            this.btnTestPatternColorGrid.Id = 198;
            this.btnTestPatternColorGrid.Name = "btnTestPatternColorGrid";
            // 
            // btnTestPatternSolidColorRed
            // 
            this.btnTestPatternSolidColorRed.Caption = "Red";
            this.btnTestPatternSolidColorRed.Id = 199;
            this.btnTestPatternSolidColorRed.Name = "btnTestPatternSolidColorRed";
            // 
            // btnTestPatternSolidColorGreen
            // 
            this.btnTestPatternSolidColorGreen.Caption = "Green";
            this.btnTestPatternSolidColorGreen.Id = 200;
            this.btnTestPatternSolidColorGreen.Name = "btnTestPatternSolidColorGreen";
            // 
            // btnTestPatternSolidColorBlue
            // 
            this.btnTestPatternSolidColorBlue.Caption = "Blue";
            this.btnTestPatternSolidColorBlue.Id = 201;
            this.btnTestPatternSolidColorBlue.Name = "btnTestPatternSolidColorBlue";
            // 
            // btnTestPatternSolidColorWhite
            // 
            this.btnTestPatternSolidColorWhite.Caption = "White";
            this.btnTestPatternSolidColorWhite.Id = 202;
            this.btnTestPatternSolidColorWhite.Name = "btnTestPatternSolidColorWhite";
            // 
            // btnTestPatternSolidColorAmber
            // 
            this.btnTestPatternSolidColorAmber.Caption = "Amber";
            this.btnTestPatternSolidColorAmber.Id = 203;
            this.btnTestPatternSolidColorAmber.Name = "btnTestPatternSolidColorAmber";
            // 
            // btnTestPatternSolidColor
            // 
            this.btnTestPatternSolidColor.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.DropDown;
            this.btnTestPatternSolidColor.Caption = "Solid Color";
            this.btnTestPatternSolidColor.DropDownControl = this.popupMenu2;
            this.btnTestPatternSolidColor.Id = 207;
            this.btnTestPatternSolidColor.Name = "btnTestPatternSolidColor";
            // 
            // popupMenu2
            // 
            this.popupMenu2.ItemLinks.Add(this.btnTestPatternSolidColorRed);
            this.popupMenu2.ItemLinks.Add(this.btnTestPatternSolidColorGreen);
            this.popupMenu2.ItemLinks.Add(this.btnTestPatternSolidColorBlue);
            this.popupMenu2.ItemLinks.Add(this.btnTestPatternSolidColorWhite);
            this.popupMenu2.ItemLinks.Add(this.btnTestPatternSolidColorAmber);
            this.popupMenu2.Name = "popupMenu2";
            this.popupMenu2.Ribbon = this.ribbonControl1;

            // 
            // popupMenu1
            // 
            this.popupMenu1.ItemLinks.Add(this.btnTestPatternExitTest);
            this.popupMenu1.ItemLinks.Add(this.btnTestPatternSolidColor);
            this.popupMenu1.ItemLinks.Add(this.btnTestPatternHRamp);
            this.popupMenu1.ItemLinks.Add(this.btnTestPatternVRamp);
            this.popupMenu1.ItemLinks.Add(this.btnTestPatternCross);
            this.popupMenu1.ItemLinks.Add(this.btnTestPatternDiagonal);
            this.popupMenu1.ItemLinks.Add(this.btnTestPatternVertical);
            this.popupMenu1.ItemLinks.Add(this.btnTestPatternColorBar);
            this.popupMenu1.ItemLinks.Add(this.btnTestPatternColorGrid);
            this.popupMenu1.Name = "popupMenu1";
		    this.popupMenu1.Ribbon = this.ribbonControl1;

            // 
            // btnLiveCategoryAdd
            // 
            this.btnLiveCategoryAdd.Caption = "Add Category";
            this.btnLiveCategoryAdd.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnLiveCategoryAdd.Hint = "Add Category";
            this.btnLiveCategoryAdd.Id = 166;
            this.btnLiveCategoryAdd.Name = "btnLiveCategoryAdd";
            this.btnLiveCategoryAdd.SourcePropertyName = null;
            this.btnLiveCategoryAdd.TargetPropertyName = null;
            // 
            // btnLiveCategoryRemove
            // 
            this.btnLiveCategoryRemove.Caption = "Remove Category";
            this.btnLiveCategoryRemove.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnLiveCategoryRemove.Hint = "Remove Category";
            this.btnLiveCategoryRemove.Id = 167;
            this.btnLiveCategoryRemove.Name = "btnLiveCategoryRemove";
            this.btnLiveCategoryRemove.SourcePropertyName = null;
            this.btnLiveCategoryRemove.TargetPropertyName = null;
            // 
            // btnLiveCategoryRename
            // 
            this.btnLiveCategoryRename.Caption = "Rename Category";
            this.btnLiveCategoryRename.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnLiveCategoryRename.Hint = "Rename Category";
            this.btnLiveCategoryRename.Id = 168;
            this.btnLiveCategoryRename.Name = "btnLiveCategoryRename";
            this.btnLiveCategoryRename.SourcePropertyName = null;
            this.btnLiveCategoryRename.TargetPropertyName = null;
            // 
            // btnLiveItemAdd
            // 
            this.btnLiveItemAdd.Caption = "Add Item";
            this.btnLiveItemAdd.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnLiveItemAdd.Id = 169;
            this.btnLiveItemAdd.Name = "btnLiveItemAdd";
            this.btnLiveItemAdd.SourcePropertyName = null;
            this.btnLiveItemAdd.TargetPropertyName = null;
            // 
            // btnLiveItemRemove
            // 
            this.btnLiveItemRemove.Caption = "Remove Item";
            this.btnLiveItemRemove.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnLiveItemRemove.Id = 170;
            this.btnLiveItemRemove.Name = "btnLiveItemRemove";
            this.btnLiveItemRemove.SourcePropertyName = null;
            this.btnLiveItemRemove.TargetPropertyName = null;
            // 
            // btnLiveItemRename
            // 
            this.btnLiveItemRename.Caption = "Rename Item";
            this.btnLiveItemRename.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnLiveItemRename.Hint = "Rename Item";
            this.btnLiveItemRename.Id = 171;
            this.btnLiveItemRename.Name = "btnLiveItemRename";
            this.btnLiveItemRename.SourcePropertyName = null;
            this.btnLiveItemRename.TargetPropertyName = null;
            // 
            // btnLiveCXCResourceLibrary
            // 
            this.btnLiveCXCResourceLibrary.ButtonStyle = DevExpress.XtraBars.BarButtonStyle.Check;
            this.btnLiveCXCResourceLibrary.Caption = "CXC Resource";
            this.btnLiveCXCResourceLibrary.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.btnLiveCXCResourceLibrary.Id = 172;
            this.btnLiveCXCResourceLibrary.Name = "btnLiveCXCResourceLibrary";
            this.btnLiveCXCResourceLibrary.SourcePropertyName = null;
            this.btnLiveCXCResourceLibrary.TargetPropertyName = null;
            // 
            // barButtonGroup1
            // 
            this.barButtonGroup1.Id = 176;
            this.barButtonGroup1.ItemLinks.Add(this.btnNew);
            this.barButtonGroup1.Name = "barButtonGroup1";
            // 
            // btnZoomIn
            // 
            this.btnZoomIn.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnZoomInLeadCaption);
            this.btnZoomIn.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
		    this.btnZoomIn.Glyph = Resource.GetImage(Resource.Images.ZoomIn16);
            this.btnZoomIn.Id = 177;
            this.btnZoomIn.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnZoomInLeadHint);
            this.btnZoomIn.Name = "btnZoomIn";
            this.btnZoomIn.SourcePropertyName = null;
            this.btnZoomIn.TargetPropertyName = null;
            // 
            // btnZoomOut
            // 
            this.btnZoomOut.Caption = Resource.GetString(Resource.Strings.RibbonBarbtnZoomOutCaption);
            this.btnZoomOut.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
		    this.btnZoomOut.Glyph = Resource.GetImage(Resource.Images.ZoomOut16);
            this.btnZoomOut.Hint = Resource.GetString(Resource.Strings.RibbonBarbtnZoomOutdHint);
            this.btnZoomOut.Id = 178;
            this.btnZoomOut.Name = "btnZoomOut";
            this.btnZoomOut.SourcePropertyName = null;
            this.btnZoomOut.TargetPropertyName = null;
            // 
            // barLineWidth
            // 
            this.barLineWidth.Caption = Resource.GetString(Resource.Strings.RibbonBarbarLineWidthCaption);
            this.barLineWidth.Command = ProWrite.UI.Controls.Common.Messages.MenuCommands.Exit;
            this.barLineWidth.Hint = Resource.GetString(Resource.Strings.RibbonBarbarLineWidthdHint); ;
            this.barLineWidth.Edit = this.InnerLineWidthSpinEdit;
            this.barLineWidth.Id = 180;
            this.barLineWidth.Name = "barLineWidth";
            this.barLineWidth.SourcePropertyName = null;
            this.barLineWidth.TargetPropertyName = null;
            // 
            // InnerLineWidthSpinEdit
            // 
            this.InnerLineWidthSpinEdit.AutoHeight = false;
            this.InnerLineWidthSpinEdit.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.InnerLineWidthSpinEdit.EditFormat.FormatType = DevExpress.Utils.FormatType.Numeric;
            this.InnerLineWidthSpinEdit.IsFloatValue = false;
            this.InnerLineWidthSpinEdit.Mask.EditMask = "N00";
            this.InnerLineWidthSpinEdit.MaxValue = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.InnerLineWidthSpinEdit.MinValue = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.InnerLineWidthSpinEdit.Name = "InnerLineWidthSpinEdit";
            this.InnerLineWidthSpinEdit.NullText = "1";
            // 
            // ribbonPageDashBoard
            // 
            this.ribbonPageDashBoard.Groups.AddRange(new PageGroupEx[] {
            this.ribbonPageGroupDashBoardSystem,
            this.ribbonPageGroupDashBoardDisplay,
            this.ribbonPageGroupDashBoardConnect,
            this.ribbonPageGroupDashBoardLive,
            //this.ribbonPageGroupManagerSystem,
            this.ribbonPageGroup20
            //,this.ribbonPageGroupDashBoardTools
            });
            this.ribbonPageDashBoard.Image = Resources.Resource.GetImage(Resources.Resource.Images.DashboardIcon16x16);
            this.ribbonPageDashBoard.KeyTip = "";
            this.ribbonPageDashBoard.Name = "ribbonPageDashBoard";
            this.ribbonPageDashBoard.Text = "DASHBOARD";
            // 
            // ribbonPageGroupDashBoardSystem
            // 
            this.ribbonPageGroupDashBoardSystem.ItemLinks.Add(this.cmbSign, false, "", "", true);
            this.ribbonPageGroupDashBoardSystem.ItemLinks.Add(this.barButtonGroup1);
            this.ribbonPageGroupDashBoardSystem.ItemLinks.Add(this.barButtonGroup3);
            this.ribbonPageGroupDashBoardSystem.ItemLinks.Add(this.btnConnect, true);
            this.ribbonPageGroupDashBoardSystem.ItemLinks.Add(this.btnUnBlankSignSet,true);
            this.ribbonPageGroupDashBoardSystem.ItemLinks.Add(this.btnBlankSignSet);
            this.ribbonPageGroupDashBoardSystem.ItemLinks.Add(this.btnTestPattern);

            //this.ribbonPageGroupDashBoardSystem.ItemLinks.Add(this.btnDisplay);
            //this.ribbonPageGroupDashBoardSystem.ItemLinks.Add(this.btnLiveView);
            this.ribbonPageGroupDashBoardSystem.KeyTip = "";
            this.ribbonPageGroupDashBoardSystem.Name = "ribbonPageGroupDashBoardSystem";
            this.ribbonPageGroupDashBoardSystem.ShowCaptionButton = false;
		    this.ribbonPageGroupDashBoardSystem.Text = "Sign";
            // 
            // ribbonPageGroupDashBoardDisplay
            // 
            //this.ribbonPageGroupDashBoardDisplay.ItemLinks.Add(this.btnDisplay);
            this.ribbonPageGroupDashBoardDisplay.ItemLinks.Add(this.btnDelete);
            this.ribbonPageGroupDashBoardDisplay.ItemLinks.Add(this.btnDashboardEdit);
            this.ribbonPageGroupDashBoardDisplay.KeyTip = "";
            this.ribbonPageGroupDashBoardDisplay.Name = "ribbonPageGroupDashBoardDisplay";
            this.ribbonPageGroupDashBoardDisplay.ShowCaptionButton = false;
		    this.ribbonPageGroupDashBoardDisplay.Visible = false;
            // 
            // ribbonPageGroupDashBoardConnect
            // 
            this.ribbonPageGroupDashBoardConnect.ItemLinks.Add(this.btnConnect);
            this.ribbonPageGroupDashBoardConnect.ItemLinks.Add(this.btnUnBlankSignSet,true);
            this.ribbonPageGroupDashBoardConnect.ItemLinks.Add(this.btnBlankSignSet);

            this.ribbonPageGroupDashBoardConnect.KeyTip = "";
            this.ribbonPageGroupDashBoardConnect.Name = "ribbonPageGroupDashBoardConnect";
            this.ribbonPageGroupDashBoardConnect.ShowCaptionButton = false;
		    this.ribbonPageGroupDashBoardConnect.Visible = false;
            // 
            // ribbonPageGroupDashBoardLive
            // 
            this.ribbonPageGroupDashBoardLive.ItemLinks.Add(this.btnLiveView);
            this.ribbonPageGroupDashBoardLive.KeyTip = "";
            this.ribbonPageGroupDashBoardLive.Name = "ribbonPageGroupDashBoardLive";
            this.ribbonPageGroupDashBoardLive.ShowCaptionButton = false;
		    this.ribbonPageGroupDashBoardLive.Visible = false;
            // 
            // ribbonPageGroupDashBoardTools
            // 
            //this.ribbonPageGroupDashBoardTools.ItemLinks.Add(this.btnDashBoardTools);
            //this.ribbonPageGroupDashBoardTools.KeyTip = "";
            //this.ribbonPageGroupDashBoardTools.Name = "ribbonPageGroupDashBoardTools";
            //this.ribbonPageGroupDashBoardTools.ShowCaptionButton = true;
            // 
            // ribbonPageEditor
            // 
            this.ribbonPageEditor.Groups.AddRange(new PageGroupEx[] {
            this.ribbonPageGroupEditorSystem,   
            this.ribbonPageGroup5,
            this.ribbonPageGroup6,
            this.ribbonPageGroupEditorPicture,
            this.ribbonPageGroupEditorDrawing,
            this.ribbonPageGroup1,
            this.ribbonPageGroupZoom,
            this.ribbonPageGroup3});
            this.ribbonPageEditor.Image = Resources.Resource.GetImage(Resources.Resource.Images.MessageIcon16x16);
            this.ribbonPageEditor.KeyTip = "";
            this.ribbonPageEditor.Name = "ribbonPageEditor";
            this.ribbonPageEditor.Text = "EDITOR";
            // 
            // ribbonPageGroupEditorSystem
            // 
            this.ribbonPageGroupEditorSystem.ItemLinks.Add(this.cmbSign, false, "", "", true);
            this.ribbonPageGroupEditorSystem.ItemLinks.Add(this.barBtnGrpNew);
            this.ribbonPageGroupEditorSystem.ItemLinks.Add(this.barButtonGroup2);
            this.ribbonPageGroupEditorSystem.KeyTip = "";
            this.ribbonPageGroupEditorSystem.Name = "ribbonPageGroupEditorSystem";
            this.ribbonPageGroupEditorSystem.ShowCaptionButton = false;
            this.ribbonPageGroupEditorSystem.Text = "Sign";
            // 
            // ribbonPageGroup5
            // 
            this.ribbonPageGroup5.ItemLinks.Add(this.btnCopy);
            this.ribbonPageGroup5.ItemLinks.Add(this.btnPaste);
            this.ribbonPageGroup5.ItemLinks.Add(this.btnSendInEditor, true);
            this.ribbonPageGroup5.ItemLinks.Add(this.btnSendMessagetoSign);
            this.ribbonPageGroup5.KeyTip = "";
            this.ribbonPageGroup5.Name = "ribbonPageGroup5";
            this.ribbonPageGroup5.ShowCaptionButton = false;
            this.ribbonPageGroup5.Text = "Files";
            // 
            // ribbonPageGroup6
            // 
            this.ribbonPageGroup6.ItemLinks.Add(this.btnInsert);
            this.ribbonPageGroup6.ItemLinks.Add(this.btnDelete);
            this.ribbonPageGroup6.KeyTip = "";
            this.ribbonPageGroup6.Name = "ribbonPageGroup6";
            this.ribbonPageGroup6.ShowCaptionButton = false;
            this.ribbonPageGroup6.Text = "Content";
            // 
            // ribbonPageGroupEditorDrawing
            // 
            this.ribbonPageGroupEditorDrawing.ItemLinks.Add(this.barBtnGrpPaintShape);
            this.ribbonPageGroupEditorDrawing.ItemLinks.Add(this.barBtnGrpPaintLine);
            this.ribbonPageGroupEditorDrawing.ItemLinks.Add(this.barLineWidth);
            this.ribbonPageGroupEditorDrawing.KeyTip = "";
            this.ribbonPageGroupEditorDrawing.Name = "ribbonPageGroupEditorDrawing";
            this.ribbonPageGroupEditorDrawing.ShowCaptionButton = false;
            this.ribbonPageGroupEditorDrawing.Text = "Paint";
       

            // 
            // ribbonPageGroupEditorDrawing
            // 
            this.ribbonPageGroupEditorPicture.ItemLinks.Add(this.btnEditPicture);
            //this.ribbonPageGroupEditorPicture.ItemLinks.Add(this.barBtnGrpPaintLine);
            //this.ribbonPageGroupEditorPicture.ItemLinks.Add(this.barLineWidth);
            this.ribbonPageGroupEditorPicture.KeyTip = "";
            this.ribbonPageGroupEditorPicture.Name = "ribbonPageGroupEditorPicture";
            this.ribbonPageGroupEditorPicture.ShowCaptionButton = false;
            this.ribbonPageGroupEditorPicture.Text = "Picture";
            this.ribbonPageGroupEditorPicture.Visible = false;
            // 
            // ribbonPageGroup1
            // 
            this.ribbonPageGroup1.ItemLinks.Add(this.btnTextFontName, false, "", "", true);
            this.ribbonPageGroup1.ItemLinks.Add(this.btnTextFontSize, false, "", "", true);
            this.ribbonPageGroup1.ItemLinks.Add(this.barBtnGrpTextColor);
            this.ribbonPageGroup1.ItemLinks.Add(this.barBtnGrpTextBoldItalic);
            this.ribbonPageGroup1.ItemLinks.Add(this.barBtnGrpTextAlign);
            this.ribbonPageGroup1.ItemLinks.Add(this.barBtnGrpTextFixed);
            this.ribbonPageGroup1.ItemLinks.Add(this.barEditTextEffect, false, "", "", true);
            this.ribbonPageGroup1.ItemLinks.Add(this.btnTextLead, true);
            this.ribbonPageGroup1.ItemLinks.Add(this.btnTextKern);
            this.ribbonPageGroup1.KeyTip = "";
            this.ribbonPageGroup1.Name = "ribbonPageGroup1";
            this.ribbonPageGroup1.ShowCaptionButton = false;
            this.ribbonPageGroup1.Text = "Text Font";
            // 
            // ribbonPageGroup3
            // 
            this.ribbonPageGroup3.ItemLinks.Add(this.btnProperties);
            //this.ribbonPageGroup3.ItemLinks.Add(this.btnZoomIn);
            //this.ribbonPageGroup3.ItemLinks.Add(this.btnZoomOut);
            this.ribbonPageGroup3.KeyTip = "";
            this.ribbonPageGroup3.Name = "ribbonPageGroup3";
            this.ribbonPageGroup3.ShowCaptionButton = false;
            this.ribbonPageGroup3.Text = "Modify";            // 
            // ribbonPageGroupZoom
            // 
            this.ribbonPageGroupZoom.ItemLinks.Add(this.btnZoomIn);
            this.ribbonPageGroupZoom.ItemLinks.Add(this.btnZoomOut);
            this.ribbonPageGroupZoom.KeyTip = "";
            this.ribbonPageGroupZoom.Name = "ribbonPageGroupZoom";
            this.ribbonPageGroupZoom.ShowCaptionButton = false;
            this.ribbonPageGroupZoom.Text = "Zoom";
            // 
            // ribbonPagePlayLists
            // 
            this.ribbonPagePlayLists.Groups.AddRange(new PageGroupEx[] {
            this.ribbonPageGroupPlaylistSystem,
            this.ribbonPageGroupPlaylistCopy,
            this.ribbonPageGroupPlaylistSend,
            this.ribbonPageGroup4});
            this.ribbonPagePlayLists.Image = Resources.Resource.GetImage(Resources.Resource.Images.PlaylistIcon16x16);
            this.ribbonPagePlayLists.KeyTip = "";
            this.ribbonPagePlayLists.Name = "ribbonPagePlayLists";
            this.ribbonPagePlayLists.Text = "PLAYLISTS";
            // 
            // ribbonPageGroupPlaylistSystem
            // 
            this.ribbonPageGroupPlaylistSystem.ItemLinks.Add(this.cmbSign, false, "", "", true);
            this.ribbonPageGroupPlaylistSystem.ItemLinks.Add(this.barBtnGrpNew);
            this.ribbonPageGroupPlaylistSystem.ItemLinks.Add(this.barButtonGroup2);
            this.ribbonPageGroupPlaylistSystem.KeyTip = "";
            this.ribbonPageGroupPlaylistSystem.Name = "ribbonPageGroupPlaylistSystem";
            this.ribbonPageGroupPlaylistSystem.ShowCaptionButton = false;
            this.ribbonPageGroupPlaylistSystem.Text = "Sign";
            // 
            // ribbonPageGroupPlaylistCopy
            // 
            this.ribbonPageGroupPlaylistCopy.ItemLinks.Add(this.btnCopy);
            this.ribbonPageGroupPlaylistCopy.ItemLinks.Add(this.btnPaste);
            this.ribbonPageGroupPlaylistCopy.ItemLinks.Add(this.btnSendInPlaylist, true);
            this.ribbonPageGroupPlaylistCopy.ItemLinks.Add(this.btnSendPlayListtoSign);
            this.ribbonPageGroupPlaylistCopy.KeyTip = "";
            this.ribbonPageGroupPlaylistCopy.Name = "ribbonPageGroupPlaylistCopy";
            this.ribbonPageGroupPlaylistCopy.ShowCaptionButton = false;
            this.ribbonPageGroupPlaylistCopy.Text = "Files";
            // 
            // ribbonPageGroupPlaylistSend
            // 
            this.ribbonPageGroupPlaylistSend.ItemLinks.Add(this.btnInsert);
            this.ribbonPageGroupPlaylistSend.ItemLinks.Add(this.btnDelete);

            this.ribbonPageGroupPlaylistSend.KeyTip = "";
            this.ribbonPageGroupPlaylistSend.Name = "ribbonPageGroupPlaylistSend";
            this.ribbonPageGroupPlaylistSend.ShowCaptionButton = false;
            this.ribbonPageGroupPlaylistSend.Text = "Content";
            // 
            // ribbonPageGroup4
            // 
            this.ribbonPageGroup4.ItemLinks.Add(this.btnProperties);
            this.ribbonPageGroup4.KeyTip = "";
            this.ribbonPageGroup4.Name = "ribbonPageGroup4";
            this.ribbonPageGroup4.ShowCaptionButton = false;
            this.ribbonPageGroup4.Text = "Modify";
            // 
            // ribbonPageSchedule
            // 
            this.ribbonPageSchedule.Groups.AddRange(new PageGroupEx[] {
            this.ribbonPageGroupSchedulerSystem,
            this.ribbonPageGroupSchedulerCopy,
            this.ribbonPageGroup7,
            this.ribbonPageGroup19});
            this.ribbonPageSchedule.Image = Resources.Resource.GetImage(Resources.Resource.Images.SchedulerIcon16x16);
            this.ribbonPageSchedule.KeyTip = "";
            this.ribbonPageSchedule.Name = "ribbonPageSchedule";
            this.ribbonPageSchedule.Text = "SCHEDULER";
            // 
            // ribbonPageGroupSchedulerSystem
            // 
            this.ribbonPageGroupSchedulerSystem.AllowTextClipping = false;
            this.ribbonPageGroupSchedulerSystem.ItemLinks.Add(this.cmbSign, false, "", "", true);
            this.ribbonPageGroupSchedulerSystem.ItemLinks.Add(this.barBtnGrpNew);
            this.ribbonPageGroupSchedulerSystem.ItemLinks.Add(this.barButtonGroup2);
            this.ribbonPageGroupSchedulerSystem.KeyTip = "";
            this.ribbonPageGroupSchedulerSystem.Name = "ribbonPageGroupSchedulerSystem";
            this.ribbonPageGroupSchedulerSystem.ShowCaptionButton = false;
            this.ribbonPageGroupSchedulerSystem.Text = "Sign";
            // 
            // ribbonPageGroupSchedulerCopy
            // 
            this.ribbonPageGroupSchedulerCopy.ItemLinks.Add(this.btnCopy);
            this.ribbonPageGroupSchedulerCopy.ItemLinks.Add(this.btnPaste);
            this.ribbonPageGroupSchedulerCopy.ItemLinks.Add(this.btnSendInScheduler, true);
            this.ribbonPageGroupSchedulerCopy.KeyTip = "";
            this.ribbonPageGroupSchedulerCopy.Name = "ribbonPageGroupSchedulerCopy";
            this.ribbonPageGroupSchedulerCopy.ShowCaptionButton = false;
            this.ribbonPageGroupSchedulerCopy.Text = "Files";
            // 
            // ribbonPageGroup7
            // 
            this.ribbonPageGroup7.ItemLinks.Add(this.btnInsert);
            this.ribbonPageGroup7.ItemLinks.Add(this.btnDelete);
            //this.ribbonPageGroup7.ItemLinks.Add(this.btnDisplay);
            this.ribbonPageGroup7.KeyTip = "";
            this.ribbonPageGroup7.Name = "ribbonPageGroup7";
            this.ribbonPageGroup7.ShowCaptionButton = false;
            this.ribbonPageGroup7.Text = "Content";
            // 
            // ribbonPageGroup19
            // 
            this.ribbonPageGroup19.ItemLinks.Add(this.btnProperties);
            this.ribbonPageGroup19.KeyTip = "";
            this.ribbonPageGroup19.Name = "ribbonPageGroup19";
            this.ribbonPageGroup19.ShowCaptionButton = false;
            this.ribbonPageGroup19.Text = "Modify";
            // 
            // ribbonPageManager
            // 
            //this.ribbonPageManager.Groups.AddRange(new PageGroupEx[] {
            //this.ribbonPageGroupManagerSystem,
            //this.ribbonPageGroup20});
            //this.ribbonPageManager.Image = ((System.Drawing.Image)(resources.GetObject("ribbonPageManager.Image")));
            //this.ribbonPageManager.KeyTip = "";
            //this.ribbonPageManager.Name = "ribbonPageManager";
            //this.ribbonPageManager.Text = "MANAGER";
            // 
            // ribbonPageGroupManagerSystem
            // 
            //this.ribbonPageGroupManagerSystem.ItemLinks.Add(this.cmbSign, false, "", "", true);
            //this.ribbonPageGroupManagerSystem.ItemLinks.Add(this.btnSystemInit);
            //this.ribbonPageGroupManagerSystem.KeyTip = "";
            //this.ribbonPageGroupManagerSystem.ShowCaptionButton = false;
            //this.ribbonPageGroupManagerSystem.Name = "ribbonPageGroupManagerSystem";
            //this.ribbonPageGroupManagerSystem.Text = "Initialization";
            //this.ribbonPageGroupManagerSystem.Visible = false;
            // 
            // ribbonPageGroup20
            // 
            this.ribbonPageGroup20.ItemLinks.Add(this.btnSystemDefault);
            this.ribbonPageGroup20.ItemLinks.Add(this.btnUserManager);
            //this.ribbonPageGroup20.ItemLinks.Add(this.btnConnect);
            this.ribbonPageGroup20.KeyTip = "";
		    this.ribbonPageGroup20.ShowCaptionButton = false;
            this.ribbonPageGroup20.Name = "ribbonPageGroup20";
		    this.ribbonPageGroup20.Text = "System Management";
            this.ribbonPageGroup20.Visible = false;

            #region Live
            // 
            // ribbonPageLive
            // 
            this.ribbonPageLive.Groups.AddRange(new DevExpress.XtraBars.Ribbon.RibbonPageGroup[] {
            this.ribbonPageGroupLiveSession,
            this.ribbonPageGroupLibrary,
            this.ribbonPageGroupModify});
            this.ribbonPageLive.Name = "ribbonPageLive";
            this.ribbonPageLive.Text = "Live";
            // 
            // ribbonPageGroupLiveSession
            // 
            this.ribbonPageGroupLiveSession.ItemLinks.Add(this.txtCurrentSession);
            this.ribbonPageGroupLiveSession.ItemLinks.Add(this.cmbSession);
            this.ribbonPageGroupLiveSession.ItemLinks.Add(this.btnSessionLoad);
            this.ribbonPageGroupLiveSession.ItemLinks.Add(this.btnSessionSave);
            this.ribbonPageGroupLiveSession.ItemLinks.Add(this.btnGoLive, true);
            this.ribbonPageGroupLiveSession.ItemLinks.Add(this.btnSync, true);
            this.ribbonPageGroupLiveSession.ItemLinks.Add(this.btnSessionSetup, true);
            this.ribbonPageGroupLiveSession.Name = "ribbonPageGroupLiveSession";
            this.ribbonPageGroupLiveSession.Text = "Live Session Manager";
            // 
            // cmbSession
            // 
            this.cmbSession.CaptionAlignment = DevExpress.Utils.HorzAlignment.Center;
            this.cmbSession.Edit = this.repositoryItemComboBox1;
            this.cmbSession.Id = 115;
            this.cmbSession.Name = "cmbSession";
            this.cmbSession.Width = 100;
            //this.cmbSession.ItemClick += new DevExpress.XtraBars.ItemClickEventHandler(this.cmbSession_ItemClick);
            // 
            // repositoryItemComboBox1
            // 
            this.repositoryItemComboBox1.AutoHeight = false;
            this.repositoryItemComboBox1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.repositoryItemComboBox1.Name = "repositoryItemComboBox1";
            this.repositoryItemComboBox1.UseParentBackground = true;
            // 
            // txtCurrentSession
            // 
            this.txtCurrentSession.Caption = "Current Session";
            this.txtCurrentSession.Id = 117;
            this.txtCurrentSession.Name = "txtCurrentSession";
            this.txtCurrentSession.TextAlignment = System.Drawing.StringAlignment.Near;
            this.txtCurrentSession.Width = 100;
            // 
            // barMdiChildrenListItem1
            // 
            this.barMdiChildrenListItem1.Caption = "barMdiChildrenListItem1";
            this.barMdiChildrenListItem1.Id = 118;
            this.barMdiChildrenListItem1.Name = "barMdiChildrenListItem1";
            // 
            // btnSessionLoad
            // 
            this.btnSessionLoad.Caption = "Load";
            this.btnSessionLoad.Id = 119;
            this.btnSessionLoad.Name = "btnSessionLoad";
            // 
            // btnSessionSave
            // 
            this.btnSessionSave.Caption = "Save";
            this.btnSessionSave.Id = 120;
            this.btnSessionSave.Name = "btnSessionSave";
            // 
            // btnGroup
            // 
            this.btnGroup.Caption = "barButtonGroup1";
            this.btnGroup.Id = 121;
            this.btnGroup.ImageIndex = 1;
            this.btnGroup.ItemLinks.Add(this.btnSessionLoad);
            this.btnGroup.ItemLinks.Add(this.btnSessionSave);
            this.btnGroup.Name = "btnGroup";
            // 
            // btnGoLive
            // 
            this.btnGoLive.Caption = "GoLive";
            this.btnGoLive.LargeGlyph = Resources.Resource.GetImage(Resources.Resource.Images.GoLive);
            this.btnGoLive.GroupIndex = 1;
            this.btnGoLive.Id = 122;
            this.btnGoLive.Name = "btnGoLive";
            // 
            // btnSync
            // 
            this.btnSync.Caption = "Sync";
            this.btnSync.GroupIndex = 2;
            this.btnSync.Id = 124;
            this.btnSync.Name = "btnSync";
            // 
            // btnSessionSetup
            // 
            this.btnSessionSetup.Caption = "Session Setup";
            this.btnSessionSetup.GroupIndex = 3;
            this.btnSessionSetup.Id = 125;
            this.btnSessionSetup.Name = "btnSessionSetup";
            // 
            // ribbonPageGroupLibrary
            // 
            this.ribbonPageGroupLibrary.ItemLinks.Add(this.btnLibraryNew);
            this.ribbonPageGroupLibrary.ItemLinks.Add(this.btnLibraryOpen, true);
            this.ribbonPageGroupLibrary.Name = "ribbonPageGroupLibrary";
            this.ribbonPageGroupLibrary.Text = "Media Library";
            // 
            // btnLibraryNew
            // 
            this.btnLibraryNew.Caption = "New";
            this.btnLibraryNew.Id = 126;
            this.btnLibraryNew.Name = "btnLibraryNew";
            // 
            // btnLibraryOpen
            // 
            this.btnLibraryOpen.Caption = "Open";
            this.btnLibraryOpen.GroupIndex = 1;
            this.btnLibraryOpen.Id = 127;
            this.btnLibraryOpen.Name = "btnLibraryOpen";
            // 
            // ribbonPageGroupModify
            // 
            this.ribbonPageGroupModify.ItemLinks.Add(this.btnLiveProperties);
            this.ribbonPageGroupModify.Name = "ribbonPageGroupModify";
            this.ribbonPageGroupModify.Text = "Modify";
            // 
            // btnLiveProperties
            // 
            this.btnLiveProperties.Caption = "Properties";
            this.btnLiveProperties.Id = 128;
            this.btnLiveProperties.Name = "btnLiveProperties";
            #endregion
            // 
            // ribbonPageLive
            // 
            //this.ribbonPageLive.Groups.AddRange(new PageGroupEx[] {
            //this.ribbonPageGroupLiveSystem,
            //this.ribbonPageGroupLiveCategory,
            //this.ribbonPageGroupLiveHotBtn,
            //this.ribbonPageGroupLiveLibrary});
            //this.ribbonPageLive.Groups.AddRange(new PageGroupEx[] {
            //this.ribbonPageGroupLiveSession
            ////this.ribbonPageGroupLiveMedia,            
            ////this.ribbonPageGroupLiveModify
            //});
            //this.ribbonPageLive.Image = ((System.Drawing.Image)(resources.GetObject("ribbonPageLive.Image")));
            //this.ribbonPageLive.KeyTip = "";
            //this.ribbonPageLive.Name = "ribbonPageLive";
            //this.ribbonPageLive.Text = "LIVE";
            //this.ribbonPageLive.Visible = false;

            //// 
            //// ribbonPageGroupLiveSession
            //// 
            //this.ribbonPageGroupLiveSession.ItemLinks.Add(this.cmbSession);
            //this.ribbonPageGroupLiveSession.ItemLinks.Add(this.btnSessionLoad);
            //this.ribbonPageGroupLiveSession.ItemLinks.Add(this.btnSessionSave);
            //this.ribbonPageGroupLiveSession.KeyTip = "";
            //this.ribbonPageGroupLiveSession.Name = "ribbonPageGroupLiveSession";
            //this.ribbonPageGroupLiveSession.Text = "Sign";

            // 
            // ribbonPageGroupLiveSystem
            // 
            //this.ribbonPageGroupLiveSystem.ItemLinks.Add(this.cmbSign, false, "", "", true);
            //this.ribbonPageGroupLiveSystem.ItemLinks.Add(this.barBtnGrpNew);
            //this.ribbonPageGroupLiveSystem.ItemLinks.Add(this.btnConnect);
            //this.ribbonPageGroupLiveSystem.KeyTip = "";
            //this.ribbonPageGroupLiveSystem.Name = "ribbonPageGroupLiveSystem";
            //this.ribbonPageGroupLiveSystem.Text = "Sign";
            //// 
            //// ribbonPageGroupLiveCategory
            //// 
            //this.ribbonPageGroupLiveCategory.ItemLinks.Add(this.btnLiveCategoryAdd);
            //this.ribbonPageGroupLiveCategory.ItemLinks.Add(this.btnLiveCategoryRemove);
            //this.ribbonPageGroupLiveCategory.ItemLinks.Add(this.btnLiveCategoryRename);
            //this.ribbonPageGroupLiveCategory.KeyTip = "";
            //this.ribbonPageGroupLiveCategory.Name = "ribbonPageGroupLiveCategory";
            //this.ribbonPageGroupLiveCategory.Text = "Category";
            //// 
            //// ribbonPageGroupLiveHotBtn
            //// 
            //this.ribbonPageGroupLiveHotBtn.ItemLinks.Add(this.btnLiveItemAdd);
            //this.ribbonPageGroupLiveHotBtn.ItemLinks.Add(this.btnLiveItemRemove);
            //this.ribbonPageGroupLiveHotBtn.ItemLinks.Add(this.btnLiveItemRename);
            //this.ribbonPageGroupLiveHotBtn.KeyTip = "";
            //this.ribbonPageGroupLiveHotBtn.Name = "ribbonPageGroupLiveHotBtn";
            //this.ribbonPageGroupLiveHotBtn.Text = "Hot Button";
            //// 
            //// ribbonPageGroupLiveLibrary
            //// 
            //this.ribbonPageGroupLiveLibrary.ItemLinks.Add(this.btnLiveCXCResourceLibrary);
            //this.ribbonPageGroupLiveLibrary.KeyTip = "";
            //this.ribbonPageGroupLiveLibrary.Name = "ribbonPageGroupLiveLibrary";
            //this.ribbonPageGroupLiveLibrary.Text = "CXC Resource Library";
            // 
            // repositoryItemTextEdit1
            // 
            this.repositoryItemTextEdit1.AutoHeight = false;
            this.repositoryItemTextEdit1.Name = "repositoryItemTextEdit1";
            // 
            // repositoryItemFontEdit1
            // 
            this.repositoryItemFontEdit1.AutoHeight = false;
            this.repositoryItemFontEdit1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.repositoryItemFontEdit1.Name = "repositoryItemFontEdit1";
            // 
            // repositoryItemButtonEdit2
            // 
            this.repositoryItemButtonEdit2.AutoHeight = false;
            this.repositoryItemButtonEdit2.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton()});
            this.repositoryItemButtonEdit2.Name = "repositoryItemButtonEdit2";
            // 
            // fontEffectListComBox
            // 
            this.fontEffectListComBox.AllowNullInput = DevExpress.Utils.DefaultBoolean.False;
            this.fontEffectListComBox.AutoComplete = false;
            this.fontEffectListComBox.AutoHeight = false;
            this.fontEffectListComBox.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.fontEffectListComBox.DropDownRows = 3;
            this.fontEffectListComBox.HideSelection = false;
            this.fontEffectListComBox.Items.AddRange(new object[] {
            "[None]",
            "Outline",
            "Shadow"});
            this.fontEffectListComBox.Name = "fontEffectListComBox";
            this.fontEffectListComBox.NullText = "[None]";
            this.fontEffectListComBox.TextEditStyle = DevExpress.XtraEditors.Controls.TextEditStyles.DisableTextEditor;
            // 
            // repositoryItemColorEdit1
            // 
            this.repositoryItemColorEdit1.AutoHeight = false;
            this.repositoryItemColorEdit1.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.repositoryItemColorEdit1.Name = "repositoryItemColorEdit1";
            // 
            // ribbonStatusBar1
            // 
            this.ribbonStatusBar1.ItemLinks.Add(ControlService.BarButton);
            ControlService.BarButton.Alignment = DevExpress.XtraBars.BarItemLinkAlignment.Right;
            this.ribbonStatusBar1.Location = new System.Drawing.Point(0, 691);
            this.ribbonStatusBar1.Name = "ribbonStatusBar1";
            this.ribbonStatusBar1.Ribbon = this.ribbonControl1;
            this.ribbonStatusBar1.Size = new System.Drawing.Size(1067, 25);
            // 
            // panelContainer1
            // 
            this.panelContainer1.Dock = DevExpress.XtraBars.Docking.DockingStyle.Fill;
            this.panelContainer1.ID = new System.Guid("d76406b5-67bd-48f8-850e-2d1f761a47a0");
            this.panelContainer1.Location = new System.Drawing.Point(0, 143);
            this.panelContainer1.Name = "panelContainer1";
            this.panelContainer1.Size = new System.Drawing.Size(200, 573);
            // 
            // barButtonGroup2
            // 
            this.barButtonGroup2.Id = 182;
            this.barButtonGroup2.ItemLinks.Add(this.btnOpen);
            this.barButtonGroup2.Name = "barButtonGroup2";
            // 
            // barButtonGroup3
            // 
            this.barButtonGroup3.Id = 183;
            this.barButtonGroup3.ItemLinks.Add(this.btnDashBoardTools);
            this.barButtonGroup3.Name = "barButtonGroup3";
            // 
            // popupContainerControl1
            // 
            this.popupContainerControl1.Location = new System.Drawing.Point(582, 54);
            this.popupContainerControl1.Name = "popupContainerControl1";
            this.popupContainerControl1.Size = new System.Drawing.Size(241, 207);
            this.popupContainerControl1.TabIndex = 185;
            // 
            // repositoryItemPopupContainerEdit3
            // 
            this.repositoryItemPopupContainerEdit3.AutoHeight = false;
            this.repositoryItemPopupContainerEdit3.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Combo)});
            this.repositoryItemPopupContainerEdit3.Name = "repositoryItemPopupContainerEdit3";
            this.repositoryItemPopupContainerEdit3.PopupControl = this.popupContainerControl1;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1067, 716);
            this.Controls.Add(this.ribbonStatusBar1);
            this.Controls.Add(this.ribbonControl1);
            this.IsMdiContainer = true;
            this.Name = "MainForm";
            this.Ribbon = this.ribbonControl1;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.StatusBar = this.ribbonStatusBar1;
            this.Text = "ProWrite";
            //#if DEBUG
            this.Text = "ProWrite " + ProWrite.Core.ProductInfo.Version;
//#endif
            this.Icon = Resource.GetIcon(Resource.Icons.TrayIcon);
            ((System.ComponentModel.ISupportInitialize)(this.popupMenuMain)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.newPopDashboardMenu)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.newPopEditorMenu)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.newPopPlaylistMenu)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.newPopSchedulerMenu)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mnuProperties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.toolsPopMenu)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.displayPopMenu)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.replacePopMenu)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.drawingPopMenu)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.sendPopMenuEditor)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.sendPopMenuPlaylist)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.sendPopMenuScheduler)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mnuRedoActionList)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mnuUndoActionList)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.windowsList)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.cmbTextFontName)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.cmbTextFontSize)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemTextEffectEdit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mnuOpen)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mnuView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mnuInsert)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mnuPlaylistInsert)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mnuSchedulerInsert)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemKernEdit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemLeadEdit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.InnerLineWidthSpinEdit)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemTextEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemFontEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemButtonEdit2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.fontEffectListComBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemColorEdit1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.popupMenu2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.popupMenu1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.popupContainerControl1)).EndInit();
            this.popupContainerControl1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.repositoryItemPopupContainerEdit3)).EndInit();

            this.ResumeLayout(false);

		}

        

		#endregion
		
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		

		private RibbonControl ribbonControl1;
		private RibbonPageEx ribbonPageDashBoard;
		private PageGroupEx ribbonPageGroupDashBoardSystem;
		private RibbonPageEx ribbonPageEditor;
		private RibbonPageEx ribbonPagePlayLists;
		private RibbonPageEx ribbonPageSchedule;
		//private RibbonPage ribbonPageManager;
		private BarListItem skinsBli;
		private BarButtonItemEx btnEditorNewMessage;
		private BarButtonItemEx btnNewSchedule;
		private BarButtonItemEx btnNewLibrary;
        private BarButtonItemEx btnNewTimeSliceGroup;
		private BarButtonItemEx btnDashboardEdit;
		private BarButtonItemEx btnNew;
		private BarButtonItemEx btnExit;
		private BarButtonItemEx btnDashbaordNewSign;
		private BarButtonItemEx btnDashboardNewSignGroup;
        private PopupMenu newPopDashboardMenu;
        private PopupMenu newPopEditorMenu;
        private PopupMenu newPopPlaylistMenu;
        private PopupMenu newPopSchedulerMenu;
        private PageGroupEx ribbonPageGroupDashBoardConnect;
		private PageGroupEx ribbonPageGroupDashBoardDisplay;
		private BarButtonItemEx btnConnect;
        //private BarButtonItemEx btnSessionLoad;
        //private BarButtonItemEx btnSessionSave;
        private BarButtonItemEx btnBlankSignSet;
        private BarButtonItemEx btnUnBlankSignSet;

        //private BarButtonItemEx btnDisplayMsg;
        //private PageGroupEx ribbonPageGroupDashBoardTools;
		private PageGroupEx ribbonPageGroupDashBoardLive;
		private BarButtonItemEx btnSignProperties;
		private BarButtonItemEx btnBlankSign;
		private BarButtonItemEx btnTestPattern;
		private BarButtonItemEx btnDisplayMsg;
		private BarButtonItemEx btnDelete;
		private BarButtonItemEx btnDashBoardTools;
		private BarButtonItemEx btnDimming;
		private BarButtonItemEx btnTempOffset;
		private BarButtonItemEx btnSetTime;
		private BarButtonItemEx btnViewLog;
		private BarButtonItemEx btnLiveView;
		private BarButtonItemEx btnSignPhotoView;
		private BarButtonItemEx btnRefreshView;
		private BarButtonItemEx btnDisplay;
		private PopupMenu displayPopMenu;
		private PopupMenu toolsPopMenu;
		private BarButtonItemEx btnInsertImage;
		private BarButtonItemEx btnInsertVideo;
		private BarButtonItemEx btnInsertText;
		private BarButtonItemEx btnInsertVariableText;
        private BarButtonItemEx btnInsertTime;
        private BarButtonItemEx btnInsertTemperature;
		private BarButtonItemEx barButtonItem21;
		private BarButtonItemEx barButtonItem22;
		private BarButtonItemEx barButtonItem23;
		private PageGroupEx ribbonPageGroupEditorSystem;
		private PageGroupEx ribbonPageGroupEditorDrawing;
        private PageGroupEx ribbonPageGroupEditorPicture;
		private PopupMenu replacePopMenu;
		private BarButtonItemEx btnDrawing;
		private BarButtonItemEx btnRectangle;
		private BarButtonItemEx btnEllipse;
		private BarButtonItemEx btnArrowUp;
		private BarButtonItemEx btnArrowDown;
		private BarButtonItemEx btnArrowRight;
		private BarButtonItemEx btnArrowLeft;
		private PopupMenu drawingPopMenu;
		private ColorBarItem btnFill;
		private ColorBarItem btnLinecolor;
		private RepositoryItemTextEffectEdit repositoryItemTextEffectEdit;
		private BarButtonItemEx btnPen;
		private BarButtonItemEx btnEraser;
        private BarButtonItemEx btnSendInEditor;
        private BarButtonItemEx btnSendInPlaylist;
        private BarButtonItemEx btnSendInScheduler;
        private BarButtonItemEx btnSendLive;
		private BarButtonItemEx btnSendSign;
        private BarButtonItemEx btnSendMessagetoSign;
        private BarButtonItemEx btnSendPlayListtoSign;
		private BarButtonItemEx btnSendPlaylist;
		private BarButtonItemEx btnSendSchedule;
        private PopupMenu sendPopMenuEditor;
        private PopupMenu sendPopMenuPlaylist;
        private PopupMenu sendPopMenuScheduler;
        private BarButtonItemEx btnProperties;
		private PageGroupEx ribbonPageGroupPlaylistSystem;
		private BarButtonItemEx btnInsertPlayList;
		private BarButtonItemEx btnInsertMessage;
		private BarButtonItemEx btnInsertTimeSliceGrp;
		private PageGroupEx ribbonPageGroupPlaylistCopy;
		private BarButtonItemEx barButtonItem58;
		private BarButtonItemEx barButtonItem59;
		private BarButtonItemEx btnScheduleInsertPlaylist;
		private BarButtonItemEx btnScheduleInsertMessage;
		private BarButtonItemEx barButtonItem63;
		private PageGroupEx ribbonPageGroupPlaylistSend;
		private PageGroupEx ribbonPageGroupSchedulerSystem;
		private PageGroupEx ribbonPageGroupSchedulerCopy;
		private PageGroupEx ribbonPageGroup19;
		private DevExpress.XtraBars.PopupMenu mnuUndoActionList;
		private BarButtonItemEx btnSave;
		private BarButtonItemEx btnSystemInit;
		private BarButtonItemEx btnSystemDefault;
        private BarButtonItemEx btnUserManager;
		private PageGroupEx ribbonPageGroup20;
		private BarButtonItemEx btnRedo;
		private BarButtonItemEx btnUndo;
        //private RibbonPage ribbonPageLive;
        //private PageGroupEx ribbonPageGroupManagerSystem;
        //private PageGroupEx ribbonPageGroupLiveSystem;
        //private PageGroupEx ribbonPageGroupLiveSession;
		private BarButtonItemEx btnCopy;
		private BarButtonItemEx btnPaste;
		private DevExpress.XtraBars.PopupMenu mnuRedoActionList;
		private DevExpress.XtraEditors.Repository.RepositoryItemTextEdit repositoryItemTextEdit1;
		private BarEditItemEx cmbSign;
		private BarButtonItemEx btnSaveAs;
        private BarButtonItemEx btnAbout;
        private BarButtonItemEx btnHelp;
        private BarButtonItemEx btnTestCommand;
        private BarButtonItemEx btnProfaneWord;
		private BarButtonItemEx btnBatchLoad;
		private BarButtonItemEx btnBold;
		private BarButtonItemEx btnItalic;
		private BarButtonItemEx btnAlignLeft;
		private BarButtonItemEx btnCenter;
		private BarButtonItemEx btnAlignRight;
		private ColorBarItem btnFontColor;
		private ColorBarItem btnBackGroundColor;
		private BarButtonItemEx btnTextFrameFixed;
		private BarButtonItemEx btnFontSizeFixed;
		private BarButtonItemEx btnWindows;
		private DevExpress.XtraBars.PopupMenu windowsList;
		private DevExpress.XtraBars.BarButtonGroup barBtnGrpTextColor;
		private PageGroupEx ribbonPageGroup1;
		private DevExpress.XtraBars.BarButtonGroup barBtnGrpTextAlign;
		private DevExpress.XtraBars.BarButtonGroup barBtnGrpTextFixed;
		private BarEditItemEx btnTextFontName;
		private RepositoryItemFontEdit repositoryItemFontEdit1; 
		//private DevExpress.XtraEditors.Repository.RepositoryItemButtonEdit repositoryItemButtonEdit1;
		private BarEditItemEx btnTextFontSize;
		private DevExpress.XtraEditors.Repository.RepositoryItemComboBox cmbTextFontSize;
		private DevExpress.XtraEditors.Repository.RepositoryItemButtonEdit repositoryItemButtonEdit2;
		private BarButtonItemEx btnPlayListNew;
		private BarButtonItemEx btnLine;
		private DevExpress.XtraBars.BarButtonGroup barBtnGrpPaintLine;
		private DevExpress.XtraBars.BarButtonGroup barBtnGrpPaintShape;
        private DockPanel panelContainer1;
		private PageGroupEx ribbonPageGroup3;
	    private PageGroupEx ribbonPageGroupZoom;
		private BarEditItemEx barEditTextEffect;
		private DevExpress.XtraEditors.Repository.RepositoryItemComboBox fontEffectListComBox;

		private DevExpress.XtraBars.BarButtonGroup barBtnGrpTextBoldItalic;
		private BarButtonItemEx btnOpen;
		private DevExpress.XtraBars.BarButtonGroup barBtnGrpNew;
		private DevExpress.XtraBars.PopupMenu popupMenuMain;
		private BarButtonItemEx btnImport;
		private BarButtonItemEx btnExport;
		private BarButtonItemEx btnView;
		private DevExpress.XtraBars.PopupMenu mnuView;
		private PageGroupEx ribbonPageGroup4;
		private DevExpress.XtraBars.BarCheckItem barCheckItem1;
		private PageGroupEx ribbonPageGroup5;
		private PageGroupEx ribbonPageGroup6;
		private BarButtonItemEx btnInsert;
        private BarButtonItemEx btnEditPicture;

		private DevExpress.XtraBars.PopupMenu mnuInsert;
		private BarButtonItemEx btnDropDownPlaylistInsert;
		private DevExpress.XtraBars.PopupMenu mnuPlaylistInsert;
		private PageGroupEx ribbonPageGroup7;
		private BarButtonItemEx btnDropDownSchedulerInsert;
		private DevExpress.XtraBars.PopupMenu mnuSchedulerInsert;
		private DevExpress.XtraEditors.Repository.RepositoryItemColorEdit repositoryItemColorEdit1;
		private BarButtonItemEx btnSignStatus;
		private BarButtonItemEx btnChangePwd;
		private DevExpress.XtraBars.PopupMenu mnuProperties;
		private BarButtonItemEx btnReboot;
        private BarButtonItemEx btnTimeZone;
		private BarButtonItemEx btnSetDateTime;
		private BarButtonItemEx btnFactoryReset;
		private BarButtonItemEx btnSkipQ;
		private BarButtonItemEx btnClearQ;
		private BarButtonItemEx btnStartStopRender;
		private BarButtonItemEx btnClearCXCLog;
		private DevExpress.XtraEditors.Repository.RepositoryItemComboBox cmbTextFontName;
		private BarEditItemEx btnTextKern;
		private DevExpress.XtraEditors.Repository.RepositoryItemSpinEdit repositoryItemKernEdit;
		private BarEditItemEx btnTextLead;
		private DevExpress.XtraEditors.Repository.RepositoryItemSpinEdit repositoryItemLeadEdit;
		private PageGroupEx ribbonPageGroupLiveCategory;
		private PageGroupEx ribbonPageGroupLiveHotBtn;
		private BarButtonItemEx btnLiveCategoryAdd;
		private BarButtonItemEx btnLiveCategoryRemove;
		private BarButtonItemEx btnLiveCategoryRename;
		private BarButtonItemEx btnLiveItemAdd;
		private BarButtonItemEx btnLiveItemRemove;
		private BarButtonItemEx btnLiveItemRename;
		private PageGroupEx ribbonPageGroupLiveLibrary;
		private BarButtonItemEx btnLiveCXCResourceLibrary;
		private BarButtonItemEx btnInsertVariableVideo;
		private PopupMenu mnuOpen;
		private BarButtonItemEx btnOpenFile;
		private BarButtonItemEx btnOpenLibrary;
		private BarButtonGroup barButtonGroup1;
		private BarButtonItemEx btnZoomIn;
		private BarButtonItemEx btnZoomOut;
        private BarButtonItemEx btnPointer;
        private BarEditItemEx barLineWidth;
        private DevExpress.XtraEditors.Repository.RepositoryItemSpinEdit InnerLineWidthSpinEdit;
		private RibbonStatusBar ribbonStatusBar1;
        private BarButtonGroup barButtonGroup2;
        private BarButtonGroup barButtonGroup3;
        private DevExpress.XtraEditors.Repository.RepositoryItemPopupContainerEdit repositoryItemPopupContainerEdit3;
        private FontPopupContainer popupContainerControl1;
        private DevExpress.Utils.ToolTipTitleItem textNameTipTitle;
        private DevExpress.Utils.ToolTipItem textNameTipItem;
        private DevExpress.Utils.SuperToolTip textNameSuperTip;
        private DevExpress.Utils.ToolTipTitleItem textSizeTipTitle;
        private DevExpress.Utils.ToolTipItem textSizeTipItem;
        private DevExpress.Utils.SuperToolTip textSizeSuperTip;

        private ProWrite.UI.Controls.BarButtonItemEx btnTestPatternExitTest;
        private ProWrite.UI.Controls.BarButtonItemEx btnTestPatternHRamp;
        private ProWrite.UI.Controls.BarButtonItemEx btnTestPatternVRamp;
        private ProWrite.UI.Controls.BarButtonItemEx btnTestPatternCross;
        private ProWrite.UI.Controls.BarButtonItemEx btnTestPatternDiagonal;
        private ProWrite.UI.Controls.BarButtonItemEx btnTestPatternVertical;
        private ProWrite.UI.Controls.BarButtonItemEx btnTestPatternColorBar;
        private ProWrite.UI.Controls.BarButtonItemEx btnTestPatternColorGrid;
        private ProWrite.UI.Controls.BarButtonItemEx btnTestPatternSolidColorRed;
        private ProWrite.UI.Controls.BarButtonItemEx btnTestPatternSolidColorGreen;
        private ProWrite.UI.Controls.BarButtonItemEx btnTestPatternSolidColorBlue;
        private ProWrite.UI.Controls.BarButtonItemEx btnTestPatternSolidColorWhite;
        private ProWrite.UI.Controls.BarButtonItemEx btnTestPatternSolidColorAmber;
        private ProWrite.UI.Controls.BarButtonItemEx btnTestPatternSolidColor;
        private DevExpress.XtraBars.PopupMenu popupMenu1;
        private DevExpress.XtraBars.PopupMenu popupMenu2;


        #region Live
        private DevExpress.XtraBars.Ribbon.RibbonPage ribbonPageLive;
        private DevExpress.XtraBars.Ribbon.RibbonPageGroup ribbonPageGroupLiveSession;
        private BarEditItem cmbSession;
        private DevExpress.XtraEditors.Repository.RepositoryItemComboBox repositoryItemComboBox1;
        private BarStaticItem txtCurrentSession;
        private BarMdiChildrenListItem barMdiChildrenListItem1;
        private BarButtonItem btnSessionLoad;
        private BarButtonItem btnSessionSave;
        private BarButtonGroup btnGroup;
        private BarButtonItemEx btnGoLive;
        private BarButtonItemEx btnSync;
        private BarButtonItemEx btnSessionSetup;
        private BarButtonItem btnLibraryNew;
        private DevExpress.XtraBars.Ribbon.RibbonPageGroup ribbonPageGroupLibrary;
        private BarButtonItem btnLibraryOpen;
        private BarButtonItem btnLiveProperties;
        private DevExpress.XtraBars.Ribbon.RibbonPageGroup ribbonPageGroupModify;
        #endregion
    }
}
