//---------------------------------------------------------------------
//
// File: SignGroupInfo.cs
//
// Description:
// 
//
// Author: Kevin
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// terry 2008-6-23 修改内容：添加GetAllChildGroups和GetAllChildGroupsByGroup方法
//  以及部分注释
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.Xml.Serialization;
using ProWrite.Core;
using ProWrite.Entity.Dashboard;

namespace ProWrite.Entity.Dashboard
{
    [Serializable]
    public class SignGroupInfo : DashboardItem, IEquatable<SignGroupInfo>
    {
        #region Non Serialized Fields
        [NonSerialized]
        static List<SignGroupInfo> list = new List<SignGroupInfo>();

        [NonSerialized]
        private bool _isEmpty;
        #endregion

        #region Serialized Fields
        protected ListSet<SignInfo> _signs = new ListSet<SignInfo>();
        protected ListSet<SignGroupInfo> _groups = new ListSet<SignGroupInfo>();
        private DashboardType _dashboardType = DashboardType.Group;
        #endregion

        public override DashboardType DashboardType
        {
            get { return _dashboardType; }
            set
            {
                if (value != _dashboardType)
                {
                    OnPropertyChanged("DashboardType");
                    _dashboardType = value;
                }
            }
        }

        public SignInfo[] Signs { get { return _signs.ToArray(); } set { _signs = new ListSet<SignInfo>(value); } }
        public SignGroupInfo[] Groups { get { return _groups.ToArray(); } set { _groups = new ListSet<SignGroupInfo>(value); } }

        public SignGroupInfo()
        {
        }

        

        public SignGroupInfo(bool isEmpty)
        {
            _isEmpty = isEmpty;
            Name = "[No Group]";
        }

        public override bool IsEmpty
        {
            get
            {
                if (_isEmpty)
                    return true;
                return base.IsEmpty;
            }
        }

        /// <summary>
        /// Clear signs
        /// </summary>
        public void ClearSigns()
        {
            foreach (SignInfo item in _signs)
                _allSigns.Remove(item);

            _signs.Clear();
        }

        /// <summary>
        /// Clear groups
        /// </summary>
        public void ClearGroups()
        {
            foreach (SignGroupInfo item in _groups)
                _allGroups.Remove(item);

            if (_groups.Count > 0)
            {
                foreach (SignGroupInfo item in _groups)
                {
                    item.Clear();
                }

                _groups.Clear();
            }
        }

        /// <summary>
        /// Clear all signs and groups
        /// </summary>
        public virtual void Clear()
        {
            ClearSigns();
            ClearGroups();
        }

        public bool ContainsSign(SignInfo sign)
        {
            //return _signs.Contains(sign);
            return _allSigns.Contains(sign);
        }

        public bool ContainsGroup(SignGroupInfo group)
        {
            //return _groups.Contains(group);
            return _allGroups.Contains(group);
        }

        private SignGroupInfo GetRootGroup()
        {
            return GetRootGroup(this);
        }

        public static SignGroupInfo GetRootGroup(SignGroupInfo group)
        {
            if (group.IsRoot || group.Parent == null)
                return group;
            if (!group.Parent.IsRoot)
            {
                return GetRootGroup(group.Parent);
            }
            return group;
        }

        /// <summary>
        /// Determine the sign  whether more than 20
        /// </summary>
        /// <param name="group">Group of testing</param>
        /// <returns></returns>
        public static bool IsSignCountValid(SignGroupInfo group)
        {
            if (group == null)
                return false;
            SignInfo[] array = DashboardItem.FindAllSigns(GetRootGroup(group));
            if (array.Length < 20)
            {
                return false;
            }
            return true;
        }

        public bool IsSameSignType(SignInfo sign,SignGroupInfo group)
        {
            SignInfo[] array = DashboardItem.FindAllSigns(group);
            if(array.Length>0)
                return sign.SignInfomation+sign.SignTypeColor == array[0].SignInfomation+array[0].SignTypeColor;
            return true;
        }

        public static int GetChildCountByGroup(SignGroupInfo group)
        {
            if (group == null)
                return 0;
            SignInfo[] array = DashboardItem.FindAllSigns(group);
            return array.Length;
        }

        public static int GetRootChildCountByGroup(SignGroupInfo group)
        {
            if (group == null)
                return 0;
            SignInfo[] array = DashboardItem.FindAllSigns(GetRootGroup(group));
            return array.Length;
        }

