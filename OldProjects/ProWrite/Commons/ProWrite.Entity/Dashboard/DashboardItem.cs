//---------------------------------------------------------------------
//
// File: DashboardItem.cs
//
// Description:
// DashboardItem abstract class
//
// Author: Kevin
//  Modify Histories:
//      Jerry Xu 2009-7-14 Add method:GetSignById(string id)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Serialization;
using ProWrite.Core;
using System.Drawing;
using ProWrite.UFE;

namespace ProWrite.Entity.Dashboard
{
	/// <summary>
	/// DashboardItem abstract class
	/// </summary>
	[Serializable]
	public abstract class DashboardItem : KeyInfo,IEquatable<DashboardItem>
    {
        #region Non Serialized Fields
        //Note all Sign in Dash Tree
        [NonSerialized]
		public static ListSet<SignInfo> _allSigns = new ListSet<SignInfo>();

        //Note all Group in Dash Tree
        [NonSerialized]
        public static ListSet<SignGroupInfo> _allGroups = new ListSet<SignGroupInfo>();

        [NonSerialized]
        [XmlIgnore]
        private EventHandler<DashboardAddEventArgs> _dashboardAdding;

        [NonSerialized]
        [XmlIgnore]
        private EventHandler<DashboardAddEventArgs> _dashboardAdded;

        [NonSerialized]
        [XmlIgnore]
        private SignGroupTree _Tree;
        #endregion

        static DashboardItem()
		{
			_allSigns.EntityNameChanged += new EntityNameChangedDelegate(_allSigns_EntityNameChanged);
			_allGroups.EntityNameChanged += new EntityNameChangedDelegate(_allGroups_EntityNameChanged);
		}

		//Dashbaord name changed event
		static void _allGroups_EntityNameChanged(EntityNameChangeEventArgs e)
		{
			// Cancel change if there is Group Name in global Group 
			if (_allGroups.Contains(e.NewValue))
			{
				e.Cancel = true;
			}
		}

		//Dashbaord name changed event
		static void _allSigns_EntityNameChanged(EntityNameChangeEventArgs e)
		{
			//Cancel change if there is Sign Name in global Sign 
			if (_allSigns.Contains(e.NewValue))
			{
				e.Cancel = true;
			}
        }

        #region Serialized Fields
        private bool _active;
        private string _parentName;
        private SignGroupInfo _parent;
        #endregion

        /// <summary>
		/// Get all Sign
		/// </summary>
		public static SignInfo[] AllSigns { get { return _allSigns.ToArray(); } }

		public static SignInfo[] FindAllSigns(SignGroupInfo group)
		{
			List<SignInfo> signs = new List<SignInfo>();
			PopulateSigns(group, signs);
			return signs.ToArray();
		}

		private static void PopulateSigns(SignGroupInfo group, List<SignInfo> signs)
		{
			if (group == null || group.IsEmpty /*|| group.Signs.Length == 0*/)
				return ;

			if (group.Signs.Length > 0)
				signs.AddRange(group.Signs);

			if (group.Groups.Length > 0)
			{
				foreach (SignGroupInfo item in group.Groups)
					PopulateSigns(item, signs);
			}
		}

		private static void PopulateGroups(SignGroupInfo group, List<SignGroupInfo> groups)
		{
			if (group == null || group.IsEmpty || group.Groups.Length == 0)
				return;
			groups.AddRange(group.Groups);

			if (group.Groups.Length > 0)
			{
				foreach (SignGroupInfo item in group.Groups)
					PopulateGroups(item, groups);
			}
		}

		public static SignGroupInfo[] FindAllGroups(SignGroupInfo group)
		{
			List<SignGroupInfo> groups = new List<SignGroupInfo>();
			PopulateGroups(group, groups);
			return groups.ToArray();
		}

		/// <summary>
		/// Get all Group
		/// </summary>
		public static SignGroupInfo[] AllGroups { get { return _allGroups.ToArray(); } }

