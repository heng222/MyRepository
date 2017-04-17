//---------------------------------------------------------------------
//
// File: DisposableObject.cs
//
// Description:
// Disposable Object class
//
// Author: qswang@live.cn
// 
// Modify History:
//
//
// Copyright (C) 2008 by  qswang All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.Communication;

namespace System
{
    [Serializable]
    public abstract class DisposableObject : IDisposable
    {
        [NonSerialized]
        private bool disposed = false;

        ~DisposableObject()
        {
            try
            {
                Dispose(false);
            }
            catch (Exception ex)
            {
                Log.Error(ex.Message, ex);
            }
            finally
            { 
            }
        }

        #region IDisposable Members

        public void Dispose()
        {
            disposed = true;
            Dispose(true);

            GC.SuppressFinalize(this);
        }

        #endregion

        [Browsable(false)]
        public bool IsDisposed
        {
            get
            {
                return disposed;
            }
        }

        protected virtual void Dispose(bool disposing)
        {
        }
    }
}
