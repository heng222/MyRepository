using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using System.ComponentModel;
using ProWrite.Core;

namespace ProWrite.Entity.Live
{
    [Serializable]
    [XmlInclude(typeof(LiveSign))]
    [XmlInclude(typeof(LiveMessageItem))]
    [XmlInclude(typeof(LiveCategory))]
    [XmlInclude(typeof(HotButtonInfo))]
    [XmlInclude(typeof(HotButtonItemInfo))]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    public abstract class MemoryLiveItem:LiveItem, ILockLiveItem, ICopyable<MemoryLiveItem>
    {
        #region Non Serialized Fields
        [NonSerialized]
        private int _lockerCounter = 0;
        #endregion

        #region Serialized Fields
        DateTime _createTime;
        DateTime _modifyTime;
        #endregion

        #region Serialized Fields Version 2
        #endregion

        public MemoryLiveItem()
		{
		}

        [XmlIgnore]
        [Browsable(false)]
        public bool IsLock
        {
            get { return _lockerCounter > 0; }
            set
            {
                if (value)
                    _lockerCounter++;
                else if(_lockerCounter>0)
                    _lockerCounter--;
            }
        }

        [XmlIgnore]
        [Browsable(false)]
        public int LockCount
        {
            get { return _lockerCounter; }
        }

        //[NonSerialized]
        
        [XmlIgnore]
        [Browsable(false)]
        public DateTime CreateTime
        {
            get { return _createTime; }
            set 
            {
                if (_createTime != value)
                    _createTime = value;
                else
                    _createTime = DateTime.Now;
            }
        }
        //[NonSerialized]
       
        [XmlIgnore]
        [Browsable(false)]
        public DateTime ModifyTime { 
            get {return _modifyTime;}
            set
            {
                if (_modifyTime != value)
                    _modifyTime = value;
                else
                    _modifyTime = DateTime.Now;
            }
        }

		/// <summary>
		/// Function: To Array for library tree to display
		/// Author  : Kevin
		/// Date    : 2008-7-8 
		/// </summary>
		/// <returns></returns>
		public override object[]  ToArray()
		{
            //if(Type == LibraryType.Schedule)
            ////if (Color == System.Drawing.Color.Empty)
            //    return new object[] { Name, Type, "N/A", null,Active };
            //else
            //    return new object[] { Name, Type, LengthText, Color,Active };
            return null;
		}

		/// <summary>
		/// Function: Clone a MemoryLibraryItem
		/// Author  : Jerry Xu
		/// Date    : 2008-7-8 
		/// </summary>
		/// <returns>MemoryLibraryItem</returns>
        public virtual MemoryLiveItem Copy()
        {
            MemoryLiveItem clone = NewInstance();
            clone.FromTo(this);
            return clone;
        }

        public void SetCounterZero()
        {
            _lockerCounter = 0;
        }

        object ICopyable.Copy()
        {
            return Copy();
        }

		/// <summary>
		/// Function: Init a new instance of this object
		/// Author  : Jerry Xu
		/// Date    : 2008-7-8 
		/// </summary>
		/// <returns>MemoryLibraryItem</returns>
        public abstract MemoryLiveItem NewInstance();

		/// <summary>
		/// Function: Get data from a object to current object
		/// Author  : Jerry Xu
		/// Date    : 2008-7-8 
		/// </summary>
		/// <param name="memory">MemoryLibraryItem</param>
        public virtual void FromTo(MemoryLiveItem memory)
		{
			//this.Caption = memory.Caption;
            this._lockerCounter = memory._lockerCounter;
            InternalFromTo(memory);
		}

        private void InternalFromTo(MemoryLiveItem memory)
        {
            this.Id = memory.Id;
            this.Name = memory.Name;
            
            this._createTime = memory._createTime;
            this._modifyTime = memory._modifyTime;            
        }

        public virtual void FromTo(ILockLiveItem locker, int lockCounter)
        {
            InternalFromTo(locker as MemoryLiveItem);
        }

		/// <summary>
		/// Function: Display text
		/// Author  : Jerry Xu
		/// Date    : 2008-7-9
		/// </summary>
		/// <returns></returns>
		public override string ToString()
		{
			return Name;
		}

		public virtual LiveAdapter ToProxy()
		{
			switch (Type)
			{
				case LiveType.HotButton:
                    return new HotButtonAdapterInfo(this as HotButtonInfo);
                case LiveType.HotButtonItem:
                    return new HotButtonItemAdapterInfo(this as HotButtonItemInfo);
                case LiveType.LiveCategory:
                    return new LiveCategoryAdapterInfo(this as LiveCategory);
                case LiveType.LiveMessage:
                    return new LiveMessageItemAdapterInfo(this as LiveMessageItem);
                case LiveType.LiveSign:
                    return new LiveSignAdapterInfo(this as LiveSign);
			}

			return null;
		}

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
        }
    }
}
