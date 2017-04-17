//---------------------------------------------------------------------
//
// File: SessionInfo.cs
//
// Description:
// SessionInfo class 
//
// Author: Jerry
// Date  : 2009-7-10
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
using System.Xml.Serialization;
using System.ComponentModel;
using System.Runtime.Serialization;
using ProWrite.Entity.Library;
using ProWrite.Entity.Dashboard;

namespace ProWrite.Entity.Live
{
    [Serializable]
    public class SessionInfo : KeyInfo, IChangedServiceProvider,IEnumerable<LiveItem>
    {
        public SessionInfo()
        {
            InitSession();
        }

        private void SessionInfo_Observers(object sender, SessionChangeMessage msg)
        {
            if(_isActive)
                _changedService.MarkChanged();
        }

        protected SessionInfo(SerializationInfo info, StreamingContext context)
        {
            InitSession();
        }

        private void InitSession()
        {
            if (_signs == null)
                _signs = new List<LiveSign>();

            if (_categories == null)
                _categories = new List<string>();

            if (_lstHotButton == null)
                _lstHotButton = new List<HotButtonItemInfo>();


            if(_changedService == null)
                _changedService = new ChangedService();

            if (_greenAlert == null)
            {
                _greenAlert = new QueueAlertItem();
                _greenAlert.Level = QueueAlertLevel.Green;
            }

            if (_yellowAlert == null)
            {
                _yellowAlert = new QueueAlertItem();
                _yellowAlert.Level = QueueAlertLevel.Yellow;
            }

            if (_redAlert == null)
            {
                _redAlert = new QueueAlertItem();
                _redAlert.Level = QueueAlertLevel.Bottom;
            }

            MessageBus.Subject<SessionChangeMessage>().Observers += new System.Communication.Messaging.ObserverHandler<SessionChangeMessage>(SessionInfo_Observers);
        }

        #region Serialized Fields
        private bool _isActive;        
        #endregion

        #region Non Serialized Fields

        [NonSerialized]
        private int _lockerCounter = 0;
        [NonSerialized]
        private static SessionInfo _current = null;
        [NonSerialized]
        private ChangedService _changedService;
        public ChangedService ChangedService
        {
            get { return _changedService; }
        } 
        #endregion

        #region Properties define
        private bool _isNew = true;
        [XmlIgnore]
        [Browsable(false)]
        public bool IsNew
        {
            get { return _isNew; }
            set { _isNew = value; }
        }

        public override string Name
        {
            get
            {
                return base.Name;
            }
            set
            {
                if (value != null && value != base.Name)
                {
                    base.Name = value;
                    MessageBus.Send(this, new SessionNameChangeMessage(value,true));
                }
            }
        }

        private List<LiveSign> _signs;
        public LiveSign[] SignItems
        {
            get
            {
                return _signs.ToArray();
            }
        }

        public void AddSigns(params LiveSign[] signs)
        {
            if (signs == null || signs.Length == 0)
                return;
            _signs.AddRange(signs);
            _changedService.MarkChanged();
        }

        public void RemoveSigns(params LiveSign[] signs)
        {
            if (_signs == null || _signs.Count == 0 || signs==null || signs.Length==0)
                return;
            bool flag = false;

            foreach (LiveSign sign in signs)
            {
                foreach (LiveSign item in _signs)
                {
                    if (item.Id == sign.Id)
                    {
                        _signs.Remove(sign);
                        flag = true;
                        continue;
                    }                    
                }
            }

            if (flag)
                _changedService.MarkChanged();
        }

        #region Category

        private List<string> _categories;
        public List<string> CategoryIds
        {
            get
            {
                return _categories;
            }
        }

        private void AddCategoriesToLibrary(LiveCategory categories)
        {
            if (categories == null) return;
            ProjectInfo.Current.ListCategories.Add(categories);
        }

        private void AddCategoryToSessionInfo(string categoryId)
        {
            _categories.Add(categoryId);
        }

