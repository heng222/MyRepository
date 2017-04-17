//---------------------------------------------------------------------
//
// File: KeyInfo.cs
//
// Description:
// 
//
// Author: Kevin
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.Xml.Serialization;
using ProWrite.Core;
using System.Runtime.Serialization;

namespace ProWrite.Core
{
    public class EntityNameChangeEventArgs : EventArgs
    {
        public readonly string NewValue;
        public readonly string OldValue;
        public readonly IKeyInfo Entity;
        public bool Cancel;

        public EntityNameChangeEventArgs(IKeyInfo entity, string newValue, string oldValue)
        {
            Entity = entity;
            NewValue = newValue;
            OldValue = oldValue;
        }
    }

    public delegate void EntityNameChangedDelegate(EntityNameChangeEventArgs e);

    public class ErrorProperty
    {
        public string Name { get; set; }
        public object OldValue { get; set; }
    }

    public interface IErrorInfo
    {
        ErrorProperty Error { get; set; }

    }

    public interface IKeyInfo : IDisposable,  INotifyPropertyChanged, IEditableObject, IChangeTracking
    {
        event EntityNameChangedDelegate NameChanged;

        string Id { get; }
        string OldName { get; }
        string Name { get; set; }
        bool IsEmpty { get; }
        bool IsEdit { get; }
    }

    /// <summary>
    /// Base class of entity class
    /// </summary>
    [Serializable]
    public class KeyInfo : DisposableObject, IKeyInfo,IEquatable<KeyInfo>, IComparable<KeyInfo>, IComparable
    {
        private int hashcode;
        private int _editLevel;

        public KeyInfo()
        {
            Id = Guid.NewGuid().ToString();
        }

        protected KeyInfo(SerializationInfo info, StreamingContext context)
        {
        }

        [NonSerialized]
        [XmlIgnore]
        private EntityNameChangedDelegate _nameChanged;
        public event EntityNameChangedDelegate NameChanged
        {
            add { _nameChanged += value; }
            remove { _nameChanged -= value; }
        }

        protected virtual bool CancelNameChanged(string newValue)
        {
            if (_nameChanged != null)
            {
                EntityNameChangeEventArgs e = new EntityNameChangeEventArgs(this, newValue, _name);
                _nameChanged(e);
                return e.Cancel;
            }

            return false;
        }

        [NonSerialized]
        [XmlIgnore]
        private string _oldName;

        [Browsable(false)]
        public string OldName
        {
            get { return _oldName; }
        }

        private bool _isChanged;

        /// <summary>
        /// Judge whether data is changed
        /// </summary>
        [Browsable(false)]
        public virtual bool IsChanged
        {
            get { return _isChanged; }
        }

        /// <summary>
        /// Accept change
        /// </summary>
        public virtual void AcceptChanges()
        {
            _isChanged = false;
        }

        private string _name;

        /// <summary>
        /// Get or set  Name properties
        /// Name properties is primary  key of entity class and it is exclusive
        /// </summary>
        public virtual string Name
        {
            get
            {
                return _name;
            }
            set
            {
                if (_name != value)
                {
                    if (!CancelNameChanged(value))
                    {
                        OnPropertyChanged("Name");
                        _oldName = _name;
                        _name = value;
                        hashcode = GenerateHashCode();
                    }

                }
            }
        }

        private string _id;
        [Browsable(false)]
        [XmlIgnore]
        public string Id
        {
            get { return _id; }
            set
            {
                if (_id != value)
                    _id = value.Replace("-","");
            }
        }

        [Browsable(false)]
        public bool IsEdit
        {
            get { return _editLevel > 0; }
        }

        #region IEditableObject Members

        public void BeginEdit()
        {
            _editLevel++;
        }

        public void CancelEdit()
        {
            _editLevel--;
        }

        public void EndEdit()
        {
            _editLevel--;
        }

        #endregion

        [NonSerialized]
        [XmlIgnore]
        private PropertyChangedEventHandler _propChangedEvent;
        /// <summary>
        /// Properties change event 
        /// </summary>
        [Browsable(false)]
        public event PropertyChangedEventHandler PropertyChanged
        {
            add { _propChangedEvent += value; }
            remove { _propChangedEvent -= value; }
        }

        protected virtual void OnPropertyChanged(string propertyName)
        {
            _isChanged = true;
            if (IsEdit)
                return;
            if (_propChangedEvent != null)
                _propChangedEvent(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
        }

        /// <summary>
        /// Indicate whether it is empty object 
        /// </summary>
        [Browsable(false)]
        public virtual bool IsEmpty
        {
            get { return string.IsNullOrEmpty(_name); }
        }

        protected override void Dispose(bool disposing)
        {
            _name = null;
            _nameChanged = null;
            _propChangedEvent = null;
            base.Dispose(disposing);
        }

        public override string ToString()
        {
            return Name;
        }

        public int CompareTo(KeyInfo other)
        {
            if (other == null)
                return 1;
            return string.Compare(_name, other.Name);
        }

        public int CompareTo(object obj)
        {
            return CompareTo((KeyInfo)obj);
        }

        public bool Equals(KeyInfo other)
        {
            return other == null ?
                false
                : _id == other.Id || string.Equals(_name, other.Name);
        }

        public override bool Equals(object obj)
        {
            if  (ReferenceEquals(this, obj)) return true;

            KeyInfo other = obj as KeyInfo;
            if (other == null)
                return false;
            return Equals(other);
        }

        public override int GetHashCode()
        {
            return hashcode;
        }

        private int GenerateHashCode()
        {
            if (_name != null)
                return _id.GetHashCode() ^ _name.GetHashCode();
            else
                return _id.GetHashCode();
        }




       
    }

    public static class ListExtensions
    {
        public static bool ContainsById<T>(this List<T> items, string id) where T : IKeyInfo
        {
            return items.Find(p => { return p.Id == id; }) != null;
        }

        public static bool Contains<T>(this List<T> items, T item) where T : IKeyInfo
        {
            if (item == null
                || item.IsEmpty) return false;

            return items.Find(p => { return p.Id == item.Id || p.Name == item.Name; }) != null;
        }

        public static bool ContainsByName<T>(this List<T> items, string name) where T : IKeyInfo
        {
            if (string.IsNullOrEmpty(name)
                || items.Count == 0)
                return false;

            return items.Find(p => { return p.Name == name; }) != null;
        }

        public static T GetByName<T>(this List<T> items, string name) where T : IKeyInfo
        {
            return items.Find(p => { return p.Name == name; });
        }

        public static T GetById<T>(this List<T> items, string id) where T : IKeyInfo
        {
            return items.Find(p => { return p.Id == id; });
        }

    }
}