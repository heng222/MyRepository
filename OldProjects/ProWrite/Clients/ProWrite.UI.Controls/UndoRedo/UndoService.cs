//---------------------------------------------------------------------
//
// File: UndoService.cs
//
// Description:
//      Undo redo service class
//
// Author: Kevin 2008-8-4
// 
// Modify History:
//      Jerry Xu 2008-8-14 Add uploadAction:AddPlaylistMessageMoveAction,AddPlaylistMessageInsertFromLibraryAction,
//          AddPlaylistMessageInsertAction,AddPlaylistMessageRemoveAtAction
//      Jerry Xu 2008-8-22 Add uploadAction:AddLayerMoveAction
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core;
using ProWrite.Entity.Shape;
using System.Reflection;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.Editor;
using ProWrite.UI.Controls.UndoRedo.Action;
using DevExpress.XtraScheduler.Services;
using DevExpress.XtraScheduler;
using ProWrite.UI.Controls.Playlist;
using ProWrite.Entity.DES;

namespace ProWrite.UI.Controls
{
    /// <summary>
    /// Undo redo service class
    /// </summary>
    public sealed class UndoService
    {
        private static readonly List<UndoManager> _services;

        static UndoService()
        {
            _services = new List<UndoManager>();
            LocalMessageBus.Subject<PWMessage<MenuCommands>>().Observers += delegate(object sender, PWMessage<MenuCommands> msg)
            {
                InitMenu(msg.Content);
            };
        }

        /// <summary>
        /// init menu event
        /// </summary>
        /// <param name="command"></param>
        private static void InitMenu(MenuCommands command)
        {
            switch (command)
            {
                case MenuCommands.Undo:
                    Undo();
                    break;
                case MenuCommands.Redo:
                    Redo();
                    break;
            }
        }

        /// <summary>
        /// register service
        /// </summary>
        /// <returns></returns>
        public static UndoManager RegisterService()
        {
            UndoManager item = new UndoManager();
            item.Changed += OnUndoManagerChanged;
            _services.Add(item);
            Current = item;
            return item;
        }

        /// <summary>
        /// remove service
        /// </summary>
        public static void RemoveService()
        {
            if (_current != null && _services.Contains(_current))
            {
                _current.Changed -= OnUndoManagerChanged;
                _current.Clear();
                _services.Remove(_current);

            }
        }

        private static void OnUndoManagerChanged(object sender, EventArgs e)
        {
            if (_current != null)
            {
                SetMenuState(_current.CanUndo, _current.CanRedo);
            }
        }

