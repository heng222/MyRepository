//---------------------------------------------------------------------
//
// File: IReferenceCounter.cs
//
// Description:
//      resource reference counter interface
//
// Author: Kevin 2008-7-22
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace ProWrite.Entity.Library
{
	/// <summary>
	/// resource reference counter interface
	/// </summary>
	public interface IReferenceCounter
	{
		/// <summary>
		/// get reference count
		/// </summary>
		int ReferenceCount { get;}
		/// <summary>
		/// increase reference count
		/// </summary>
		void IncreaseReference();
		/// <summary>
		/// decrease reference count
		/// </summary>
		void DecreaseReference();
	}

	public interface IReferenceCounterHost
	{
		IReferenceCounter RefCounter { get;}
	}

	/// <summary>
	/// Resource reference counter class
	/// </summary>
	[Serializable]
	public class ResourceReferenceCounter:IReferenceCounter
	{
		private int _referenceCount = 0;


		/// <summary>
		/// get resource reference count
		/// </summary>
		public int ReferenceCount
		{
			get { return _referenceCount; }
		}

		/// <summary>
		/// increase reference count
		/// </summary>
		/// <returns></returns>
		public void IncreaseReference()
		{
			Interlocked.Increment(ref _referenceCount);
		}

		/// <summary>
		/// decrease reference count
		/// </summary>
		/// <returns></returns>
		public void DecreaseReference()
		{
			Interlocked.Decrement(ref _referenceCount);
		}
	}
}