//---------------------------------------------------------------------
//
// File: ILibraryController.cs
//      
// Description:
//      Library conterller interface
//
// Author: Kevin 2008-7-28
//
// Modify History:
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;

namespace ProWrite.Entity.Library.Controller
{
	/// <summary>
	/// Library controller interface
	/// </summary>
	public interface ILibraryController:IEnumerable<LibraryItem>
	{
        LibraryItem GetByName(string name);
        LibraryItem GetById(string id);
		/// <summary>
		/// and library item
		/// </summary>
		/// <param name="item"></param>
		bool Add(LibraryItem item);
		/// <summary>
		/// remove library item
		/// </summary>
		/// <param name="item"></param>
		/// <returns></returns>
		bool Remove(LibraryItem item);
		/// <summary>
		/// update library item
		/// </summary>
		/// <param name="item"></param>
		bool Update(LibraryItem item);
		/// <summary>
		/// is contains library item
		/// </summary>
		/// <param name="item"></param>
		/// <returns></returns>
		bool Contains(LibraryItem item);

        bool Contains(string name);

        bool Rename(string newName, string oldName);
	}

	/// <summary>
	/// Generic library controller interface
	/// </summary>
	/// <typeparam name="T"></typeparam>
	public interface ILibraryController<T> : ILibraryController where T : LibraryItem
	{
        new T GetByName(string name);
        new T GetById(string id);
		/// <summary>
		/// and library item
		/// </summary>
		/// <param name="item"></param>
		bool Add(T item);
		/// <summary>
		/// remove library item
		/// </summary>
		/// <param name="item"></param>
		/// <returns></returns>
		bool Remove(T item);
		/// <summary>
		/// update library item
		/// </summary>
		/// <param name="item"></param>
		bool Update(T item);
		/// <summary>
		/// is contains library item
		/// </summary>
		/// <param name="item"></param>
		/// <returns></returns>
		bool Contains(T item);
	}

	/// <summary>
	/// Library event args class
	/// </summary>
	public class LibraryEventArgs : EventArgs
	{
		public readonly LibraryItem Item;
		public LibraryEventArgs(LibraryItem item)
		{
			Item = item;
		}
	}
}