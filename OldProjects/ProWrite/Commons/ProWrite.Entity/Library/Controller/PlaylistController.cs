//---------------------------------------------------------------------
//
// File: PlaylistController.cs
//      
// Description:
//      PlaylistController class
//
// Author: Jerry Xu 2009-4-22
//
// Modify History:
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core;
using System.IO;
using System.Xml.Serialization;
using ProWrite.Entity.Library.Controller;
using ProWrite.Entity.Library.ImportExport;

namespace ProWrite.Entity.Library.Controller
{
    /// <summary>
    /// Playlist controller class
    /// </summary>
    [Serializable]
    public class PlaylistController:FileController<PlaylistInfo>
    {
        [NonSerialized]
        private static Serialiser<PlaylistWrapper> _ser = Serialiser<PlaylistWrapper>.Binaray;

        public static void Save(string file, PlaylistInfo group)
        {
            _ser.Serialize(new PlaylistWrapper(group), file);
        }

        public static PlaylistWrapper Load(string file)
        {
            return _ser.Deserialise(file);
        }

        public override LibraryItem AddFile(string file)
        {
            //MessageInfo item = Load1(file);
            //if (item != null)
            //{
            //    item.Name = AllocateMessageName(item.Name);
            //    Add(item);
            //    OnAddCompleted(item);
            //}
            return null;
        }

        /// <summary>
        /// add item
        /// </summary>
        /// <param name="item"></param>
        public override bool Add(PlaylistInfo item)
        {
            if (item == null || Contains(item.Name))
                return false;

            bool flag = base.Add(item);

            OnAddCompleted(item);
            return flag;
        }

        /// <summary>
        /// update item
        /// </summary>
        /// <param name="item"></param>
        public override bool Update(PlaylistInfo item)
        {
            if (item == null)
                return false;

            bool flag = base.Update(item);
            return flag;
        }    
    }
}