        private void RemoveCategoriesFromLibrary(LiveCategory category)
        {
            if (ProjectInfo.Current.ListCategories.Count == 0 || category == null)
                return;
            ProjectInfo.Current.ListCategories.Remove(category);
        }

        private void RemoveCategoryFromSessionInfo(string categoryId)
        {
            _categories.Remove(categoryId);
        }

        public void MergeCategoryLibrary(LiveCategory[] categories)
        {
            //TODO:Method define is different method implemention
            ProjectInfo.Current.ListCategories.Clear();
            ProjectInfo.Current.ListCategories.AddRange(categories);
        }

        public void MergeCategoryToSessionInfo(LiveCategory[] categories)
        {
            bool flag = false;
            int newCategoryLength = categories.Length;
            int oldCategoryLength = _categories.Count;
            int loopCount = newCategoryLength > oldCategoryLength ? newCategoryLength : oldCategoryLength;

            for (int i = 0; i < loopCount; i++)
            {
                string oldId = string.Empty;
                string newId = string.Empty;

                if (newCategoryLength > i)
                    newId = categories[i].Id;

                if (oldCategoryLength > i)
                    oldId = _categories[i];

                if (oldId != string.Empty && newId != string.Empty && newId != oldId)
                {
                    _categories[i] = newId;
                    flag = true;
                }
                else if (oldId == string.Empty)
                {
                    AddCategoryToSessionInfo(newId);
                    flag = true;
                }
                else if (newId == string.Empty)
                {
                    RemoveCategoryFromSessionInfo(oldId);
                    flag = true;
                }
            }

            if (flag)
                _changedService.MarkChanged();
        }
        #endregion

        #region HotButton
        
        private List<HotButtonItemInfo> _lstHotButton;

        public HotButtonItemInfo[] HotButtons
        {
            get
            {
                return _lstHotButton.ToArray();
            }
        }

        public void AddHotButton(HotButtonItemInfo[] items)
        {
            if (items.Length > 0)
            {
                _lstHotButton.AddRange(items);
                _changedService.MarkChanged();
            }
        }

        public void RemoveButton(HotButtonItemInfo item)
        {
            if (_lstHotButton.Count > 0)
            {
                if (_lstHotButton.IndexOf(item) != 0)
                {
                    _lstHotButton.Remove(item);
                    _changedService.MarkChanged();
                }
            }
        }

        public void ClearAllHotButton()
        {
            _lstHotButton.Clear();
        }

        #endregion

        private bool _isAlert;
        public bool IsAlert
        {
            get
            {
                return _isAlert;
            }
            set
            {
                if (_isAlert != value)
                {
                    _isAlert = value;
                    _changedService.MarkChanged();
                }
            }
        }

        private QueueAlertItem _greenAlert;
        public QueueAlertItem GreenAlert
        {
            get
            {
                return _greenAlert;
            }
            private set
            {
                _greenAlert = value;
            }
        }

        private QueueAlertItem _yellowAlert;
        public QueueAlertItem YellowAlert
        {
            get
            {
                return _yellowAlert;
            }
            private set
            {
                _yellowAlert = value;
            }
        }

        private QueueAlertItem _redAlert;
        public QueueAlertItem RedALert
        {
            get
            {
                return _redAlert;
            }
            private set
            {
                _redAlert = value;
            }
        }

        private int _autoQueueCounter = 1;
        public int AutoQueueCounter
        {
            set
            {
                if (value != _autoQueueCounter)
                {
                    _autoQueueCounter = value;
                    _changedService.MarkChanged();
                }
            }
            get
            {
                return _autoQueueCounter;
            }
        }

        private bool _isVisibleCounter = true;
        public bool IsVisibleCounter
        {
            set
            {
                if (value != _isVisibleCounter)
                {
                    _isVisibleCounter = value;
                    _changedService.MarkChanged();
                }
            }
            get
            {
                return _isVisibleCounter;
            }
        }

