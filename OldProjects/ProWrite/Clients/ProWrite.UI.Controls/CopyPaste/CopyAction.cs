//---------------------------------------------------------------------
//
// File: CopyActionBase.cs
//
// Description:
//      Copy paste uploadAction base class
//
// Author: Kevin 2008-8-11
// 
// Modify History:
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Entity.Library;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.Scheduler;
using ProWrite.UI.Controls.Playlist;
using ProWrite.UI.Controls.MLPlaylist;
using DevExpress.XtraScheduler;

namespace ProWrite.UI.Controls.CopyPaste
{
    /// <summary>
    /// Copy paste uploadAction base class
    /// </summary>
    public abstract class CopyAction:ICopyAction
    {
        /// <summary>
        /// copy
        /// </summary>
        public void Copy()
        {
            if (CanCopy)
            {
                if (DoCopy())
                {
                    LocalMessageBus.Send(this, new MenuMessage(MenuCommands.Paste, true));
                }
            }
        }

        /// <summary>
        /// paste
        /// </summary>
        public void Paste()
        {
            if (CanPaste)
            {
                UndoService.BeginTransaction("Paste");
                if (DoPaste())
                    UndoService.Commit();
                else
                    UndoService.Current.Rollback();
            }
        }

        /// <summary>
        /// do copy
        /// </summary>
        /// <returns></returns>
        protected abstract bool DoCopy();
        /// <summary>
        /// can copy
        /// </summary>
        public abstract bool CanCopy { get;}
        /// <summary>
        /// can paste
        /// </summary>
        public abstract bool CanPaste{ get;}
        /// <summary>
        /// do paste
        /// </summary>
        /// <returns></returns>
        protected abstract bool DoPaste();

        private static CopyAction _current;
        public static CopyAction Current
        {
            get { return _current; }
            set
            {
                if (value == null)
                {
                    LocalMessageBus.Send(_current, new MenuMessage(MenuCommands.Paste, false));
                }
                else if (value != _current)
                {
                    _current = value;
                    if (_current.CanPaste)
                    {
                        LocalMessageBus.Send(_current, new MenuMessage(MenuCommands.Paste, true));
                    }
                }
            }
        }
    }

    public abstract class CopyAction<TModel, TControlPanel> : CopyAction
        where TModel : MemoryLibraryItem, new()
        where TControlPanel : ControlPanel<TModel, TControlPanel>, new()
    {
        public CopyAction() { }

        protected TControlPanel innerControl;

        public TControlPanel ControlPanel
        {
            get { return innerControl; }
            set
            {
                if (null != value && !object.Equals(value, innerControl))
                {
                    Check.Require(value, "value", Check.NotNull);
                    innerControl = value;
                }
            }
        }
    }


    public class PlaylistCopyAction : CopyAction<PlaylistInfo, PlaylistControl>
    {
        static Type clipboardType = typeof(MemoryLibraryItem[]);
        MemoryLibraryItem[] items = null;
        public override bool CanCopy
        {
            get 
            {
                bool canCopy = innerControl != null
                    && innerControl.DragControl.Controls != null
                    && innerControl.DragControl.Controls.Count > 0;
                LocalMessageBus.Send(this, new MenuMessage(MenuCommands.Copy, canCopy));
                return canCopy;
            }
        }

        protected override bool DoCopy()
        {
            items = new MemoryLibraryItem[1];
            items[0] = innerControl.DragControl._rightMessageBtn.PlaylistItem.Target;
            ClipboardService.Set(items);
            return true;
        }

        public override bool CanPaste
        {
            get 
            {
                if (innerControl == null)
                    return false;
                if (!ClipboardService.Contains<MemoryLibraryItem[]>())
                    return false;
                items = ClipboardService.Get<MemoryLibraryItem[]>();
                if (items == null)
                    return false;
                return true;
            }
        }

        protected override bool DoPaste()
        {
            MemoryLibraryItem item = items[0];
            if (item.Type == ProWrite.Core.LibraryType.Playlist)
                item = LibraryGroup.Current.Playlists.GetByName(item.Name);
            innerControl.DragControl.InsertLibrary(item.ToProxy(), innerControl.DragControl.Controls.Count, true);
            return true;
        }
    }

    public class SchedulerCopyAction : CopyAction<SchedulerInfo, ScheduleControl>
    {
        static Type clipboardType = typeof(AppointmentInfo[]);
        private AppointmentInfo[] items = null;

        public override bool CanCopy
        {
            get
            {
                bool canCopy = innerControl != null 
                    && innerControl.Scheduler.SelectedAppointments != null 
                    && innerControl.Scheduler.SelectedAppointments.Count > 0;
                LocalMessageBus.Send(this, new MenuMessage(MenuCommands.Copy, canCopy));
                return canCopy;
            }
        }

        protected override bool DoCopy()
        {
            if (innerControl == null || innerControl.Scheduler.SelectedAppointments == null || innerControl.Scheduler.SelectedAppointments.Count == 0)
                return false;

            
                int length = innerControl.Scheduler.SelectedAppointments.Count;
                var clones = new AppointmentInfo[length];
                for (int i = 0; i < length; i++)
                {
                    clones[i] = innerControl.appointConverter.Convert(innerControl.Scheduler.SelectedAppointments[i]);
                    clones[i].Id = Guid.NewGuid().ToString();
                }

                ClipboardService.Set(clones);
                return true;
           
        }

        public override bool CanPaste
        {
            get
            {
                if (innerControl == null)
                    return false;
                if (!ClipboardService.Contains<AppointmentInfo[]>())
                    return false;
                items = ClipboardService.Get<AppointmentInfo[]>();
                if (items.Length < 1)
                    return false;
                return true;
            }
            
        }

        protected override bool DoPaste()
        {
            innerControl.AddAppointments(items);
            return true;
        }
        
    }

    public class MLPlaylistCopyAction : CopyAction<MLPlaylistInfo, MLPlaylistControl>
    {
        public override bool CanCopy
        {
            get { return false; }
        }

        protected override bool DoCopy()
        {
            throw new NotImplementedException();
        }

        public override bool CanPaste
        {
            get { return false; }
        }

        protected override bool DoPaste()
        {
            throw new NotImplementedException();
        }
    }
}
