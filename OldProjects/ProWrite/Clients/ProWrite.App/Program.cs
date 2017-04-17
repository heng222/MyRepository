//---------------------------------------------------------------------
//
// File: LoginForm.cs
//
// Description:
// The main entry program 
//
// Author: Louis
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
// Modification History
// Louis 2008-6-25 fixed logform close bug
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using ProWrite.UI.Controls;
using System.Diagnostics;
using System.Reflection;

namespace ProWrite.App
{
    public class Program
    {
		
        [STAThread]
        static void Main(params string[] args)
        {
            //args = new string[] { "d:\\912111.pme" };
            Shell.Run(args);

        }
    }
}
