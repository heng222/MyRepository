//---------------------------------------------------------------------
//
// File: HotButtonInfo.cs
//
// Description:
// HotButtonInfo class 
//
// Author: Jerry
// Date  : 2009-7-14
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
using System.Drawing;
using System.ComponentModel;

namespace ProWrite.Entity.Live
{
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    public class HotButtonInfo : MemoryLiveItem, IEquatable<HotButtonInfo>
    {
        private List<HotButtonItemInfo> lstHotButton = new List<HotButtonItemInfo>();

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
            get { return LiveType.HotButton; }
        }

        #endregion

        #region Functions define

        #region IEquatable<HotButtonInfo> Members

        public bool Equals(HotButtonInfo other)
        {
            if (other == null)
                return false;

            return true;
        }

        #endregion

        public void AddHotButtonItem(HotButtonItemInfo item)
        {
            lstHotButton.Add(item);
        }

        public void RemoveButtonItem(HotButtonItemInfo item)
        {
            lstHotButton.Remove(item);
        }

        public override bool Equals(object obj)
        {
            return Equals(obj as HotButtonInfo);
        }

        public override MemoryLiveItem NewInstance()
        {
            return new HotButtonInfo();
        }

        /// <summary>
        /// Function: Get data from a object to current object
        /// Author  : Jerry Xu
        /// Date    : 2008-7-8 
        /// </summary>
        /// <param name=memory>MemoryLibraryItem</param>
        public override void FromTo(MemoryLiveItem memory)
        {
            base.FromTo(memory);

            InternalFromTo(memory as HotButtonInfo);
        }

        private void InternalFromTo(HotButtonInfo message)
        {

        }

        public override void FromTo(ILockLiveItem locker, int lockCounter)
        {
            base.FromTo(locker, lockCounter);
            InternalFromTo(locker as HotButtonInfo);
        }



        public object[] ToArrayTimeSliceGroupItem()
        {
            //return new object[] { false, Name, Type, LengthText };
            return null;
        }

        public override LiveAdapter ToProxy()
        {
            return new HotButtonAdapterInfo(this);
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
