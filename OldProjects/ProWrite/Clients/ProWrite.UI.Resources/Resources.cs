//---------------------------------------------------------------------
//
// File: Resources.cs
//
// Description:
// Get all resource from res file using resource key
//
// Author: Louis
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
// Modification History
// Louis 2008-6-25 Add icons resource
// Terry 2008-6-26 Add strings of dashboard module
//---------------------------------------------------------------------
using System;
using System.Reflection;
using System.Resources;
using System.Drawing;
using System.Globalization;
using System.Text.RegularExpressions;

namespace ProWrite.Resources
{
    /// <summary>
    /// Resource class
    /// </summary>
    public abstract class Resource
    {
        private static readonly ResourceManager _rmImage = new ResourceManager("ProWrite.Resources.ResImages", Assembly.GetExecutingAssembly());
        private static readonly ResourceManager _rmString = new ResourceManager("ProWrite.Resources.ResStrings", Assembly.GetExecutingAssembly());
        private static readonly ResourceManager _rmHelp = new ResourceManager("ProWrite.Resources.ResHelps", Assembly.GetExecutingAssembly());

        private static CultureInfo _culture;

        /// <summary>
        /// Recource key of strings constance class 
        /// </summary>
        public abstract class Strings
        {
            public const string
                Add = "Add",
                Edit = "Edit",
                Dashboard = "Dashboard",
                NameError = "NameError",
                AddSignGroupUnderSign = "AddSignGroupUnderSign",
                AssignableFailingMessage = "AssignableFailingMessage",
                AddSignGroup = "AddSignGroup",
                AddSign = "AddSign",
                ButtonCaptionYes = "Button.Caption.Yes",
                ButtonCaptionYesToolTip = "Button.Caption.Yes.ToolTip",
                ButtonCaptionNo = "Button.Caption.No",
                ButtonCaptionNoToolTip = "Button.Caption.Yes.ToolTip",
                ButtonCaptionCancel = "Button.Caption.Cancel",
                ButtonCaptionCancelToolTip = "Button.Caption.Yes.ToolTip",
                BatchLoadResultInfoStart = "BatchLoad.ResultInfo.Start",
                BatchLoadResultInfoSuccess = "BatchLoad.ResultInfo.Success",
                BatchLoadResultInfoFailure = "BatchLoad.ResultInfo.Failure",
                BatchLoadResultInfoTitle = "BatchLoad.ResultInfo.Title",
                ConfirmDeleteItem = "ConfirmDeleteItem",
                ConfirmDeleteImage = "ConfirmDeleteImage",
                ConfirmDeleteLayer = "ConfirmDeleteLayer",
                ConfirmDeleteMsg = "ConfirmDeleteMsg",
                ConfirmDeletePlaylist = "ConfirmDeletePlaylist",
                ConfirmDeleteSign = "ConfirmDeleteSign",
                ConfirmDeleteGroup = "ConfirmDeleteGroup",
                ConfirmSaveChange = "ConfirmSaveChange",
                UploadSchedulerConnectFTPServer = "Upload.Scheduler.ConnectFTPServer",
                Delete = "Delete",
                DeleteFailed = "DeleteFailed",
                LibraryTreeDeleteFailed = "LibraryTree.DeleteFailed",
                LibraryTreeControlDeleteConfirmDeleteItem = "LibraryTreeControl.Delete.ConfirmDeleteItem",
                DialogConfirmInfo = "Dialog.Confirm.Info",
                DialogSaveEmptyInfo = "Dialog.SaveEmpty.Info",
                ErrorUnableToLocateFile = "ErrorUnableToLocateFile",
                ErrorHapenViewLog = "ErrorHapenViewLog",
                ExceedSignNumber = "ExceedSignNumber",
                EditerInsertFileLock = "Editer.Insert.File.Lock",
                EditSignGroup = "EditSignGroup",
                EditSign = "EditSign",
                EmailAddress = "EmailAddress",
                EmailSubject = "EmailSubject",
                GreaterThanFailingMessage = "GreaterThanFailingMessage",
                GreaterThanOrEqualFailMessage = "GreaterThanOrEqualFailMessage",
                GroupEmpty = "GroupEmpty",
                HelpDeskInfo = "HelpDeskInfo",
                InfoSaveMessage = "InfoSaveMessage",
                ImportNameMaxLength = "ImportNameMaxLength",
                NewFileName = "NewFileName",
                LessThanFailingMessage = "LessThanFailingMessage",
                LessThanOrEqualFailingMessage = "LessThanOrEqualFailingMessage",
                LoginForm_HelpDesk = "LoginForm.HelpDesk",
                LoginForm_http = "LoginForm.http",
                LoginForm_ProWrite = "LoginForm.ProWrite",

                LoginForm_HaveNoRegisted = "LoginForm.HaveNoRegisted",
                LoginForm_OverDue = "LoginOverDue",
                DashboardForm_lblParent = "DashboardForm.lblParent",
                DashboardForm_lblGroupName = "DashboardForm.lblGroupName",
                DashboardForm_lblSignName = "DashboardForm.lblSignName",
                DashboardForm_lbnSignType = "DashboardForm.lbnSignType",
                DashboardForm_lblPX = "DashboardForm.lblPX",
                DashboardForm_lblWidth = "DashboardForm.lblWidth",
                DashboardForm_lblHeight = "DashboardForm.lblHeight",
                DashboardForm_lblImage = "DashboardForm.lblImage",
                DashBoard_SaveSignRepeat = "DashBoard.SaveSignRepeat",
                DashBoard_SaveGroupRepeat = "DashBoard.SaveGroupRepeat",
                DashboardForm_newSignTool = "DashboardForm.newSignTool",
                DashboardForm_newSignGroupTool = "DashboardForm.newSignGroupTool",
                DashboardForm_lblResponding = "DashboardForm.lblResponding",
                DashboardForm_lblNA = "DashboardForm.lblNA",
                DashboardForm_lblMisConfiguration = "DashboardForm.lblMisConfiguration",
                DashboardForm_lblMaintenceRequired = "DashboardForm.lblMaintenceRequired",
                DashboardForm_lblLastUpdate = "DashboardForm.lblLastUpdate",
                DashboardForm_lblHoustingMarketDown = "DashboardForm.lblHoustingMarketDown",
                DashboardForm_lblFaulty = "DashboardForm.lblFaulty",
                DashboardForm_lblF = "DashboardForm.lblF",
                DashboardForm_lblEtc = "DashboardForm.lblEtc",
                DashboardForm_lblE = "DashboardForm.lblE",
                DashboardForm_grpStorageIndicator = "DashboardForm.grpStorageIndicator",
                DashboardForm_grpSignStatus = "DashboardForm.grpSignStatus",
                DashboardForm_grpSignImage = "DashboardForm.grpSignImage",
                DashboardForm_grpCurrentClip = "DashboardForm.grpCurrentClip",
                DashboardForm_grbCurrentSign = "DashboardForm.grbCurrentSign",
                DashboardForm_editTool = "DashboardForm.editTool",
                DashboardForm_deleteTool = "DashboardForm.deleteTool",
                DefaultInformationDeleteFailed = "DefaultInformationDeleteFailed",
                DashboardTemplateChanged = "Dashboard.TemplateChanged",
                //DialogConfirmInfo = "Dialog.Confirm.Info",
                EditerFontSelectFormFontSizeText = "Editer.FontSelectForm.FontSizeText",
                EditerFontSelectFormFontStyleText = "Editer.FontSelectForm.FontStyleText",
                EditerFontSelectFormFontText = "Editer.FontSelectForm.FontText",
                EditerFontSelectFormFontTypeText = "Editer.FontSelectForm.FontTypeText",
                EditerShapeLabelIsAddNewLayer = "Editer.ShapeLabel.IsAddNewLayer",
                EditerInsertFileExist = "Editer.Insert.File.Exist",
                IsExist = "IsExist",
                LibraryTreeControlRightMenuRenameTitle = "LibraryTreeControl.RightMenu.Rename.Title",
                LibraryTreeControlRightMenuDeleteTitle = "LibraryTreeControl.RightMenu.Delete.Title",
                LibraryTreeControlRightMenuImportTitle = "LibraryTreeControl.RightMenu.Import.Title",
                LibraryTreeControlRightMenuExportTitle = "LibraryTreeControl.RightMenu.Export.Title",

                LibraryOpenFailure = "Library.OpenFailure",
                LibraryGroupEdit = "LibraryGroup.Edit",
                LibraryGroupDelete = "LibraryGroup.Delete",

