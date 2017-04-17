//---------------------------------------------------------------------
//
// File: PlaylistInfo.cs
//
// Description:
// Entity of Playlist 
//
// Author: Jerry Xu
//
// Date:2008-6-18
//
// Modify History:
//      Jerry Xu 2008-6-26 Add the property of PlayListsName
//      Jerry Xu 2008-6-26 Change Length to LengthText,Add LengthValue,change their references
//      Jerry Xu 2008-6-30 Add fields:LengthPixel and Zoom
//      Jerry Xu 2008-6-30 modify field type:SID(string->int),PlayListsID(string->int),LibraryID(string->int),
//          Type(string->LibraryType),ImageIndex(string->int),Order(string->int)
//      Jerry Xu 2008-7-7  PlayListsInfo inherit from MemoryLibraryItem
//      Jerry Xu 2008-7-7  Rename PlaylistsInfo to PlaylistInfo
//      Jerry Xu 2008-7-7  Add the property of Items,its type is linked list of MessageInfo.
//      Jerry Xu 2008-7-7  Add the method of Add , Delete 
//      Jerry Xu 2008-7-8  Add the method:Copy,NewInstance,FromTo,CopyTo,IsExist
//      Jerry Xu 2008-7-10 Add the method:AddFirst,AddLast
//      Jerry Xu 2008-7-10 LinkedList<MemoryLibraryItem> Items to MemoryLibraryItem[]
//      Jerry Xu 2008-7-10 Add the method:Clear
//      Jerry Xu 2008-7-15 ToProxy
//      Jerry Xu 2008-7-23 Add property:ImageAdapterName
//      Michael  2008-7-31 增加image和imagepath属性
//      Jerry Xu 2008-11-27 Add property:Messages
//      Jerry Xu 2008-11-27 Add methods:GetAllMessages,GetMessages 
//      Jerry Xu 2008-11-27 Add property:TimeSliceGroupAdapters
//      Jerry Xu 2008-11-27 Add methods:GetAllTimeSliceGroupAdapters 
//      Jerry Xu 2008-11-27 Add method:GetTimeSliceGroups 
//      Jerry Xu 2009-2-12  Add property:IsInPlaylist
//      Jerry Xu 2009-4-27  Add property:AllTimeSliceGroups
//      Jerry Xu 2009-4-28  Add method:CheckIsEmpty()
//                          Update property:IsEmpty
//      Jerry Xu 2009-6-3   Update method:CheckManyLevel()
//      Jerry Xu 2009-6-8   Update method:InternalFromTo(PlaylistInfo playlist)
//                          Inert property:NailImageID
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------


using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Design;
using ProWrite.Core;
using ProWrite.Entity.Library;
using System.Xml.Serialization;
using System.Runtime.Serialization;

