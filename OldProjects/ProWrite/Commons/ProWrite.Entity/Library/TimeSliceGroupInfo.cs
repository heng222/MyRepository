//---------------------------------------------------------------------
//
// File: TimeSliceGroupInfo.cs
//
// Description:
// The class of TimeSliceGroupInfo
//
// Author: Louis
//
// Date:2008-7-04
//
// Modify History:
//      Jerry Xu 2008-7-7  Add the property of IsRandom,its type is bool and its default value is false.
//      Jerry Xu 2008-7-7  Delete the property of Item.
//      Jerry Xu 2008-7-7  Add the property of Items,its type is linked list of MessageInfo.
//      Jerry Xu 2008-7-7  Add the method of Add , Delete
//      Jerry Xu 2008-7-8  Add the method:Copy,NewInstance,FromTo,CopyTo
//      Jerry Xu 2008-7-13 Add the method:Add(MessageInfo message)
//      Jerry Xu 2008-7-15 Add the property:Current,AdapterName
//      Jerry Xu 2008-7-15 ToProxy
//      Jerry Xu 2008-7-16 Add the method:Clear
//      Jerry Xu 2008-7-17 Delete property:Current,AdapterName
//      Jerry Xu 2008-7-23 Add property:ImageAdapterName
//      Jerry Xu 2008-11-27 Add property:MessageAdapters
//      Jerry Xu 2008-11-27 Add the method:GetMessageAdapters,GetCurrentMessageAdapter
//      Jerry Xu 2009-3-12 Update method:GetMessageInfo(string proxyID)
//      Jerry Xu 2009-4-27 Add method:GetMessageID(string proxyID)
//      Jerry Xu 2009-4-28  Add method:CheckIsEmpty()
//                          Update property:IsEmpty
//      Jerry Xu 2009-6-8   Update method:InternalFromTo(TimeSliceGroupInfo group)
//                          Inert property:NailImageID
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core;
using System.Xml.Serialization;
using System.ComponentModel;
using System.Drawing.Design;
using System.Drawing;
using ProWrite.Entity.Library;
using System.Runtime.Serialization;

namespace ProWrite.Entity.Library
{
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
    public class TimeSliceGroupInfo : MemoryLibraryItem
    {
        #region Non Serialized Fields
        [NonSerialized]
        private LinkedListNode<MessageAdapterInfo> _node;
        #endregion

        #region Serialized Fields
        private LinkedList<MessageAdapterInfo> _items = new LinkedList<MessageAdapterInfo>();
        private string _currentMessageAdapterID = string.Empty;
        private bool _isRandom = false;
        #endregion

        #region Serialized Fields Version 2
        [OptionalField]
        private string _nailImageID;
        #endregion

        #region Variant define
        
		#endregion

		#region Property define
        
		[Editor(Constance.Designers.NoneCollection,typeof(UITypeEditor))]
		public MessageAdapterInfo[] Items
		{
			get
			{
                if (_items == null || _items.Count == 0)
                    return null;
				MessageAdapterInfo[] array = new MessageAdapterInfo[_items.Count];
				_items.CopyTo(array, 0);
				return array;
			}

			set { _items = new LinkedList<MessageAdapterInfo>(value); }
		}

        /// <summary>
        /// Current play item
        /// </summary>
        [Browsable(false)]
        public string CurrentMessageAdapterID
        {
            get { return _currentMessageAdapterID; }
            set
            {
                if (!string.Equals(_currentMessageAdapterID, value))
                    _currentMessageAdapterID = value;
            }
        }

        public override Image Image
        {
            get
            {
                if (!string.IsNullOrEmpty(_currentMessageAdapterID)
                    && GetMessageInfo(_currentMessageAdapterID)!=null)
                {
                    return GetMessageInfo(_currentMessageAdapterID).Image;
                }
                else
                    return null;
            }
            set
            {
                //base.Image = value;
            }
        }

        public string GetMessageID(string proxyID)
        {
            foreach (MessageAdapterInfo item in _items)
            {
                if (item.Id == proxyID)
                    return item.TargetId;                    
            }
            return null;
        }