                LibraryDialogLibraryIsOpen = "LibraryDialog.Library.IsOpen",
                LibraryTreeImportFailure = "LibraryTree.Import.Failure",

                LibraryLockRemove = "Library.LockRemove",
                LibraryTreeDeleteFailedIsLock = "LibraryTree.DeleteFailed.IsLock",
                LibraryTreeDeleteFailedFileIsLock = "LibraryTree.DeleteFailed.FileIsLock",
                LibraryTreeDeleteSuccess = "LibraryTree.DeleteSuccess",
                LibraryTreeDeleteFailedIsOpen = "LibraryTree.DeleteFailed.IsOpen",

                LiveCategoryItemEditFormCaption = "Live.CategoryItem.EditForm.Caption",
                LiveCategoryItemEditFormTitle = "Live.CategoryItem.EditForm.Title",
                LiveEditFormNameExists = "Live.EditForm.NameExists",
                LibraryImportNameExistInfo = "Library.Import.Name.ExistInfo",
                MessageFileIsNotExist = "MessageFileIsNotExist",
                MessageChangeLayerName = "Message.ChangeLayerName",
                MessageLayerNameNotNull = "Message.LayerNameNotNull",
                MessageShapOutSide = "Message.ShapOutSide",
                OK = "OK",
                OptionButtonTextYes = "OptionButtonTextYes",
                OptionButtonTextNo = "OptionButtonTextNo",

            #region Playlist
 PlayListAppendEffectException = "PlayList.AppendEffectException",
                PlayListAppendLayerException = "PlayList.AppendLayerException",
                PlayListAppendPropertyException = "PlayList.AppendPropertyException",
                PlayListConvertLabelTimeToPixelException = "PlayList.ConvertLabelTimeToPixelException",
                PlayListConvertLabelTimeToSecondException = "PlayList.ConvertLabelTimeToSecondException",
                PlayListConvertLabelTimeToTimeException = "PlayList.ConvertLabelTimeToTimeException",
                PlayListConvertPixelToTimeException = "PlayList.ConvertPixelToTimeException",
                PlayListConvertPixelToLabelTimeException = "PlayList.ConvertPixelToLabelTimeException",
                PlayListConvertTimeToPixelException = "PlayList.ConvertTimeToPixelException",
                PlayListConvertTimeToSecondException = "PlayList.ConvertTimeToSecondException",
                PlayListCreateImageException = "PlayList.CreateImageException",
                PlayListCreateNewImageException = "PlayList.CreateNewImageException",
                PlayListDefaultTimeSliceGroupName = "PlayList.DefaultTimeSliceGroupName",
                PlayListDragDropLayoutControlDeleteMessageBtnException = "PlayList.DragDropLayoutControl.DeleteMessageBtnException",
                PlayListDragDropLayoutControlInitException = "PlayList.DragDropLayoutControl.InitException",
                PlayListDragDropLayoutControlInitializeResourceException = "PlayList.DragDropLayoutControl.InitializeResourceException",
                PlayListDragDropLayoutControlMessageBtnDragDropEventException = "PlayList.DragDropLayoutControl.MessageBtnDragDropEventException",
                PlayListDragDropLayoutControlMessageBtnMouseDownEventException = "PlayList.DragDropLayoutControl.MessageBtnMouseDownEventException",
                PlayListDragDropLayoutControlMessageBtnMouseUpEventException = "PlayList.DragDropLayoutControl.MessageBtnMouseUpEventException",
                PlayListDragDropLayoutControlPanelControlDragDropEventException = "PlayList.DragDropLayoutControl.PanelControlDragDropEventException",
                PlayListDragDropLayoutControlSendPropertyMessageException = "PlayList.DragDropLayoutControl.SendPropertyMessageException",
                PlayListDragDropLayoutControlSizeChangedEventException = "PlayList.DragDropLayoutControl.SizeChangedEventException",
                PlayListDragDropLayoutControlUpdateTotalTimesException = "PlayList.DragDropLayoutControl.UpdateTotalTimesException",
                PlayListDragDropLayoutControlViewMessageException = "PlayList.DragDropLayoutControl.ViewMessageException",
                PlayListDragDropLayoutControlViewPlayListException = "PlayList.DragDropLayoutControl.ViewPlayListException",
                PlayListDragDropLayoutControlZoomException = "PlayList.DragDropLayoutControl.ZoomException",
                PlayListGetCurrentSecondByListIndexForNextException = "PlayList.GetCurrentSecondByListIndexForNextException",
                PlayListGetCurrentSecondByListIndexForPreviousException = "PlayList.GetCurrentSecondByListIndexForPreviousException",
                PlayListGetDsVideoException = "PlayList.GetDsVideoException",
                PlayListGetNewLayerSizeAndLocationException = "PlayList.GetNewLayerSizeAndLocationException",
                PlayListGetPlayListPropertyException = "PlayList.GetPlayListPropertyException",
                PlayListInitEffectException = "PlayList.InitEffectException",
                PlayListLabelTimeDefaultText = "PlayList.LabelTimeDefaultText",
                PlayListMessageLengthIsZero = "PlayList.MessageLengthIsZero",
                PlayListMessageLengthEmpty = "PlayList.MessageLengthEmpty",
                PlayListNameEmpty = "PlayList.NameEmpty",
                PlayListOpenMessageException = "PlayList.OpenMessageException",
                PlaylistManyLevel = "Playlist.ManyLevel",