        private bool _isNail = true;
        public bool IsNail
        {
            set
            {
                if (value != _isNail)
                {
                    _isNail = value;
                    _changedService.MarkChanged();
                }
            }
            get
            {
                return _isNail;
            }
        }

        [XmlIgnore]
        [Browsable(false)]
        public bool IsLock
        {
            get { return _lockerCounter > 0; }
            set
            {
                if (value)
                    _lockerCounter++;
                else if (_lockerCounter > 0)
                    _lockerCounter--;
            }
        }

        [XmlIgnore]
        [Browsable(false)]
        public int LockCount
        {
            get { return _lockerCounter; }
        }

        /// <summary>
        /// Current library group
        /// </summary>
        public static SessionInfo Current
        {
            get
            {
                return _current;
            }
            set
            {
                if (_current != null)
                    _current._isActive = false;
                _current = value;
                if (_current != null)
                    _current._isActive = true;
            }

        }

        public MemoryLibraryItem[] MemoryLibraries
        {
            get
            {
                var items = new ListSet<MemoryLibraryItem>();
                SessionCategories.ForEach(cat => cat.Items.ForEach(item => items.Add(item.Target)));
                return items.ToArray();
            }
        }

        public bool UpdateLibraryItemStatus(SignInfo sign)
        {
            var serverLibs = sign.Controller.Connection.ServerLibraries;
            var clientLibs = (from cat in SessionCategories
                              from item in cat.Items
                              select item).ToArray();

            bool hasUpdated = false;
            serverLibs.ForEach(sitem =>
                {
                    var citem = clientLibs.FirstOrDefault(clientItem => clientItem.Id == sitem.Id);
                    if (citem == null)
                    {
                        citem.Status = DataStatus.Deleted;
                        hasUpdated = true;
                    }
                });


            clientLibs.ForEach(item =>
            {
                var sitem = serverLibs.FirstOrDefault(serItem => item.Id == serItem.Id);
                if (sitem == null)
                {
                    item.Status = DataStatus.Created;
                    hasUpdated = true;
                }
                else
                {
                    item.Status = DataStatus.NoChanged;
                    var sModifyTime = DateTime.Parse(sitem.ModifyTime);
                    if (CompareDateTime(item.ModifyTime, sModifyTime))
                    {
                        item.Status = DataStatus.Updated;
                        hasUpdated = true;
                    }
                }
            });

            return hasUpdated;
        }

        private static bool CompareDateTime(DateTime source, DateTime target)
        {
            return source.Year != target.Year
                || source.Month != target.Month
                || source.Day != target.Day
                || source.Hour != target.Hour
                || source.Minute != target.Minute
                || source.Second != target.Second;
        }

        #endregion    
    
        #region Methods define
        /// <summary>
        /// Function: Clone a SessionInfo
        /// Author  : Jerry Xu
        /// Date    : 2008-7-30 
        /// </summary>
        /// <returns>SessionInfo</returns>
        public SessionInfo Copy()
        {
            SessionInfo clone = NewInstance();
            clone.FromTo(this);
            return clone;
        }

        public LiveCategory[] SessionCategories
        {
            get
            {
                return _categories.ConvertAll<LiveCategory>(categoryId => ProjectInfo.Current.ListCategories.First(category => categoryId == category.Id)).ToArray();
            }
        }

        public LiveCategory[] LibraryCategories
        {
            get
            {
                return ProjectInfo.Current.ListCategories.ToArray();
            }
        }

