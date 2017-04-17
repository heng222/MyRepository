//---------------------------------------------------------------------
//
// File: LiveMessageItem.cs
//
// Description:
// LiveMessageItem class 
//
// Author: Jerry
// Date  : 2009-7-10
//
// Modify history:
//      
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.ComponentModel;
using System.Xml.Serialization;

using ProWrite.Core;
using ProWrite.Entity.Library;

namespace ProWrite.Entity.Live
{
    public enum DataStatus
    {
        Created,
        Updated,
        Deleted,
        NoChanged,
    }

    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    public class LiveMessageItem : MemoryLiveItem, IEquatable<LiveMessageItem>
    {        
        //public PropertyChangedEventArgs

        [NonSerialized]
        protected MemoryLibraryItem _target;
        public MemoryLibraryItem Target
        {
            get
            {                
                if(string.IsNullOrEmpty(Id))
                    return null;

                if (_target == null)
                {
                    _target = LibraryGroup.Current.GetById(Id);
                }
                return _target;
            }
            set
            {
                string @new = null;
                if (value != null)
                    @new = value.Id;
                if (@new != Id)
                    Id = @new;
            }
        }
        private LiveMessageState _state;
        public LiveMessageState State
        {
            get { return _state; }
            set
            {
                if (value != _state)
                {
                    _state = value;
                    MessageBus.Send(null, new PWMessage<SessionChangeMessage>(null));
                }
            }
        }

        private int _counter;
        public int Counter
        {
            get { return _counter; }
            set
            {
                if (value != _counter)
                {
                    _counter = value;
                    MessageBus.Send(null, new PWMessage<SessionChangeMessage>(null));
                }
            }
        }

        public Image Image
        {
            get
            {
                return Target.Image;
            }
        }

        public string LengthText
        {
            get
            {
                return Target.LengthText;
            }
        }

        ///////////////////////////////////////////////
        #region Non Serialized Fields
        
        #endregion

        #region Serialized Fields
        
        #endregion

        #region Serialized Fields Version 2
        #endregion

        
        #region Properties define             
        public override LiveType Type
        {
            get { return LiveType.LiveMessage; }
        }

        [XmlIgnore]
        [Browsable(false)]
        public DataStatus Status { get; set; }
        private bool _isNew = true;
        [XmlIgnore]
        [Browsable(false)]
        public virtual bool IsNew
        {
            get { return Status == DataStatus.Created; }
        }

        [XmlIgnore]
        [Browsable(false)]
        public bool IsUpdated
        {
            get { return Status == DataStatus.Updated; }
        }

        [XmlIgnore]
        [Browsable(false)]
        public bool IsDeleted
        {
            get { return Status == DataStatus.Deleted; }
        }

        #endregion

        #region Functions define     
        #region IEquatable<HotButtonInfo> Members

        public bool Equals(LiveMessageItem other)
        {
            if (other == null)
                return false;

            return true;
        }

        #endregion

        public override bool Equals(object obj)
        {
            return Equals(obj as LiveMessageItem);
        }        

        public override MemoryLiveItem NewInstance()
        {
            return new LiveMessageItem();
        }

        /// <summary>
        /// Function: Get data from a object to current object
        /// Author  : Jerry Xu
        /// Date    : 2008-7-8 
        /// </summary>
        /// <param name="memory">MemoryLibraryItem</param>
        public override void FromTo(MemoryLiveItem memory)
        {
            base.FromTo(memory);

            InternalFromTo(memory as LiveMessageItem);
        }

        private void InternalFromTo(LiveMessageItem message)
        {
            
        }

        public override void FromTo(ILockLiveItem locker, int lockCounter)
        {
            base.FromTo(locker, lockCounter);
            InternalFromTo(locker as LiveMessageItem);
        }      



        public object[] ToArrayTimeSliceGroupItem()
        {
            //return new object[] { false, Name, Type, LengthText };
            return null;
        }

        public override LiveAdapter ToProxy()
        {
            return new LiveMessageItemAdapterInfo(this);
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
        }
        #endregion

    }
}
