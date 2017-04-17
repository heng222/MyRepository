//---------------------------------------------------------------------
//
// File: LibraryAdapter.cs
//      
// Description:
//      Library adapter class
//
// Author: Jerry Xu 2008-11-17
//
// Modify History:
//      Jerry Xu 2009-4-20 Update property:MemoryLibraryItem Target
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Serialization;
using System.ComponentModel;
using ProWrite.Core;
using System.Runtime.Serialization;

namespace ProWrite.Entity.Library
{
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public abstract class LibraryAdapter : LibraryItem
    {
        #region Non Serialized Fields
        [NonSerialized]
        protected MemoryLibraryItem _target;
        #endregion

        #region Serialized Fields
        private string _targetName;
        //[OptionalField]
        protected string _targetId;
        #endregion

        #region Serialized Fields Version 2
        #endregion
        
		public LibraryAdapter()
		{
			base.Name = KeyGenerator.Library.ToString();
		}

		public LibraryAdapter(MemoryLibraryItem target)
		{
			base.Name = KeyGenerator.Library.ToString();
			SetTarget(target);
		}

		private void SetTarget(MemoryLibraryItem target)
		{
			_target = target;
            if (_target != null)
            {
                _targetId = _target.Id;
            }
		}        

		void OnTargetNameChanged(EntityNameChangeEventArgs e)
		{
			_targetName = e.NewValue;
		}

		[Browsable(false)]
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

		[XmlIgnore]
		[Browsable(false)]
		public virtual MemoryLibraryItem Target
		{
			get 
            { 
                if(_target!=null)
                    return _target;
                LibraryType targetType = LibraryType.Message;
                switch (Type)
                {
                    case LibraryType.MessageProxy:
                        targetType = LibraryType.Message;
                        break;
                    case LibraryType.PlaylistProxy:
                        targetType = LibraryType.Playlist;
                        break;
                    case LibraryType.TimeSliceGroupProxy:
                        targetType = LibraryType.TimeSliceGroup;
                        break;
                }
                _target = LibraryGroup.Current.GetById(_targetId, targetType) as MemoryLibraryItem;
                return _target;
            }
			set
			{
				SetTarget(value);
			}
		}

        [Browsable(false)]
        public string TargetId
        {
            get { return _targetId; }
            set { _targetId = value; }
        }

        //[Browsable(false)]
        //public string TargetName
        //{
        //    get { return _targetName; }
        //    set { _targetName = value; }
        //}
        
        //private bool _active = true;
        //[Browsable(false)]
        //public bool Active
        //{
        //    get { return _active; }
        //    set { _active = value; }
        //}

        /// <summary>
        /// Function: Clone a LibraryAdapter
        /// Author  : Jerry Xu
        /// Date    : 2008-7-8 
        /// </summary>
        /// <returns>LibraryAdapter</returns>
        public virtual LibraryAdapter Copy()
        {
            LibraryAdapter clone = NewInstance();
            clone.FromTo(this);
            return clone;
        }

        /// <summary>
        /// Function: Init a new instance of this object
        /// Author  : Jerry Xu
        /// Date    : 2008-7-8 
        /// </summary>
        /// <returns>LibraryAdapter</returns>
        public abstract LibraryAdapter NewInstance();

        /// <summary>
        /// Function: Get data from a object to current object
        /// Author  : Jerry Xu
        /// Date    : 2008-7-8 
        /// </summary>
        /// <param name="memory">LibraryAdapter</param>
        public virtual void FromTo(LibraryAdapter item)
        {
            this.Id = item.Id;
            this.Name = item.Name;
            _targetId = item._targetId;
            _target = item._target;
            _targetName = item._targetName;
            //_active = item._active;
        }

		/// <summary>
		/// Function: To Array for library tree to display
		/// Author  : Kevin
		/// Date    : 2008-7-8 
		/// </summary>
		/// <returns></returns>
		public override object[] ToArray()
		{
			if (_target == null)
				return null;
			return _target.ToArray();
		}

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            _targetName = null;
        }

	}
}
