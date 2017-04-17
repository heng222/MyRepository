//---------------------------------------------------------------------
//
// File: ISupportGlobalization.cs
//
// Description:
// Support Globalization interface
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
    /// Globalization support interface
    /// </summary>
    public interface ISupportGlobalization
    {
        /// <summary>
        /// Get or set whether it support internationalization function
        /// </summary>
        bool IsSupportGlobalization { get;set;}
        /// <summary>
        /// Initialize resource infomation
        /// </summary>
        void InitializeResource();
        /// <summary>
        /// Refresh the resource if it support internationalization ,otherwise don't refresh
        /// </summary>
        void RefreshResource();
    }

    /// <summary>
    /// simple extent interface of internationalization
    /// </summary>
    public interface ISampleGlobalization: ISupportGlobalization
    {
        /// <summary>
        /// Get or set resource key
        /// </summary>
        string ResourceKey { get; set;} 
    }
}