                PlayListPlayListLengthEmpty = "PlayList.PlayListLengthEmpty",
                PlayListPlayListsBarGetPlayListException = "PlayList.PlayListsBar.GetPlayListException",
                PlayListPlayListsBarInitException = "PlayList.PlayListsBar.InitException",
                PlayListPlayListsBarInitializeResourceException = "PlayList.PlayListsBar.InitializeResourceException",
                PlayListPlayListsBarPlayClickEventException = "PlayList.PlayListsBar.PlayClickEventException",
                PlayListPlayListsBarPlayCompletedEventException = "PlayList.PlayListsBar.PlayCompletedEventException",
                PlayListPlayListsBarPlayingException = "PlayList.PlayListsBar.PlayingException",
                PlayListPlayListsBarPlayNextClickEventException = "PlayList.PlayListsBar.PlayNextClickEventException",
                PlayListPlayListsBarPlayPaintEventExceptiohn = "PlayList.PlayListsBar.PlayPaintEventExceptiohn",
                PlayListPlayListsBarPlayPreviousClickEventException = "PlayList.PlayListsBar.PlayPreviousClickEventException",
                PlayListPlayListsBarRecycleDragDropEventException = "PlayList.PlayListsBar.RecycleDragDropEventException",
                PlayListPlayListsBarRecycleDragEnterEventException = "PlayList.PlayListsBar.RecycleDragEnterEventException",
                PlayListPlayListsBarRecycleDragLeaveEventException = "PlayList.PlayListsBar.RecycleDragLeaveEventException",
                PlayListPlayListsBarSaveClickEventException = "PlayList.PlayListsBar.SaveClickEventException",
                PlayListPlayListsBarScrollBarScrollEventException = "PlayList.PlayListsBar.ScrollBarScrollEventException",
                PlayListPlayListsBarScrollBarValueChangedEventException = "PlayList.PlayListsBar.ScrollBarValueChangedEventException",
                PlayListPlayListsBarSetPlayingStatusException = "PlayList.PlayListsBar.SetPlayingStatusException",
                PlayListPlayListsBarZoomInClickEventException = "PlayList.PlayListsBar.ZoomInClickEventException",
                PlayListPlayListsBarZoomOutClickEventException = "PlayList.PlayListsBar.ZoomOutClickEventException",
                PlayListPlayListsSaveInitializeResourceException = "PlayList.PlayListsSave.InitializeResourceException",
                PlayListPlayListsSaveSaveException = "PlayList.PlayListsSave.SaveException",
                PlayListPlayListsSignTabInitException = "PlayList.PlayListsSignTab.InitException",
                PlaylistPlaylistControlInitializeResourceException = "PlayList.PlayListsSignTab.InitializeResourceException",
                PlayListPlayListsSignTabPanelResizeEventException = "PlayList.PlayListsSignTab.PanelResizeEventException",
                PlayListPlayListsTabAppendNewSignTabException = "PlayList.PlayListsTab.AppendNewSignTabException",
                PlayListPlayListsTabAppendSignTabException = "PlayList.PlayListsTab.AppendSignTabException",
                PlaylistPlaylistsTabCurrentSignSelectedValueChangedEventException = "PlayList.PlayListsTab.CurrentSignSelectedValueChangedEventException",
                PlayListPlayListsTabDeletePlayListElementException = "PlayList.PlayListsTab.DeletePlayListElementException",
                PlayListPlayListsTabInitException = "PlayList.PlayListsTab.InitException",
                PlayListPlayListsTabInitializeResourceException = "PlayList.PlayListsTab.InitializeResourceException",
                PlaylistPlaylistsTabInitMenuException = "PlayList.PlayListsTab.InitMenuException",
                PlayListPlayListsTabInsertMessageException = "PlayList.PlayListsTab.InsertMessageException",
                PlayListPlayListsTabInsertPlayListException = "PlayList.PlayListsTab.InsertPlayListException",
                PlayListPlayListsTabNewPlayListException = "PlayList.PlayListsTab.NewPlayListException",
                PlaylistPlaylistsTabOpenMessageException = "PlayList.PlayListsTab.OpenMessageException",
                PlaylistPlaylistsTabSaveAllPlaylistException = "PlayList.PlayListsTab.SaveAllPlayListException",
                PlayListPlayListsTabSaveAsPlayListException = "PlayList.PlayListsTab.SaveAsPlayListException",
                PlaylistPlaylistsTabSavePlaylistException = "PlayList.PlayListsTab.SavePlayListException",
                PlaylistPlaylistsTabTabSignCloseButtonClickException = "PlayList.PlayListsTab.TabSignCloseButtonClickException",
                PlaylistPlaylistsTabUpdateDisplayInfoAfterSaveException = "PlayList.PlayListsTab.UpdateDisplayInfoAfterSaveException",
                PlayListPlayListsTrackBarClearTimeLabelException = "PlayList.PlayListsTrackBar.ClearTimeLabelException",
                PlayListPlayListsTrackBarInitException = "PlayList.PlayListsTrackBar.InitException",
                PlayListPlayListsTrackBarInitializeResourceException = "PlayList.PlayListsTrackBar.InitializeResourceException",
                PlaylistPlaylistTrackBarInitTimeValueLabelException = "PlayList.PlayListsTrackBar.InitTimeValueLabelException",
                PlaylistPlaylistTrackBarPlayTrackBarCtrlValueChangedEventException = "PlayList.PlayListsTrackBar.PlayTrackBarCtrlValueChangedEventException",
                PlaylistPlaylistTrackBarZoomException = "PlayList.PlayListsTrackBar.ZoomException",
                PlayListSaveExit = "PlayList.SaveExit",
                PlayListSaveTotalLengthEmpty = "PlayList.SaveTotalLengthEmpty",
                PlayListTimeSliceGroupControlConfigMessageActiveException = "PlayList.TimeSliceGroupControl.ConfigMessageActiveException",
                PlayListTimeSliceGroupControlDragDropException = "PlayList.TimeSliceGroupControl.DragDropException",
                PlayListTimeSliceGroupControlDragMessageException = "PlayList.TimeSliceGroupControl.DragMessageException",
                PlayListTimeSliceGroupControlEditGroupInfoException = "PlayList.TimeSliceGroupControl.EditGroupInfoException",
                PlayListTimeSliceGroupControlGroupItemActiveTitle = "PlayList.TimeSliceGroupControl.GroupItemActiveTitle",
                PlayListTimeSliceGroupControlGroupItemNameTitle = "PlayList.TimeSliceGroupControl.GroupItemNameTitle",
                PlayListTimeSliceGroupControlGroupItemLengthTitle = "PlayList.TimeSliceGroupControl.GroupItemLengthTitle",
                PlayListTimeSliceGroupControlGroupItemTypeTitle = "PlayList.TimeSliceGroupControl.GroupItemTypeTitle",
                PlayListTimeSliceGroupControlLabelGroupTitle = "PlayList.TimeSliceGroupControl.LabelGroupTitle",
                PlayListTimeSliceGroupControlLoadGroupInfoException = "PlayList.TimeSliceGroupControl.LoadGroupInfoException",
                PlayListTimeSliceGroupControlMoveMessageException = "PlayList.TimeSliceGroupControl.MoveMessageException",
                PlayListTimeSliceGroupControlReloadNodesException = "PlayList.TimeSliceGroupControl.ReloadNodesException",
                PlayListTimeSliceGroupEditFormAddTitle = "PlayList.TimeSliceGroupEditForm.AddTitle",
                PlayListTimeSliceGroupEditFormEditTitle = "PlayList.TimeSliceGroupEditForm.EditTitle",
                PlayListTimeSliceGroupEditFormNameEmpty = "PlayList.TimeSliceGroupEditForm.NameEmpty",
                PlayListTimeSliceGroupEditFormNameTitle = "PlayList.TimeSliceGroupEditForm.NameTitle",
                PlayListTimeSliceGroupEditFormLengthTitle = "PlayList.TimeSliceGroupEditForm.LengthTitle",
                PlayListTimeSliceGroupEditFormLengthZero = "PlayList.TimeSliceGroupEditForm.LengthZero",
                PlayListTimeSliceGroupEditFormRandomTitle = "PlayList.TimeSliceGroupEditForm.RandomTitle",
                PlayListTimeSliceGroupEditFormSaveException = "PlayList.TimeSliceGroupEditForm.SaveException",
                PlayListTimeSliceGroupEditFormTimeFormat = "PlayList.TimeSliceGroupEditForm.TimeFormat",
                PlayListTimeSliceGroupLengthEmpty = "PlayList.TimeSliceGroupLengthEmpty",
                PlayListTimeSliceGroupControlGroupItemCountEmpty = "PlayList.TimeSliceGroupControl.GroupItemCountEmpty",
                PlayListTimeSliceGroupControlRightMenuSetNailImageTitle = "PlayList.TimeSliceGroupControl.RightMenu.SetNailImage.Title",
                PlayListViewMessageException = "PlayList.ViewMessageException",
                PlayListViewMessageFailure = "PlayList.ViewMessageFailure",
                PlayListViewPlayListException = "PlayList.ViewPlayListException",
                PlayListViewPlayListFailure = "PlayList.ViewPlayListFailure",
                PlaylistTimeDefaultText = "PlayList.TimeDefaultText",
                PlayListSaveFormTitle = "PlayList.SaveForm.Title",
                PlayListSaveFormPlayListNameTitle = "PlayList.SaveForm.PlayListNameTitle",
                PlaylistNotDragItself = "Playlist.NotDragItself",
            #endregion
 ProductName = "ProductName",
                Save = "Save",
                SaveAs = "SaveAs",
                SaveFailed = "SaveFailed",
                Savesuccess = "Savesuccess",
                SaveEmptyInfo = "Save.Empty.Info",
                SendSendToSignNoPermission = "Send.SendToSign.NoPermission",
                SendSendToSignLoginFirst = "Send.SendToSign.LoginFirst",
                SendSendToSignSignConflict = "Send.SendToSign.SignConflict",
                SendSaveFirst = "Send.SaveFirst",
                SignEmpty = "SignEmpty",
                SignsCountMoreThanTwenty = "SignsCountMoreThanTwenty",
                SerialGen_RegsterError = "SerialGen.RegsterError",
                SettingDefaultHasUsed = "SettingDefaultHaveUsed",
                TemplateEmpty = "TemplateEmpty",
                TemplateRepeat = "TemplateRepeat",
                TimeSliceGroupDeleteFailed = "TimeSliceGroup.DeleteFailed",
                TimesliceGroupEditFormTitleAdd = "TimesliceGroup.EditForm.Title.Add",
                TimesliceGroupEditFormTitleEdit = "TimesliceGroup.EditForm.Title.Edit",
                Cancel = "Cancel",
                Image = "Image",
                PlayList = "PlayList",
                Layer = "Layer",
                Message = "Message",
                AddNewLibraryGrpName = "AddNewLibraryGrpName",
                EditLibraryGrpName = "EditLibraryGrpName",
                ImageFileNotExist = "ImageFileNotExist",
                NameAlreadyExist = "NameAlreadyExist",
                InputName = "InputName",
                MessageChanged = "MessageChanged",
                AddNewSignFirst = "AddNewSignFirst",

                LiveHotButtonEditTypeTitle = "Live.HotButtonEdit.TypeTitle",
                LiveHotButtonEditNameTitle = "Live.HotButtonEdit.NameTitle",
                LiveHotButtonEditTitle = "Live.HotButtonEdit.Title",
                LiveHotButtonEditFormTitle = "Live.HotButtonEdit.FormTitle",
                LiveHotButtonEditTypeEmpty = "Live.HotButtonEdit.Type.Empty",
                LiveHotButtonDragReplaceInfo = "Live.HotButton.Drag.Replace.Info",

