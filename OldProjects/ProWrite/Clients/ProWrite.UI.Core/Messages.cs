//---------------------------------------------------------------------
//
// File: Messages.cs
//
// Description:
// 该文件包含了一系列于系统消息相关的枚举和消息类
//
// Author: Kevin
// Modify History:
//      Jerry Xu 2008-6-20 Add message of PlayListsSavedMessage
//      Jerry Xu 2008-6-20 Add message of PlayListsUpdateMessageBtnControlsMessage
//      Jerry Xu 2008-6-20 Add message of PlayListsLibraryViewPlayListMessage
//      Jerry Xu 2008-6-20 Add message of PlayListsLibraryViewMessageMessage
//      Jerry Xu 2008-6-24 Change ZoomType reference from SysEnumType to Prowrite.Core.Entity
//      Jerry Xu 2008-6-25 Add message of PlayListsUpdateDragDropLayoutControlPositionMessage
//      Jerry Xu 2008-6-25 Add message of PlayListsDelete
//      Jerry Xu 2008-6-26 The message of PlayListsShowPropertyMessage ,its parameter change to PlayListsInfo
//      Jerry Xu 2008-6-26 Delete the message of PlayListsUpdateTickAndUnitWidthMessage
//      Terry Li 2008-6-26 Modify ActiveChange class
//      Jerry Xu 2008-6-30 PlayListsUpdateMessageBtnControlsMessage's parameter and property type from Control[] to List<PlayListsInfo>
//      Jerry Xu 2008-6-30 PlayListsUpdateCurrentPositionLabelMessage add parameter:LabelSlideLeft
//      Jerry Xu 2008-7-2  Delete Message:PlayListsLibraryViewMessageMessage,PlayListsLibraryViewPlayListMessage
//      Jerry Xu 2008-8-12 Add FitToSign to enum MenuCommands
//      Jerry Xu 2008-11-05 Add message:LibraryRenameMessage
//      Jerry Xu 2009-3-20 Add new command:NewTimesliceGroup
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core;
using System.Windows.Forms;

namespace ProWrite.UI.Controls.Common.Messages
{
    /// <summary>
    /// 菜单命令枚举
    /// </summary>
    public enum MenuCommands
    {
        None = -2,
        Exit = -1,

        Connect = Commands.Login,
        DisConnect = Commands.Logoff,
        StatusReport = Commands.GetStatus,
        ChangePassword = Commands.ChangePassword,


        SendToSign = Commands.UploadFile,

        Dimming = Commands.Dimming,
        TempOffset = Commands.TempOffset,
        RebootCXC = Commands.RebootCXC,
        ResetTime = Commands.SetDateTime,
        TimeZone = Commands.TimeZone,
        //FactoryReset = Commands.FactoryReset,
        SkipMessage = Commands.SkipQueueMessage,
        ClearQMessage = Commands.ClearQueueMessage,
        StartRender = Commands.StartRender,
        StopRender = Commands.StopRender,
        BlankSign = Commands.BlankSign,
        TestPattern = Commands.TestPattern,
        LiveImage = Commands.LiveImage,
        RefreshCurrentClip = Commands.RefreshCurrentClip,
        LoadScheduler = Commands.LoadScheduler,
        GoLive =Commands.GoLive,

        //Import and export
        Import = ResetTime + 1,
        ImportMessage,
        ImportTimesliceGroup,
        ImportPlaylist,
        ImportScheduler,

        Export,
        ExportMessage,
        ExportTimeSliceGroup,
        ExportPlaylist,
        ExportScheduler,


        
        Undo,
        Redo,
        Copy,
        Paste,
        Properties,

        New,
        NewSign,
        NewSignGroup,
        NewMessage,
        NewPlaylist,
        NewTimesliceGroup,
        NewScheduler,
        NewLibraryGroup,

        Open,
        OpenMessage,
        OpenPlaylist,
        OpenScheduler,
        OpenLibrary,
        OpenLibraryFile,
        Save,
        SaveAs,
        Delete,

        Insert,
        InsertMessage,
        InsertTimeSlice,
        InsertPlaylist,

        SendToInEditor,
        SendToInPlaylist,
        SendToInScheduler,
        SendToLiveStorage,
        SendToPlaylist,
        SendToScheduler,

        DashboardEdit,
        BatchLoad,


        Pointer,
        Drawing,
        Line,
        Rectangle,
        Ellipse,
        ArrowUp,
        ArrowDown,
        ArrowRight,
        ArrowLeft,
        Image,
        Video,
        Text,
        DynamicText,
        DynamicVideo,
        Time,
        Temperature,

        LineDash,
        LineColor,
        LineThickness,
        ColorFill,

        TextFont,
        TextFontSize,
        TextFontColor,
        TextBackgroundColor,
        TextBold,
        TextItalic,
        TextAlignLeft,
        TextAlignCenter,
        TextAlignRight,
        TextFrameFixed,
        TextFontSizeFixed,
        TextKern,
        TextLead,
        TextEffect,

        ZoomIn,
        ZoomOut,
        UnBlankSign,

        CancelConnect,

        
        //UpdateLiveView = Commands.RefreshSignImage,


        PropertySet ,
        SendMessageOrPlaylistToSign,
        SendPlayListToSign,
        UserManager,
        InitSystem,

        LogView,

        //Live

        SessionSetup,
        Sync,
    }
   
}