        private static void SetMenuState(bool canUndo,bool canRedo)
        {
            LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[]{
                    new MenuCommand(MenuCommands.Undo, canUndo)
                    ,new MenuCommand(MenuCommands.Redo,canRedo)
                }));
        }

        static UndoManager _current;
        /// <summary>
        /// current service
        /// </summary>
        public static UndoManager Current
        {
            get
            {
                return _current;
            }
            set
            {
                //if (value == null)
                //    SetMenuState(false, false);

                if (_current != value)
                {
                    _current = value;
                    if (_current != null)
                    {
                        SetMenuState(_current.CanUndo, _current.CanRedo);
                        UndoManager.Current = value;
                    }
                }
            }
        }

        /// <summary>
        /// preform undo uploadAction
        /// </summary>
        public static void Undo()
        {
            if (_current != null && _current.CanUndo)
            {
                _current.Undo();
            }
        }

        /// <summary>
        /// preform redo uploadAction
        /// </summary>
        public static void Redo()
        {
            if (_current != null && _current.CanRedo)
            {
                _current.Redo();
            }
        }

        /// <summary>
        /// can add uploadAction
        /// </summary>
        public static bool CandAddAction
        {
            get
            {
                if (_current == null)
                    return false;
                return _current.CanAddAction;
            }
        }

        #region Add undo uploadAction
        /// <summary>
        /// add uploadAction
        /// </summary>
        /// <param name="item"></param>
        public static void AddAction(IUndoAction item)
        {
            if (_current != null)
                _current.AddAction(item);
        }


        /// <summary>
        /// add property changed uploadAction
        /// </summary>
        /// <param name="target"></param>
        /// <param name="propertyName"></param>
        /// <param name="newValue"></param>
        /// <param name="oldValue"></param>
        public static void AddPropertyChangedAction(object target, string propertyName, object newValue, object oldValue)
        {
            AddPropertyChangedAction(target, new PropertyItem(propertyName, newValue, oldValue));
        }

        public static void AddPropertyChangedAction(object target, params PropertyItem[] items)
        {
            if (_current != null && _current.CanAddAction)
            {
                Check.Require(target, "target", Check.NotNull);
                Check.Require(items, "items", Check.NotNull);
                Check.Require(items.Length, "items.Length", Check.GreaterThan<int>(0));

                Type type = target.GetType();
                foreach (PropertyItem item in items)
                {
                    //item.Prop = type.GetProperty(item.Name);
                    var prop = ParseProperty(target, item.Name);
                    Check.Require(prop, "prop", Check.NotNull);
                    Check.Require(prop.Name, "prop.Name", Check.NotNull);
                    Check.Require(prop.Owner, "prop.Owner", Check.NotNull);
                    item.Target = prop.Owner;
                    item.Prop = prop.Name;
                }

                _current.AddAction(new PropertyChangedAction(target, items));
            }
        }

        /// <summary>
        /// add shape removed uploadAction
        /// </summary>
        /// <param name="shape"></param>
        /// <param name="frameLayer"></param>
        public static void AddLayerRemovedAction(LayerControl frameLayer)
        {
            if (_current != null 
                && _current.CanAddAction 
                && MessageControl.Current != null
                && frameLayer != null)
                UndoService.AddAction(new LayerRemovedActionNew(frameLayer));
        }


        /// <summary>
        /// add item added uploadAction
        /// </summary>
        /// <param name="shape"></param>
        /// <param name="frameLayer"></param>
        public static void AddLayerAddedAction(LayerControl frameLayer)
        {
            if (_current != null
                && _current.CanAddAction
                && MessageControl.Current != null
                && frameLayer != null)
                UndoService.AddAction(new LayerAddedAction(frameLayer));
        }

        /// <summary>
        /// Function: Add item move uploadAction
        /// Author  : Jerry Xu
        /// Date    : 2008-8-22
        /// </summary>
        /// <param name="layerContainer">FrameLayerContainerNew</param>
        /// <param name="source">FrameLayerNew</param>
        /// <param name="dest">FrameLayerNew</param>
        public static void AddLayerMoveAction(MessageControl layerContainer, LayerControl source, LayerControl dest)
        {
            if (_current != null
                && _current.CanAddAction
                && layerContainer != null
                && source != null
                && dest != null)
                UndoService.AddAction(new LayerMoveActionNew(layerContainer, source, dest));
        }

        public static void AddShapeAddedAction(ShapeBase shape)
        {
            if (_current != null
                && _current.CanAddAction
                && shape != null
                && shape.LayerType == LayerType.Paint
                && shape.Type != ShapeType.ShapeDraw
                && MessageControl.Current != null)
                _current.AddAction(new ShapeAddedAction(shape));
        }

        public static void AddShapeRemovedAction(ShapeBase shape)
        {
            if (_current != null
                && _current.CanAddAction
                && shape != null
                && shape.LayerType == LayerType.Paint
                && shape.Type != ShapeType.ShapeDraw
                && MessageControl.Current != null)
                _current.AddAction(new ShapeRemovedAction(shape));
        }

        public static void AddLayerEffectAddedAction(LayerEffect effect)
        {
            if (_current != null
                && _current.CanAddAction
                && effect != null
                && (LayerControl.CurrentDrag != null || LayerControl.Current != null))
                _current.AddAction(new LayerEffectAddedAction(effect));
        }

        public static void AddLayerEffectRemovedAction(LayerControl framelayer, LayerEffect effect)
        {
            if (_current != null
                && _current.CanAddAction
                && effect != null
                && framelayer != null)
                _current.AddAction(new LayerEffectRemovedAction(framelayer,effect));
        }

        public static void AddGotoDateAction(IDateTimeNavigationService navigate, DateTime newValue, DateTime oldValue, SchedulerViewType newViewType, SchedulerViewType oldViewType)
        {
            if (UndoService.CandAddAction)
                UndoService.AddAction(new GotoDateAction(navigate, newValue, oldValue, newViewType, oldViewType));
        }

        public static void AddNavigateBackwardAction(IDateTimeNavigationService navigate)
        {
            if (UndoService.CandAddAction)
                UndoService.AddAction(new NavigateBackwardAction(navigate));
        }

        public static void AddNavigateForwardAction(IDateTimeNavigationService navigate)
        {
            if (UndoService.CandAddAction)
                UndoService.AddAction(new NavigateForwardAction(navigate));
        }

        public static void AddAppointmentAddedAction(SchedulerStorage storage, Appointment appointment)
        {
            if (_current != null && _current.CanAddAction)
                _current.AddAction(new AppointmentAddedAction(storage,appointment));
        }

        public static void AddAppointmentRemovedAction(SchedulerStorage storage, Appointment appointment)
        {
            if (_current != null && _current.CanAddAction)
                _current.AddAction(new AppointmentRemovedAction(storage, appointment));
        }

        public static void AddPlaylistItemMoveAction(IPlaylistItemService dragDropControl, int sourceIndex, int destIndex)
        {
            if (UndoService.CandAddAction)
                UndoService.AddAction(new PlaylistItemMoveAction(dragDropControl, sourceIndex, destIndex));
        }

        public static void AddPlaylistItemInsertFromLibraryAction(IPlaylistItemService dragDropControl, PlaylistItemControl btn, int index)
        {
            if (UndoService.CandAddAction)
                UndoService.AddAction(new PlaylistItemInsertAction(dragDropControl, btn, index));
        }
        public static void AddPlaylistItemInsertAction(IPlaylistItemService dragDropControl, PlaylistItemControl btn, int index)
        {
            if (UndoService.CandAddAction)
                UndoService.AddAction(new PlaylistItemInsertAction(dragDropControl, btn, index));
        }
        public static void AddPlaylistItemRemoveAtAction(IPlaylistItemService dragDropControl, ProWrite.UI.Controls.Playlist.PlaylistItemControl btn, int index)
        {
            if (UndoService.CandAddAction)
                UndoService.AddAction(new PlaylistItemRemoveAtAction(dragDropControl, btn, index));
        }

        private class Property
        {
            public readonly PropertyInfo Name;
            public readonly object Owner;

            public Property(PropertyInfo name, object owner)
            {
                Name = name;
                Owner = owner;
            }
        }

        private static readonly BindingFlags propertyBindingFlags = BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Static;
        private static Property ParseProperty(object root, string propertyName)
        {
            try
            {
                if (root == null)
                    return null;
                string[] items = propertyName.Split('.');
                if (items == null || items.Length < 1)
                    return null;
                if (items.Length == 1)
                    return new Property(root.GetType().GetProperty(propertyName, propertyBindingFlags), root);
                object target = root;

                string name = null;
                for (int i = 0; i < items.Length; i++)
                {
                    name = items[i];
                    PropertyInfo p = target.GetType().GetProperty(name, propertyBindingFlags);
                    if (i < items.Length - 1)
                        target = p.GetValue(target, null);
                }
                return new Property(target.GetType().GetProperty(name, propertyBindingFlags), target);
            }
            catch
            {
                return null;
            }
        }
        #endregion

        /// <summary>
        /// begin transaction
        /// </summary>
        /// <param name="name"></param>
        public static void BeginTransaction(string name)
        {
            if (_current != null)
                _current.BeginTransaction(name);
        }

        /// <summary>
        /// commit transaction
        /// </summary>
        public static void Commit()
        {
            if (_current != null)
                _current.Commit();
        }

        public static void Rollback()
        {
            if (_current != null)
                _current.Rollback();
        }

        public static void Suspend()
        {
            if (_current != null)
                _current.Suspend();
        }

        public static void Resume()
        {
            if (_current != null)
                _current.Resume();
        }
    }
}
