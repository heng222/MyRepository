//---------------------------------------------------------------------
//
// File: Enums.cs
//
// Description:
// 
//
// Author: 
//
// Modify history:
//      Kevin    2008-6-25 把MessageTab.cs 文件 中的EditStatus枚举存放到Enums文件中
//      Kevin    2008-6-25 把Layer.cs 文件 中的PeriodOfTimeType枚举存放到Enums文件中
//      Kevin    2008-6-25 把UndoManager.cs 文件 中的UndoActionKind枚举存放到Enums文件中
//      Kevin    2008-6-25 把ShapeFigure.cs 文件 中的ShapeKind枚举存放到Enums文件中
//      Kevin    2008-6-25 把ShapeLine.cs 文件 中的LineDirection枚举存放到Enums文件中
//      Kevin    2008-6-25 把SysEnum.cs 文件 中的MessageActionType枚举存放到Enums文件中
//      Kevin    2008-6-25 把Enums.cs 文件 中的UndoActionKind枚举存放到UndoAction.cs文件中
//      Michael  2008-7-3  在Enums.cs 文件 中的增加了Align和Valign两个枚举变量
//      Jerry Xu 2008-8-11 Add enum OutLineShadow
//      Jerry Xu 2008-8-12 Add enum AutoFitType 
//      Jerry Xu 2009-2-13 Update enum LayerType
//      Jerry Xu 2009-7--3 Add enum:LiveLibraryType,QueueAlertLevel
//      Jerry Xu 2009-7-14 Add enum:QueueAlertLevel,LiveMessageState,ProWriteKeys,MediaControlType,QueueControlType
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.Drawing.Design;


namespace ProWrite.Core
{
    /// <summary>
    /// Command constance class
    /// </summary>
    public enum Commands
    {
        None = -2,
        Heart = 0,
        GetSignInfo = 1,
        Disconnect = 2,

        Login = 2000 + 1,
        ChangePassword = Login + 1,
        CreateUser = ChangePassword + 1,
        DeleteUser = CreateUser + 1,
        GetUserList = DeleteUser + 1,
        UpdateUserRole = GetUserList + 1,
        Logoff = UpdateUserRole + 1,

        GetLock = 3000 + 1,
        FreeLock = GetLock + 1,
        CreateMessageDir = FreeLock + 1,
        UploadFile = CreateMessageDir + 1,
        UploadFileCompleted = UploadFile + 1,
        UploadFileExeption = UploadFileCompleted + 1,
        DownloadFile = UploadFileExeption + 1,
        DownloadFileCompleted = DownloadFile + 1,
        DeleteFile = DownloadFileCompleted + 1,
        GetFileList = DeleteFile + 1,

        GetLog = 4000 + 1,
        ClearLog = GetLog + 1,

        GetStatus = 1000 + 1,
        Play = GetStatus + 1,//
        SkipQueueMessage = Play + 1,//
        ClearQueueMessage = SkipQueueMessage + 1,//
        StartRender = ClearQueueMessage + 1,//
        StopRender = StartRender + 1,//
        LoadScheduler = StopRender + 1,
        Diagnostics = LoadScheduler + 1,//delete
        BlankSign = Diagnostics + 1,
        TestPattern = BlankSign + 1,
        Dimming = TestPattern + 1,
        TempOffset = Dimming + 1,
        PlayCompleted = TempOffset + 1,//
        LiveImage = PlayCompleted + 1,
        RefreshCurrentClip = LiveImage + 1,//del
        TimeZone = RefreshCurrentClip + 1,//

        GetLiveState = TimeZone + 1,//del
        GoLive = GetLiveState + 1,//
        GetQueueList = GoLive + 1,//del
        QueueList = GetQueueList + 1,//del
        GetRendererState = QueueList + 1,//
        GetHealthStatus = GetRendererState + 1,
        GetConnectionType = GetHealthStatus + 1,//
        GetSerialInfo = GetConnectionType + 1,//
        DataSourceManager = GetSerialInfo + 1,//
        DataPassThrough = DataSourceManager + 1,//
        GetDBSourceData = DataPassThrough + 1,//
        EnableDBSource = GetDBSourceData + 1,//

        RebootCXC = 5000 + 1,
        SetDateTime = RebootCXC + 1,

    }
    /// <summary>
    /// Time:2008-5-25
    /// Author:Jerry
    /// Function:Action Message Type
    /// Update:
    /// </summary>
    public enum MessageActionType : byte
    {
        Savesuccess = 1,
        SaveFailed = 2,
        MessageFileIsNotExist = 3,

