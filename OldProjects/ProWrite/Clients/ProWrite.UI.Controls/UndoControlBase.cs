//---------------------------------------------------------------------
//
// File: UndoControlBase.cs
//      
// Description:
//      Support undo & redo function control base class
//
// Author: Kevin 2008-8-4
//
// Modify History:
//          Jerry Xu 2009-1-9 Add property:IsNew
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core;
using System.ComponentModel;
using ProWrite.Entity.Library;

using System.Drawing;
using ProWrite.Entity.Dashboard;

namespace ProWrite.UI.Controls
{
    /// <summary>
    /// Support undo & redo function control base class
    /// </summary>
    public class UndoControlBase:ControlBase
    {
        public UndoControlBase()
        {
            if (!DesignMode)
                _undoManager = UndoService.RegisterService();
        }

        private UndoManager _undoManager;
        /// <summary>
        /// get undo manager
        /// </summary>
        [Browsable(false)]
        public UndoManager UndoManager
        {
            get
            {
                return _undoManager;
            }
        }

        protected override void Dispose(bool disposing)
        {
            //UndoService.RemoveService();
            base.Dispose(disposing);
        }
    }

    /// <summary>
    /// Control panel class
    /// </summary>
    /// <typeparam name="T">library entity class</typeparam>
    /// <typeparam name="M">Sub class for control panel</typeparam>
    public class ControlPanel<TModel,TControlPanel> : UndoControlBase ,IChangedServiceProvider
        where TModel :MemoryLibraryItem,new ()
        where TControlPanel: ControlPanel<TModel,TControlPanel>
    {
        protected SignInfo _sign = null;
        protected Size _signSize = Size.Empty;

        protected ChangedService _changedService;
        protected TModel _model;
        protected static TControlPanel _current;
        protected internal string LibraryName;
        public bool IsNew { get; set; }

        public ControlPanel()
        {
            _changedService = new ChangedService();
            HasSaved = false;
        }

        void UndoManager_UndoAllComleted(object sender, EventArgs e)
        {
            _changedService.AcceptChanged();
        }

        public bool HasSaved { get; set; }
        /// <summary>
        /// Get changed service
        /// </summary>
        public ChangedService ChangedService
        {
            get { return _changedService; }
        }

        /// <summary>
        /// get library model
        /// </summary>
        public virtual TModel Model
        {
            get { return _model; }
        }

        public SignInfo Sign { get { return _sign; } }
        
        /// <summary>
        /// get or set current active control panel
        /// </summary>
        public static TControlPanel Current
        {
            get { return _current; }
            set { _current = value; }
        }

        /// <summary>
        /// is active playlist control
        /// </summary>
        public bool IsActive
        {
            get
            {
                return _current == this;
            }
        }

        /// <summary>
        /// load library model data in order to save
        /// </summary>
        public virtual void LoadModelInfo()
        {
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            if (!DesignMode)
                UndoManager.UndoAllComleted += new EventHandler(UndoManager_UndoAllComleted); 

        }

        /// <summary>
        /// populate data in order to open control panel
        /// </summary>
        /// <param name="signType"></param>
        /// <param name="size"></param>
        /// <param name="model"></param>
        public void Populate(SignInfo sign, TModel model)
        {
            _sign = sign;
            _signSize = new Size(sign.Width, sign.Height);
            _model = model;
            DoPopulate();
        }

        /// <summary>
        /// do populate in order to open control panel
        /// </summary>
        protected virtual void DoPopulate()
        {
        }

        public virtual void InsertLibrary(params MemoryLibraryItem[] items)
        {
        }

        public virtual void OnClosing()
        {
        }

        public virtual void SendToSign() { }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            if (_changedService != null)
            {
                _changedService.Dispose();
                _changedService = null;
                UndoManager.UndoAllComleted -= UndoManager_UndoAllComleted;
            }
        }
    }
}
