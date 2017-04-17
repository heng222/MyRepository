//---------------------------------------------------------------------
//
// File: TimeSliceGroupAdapterInfo.cs
//
// Description:
// The class of TimeSliceGroupAdapterInfo
//
// Author: Kevin Wang
//
// Date:2008-7-15
//
// Modify History:
//      Jerry Xu 2008-7-17  Add the property:IsActive
//      Jerry Xu 2008-7-25  _isActive default value:true
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
	public class MessageAdapterInfo : LibraryAdapter
    {
        #region Non Serialized Fields
        #endregion

        #region Serialized Fields
        private bool _isActive = true;
        #endregion

        #region Serialized Fields Version 2
        #endregion

        public MessageAdapterInfo()
		{
		}

		public MessageAdapterInfo(MessageInfo message):base(message)
		{
		}

		public MessageInfo Message
		{
			get { return base.Target as MessageInfo; }
		}

		
		/// <summary>
		/// Is active
		/// </summary>
		public bool IsActive
		{
			get { return _isActive; }
			set { _isActive = value; }
		}

        
		public override LibraryType Type
		{
			get { return LibraryType.MessageProxy; }
		}

        /// <summary>
        /// Function: Init a new instance of this object
        /// Author  : Jerry Xu
        /// Date    : 2008-7-8 
        /// </summary>
        /// <returns>LibraryAdapter</returns>
        public override LibraryAdapter NewInstance()
        {
            return new MessageAdapterInfo();
        }

        public object[] ToArrayTimeSliceGroupItem(int groupLength)
        {
            if (Target == null || Target.IsEmpty)
                return null;
            return new object[] { IsActive, Target.Name, Formaters.FormatTime(groupLength) };
        }

        public override LibraryAdapter Copy()
        {
            MessageAdapterInfo clone = new MessageAdapterInfo();
            clone.FromTo(this);
            return clone;
            //return base.Copy();
        }

        /// <summary>
        /// Function: Get data from a object to current object
        /// Author  : Jerry Xu
        /// Date    : 2008-7-8 
        /// </summary>
        /// <param name="memory">LibraryAdapter</param>
        public override void FromTo(LibraryAdapter item)
        {
            //this.Caption = memory.Caption;
            if (item != null)
            {
                base.FromTo(item);
                //TODO:
                InternalFromTo(item as MessageAdapterInfo);
            }
        }

        private void InternalFromTo(LibraryAdapter item)
        {
            //TODO:
            if (item != null)
            {
                this.IsActive = (item as MessageAdapterInfo).IsActive;                
            }
        }
	}
}