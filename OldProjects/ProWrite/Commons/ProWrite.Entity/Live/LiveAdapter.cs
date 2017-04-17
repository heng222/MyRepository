using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using ProWrite.Core;
using System.Xml.Serialization;

namespace ProWrite.Entity.Live
{
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    public abstract class LiveAdapter : LiveItem
    {
        #region Non Serialized Fields
        [NonSerialized]
        protected MemoryLiveItem _target;
        #endregion

        #region Serialized Fields
        private string _targetName;
        //[OptionalField]
        protected string _targetId;
        #endregion

        #region Serialized Fields Version 2
        #endregion
        
		public LiveAdapter()
		{
			base.Name = KeyGenerator.Library.ToString();
		}

		public LiveAdapter(MemoryLiveItem target)
		{
			base.Name = KeyGenerator.Library.ToString();
			SetTarget(target);
		}

        private void SetTarget(MemoryLiveItem target)
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
		public virtual MemoryLiveItem Target
		{
			get 
            { 
                if(_target!=null)
                    return _target;
                LiveType targetType = LiveType.HotButton;
                switch (Type)
                {
                    case LiveType.HotButtonProxy:
                        targetType = LiveType.HotButton;
                        break;
                    case LiveType.HotButtonItem:
                        targetType = LiveType.HotButtonItemProxy;
                        break;
                    case LiveType.LiveCategory:
                        targetType = LiveType.LiveCategoryProxy;
                        break;
                    case LiveType.LiveMessage:
                        targetType = LiveType.LiveMessageProxy;
                        break;
                    case LiveType.LiveSign:
                        targetType = LiveType.LiveSignProxy;
                        break;
                }
                //_target = SessionInfo.Current.GetById(_targetId, targetType) as MemoryLibraryItem;
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
        public virtual LiveAdapter Copy()
        {
            LiveAdapter clone = NewInstance();
            clone.FromTo(this);
            return clone;
        }

        /// <summary>
        /// Function: Init a new instance of this object
        /// Author  : Jerry Xu
        /// Date    : 2008-7-8 
        /// </summary>
        /// <returns>LibraryAdapter</returns>
        public abstract LiveAdapter NewInstance();

        /// <summary>
        /// Function: Get data from a object to current object
        /// Author  : Jerry Xu
        /// Date    : 2008-7-8 
        /// </summary>
        /// <param name="memory">LibraryAdapter</param>
        public virtual void FromTo(LiveAdapter item)
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