                LibraryLibraryFileItemSourceCaption = "Library.LibraryFileItem.SourceCaption",
                LibraryLibraryFileItemDestCaption = "Library.LibraryFileItem.DestCaption",
                LibraryLibraryFileItemCheckCaption = "Library.LibraryFileItem.CheckCaption",
                LibraryLibraryFileItemTitle = "Library.LibraryFileItem.Title",

                LibraryLibraryMessageItemSourceCaption = "Library.LibraryMessageItem.SourceCaption",
                LibraryLibraryMessageItemDestCaption = "Library.LibraryMessageItem.DestCaption",
                LibraryLibraryMessageItemCheckCaption = "Library.LibraryMessageItem.CheckCaption",
                LibraryLibraryMessageItemTitle = "Library.LibraryMessageItem.Title",

                LibraryImportTimeSliceGroupGroupItemSourceCaption = "Library.Import.TimeSliceGroup.GroupItem.SourceCaption",
                LibraryImportTimeSliceGroupGroupItemTargetCaption = "Library.Import.TimeSliceGroup.GroupItem.TargetCaption",

                LibraryImportPlaylistGroupItemSourceCaption = "Library.Import.Playlist.GroupItem.SourceCaption",
                LibraryImportPlaylistGroupItemTargetCaption = "Library.Import.Playlist.GroupItem.TargetCaption",
                RebootCXC = "RebootCXC",
                ShapSelectFormatFirst = "Shap.SelectFormatFirst",

                SkinName = "SkinName",
                NameEmpty = "NameEmpty",
                MessageIsEmpty = "MessageIsEmpty",
                LibrarySaveFormTitle = "Library.SaveForm.Title",
                LibrarySaveFormNameExists = "Library.SaveForm.NameExists",
                NameLengthLimit = "NameLengthLimit",
                ConfirmRenameItem = "ConfirmRenameItem",
                NewLibraryName = "NewLibraryName",
                FileRenameInvalid = "FileRenameInvalid",
                NameRegulation = "NameRegulation",
                LiveCategoryLinkEditFormCaption = "Live.CategoryLink.EditForm.Caption",
                LiveCategoryLinkEditFormTitle = "Live.CategoryLink.EditForm.Title",

                //Upload scheduler info resources
                GetLockFailure = "GetLock.Failure",
                UploadSuccessful = "Upload.Successful",
                UploadFailed = "Upload.Failed",
                UploadGetLockStart = "Upload.GetLock.Start",
                UploadGetLockFailed = "Upload.GetLock.Failed",
                UploadGetLockSuccessful = "Upload.GetLock.Successful",
                ConnectionException = "Connection.Exception",
                UploadSchedulerPopulateStart = "Upload.Scheduler.Populate.Start",
                UploadSchedulerPopulateException = "Upload.Scheduler.Populate.Exception",
                UploadSchedulerSaveStart = "Upload.Scheduler.Save.Start",
                UploadSchedulerSaveException = "Upload.Scheduler.Save.Exception",
                UploadSchedulerSaveEnd = "Upload.Scheduler.Save.End",
                UploadSchedulerSaveFailed = "Upload.Scheduler.Save.Failed",
                UploadSchedulerEmpty = "Upload.Scheduler.Empty",
                UploadSchedulerLibraryFileEmpty = "Upload.Scheduler.LibraryFile.Empty",
                UploadSchedulerUploadStart = "Upload.Scheduler.Upload.Start",
                UploadSchedulerUploadException = "Upload.Scheduler.Upload.Exception",
                UploadSchedulerUploadFtpStart = "Upload.Scheduler.Upload.Ftp.Start",
                UploadSchedulerUploadFtpEnd = "Upload.Scheduler.Upload.Ftp.End",
                UploadSchedulerUploadSuccessful = "Upload.Scheduler.Upload.Successful",
                UploadSchedulerUploadFtpFileStart = "Upload.Scheduler.Upload.Ftp.File.Start",
                UploadSchedulerUploadFtpFileEnd = "Upload.Scheduler.Upload.Ftp.File.End",
                UploadSchedulerUploadFtpFileException = "Upload.Scheduler.Upload.Ftp.File.Exception",
                UploadFtpServerDisConnection = "Upload.FtpServer.DisConnection",
                UploadGetLockFailedNoParameter = "Upload.GetLock.Failed.NoParameter",
                UpLoadMessageSuccessful = "UpLoad.MessageSuccessful",
                UpLoadMessageNotLiveSign = "UpLoad.MessageNotLiveSign",
                UpLoadMessageConfirm = "UpLoad.MessageConfirm",

                ServerDisConnection = "Server.DisConnection",