        PlayListNameEmpty = 4,
        ConfirmDeletePlaylist = 5,
        PlayListMessageLengthEmpty = 6,
        PlayListPlayListLengthEmpty = 7,
        PlaylistSaveTotalLengthEmpty = 8,
        PlaylistSaveExit = 9,
        PlayListViewMessageFailure = 10,
        PlayListViewMessageException = 11,
        PlayListViewPlayListFailure = 12,
        PlayListViewPlayListException = 13,
    }

    public enum LineDirection
    {
        Slant,
        BackSlant,
        Horizontal,
        Vertical
    }

    #region Live enum
    public enum LiveType
    {
        None,
        LiveSign,
        LiveMessage,
        LiveCategory,
        HotButtonItem,
        HotButton,
        LiveSignProxy = HotButton * 2,
        LiveMessageProxy = LiveSignProxy * 2,
        LiveCategoryProxy = LiveMessageProxy * 2,
        HotButtonItemProxy = LiveCategoryProxy * 2,
        HotButtonProxy = HotButtonItemProxy * 2,
    }

    public enum LiveCategoryViewState
    {
        ListView,
        CardView
    }

    public enum QueueAlertLevel
    {
        Green,
        Yellow,
        Bottom,
    }

    public enum LiveMessageState
    {        
        Native,
        Server,
        Both,
    }

    public enum LiveCategoryDisplayState
    {
        Yes,
        No
    }
    
