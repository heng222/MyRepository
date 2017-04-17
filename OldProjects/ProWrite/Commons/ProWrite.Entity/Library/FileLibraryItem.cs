//---------------------------------------------------------------------
//
// File: FileLibraryItem.cs
//
// Description:
// The abstract class of FileLibraryItem
//
// Author: Louis
//
// Date:2008-7-04
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.IO;
using ProWrite.Core;
using System.Xml.Serialization;

namespace ProWrite.Entity.Library
{
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
    public abstract class FileLibraryItem : LibraryItem, ILockLibraryItem //, IReferenceLibraryItem
    {
        #region Non Serialized Fields
        [NonSerialized]
        private int _lockerCounter = 0;
        #endregion

        #region Serialized Fields
        private string _path = string.Empty;
        #endregion

        #region Serialized Fields Version 2
        #endregion
        
		//private IReferenceCounter _refCounter;

		public FileLibraryItem()
		{
			//_refCounter = new ResourceReferenceCounter();
			//_refCounter.IncreaseReference();
		}

		public FileLibraryItem(string path)
		{
			_path = path;

			if (!string.IsNullOrEmpty(_path))
				Name = System.IO.Path.GetFileName(_path);
		}
        
		public static FileLibraryItem Create(LibraryType type,string path)
		{
			if (!string.IsNullOrEmpty(path) || File.Exists(path))
				return null;

			FileLibraryItem item = null;
			if (type == LibraryType.Image)
				item = new ImageInfo();
			else if (type == LibraryType.Video)
				item = new VideoInfo();
			else
				return null;

			item.Path = path;

			return item;
		}

		[ReadOnly(true)]
		public string Path
		{
			get { return _path; }
			set{ _path = value; }
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
		public bool IsValiad
		{
			get
			{
				return File.Exists(Path);
			}
		}

        
        [XmlIgnore]
        [ReadOnly(true)]
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

        public void FromTo(ILockLibraryItem locker, int lockCounter)
        {
            FileLibraryItem item = locker as FileLibraryItem;
            this._path = item._path;
            this.Name = item.Name;
        }
		//public IReferenceCounter RefCounter
		//{
		//    get { return _refCounter; }
		//}

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            _path = null;
        }
	}
}