                RibbonBarbtnSaveCaption = "RibbonBar.General.btnSave.Caption",
                RibbonBarbtnSaveHint = "RibbonBar.General.btnSave.Hint"
                , RibbonBarbtnSaveAsCaption = "RibbonBar.General.btnSaveAs.Caption"
                , RibbonBarbtnSaveAsHint = "RibbonBar.General.btnSaveAs.Hint"
                , RibbonBarbtnBatchLoadCaption = "RibbonBar.General.btnBatchLoad.Caption"
                , RibbonBarbtnBatchLoadHint = "RibbonBar.General.btnBatchLoad.Hint"
                , RibbonBarbtnAboutCaption = "RibbonBar.General.btnAbout.Caption"
                , RibbonBarbtnAboutHint = "RibbonBar.General.btnAbout.Hint"
                , RibbonBarbtnHelpCaption = "RibbonBar.General.btnHelp.Caption"
                , RibbonBarbtnProfaneWordsCaption = "RibbonBar.General.btnProfaneWords.Caption"
                , RibbonBarbtnProfaneWordsHint = "RibbonBar.General.btnProfaneWords.Hint"
                , RibbonBarbtnHelpHint = "RibbonBar.General.btnHelp.Hint"
                , RibbonBarbtnImportCaption = "RibbonBar.General.btnImport.Caption"
                , RibbonBarbtnImportHint = "RibbonBar.General.btnImport.Hint"
                , RibbonBarbtnExportCaption = "RibbonBar.General.btnExport.Caption"
                , RibbonBarbtnExportHint = "RibbonBar.General.btnExport.Hint"
                , RibbonBarbtnExitCaption = "RibbonBar.General.btnExit.Caption"
                , RibbonBarbtnExitHint = "RibbonBar.General.btnExit.Hint"
                , RibbonBarbtnNewMessageCaption = "RibbonBar.General.btnNewMessage.Caption"
                , RibbonBarbtnNewMessageHint = "RibbonBar.General.btnNewMessage.Hint"
                , RibbonBarbtnNewPlaylistCaption = "RibbonBar.General.btnNewPlaylist.Caption"
                , RibbonBarbtnNewPlaylistHint = "RibbonBar.General.btnNewPlaylist.Hint"
                , RibbonBarbtnNewSchedulerCaption = "RibbonBar.General.btnNewScheduler.Caption"
                , RibbonBarbtnNewSchedulerHint = "RibbonBar.General.btnNewScheduler.Hint"
                , RibbonBarbtnNewLibraryCaption = "RibbonBar.General.btnNewLibrary.Caption"
                , RibbonBarbtnNewLibraryHint = "RibbonBar.General.btnNewLibrary.Hint"
                , RibbonBarbtnNewTimeSliceGroupCaption = "RibbonBar.General.btnNewTimeSliceGroup.Caption"
                , RibbonBarbtnNewTimeSliceGroupHint = "RibbonBar.General.btnNewTimeSliceGroup.Hint"
                , RibbonBarbtnNewCaption = "RibbonBar.General.btnNew.Caption"
                , RibbonBarbtnNewHint = "RibbonBar.General.btnNew.Hint"
                , RibbonBarbtnNewSignCaption = "RibbonBar.General.btnNewSign.Caption"
                , RibbonBarbtnNewSignHint = "RibbonBar.General.btnNewSign.Hint"
                , RibbonBarbtnNewSignGroupCaption = "RibbonBar.General.btnNewSignGroup.Caption"
                , RibbonBarbtnNewSignGroupHint = "RibbonBar.General.btnNewSignGroup.Hint"
                , RibbonBarbtnLoginCaption = "RibbonBar.General.btnLogin.Caption"
                , RibbonBarbtnLoginHint = "RibbonBar.General.btnLogin.Hint"
                , RibbonBarbtnLogoffHint = "RibbonBar.General.btnLogoff.Hint"
                , RibbonBarbtnPropertiesCaption = "RibbonBar.General.btnProperties.Caption"
                , RibbonBarbtnPropertiesHint = "RibbonBar.General.btnProperties.Hint"
                , RibbonBarbtnSignStatusCaption = "RibbonBar.General.btnSignStatus.Caption"
                , RibbonBarbtnSignStatusHint = "RibbonBar.General.btnSignStatus.Hint"
                , RibbonBarbtnChangePSWCaption = "RibbonBar.General.btnChangePSW.Caption"
                , RibbonBarbtnChangePSWHint = "RibbonBar.General.btnChangePSW.Hint"
                , RibbonBarbtnSetDateTimeCaption = "RibbonBar.General.btnSetDateTime.Caption"
                , RibbonBarbtnSetDateTimeHint = "RibbonBar.General.btnSetDateTime.Hint"
                , RibbonBarbtnBlankSignCaption = "RibbonBar.General.btnBlankSign.Caption"
                , RibbonBarbtnBlankSignHint = "RibbonBar.General.btnBlankSign.Hint"
                , RibbonBarbtnTestPatternCaption = "RibbonBar.General.btnTestPattern.Caption"
                , RibbonBarbtnTestPatternHint = "RibbonBar.General.btnTestPattern.Hint"
                , RibbonBarbtnDeleteCaption = "RibbonBar.General.btnDelete.Caption"
                , RibbonBarbtnDeleteHint = "RibbonBar.General.btnDelete.Hint"
                , RibbonBarbtnSetupCaption = "RibbonBar.General.btnSetup.Caption"
                , RibbonBarbtnSetupHint = "RibbonBar.General.btnSetup.Hint"
                , RibbonBarbtnDimmingCaption = "RibbonBar.General.btnDimming.Caption"
                , RibbonBarbtnDimmingHint = "RibbonBar.General.btnDimming.Hint"
                , RibbonBarbtnTempOffsetCaption = "RibbonBar.General.btnTempOffset.Caption"
                , RibbonBarbtnTempOffsetHint = "RibbonBar.General.btnTempOffset.Hint"
                , RibbonBarbtnLiveViewCaption = "RibbonBar.General.btnLiveView.Caption"
                , RibbonBarbtnLiveViewHint = "RibbonBar.General.btnLiveView.Hint"
                , RibbonBarbtnDisplayCaption = "RibbonBar.General.btnDisplay.Caption"
                , RibbonBarbtnDisplayHint = "RibbonBar.General.btnDisplay.Hint"
                , RibbonBarbtnInsertImageCaption = "RibbonBar.General.btnInsertImage.Caption"
                , RibbonBarbtnInsertImageHint = "RibbonBar.General.btnInsertImage.Hint"
                , RibbonBarbtnInsertVideoCaption = "RibbonBar.General.btnInsertVideo.Caption"
                , RibbonBarbtnInsertVideoHint = "RibbonBar.General.btnInsertVideo.Hint"
                , RibbonBarbtnInsertTextCaption = "RibbonBar.General.btnInsertText.Caption"
                , RibbonBarbtnInsertTextHint = "RibbonBar.General.btnInsertText.Hint"
                , RibbonBarbtnInsertVariableTextCaption = "RibbonBar.General.btnInsertVariableText.Caption"
                , RibbonBarbtnInsertVariableTextHint = "RibbonBar.General.btnInsertVariableText.Hint"
                , RibbonBarbtnInsertTimeCaption = "RibbonBar.General.btnInsertTime.Caption"
                , RibbonBarbtnInsertTimeHint = "RibbonBar.General.btnInsertTime.Hint"
                , RibbonBarbtnInsertTemperatureCaption = "RibbonBar.General.btnInsertTemperature.Caption"
                , RibbonBarbtnInsertTemperatureHint = "RibbonBar.General.btnInsertTemperature.Hint"
                , RibbonBarbtnDrawingCaption = "RibbonBar.General.btnDrawing.Caption"
                , RibbonBarbtnDrawingHint = "RibbonBar.General.btnDrawing.Hint"
                , RibbonBarbtnRectangleCaption = "RibbonBar.General.btnRectangle.Caption"
                , RibbonBarbtnRectangleHint = "RibbonBar.General.btnRectangle.Hint"
                , RibbonBarbtnEllipseCaption = "RibbonBar.General.btnEllipse.Caption"
                , RibbonBarbtnEllipseHint = "RibbonBar.General.btnEllipse.Hint"
                , RibbonBarbtnArrowUpCaption = "RibbonBar.General.btnArrowUp.Caption"
                , RibbonBabtnArrowUpHint = "RibbonBar.General.btnArrowUp.Hint"
                , RibbonBarbtnbtnArrowDownCaption = "RibbonBar.General.btnArrowDown.Caption"
                , RibbonBarbtnbtnArrowDownHint = "RibbonBar.General.btnArrowDown.Hint"
                , RibbonBarbtnFillCaption = "RibbonBar.General.btnFill.Caption"
                , RibbonBarbtnFillDownHint = "RibbonBar.General.btnFill.Hint"
                , RibbonBarbtnLinecolorCaption = "RibbonBar.General.btnLinecolor.Caption"
                , RibbonBarbtnLinecolorDownHint = "RibbonBar.General.btnLinecolor.Hint"
                , RibbonBarbtnSendInEditorCaption = "RibbonBar.General.btnSendInEditor.Caption"
                , RibbonBarbtnSendInEditorHint = "RibbonBar.General.btnSendInEditor.Hint"
                , RibbonBarbtnSendInPlaylistCaption = "RibbonBar.General.btnSendInPlaylist.Caption"
                , RibbonBarbtnSendInPlaylistHint = "RibbonBar.General.btnSendInPlaylist.Hint"
                , RibbonBarbtnSendInSchedulerCaption = "RibbonBar.General.btnSendInScheduler.Caption"
                , RibbonBarbtnSendInSchedulerHint = "RibbonBar.General.btnSendInScheduler.Hint"
                , RibbonBarbtnSystemInitCaption = "RibbonBar.General.btnSystemInit.Caption"
                , RibbonBarbtnSystemInitHint = "RibbonBar.General.btnSystemInit.Hint"
                , RibbonBarbtnSystemDefaultCaption = "RibbonBar.General.btnSystemDefault.Caption"
                , RibbonBarbtnSystemDefaultHint = "RibbonBar.General.btnSystemDefault.Hint"
                , RibbonBarbtnUserManagerCaption = "RibbonBar.General.btnUserManager.Caption"
                , RibbonBarbtnUserManagerHint = "RibbonBar.General.btnUserManager.Hint"
                , RibbonBarbtnRedoCaption = "RibbonBar.General.btnRedo.Caption"
                , RibbonBarbtnRedoHint = "RibbonBar.General.btnRedo.Hint"
                , RibbonBarbtnUndoCaption = "RibbonBar.General.btnUndo.Caption"
                , RibbonBarbtnUndoHint = "RibbonBar.General.btnUndo.Hint"
                , RibbonBarbtnCopyCaption = "RibbonBar.General.btnCopy.Caption"
                , RibbonBarbtnCopyHint = "RibbonBar.General.btnCopy.Hint"
                , RibbonBarbtnPasteCaption = "RibbonBar.General.btnPaste.Caption"
                , RibbonBarbtnPasteHint = "RibbonBar.General.btnPaste.Hint"
                , RibbonBarbtnBoldCaption = "RibbonBar.General.btnBold.Caption"
                , RibbonBarbtnBoldHint = "RibbonBar.General.btnBold.Hint"
                , RibbonBarbtnItalicCaption = "RibbonBar.General.btnItalic.Caption"
                , RibbonBarbtnItalicHint = "RibbonBar.General.btnItalic.Hint"
                , RibbonBarbtnAlignLeftCaption = "RibbonBar.General.btnAlignLeft.Caption"
                , RibbonBarbtnAlignLeftHint = "RibbonBar.General.btnAlignLeft.Hint"
                , RibbonBarbtnCenterCaption = "RibbonBar.General.btnCenter.Caption"
                , RibbonBarbtnCenterHint = "RibbonBar.General.btnCenter.Hint"
                , RibbonBarbtnAlignRightCaption = "RibbonBar.General.btnAlignRight.Caption"
                , RibbonBarbtnAlignRightHint = "RibbonBar.General.btnAlignRight.Hint"
                , RibbonBarbtnFontColorCaption = "RibbonBar.General.btnFontColor.Caption"
                , RibbonBarbtnFontColorHint = "RibbonBar.General.btnFontColor.Hint"
                , RibbonBarbtnBackGroundColorCaption = "RibbonBar.General.btnBackGroundColor.Caption"
                , RibbonBarbtnBackGroundColorHint = "RibbonBar.General.btnBackGroundColor.Hint"
                , RibbonBarbtnTextFontNameCaption = "RibbonBar.General.btnTextFontName.Caption"
                , RibbonBarbtnTextFontNameHint = "RibbonBar.General.btnTextFontName.Hint"
                , RibbonBarbtnTextFontSizeCaption = "RibbonBar.General.btnTextFontSize.Caption"
                , RibbonBarbtnTextFontSizeHint = "RibbonBar.General.btnTextFontSize.Hint"
                , RibbonBarbtnLineCaption = "RibbonBar.General.btnLine.Caption"
                , RibbonBarbtnLineHint = "RibbonBar.General.btnLine.Hint"
                , RibbonBarbtnPointerCaption = "RibbonBar.General.btnPointer.Caption"
                , RibbonBarbtnPointerHint = "RibbonBar.General.btnPointer.Hint"
                , RibbonBarbarEditTextEffectCaption = "RibbonBar.General.barEditTextEffect.Caption"
                , RibbonBarbarEditTextEffectHint = "RibbonBar.General.barEditTextEffect.Hint"
                , RibbonBarbtnOpenCaption = "RibbonBar.General.btnOpen.Caption"
                , RibbonBarbtnOpenHint = "RibbonBar.General.btnOpen.Hint"
                , RibbonBarbtnOpenLibraryCaption = "RibbonBar.General.btnOpenLibrary.Caption"
                , RibbonBarbtnOpenLibraryHint = "RibbonBar.General.btnOpenLibrary.Hint"
                , RibbonBarbtnInsertCaption = "RibbonBar.General.btnInsert.Caption"
                , RibbonBarbtnInsertHint = "RibbonBar.General.btnInsert.Hint"
                , RibbonBarbtnTextKernCaption = "RibbonBar.General.btnTextKern.Caption"
                , RibbonBarbtnTextKernHint = "RibbonBar.General.btnTextKern.Hint"
                , RibbonBarbtnTextLeadCaption = "RibbonBar.General.btnTextLead.Caption"
                , RibbonBarbtnTextLeadHint = "RibbonBar.General.btnTextLead.Hint"
                , RibbonBarbtnZoomInLeadCaption = "RibbonBar.General.btnZoomIn.Caption"
                , RibbonBarbtnZoomInLeadHint = "RibbonBar.General.btnZoomIn.Hint"
                , RibbonBarbtnZoomOutCaption = "RibbonBar.General.btnZoomOut.Caption"
                , RibbonBarbtnZoomOutdHint = "RibbonBar.General.btnZoomOut.Hint"
                , RibbonBarbarLineWidthCaption = "RibbonBar.General.barLineWidth.Caption"
                , RibbonBarbarLineWidthdHint = "RibbonBar.General.barLineWidth.Hint"
                , RibbonBarbtnLineDashCaption = "RibbonBar.General.btnLineDash.Caption"
                , RibbonBarbtnLineDashdHint = "RibbonBar.General.btnLineDash.Hint"
                , RibbonBarbtnTextFrameFixedCaption = "RibbonBar.General.btnTextFrameFixed.Caption"
                , RibbonBarbtnTextFrameFixedHint = "RibbonBar.General.btnTextFrameFixed.Hint"
                , RibbonBarcmbSignCaption = "RibbonBar.General.cmbSign.Caption"
                , RibbonBarcmbSignHint = "RibbonBar.General.cmbSign.Hint"