    public enum ProWriteKeys
    {
        // Summary:
        //     The bitmask to extract modifiers from a key value.
        Modifiers = -65536,
        //
        // Summary:
        //     No key pressed.
        None = 0,
        //
        // Summary:
        //     The left mouse button.
        LButton = 1,
        //
        // Summary:
        //     The right mouse button.
        RButton = 2,
        //
        // Summary:
        //     The CANCEL key.
        Cancel = 3,
        //
        // Summary:
        //     The middle mouse button (three-button mouse).
        MButton = 4,
        //
        // Summary:
        //     The first x mouse button (five-button mouse).
        XButton1 = 5,
        //
        // Summary:
        //     The second x mouse button (five-button mouse).
        XButton2 = 6,
        //
        // Summary:
        //     The BACKSPACE key.
        Back = 8,
        //
        // Summary:
        //     The TAB key.
        Tab = 9,
        //
        // Summary:
        //     The LINEFEED key.
        LineFeed = 10,
        //
        // Summary:
        //     The CLEAR key.
        Clear = 12,
        //
        // Summary:
        //     The ENTER key.
        Enter = 13,
        //
        // Summary:
        //     The RETURN key.
        Return = 13,
        //
        // Summary:
        //     The SHIFT key.
        ShiftKey = 16,
        //
        // Summary:
        //     The CTRL key.
        ControlKey = 17,
        //
        // Summary:
        //     The ALT key.
        Menu = 18,
        //
        // Summary:
        //     The PAUSE key.
        Pause = 19,
        //
        // Summary:
        //     The CAPS LOCK key.
        CapsLock = 20,
        //
        // Summary:
        //     The CAPS LOCK key.
        Capital = 20,
        //
        // Summary:
        //     The IME Kana mode key.
        KanaMode = 21,
        //
        // Summary:
        //     The IME Hanguel mode key. (maintained for compatibility; use HangulMode)
        HanguelMode = 21,
        //
        // Summary:
        //     The IME Hangul mode key.
        HangulMode = 21,
        //
        // Summary:
        //     The IME Junja mode key.
        JunjaMode = 23,
        //
        // Summary:
        //     The IME final mode key.
        FinalMode = 24,
        //
        // Summary:
        //     The IME Kanji mode key.
        KanjiMode = 25,
        //
        // Summary:
        //     The IME Hanja mode key.
        HanjaMode = 25,
        //
        // Summary:
        //     The ESC key.
        Escape = 27,
        //
        // Summary:
        //     The IME convert key.
        IMEConvert = 28,
        //
        // Summary:
        //     The IME nonconvert key.
        IMENonconvert = 29,
        //
        // Summary:
        //     The IME accept key. Obsolete, use System.Windows.Forms.Keys.IMEAccept instead.
        IMEAceept = 30,
        //
        // Summary:
        //     The IME accept key, replaces System.Windows.Forms.Keys.IMEAceept.
        IMEAccept = 30,
        //
        // Summary:
        //     The IME mode change key.
        IMEModeChange = 31,
        //
        // Summary:
        //     The SPACEBAR key.
        Space = 32,
        //
        // Summary:
        //     The PAGE UP key.
        Prior = 33,
        //
        // Summary:
        //     The PAGE UP key.
        PageUp = 33,
        //
        // Summary:
        //     The PAGE DOWN key.
        Next = 34,
        //
        // Summary:
        //     The PAGE DOWN key.
        PageDown = 34,
        //
        // Summary:
        //     The END key.
        End = 35,
        //
        // Summary:
        //     The HOME key.
        Home = 36,
        //
        // Summary:
        //     The LEFT ARROW key.
        Left = 37,
        //
        // Summary:
        //     The UP ARROW key.
        Up = 38,
        //
        // Summary:
        //     The RIGHT ARROW key.
        Right = 39,
        //
        // Summary:
        //     The DOWN ARROW key.
        Down = 40,
        //
        // Summary:
        //     The SELECT key.
        Select = 41,
        //
        // Summary:
        //     The PRINT key.
        Print = 42,
        //
        // Summary:
        //     The EXECUTE key.
        Execute = 43,
        //
        // Summary:
        //     The PRINT SCREEN key.
        PrintScreen = 44,
        //
        // Summary:
        //     The PRINT SCREEN key.
        Snapshot = 44,
        //
        // Summary:
        //     The INS key.
        Insert = 45,
        //
        // Summary:
        //     The DEL key.
        Delete = 46,
        //
        // Summary:
        //     The HELP key.
        Help = 47,
        //
        // Summary:
        //     The 0 key.
        D0 = 48,
        //
        // Summary:
        //     The 1 key.
        D1 = 49,
        //
        // Summary:
        //     The 2 key.
        D2 = 50,
        //
        // Summary:
        //     The 3 key.
        D3 = 51,
        //
        // Summary:
        //     The 4 key.
        D4 = 52,
        //
        // Summary:
        //     The 5 key.
        D5 = 53,
        //
        // Summary:
        //     The 6 key.
        D6 = 54,
        //
        // Summary:
        //     The 7 key.
        D7 = 55,
        //
        // Summary:
        //     The 8 key.
        D8 = 56,
        //
        // Summary:
        //     The 9 key.
        D9 = 57,
        //
        // Summary:
        //     The A key.
        A = 65,
        //
        // Summary:
        //     The B key.
        B = 66,
        //
        // Summary:
        //     The C key.
        C = 67,
        //
        // Summary:
        //     The D key.
        D = 68,
        //
        // Summary:
        //     The E key.
        E = 69,
        //
        // Summary:
        //     The F key.
        F = 70,
        //
        // Summary:
        //     The G key.
        G = 71,
        //
        // Summary:
        //     The H key.
        H = 72,
        //
        // Summary:
        //     The I key.
        I = 73,
        //
        // Summary:
        //     The J key.
        J = 74,
        //
        // Summary:
        //     The K key.
        K = 75,
        //
        // Summary:
        //     The L key.
        L = 76,
        //
        // Summary:
        //     The M key.
        M = 77,
        //
        // Summary:
        //     The N key.
        N = 78,
        //
        // Summary:
        //     The O key.
        O = 79,
        //
        // Summary:
        //     The P key.
        P = 80,
        //
        // Summary:
        //     The Q key.
        Q = 81,
        //
        // Summary:
        //     The R key.
        R = 82,
        //
        // Summary:
        //     The S key.
        S = 83,
        //
        // Summary:
        //     The T key.
        T = 84,
        //
        // Summary:
        //     The U key.
        U = 85,
        //
        // Summary:
        //     The V key.
        V = 86,
        //
        // Summary:
        //     The W key.
        W = 87,
        //
        // Summary:
        //     The X key.
        X = 88,
        //
        // Summary:
        //     The Y key.
        Y = 89,
        //
        // Summary:
        //     The Z key.
        Z = 90,
        //
        // Summary:
        //     The left Windows logo key (Microsoft Natural Keyboard).
        LWin = 91,
        //
        // Summary:
        //     The right Windows logo key (Microsoft Natural Keyboard).
        RWin = 92,
        //
        // Summary:
        //     The application key (Microsoft Natural Keyboard).
        Apps = 93,
        //
        // Summary:
        //     The computer sleep key.
        Sleep = 95,
        //
        // Summary:
        //     The 0 key on the numeric keypad.
        NumPad0 = 96,
        //
        // Summary:
        //     The 1 key on the numeric keypad.
        NumPad1 = 97,
        //
        // Summary:
        //     The 2 key on the numeric keypad.
        NumPad2 = 98,
        //
        // Summary:
        //     The 3 key on the numeric keypad.
        NumPad3 = 99,
        //
        // Summary:
        //     The 4 key on the numeric keypad.
        NumPad4 = 100,
        //
        // Summary:
        //     The 5 key on the numeric keypad.
        NumPad5 = 101,
        //
        // Summary:
        //     The 6 key on the numeric keypad.
        NumPad6 = 102,
        //
        // Summary:
        //     The 7 key on the numeric keypad.
        NumPad7 = 103,
        //
        // Summary:
        //     The 8 key on the numeric keypad.
        NumPad8 = 104,
        //
        // Summary:
        //     The 9 key on the numeric keypad.
        NumPad9 = 105,
        //
        // Summary:
        //     The multiply key.
        Multiply = 106,
        //
        // Summary:
        //     The add key.
        Add = 107,
        //
        // Summary:
        //     The separator key.
        Separator = 108,
        //
        // Summary:
        //     The subtract key.
        Subtract = 109,
        //
        // Summary:
        //     The decimal key.
        Decimal = 110,
        //
        // Summary:
        //     The divide key.
        Divide = 111,
        //
        // Summary:
        //     The F1 key.
        F1 = 112,
        //
        // Summary:
        //     The F2 key.
        F2 = 113,
        //
        // Summary:
        //     The F3 key.
        F3 = 114,
        //
        // Summary:
        //     The F4 key.
        F4 = 115,
        //
        // Summary:
        //     The F5 key.
        F5 = 116,
        //
        // Summary:
        //     The F6 key.
        F6 = 117,
        //
        // Summary:
        //     The F7 key.
        F7 = 118,
        //
        // Summary:
        //     The F8 key.
        F8 = 119,
        //
        // Summary:
        //     The F9 key.
        F9 = 120,
        //
        // Summary:
        //     The F10 key.
        F10 = 121,
        //
        // Summary:
        //     The F11 key.
        F11 = 122,
        //
        // Summary:
        //     The F12 key.
        F12 = 123,
        //
        // Summary:
        //     The F13 key.
        F13 = 124,
        //
        // Summary:
        //     The F14 key.
        F14 = 125,
        //
        // Summary:
        //     The F15 key.
        F15 = 126,
        //
        // Summary:
        //     The F16 key.
        F16 = 127,
        //
        // Summary:
        //     The F17 key.
        F17 = 128,
        //
        // Summary:
        //     The F18 key.
        F18 = 129,
        //
        // Summary:
        //     The F19 key.
        F19 = 130,
        //
        // Summary:
        //     The F20 key.
        F20 = 131,
        //
        // Summary:
        //     The F21 key.
        F21 = 132,
        //
        // Summary:
        //     The F22 key.
        F22 = 133,
        //
        // Summary:
        //     The F23 key.
        F23 = 134,
        //
        // Summary:
        //     The F24 key.
        F24 = 135,
        //
        // Summary:
        //     The NUM LOCK key.
        NumLock = 144,
        //
        // Summary:
        //     The SCROLL LOCK key.
        Scroll = 145,
        //
        // Summary:
        //     The left SHIFT key.
        LShiftKey = 160,
        //
        // Summary:
        //     The right SHIFT key.
        RShiftKey = 161,
        //
        // Summary:
        //     The left CTRL key.
        LControlKey = 162,
        //
        // Summary:
        //     The right CTRL key.
        RControlKey = 163,
        //
        // Summary:
        //     The left ALT key.
        LMenu = 164,
        //
        // Summary:
        //     The right ALT key.
        RMenu = 165,
        //
        // Summary:
        //     The browser back key (Windows 2000 or later).
        BrowserBack = 166,
        //
        // Summary:
        //     The browser forward key (Windows 2000 or later).
        BrowserForward = 167,
        //
        // Summary:
        //     The browser refresh key (Windows 2000 or later).
        BrowserRefresh = 168,
        //
        // Summary:
        //     The browser stop key (Windows 2000 or later).
        BrowserStop = 169,
        //
        // Summary:
        //     The browser search key (Windows 2000 or later).
        BrowserSearch = 170,
        //
        // Summary:
        //     The browser favorites key (Windows 2000 or later).
        BrowserFavorites = 171,
        //
        // Summary:
        //     The browser home key (Windows 2000 or later).
        BrowserHome = 172,
        //
        // Summary:
        //     The volume mute key (Windows 2000 or later).
        VolumeMute = 173,
        //
        // Summary:
        //     The volume down key (Windows 2000 or later).
        VolumeDown = 174,
        //
        // Summary:
        //     The volume up key (Windows 2000 or later).
        VolumeUp = 175,
        //
        // Summary:
        //     The media next track key (Windows 2000 or later).
        MediaNextTrack = 176,
        //
        // Summary:
        //     The media previous track key (Windows 2000 or later).
        MediaPreviousTrack = 177,
        //
        // Summary:
        //     The media Stop key (Windows 2000 or later).
        MediaStop = 178,
        //
        // Summary:
        //     The media play pause key (Windows 2000 or later).
        MediaPlayPause = 179,
        //
        // Summary:
        //     The launch mail key (Windows 2000 or later).
        LaunchMail = 180,
        //
        // Summary:
        //     The select media key (Windows 2000 or later).
        SelectMedia = 181,
        //
        // Summary:
        //     The start application one key (Windows 2000 or later).
        LaunchApplication1 = 182,
        //
        // Summary:
        //     The start application two key (Windows 2000 or later).
        LaunchApplication2 = 183,
        //
        // Summary:
        //     The OEM 1 key.
        Oem1 = 186,
        //
        // Summary:
        //     The OEM Semicolon key on a US standard keyboard (Windows 2000 or later).
        OemSemicolon = 186,
        //
        // Summary:
        //     The OEM plus key on any country/region keyboard (Windows 2000 or later).
        Oemplus = 187,
        //
        // Summary:
        //     The OEM comma key on any country/region keyboard (Windows 2000 or later).
        Oemcomma = 188,
        //
        // Summary:
        //     The OEM minus key on any country/region keyboard (Windows 2000 or later).
        OemMinus = 189,
        //
        // Summary:
        //     The OEM period key on any country/region keyboard (Windows 2000 or later).
        OemPeriod = 190,
        //
        // Summary:
        //     The OEM question mark key on a US standard keyboard (Windows 2000 or later).
        OemQuestion = 191,
        //
        // Summary:
        //     The OEM 2 key.
        Oem2 = 191,
        //
        // Summary:
        //     The OEM tilde key on a US standard keyboard (Windows 2000 or later).
        Oemtilde = 192,
        //
        // Summary:
        //     The OEM 3 key.
        Oem3 = 192,
        //
        // Summary:
        //     The OEM 4 key.
        Oem4 = 219,
        //
        // Summary:
        //     The OEM open bracket key on a US standard keyboard (Windows 2000 or later).
        OemOpenBrackets = 219,
        //
        // Summary:
        //     The OEM pipe key on a US standard keyboard (Windows 2000 or later).
        OemPipe = 220,
        //
        // Summary:
        //     The OEM 5 key.
        Oem5 = 220,
        //
        // Summary:
        //     The OEM 6 key.
        Oem6 = 221,
        //
        // Summary:
        //     The OEM close bracket key on a US standard keyboard (Windows 2000 or later).
        OemCloseBrackets = 221,
        //
        // Summary:
        //     The OEM 7 key.
        Oem7 = 222,
        //
        // Summary:
        //     The OEM singled/double quote key on a US standard keyboard (Windows 2000
        //     or later).
        OemQuotes = 222,
        //
        // Summary:
        //     The OEM 8 key.
        Oem8 = 223,
        //
        // Summary:
        //     The OEM 102 key.
        Oem102 = 226,
        //
        // Summary:
        //     The OEM angle bracket or backslash key on the RT 102 key keyboard (Windows
        //     2000 or later).
        OemBackslash = 226,
        //
        // Summary:
        //     The PROCESS KEY key.
        ProcessKey = 229,
        //
        // Summary:
        //     Used to pass Unicode characters as if they were keystrokes. The Packet key
        //     value is the low word of a 32-bit virtual-key value used for non-keyboard
        //     input methods.
        Packet = 231,
        //
        // Summary:
        //     The ATTN key.
        Attn = 246,
        //
        // Summary:
        //     The CRSEL key.
        Crsel = 247,
        //
        // Summary:
        //     The EXSEL key.
        Exsel = 248,
        //
        // Summary:
        //     The ERASE EOF key.
        EraseEof = 249,
        //
        // Summary:
        //     The PLAY key.
        Play = 250,
        //
        // Summary:
        //     The ZOOM key.
        Zoom = 251,
        //
        // Summary:
        //     A constant reserved for future use.
        NoName = 252,
        //
        // Summary:
        //     The PA1 key.
        Pa1 = 253,
        //
        // Summary:
        //     The CLEAR key.
        OemClear = 254,
        //
        // Summary:
        //     The bitmask to extract a key code from a key value.
        KeyCode = 65535,
        //
        // Summary:
        //     The SHIFT modifier key.
        Shift = 65536,
        //
        // Summary:
        //     The CTRL modifier key.
        Control = 131072,
        //
        // Summary:
        //     The ALT modifier key.
        Alt = 262144,
    }