		public MessageInfo GetMessageInfo(string proxyID)
		{
			foreach (MessageAdapterInfo item in _items)
			{
                if (item.Id == proxyID)
                {
                    if (item.Target != null)
                        return item.Target as MessageInfo;
                    else
                    {
                        return LibraryGroup.Current.Messages.GetById(item.TargetId);
                    }

                }
			}
			return null;
		}
		/// <summary>
		/// Library type
		/// </summary>
		public override LibraryType Type
		{
			get { return LibraryType.TimeSliceGroup; }
		}
		
		/// <summary>
		/// Is random
		/// </summary>
		public bool IsRandom
		{
			set { _isRandom = value; }
			get { return _isRandom; }
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

            foreach (MessageAdapterInfo adapter in _items)
            {
                if (adapter != null && adapter.Target!=null && !adapter.Target.IsEmpty)
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
		/// <summary>
		/// Function:Add a message info to TimeSliceGroup items
		/// Author:Jerry Xu
		/// Date:2008-7-7
		/// </summary>
		/// <param name="message">inserted position:MessageAdpaterInfo</param>
		/// <param name="newMessage">Inserted message:MessageAdpaterInfo</param>
		/// <returns>bool:Insert flag</returns>
		public bool Add(MessageAdapterInfo message, MessageAdapterInfo newMessage)
		{
			if (newMessage == null || newMessage.IsEmpty)
				return false;

			if (message == null)
				_items.AddFirst(newMessage);
			else
			{
				//Find the message info in TimeSliceGroup items
				_node = _items.Find(message);                
				if (_node != null)
					_items.AddBefore(_node, newMessage);
				else
					_items.AddLast(newMessage);
			}
			return true;
		}

		/// <summary>
		/// Function:Add a message info to TimeSliceGroup items
		/// Author:Jerry Xu
		/// Date:2008-7-13
		/// </summary>
		/// <param name="message">inserted MessageInfo</param>
		/// <returns>bool:Insert flag</returns>
		public bool Add(MessageAdapterInfo message)
		{
			if (message == null)
				return false;
			_items.AddLast(message);
			return true;
		}

		/// <summary>
		/// Function:Clear TimeSliceGroup items
		/// Author:Jerry Xu
		/// Date:2008-7-16
		/// </summary>                
		public void Clear()
		{
			_items.Clear();
		}

		/// <summary>
		/// Function:Delete a message info from TimeSliceGroup items
		/// Author:Jerry Xu
		/// Date:2008-7-7
		/// </summary>
		/// <param name="message">Deleted message info:MessageInfo</param>
		/// <returns>bool:Deleted flag</returns>
		public bool Delete(MessageAdapterInfo message)
		{
			if (message != null && message.IsEmpty)
			{
				_items.Remove(message);
			}
			return true;
		}

		public override MemoryLibraryItem NewInstance()
		{
			return new TimeSliceGroupInfo();
		}

		public override void FromTo(MemoryLibraryItem memory)
		{
            if (memory != null)
            {
                base.FromTo(memory);

                //TODO:
                InternalFromTo(memory as TimeSliceGroupInfo);
            }

		}

        private void InternalFromTo(TimeSliceGroupInfo group)
        {
            if (group != null)
            {
                _currentMessageAdapterID = group._currentMessageAdapterID;
                _isRandom = group._isRandom;
                _nailImageID = group._nailImageID;
                AddRange(group.Items);
                //_items = group._items;
            }
        }

        public void AddRange(MessageAdapterInfo[] items)
        {
            _items.Clear();
            if (items == null || items.Length < 1)
                return;
            foreach (MessageAdapterInfo item in items)
                _items.AddLast((item as MessageAdapterInfo).Copy() as MessageAdapterInfo);
        }

        public override void FromTo(ILockLibraryItem locker, int lockCounter)
        {
            base.FromTo(locker, lockCounter);
            InternalFromTo(locker as TimeSliceGroupInfo);
        }

        /// <summary>
        /// Function: Clone a MemoryLibraryItem
        /// Author  : Jerry Xu
        /// Date    : 2008-10-30 
        /// </summary>
        /// <returns>MemoryLibraryItem(MessageInfo)</returns>
        public override MemoryLibraryItem Copy()
        {
            TimeSliceGroupInfo clone = new TimeSliceGroupInfo();
            clone.FromTo(this);
            return clone;
        }

		/// <summary>
		/// Function: New a TimeSliceGroupAdapter
		/// Author  : Jerry Xu
		/// Date    : 2008-7-15  
		/// </summary>
		/// <returns>TimeSliceGroupAdapter</returns>
		public new TimeSliceGroupAdapterInfo ToProxy()
		{
			return new TimeSliceGroupAdapterInfo(this);
		}

		public override LibraryType AcceptType
		{
			get
			{
				return LibraryType.Message;
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

        [NonSerialized]
        private List<MessageAdapterInfo> _messageAdapters;
        [Browsable(false)]
        public MessageAdapterInfo[] MessageAdapters
        {
            get
            {
                GetMessageAdapters();
                if (_messageAdapters != null && _messageAdapters.Count > 0)
                    return _messageAdapters.ToArray();
                return null;
            }
        }

        /// <summary>
        /// Function:Get all messages and these messages are active 
        /// Author:Jerry Xu
        /// Date:2008-11-27
        /// </summary>
        private void GetMessageAdapters()
        {
            if(_items==null || Items.Length==0)
            {
                _messageAdapters = null;
                return;
            }
            foreach(MessageAdapterInfo item in _items)
            {
                if(item.Target!=null && item.IsActive)
                    _messageAdapters.Add(item);
            }
        }

        /// <summary>
        /// Function:Get next MessageAdapterInfo by current MessageAdapterInfo name 
        /// Author:Jerry Xu
        /// Date:2008-11-27
        /// </summary>
        /// <param name="messageAdapterName">current MessageAdapterInfo name</param>
        /// <returns>MessageAdapterInfo:Next MessageAdapterInfo</returns>
        public MessageAdapterInfo GetCurrentMessageAdapter(string messageAdapterName)
        {
            if(_items == null || _items.Count==0)
                return null;

            GetMessageAdapters();

            if(_messageAdapters == null || _messageAdapters.Count==0)
                return null;
            
			if(_messageAdapters.Count==1)
                return _messageAdapters[0];
            
            int currentIndex = 0;//Current play message adapter index

            //Set current play message name
            if (_isRandom)
			{

			    //Set random message adapter index
			    int max = _messageAdapters.Count;
			    Random ran = new Random();
			    currentIndex = ran.Next(max);
		    }
			else//Set no random message adapter
			{
                if (string.IsNullOrEmpty(messageAdapterName))
                {
                    currentIndex = 0;
                    return _messageAdapters[currentIndex];
                }

				//Set current play message name
				int lastIndex = 0;//Last play message adapter index
				//Get last play message adapter index
				for (int i = 0; i < _messageAdapters.Count; i++)
				{
					if (_messageAdapters[i].Name == messageAdapterName)
						lastIndex = i;
				}
				//Set current play message adapter index
				if (lastIndex == _messageAdapters.Count - 1)
					currentIndex = 0;
				else
					currentIndex = lastIndex + 1;					
			}
			return _messageAdapters[currentIndex];
        }

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
        /// Function:Get all Messages in this timeSliceGroup 
        /// Author:Jerry Xu
        /// Date:2009-6-4
        /// </summary>
        private void GetAllMessages()
        {
            _allmessages = new List<MessageInfo>();
            foreach (LibraryAdapter adapter in _items)
            {
                if (adapter.Target != null)
                    if (adapter.Target.Length > 0)
                        _allmessages.Add(adapter.Target as MessageInfo);
            }
        }        
        #endregion

		#endregion

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if (_items != null)
            {
                _items.Clear();
                _items = null;
            }
            _node = null;
        }
	}
}