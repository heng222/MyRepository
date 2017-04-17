//---------------------------------------------------------------------
//
// File: TimeSliceGroupAdapterInfo.cs
//
// Description:
// The class of TimeSliceGroupAdapterInfo
//
// Author: Jerry Xu
//
// Date:2008-7-15
//
// Modify History:
//      Jerry Xu 2008-7-17  Add the property:CurrentMessageAdapterName.
//      Jerry Xu 2008-11-27 Add the method:SetCurrentMessageAdapter
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
using ProWrite.Entity.Library;

namespace ProWrite.Entity.Library
{
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public class TimeSliceGroupAdapterInfo : LibraryAdapter
    {
        #region Non Serialized Fields
        #endregion

        #region Serialized Fields
        private string _currentMessageAdapterName;
        #endregion

        #region Serialized Fields Version 2
        #endregion

        public TimeSliceGroupAdapterInfo()
		{
		}

		public TimeSliceGroupAdapterInfo(TimeSliceGroupInfo group):base(group)
		{
		}

		
		[Browsable(false)]
		public string CurrentMessageAdapterName
		{
			get { return _currentMessageAdapterName; }
			set { _currentMessageAdapterName = value; }
		}

		public TimeSliceGroupInfo TimeSliceGroup
		{
			get { return base.Target as TimeSliceGroupInfo; }
			set
			{
				base.Target = value;
			}
		}

        /// <summary>
        /// Function:Set next MessageAdapterInfo by current MessageAdapterInfo name 
        /// Author:Jerry Xu
        /// Date:2008-11-27
        /// </summary>
        public void SetCurrentMessageAdapter()
        {
            if (Target == null)
            {
                _currentMessageAdapterName = string.Empty;
                return;
            }
            MessageAdapterInfo adapter = TimeSliceGroup.GetCurrentMessageAdapter(_currentMessageAdapterName);
            if (adapter != null)
                _currentMessageAdapterName = adapter.Name;
            else
                _currentMessageAdapterName = string.Empty;

        }

		public override LibraryType Type
		{
			get { return LibraryType.TimeSliceGroupProxy; }
		}

        /// <summary>
        /// Function: Init a new instance of this object
        /// Author  : Jerry Xu
        /// Date    : 2008-7-8 
        /// </summary>
        /// <returns>LibraryAdapter</returns>
        public override LibraryAdapter NewInstance()
        {
            return new TimeSliceGroupAdapterInfo();
        }

        ///// <summary>
        ///// Function: Get data from a object to current object
        ///// Author  : Jerry Xu
        ///// Date    : 2008-7-8 
        ///// </summary>
        ///// <param name="memory">LibraryAdapter</param>
        //public override void FromTo(LibraryAdapter item)
        //{
        //    //this.Caption = memory.Caption;
        //    base.FromTo(item);

        //    //TODO:
        //    TimeSliceGroupAdapterInfo adp = item as TimeSliceGroupAdapterInfo;
        //    this.Name = adp.Name;
        //    this._targetName = adp._targetName;
        //    this._target = adp._target.Copy();
        //}
	}
}