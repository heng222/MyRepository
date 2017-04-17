//---------------------------------------------------------------------
//
// File: TimeSliceGroupController.cs
//      
// Description:
//      TimeSliceGroupController class
//
// Author: Kevin 2008-11-20
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
using ProWrite.Entity.Shape;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Library.ImportExport;

namespace ProWrite.Entity.Library.Controller
{
    /// <summary>
    /// TimeSliceGroup controller class
    /// </summary>
    [Serializable]
    public class TimeSliceGroupController: FileController<TimeSliceGroupInfo>
    {
        [NonSerialized]
        private static Serialiser<TimeSliceGroupWrapper> _ser = Serialiser<TimeSliceGroupWrapper>.Binaray;

        public static void Save(string file, TimeSliceGroupInfo group)
        {
            _ser.Serialize(new TimeSliceGroupWrapper(group), file);
        }

        public static TimeSliceGroupWrapper Load(string file)
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
        /// add group item
        /// </summary>
        /// <param name="item"></param>
        public override bool Add(TimeSliceGroupInfo item)
        {
            if (item == null || Contains(item.Name))
                return false;

            bool flag = base.Add(item);           
            
            OnAddCompleted(item);
            return flag;
        }

        /// <summary>
        /// update message item
        /// </summary>
        /// <param name="item"></param>
        public override bool Update(TimeSliceGroupInfo item)
        {
            if (item == null)
                return false;

            bool flag = base.Update(item);            
            return flag;
        }

        //public new bool Contains(TimeSliceGroupInfo item)
        //{
        //    if (item == null)
        //        return false;
        //    return Find(p => p.Name == item.Name || p.Id == item.Id) != null;
        //}
    }
}
