//---------------------------------------------------------------------
//
// File: UFERequestActionBase.cs
//
// Description:
// The Base class of UFERequestAction
//
// Author: Terry
//
// Copyright (C) 2008 by ISoftstone Corporation.  All rights reserved.
// 
// Modify history:   
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.UFE;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Actions.UFE.Requests
{
    /// <summary>
    /// The Base class of UFERequestAction
    /// </summary>
    public abstract class UFERequestActionBase:RequestActionBase
    {
        public virtual Commands Id { get; set; }
    }
}
