//---------------------------------------------------------------------
//
// File: LiveCategory.cs
//
// Description:
// LiveCategory class 
//
// Author: Jerry
// Date  : 2009-7-13
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
using System.ComponentModel;

namespace ProWrite.Entity.Live
{
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    public class LiveCategory : MemoryLiveItem, IEquatable<LiveCategory>
    {
        public override string Name
        {
            get
            {
                return base.Name;
            }
            set
            {
                if (value != base.Name)
                {
                    base.Name = value;
                    MessageBus.Send(null, new PWMessage<SessionChangeMessage>(null));
                }
            }
        }

        private List<LiveMessageItem> _items = new List<LiveMessageItem>();
        public LiveMessageItem[] Items
        {
            get
            {
                return _items.ToArray();
            }
        }

        private bool _checkedState = false;
        public bool CheckedState
        {
            set
            {
                _checkedState = value;
            }
            get
            {
                return _checkedState;
            }
        }

        public void AddItems(params LiveMessageItem[] items)
        {
            if (items == null || items.Length == 0)
                return;

            _items.AddRange(items);

            MessageBus.Send(null, new PWMessage<SessionChangeMessage>(null));            
        }

        public void RemoveAllItems()
        {
            //if (_items == null || _items.Count == 0 || items==null || items.Length==0)
            //    return;
            //signs.ForEach(p =>
            //{
            //    _signs.ForEach(p1 =>
            //        {
            //            if (p1.Id == p.Id)
            //            {
            //                _signs.Remove(p1);                            
            //                _changedService.MarkChanged();                            
            //            }
            //        }
            //    );

            //}
            //);
            bool flag = false;

            if (_items.Count > 0)
            {
                _items.Clear();
                flag = true;
            }
            
            if(flag)
                MessageBus.Send(null, new PWMessage<SessionChangeMessage>(null));
        }

        private LiveCategoryViewState _viewState;
        public LiveCategoryViewState ViewState
        {
            set
            {
                _viewState = value;
            }
            get
            {
                return _viewState;
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
            get { return LiveType.LiveCategory; }
        }


        #endregion

        #region Functions define
        #region IEquatable<HotButtonInfo> Members

        public bool Equals(LiveCategory other)
        {
            if (other == null)
                return false;

            if (other.Items.Length != this.Items.Length || this.Id != other.Id)
                return false;

            for(int i = 0; i < other.Items.Length; i++)
            {
                if (this.Items[i].Id != other.Items[i].Id)
                    return false;
            }

            return true;
        }

        #endregion

        public override bool Equals(object obj)
        {
            return Equals(obj as LiveCategory);
        }                

        public override MemoryLiveItem Copy()
        {
            LiveCategory item = NewInstance() as LiveCategory;
            item.FromTo(this);
            return item;

        }

        public override MemoryLiveItem NewInstance()
        {
            return new LiveCategory();
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

            InternalFromTo(memory as LiveCategory);
        }

        private void InternalFromTo(LiveCategory category)
        {
            CopyMessageItems(category.Items);
        }

        public override void FromTo(ILockLiveItem locker, int lockCounter)
        {
            base.FromTo(locker, lockCounter);
            InternalFromTo(locker as LiveCategory);
        }

        public void CopyMessageItems(LiveMessageItem[] items)
        {
            _items.Clear();
            if (items == null || items.Length < 1)
                return;
            foreach (LiveMessageItem item in items)
                _items.Add(item.Copy() as LiveMessageItem);
        }

        public object[] ToArrayTimeSliceGroupItem()
        {
            //return new object[] { false, Name, Type, LengthText };
            return null;
        }

        public override LiveAdapter ToProxy()
        {
            return new LiveCategoryAdapterInfo(this);
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
