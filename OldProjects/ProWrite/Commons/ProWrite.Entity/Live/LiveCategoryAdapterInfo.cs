using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;

namespace ProWrite.Entity.Live
{
    [Serializable]
    public class LiveCategoryAdapterInfo:LiveAdapter
    {
        #region Non Serialized Fields
        #endregion

        #region Serialized Fields
        private bool _isActive = true;
        #endregion

        #region Serialized Fields Version 2
        #endregion

        public LiveCategoryAdapterInfo()
		{
		}

        public LiveCategoryAdapterInfo(LiveCategory message)
            : base(message)
		{
		}

        public LiveCategory Message
		{
            get { return base.Target as LiveCategory; }
		}

		
		/// <summary>
		/// Is active
		/// </summary>
		public bool IsActive
		{
			get { return _isActive; }
			set { _isActive = value; }
		}

        
		public override LiveType Type
		{
            get { return LiveType.LiveCategoryProxy; }
		}

        /// <summary>
        /// Function: Init a new instance of this object
        /// Author  : Jerry Xu
        /// Date    : 2008-7-8 
        /// </summary>
        /// <returns>LibraryAdapter</returns>
        public override LiveAdapter NewInstance()
        {
            return new LiveCategoryAdapterInfo();
        }

        public object[] ToArrayTimeSliceGroupItem(int groupLength)
        {
            if (Target == null || Target.IsEmpty)
                return null;
            return new object[] { IsActive, Target.Name, Formaters.FormatTime(groupLength) };
        }

        public override LiveAdapter Copy()
        {
            LiveCategoryAdapterInfo clone = new LiveCategoryAdapterInfo();
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
        public override void FromTo(LiveAdapter item)
        {
            //this.Caption = memory.Caption;
            if (item != null)
            {
                base.FromTo(item);
                //TODO:
                InternalFromTo(item as LiveCategoryAdapterInfo);
            }
        }

        private void InternalFromTo(LiveAdapter item)
        {
            //TODO:
            if (item != null)
            {
                this.IsActive = (item as LiveCategoryAdapterInfo).IsActive;                
            }
        }
    }
}
