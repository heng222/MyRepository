//---------------------------------------------------------------------
//
// File: PlaylistAdapterInfo.cs
//
// Description:
// The class of PlaylistAdapterInfo
//
// Author: Jerry Xu
//
// Date:2008-7-15
//
// Modify History:
//      Jerry Xu 2008-7-7  Add the property of IsRandom,its type is bool and its default value is false.
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core;
using System.Xml.Serialization;
using System.ComponentModel;
using ProWrite.Entity.Library;

namespace ProWrite.Entity.Library
{
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
	public class PlaylistAdapterInfo : LibraryAdapter
    {
        #region Non Serialized Fields
        #endregion

        #region Serialized Fields
        #endregion

        #region Serialized Fields Version 2
        #endregion

        public PlaylistAdapterInfo()
		{
		}

		public PlaylistAdapterInfo(PlaylistInfo playlist):base(playlist)
		{
		}

		//[Browsable(false)]
		//public new PlaylistInfo Target
		//{
		//    get { return base.Target as PlaylistInfo; }
		//    set
		//    {
		//        base.Target = value;
		//    }
		//}

		public PlaylistInfo Playlist
		{
			get { return base.Target as PlaylistInfo; }
			set { base.Target = value; }
		}

		public override LibraryType Type
		{
			get { return LibraryType.PlaylistProxy; }
		}

        /// <summary>
        /// Function: Init a new instance of this object
        /// Author  : Jerry Xu
        /// Date    : 2008-7-8 
        /// </summary>
        /// <returns>LibraryAdapter</returns>
        public override LibraryAdapter NewInstance()
        {
            return new PlaylistAdapterInfo();
        }

        ///// <summary>
        ///// Function: Get data from a object to current object
        ///// Author  : Jerry Xu
        ///// Date    : 2008-7-8 
        ///// </summary>
        ///// <param name="memory">LibraryAdapter</param>
        //public override void FromTo(LibraryAdapter item)
        //{
        //    //this.Caption = memory.Caption;
        //    base.FromTo(item);

        //    //TODO:
        //    PlaylistAdapterInfo adp = item as PlaylistAdapterInfo;
        //    this.Name = adp.Name;
        //    this._targetName = adp._targetName;
        //    this._target = adp._target.Copy();
        //}

	}
}