//---------------------------------------------------------------------
//
// File: LiveSign.cs
//
// Description:
// LiveSign class 
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
using ProWrite.Core;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Library;
using System.Collections;
using System.ComponentModel;

namespace ProWrite.Entity.Live
{
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    public class LiveSign : MemoryLiveItem, IEquatable<LiveSign>
    {

        public override string Name
        {
            get
            {
                var sign = Sign;
                return sign == null ? null : sign.Name;
            }
            set
            {
                ;
            }
        }

        private LiveMessageItem _message;
        public LiveMessageItem Message
        {
            set
            {
                _message = value;
            }
            get
            {
                return _message;
            }
        }

        private MediaControlType _mediaControl;
        public MediaControlType MediaControl
        {
            set
            {
                _mediaControl = value;
            }
            get
            {
                return _mediaControl;
            }
        }

        private QueueControlType[] _queueControl;
        public QueueControlType[] QueueControl
        {
            set
            {
                _queueControl = value;
            }
            get
            {
                return _queueControl;
            }
        }

        [field:NonSerialized]
        public DashboardItem Sign
        {
            get
            {
                if (string.IsNullOrEmpty(Id))
                    return null;
                return DashboardItem.GetSignById(Id);
            }
            set
            {
                string @new = null;
                if (value != null)
                    @new = value.Id;
                if (@new != Id)
                {
                    //if (PropertyChanged != null)
                    //    PropertyChanged(this, new PropertyChangedEventArgs("Sign", value, Sign));
                    Id = @new;
                }
            }
        }

        private bool _useButtonGraphic;
        public bool ButtonGraphic
        {
            get
            {
                return _useButtonGraphic;
            }
            set
            {
                _useButtonGraphic = value;
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
            get { return LiveType.LiveSign; }
        }


        #endregion

        #region Functions define        

        #region IEquatable<HotButtonInfo> Members

        public bool Equals(LiveSign other)
        {
            if (other == null)
                return false;

            return true;
        }

        #endregion

        public override bool Equals(object obj)
        {
            return Equals(obj as LiveSign);
        }

        public override MemoryLiveItem NewInstance()
        {
            return new LiveSign();
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

            InternalFromTo(memory as LiveSign);
        }

        private void InternalFromTo(LiveSign message)
        {

        }

        public override void FromTo(ILockLiveItem locker, int lockCounter)
        {
            base.FromTo(locker, lockCounter);
            InternalFromTo(locker as LiveSign);
        }



        public object[] ToArrayTimeSliceGroupItem()
        {
            //return new object[] { false, Name, Type, LengthText };
            return null;
        }

        public override LiveAdapter ToProxy()
        {
            return new LiveSignAdapterInfo(this);
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
