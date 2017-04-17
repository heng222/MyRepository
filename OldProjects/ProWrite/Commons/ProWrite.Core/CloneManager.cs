//---------------------------------------------------------------------
//
// File: CloneManager.cs
//
// Description:
// Clone Manager class
//
// Author: Kevin
// 
// Modify History:
//
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace ProWrite.Core
{
    public sealed class CloneManager
    {
        public static T Clone<T>(T source) where T:class
        {
            if (source == default(T))
                return source;

            T dest = default(T);
            Serialiser<T> ser = Serialiser<T>.Binaray;
            using (MemoryStream stream = new MemoryStream())
            {
                ser.Serialize(source, stream);
                stream.Position = 0;
                dest = ser.Deserialise(stream);
            }
            return dest;
        }
    }
}
