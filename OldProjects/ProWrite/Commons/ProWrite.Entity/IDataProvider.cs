//---------------------------------------------------------------------
//
// File: IDataProvider.cs
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
using ProWrite.Core;

namespace ProWrite.Entity
{
	/// <summary>
	/// Data provider interface
	/// </summary>
	public interface IDataProvider:IDisposable
	{
		/// <summary>
		/// Get data
		/// </summary>
		/// <returns></returns>
		object Get();
		/// <summary>
		/// Update data
		/// </summary>
		/// <returns></returns>
		bool Update();
		/// <summary>
		/// 
		/// </summary>
		/// <param name="data"></param>
		/// <returns></returns>
		bool Update(object data);
	}

	/// <summary>
	/// Data provider that have auto update function
	/// </summary>
	public interface IAutoUpdateDataProvider : IDataProvider
	{
		/// <summary>
		/// Get or set auto update's interval and its unit is second 
		/// </summary>
		int Interval { get; set;}

		/// <summary>
		/// if it is updating 
		/// </summary>
		bool IsRuning { get;}

		/// <summary>
		/// Start Call
		/// </summary>
		void Start();
		/// <summary>
		/// End Call
		/// </summary>
		void Stop();
	}

	/// <summary>
	/// Generic data providers
	/// </summary>
	/// <typeparam name="T"></typeparam>
	public interface IDataProvider<T>: IDataProvider where T : class, new()
	{
		new T Get();
		bool Update(T data);
	}

	/// <summary>
	/// Generic data providers that have auto update function
	/// </summary>
	/// <typeparam name="T"></typeparam>
	public interface IAutoUpdateDataProvider<T>:  IAutoUpdateDataProvider,IDataProvider<T> where T : class, new()
	{
	}
}