//---------------------------------------------------------------------
//
// File: ListSet.cs
//
// Description:
// 
//
// Author: Kevin
//
// Modify Histories:
//      Jerry Xu 2009-5-6 Update method:Remove(T item)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Serialization;
using ProWrite.Core;
using System.Linq;

namespace ProWrite.Core
{
	public enum EntityAction
	{
		Add,
		Delete,
        Update,
	}

	public class EntityChangedMessage<T> : PWMessage where T : IKeyInfo
	{
		public readonly T Entity;
		public readonly T[] Entities;

		public readonly EntityAction Action;

		public EntityChangedMessage(T[] entities, EntityAction action)
		{
			Entities = entities;
			Entity = Entities[0];
			Action = action;
		}
	}

    /// <summary>
    /// Not allow repeat list class
    /// </summary>
    /// <typeparam name="T"></typeparam>
    [Serializable]
    public class ListSet<T> : List<T>, IDisposable, IEquatable<ListSet<T>> where T : IKeyInfo
    {

        [NonSerialized]
        [XmlIgnore]
        private EntityNameChangedDelegate _entityNameChanged;
        public event EntityNameChangedDelegate EntityNameChanged
        {
            add { _entityNameChanged += value; }
            remove { _entityNameChanged -= value; }
        }

        public ListSet()
        {
        }

        public ListSet(IEnumerable<T> collection)
        {
            AddRange(collection);
        }

        protected virtual bool CancelNameChanged(EntityNameChangeEventArgs e)
        {
            if (_entityNameChanged != null)
            {
                _entityNameChanged(e);
                return e.Cancel;
            }

            return false;
        }

        private void OnEntityAdded(params T[] items)
        {
             MessageBus.Send(this, new EntityChangedMessage<T>(items, EntityAction.Add));
        }

        private void OnEntityDeleted(params T[] items)
        {
             MessageBus.Send(this, new EntityChangedMessage<T>(items, EntityAction.Delete));
        }

        public bool HasChanged
        {
            get
            {
                if (Count < 1)
                    return false;
                foreach (T item in this)
                {
                    if (item.IsChanged)
                        return true;
                }
                return false;
            }
        }

        public void AcceptChanges()
        {
            if (Count < 1)
                return;

            foreach (T item in this)
                item.AcceptChanges();
        }

        public new virtual bool Contains(T item)
        {
            if (item == null
                || item.IsEmpty) return false;
            return Find(p =>p.Name == item.Name || p.Id == item.Id) != null;
        }

        public virtual bool Contains(string name)
        {
            if (string.IsNullOrEmpty(name)
                || Count == 0)
                return false;

            return Find(p => p.Name == name) != null;
        }

        public bool ContainsById(string id)
        {
            if (string.IsNullOrEmpty(id)
                || Count == 0)
                return false;

            return Find(p => p.Id == id) != null;
        }

        public virtual T GetByName(string name)
        {
            return Find(p =>p.Name == name);
        }

        public T GetById(string id)
        {
            return Find(p => p.Id == id);
        }

        public virtual bool Rename(string newName, string oldName)
        {
            if (string.IsNullOrEmpty(newName) || newName == oldName)
                return false;

            T item = GetByName(oldName);
            if (item == null)
                return false;

            item.Name = newName;
            return true;
        }

        public new bool Add(T item)
        {
            if (!Contains(item.Name)
                && !string.IsNullOrEmpty(item.Name))
            {
                base.Add(item);
                OnEntityAdded(item);
                item.NameChanged += new EntityNameChangedDelegate(item_NameChanged);
                
                return true;
            }
            return false;
        }

        void item_NameChanged(EntityNameChangeEventArgs e)
        {
            if (e.NewValue == null)
            {
                e.Cancel = true;
                return;
            }

            if (Contains(e.NewValue))
            {
                e.Cancel = true;
                return;
            }

            if (CancelNameChanged(e))
                return;
        }

        public new void AddRange(IEnumerable<T> items)
        {
            if (items != null)
            {
                List<T> added = new List<T>();
                foreach (T item in items)
                {
                    if (!Contains(item.Name))
                        added.Add(item);
                }
                if (added.Count > 0)
                {
                    foreach (T item in added)
                    {
                        base.Add(item);
                        item.NameChanged += new EntityNameChangedDelegate(item_NameChanged);
                    }

                    OnEntityAdded(added.ToArray());
                }
            }
        }

        public new bool Remove(T item)
        {
            //when remove item ,temp delete code contains
            //if (base.Count < 1 || !Contains(item))
            //  return false;
            if (base.Count < 1)
                return false;
            else
            {
                int index = IndexOf(item);
                if (index == -1)
                    return false;
                base.RemoveAt(index);
                OnEntityDeleted(item);
                item.NameChanged -= item_NameChanged;
                return true;
            }
        }

        public new int IndexOf(T item)
        {
            int length = base.Count;
            for (int i = 0; i < length; i++)
            {
                if (base[i].Name == item.Name)
                    return i;
            }
            return -1;
        }

        public new int RemoveAll(Predicate<T> match)
        {
            if (match == null || base.Count < 1)
                return -1;

            List<T> deleted = new List<T>();
            foreach (T item in this)
            {
                if (match(item))
                    deleted.Add(item);
            }

            int ret = 0;
            if (deleted.Count > 0)
            {
                foreach (T item in deleted)
                {
                    int index = base.IndexOf(item);
                    if (index != -1)
                    {
                        base.RemoveAt(index);
                        item.NameChanged -= item_NameChanged;
                    }
                }

                OnEntityDeleted(deleted.ToArray());
                ret = deleted.Count;
                deleted.Clear();
                deleted = null;
            }

            return ret;
        }

        public new void RemoveAt(int index)
        {
            if (index < 0 || index >= Count)
                return;
            T item = base[index];

            if (item != null)
            {
                base.RemoveAt(index);
                item.NameChanged -= item_NameChanged;
                OnEntityDeleted(item);
                item = default(T);
            }

        }
        public new void RemoveRange(int index, int count)
        {
            List<T> deleted = base.GetRange(index, count);
            if (deleted != null && deleted.Count > 0)
            {
                base.RemoveRange(index, count);
                foreach (T item in deleted)
                {
                    item.NameChanged -= item_NameChanged;
                }

                OnEntityDeleted(deleted.ToArray());
            }
        }

        #region IEquatable<ListSet<T>> Members

        public bool Equals(ListSet<T> other)
        {
            if (other == null)
                return false;
            if (Count != other.Count)
                return false;

            int count = Count;
            for (int i = 0; i < count; i++)
            {
                if (!other[i].Equals(this[i]))
                    return false;
            }
            return true;
        }

        public override bool Equals(object obj)
        {
            return Equals(obj as ListSet<T>);
        }
        #endregion

        public static bool Equals(ListSet<T> first, ListSet<T> second)
        {
            if (object.Equals(null, first))
            {
                if (object.Equals(null, second))
                    return true;
                return false;
            }
            else
            {
                return first.Equals(second);
            }
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        private bool disposed = false;

        ~ListSet()
        {
            Dispose(false);
        }

        #region IDisposable Members

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        #endregion


        protected bool IsDisposed
        {
            get
            {
                return disposed;
            }
        }

        protected virtual void Dispose(bool disposing)
        {
            disposed = disposing;
            //int length = Count;
            //if (length > 0)
            //{
            //    T[] items = base.ToArray();
            //    for (int i = length - 1; i > 0; i--)
            //    {
            //        if (null != items[i])
            //            items[i].Dispose();
            //    }
            //    Clear();
            //    _map = null;
            //    _entityNameChanged = null;
            //}
        }

    }
}