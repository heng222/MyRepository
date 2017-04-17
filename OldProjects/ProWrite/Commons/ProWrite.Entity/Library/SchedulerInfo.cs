//---------------------------------------------------------------------
//
// File: SchedulerInfo.cs
//
// Description:
//      Scheduler library
//
// Author: Kevin 2008-7-23
//
// Modify Histories:
//      Jerry Xu 2009-1-21 Add property: AcceptType
//      Jerry Xu 2009-1-21 Add method  : IsReferenceLibrary(LibraryItem library)
//      Jerry Xu 2009-3-13 Update method:GetAllMessages(bool isAll),GetMessages(PlaylistInfo playlistInfo,bool isAll)
//      Jerry Xu 2009-4-28  Add method:CheckIsEmpty()
//                          Update property:IsEmpty
//      Jerry Xu 2009-4-30  Update method:CheckIsEmpty()
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core;
using System.ComponentModel;
using System.Drawing.Design;
using ProWrite.Entity.Library;
using System.Xml.Serialization;

namespace ProWrite.Entity.Library
{
	/// <summary>
	/// Scheduler library item
	/// </summary>
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public class SchedulerInfo:MemoryLibraryItem
    {
        #region Non Serialized Fields
        [NonSerialized]
        private List<MessageInfo> _allMessages;
        [NonSerialized]
        private List<MessageInfo> _messages;
        [NonSerialized]
        private List<TimeSliceGroupInfo> _timeSliceGroups;
        [NonSerialized]
        private List<TimeSliceGroupInfo> _allTimeSliceGroups;
        [NonSerialized]
        private List<PlaylistInfo> _allPlaylists;
        [NonSerialized]
        private List<PlaylistInfo> _playlists;
        #endregion

        #region Serialized Fields
        private List<AppointmentInfo> _items = new List<AppointmentInfo>();

        private PWSchedulerViewType _schedulerViewType;
        #endregion

        #region Serialized Fields Version 2
        #endregion

        
        [Browsable(false)]
		[Editor(Constance.Designers.NoneCollection,typeof(UITypeEditor))]
		public AppointmentInfo[] Items
		{
			get { return _items.ToArray(); }
			set
			{
				if (_items == null)
					_items = new List<AppointmentInfo>();
				else
					_items.Clear();

				if (value != null && value.Length > 0)
					_items.AddRange(value);
			}
		}

		/// <summary>
		/// get or set appointment type
		/// </summary>
		[Browsable(false)]
		public PWSchedulerViewType SchedulerViewType
		{
			get { return _schedulerViewType; }
			set
			{
				_schedulerViewType = value;
			}
		}

        public override bool IsEmpty
        {
            get
            {
                return CheckIsEmpty();
                //return _items.Count == 0;
                
                //return _layers.Count == 0;
            }
        }

        private bool CheckIsEmpty()
        {
            if (this == null || _items == null || _items.Count == 0)
                return true;

            foreach (AppointmentInfo adapter in _items)
            {
                if (adapter != null && adapter.Target != null && !adapter.Target.IsEmpty)
                    return false;
            }

            return true;
        }


        public override LibraryType AcceptType
        {
            get
            {
                return LibraryType.Message | LibraryType.Playlist | LibraryType.TimeSliceGroup;
            }
        }

        public override void FromTo(MemoryLibraryItem memory)
        {
            if (memory != null)
            {
                base.FromTo(memory);
                InternalFromTo(memory as SchedulerInfo);
            }
        }

        public override void FromTo(ILockLibraryItem locker, int lockCounter)
        {
            base.FromTo(locker, lockCounter);
            InternalFromTo(locker as SchedulerInfo);
        }

        private void InternalFromTo(SchedulerInfo other)
        {
            if (other != null)
            {
                _schedulerViewType = other._schedulerViewType;

                if (_items != null)
                    _items.Clear();
                else
                    _items = new List<AppointmentInfo>();
                if (other._items != null && other._items.Count > 0)
                {
                    foreach (AppointmentInfo appointment in other._items)
                    {
                        _items.Add(appointment.Copy() as AppointmentInfo);
                    }
                }
            }
        }
		
		public override MemoryLibraryItem NewInstance()
		{
			return new SchedulerInfo();
		}

		public override LibraryType Type
		{
			get { return LibraryType.Schedule; }
		}

		public void Clear()
		{
			_items.Clear();
		}

		public void Delete(AppointmentInfo item)
		{
			_items.Remove(item);
		}

		public void Add(AppointmentInfo item)
		{
			_items.Add(item);
		}

        #region All libraryitems
        
        [Browsable(false)]
        public MemoryLibraryItem[] MemoryLibraryItems
        {
            get
            {
                var items = new ListSet<MemoryLibraryItem>();
                items.Add(this);


                return items.ToArray();
            }
        }
        #endregion

        #region NO All TimeSliceGroupAdapters
        private bool IsExistTimeSliceGroup(List<TimeSliceGroupInfo> items, TimeSliceGroupInfo group)
        {
            if (items == null || items.Count == 0)
                return false;
            foreach (TimeSliceGroupInfo item in items)
            {
                if (item.Id == group.Id)
                    return true;
            }
            return false;
        }

        
        [Browsable(false)]
        public List<TimeSliceGroupInfo> TimeSliceGroups
        {
            get
            {
                _timeSliceGroups = new List<TimeSliceGroupInfo>();
                GetAllTimeSliceGroups(false);
                return _timeSliceGroups;
            }
        }
        #endregion

        #region All TimeSliceGroupAdapters
        
        [Browsable(false)]
        public  List<TimeSliceGroupInfo> AllTimeSliceGroups
        {
            get
            {
                _allTimeSliceGroups = new List<TimeSliceGroupInfo>();
                GetAllTimeSliceGroups(true);
                return _allTimeSliceGroups;
            }
        }

        /// <summary>
        /// Function:Get all TimeSliceGroups in this playlist 
        /// Author:Jerry Xu
        /// Date:2008-11-27
        /// </summary>
        private void GetAllTimeSliceGroups(bool isAll)
        {
            _allTimeSliceGroups = new List<TimeSliceGroupInfo>();
            TimeSliceGroupInfo group = null;
            foreach (AppointmentInfo appoint in _items)
            {
                if (appoint.Target != null)
                {
                    switch (appoint.Target.Type)
                    {
                        case LibraryType.TimeSliceGroup:
                            group = appoint.Target as TimeSliceGroupInfo;
                            //if (!string.IsNullOrEmpty(group.ImageMessageAdapterName) && group.Items.Length > 0 && group.GetMessageInfo(group.ImageMessageAdapterName) != null)
                            if (group.Items!=null && group.Items.Length > 0)
                            {
                                if (isAll)
                                    _allTimeSliceGroups.Add(group);
                                else
                                {
                                    if (!IsExistTimeSliceGroup(_timeSliceGroups, group))
                                    {
                                        _timeSliceGroups.Add(group);
                                    }
                                }
                            }
                            break;
                        case LibraryType.Playlist:
                            PlaylistInfo playlist = appoint.Target as PlaylistInfo;
                            if (playlist.Items != null && playlist.Items.Length > 0)
                            {
                                GetTimeSliceGroups(playlist,isAll);
                            }
                            break;
                    }
                }
            }
        }

        private void GetTimeSliceGroups(PlaylistInfo playlistInfo,bool isAll)
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
                            //if (!string.IsNullOrEmpty(group.ImageMessageAdapterName) && group.Items.Length > 0 && group.GetMessageInfo(group.ImageMessageAdapterName) != null)
                            if (group.Items != null && group.Items.Length > 0)
                            {
                                if (isAll)
                                    _allTimeSliceGroups.Add(group);
                                else
                                {
                                    if (!IsExistTimeSliceGroup(_timeSliceGroups, group))
                                    {
                                        _timeSliceGroups.Add(group);
                                    }
                                }
                            }
                            break;
                        case LibraryType.Playlist:
                            PlaylistInfo playlist = adapter.Target as PlaylistInfo;
                            if (playlist.Items != null && playlist.Items.Length > 0)
                            {
                                GetTimeSliceGroups(playlist,isAll);
                            }
                            break;
                    }

                }
            }
        }
        #endregion

        #region NO All Messages
        private bool IsExistMessage(List<MessageInfo> items, MessageInfo message)
        {
            if (items == null || items.Count == 0)
                return false;
            foreach (MessageInfo item in items)
            {
                if (item.Id == message.Id)
                    return true;
            }
            return false;
        }

        
        [Browsable(false)]
        public List<MessageInfo> Messages
        {
            get
            {
                _messages = new List<MessageInfo>();

                GetAllMessages(false);
                return _messages;
            }
        }
        #endregion

        #region All messages
        
        [Browsable(false)]
        public List<MessageInfo> AllMessages
        {
            get
            {
                _allMessages = new List<MessageInfo>();
                GetAllMessages(true);
                return _allMessages;
            }
        }

        /// <summary>
        /// Function:Get all Messages in this playlist 
        /// Author:Jerry Xu
        /// Date:2008-11-27
        /// </summary>
        private void GetAllMessages(bool isAll)
        {
            _allMessages = new List<MessageInfo>();
            foreach (LibraryAdapter adapter in _items)
            {
                if (adapter.Target != null)
                {
                    switch (adapter.Target.Type)
                    {
                        case LibraryType.Message:
                            //if (adapter.Target.Length > 0)
                            //{
                                if (isAll)
                                    _allMessages.Add(adapter.Target as MessageInfo);
                                else
                                {
                                    if (!IsExistMessage(_messages, adapter.Target as MessageInfo))
                                        _messages.Add(adapter.Target as MessageInfo);
                                }
                            //}
                            break;
                        case LibraryType.TimeSliceGroup:
                            TimeSliceGroupInfo group = adapter.Target as TimeSliceGroupInfo;
                            if (!string.IsNullOrEmpty(group.CurrentMessageAdapterID) && group.Items.Length > 0 && group.GetMessageInfo(group.CurrentMessageAdapterID) != null)
                            {
                                foreach (MessageAdapterInfo item in group.Items)
                                {
                                    //if (item.Target != null && item.IsActive && item.Target.Length>0)
                                    if (item.Target != null && item.IsActive)
                                    {
                                        if (isAll)
                                            _allMessages.Add(adapter.Target as MessageInfo);
                                        else
                                        {
                                            if (!IsExistMessage(_messages, item.Target as MessageInfo))
                                                _messages.Add(item.Target as MessageInfo);
                                        }
                                    }
                                }
                            }
                            break;
                        case LibraryType.Playlist:
                            PlaylistInfo playlist = adapter.Target as PlaylistInfo;
                            if (playlist.Items != null && playlist.Items.Length > 0)
                            {
                                GetMessages(playlist,isAll);
                            }
                            break;
                    }
                }
            }
        }

        private void GetMessages(PlaylistInfo playlistInfo,bool isAll)
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
                            //if (adapter.Target.Length > 0)
                            //{
                                if (isAll)
                                    _allMessages.Add(adapter.Target as MessageInfo);
                                else
                                {
                                    if (!IsExistMessage(_messages, adapter.Target as MessageInfo))
                                        _messages.Add(adapter.Target as MessageInfo);
                                }
                            //}
                            break;
                        case LibraryType.TimeSliceGroup:
                            TimeSliceGroupInfo group = adapter.Target as TimeSliceGroupInfo;
                            if (!string.IsNullOrEmpty(group.CurrentMessageAdapterID) && group.Items.Length > 0 && group.GetMessageInfo(group.CurrentMessageAdapterID) != null)
                            {
                                foreach (MessageAdapterInfo item in group.Items)
                                {
                                    //if (item.Target != null && item.IsActive && item.Target.Length > 0)
                                    if (item.Target != null && item.IsActive)
                                    {
                                        if (isAll)
                                            _allMessages.Add(adapter.Target as MessageInfo);
                                        else
                                        {
                                            if (!IsExistMessage(_messages, item.Target as MessageInfo))
                                                _messages.Add(item.Target as MessageInfo);
                                        }
                                    }
                                }
                            }
                            break;
                        case LibraryType.Playlist:
                            PlaylistInfo playlist = adapter.Target as PlaylistInfo;
                            if (playlist.Items != null && playlist.Items.Length > 0)
                            {
                                GetMessages(playlist,isAll);
                            }
                            break;
                    }

                }
            }
        }
        #endregion

        #region NO All Playlists
        private bool IsExistPlaylist(List<PlaylistInfo> items, PlaylistInfo playlist)
        {
            if (items == null || items.Count == 0)
                return false;
            foreach (PlaylistInfo item in items)
            {
                if (item.Id == playlist.Id)
                    return true;
            }
            return false;
        }

        
        [Browsable(false)]
        public List<PlaylistInfo> Playlists
        {
            get
            {
                _playlists = new List<PlaylistInfo>();
                GetAllPlaylists(false);
                return _playlists;
            }
        }
        #endregion

        #region All playlists
        
        [Browsable(false)]
        public List<PlaylistInfo> AllPlaylists
        {
            get
            {
                _allPlaylists = new List<PlaylistInfo>();
                GetAllPlaylists(true);
                return _allPlaylists;
            }
        }

        /// <summary>
        /// Function:Get all Playlists in this playlist 
        /// Author:Jerry Xu
        /// Date:2008-12-05
        /// </summary>
        private void GetAllPlaylists(bool isAll)
        {
            _allPlaylists = new List<PlaylistInfo>();
            foreach (LibraryAdapter adapter in _items)
            {
                if (adapter.Target != null && adapter.Target.Type == LibraryType.Playlist)
                {
                    PlaylistInfo playlist = adapter.Target as PlaylistInfo;
                    if (playlist.Items != null && playlist.Items.Length > 0)
                    {
                        if (isAll)
                            _allPlaylists.Add(playlist);
                        else
                        {
                            if (!IsExistPlaylist(_allPlaylists, playlist))
                                _playlists.Add(playlist);
                        }
                        GetPlaylists(playlist,isAll);
                    }
                }
            }
        }

        private void GetPlaylists(PlaylistInfo playlistInfo,bool isAll)
        {
            if (playlistInfo.Items == null || playlistInfo.Items.Length == 0)
                return;
            foreach (LibraryAdapter adapter in playlistInfo.Items)
            {
                if (adapter.Target != null && adapter.Target.Type == LibraryType.Playlist)
                {
                    PlaylistInfo playlist = adapter.Target as PlaylistInfo;
                    if (playlist.Items != null && playlist.Items.Length > 0)
                    {
                        if (isAll)
                            _allPlaylists.Add(playlist);
                        else
                        {
                            if (!IsExistPlaylist(_allPlaylists, playlist))
                                _playlists.Add(playlist);
                        }
                        GetPlaylists(playlist, isAll);
                    }
                }
            }
        }
        #endregion

        public override bool IsReferenceLibrary(LibraryItem library)
        {
            if ((AcceptType & library.Type) != library.Type)
                return false;

            foreach (AppointmentInfo item in _items)
            {
                if (item != null
                    && item.Target != null
                    && item.Target.Type == library.Type
                    && item.Target.Name == library.Name)
                    return true;

            }
            return false;
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if (_items != null)
            {
                int length = _items.Count;
                for (int i = 0; i < length; i++)
                {
                    _items[i].Dispose();
                    _items[i] = null;
                }
                _items.Clear();
                _items = null;
            }
        }
    }
}
