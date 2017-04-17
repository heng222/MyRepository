//---------------------------------------------------------------------
//
// File: MemoryLibraryItem.cs
//
// Description:
// The abstract class of MemoryLibraryItem includes: Message, Playlist and TimeSliceGroupInfo
//
// Author: Louis
//
// Date:2008-7-04
//
// Modify History:
//      Jerry Xu 2008-7-8  Add the method:Copy,NewInstance,FromTo,CopyTo
//      Jerry Xu 2008-7-9  Add the mothod:ToString
//      Jerry Xu 2009-1-15 Update method:UpdateInternalFromTo(MemoryLibraryItem memory)
//      Jerry Xu 2009-3-19 Update method:InternalFromTo(MemoryLibraryItem memory)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Xml.Serialization;
using ProWrite.Core;
using System.ComponentModel;
using System.Drawing.Design;
using System.IO;
using ProWrite.Entity.Library;

namespace ProWrite.Entity.Library
{
	[Serializable]
	[XmlInclude(typeof(MessageInfo))]
	[XmlInclude(typeof(PlaylistInfo))]
	[XmlInclude(typeof(TimeSliceGroupInfo))]
	[TypeConverter(typeof(ExpandableObjectConverter))]
    public abstract class MemoryLibraryItem : LibraryItem, ILockLibraryItem, ICopyable<MemoryLibraryItem>
    {
        #region Non Serialized Fields
        [NonSerialized]
        private bool _isOpen = false;
        [NonSerialized]
        private Image _image;
        [NonSerialized]
        private bool _active;
        [NonSerialized]
        private int _lockerCounter = 0;
        #endregion

        #region Serialized Fields
        private int _length = 0;
        private Color _color;
        DateTime _createTime;
        DateTime _modifyTime;
        private string _imagePath;
        #endregion

        #region Serialized Fields Version 2
        #endregion

        public MemoryLibraryItem()
		{
		}

        
        [XmlIgnore]
        [Browsable(false)]
        public virtual bool IsOpen
        {
            get { return _isOpen; }
            set { _isOpen = value; }
        }

		
		[ReadOnly(true)]
		public virtual int Length
		{
			get{ return _length;}
			set { _length = value;}
		}

		
		[Browsable(false)]
		public Color Color
		{
			get { return _color;}
			set{ _color = value;}
		}

        
        [Browsable(false)]
        public string ImagePath
        {
            get { return _imagePath; }
            set { _imagePath = value; }
        }


		[XmlIgnore]
		[ReadOnly(true)]
		// [Editor(Constance.Designers.ReadOnlyImage, typeof(UITypeEditor))]
        [Browsable(false)]
		public virtual Image Image
		{
			get
			{
                if (_image == null && !string.IsNullOrEmpty(_imagePath))
                {
                    _image = IOHelper.GetImageFromFile(_imagePath);
                }
                
                return _image;
			}
			set { _image = value;}
		}

		/// <summary>
		/// Function: Format Length to length text for display
		/// Author  : Kevin
		/// Date    : 2008-7-10 
		/// </summary>
		[Browsable(false)]
		public string LengthText
		{
			get { return Formaters.FormatTime(Length, Constance.TimeSeparator); }
		}

        //判断是否被选中（仅仅用在LibraryDialog 中)
        [XmlIgnore]
        [Browsable(false)]
        public bool Active
        {
            get { return _active; }
            set { _active = value; }
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
			if(Type == LibraryType.Schedule)
			//if (Color == System.Drawing.Color.Empty)
				return new object[] { Name, Type, "N/A", null,Active };
			else
				return new object[] { Name, Type, LengthText, Color,Active };
		}

		/// <summary>
		/// Function: Clone a MemoryLibraryItem
		/// Author  : Jerry Xu
		/// Date    : 2008-7-8 
		/// </summary>
		/// <returns>MemoryLibraryItem</returns>
        public virtual MemoryLibraryItem Copy()
        {
            MemoryLibraryItem clone = NewInstance();
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
		public abstract MemoryLibraryItem NewInstance();

		/// <summary>
		/// Function: Get data from a object to current object
		/// Author  : Jerry Xu
		/// Date    : 2008-7-8 
		/// </summary>
		/// <param name="memory">MemoryLibraryItem</param>
		public virtual void FromTo(MemoryLibraryItem memory)
		{
			//this.Caption = memory.Caption;
            this._lockerCounter = memory._lockerCounter;
            InternalFromTo(memory);
		}

        private void InternalFromTo(MemoryLibraryItem memory)
        {
            this.Id = memory.Id;
            this.Name = memory.Name;
            this._color = memory._color;
            this._length = memory._length;
            this._isOpen = memory._isOpen;
            this._createTime = memory._createTime;
            this._modifyTime = memory._modifyTime;
            this._imagePath = memory._imagePath;
            this._image = null;
            //if (memory._image != null)
            //    this._image = memory._image.Clone() as Image;
        }

        public virtual void FromTo(ILockLibraryItem locker, int lockCounter)
        {
            InternalFromTo(locker as MemoryLibraryItem);
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

		public virtual LibraryAdapter ToProxy()
		{
			switch (Type)
			{
				case LibraryType.Message:
					return new MessageAdapterInfo(this as MessageInfo);
				case LibraryType.Playlist:
					return new PlaylistAdapterInfo(this as PlaylistInfo);
				case LibraryType.TimeSliceGroup:
					return new TimeSliceGroupAdapterInfo(this as TimeSliceGroupInfo);
			}

			return null;
		}

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if (_image != null)
            {
                _image.Dispose();
                _image = null;
            }
        }
	}
}