    public enum MediaControlType
    {
        PlayNow,
        PlayNext,
        PlayNormal,
        SendToAutoQueue
    }

    public enum QueueControlType
    {
        EjectMessage,
        ClearQueue,
        Pause,
        Resume,
        ClearAll,
        AutoQueueOn,
        AutoQueueOff
    }

    #endregion

    //public enum FigureType
    //{
    //    Rectangle,
    //    Ellipse,
    //    UpArrow,
    //    DownArrow,
    //    RightArrow,
    //    LeftArrow
    //}

    
    ///// <summary>
    ///// 2008-6-25, Kevin 迁移
    ///// </summary>
    //public enum EditStatus
    //{
    //    New,
    //    Open,
    //    Updated
    //}

    [Serializable]
    public enum DashboardType:sbyte
    {
        Sign,
        Group,
        DemoSign,
    }

    [Serializable]
    public enum SignType:sbyte
    {
        RGB,
        Red,
        Amber,
        Green,
        Blue,
        White,
        //BlueGreen,
        //RedGreen,
    }

   
    /// <summary>
    /// Library Type
    /// </summary>
    [Flags]
    public enum LibraryType : ushort 
    {
        None = 0,
        Image = 1,
		Video = 2,
		Message = 4,
		Playlist = 8,
		TimeSliceGroup = 16,
        //Template = 32,
        //Region = 64,
        MessageProxy = TimeSliceGroup * 2,
        PlaylistProxy = MessageProxy * 2,
        TimeSliceGroupProxy = PlaylistProxy * 2,
        ShowColor = TimeSliceGroupProxy * 2,
        Appointment = ShowColor * 2,
        Schedule = Appointment * 2,
        Region = Schedule * 2,
        MLPlaylist = Region * 2,
        MLPlaylistProxy = MLPlaylist * 2,
    }