		/// <summary>
		/// Get all active Sign
		/// </summary>
		public static SignInfo[] ActiveSigns
		{
			get
			{
				return _allSigns.FindAll(delegate(SignInfo item) { return item.Active == true; }).ToArray();
			}
		}

		/// <summary>
		/// Get appointed sign by sign name 
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		public static SignInfo GetSignByName(string name)
		{
			return _allSigns.GetByName(name);
		}

        /// <summary>
        /// Get appointed sign by sign name 
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public static DashboardItem GetSignById(string id)
        {
            if (_allSigns.ContainsById(id))
                return _allSigns.GetById(id);
            else
                return _allGroups.GetById(id);
        }

		/// <summary>
		///  Get appointed sign by Group name 
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		public static SignGroupInfo GetGroupByName(string name)
		{
			return _allGroups.GetByName(name);
		}

		
		/// <summary>
		/// Get or set current Dashboard's active state
		/// </summary>
		public bool Active
		{
			get
			{
				return _active;
			}
			set
			{
				if (value != _active)
				{
					OnPropertyChanged("Active");
					_active = value;
				}
			}
		}

        public SignType _type;
        public SignType Type
        {
            get 
            {
                //if (DashboardType == DashboardType.Group)
                //    return SignType.GroupType;
                return _type;
            }
            set
            {
                
                if (value != _type)
                {
                    if (DashboardType == DashboardType.Group)
                    {
                        //_type = SignType.GroupType;
                        OnPropertyChanged("Type");
                        return;
                    }
                    OnPropertyChanged("Type");
                    _type = value;
                }
            }
        }

        private int _freeMemory = 70;
        public int FreeMemory
        {
            get
            {
                if (DashboardType != DashboardType.Sign)
                    return 0;
                if (IsConnected == "Disconnected")
                    return 0;

                return _freeMemory;

            }
            set { _freeMemory = value; }
        }

        //private string _freeMemory1 = "N/A";
        //public string FreeMemory1
        //{
        //    get
        //    {
        //        if (DashboardType != DashboardType.Sign)
        //            return "--";
        //        if (IsConnected == "Disconnected")
        //            return "N/A";

        //        return _freeMemory1;

        //    }
        //    set { _freeMemory1 = value; }
        //}

        private int _totalSize = 50;
        public int TotalSize
        {
            get 
            {
                if (DashboardType == DashboardType.Sign)
                    return _totalSize;
                else
                    return 0;
            }
            set { _totalSize = value; }
        }

        private string _status = "yellow";
        public string Status
        {
            get
            {
                if (DashboardType == DashboardType.Sign)
                    return _status;
                else
                    return "";
            }
            set { _status = value; }
        }

        //private Image _status = Image.FromFile(
        //public string Status
        //{
        //    get { return _status; }
        //    set { _status = value; }
        //}

        private string _logView = "Double click to show details";
        public string ShowLogView
        {
            get 
            {
                if (DashboardType == DashboardType.Sign)
                    return _logView;
                else
                    return "";
            }
            set {_logView = value; }
        }


        public string SignInfomation
        {
            get;
            set;
        }

        public string SignTypeColor
        {
            get
            {
                if (DashboardType == DashboardType.Group)
                    return "--";
                return _type.ToString() ;
            }
        }

        private string _messageIdInfo;
        public string MessageIdInfo
        {
            get
            {
                if (DashboardType != DashboardType.Sign)
                    return "--";
                if (IsConnected == "Disconnected")
                    return "N/A";
                return _messageIdInfo;
            }
            set
            {
                _messageIdInfo = value;
            }
        }

        private string _messageStatus;
        public string MessageStatus
        {
            get
            {
                if (DashboardType != DashboardType.Sign)
                    return "--";
                if (IsConnected == "Disconnected")
                    return "N/A";
                return _messageStatus;
            }
            set
            {
                _messageStatus = value;
            }
        }