                 , SetDimmingSuccessed = "SetDimmingSuccessed"
                , SetDimmingFailed = "SetDimmingFailed"
                , SetDateTimeSuccessed = "SetDateTimeSuccessed"
                , SetDateTimeFailed = "SetDateTimeFailed"
                , SetTempoffsetSuccessed = "SetTempoffsetSuccessed"
                , SetTempoffsetFailed = "SetTempoffsetFailed"
                , SetTimeZoneSuccessed = "SetTimeZoneSuccessed"
                , SetTimeZoneFailed = "SetTimeZoneFailed"
                , SetTestPatternSuccessed = "SetTestPatternSuccessed"
                , SetTestPatternFailed = "SetTestPatternFailed"
                , SetBlankSignSuccessed = "SetBlankSignSuccessed"
                , SetBlankSignFailed = "SetBlankSignFailed"
                , SetUnBlankSignSuccessed = "SetUnBlankSignSuccessed"
                , SetUnBlankSignFailed = "SetUnBlankSignFailed"
                , TempoffsetNotEmpty = "TempoffsetNotEmpty"
                , RebootFailed = "RebootFailed"

            #region Live
, LiveSessionAddSuccessful = "Live.Session.Add.Successful"
                , LiveSessionAddFailure = "Live.Session.Add.Failure"
                , LiveSessionUpdateSuccessful = "Live.Session.Update.Successful"
                , LiveSessionUpdateFailure = "Live.Session.Update.Failure"
                , LiveSessionSesssionSetupFormTitleDefault = "Live.Session.SesssionSetupForm.Title.Default"
                ;
            #endregion

        }

        /// <summary>
        /// Recource key of images constance class
        /// </summary>
        public abstract class Images
        {
            public const string
                Welcome = "about1_modify"
                , Splash = "Splash"
                , About = "about"
                , Help = "help"
                , TransLuxLog = "Translux"
                , PWLogoG = "PWLogoG"
                , PWLogoR = "PWLogoR"
                , PWLogoY = "PWLogoY"
                , PW_LogoG16 = "PW_Logo16"
                , PW_LogoR16 = "PW_Logor16"
                , PW_LogoY16 = "PW_Logoy16"
                , Stop = "stop"
                , PlaySign = "playsign"
                , Import = "Import32"
                , Import16 = "Import16"
                , Export = "Export32"
                , Export16 = "Export16"
                , TimeZone = "TimeZone"
                , Cancel = "Cancel"
                , Cancel16 = "Cancel16"
                , ConnectingProgress = "ConnectingProgress"
                , Pass = "pass"
                , Baffle = "baffle"
                , CurrentContent = "CurrentContent"
                , AddToGroup = "AddToGroup"
                , BringToFront = "BringToFront"
                , CancelBackground = "CancelBackground"
                , CloseShowAllLayers = "CloseShowAllLayers"
                //, Export = "export"
                , FitToSign = "FitToSign"
                , GeneraleNailImage = "GeneraleNailImage"
                //, Import = "import"
                , Rename = "rename"
                , SendToBack = "SendToBack"
                , SetBackground = "SetBackground"
                , ShowAllLayers = "ShowAllLayers"
                , SnapAllLayers = "SnapAllLayers"
                , GoLive = "GoLive"
                , GoLive16 = "GoLive16"

                , Exit = "Exit"
                , Exit16 = "Exit16"
                , Open16 = "OpenFile"
                , New = "New"
                , New16 = "New16"
                , NewSign = "DashboardIcon 32x32"
                , NewSign16 = "DashboardIcon 16x16"
                , NewSignGroup = "DashboardGroupIcon 32x32"
                , NewSignGroup16 = "DashboardGroupIcon 16x16"
                , NewMessage = "MessageIcon 32x32"
                , NewMessage16 = "NewMessage16"
                , NewPlaylist = "PlaylistIcon 32x32"
                , NewPlaylist16 = "NewPlaylist16"
                , NewLibrary = "LibraryIcon 32x32"
                , NewLibrary16 = "LibraryIcon 16x16"
                , NewSchedule = "ScheduleIcon 32x32"
                , NewSchedule16 = "NewSchedule16"

                , Insert = "Insert"
                , Insert16 = "InsertNew16"
                , Insert32 = "InsertNew32"
                , InsertSignPhoto = "InsertSignPhoto"
                , InsertSignPhoto16 = "InsertSignPhoto16"

                , Connect = "Connect"
                , Connect16 = "Connect16"
                , Disconnect = "Disconnect"
                , Disconnect16 = "Disconnect16"
                , Properties = "Properties"
                , Properties16 = "Properties16"

                , Display = "Display"
                , Display16 = "Display16"
                , BlankSign = "BlankSign"
                , BlankSign16 = "BlankSign16"
                , TestPattern = "TestPattern"
                , TestPattern16 = "TestPattern16"
                , DisplayMessage = "DisplayMessage"
                , DisplayMessage16 = "DisplayMessage16"

                , CXCInit16 = "CXCInit16"
                , CXCInit = "CXCInit32"