    /// <summary>
    /// Live Library Type
    /// </summary>
    [Flags]
    public enum LiveLibraryType : ushort
    {
        None = 0,
        Message = LibraryType.Message,
        Playlist = LibraryType.Playlist,
        TimeSliceGroup = LibraryType.TimeSliceGroup,
        //ServerMessage,//FiltType.Message
        //ServerPlaylist,//FiltType.Playlist
        //ServerTimeSliceGroup,//FiltType.TimeSliceGroup
    }

    /// <summary>
    /// Time:2008-6-23
    /// Author:michael
    /// Function:Layer Type
    /// </summary>
    /// 
    public enum LayerType
    {
        /// <summary>
        /// Text layer
        /// </summary>
        Text =0,
        /// <summary>
        /// Paint layer
        /// </summary>
        Paint=1,
        /// <summary>
        /// Image layer
        /// </summary>
        Image =2,
        /// <summary>
        /// Video layer
        /// </summary>
        Video=3,
        //Marquee,
        //MaxStatic,
        DynamicText = 4,
        Time=5,
        Temp=6,
        DynamicVideo=7,
        //Visible,
        //Max,

        //2008-6-25 Kevin add Marquee,Flash
        
        //Flash,
    }

    /// <summary>
    /// Function: Layer container type
    /// Author  : Jerry Xu
    /// Date    : 2008-8-21
    /// </summary>
    [Flags]
    public enum LayerContainerType
    {
        /// <summary>
        /// Danymic layer container
        /// </summary>
        Danymic,
        /// <summary>
        /// Static layer container
        /// </summary>
        Static, 
    }