        private string _isConnected;
        public string IsConnected
        {
            get
            {
                if (DashboardType == DashboardType.Sign)
                {
                    var con = (this as SignInfo).Controller.Connection;

                    if (con.State != System.Communication.ConnectionState.Opened)
                        return "Disconnected";

                    if (_isConnected != null)
                        return _isConnected;
                    
                    if (con.User.Status == UserStatus.Online || con.State == System.Communication.ConnectionState.Opened)
                    {
                        return "Connected";
                    }
                    else
                        return "Disconnected";
                }
                else
                    return "--";
            }
            set
            {
                _isConnected = value;
            }
        }

		public class DashboardAddEventArgs : EventArgs
		{
			public readonly SignGroupInfo Parent;
			public bool Cancel;
			public DashboardAddEventArgs(SignGroupInfo group)
			{
				Parent = group;
			}
		}

		
		public event EventHandler<DashboardAddEventArgs> DashboardAdding
		{
			add { _dashboardAdding += value; }
			remove { _dashboardAdding -= value; }
		}
		public event EventHandler<DashboardAddEventArgs> DashboardAdded
		{
			add { _dashboardAdded += value; }
			remove { _dashboardAdded -= value; }
		}

		private bool OnDashboardAdding(SignGroupInfo parent)
		{
			if (_dashboardAdding != null)
			{
				DashboardAddEventArgs e = new DashboardAddEventArgs(parent);
				_dashboardAdding(this, e);
				return e.Cancel;
			}
			return false;
		}

		private void OnDashboardAdded(SignGroupInfo parent)
		{
			if (_dashboardAdded != null)
			{
				DashboardAddEventArgs e = new DashboardAddEventArgs(parent);
				_dashboardAdded(this, e);
			}
		}

		
		[XmlIgnore]//Add [XmlIgnore] by william
		public string ParentName
		{
			get 
			{
				if (_parentName == "SignGroupTree"||_parentName =="")
					return "[No Group]";
				return _parentName; 
			}
			set
			{
				//if (value == "[No Group]")
				//    value = null;

				if ( (value == null && _parentName == null) 
				     || value != _parentName )
				{
					if (_parent != null && _parent != Tree)
						_parent.Remove(this);

					SignGroupInfo tmpParent = GetGroupByName(value);

					if (OnDashboardAdding(tmpParent))
						return;

					_parent = tmpParent;
					OnPropertyChanged("ParentName");
					_parentName = value;
					if (_parent != null)
						_parent.Add(this);
					else
						Tree.Add(this);


					OnDashboardAdded(_parent);
                   
				}
			}
		}

		
        
		/// <summary>
		/// Get root object of current node 
		/// </summary>
		[XmlIgnore]
		public SignGroupTree Tree
		{
			get { return _Tree; }
			internal set { _Tree = value; }
		}

        public virtual object[] ItemArray { get { return new object[] { Name, DashboardType, SignTypeColor, Active, SignInfomation, FreeMemory, IsConnected, MessageIdInfo, MessageStatus, Status, ShowLogView, TotalSize }; } }

		/// <summary>
		/// Get Dashbaord Type
		/// </summary>
        public abstract DashboardType DashboardType { get; set; }


		
		[XmlIgnore]
		public SignGroupInfo Parent
		{
			get { return _parent; }
			set
			{
				if (_parent != value)
				{
					if (_parent != null && value != null)
						_parent.Remove(this);

					_parent = value;
					OnPropertyChanged("Parent");
					if (_parent != null)
					{
						_parentName = _parent.Name;
						_parent.Add(this);
					}
					else
						_parentName = null;
                   
				}
			}
		}

		public bool Equals(DashboardItem other)
		{
			if (other == null)
				return false;
			if (Active != other.Active)
				return false;
			if (DashboardType != other.DashboardType)
				return false;
			if (_parent != other._parent)
				return false;
			return base.Equals(other);
		}

		public override bool Equals(object obj)
		{
			return Equals(obj as DashboardItem);
		}

		public override int GetHashCode()
		{
			return base.GetHashCode();
		}

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            _dashboardAdding = null;
            _dashboardAdded = null;
        }

	}
}