                , Setup16 = "Setup16"
                , Setup = "Setup"

                , Delete = "Delete"
                , Delete16 = "Delete16"

                , GreenStatus = "GreenStatus"
                , RedStatus = "RedStatus"
                , YellowStatus = "YellowStatus"

                , Dimming = "Dimming"
                , Dimming16 = "Dimming16"
                , Temp = "Temp"
                , Temp16 = "Temp16"
                , Time = "Time"
                , Time16 = "Time16"
                , ViewLogs = "ViewLogs"
                , ViewLogs16 = "ViewLogs16"

                , LiveView = "LiveView"
                , LiveView16 = "LiveView16"
                , SignPhotoView = "SignPhotoView"
                , SignPhotoView16 = "SignPhotoView16"
                , RefreshView = "RefreshView"
                , RefreshView16 = "RefreshView16"

                , ClearCXCLog = "deletelog32"
                , ClearCXCLog16 = "deletelog16"

                , Save = "Save"
                , Save16 = "Save16"
                , SaveAs = "SaveAs"
                , SaveAs16 = "SaveAs16"
                , BatchLoad = "BatchLoad"
                , BatchLoad16 = "BatchLoad16"

                , Copy = "Copy"
                , Copy16 = "Copy16"
                , Paste = "Paste"
                , Paste16 = "Paste16"
                , Undo = "Undo"
                , Undo16 = "Undo16"
                , Redo = "Redo"
                , Redo16 = "Redo16"

                , InsertImage = "InsertImage"
                , InsertImage16 = "InsertImage16"
                , InsertVideo = "InsertVideo"
                , InsertVideo16 = "InsertVideo16"
                , InsertTextbox = "InsertTextbox"
                , InsertTextbox16 = "InsertTextbox16"
                , Replaceables = "Replaceables"
                , Replaceables16 = "Replaceables16"
                , Other = "Other"
                , Other16 = "Other16"

                , PlayEffect16 = "PlayEffect16"
                , PlayEffect = "PlayEffect32"
                , EnterEffect16 = "EnterEffect16"
                , EnterEffect = "EnterEffect32"
                , ExitEffect16 = "ExitEffect16"
                , ExitEffect = "ExitEffect32"

                , Drawing = "Drawing"
                , Drawing16 = "Drawing16"
                , PointerTool16 = "PointerTool16"
                , Rectangle = "Rectangle"
                , Rectangle16 = "Rectangle16"
                , Ellipse = "Ellipse"
                , Ellipse16 = "Ellipse16"
                , ArrowUp = "ArrowUp"
                , ArrowUp16 = "ArrowUp16"
                , ArrowDown = "ArrowDown"
                , ArrowDown16 = "ArrowDown16"
                , ArrowLeft = "ArrowLeft"
                , ArrowLeft16 = "ArrowLeft16"
                , ArrowRight = "ArrowRight"
                , ArrowRight16 = "ArrowRight16"

                , FillPaintCan = "PaintFill32"
                , FillPaintCan16 = "PaintFill16"

                , LineColor = "LineColor"
                , LineColor16 = "Line_Color16"
                , LineThickness = "Line_Thickness"
                , LineThickness16 = "Line_Thickness16"
                , Pen = "Pen"
                , Pen16 = "Pen16"
                , Eraser = "Eraser"
                , Eraser16 = "Eraser16"

                , SendTo = "SendTo"
                , SendTo16 = "SendTo16"
                , SendInEditor = "EditorAddToIcon 32x32"
                , SendInPlaylist = "PlaylistAddToIcon 32x32"
                , SendInScheduler = "SchedulerUpload 32x32"
                , LiveStorage = "LiveStorage"
                , LiveStorage16 = "LiveStorage16"
                , Sign = "Sign"
                , Sign16 = "Sign16"
                , Playlist = "Playlist"
                , Playlist16 = "Playlist16"
                , Schedule = "Schedule"
                , Schedule16 = "Schedule16"

                , TextBackColor = "BackColor"
                , TextFontBold = "FontBold"
                , TextFontItalic = "FontItalic"
                , TextFontColor = "ForeColor"
                , TextJustifyCenter = "JustifyCenter"
                , TextJustifyLeft = "JustifyLeft"
                , TextJustifyRight = "JustifyRight"
                , FontFrameFixed16 = "FontFrameFixed16"
                , FontSizeFixed16 = "FontSizeFixed16"
                , FrameFixed16 = "FrameFixed16"
                , FrameFixed32 = "FrameFixed32"
                , FrameFixedTrue16 = "FrameFixedTrue16"
                , BitMap16 = "BitMap16"
                , TrueType16 = "TrueType16"

                , Windows = "WindowsLarge"
                , Windows16 = "Windows"

                , InsertPlaylist = "InsertPlaylist"
                , InsertPlaylist16 = "InsertPlaylist16"
                , InsertMessage = "InsertMessage"
                , InsertMessage16 = "InsertMessage16"
                , InsertTimeSliceGroup = "InsertTimeSliceGroup"
                , InsertTimeSliceGroup16 = "InsertTimeSliceGroup16"
                , Default = "Default"

                , Edit = "Edit"
                , Edit16 = "Edit16"

                , Init = "Init"
                , Init16 = "Init16"

                , Pause = "Pause"
                , Pause16 = "Pause16"
                , Play = "Play"
                , Play16 = "Play16"
                , PlayNext = "PlayNext"
                , PlayPrevious = "PlayPrevious"

                , RecycleClose = "RecycleClose_png"
                , RecycleClose16 = "RecycleClose16"

                , RecycleOpen = "RecycleOpen_png"
                , RecycleOpen16 = "RecycleOpen16"

                , Reboot = "Reboot"

                , TextLayer = "TextLayer"
                , TextLayer16 = "TextLayer16"

                , Tools = "Tools"
                , Tools16 = "Tools16"
                , Video = "Video"
                , Video16 = "Video16"
                , VisiableLayer = "Eye30_25"
                , VisiableLayer16 = "Eye30_25"
                , ScrollText16 = "ScrollText16"
                , ScrollText = "ScrollText32"

                , ZoomIn = "ZoomIn"
                , ZoomIn16 = "ZoomIn16"
                , ZoomOut = "ZoomOut"
                , ZoomOut16 = "ZoomOut16"
                , ZoomInBar = "ZoomInBar"
                , ZoomOutBar = "ZoomOutBar"

                , Image30 = "Image30_25"
                , shape30 = "shape30_25"
                , Temp30 = "Temp30_25"
                , Time30 = "Time30_25"
                , Video30 = "Video30_25"
                , ScrollText30 = "ScrollText30_25"
                , Viable30 = "Viable30_25"
                , Text30 = "Text30_25"

                , Image16 = "Image16"
                , Line16 = "line16"
                , Shape16 = "ShapeLayer16"

                , PlayNowIcon32 = "PlayNowIcon_32"
                , Play2Normal = "Play3Normal"
                , Play2Hover = "Play3Hover"
                , Play2Push = "Play3Push"
                , Play2Disable = "Play3Disable"
                , PlayNormal = "PlayNormal"
                , PlayHover = "PlayHover"
                , PlayPush = "PlayPush"
                , PlayDisable = "PlayDisable"
                , PauseDisable = "PauseDisable"
                , PauseHover = "PauseHover"
                , PauseNormal = "PauseNormal"
                , PausePush = "PausePush"
                , StopNormal = "StopNormal"
                , StopHover = "StopHover"
                , StopPush = "StopPush"
                , StopDisable = "StopDisable"
                , PreviousNormal = "PreviousNormal"
                , PreviousHover = "PreviousHover"
                , PreviousPush = "PreviousPush"
                , PreviousDisable = "PreviousDisable"
                , NextNormal = "NextNormal"
                , NextHover = "NextHover"
                , NextPush = "NextPush"
                , NextDisable = "NextDisable"
                , PlayBar_01 = "PlayBar_01"
                , PlayBarBackground = "PlayBarBackground"
                , PlayBarBackground_01 = "PlayBarBackground_01"
                , PlayBarBackground_02 = "PlayBarBackground_02"
                , AddNewLayer = "NewLayer16"
                , DashboardIcon16x16 = "DashboardIcon16x16"
                , MessageIcon16x16 = "MessageIcon16x16"
                , PlaylistIcon16x16 = "Playlist Icon 16x16"
                , SchedulerIcon16x16 = "SchedulerIcon16x16"
                , SignImageDefault = "SignImageDefault"

