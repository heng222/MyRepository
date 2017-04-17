//---------------------------------------------------------------------
//
// File: SessionCommon.cs
//
// Description:
// SessionCommon class 
//
// Author: Jerry
// Date  : 2009-7-27
//
// Modify history:
//      
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Entity.Live;
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public class SessionCommon
    {
        /// <summary>
        /// Add new library group
        /// </summary>
        public static bool AddSession(SessionInfo session)
        {
            if (session == null)
                return false;

            return DataGate.AddSession(session);
        }

        // <summary>
        /// Add new library group
        /// </summary>
        public static bool UpdateSession()
        {
            if (SessionInfo.Current != null)
            {
                SessionInfo session = SessionInfo.Current.Copy();
                SessionInfo oldSession = DataGate.Project.SessionInfos.GetByName(session.Name);
                oldSession = session;
            }
            return DataGate.Update();
        }   
    }
}