    /// <summary>
    /// Shape type enum
    /// </summary>
    [Serializable]
    public enum ShapeType
    {
        Default,
        Text,

        ShapeDraw,

        Line,
        Rectangle,
        Ellipse,
        UpArrow,
        DownArrow,
        RightArrow,
        LeftArrow,

        Image,
        Video,
        //Marquee,

        Temperature,
        Time,
        DynamicText,
        DynamicVideo,
    }
    
    /// <summary>
    /// Time:2008-6-23
    /// Author:michael
    /// Enum:Effect Type
    /// </summary>
    public enum EffectType
    {
        /// <summary>
        /// Entry effect
        /// </summary>
        Entry,
        /// <summary>
        /// Emphasis effect
        /// </summary>
        Emphasis,
        /// <summary>
        /// Exit effect
        /// </summary>
        Exit,
        /// <summary>
        /// None effect - TimeSpan
        /// </summary>
        None,
    }

    ///// <summary>
    ///// Period of time type enum
    ///// </summary>
    //public enum PeriodOfTimeType
    //{
    //    /// <summary>
    //    /// Time span type
    //    /// </summary>
    //    TimeSpan,
    //    /// <summary>
    //    /// 
    //    /// </summary>
    //    EntryEffect,
    //    /// <summary>
    //    /// 
    //    /// </summary>
    //    ExitEffect
    //}

    /// <summary>
    /// Time:2008-6-23
    /// Author:michael
    /// Function:Property Data Type
    /// </summary>
    public enum DataType
    {
        varchar,
        number,
        bit,
        dword
    }

    /// <summary>
    /// Time:2008-6-23
    /// Author:michael
    /// Function:Property Input Type
    /// </summary>
    public enum InputType
    {
        Input,
        Select
    }

    /// <summary>
    /// Time:2008-6-23
    /// Author:michael
    /// Function:视频播放状态
    /// </summary>
    public enum PlayState
    {
        Run,
        Stop,
        Pause,
        Next
    }