        /// <summary>
        /// Function: Get data from a object to current object
        /// Author  : Jerry Xu
        /// Date    : 2008-7-8 
        /// </summary>
        /// <param name="memory">MemoryLibraryItem</param>
        public void FromTo(SessionInfo memory)
        {
            this.Id = memory.Id;
            this.Name = memory.Name;
            this._isActive = memory._isActive;  
            this._isNail = memory._isNail;
            this._isVisibleCounter = memory._isVisibleCounter;
            this._isNew = memory._isNew;
            this._autoQueueCounter = memory._autoQueueCounter;

            if (memory._signs != null && memory._signs.Count > 0)
                CopySigns(memory.SignItems);
            if (memory._categories != null && memory._categories.Count > 0)
                CopyCategories(memory.SessionCategories);
            if (memory._lstHotButton != null && memory._lstHotButton.Count > 0)
                CopyHotButton(memory.HotButtons);

            this._isAlert = memory._isAlert;
            if (memory._greenAlert != null)
                this._greenAlert = memory._greenAlert.Copy();
            if (memory._yellowAlert != null)
                this._yellowAlert = memory._yellowAlert.Copy();
            if (memory._redAlert != null)
                this._redAlert = memory._redAlert.Copy();
        }

        public void CopySigns(LiveSign[] items)
        {
            _signs.Clear();
            if (items == null || items.Length < 1)
                return;
            foreach (LiveSign item in items)
                _signs.Add(item.Copy() as LiveSign);
        }

        public void CopyCategories(LiveCategory[] items)
        {
            _categories.Clear();
            if (items == null || items.Length < 1)
                return;
            foreach (LiveCategory item in items)
                _categories.Add(item.Id);
        }

        public void CopyHotButton(HotButtonItemInfo[] items)
        {
            _lstHotButton.Clear();
            if (items == null || items.Length < 1)
                return;
            foreach (HotButtonItemInfo item in items)
                _lstHotButton.Add(item);
        }

        public SessionInfo NewInstance()
        {
            return new SessionInfo();
        }



        #region IEnumerable<LiveItem> Members
        public IEnumerator<LiveItem> GetEnumerator()
        {
            //foreach (LibraryItem item in _images)
            //    yield return item;
            //foreach (LibraryItem item in _videos)
            //    yield return item;
            //foreach (LibraryItem item in _messages)
            //    yield return item;
            //foreach (LibraryItem item in _playlists)
            //    yield return item;
            //foreach (LibraryItem item in _timeSliceGroups)
            //    yield return item;
            //foreach (LibraryItem item in _schedulers)
            //    yield return item;
            return null;
        }

        #endregion

        #region IEnumerable Members
        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
        #endregion

        public override string ToString()
        {
            return base.Name;
        }

        #region IEquatable<HotButtonInfo> Members

        //public bool Equals(SessionInfo other)
        //{
        //    if (other == null)
        //        return false;

        //    return true;
        //}

        //#endregion

        //public override bool Equals(object obj)
        //{
        //    return Equals(obj as SessionInfo);
        //}

        //public override LiveItem NewInstance()
        //{
        //    return new SessionInfo();
        //}

        #region Fine methods
        //public bool Contains(LibraryItem item)
        //{
        //    if (item == null || !Controllers.ContainsKey(item.Type))
        //        return false;
        //    return controllers[item.Type].Contains(item);
        //}

        //public LibraryItem GetByName(string name, LibraryType type)
        //{
        //    if (!Controllers.ContainsKey(type))
        //        return null;
        //    return controllers[type].GetByName(name);
        //}

        //public LibraryItem GetById(string id, LibraryType type)
        //{
        //    if (!Controllers.ContainsKey(type))
        //        return null;
        //    return controllers[type].GetById(id);
        //}

        //public MemoryLibraryItem GetById(string id)
        //{
        //    if (string.IsNullOrEmpty(id))
        //        return null;

        //    if (_messages.ContainsById(id))
        //        return _messages.GetById(id);

        //    if (_timeSliceGroups.ContainsById(id))
        //        return _timeSliceGroups.GetById(id);

        //    if (_playlists.ContainsById(id))
        //        return _playlists.GetById(id);

        //    return null;
        //}

        //public bool Contains(string name, LibraryType type)
        //{
        //    if (!Controllers.ContainsKey(type))
        //        return false;
        //    return controllers[type].Contains(name);
        //}
        #endregion
        #endregion

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            _changedService = null;
        }

      
        #endregion
             
    }
}
