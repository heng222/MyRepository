//---------------------------------------------------------------------
//
// File: Vector.cs
//
// Description:
// vector list class
//
// Author: Kevin
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;

namespace ProWrite.Core
{
    /// <summary>
    /// vector list class
    /// </summary>
    /// <typeparam name="T"></typeparam>
    [Serializable]
    public class Vector<T>:List<T>
    {
        public override bool Equals(object obj)
        {
            Vector<T> other = obj as Vector<T>;
            if (other == null)
                return false;
            if (other.Count != Count)
                return false;
            for (int i = 0; i < Count; i++)
            {
                if (!other[i].Equals(this[i]))
                    return false;
            }

            return true;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
    }
}