    /// <summary>
    /// Time:2008-6-23
    /// Author:michael
    /// Function:设置字幕滚动方式
    /// </summary>
    [Editor(Constance.Designers.Enum, typeof(UITypeEditor))]
    [TypeConverter(typeof(EnumTypeConverter))]
    public enum RollWay
    {
        [EnumDescription("None")]
        None = -1,
        [EnumDescription("→")]
        LeftToRight = 0,
        [EnumDescription("←")]
        RightToLeft = 180,
        [EnumDescription("↓")]
        TopToBottom = 90,
        [EnumDescription("↑")]
        BottomToTop = -90,
    }

    /// <summary>
    /// Time:2008-7-3
    /// Author:michael
    /// Function:设置字幕横对齐方式
    /// </summary>
    public enum Align
    {
        CENTER,
        LEFT,
        RIGHT
    }

    /// <summary>
    /// Time:2008-7-3
    /// Author:michael
    /// Function:设置字幕竖对齐方式
    /// </summary>
    public enum Valign
    {
        //CENTER,
        MIDDLE, 
        BOTTOM,
        TOP
    }

    /// <summary>
    /// Used to indicate the state of the class
    /// </summary>
    public enum ClassState
    {
        Constructed,
        FilesAdded,
        RenderSelected,
        GraphStarted,
        GraphCompleting,
        GraphCompleted,
        Cancelling,
        Cancelled
    }
    /// <summary>
    /// Time:2008-5-9
    /// Author:Jerry
    /// Function:Zoom Type of the PlayLists
    /// Update:
    /// </summary>
    public enum ZoomType
    {
        ZoomNone = -1,
        ZoomIn = 0,
        ZoomOut = 1,
    }

    /// <summary>
    /// Function: OutlineShadowType
    /// Author  : Jerry Xu
    /// Date    : 2008-8-11
    /// Update:
    /// </summary>
    public enum OutlineShadowType
    {
        NONE = 0,
        OUTLINE = 1,//outline rename to bubble by louis
        SHADED = 2,
        BubbleSurround = 3,
    }

    /// <summary>
    /// Function: AutoFitType
    /// Author  : Jerry Xu
    /// Date    : 2008-8-12
    /// Update:
    /// </summary>
    public enum AutoFitType
    {
        None = 0,
        BorderFitText = 1,
        TextFitBorder = 2,
    }

    /// <summary>
    /// Function: PaingType
    /// Author  : Jerry Xu
    /// Date    : 2008-8-12
    /// Update:
    /// </summary>
    public enum PaintActionType
    {
        None = 0,
        BorderFitText = 1,
        TextFitBorder = 2,   
        FontChange = 3,
        Shadow = 4,
        OutLine = 5,
        BubbleSurround = 6,
        FrameFontSizeStyle = 7,
    }


    public enum PWAppointmentType
    {
        Normal = 0,
        Pattern = 1,
        Occurrence = 2,
        ChangedOccurrence = 3,
        DeletedOccurrence = 4
    }

    public enum PWRecurrenceRange
    {
        NoEndDate = 0,
        OccurrenceCount = 1,
        EndByDate = 2
    }

    public enum PWRecurrenceType
    {
        Daily = 0,
        Weekly = 1,
        Monthly = 2,
        Yearly = 3,
        Minutely = 4,
        Hourly = 5,
    }

    public enum PWSchedulerViewType
    {
        Day=3,
        Week=1,
        Month=2,
    }

    #region FirstDayOfWeek
    public enum PWFirstDayOfWeek
    {
        System = 7,
        Sunday = DayOfWeek.Sunday,
        Monday = DayOfWeek.Monday,
        Tuesday = DayOfWeek.Tuesday,
        Wednesday = DayOfWeek.Wednesday,
        Thursday = DayOfWeek.Thursday,
        Friday = DayOfWeek.Friday,
        Saturday = DayOfWeek.Saturday
    }
    #endregion
    #region WeekDays
    
    public enum PWWeekDays
    {
        Sunday = 1,
        Monday = 2,
        Tuesday = 4,
        Wednesday = 8,
        Thursday = 16,
        Friday = 32,
        Saturday = 64,
        WeekendDays = Sunday | Saturday,
        WorkDays = Monday | Tuesday | Wednesday | Thursday | Friday,
        EveryDay = WeekendDays | WorkDays
    }
    #endregion
    #region WeekOfMonth
    public enum PWWeekOfMonth
    {
        None = 0,
        First = 1,
        Second = 2,
        Third = 3,
        Fourth = 4,
        Last = 5
    }
    #endregion

    public enum CompareOp
    {
        Equal,
        NotEqual,
        GreaterThan,
        GreaterOrEqual,
        LessThan,
        LessOrEqual,
    }

    public enum QueueType
    {
        Normal,
        Hot,
        RedHot,
    }

    /// <summary>
    /// Live queue mouse right menu action type
    /// </summary>
    public enum QueueMouseRightMenuType
    {
        Delete,
        Clear,

        Start,
        Stop,

        MoveForward,
        MoveBackward,
        PlayNow,
        SetNextToPlay,
    }

