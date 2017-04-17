//---------------------------------------------------------------------
//
// File: HotButtonItemInfo.cs
//
// Description:
// HotButtonItemInfo class 
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
    public enum MainHotKey
    {
        Ctrl,
        Alt
    }

    public enum SubHotKey
    {
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
    }

    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    public class HotButtonItemInfo : MemoryLiveItem, IEquatable<HotButtonItemInfo>
    {
        #region Properties define

        //public Image NailImage;
        //public bool IsNail;

        public LiveSign[] Sign;
        public MainHotKey MainHotKey;
        public SubHotKey SubHotKey;
        public Color ButtonBackColor;
        public bool IsLarge;
        public string ButtonName;

        #endregion

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
            get { return LiveType.HotButtonItem; }
        }


        #endregion

        #region Functions define
        #region IEquatable<HotButtonInfo> Members

        public bool Equals(HotButtonItemInfo other)
        {
            if (other == null)
                return false;

            return true;
        }

        #endregion

        public override bool Equals(object obj)
        {
            return Equals(obj as HotButtonItemInfo);
        }

        public override MemoryLiveItem NewInstance()
        {
            return new HotButtonItemInfo();
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

            InternalFromTo(memory as HotButtonItemInfo);
        }

        private void InternalFromTo(HotButtonItemInfo message)
        {

        }

        public override void FromTo(ILockLiveItem locker, int lockCounter)
        {
            base.FromTo(locker, lockCounter);
            InternalFromTo(locker as HotButtonItemInfo);
        }



        public object[] ToArrayTimeSliceGroupItem()
        {
            //return new object[] { false, Name, Type, LengthText };
            return null;
        }

        public override LiveAdapter ToProxy()
        {
            return new HotButtonItemAdapterInfo(this);
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