        public static bool IsTwoGroupSameRoot(SignGroupInfo group1, SignGroupInfo group2)
        {
            return GetRootGroup(group1) == GetRootGroup(group2);
        }
        public virtual bool IsRoot
        {
            get { return false; }
        }

        public bool Add(DashboardItem item)
        {
            if (item == null)
                return false;


            return item.DashboardType == DashboardType.Group ?AddGroup(item as SignGroupInfo)
                    : AddSign(item as SignInfo);
        }

        public bool AddSign(SignInfo sign)
        {
            bool flg = false;

            if (sign != null
                && !sign.IsEmpty
                && !_allSigns.Contains(sign)
                && !_allGroups.Contains(sign.Name))//&& !_signs.Contains(sign))
            {
                _signs.Add(sign);
                _allSigns.Add(sign);
                sign.Parent = this;
                sign.Parent.Active = true;
                flg = true;
            }

            return flg;
        }

        public bool RemoveSign(SignInfo sign)
        {
            if (sign == null)
                return false;

            sign.Parent = null;
            _allSigns.Remove(sign);
            return _signs.Remove(sign);
        }

        public bool AddGroup(SignGroupInfo group)
        {
            bool flg = false;
            if (group != null
                && !group.IsEmpty
                && !_allGroups.Contains(group) && !_allSigns.Contains(group.Name))//&& !_groups.Contains(group))
            {
                _groups.Add(group);
                _allGroups.Add(group);
                group.Parent = this;
                flg = true;
            }
            return flg;
        }

        public bool Remove(DashboardItem item)
        {
            if (item == null)
                return false;

            return item.DashboardType == DashboardType.Group ?RemoveGroup(item as SignGroupInfo,false)
                    : RemoveSign(item as SignInfo);
        }

        /// <summary>
        /// 删除Group
        /// </summary>
        /// <param name="group">要删除的Group</param>
        /// <returns>删除成功，返回True</returns>
        public bool RemoveGroup(SignGroupInfo group, bool deleteAllSign)
        {
            if (group == null)
                return false;

            group.Parent = null;
            _allGroups.Remove(group);
            if (deleteAllSign)
                group.Clear();
            return _groups.Remove(group);
        }

        /// <summary>
        /// 判断数据库中是否已经包含了传入的Sign
        /// </summary>
        /// <param name="item">传入的Sign</param>
        /// <returns>如果包含，则返回True,否则，返回False</returns>
        public virtual bool Contains(SignInfo item)
        {
            return _allSigns.Contains(item);
        }

        /// <summary>
        /// 判断数据库中是否已经包含了传入的Group
        /// </summary>
        /// <param name="item">传入的Group</param>
        /// <returns>如果包含，则返回True,否则，返回False</returns>
        public virtual bool Contains(SignGroupInfo item)
        {
            return _allGroups.Contains(item);
        }

        #region IEquatable<SignGroupInfo> Members

        public bool Equals(SignGroupInfo other)
        {
            if (other == null)
                return false;
            if (!_signs.Equals(other._signs))
                return false;
            if (!_groups.Equals(other._groups))
                return false;
            return base.Equals(other);
        }

        public override bool Equals(object obj)
        {
            return Equals(obj as SignGroupInfo);
        }

        /// <summary>
        /// 传入一个Group，获取他的所有子Group项
        /// </summary>
        /// <param name="group">传入的Group</param>
        /// <returns>返回符合条件的Group项的列表</returns>
        public static List<SignGroupInfo> GetAllChildGroups(SignGroupInfo group)
        {
            list.Clear();
            GetAllChildGroupsByGroup(group);
            return list;
        }

        /// <summary>
        /// 传入一个Group，获取他的所有子Group项
        /// </summary>
        /// <param name="group">传入的Group</param>
        public static void GetAllChildGroupsByGroup(SignGroupInfo group)
        {
            //group._groups;
            if (group == null)
                return;
            foreach (SignGroupInfo item in group._groups)
            {
                list.Add(item);
                GetAllChildGroupsByGroup(item);
            }

        }

        #endregion

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if (_signs != null)
            {
                _signs.Dispose();
                _signs.Clear();
                _signs = null;
            }
            if (_groups != null)
            {
                foreach (SignGroupInfo item in _groups)
                    item.Dispose(disposing);
                _groups.Clear();
                _groups = null;
            }
        }
    }
}