namespace ProWrite.Entity.Library
{
    /// <summary>
    /// Function:Playlist info
    /// Author:Jerry Xu
    /// Date: 2008-6-18
    /// </summary>
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    public class PlaylistInfo : MemoryLibraryItem
    {
        #region Non Serialized Fields
        [NonSerialized]
        private LinkedListNode<LibraryAdapter> _node;
        #endregion

        #region Serialized Fields
        private LinkedList<LibraryAdapter> _items = new LinkedList<LibraryAdapter>();
        private string _imageAdapterName;
        #endregion

        #region Serialized Fields Version 2
        [OptionalField]
        private string _nailImageID;
        #endregion


        #region Property define
        #region NailImage properties
        ///// <summary>
        ///// Current play item
        ///// </summary>
        //[Browsable(false)]
        //public string CurrentMessageAdapterID
        //{
        //    get { return _currentMessageAdapterID; }
        //    set
        //    {
        //        if (!string.Equals(_currentMessageAdapterID, value))
        //            _currentMessageAdapterID = value;
        //    }
        //}

        //public override Image Image
        //{
        //    get
        //    {
        //        if (!string.IsNullOrEmpty(_currentMessageAdapterID)
        //            && GetMessageInfo(_currentMessageAdapterID) != null)
        //        {
        //            return GetMessageInfo(_currentMessageAdapterID).Image;
        //        }
        //        else
        //            return null;
        //    }
        //    set
        //    {
        //        //base.Image = value;
        //    }
        //}

        //public string GetMessageID(string proxyID)
        //{
        //    foreach (MessageAdapterInfo item in _items)
        //    {
        //        if (item.Id == proxyID)
        //            return item.TargetId;
        //    }
        //    return null;
        //}

        //public MessageInfo GetMessageInfo(string proxyID)
        //{
        //    foreach (MessageAdapterInfo item in _items)
        //    {
        //        if (item.Id == proxyID)
        //        {
        //            if (item.Target != null)
        //                return item.Target as MessageInfo;
        //            else
        //            {
        //                return LibraryGroup.Current.Messages.GetById(item.TargetId);
        //            }

        //        }
        //    }
        //    return null;
        //}
        #endregion

        private int _inPlaylistCounter = 0;
        [Browsable(false)]
        public bool IsInPlaylist
        {
            get { return _inPlaylistCounter > 0; }
            set
            {
                if (value)
                    _inPlaylistCounter++;
                else if (_inPlaylistCounter > 0)
                    _inPlaylistCounter--;
            }
        }

        [Browsable(false)]
        public int InPlaylistCount
        {
            get { return _inPlaylistCounter; }
        }        

        [Browsable(false)]
        public bool IsManyLevel
        {
            get
            {
                return CheckManyLevel();
            }
        }

        [Browsable(true)]
        public override int Length
        {
            get
            {
                int TotalLength = 0;
                foreach (LibraryAdapter item in Items)
                {
                    if(item.Target != null)
                        TotalLength += item.Target.Length;
                }
                return TotalLength;
            }
        }

        

        [Browsable(false)]
        [Editor(Constance.Designers.NoneCollection, typeof(UITypeEditor))]
        public LibraryAdapter[] Items
        {
            get
            {
                LibraryAdapter[] array = new LibraryAdapter[_items.Count];
                _items.CopyTo(array, 0);
                return array;
            }

            set { _items = new LinkedList<LibraryAdapter>(value); }
        }

        

        [ReadOnly(true)]
        public override string Name
        {
            get
            {
                return base.Name;
            }
            set
            {
                base.Name = value;
            }
        }

        [Browsable(false)]
        public string ImageAdapterName
        {
            get { return _imageAdapterName; }
            set
            {
                if (!string.Equals(_imageAdapterName, value))
                {
                    _imageAdapterName = value;

                    //TODO:

                    for (int i = 0; i < Items.Length; i++)
                    {
                        if (Items[i].Name == _imageAdapterName)
                            Image = Items[i].Target.Image;
                    }
                }
            }
        }

        public override LibraryType AcceptType
        {
            get
            {
                return LibraryType.Message | LibraryType.Playlist | LibraryType.TimeSliceGroup;
            }
        }

        public override bool IsReferenceLibrary(LibraryItem library)
        {
            if ((AcceptType & library.Type) != library.Type)
                return false;

            foreach (LibraryAdapter item in _items)
            {
                if (item != null
                    && item.Target != null
                    && item.Target.Type == library.Type
                    && item.Target.Name == library.Name)
                    return true;

            }
            return false;
        }


        /// <summary>
        /// Library type
        /// </summary>
        public override LibraryType Type
        {
            get { return LibraryType.Playlist; }
        }

        public bool IsReferenceMessage(MessageInfo msg)
        {
            foreach (LibraryAdapter item in _items)
            {
                if (item != null
                    && item.Type == LibraryType.MessageProxy
                    && item.Target != null
                    && item.Target.Name == msg.Name)
                    return true;

            }
            return false;
        }

        public override bool IsEmpty
        {
            get
            {
                return CheckIsEmpty();
                //return _layers.Count == 0;
            }
        }

        private bool CheckIsEmpty()
        {
            if (this == null || this.Length == 0 || _items == null || _items.Count == 0)
                return true;

            foreach (LibraryAdapter adapter in _items)
            {
                if (adapter != null && adapter.Target != null && !adapter.Target.IsEmpty)
                    return false;
            }

            return true;
        }

        [Browsable(false)]
        public string NailImageID
        {
            get
            {
                return _nailImageID;
            }

            set { _nailImageID = value; }
        }
        #endregion

        #region Function define
        private bool CheckManyLevel()
        {
            if (_items == null || _items.Count == 0)
                return false;

            foreach (LibraryAdapter item in _items)
            {
                if (item.Target!=null && (item.Target.Type == LibraryType.Playlist || item.Target.Type == LibraryType.TimeSliceGroup))
                    return true;
            }
            return false;
        }


        /// <summary>
        /// Function:Add a message item to PlaylistInfo items
        /// Author:Jerry Xu
        /// Date:2008-7-7
        /// </summary>
        /// <param name="message">inserted position:MemoryLibraryItem</param>
        /// <param name="newMessage">Inserted message:MemoryLibraryItem</param>
        /// <returns>bool:Insert flag</returns>
        public bool Add(LibraryAdapter message, LibraryAdapter newMessage)
        {
            if (newMessage == null || newMessage.IsEmpty)
                return false;

            if (message == null)
                _items.AddFirst(newMessage);
            else
            {
                //Find the message item in PlaylistInfo items
                _node = _items.Find(message);
                if (_node != null)
                    _items.AddBefore(_node, newMessage);
                else
                    _items.AddLast(newMessage);
            }
            return true;
        }

        /// <summary>
        /// Function:Add a message item to PlaylistInfo items first
        /// Author:Jerry Xu
        /// Date:2008-7-10
        /// </summary>
        /// <param name="message">inserted message:MemoryLibraryItem</param>
        /// <returns>bool:Insert flag</returns>
        public bool AddFirst(LibraryAdapter message)
        {
            if (message == null || message.IsEmpty)
                return false;
            _items.AddFirst(message);
            return true;
        }
        /// <summary>
        /// Function:Add a message item to PlaylistInfo items last
        /// Author:Jerry Xu
        /// Date:2008-7-10
        /// </summary>
        /// <param name="message">inserted message:MemoryLibraryItem</param>
        /// <returns>bool:Insert flag</returns>
        public bool AddLast(LibraryAdapter message)
        {
            if (message == null || message.IsEmpty)
                return false;
            _items.AddLast(message);
            return true;
        }

        #region Move
        /// <summary>
        /// Function: Move messagebtn in panel
        /// Author  : Jerry Xu
        /// Date    : 2008-8-13
        /// </summary>
        /// <param name="index">messagebtn index</param>
        public void MoveItem(int sourceIndex, int destIndex)
        {
            if (sourceIndex != destIndex && destIndex - sourceIndex != 1)
            {
                LibraryAdapter source;
                if (sourceIndex < destIndex)
                    destIndex--;
                source = Items[sourceIndex];
                _node = _items.Find(Items[destIndex]);
                _items.Remove(source);

                if (sourceIndex > destIndex)
                    _items.AddBefore(_node, source);
                else
                    _items.AddAfter(_node, source);


                ////Move forward
                //if (destIndex == Items.Length)
                //{
                //    dest = Items[destIndex - 1];
                //    //Find the message item in PlaylistInfo items
                //    _node = _items.Find(dest);
                //    if (_node != null)
                //        _items.AddAfter(_node, source);
                //}
                //else
                //{
                //    //Move backward
                //    dest = Items[destIndex];
                //    //Find the message item in PlaylistInfo items
                //    _node = _items.Find(dest);
                //    if (_node != null)
                //        _items.AddBefore(_node, source);
                //}
                //_items.Remove(source);
            }
        }

        #endregion

        public bool Delete(LibraryAdapter message)
        {
            if (message != null && !message.IsEmpty)
            {
                _items.Remove(message);
            }
            return true;
        }

        /// <summary>
        /// Function:Delete all messages in PlaylistInfo
        /// Author:Jerry Xu
        /// Date:2008-7-10
        /// </summary>
        public void Clear()
        {
            _items.Clear();
        }


        /// <summary>
        /// Function:Judge a MemoryLibraryItem is exist in playlist items. 
        /// Author:Jerry Xu
        /// Date:2008-7-8
        /// </summary>
        /// <param name="memory">MemoryLibraryItem</param>
        /// <returns>bool:false(no exisit),true(exist)</returns>
        public bool IsExist(LibraryAdapter memory)
        {
            if (_items.Count == 0 || _items.Find(memory).Value == null || _items.Find(memory).Value.IsEmpty)
                return false;
            return true;
        }        

        /// <summary>
        /// Function: Init a new instance of this object
        /// Author  : Jerry Xu
        /// Date    : 2008-7-8 
        /// </summary>
        /// <returns>MemoryLibraryItem(PlaylistInfo)</returns>
        public override MemoryLibraryItem NewInstance()
        {
            return new PlaylistInfo();
        }

        /// <summary>
        /// Function: Get data from a object to current object
        /// Author  : Jerry Xu
        /// Date    : 2008-7-8 
        /// </summary>
        /// <param name="memory">MemoryLibraryItem</param>
        public override void FromTo(MemoryLibraryItem memory)
        {
            base.FromTo(memory);

            InternalFromTo(memory as PlaylistInfo);

        }

        public override void FromTo(ILockLibraryItem locker, int lockCounter)
        {
            base.FromTo(locker, lockCounter);
            InternalFromTo(locker as PlaylistInfo);
        }

        private void InternalFromTo(PlaylistInfo playlist)
        {
            //TODO:

            if (playlist._items == null || playlist._items.Count < 1)
                return;
            _items.Clear();
            _inPlaylistCounter = playlist._inPlaylistCounter;
            _nailImageID = playlist._nailImageID;
            foreach (LibraryAdapter item in playlist._items)
            {
                _items.AddLast(item.Copy());
            }
            //_image = playlist.Image;
            //_imagePath = playlist._imagePath;
        }

        /// <summary>
        /// Function: New a PlaylistAdapterInfo
        /// Author  : Jerry Xu
        /// Date    : 2008-7-15  
        /// </summary>
        /// <returns>PlaylistAdapterInfo</returns>
        public override LibraryAdapter ToProxy()
        {
            return new PlaylistAdapterInfo(this);
        }
        #region Set TimeSliceGroup next message
        public void SetTimeSliceGroupNextMessage()
        {
            foreach (TimeSliceGroupAdapterInfo adapter in TimeSliceGroupAdapters)
            {
                if (adapter.TimeSliceGroup != null && adapter.TimeSliceGroup.Items != null && adapter.TimeSliceGroup.Items.Length > 0)
                    adapter.SetCurrentMessageAdapter();
            }
        }
        #endregion
        #region All TimeSliceGroupAdapters
        [NonSerialized]
        private List<TimeSliceGroupAdapterInfo> _timeSliceGroupAdapters;
        [Browsable(false)]
        public TimeSliceGroupAdapterInfo[] TimeSliceGroupAdapters
        {
            get
            {
                GetAllTimeSliceGroupAdapters();
                if (_timeSliceGroupAdapters != null && _timeSliceGroupAdapters.Count > 0)
                    return _timeSliceGroupAdapters.ToArray();
                return null;
            }
        }

        /// <summary>
        /// Function:Get all TimeSliceGroups in this playlist 
        /// Author:Jerry Xu
        /// Date:2008-11-27
        /// </summary>
        private void GetAllTimeSliceGroupAdapters()
        {
            _timeSliceGroupAdapters = new List<TimeSliceGroupAdapterInfo>();
            TimeSliceGroupInfo group = null;
            foreach (LibraryAdapter adapter in _items)
            {
                switch (adapter.Target.Type)
                {
                    case LibraryType.TimeSliceGroup:
                        if (adapter.Target != null)
                        {
                            group = adapter.Target as TimeSliceGroupInfo;
                            if (!string.IsNullOrEmpty(group.CurrentMessageAdapterID) && group.Items.Length > 0 && group.GetMessageInfo(group.CurrentMessageAdapterID) != null)
                            {
                                _timeSliceGroupAdapters.Add(adapter as TimeSliceGroupAdapterInfo);
                            }
                        }
                        break;
                    case LibraryType.Playlist:
                        PlaylistInfo playlist = adapter.Target as PlaylistInfo;
                        if (playlist.Items != null && playlist.Items.Length > 0)
                        {
                            GetTimeSliceGroups(playlist);
                        }
                        break;
                }
                
            }
        }

        private void GetTimeSliceGroups(PlaylistInfo playlistInfo)
        {
            if (playlistInfo.Items == null || playlistInfo.Items.Length == 0)
                return;
            foreach (LibraryAdapter adapter in playlistInfo.Items)
            {
                if (adapter.Target != null)
                {
                    switch (adapter.Target.Type)
                    {
                        case LibraryType.TimeSliceGroup:
                            TimeSliceGroupInfo group = adapter.Target as TimeSliceGroupInfo;
                            if (!string.IsNullOrEmpty(group.CurrentMessageAdapterID) && group.Items.Length > 0 && group.GetMessageInfo(group.CurrentMessageAdapterID) != null)
                            {
                                _timeSliceGroupAdapters.Add(adapter as TimeSliceGroupAdapterInfo);
                            }
                            break;
                        case LibraryType.Playlist:
                            PlaylistInfo playlist = adapter.Target as PlaylistInfo;
                            if (playlist.Items != null && playlist.Items.Length > 0)
                            {
                                GetTimeSliceGroups(playlist);
                            }
                            break;
                    }

                }
            }
        }
        #endregion

        #region All messages
        [NonSerialized]
        private List<MessageInfo> _allmessages;
        [Browsable(false)]
        public MessageInfo[] AllMessages
        {
            get
            {
                GetAllMessages();
                if (_allmessages != null && _allmessages.Count > 0)
                    return _allmessages.ToArray();
                return null;
            }
        }

        /// <summary>
        /// Function:Get all Messages in this playlist 
        /// Author:Jerry Xu
        /// Date:2008-11-27
        /// </summary>
        private void GetAllMessages()
        {
            _allmessages = new List<MessageInfo>();
            foreach (LibraryAdapter adapter in _items)
            {
                if (adapter.Target != null)
                {
                    switch (adapter.Target.Type)
                    {
                        case LibraryType.Message:
                            if (adapter.Target.Length > 0)
                                _allmessages.Add(adapter.Target as MessageInfo);
                            break;
                        case LibraryType.TimeSliceGroup:
                            TimeSliceGroupInfo group = adapter.Target as TimeSliceGroupInfo;
                            
                            //if (!string.IsNullOrEmpty(group.CurrentMessageAdapterID) && group.Items.Length > 0 && group.GetMessageInfo(group.CurrentMessageAdapterID) != null)
                            if(group.Items!=null && group.Items.Length>0)
                            {
                                foreach (MessageAdapterInfo item in group.Items)
                                    _allmessages.Add(LibraryGroup.Current.Messages.GetById(item.TargetId));
                            }
                            break;
                        case LibraryType.Playlist:
                            PlaylistInfo playlist = adapter.Target as PlaylistInfo;
                            if (playlist.Items != null && playlist.Items.Length > 0)
                            {
                                GetMessages(playlist);
                            }
                            break;
                    }
                }
            }
        }

        private void GetMessages(PlaylistInfo playlistInfo)
        {
            if (playlistInfo.Items == null || playlistInfo.Items.Length == 0)
                return;
            foreach (LibraryAdapter adapter in playlistInfo.Items)
            {
                if (adapter.Target != null)
                {
                    switch (adapter.Target.Type)
                    {
                        case LibraryType.Message:
                            if (adapter.Target.Length > 0)
                                _allmessages.Add(adapter.Target as MessageInfo);
                            break;
                        case LibraryType.TimeSliceGroup:
                            TimeSliceGroupInfo group = adapter.Target as TimeSliceGroupInfo;
                            if (!string.IsNullOrEmpty(group.CurrentMessageAdapterID) && group.Items.Length > 0 && group.GetMessageInfo(group.CurrentMessageAdapterID) != null)
                            {
                                _allmessages.Add(group.GetMessageInfo(group.CurrentMessageAdapterID));
                            }
                            break;
                        case LibraryType.Playlist:
                            PlaylistInfo playlist = adapter.Target as PlaylistInfo;
                            if (playlist.Items != null && playlist.Items.Length > 0)
                            {
                                GetMessages(playlist);
                            }
                            break;
                    }

                }
            }
        }
        #endregion

        #region All TimeSliceGroups
        [NonSerialized]
        private List<TimeSliceGroupInfo> _alltimeSliceGroups;
        [Browsable(false)]
        public TimeSliceGroupInfo[] AllTimeSliceGroups
        {
            get
            {
                GetAllTimeSliceGroups();
                if (_alltimeSliceGroups != null && _alltimeSliceGroups.Count > 0)
                    return _alltimeSliceGroups.ToArray();
                return null;
            }
        }

        /// <summary>
        /// Function:Get all TimeSliceGroups in this playlist 
        /// Author:Jerry Xu
        /// Date:2008-11-27
        /// </summary>
        private void GetAllTimeSliceGroups()
        {
            _alltimeSliceGroups = new List<TimeSliceGroupInfo>();
            TimeSliceGroupInfo group = null;
            foreach (LibraryAdapter adapter in _items)
            {
                switch (adapter.Target.Type)
                {
                    case LibraryType.TimeSliceGroup:
                        if (adapter.Target != null)
                        {
                            group = adapter.Target as TimeSliceGroupInfo;
                            if (!string.IsNullOrEmpty(group.CurrentMessageAdapterID) && group.Items.Length > 0 && group.GetMessageInfo(group.CurrentMessageAdapterID) != null)
                            {
                                _alltimeSliceGroups.Add(adapter.Target as TimeSliceGroupInfo);
                            }
                        }
                        break;
                    case LibraryType.Playlist:
                        PlaylistInfo playlist = adapter.Target as PlaylistInfo;
                        if (playlist.Items != null && playlist.Items.Length > 0)
                        {
                            GetAllTimeSliceGroups(playlist);
                        }
                        break;
                }

            }
        }

        private void GetAllTimeSliceGroups(PlaylistInfo playlistInfo)
        {
            if (playlistInfo.Items == null || playlistInfo.Items.Length == 0)
                return;
            foreach (LibraryAdapter adapter in playlistInfo.Items)
            {
                if (adapter.Target != null)
                {
                    switch (adapter.Target.Type)
                    {
                        case LibraryType.TimeSliceGroup:
                            TimeSliceGroupInfo group = adapter.Target as TimeSliceGroupInfo;
                            if (!string.IsNullOrEmpty(group.CurrentMessageAdapterID) && group.Items.Length > 0 && group.GetMessageInfo(group.CurrentMessageAdapterID) != null)
                            {
                                _alltimeSliceGroups.Add(adapter.Target as TimeSliceGroupInfo);
                            }
                            break;
                        case LibraryType.Playlist:
                            PlaylistInfo playlist = adapter.Target as PlaylistInfo;
                            if (playlist.Items != null && playlist.Items.Length > 0)
                            {
                                GetAllTimeSliceGroups(playlist);
                            }
                            break;
                    }

                }
            }
        }
        #endregion

        #region All playlists
        [NonSerialized]
        private List<PlaylistInfo> _allplaylists;
        [Browsable(false)]
        public PlaylistInfo[] AllPlaylists
        {
            get
            {
                GetAllPlaylists();
                if (_allplaylists != null && _allplaylists.Count > 0)
                    return _allplaylists.ToArray();
                return null;
            }
        }

        /// <summary>
        /// Function:Get all Playlists in this playlist 
        /// Author:Jerry Xu
        /// Date:2008-12-05
        /// </summary>
        private void GetAllPlaylists()
        {
            _allplaylists = new List<PlaylistInfo>();
            foreach (LibraryAdapter adapter in _items)
            {
                if (adapter.Target != null && adapter.Target.Type == LibraryType.Playlist)
                {
                    PlaylistInfo playlist = adapter.Target as PlaylistInfo;
                    _allplaylists.Add(playlist);
                    if (playlist.Items != null && playlist.Items.Length > 0)
                    {
                        GetPlaylists(playlist);
                    }
                 }
            }
        }

        private void GetPlaylists(PlaylistInfo playlistInfo)
        {
            if (playlistInfo.Items == null || playlistInfo.Items.Length == 0)
                return;
            foreach (LibraryAdapter adapter in playlistInfo.Items)
            {
                if (adapter.Target != null && adapter.Target.Type == LibraryType.Playlist)
                {
                    PlaylistInfo playlist = adapter.Target as PlaylistInfo;
                    _allplaylists.Add(playlist);
                    if (playlist.Items != null && playlist.Items.Length > 0)
                    {
                        GetPlaylists(playlist);
                    }
                }
            }
        }
        #endregion

        #region ufe Messages TimeSliceGroups Playlists
        //[NonSerialized]
        //private List<MessageInfo> _messages;
        //[Browsable(false)]
        //public MessageInfo[] Messages
        //{
        //    get
        //    {
        //        _messages = new List<MessageInfo>();
        //        GetPlaylistItems(LibraryType.Message);
        //        if (_messages != null && _messages.Count > 0)
        //            return _messages.ToArray();
        //        return null;
        //    }
        //}

        //[NonSerialized]
        //private List<TimeSliceGroupInfo> _timeslicegroups;
        //[Browsable(false)]
        //public TimeSliceGroupInfo[] TimeSliceGroups
        //{
        //    get
        //    {
        //        _timeslicegroups = new List<TimeSliceGroupInfo>();
        //        GetPlaylistItems(LibraryType.TimeSliceGroup);
        //        if (_timeslicegroups != null && _timeslicegroups.Count > 0)
        //            return _timeslicegroups.ToArray();
        //        return null;
        //    }
        //}

        //[NonSerialized]
        //private List<PlaylistInfo> _playlists;
        //[Browsable(false)]
        //public PlaylistInfo[] Playlists
        //{
        //    get
        //    {
        //        _playlists = new List<PlaylistInfo>();
        //        GetPlaylistItems(LibraryType.Playlist);
        //        if (_playlists != null && _playlists.Count > 0)
        //            return _playlists.ToArray();
        //        return null;
        //    }
        //}

        //private void GetPlaylistItems(LibraryType type)
        //{
        //    if (_items == null || _items.Count == 0)
        //        return;
        //    foreach (LibraryAdapter adapter in _items)
        //    {
        //        if (adapter.Target != null && adapter.Target.Length > 0 && adapter.Target.Type == type)
        //        {
        //            if (type == LibraryType.Message)
        //                _messages.Add(adapter.Target as MessageInfo);
        //            if (type == LibraryType.TimeSliceGroup)
        //                _timeslicegroups.Add(adapter.Target as TimeSliceGroupInfo);
        //            if (type == LibraryType.Playlist)
        //                _playlists.Add(adapter.Target as PlaylistInfo);
        //        }
        //    }
        //}
        #endregion
        #endregion

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if (_items != null)
                _items.Clear();
            _items = null;
            _node = null;
        }
    }
}