    /// <summary>
    /// File exist type
    /// </summary>
    public enum FileExistType
    {
        Yes,
        No,
        SizeNoEqual //exist but size no equal
    }

    /// <summary>
    /// Library exist type
    /// </summary>
    public enum ExistType
    {
        Yes,
        No,
        NeededUpdate, //exist but size no equal

    }

    //public enum FileType
    //{
    //    Text_SVG,
    //    Paint_SVG,
    //    Image,
    //    Image_Meta,
    //    Video,
    //    Video_Meta,
    //    Message,
    //    TimesliceGroup,
    //    Playlist,
    //    Schedule,
    //    TemplateMessage,
    //    Log,
    //}

    /// <summary>
    /// 
    /// </summary>
    [Editor(Constance.Designers.Enum, typeof(UITypeEditor))]
    [TypeConverter(typeof(EnumTypeConverter))]
    public enum TimeFormat
    {
        [EnumDescription("12 hour time w AM/PM")]
        Twelve_hour_time_w_AMPM=1,
        [EnumDescription("12 hour time w/o AM/PM")]
        Twelve_hour_time_w_o_AMPM = 2,
        [EnumDescription("24 hour time")]
        Twenty_Four_Hour_Time = 3,
        [EnumDescription("12 hour time w seconds")]
        Twelve_hour_time_w_seconds = 4,
        [EnumDescription("24 hour time w seconds")]
        Twenty_Four_hour_time_w_seconds = 5,
        [EnumDescription("Date (US)")]
        Date_US = 6,
        [EnumDescription("Date (US) Full Yr")]
        Date_US_Full_Yr = 7,
        [EnumDescription("Date (Intl-1)")]
        DateIntl_1 = 8,
        [EnumDescription("Date (Intl-1) Full Yr")]
        DateIntl_1FullYr = 9,
        [EnumDescription("Date (Intl-2)")]
        DateIntl_2= 10,
        [EnumDescription("Date (Intl-2) Full Yr")]
        DateIntl_2FullYr = 11,
        [EnumDescription("Day of Week")]
        Day_of_Week = 12,
        [EnumDescription("Day of Week (Abbr)")]
        Day_of_Week_Abbr = 13,
        [EnumDescription("Month")]
        Month = 14,
        [EnumDescription("Month (Abbr)")]
        Month_Abbr = 15,
        [EnumDescription("Day of Month")]
        Day_of_Month = 16,
        [EnumDescription("Month of Year")]
        Month_of_Year = 17,
        [EnumDescription("Year")]
        Year = 18,
        [EnumDescription("Year (short)")]
        Year_short = 19,
        [EnumDescription("Hours (12 hour)")]
        Hours_12hour = 20,
        [EnumDescription("Hours (24 hour)")]
        Hours_24hour = 21,
        [EnumDescription("Minutes")]
        Minutes = 22,
        [EnumDescription("Seconds")]
        Seconds = 23,

    }

    public enum TempFormat
    {
        [EnumDescription("Farenheit")]
        Farenheit = 0,
        [EnumDescription("Farenheit w degree")]
        Farenheit_w_degree = 1,
        [EnumDescription("Farenheit w degree and F")]
        Farenheit_w_degree_and_F = 2,
        [EnumDescription("Celsius")]
        Celsius = 3,
        [EnumDescription("Celsius w degree")]
        Celsius_w_degree = 4,
        [EnumDescription("Celsius w degree and C")]
        Celsius_w_degree_and_C = 5,
    }

    public enum NumberType
    {
        Decimal,
        Hex
    }

    public enum PictureBoxSizeType
    {
        // Summary:
        //     The image is placed in the upper-left corner of the System.Windows.Forms.PictureBox.
        //     The image is clipped if it is larger than the System.Windows.Forms.PictureBox
        //     it is contained in.
        //Normal = 0,
        
        //
        // Summary:
        //     The image within the System.Windows.Forms.PictureBox is stretched or shrunk
        //     to fit the size of the System.Windows.Forms.PictureBox.
        StretchImage = 1,
        
        //
        // Summary:
        //     The System.Windows.Forms.PictureBox is sized equal to the size of the image
        //     that it contains.
        //AutoSize = 2,
        
        //
        // Summary:
        //     The image is displayed in the center if the System.Windows.Forms.PictureBox
        //     is larger than the image. If the image is larger than the System.Windows.Forms.PictureBox,
        //     the picture is placed in the center of the System.Windows.Forms.PictureBox
        //     and the outside edges are clipped.
        CenterImage = 3,
        
        //
        // Summary:
        //     The size of the image is increased or decreased maintaining the size ratio.
        Zoom = 4,
    }

    public enum LibraryState
    {
        None,
        Lock =1,
        Referrence=2,
    }
}