                , SignGroup = "DashboardGroupIcon 16x16"
                , TabPageDashBoard = "DashboardIcon 16x16"
                , TabPageEditor = "Edit16"
                , TabPagePlaylist = "Playlist16"
                , TabPageScheuler = "Schedule16"
                , TabPageManager = "Manager16"
                , TabPageLive = "live16"
                , Live = "Live32"
                , Live16 = "Live16"
                , SystemDefault = "SystemDefault32"
                , SystemDefault16 = "SystemDefault16"
                , UserManager = "UserManager32"
                , UserManager16 = "UserManager16"
                , ProWriteInit = "ProWriteInit32"
                , ProWriteInit16 = "ProWriteInit16"
                , Manager16 = "Manager16"
                , Manager = "Manager32"
                , SignConnect = "SignConnect161"
                , SignConnectNew = "DashboardConnectIcon 16x16"
                , DeleteEmphasisEffect = "DeleteEmphasisEffect"
                , DeleteEntryEffect = "DeleteEntryEffect"
                , DeleteExitEffect = "DeleteExitEffect"
                , MoveLayerBackwards = "MoveLayerBackwards"
                , MoveLayerForward = "MoveLayerForward"
                , Removefromthisgroup = "Removefromthisgroup"
                , SetEmphasisEffect = "SetEmphasisEffect"
                , SetentryEffect = "SetentryEffect"
                , SetExitEffect = "SetExitEffect"

                , Xiangji16 = "xingji16"
                , Xiangji32 = "xingji32"
                ;
        }

        /// <summary>
        /// Recource key of icons constance class
        /// </summary>
        public abstract class Icons
        {
            public const string
                TrayIcon = "PWLogoG1"
                , Default = "Default1"
                , PW_LogoG16icon = "PW_LogoG16"
                , PW_LogoR16icon = "PW_LogoR161"
                , PW_LogoY16icon = "PW_LogoY161"
                , Message = "Message"
                , Playlist = "Playlist1"
                , Schedule = "Schedule1"
                , Sign = "Sign1"
                , SignGroup = "SignGroup"
                , Library = "Library"
                , Layer = "Layer"
                 , Bijou = "bijou"
                , Blackhole = "blackhole"
                , Bounce = "bounce"
                , Coalesce = "coalesce"
                , Fade = "fade"
                , Filter = "filter"
                , Flash = "flash"
                , Green = "green"
                , Interleave = "interleave"
                , Line = "line"
                , Multiwipe = "multiwipe"
                , Questionmark = "questionmark"
                , Radar = "radar"
                , Rain = "rain"
                , Red = "red"
                , Rss = "rss"
                , Slot = "slot"
                , Snow = "snow"
                , Slide = "Slide"
                , Sparkle = "sparkle"
                , Venitian = "venitian"
                , Wipe = "wipe"
                , Wraparound = "wraparound"
                , Yellow = "yellow"
                ;
        }

        public abstract class Helps
        {
            public const string
                HelpFileName = "~HelpFileName"
                , HelpFileNameRelease = "~HelpFileNameRelease"
                , About = "About"
                , DashboardNew = "Dashboard.New"
                , CurrentSign = "CurrentSign"
                , QuickStart = "QuickStart"
                , Dashboard = "Dashboard"
                , DashboardDisplay = "Dashboard.Display"
                , DashboardSignImage = "Dashboard.SignImage"
                , DashboardSignStatus = "Dashboard.SignStatus"
                , DashboardSignList = "Dashboard.SignList"
                , DashboardModify = "Dashboard.Modify"
                , DashboardConnect = "Dashboard.Connect"
                , DashboardMonitor = "Dashboard.Monitor"
                , DashboardTools = "Dashboard.Tools"
                , DashboardAddSign = "Dashboard.AddSign"
                , DashboardSettingDefault = "Dashboard.SettingDefault"
                , DashboardUserLogin = "Dashboard.UserLogin"
                , DashboardCurrentClip = "Dashboard.CurrentClip"
                , DashboardInit = "Dashboard.Init"
                , DashboardSetup = "Dashboard.Setup"
                , DashboardUserManager = "Dashboard.UserManager"
                , DashboardLiveView = "Dashboard.LiveView"
                , DashboardSign = "Dashboard.Sign"
                , DashboardSystemDefault = "Dashboard.SystemDefault"
                , Editor = "Editor"
                , EditorNew = "Editor.New"
                , EditorOpen = "Editor.Open"
                , EditorEffect = "Editor.Effect"
                , EditorToolBox = "Editor.ToolBox"
                , EditorLibrary = "Editor.Library"
                , EditorMessage = "Editor.Message"
                , EditorProperty = "Editor.Property"
                , EditorContent = "Editor.Content"
                , EditorFiles = "Editor.Files"
                , EditorPaint = "Editor.Paint"
                , EditorSign = "Editor.Sign"
                , EditorTextFont = "Editor.TextFont"
                , EditorWindows = "Editor.Windows"
                , Playlist = "Playlists"
                , PlaylistNew = "Playlist.New"
                , PlaylistOpen = "Playlist.Open"
                , PlaylistsPreview = "Playlists.Preview"
                , PlaylistsTimeSliceGroup = "Playlists.TimeSliceGroup"
                , PlaylistsPlayer = "Playlists.Player"
                , SchedulerCalendar = "Scheduler.Calendar"
                , PlaylistsContent = "Playlists.Content"
                , PlaylistsFiles = "Playlists.Files"
                , PlaylistsSign = "Playlists.Sign"
                , PlaylistsProperties = "Playlists.Properties"
                , SchedulerFiles = "Scheduler.Files"
                , SchedulerNew = "Scheduler.New"
                , SchedulerOpen = "Scheduler.Open"
                , SchedulerProperties = "Scheduler.Properties"
                , SchedulerSign = "Scheduler.Sign"
                , SchedulerContent = "Scheduler.Content"
                , Scheduler = "Scheduler"
                ;
        }

        /// <summary>
        /// get string by resource key
        /// </summary>
        /// <param name="resourceKey">resource key</param>
        /// <returns>resource string</returns>
        public static string GetHelpString(string resourceKey)
        {
            if (string.IsNullOrEmpty(resourceKey))
                return null;
            return _rmHelp.GetString(resourceKey, _culture);
        }

        /// <summary>
        /// get string by resource key
        /// </summary>
        /// <param name="resourceKey">resource key</param>
        /// <returns>resource string</returns>
        public static string GetString(string resourceKey)
        {
            if (string.IsNullOrEmpty(resourceKey))
                return null;
            return _rmString.GetString(resourceKey, _culture);
        }

        /// <summary>
        /// get formated string by resource key and format arguments
        /// </summary>
        /// <param name="resourceKey">resource key</param>
        /// <param name="args">formated arguments</param>
        /// <returns>formated string</returns>
        public static string GetFormatString(string resourceKey, params object[] args)
        {
            if (string.IsNullOrEmpty(resourceKey))
                return null;
            return string.Format(_rmString.GetString(resourceKey, _culture), args);
        }

        /// <summary>
        /// get or set culture info
        /// </summary>
        public static CultureInfo Culture
        {
            get
            {
                return _culture;
            }
            set
            {
                _culture = value;
            }
        }

        /// <summary>
        /// get image by resource key
        /// </summary>
        /// <param name="resourceKey">resource key</param>
        /// <returns>resource image, if doesn't find, return defalut image</returns>
        public static Image GetImage(string resourceKey)
        {
            if (string.IsNullOrEmpty(resourceKey))
                return _rmImage.GetObject("Default") as Image; ;

            Image ic = _rmImage.GetObject(resourceKey, _culture) as Image;
            if (ic != null)
                return ic;
            else
            {
                Image im = _rmImage.GetObject(resourceKey) as Image;
                if (im == null)
                    im = _rmImage.GetObject("Default") as Image;
                return im;
            }
        }

        /// <summary>
        /// get icon by resource key
        /// </summary>
        /// <param name="resourceKey">resource key</param>
        /// <returns>resource icon, if doesn't find, return defalut </returns>
        public static Icon GetIcon(string resourceKey)
        {
            Icon ic = _rmImage.GetObject(resourceKey, _culture) as Icon;
            if (ic == null)
                return ic;
            else
            {
                Icon im = _rmImage.GetObject(resourceKey) as Icon;
                if (im == null)
                    im = _rmImage.GetObject("Default1") as Icon;
                return im;
            }
        }

        public static bool CheckName(string name)
        {
            Regex RegName = new Regex(Resource.GetString(Resource.Strings.NameRegulation));
            Match m = RegName.Match(name);
            return m.Success;
        }

    }

}
