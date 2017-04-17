//---------------------------------------------------------------------
//
// File: ClipboardService.cs
//
// Description:
//      Clipboard service class
//
// Author: Kevin 2008-8-11
// 
// Modify History:
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace ProWrite.UI.Controls.Common
{
	/// <summary>
	/// Clipboard service class
	/// </summary>
	public sealed class ClipboardService
	{
		/// <summary>
		/// set data
		/// </summary>
		/// <param name="data"></param>
		public static void Set(object data)
		{
			Clipboard.SetDataObject(data,true);
		}

		/// <summary>
		/// get data
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		public static T Get<T>()
		{
            var data = Clipboard.GetDataObject();
            if (data == null)
                return default(T);

			return (T)data.GetData(typeof(T));
		}

		public static bool Contains(Type type)
		{
            var data = Clipboard.GetDataObject();
            if (data == null || type == null)
                return false;
            return data.GetDataPresent(type);
		}
		/// <summary>
		/// is contains data
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		public static bool Contains<T>()
		{
            var data = Clipboard.GetDataObject();
            if (data == null)
                return false;
			return data.GetDataPresent(typeof(T));
		}

        public static bool ContainsImage()
        {
            return false;
            //return Clipboard.ContainsImage();
        }

        public static Image GetImage()
        {
            return Clipboard.GetImage();
        }
	}
}