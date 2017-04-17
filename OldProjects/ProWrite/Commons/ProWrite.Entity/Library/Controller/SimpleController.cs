//---------------------------------------------------------------------
//
// File: SimpleController.cs
//      
// Description:
//      Simple conterller class
//
// Author: Kevin 2008-7-28
//
// Modify History:
//      Jerry Xu 2009-3-16 update method:Update(T item)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Entity.Library.Controller;
using ProWrite.Core;
using ProWrite.Entity.Library.ImportExport;

namespace ProWrite.Entity.Library.Controller
{
	/// <summary>
	/// Simple controller class
	/// </summary>
	/// <typeparam name="T"></typeparam>
	[Serializable]
	public class SimpleController<T> : ListSet<T>, ILibraryController<T> where T : LibraryItem
	{
		#region ILibraryController Members
        LibraryItem ILibraryController.GetByName(string name)
        {
            return base.GetByName(name);
        }

        LibraryItem ILibraryController.GetById(string id)
        {
            return base.GetById(id);
        }
		/// <summary>
		/// is contains library item
		/// </summary>
		/// <param name="item"></param>
		/// <returns></returns>
		public bool Contains(LibraryItem item)
		{
			return base.Contains(item as T);
		}

		/// <summary>
		/// add library item
		/// </summary>
		/// <param name="item"></param>
		public virtual new bool Add(T item)
		{
			return base.Add(item);
		}

		/// <summary>
		/// remove library item
		/// </summary>
		/// <param name="item"></param>
		/// <returns></returns>
		public virtual new bool Remove(T item)
		{
            MemoryLibraryItem lib = item as MemoryLibraryItem;
            if (lib != null)
                ProjectInfo.Current.Recents.Remove(lib);
			return base.Remove(item);
		}

		/// <summary>
		/// and library item
		/// </summary>
		/// <param name="item"></param>
		public bool Add(LibraryItem item)
		{
			return Add(item as T);
		}

		/// <summary>
		/// remove library item
		/// </summary>
		/// <param name="item"></param>
		/// <returns></returns>
		public bool Remove(LibraryItem item)
		{
			return Remove(item as T);
		}

		/// <summary>
		/// update library item
		/// </summary>
		/// <param name="item"></param>
		public virtual bool Update(T item)
		{
			if (item != null && !string.IsNullOrEmpty(item.Name))
			{
				int length = Count;
				for (int i = 0; i < length; i++)
				{
					if (string.Equals(this[i].Name, item.Name))
					{
                        //this[i].Dispose();
                        //this[i] = null;
                        ILockLibraryItem locker = this[i] as ILockLibraryItem;
                        if (locker != null)
                        {
                            item.Id = this[i].Id;
                            locker.FromTo(item as ILockLibraryItem, locker.LockCount);
                        }
                        else
                            this[i] = item;

                        MessageBus.Send(this,new EntityChangedMessage<T>(new T[]{item},EntityAction.Update));
                        return true;
					}
				}
			}
            return false;
		}

        /// <summary>
		/// update library item
		/// </summary>
		/// <param name="item"></param>
		public bool Update(LibraryItem item)
		{
			return Update(item as T);
		}

		#endregion

		#region IEnumerable<LibraryItem> Members

		public new IEnumerator<LibraryItem> GetEnumerator()
		{
			LibraryItem[] items = this.ToArray();
			foreach(LibraryItem item in items)
				yield return item;
		}

		#endregion
	}
}