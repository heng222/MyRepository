//---------------------------------------------------------------------
//
// File: PlaylistControl.DragDropControl.cs
//
// Description:
//      DragDrop Control
//
// Author: Jerry Xu
// Date  : 2008-10-22
//
//Modify History:
//      Jerry Xu 2009-2-12 Update Event:MessageBtn_DragDrop(object sender, DragEventArgs e)
//      Jerry Xu 2009-2-12 Update Event:MessageBtn_DragDrop(object sender, DragEventArgs e),OnDragDrop(DragEventArgs e)
//      Jerry Xu 2009-2-25 Update method:GetNailImage(PlaylistItemControl item)
//      Jerry Xu 2009-3-16 Update event:button_MouseDown(object sender, MouseEventArgs e)
//      Jerry Xu 2009-3-16 Update method:RemoveAt(int index),FirstRefreshView(),InsertLibrary(LibraryAdapter item, int index, bool isNew)
//      Jerry Xu 2009-3-16 Insert new property:CurrentItem
//      Jerry Xu 2009-4-8  Add method:CheckItemValid(MemoryLibraryItem item)
//                         Update method:InsertLibrary(params MemoryLibraryItem[] items)
//      Jerry Xu 2009-5-6  Add method: OnPaint
//                         Update method:Insert(PlaylistItemControl item, int index,bool isNew),RemoveAt(int index)
//      Jerry Xu 2009-5-6  Update method:InsertLibrary(LibraryAdapter item, int index, bool isNew)
//      Jerry Xu 2009-5-7  Update method:OnPaint()
//      Jerry Xu 2009-5-26 Update method:OnPaint(),Insert(PlaylistItemControl item, int index,bool isNew)
//                         Update event:button_MouseDown(object sender, MouseEventArgs e)
//      Jerry Xu 2009-6-5  Update method:GetNailImage(PlaylistItemControl item),SetDefaultNailImage()
//      Jerry Xu 2009-6-5  Update method:OnUpdateTotalLength(),OnUpdateTotalWidth(int pos)
//      Jerry Xu 2009-6-8  Update method:FirstRefreshView(),GetNailImage(PlaylistItemControl item),
//                              SetDefaultNailImage(),RemoveAt(int index)
//      Jerry Xu 2009-6-9  Update event:Insert(PlaylistItemControl item, int index,bool isNew),SetDefaultNailImage()
//                              
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Library;
using ProWrite.Resources;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Library;
using ProWrite.UI.Controls.CopyPaste;
using DevExpress.XtraEditors;
using System.Drawing;
using ProWrite.Core;
using DevExpress.XtraEditors.ViewInfo;
using ProWrite.UI.Controls.Common.Messages;
using ProWrite.UI.Controls.Editor;
using ProWrite.Unsafe;
using System.Drawing.Imaging;

namespace ProWrite.UI.Controls.Playlist
{
    public partial class PlaylistControl
    {
        /// <summary>
        /// Kevin 2008-10-29
        /// </summary>
        /// <param name="item"></param>
        public override void InsertLibrary(params MemoryLibraryItem[] items)
        {
            if (items != null && items.Length > 0)
            {
                foreach (MemoryLibraryItem item in items)
                {

                    if(dragDropControl.CheckItemValid(item))
                    //if (item.Type == LibraryType.TimeSliceGroup && (item == null || (item as TimeSliceGroupInfo).Items == null || (item as TimeSliceGroupInfo).Items.Length == 0))
                    //{
                    //    MsgBox.Warning(Resource.GetString(Resource.Strings.PlayListTimeSliceGroupLengthEmpty));
                    //}
                    //else
                    //{
                        dragDropControl.InsertLibrary(item.ToProxy(), dragDropControl.Controls.Count, true);
                    //}
                }
            }
        }

        public class DragDropControl : PanelControl, IPlaylistItemService
        {
            #region Variants define
            PlaylistControl _playlistCtrl;
            PlaylistItemControl _sourceMessageBtn;
            public PlaylistItemControl _rightMessageBtn;
            private int _scrollWidth = 512;
            private const int defaultWidth = 20;
            private string _totalLength = "00;00;00";
            private ZoomType _zoomaction = ZoomType.ZoomNone;
            Rectangle _dragBoxFromMouseDown = Rectangle.Empty;
            private int _NailImageIndex = 0;
            
            private ContextMenuStrip contextMenuStrip1;
            private ToolStripMenuItem deleteToolStripMenuItem;
            private ToolStripMenuItem setDefaultImagetoolStripMenuItem;
            private ToolStripMenuItem CopyToolStripMenuItem;
            private ToolStripMenuItem PastetoolStripMenuItem;
            public event EventHandler ItemSelectChange = null;
            #endregion

            public DragDropControl()
            {
                this.AllowDrop = true;
            }

            #region Properties define
            private int _unitWidth = Constance.TrackBar.UnitWidth;
            /// <summary>
            /// Trackbar unit width which will change by zoom event
            /// </summary>
            public int UnitWidth
            {
                get { return _unitWidth; }
                set { _unitWidth = value; }
            }

            public int NailImageIndex
            {
                set { _NailImageIndex = value; }
            }

            private int _tick = Constance.TrackBar.Tick;
            /// <summary>
            /// Trackbar tick
            /// </summary>
            public int Tick
            {
                get { return _tick; }
                set { _tick = value; }
            }

            private PlaylistItemControl _currentItem;
            public PlaylistItemControl CurrentItem
            {
                get
                {
                    return _currentItem;
                }
                set
                {
                    _currentItem = value;
                }
            }

            public List<PlaylistItemControl> Items
            {
                get
                {
                    if (Controls.Count <= 0)
                        return null;

                    List<PlaylistItemControl> _Items = new List<PlaylistItemControl>();
                    foreach (Control item in Controls)
                        _Items.Add(item as PlaylistItemControl);
                    return _Items;
                }
            }
            #endregion

            #region Functions define
            public bool CheckItemValid(MemoryLibraryItem item)
            {
                if (item == null)
                    return false;
                if (item.Type == LibraryType.Playlist && item.Name == _playlistCtrl.Model.Name)
                {
                    MsgBox.Warning(Resource.GetString(Resource.Strings.PlaylistNotDragItself));
                    return false; ;
                }

                if (item != null && item.Length == 0)
                {
                    if (item.Type == LibraryType.Message)
                    {
                        MsgBox.Warning(Resource.GetString(Resource.Strings.PlayListMessageLengthEmpty));
                    }
                    if (item.Type == LibraryType.Playlist)
                    {
                        MsgBox.Warning(Resource.GetString(Resource.Strings.PlayListPlayListLengthEmpty));
                    }
                    if (item.Type == LibraryType.TimeSliceGroup)
                    {
                        MsgBox.Warning(Resource.GetString(Resource.Strings.PlayListTimeSliceGroupLengthEmpty));
                    }
                    _playlistCtrl.dragDropLine1.Visible = false;
                    return false;
                }
                if (item.Type == LibraryType.TimeSliceGroup)
                {
                    TimeSliceGroupInfo group = item as TimeSliceGroupInfo;
                    if (group.Items == null || group.Items.Length == 0)
                    {
                        MsgBox.Warning(Resource.GetString(Resource.Strings.PlayListTimeSliceGroupLengthEmpty));
                        _playlistCtrl.dragDropLine1.Visible = false;
                        return false;
                    }
                }
                if (item.Type == LibraryType.Playlist)
                {
                    PlaylistInfo playlist = item as PlaylistInfo;
                    if (playlist.Items == null || playlist.Items.Length == 0)
                    {
                        MsgBox.Warning(Resource.GetString(Resource.Strings.PlayListPlayListLengthEmpty));
                        _playlistCtrl.dragDropLine1.Visible = false;
                        return false;
                    }
                    if (playlist.IsManyLevel || _playlistCtrl.Model.IsInPlaylist)
                    {
                        MsgBox.Warning(Resource.GetString(Resource.Strings.PlaylistManyLevel));
                        _playlistCtrl.dragDropLine1.Visible = false;
                        return false;
                    }
                    playlist.IsInPlaylist = true;
                    
                }
                return true;
            }

            #region Init
            /// <summary>
            /// Function:Init DragDropPanel info
            /// Author: Jerry Xu
            /// Date:2008-8-13
            /// </summary>
            internal void Init(PlaylistControl owner)
            {
                InitRightKeyMenu();
                _playlistCtrl = owner;
                //LocalMessageBus.Subject<LibraryImageChangeMessage>().Observers += new System.Communication.Messaging.ObserverHandler<LibraryImageChangeMessage>(OnLibraryImageChange);
                _zoomaction = ZoomType.ZoomNone;
                //this.Width = Constance.MaxZoomLength;
            }

            //void OnLibraryImageChange(object sender, LibraryImageChangeMessage msg)
            //{
            //    if (CurrentItem!=null && msg.Name == CurrentItem.PlaylistItem.Target.Name && msg.Type == CurrentItem.PlaylistItem.Target.Type)
            //    {
            //        CurrentItem.NailImage = GetNailImage(CurrentItem);
            //        using (Graphics g = Graphics.FromHwnd(_playlistCtrl.playPanel.Handle))
            //            g.DrawImage(CurrentItem.NailImage, new Point(0, 0));
            //    }
            //}

            public void FirstRefreshView()
            {
                if (_playlistCtrl._model == null)
                    return;

                int length = _playlistCtrl._model.Items.Length;
                UndoService.Suspend();
                //_playlistCtrl._changedService.SuspendChanged();
                Controls.Clear();
                for (int i = 0; i < length; i++)
                {
                    InsertLibrary(_playlistCtrl._model.Items[i], i, false);
                }
                PopulateSize();

                if (!string.IsNullOrEmpty(_playlistCtrl._model.NailImageID))
                {
                    _currentItem = Items.Find(p => { return (p.PlaylistItem.TargetId == _playlistCtrl._model.NailImageID); });
                }
                this.Invalidate();
                //OnPaint();
                //_playlistCtrl._changedService.SuspendChanged();
                //if (length > 0)
                //{
                //    PlaylistItemControl item = (_playlistCtrl.dragDropControl.Controls[0] as PlaylistItemControl);
                //    item.NailImage = _playlistCtrl.dragDropControl.GetNailImage(_playlistCtrl.dragDropControl.Controls[0] as PlaylistItemControl);
                //    if (item.NailImage != null)
                //    {
                //        using (Graphics g = Graphics.FromHwnd(_playlistCtrl.playPanel.Handle))
                //            g.DrawImage(item.NailImage, new Point(0, 0));
                //    }
                    
                //}
                UndoService.Resume();
            }
            #endregion
            //protected override void OnPaint(PaintEventArgs e)
            //{
            //    OnPaint();
            //}

            public void OnPaint()
            {
                if (_currentItem != null)
                {
                    
                    if(_currentItem.NailImage !=null)
                        using (Graphics g = Graphics.FromHwnd(_playlistCtrl.playPanel.Handle))
                        {
                            g.Clear(_playlistCtrl.playPanel.BackColor);
                            g.DrawImage(_currentItem.NailImage, new Point(0, 0));
                        }
                    //_playlistCtrl.playPanel.BackgroundImage = _currentItem.NailImage; //dragDropControl.GetNailImage(dragDropControl.NailPlaylistItemItem);
                }
                else
                {
                    if (Controls.Count > 0)
                    {
                        _currentItem = Controls[0] as PlaylistItemControl;
                        if (_currentItem.NailImage != null)
                            using (Graphics g = Graphics.FromHwnd(_playlistCtrl.playPanel.Handle))
                                g.DrawImage((Controls[0] as PlaylistItemControl).NailImage, new Point(0, 0));
                        //_playlistCtrl.playPanel.BackgroundImage = (Controls[0] as PlaylistItemControl).NailImage;
                    }
                    else
                        using (Graphics g = Graphics.FromHwnd(_playlistCtrl.playPanel.Handle))
                        {
                            //Image img = new Bitmap(playPanel.Size.Width,playPanel.Size.Height);
                            //g.DrawImage(img, new Point(0, 0));
                            g.Clear(_playlistCtrl.playPanel.BackColor);
                        }
                        //_playlistCtrl.playPanel.BackgroundImage = null;
                }
            }

            #region InitRightKeyMenu
            /// <summary>
            /// InitRightKeyMenu
            /// </summary>
            private void InitRightKeyMenu()
            {
                // 
                // CopyToolStripMenuItem
                // 
                this.CopyToolStripMenuItem = new ToolStripMenuItem();
                this.CopyToolStripMenuItem.Size = new System.Drawing.Size(155, 22);
                this.CopyToolStripMenuItem.Text = "Copy";
                this.CopyToolStripMenuItem.Click += new System.EventHandler(this.CopyToolStripMenuItem_Click);
                this.CopyToolStripMenuItem.Image = Resource.GetImage(Resource.Images.Copy);

                // 
                // deleteToolStripMenuItem
                // 
                this.PastetoolStripMenuItem = new ToolStripMenuItem();
                this.PastetoolStripMenuItem.Size = new System.Drawing.Size(155, 22);
                this.PastetoolStripMenuItem.Text = "Paste";
                this.PastetoolStripMenuItem.Click += new System.EventHandler(this.PastetoolStripMenuItem_Click);
                this.PastetoolStripMenuItem.Image = Resource.GetImage(Resource.Images.Paste);

                // 
                // deleteToolStripMenuItem
                // 
                deleteToolStripMenuItem = new ToolStripMenuItem();
                this.deleteToolStripMenuItem.Size = new System.Drawing.Size(155, 22);
                this.deleteToolStripMenuItem.Text = "Delete";
                this.deleteToolStripMenuItem.Click += new System.EventHandler(this.deleteToolStripMenuItem_Click);
                this.deleteToolStripMenuItem.Image = Resource.GetImage(Resource.Images.Delete16);

                // 
                // setDefaultImagetoolStripMenuItem
                // 
                setDefaultImagetoolStripMenuItem = new ToolStripMenuItem();
                this.setDefaultImagetoolStripMenuItem.Size = new System.Drawing.Size(155, 22);
                this.setDefaultImagetoolStripMenuItem.Text = "Set Thumbnail Image";
                this.setDefaultImagetoolStripMenuItem.Click += new System.EventHandler(this.setDefaultImagetoolStripMenuItem_Click);
                this.setDefaultImagetoolStripMenuItem.Image = Resource.GetImage(Resource.Images.GeneraleNailImage);

                // 
                // contextMenuStrip1
                //             
                contextMenuStrip1 = new ContextMenuStrip();
                this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
                    this.CopyToolStripMenuItem,
                    this.PastetoolStripMenuItem,
                    this.deleteToolStripMenuItem,
                    this.setDefaultImagetoolStripMenuItem});
                this.contextMenuStrip1.Size = new System.Drawing.Size(156, 70);

            }
            #endregion //InitRightKeyMenu

            #region InsertLibrary
            /// <summary>
            /// Function: Insert library item to panel
            /// Author  : Jerry Xu
            /// Date    : 2008-8-13
            /// <param name="item">Inserted item</param>
            /// <param name="index">Inserted position</param>
            /// </summary>
            public void InsertLibrary(LibraryAdapter item, int index, bool isNew)
            {
                if (item != null)
                {
                    ILockLibraryItem locker = item.Target as ILockLibraryItem;
                    if (locker != null)
                        locker.IsLock = true;

                    PlaylistItemControl btn = new PlaylistItemControl(item, _unitWidth);
                    btn.OnlblNameMouseDown += new MouseEventHandler(button_MouseDown);
                    btn.OnlblNameMouseHover += new EventHandler(btn_MouseHover);
                    btn.OnlblNameMouseLeave += new EventHandler(btn_MouseLeave);
                    btn.OnlblNameDragDrop += new DragEventHandler(MessageBtn_DragDrop);
                    btn.OnlblNameDragOver += new DragEventHandler(btn_DragOver);
                    btn.OnlblNameDragEnter += new DragEventHandler(MessageBtn_DragEnter);
                    btn.OnlblNameMouseMove += new MouseEventHandler(button_MouseMove);

                    btn.MouseDown += new MouseEventHandler(button_MouseDown);
                    btn.MouseMove += new MouseEventHandler(button_MouseMove);
                    btn.MouseHover += new EventHandler(btn_MouseHover);
                    btn.MouseLeave += new EventHandler(btn_MouseLeave);
                    btn.DragEnter += new DragEventHandler(MessageBtn_DragEnter);
                    btn.DragDrop += new DragEventHandler(MessageBtn_DragDrop);
                    btn.DragOver += new DragEventHandler(btn_DragOver);
                    btn.DragLeave += new EventHandler(btn_DragLeave);
                    btn.ContextMenuStrip = contextMenuStrip1;
                    btn.KeyUp += new KeyEventHandler(MessageBtn_KeyUp);
                    btn.Click += new EventHandler(btn_Click);
                    btn.OnDurationChage += new EventHandler(OnDurationChage);
                    
                    
                    //if (btn.NailImage != null)
                    //{
                    //    using (Graphics g = Graphics.FromHwnd(_playlistCtrl.playPanel.Handle))
                    //        g.DrawImage(btn.NailImage, new Point(0, 0));
                    //}
                    
                    Insert(btn, index, isNew);
                }
            }

            void btn_MouseLeave(object sender, EventArgs e)
            {
                (sender as PlaylistItemControl).BackColor = (sender as PlaylistItemControl).BackColor == ControlService.MouseDownColor ? ControlService.MouseDownColor : ControlService.MouseLeaveColor;
            }

            void btn_MouseHover(object sender, EventArgs e)
            {
                (sender as PlaylistItemControl).BackColor = (sender as PlaylistItemControl).BackColor == ControlService.MouseDownColor ? ControlService.MouseDownColor : ControlService.MouseOverColor;
            }
            #endregion

            #region Insert
            /// <summary>
            /// Function: Insert messagebtn to panel
            /// Author  : Jerry Xu
            /// Date    : 2008-8-13
            /// <param name="item">Inserted item</param>
            /// <param name="index">Inserted position</param>
            public void Insert(PlaylistItemControl item, int index,bool isNew)
            {
                if (item != null)
                {
                    UndoService.AddPlaylistItemInsertAction(this, item, index);
                     
                    this.Controls.Add(item);

                    _playlistCtrl._changedService.MarkChanged();
                    if(this.Controls.Count==1)
                    {
                        //First insert
                        if (isNew)
                            _playlistCtrl._model.AddLast(item.PlaylistItem);
                    }
                    else
                    {
                        //Insert at middle
                        if (index != Controls.Count-1)
                        {
                            //Re playlistctrl model
                            _playlistCtrl._model.Add((Controls[index] as PlaylistItemControl).PlaylistItem, item.PlaylistItem);
                            this.Controls.SetChildIndex(item, index);                        
                            //_playlistCtrl._model.Items.
                            ReComputerLeft(index);
                        }
                        else //Inser at last
                        {
                            //this.Controls.SetChildIndex(item, index - 1);
                            this.Controls[Controls.Count - 1].Left = Controls[Controls.Count - 2].Left + Controls[Controls.Count - 2].Width + 1;
                            if (isNew)
                                _playlistCtrl._model.AddLast(item.PlaylistItem);
                        }
                    }
                    _playlistCtrl._model.AcceptChanges();

                    item.NailImage = GetNailImage(item);
                    if (item.NailImage != null && isNew)
                        _playlistCtrl.Model.ImagePath = item.PlaylistItem.Target.ImagePath;
                    if (item != null && item.NailImage != null)
                    {
                        _currentItem = item;
                        //_playlistCtrl.playPanel.BackgroundImage = btn.NailImage;
                        _NailImageIndex = item.TabIndex;
                        OnPaint();
                        if (string.IsNullOrEmpty(_playlistCtrl._model.NailImageID))
                            _playlistCtrl._model.NailImageID = item.PlaylistItem.TargetId;
                    }                    
                }
                OnUpdateTotalLength();
                
                //LocalMessageBus.Send(this, new MenuMessage(new MenuCommand[]{
                //new MenuCommand{ Command= MenuCommands.Undo, Enabled =true}}));

            }
            #endregion

            private void ReComputerLeft(int index)
            {
                for (int i = index; i < this.Controls.Count; i++)
                {
                    if (i == 0)
                        this.Controls[i].Left = 1;
                    else
                        this.Controls[i].Left = this.Controls[i - 1].Left + this.Controls[i - 1].Width + 1;
                }
            }

            #region Move
            /// <summary>
            /// Function: Move messagebtn in panel
            /// Author  : Jerry Xu
            /// Date    : 2008-8-13
            /// </summary>
            /// <param name="index">messagebtn index</param>
            public void MoveItem(int sourceIndex, int destIndex)
            {
                if (sourceIndex != destIndex && destIndex - sourceIndex != 1)
                {
                    UndoService.AddPlaylistItemMoveAction(this, sourceIndex, destIndex);

                    _playlistCtrl._changedService.MarkChanged();

                    //Move forward
                    if (sourceIndex > destIndex)
                    {
                        Controls.SetChildIndex(Controls[sourceIndex], destIndex);
                        ReComputerLeft(destIndex);
                    }
                    else
                    {//Move backward
                        Controls.SetChildIndex(Controls[sourceIndex], destIndex - 1);
                        ReComputerLeft(sourceIndex);
                    }
                    _playlistCtrl._model.MoveItem(sourceIndex, destIndex);
                    
                }
            }
            
            #endregion

            
            #region Remove item from play list
            /// <summary>
            /// Function: Remove item from play list
            /// Author  ; Jerry Xu
            /// Date    : 2008-8-14 
            /// </summary>
            public void Delete()
            {
                if (_rightMessageBtn != null)
                {
                    ILockLibraryItem locker = _rightMessageBtn.PlaylistItem.Target as ILockLibraryItem;
                    if (locker != null)
                        locker.IsLock = false;
                    if (_rightMessageBtn.PlaylistItem.Target.Type == LibraryType.Playlist)
                    {
                        (_rightMessageBtn.PlaylistItem.Target as PlaylistInfo).IsInPlaylist = false;
                    }
                    int n = Controls.GetChildIndex(_rightMessageBtn);
                    if (_NailImageIndex == _rightMessageBtn.TabIndex)
                    {
                        _playlistCtrl.playPanel.BackgroundImage = null;
                    }
                    
                    RemoveAt(n);
                    _rightMessageBtn = null;
                }
                ControlService.EnableCopyMenu(false);
            }
            #endregion

            #region Send property message
            /// <summary>
            /// Function:Send property message
            /// Author:Jerry
            /// Date:20080617 1400
            /// </summary>
            private void SendPropertyMessage()
            {
                if (_rightMessageBtn != null && _rightMessageBtn.PlaylistItem != null)
                {
                    ControlService.RefreshPropertyGrid(_rightMessageBtn.PlaylistItem.Target);
                }
            }
            #endregion

            #region Set default nail shape in play list
            /// <summary>
            /// Function: Set default nail shape in play list
            /// Author  : Jerry Xu
            /// Date    : 2008-8-14
            /// </summary>
            private void SetDefaultNailImage()
            {
                if (_rightMessageBtn == null)
                    return;
                _playlistCtrl._model.ImageAdapterName = _rightMessageBtn.PlaylistItem.Name;
                _playlistCtrl._model.Image = _rightMessageBtn.PlaylistItem.Target.Image;
                _playlistCtrl._model.ImagePath = SaveNailImage(_playlistCtrl._model.Image);
                _playlistCtrl._model.NailImageID = _rightMessageBtn.PlaylistItem.TargetId;
                
                //if(_rightMessageBtn.PlaylistItem.Target.Type == LibraryType.Message)
                //    _playlistCtrl._model.NailImageID = _rightMessageBtn.PlaylistItem.Target.Id;
                //else if (_rightMessageBtn.PlaylistItem.Target.Type == LibraryType.TimeSliceGroup)
                //{
                //    TimeSliceGroupInfo group = _rightMessageBtn.PlaylistItem.Target as TimeSliceGroupInfo;
                //    if(string.IsNullOrEmpty(group.NailImageID)
                //}
                //else if (_rightMessageBtn.PlaylistItem.Target.Type == LibraryType.Playlist)
                //{
                //}

                if (LibraryGroup.Current.Playlists.GetByName(_playlistCtrl._model.Name) == null)
                    ControlService.LibraryTree.Add(_playlistCtrl._model);
                else
                    ControlService.LibraryTree.Update(_playlistCtrl._model);
                
                ControlService.RefreshPropertyGrid(_playlistCtrl._model);
                //_playlistCtrl._changedService.MarkChanged();
            }
            #endregion

            #region RemoveAt
            /// <summary>
            /// Function: Remove messagebtn from panel
            /// Author  : Jerry Xu
            /// Date    : 2008-8-13
            /// </summary>
            /// <param name="index">messagebtn index</param>
            public void RemoveAt(int index)
            {
                ILockLibraryItem locker = (Controls[index] as PlaylistItemControl).PlaylistItem.Target as ILockLibraryItem;
                if (locker != null)
                    locker.IsLock = false;
                UndoService.AddPlaylistItemRemoveAtAction(this, Controls[index] as PlaylistItemControl, index);

                string id = (Controls[index] as PlaylistItemControl).PlaylistItem.TargetId;
                
                _playlistCtrl._model.Delete((Controls[index] as PlaylistItemControl).PlaylistItem);
                Controls.RemoveAt(index);
                if (index != Controls.Count)
                {
                    for (int i = index; i < Controls.Count; i++)
                    {
                        if (i == 0)
                            Controls[i].Left = 1;
                        else
                            Controls[i].Left = Controls[i - 1].Left + Controls[i - 1].Width + 1;
                    }
                }

                if (Controls.Count > 0 && index >= 0 && index < Controls.Count)
                {
                    //_playlistCtrl.playPanel.BackgroundImage = (Controls[index] as PlaylistItemControl).NailImage; //(Controls[index] as PlaylistItemControl).PlaylistItem.Target.Image; //GetNailImage(Controls[index] as PlaylistItemControl);
                    if ((Controls[index] as PlaylistItemControl).NailImage!=null)
                        using (Graphics g = Graphics.FromHwnd(_playlistCtrl.playPanel.Handle))
                            g.DrawImage((Controls[index] as PlaylistItemControl).NailImage, new Point(0, 0));
                    _currentItem = Controls[index] as PlaylistItemControl;
                    _NailImageIndex = (Controls[index] as PlaylistItemControl).TabIndex;

                }
                else if (Controls.Count > 0 && index >= 0 && index == Controls.Count)
                {
                    //_playlistCtrl.playPanel.BackgroundImage = (Controls[index - 1] as PlaylistItemControl).NailImage; //(Controls[index-1] as PlaylistItemControl).PlaylistItem.Target.Image;//GetNailImage(Controls[index - 1] as PlaylistItemControl);
                    if ((Controls[index-1] as PlaylistItemControl).NailImage != null)
                        using (Graphics g = Graphics.FromHwnd(_playlistCtrl.playPanel.Handle))
                            g.DrawImage((Controls[index-1] as PlaylistItemControl).NailImage, new Point(0, 0));
                    _currentItem = Controls[index - 1] as PlaylistItemControl;
                    _NailImageIndex = (Controls[index - 1] as PlaylistItemControl).TabIndex;
                }
                else
                {
                    _currentItem = null;
                    //_playlistCtrl.playPanel.BackgroundImage = null;
                    //_playlistCtrl.playPanel.BackColor = this._playlistCtrl.BackColor;
                    //using (Graphics g = Graphics.FromHwnd(_playlistCtrl.playPanel.Handle))
                    //{
                    //    //Image shape = new Bitmap(_playlistCtrl.playPanel.Width,_playlistCtrl.playPanel.Height);
                    //    ////g.b
                        
                    //    //g.DrawImage(shape, new Point(0, 0));                        
                    //    Bitmap img = new Bitmap(_playlistCtrl.playPanel.Width, _playlistCtrl.playPanel.Height);
                    //    using (var g = Graphics.FromImage(img))
                    //        g.DrawImage(item.PlaylistItem.Target.Image, new Rectangle((_playlistCtrl.playPanel.Width - newLastWidth) / 2, (_playlistCtrl.playPanel.Height - newLastHeight) / 2, newLastWidth, newLastHeight), new Rectangle(0, 0, item.PlaylistItem.Target.Image.Width, item.PlaylistItem.Target.Image.Height), GraphicsUnit.Pixel);
                    //    //_NailPlaylistItemItem = item;
                    //    return img;
                    //}
                    _NailImageIndex = 0;
                    //_playlistCtrl.playPanel.BackColor = this._playlistCtrl.BackColor;
                }
                if (id == _playlistCtrl._model.NailImageID && _currentItem != null)
                    _playlistCtrl._model.NailImageID = _currentItem.PlaylistItem.TargetId;

                _playlistCtrl._model.AcceptChanges();
                _playlistCtrl._changedService.MarkChanged();
                ControlService.EnableCopyMenu(false);
                OnUpdateTotalLength();
                _rightMessageBtn = null;
                _sourceMessageBtn = null;
                if (ItemSelectChange != null)
                    ItemSelectChange(this, new EventArgs());
                OnPaint();
            }
            #endregion

            #region Update playlist total length
            /// <summary>
            /// Function:Update playlist total length
            /// Author: Jerry Xu
            /// Date:2008-8-14
            /// </summary>
            private void UpdateTotalTimes()
            {
                string strPos = string.Empty;
                int intPos = 0;
                PlaylistItemControl btn = null;
                if (Controls.Count != 0)
                {
                    btn = Controls[Controls.Count - 1] as PlaylistItemControl;
                    intPos = btn.Left + btn.Width;
                }
                //Get total length by position and unitwidth and tick
                strPos = Common.CommonHelper.ConvertPixelToLabelTime(intPos, Constance.TrackBar.UnitWidth, Constance.TrackBar.Tick);
                _playlistCtrl._model.Length = Common.CommonHelper.ConvertLabelTimeToSecond(strPos, Constance.TrackBar.Tick);
                
                //_totalLength = Commons.Helper.ConvertLabelTimeToSecond(strPos, Constance.TrackBar.Tick);
                //LocalMessageBus.Send(this, new PlaylistsUpdateMessageTotalLengthMessage(strPos));
            }
            #endregion

            #region Zoom
            /// <summary>
            /// Function:Zoom
            /// Author:Jerry Xu
            /// Date:2008-6-17
            /// </summary>
            /// <param name="pZoomType">ZoomType:Enum</param>
            public void Zoom(ZoomType pZoomType)
            {
                //Zoom the dragdraplayoutcontrol out
                if (pZoomType == ZoomType.ZoomOut)
                {
                    _unitWidth = _unitWidth * 2;
                    for (int i = 0; i < Controls.Count; i++)
                    {
                        Controls[i].Width = Controls[i].Width * 2;
                        (Controls[i] as PlaylistItemControl).UnitWidth = _unitWidth;
                        if (i != 0)
                            Controls[i].Left = Controls[i - 1].Left + Controls[i - 1].Width;

                    }
                    _zoomaction = ZoomType.ZoomNone;
                }
                //Zoom the dragdraplayoutcontrol in
                if (pZoomType == ZoomType.ZoomIn)
                {
                    _unitWidth = _unitWidth / 2;
                    for (int i = 0; i < Controls.Count; i++)
                    {
                        Controls[i].Width = Controls[i].Width / 2;
                        (Controls[i] as PlaylistItemControl).UnitWidth = _unitWidth;
                        if (i != 0)
                            Controls[i].Left = Controls[i - 1].Left + Controls[i - 1].Width;

                    }
                    _zoomaction = ZoomType.ZoomNone;
                }

            }
            #endregion

            private void SetSelectBackColor()
            {
                if (_sourceMessageBtn == null)
                    return;                
                foreach (Control item in Controls)
                {
                    item.BackColor = ControlService.MouseLeaveColor;
                }
                _sourceMessageBtn.BackColor = ControlService.MouseDownColor;
            }
            #endregion

            #region Event define
            
            void btn_Click(object sender, EventArgs e)
            {
                
            }

            void btn_DragLeave(object sender, EventArgs e)
            {
                _playlistCtrl.dragDropLine1.Visible = false;
            }

            private void MessageBtn_KeyUp(object sender, KeyEventArgs e)
            {
                if (e.KeyCode == Keys.Delete)
                {
                    if (MsgBox.Confirm(Resource.GetString(Resources.Resource.Strings.ConfirmDeleteItem)) == DialogResult.Yes)
                    {
                        Delete();
                    }
                }
            }

            #region PlaylistItemControl mousedown event
            /// <summary>
            /// Function:PlaylistItemControl mousedown event
            /// Author:Jerry Xu
            /// Date:2008-6-17
            /// </summary>
            /// <param name="sender"></param>
            /// <param name="e"></param>
            private void button_MouseDown(object sender, MouseEventArgs e)
            {
                _rightMessageBtn = sender as PlaylistItemControl;
                ControlService.EnableCopyMenu(true);
                this.CopyToolStripMenuItem.Enabled = CopyAction.Current.CanCopy;
                this.PastetoolStripMenuItem.Enabled = CopyAction.Current.CanPaste;

                if (e.Button == MouseButtons.Left)
                {
                    _sourceMessageBtn = sender as PlaylistItemControl;
                    if (_sourceMessageBtn.PlaylistItem.Target != null)
                    {
                        ControlService.RefreshPropertyGrid(new LibraryPropertys( _sourceMessageBtn.PlaylistItem.Target));
                        ControlService.NailImageBox.Image = _sourceMessageBtn.NailImage; //_sourceMessageBtn.PlaylistItem.Target.Image;
                    }
                    SetSelectBackColor(); 
                    Size dragSize = SystemInformation.DragSize;
                    // Create a rectangle using the DragSize, with the mouse position being
                    // at the center of the rectangle.
                    _dragBoxFromMouseDown = new Rectangle(new Point(e.X - (dragSize.Width / 2),
                                                                   e.Y - (dragSize.Height / 2)), dragSize);
                    if (_sourceMessageBtn.NailImage != null)
                    {
                        _NailImageIndex = _sourceMessageBtn.TabIndex;
                        _currentItem = _sourceMessageBtn;
                        OnPaint();
                    }
                        //using (Graphics g = Graphics.FromHwnd(_playlistCtrl.playPanel.Handle))
                          //  g.DrawImage(_sourceMessageBtn.NailImage, new Point(0, 0));

                    //_playlistCtrl.playPanel.BackgroundImage = _sourceMessageBtn.NailImage; //GetNailImage(_sourceMessageBtn);//_sourceMessageBtn.PlaylistItem.Target.Image; 
                    
                    if (ItemSelectChange != null)
                        ItemSelectChange(this, new EventArgs());
                }
            }

            private void DrawLabelLine(Control control, Point location)
            {
                //Move item
                if (_sourceMessageBtn != null)
                {
                    if (_sourceMessageBtn == (control as PlaylistItemControl))
                    {
                        _playlistCtrl.dragDropLine1.Visible = false;
                        return;
                    }
                    int sourceIndex = Controls.GetChildIndex(_sourceMessageBtn);
                    int targetIndex = Controls.GetChildIndex(control);
                    Point pt = control.PointToClient(location);
                    if (Math.Abs(sourceIndex - targetIndex) == 1)
                    {
                        if (sourceIndex > targetIndex)
                        {
                            if (pt.X > control.Width / 2)
                            {
                                _playlistCtrl.dragDropLine1.Visible = false;
                                return;
                            }
                        }
                        else
                        {
                            if (pt.X < control.Width / 2)
                            {
                                _playlistCtrl.dragDropLine1.Visible = false;
                                return;
                            }
                        }
                    }

                    int picX;

                    if (pt.X > (control.Width / 2))
                        picX = this.Left + control.Left + control.Width + 1;
                    else
                        picX = this.Left + control.Left - 1;

                    _playlistCtrl.dragDropLine1.Location = new Point(picX, 1 + this.Top);
                    _playlistCtrl.dragDropLine1.Visible = true;
                }
                else
                {
                    //DragDrop:Library tree->Playlist
                    int targetIndex = Controls.GetChildIndex(control);
                    Point pt = control.PointToClient(location);
                    int picX;
                    if (pt.X > (control.Width / 2))
                        picX = this.Left + control.Left + control.Width + 1;
                    else
                        picX = this.Left + control.Left - 1;

                    _playlistCtrl.dragDropLine1.Location = new Point(picX, 1 + this.Top);
                    _playlistCtrl.dragDropLine1.Visible = true;
                }
            }

            void btn_DragOver(object sender, DragEventArgs e)
            {
                DrawLabelLine(sender as Control, new Point(e.X, e.Y));
            }
            #endregion

            #region PlaylistItemControl mousemove event
            /// <summary>
            /// Function:PlaylistItemControl mousemove event
            /// Author:Jerry Xu
            /// Date:2008-6-17
            /// </summary>
            /// <param name="sender"></param>
            /// <param name="e"></param>
            private void button_MouseMove(object sender, MouseEventArgs e)
            {
                if ((e.Button & MouseButtons.Left) == MouseButtons.Left)
                {
                    this.DoDragDrop(Controls.GetChildIndex(sender as Control), DragDropEffects.Copy | DragDropEffects.All | DragDropEffects.Move);
                }
            }
            #endregion

            private void DrawPanelLabelLine(Control control, Point location)
            {
                if (Controls.Count == 0)
                    return;
                Point pt = control.PointToClient(location);
                if (pt.X < control.Controls[0].Location.X)
                {
                    _playlistCtrl.dragDropLine1.Location = new Point(control.Left + control.Controls[0].Left - 1, control.Top + 1);
                    _playlistCtrl.dragDropLine1.Visible = true;
                }

                if (pt.X > control.Controls[control.Controls.Count - 1].Left + control.Controls[control.Controls.Count - 1].Width)
                {
                    _playlistCtrl.dragDropLine1.Location = new Point(control.Left + control.Controls[this.Controls.Count - 1].Left + control.Controls[control.Controls.Count - 1].Width + 1, control.Top + 1);
                    _playlistCtrl.dragDropLine1.Visible = true;
                }
            }

            protected override void OnDragOver(DragEventArgs drgevent)
            {
                DrawPanelLabelLine(this as Control, new Point(drgevent.X, drgevent.Y));
            }

            protected override void OnDragDrop(DragEventArgs e)
            {
                try
                {   
                    LibraryNode newNode;//The TreeNode of be draged 
                    #region DragDrop TreeNode
                    //it is TreeListNode or no which the control was draged    
                    //Drag LibrayNode to DragDropPanel at last
                    if (e.Data.GetDataPresent(typeof(LibraryNode)))
                    {
                        newNode = (LibraryNode)e.Data.GetData(typeof(LibraryNode));
                        MemoryLibraryItem source = (MemoryLibraryItem)(newNode.Tag);
                        if (source.Type == LibraryType.Playlist && source.Name == _playlistCtrl.Model.Name)
                        {
                            MsgBox.Warning(Resource.GetString(Resource.Strings.PlaylistNotDragItself));
                            return;
                        }

                        if (source != null && source.Length == 0)
                        {
                            if (source.Type == LibraryType.Message)
                            {
                                MsgBox.Warning(Resource.GetString(Resource.Strings.PlayListMessageLengthEmpty));
                            }
                            if (source.Type == LibraryType.Playlist)
                            {
                                MsgBox.Warning(Resource.GetString(Resource.Strings.PlayListPlayListLengthEmpty));
                            }
                            if (source.Type == LibraryType.TimeSliceGroup)
                            {
                                MsgBox.Warning(Resource.GetString(Resource.Strings.PlayListTimeSliceGroupLengthEmpty));
                            }
                            _playlistCtrl.dragDropLine1.Visible = false; 
                            return;
                        }
                        if (source.Type == LibraryType.TimeSliceGroup)
                        {
                            TimeSliceGroupInfo group = source as TimeSliceGroupInfo;
                            if (group.Items == null || group.Items.Length == 0)
                            {
                                MsgBox.Warning(Resource.GetString(Resource.Strings.PlayListTimeSliceGroupLengthEmpty));
                                _playlistCtrl.dragDropLine1.Visible = false;
                                return;
                            }
                        }
                        if (source.Type == LibraryType.Playlist)
                        {
                            PlaylistInfo playlist = source as PlaylistInfo;
                            if (playlist.Items == null || playlist.Items.Length == 0)
                            {
                                MsgBox.Warning(Resource.GetString(Resource.Strings.PlayListPlayListLengthEmpty));
                                _playlistCtrl.dragDropLine1.Visible = false;
                                return;
                            }
                            if (playlist.IsManyLevel || _playlistCtrl.Model.IsInPlaylist)
                            {
                                MsgBox.Warning(Resource.GetString(Resource.Strings.PlaylistManyLevel));
                                _playlistCtrl.dragDropLine1.Visible = false;
                                return;
                            }
                            playlist.IsInPlaylist = true;
                        }
                        InsertLibrary(source.ToProxy(), this.Controls.Count, true);
                    }
                    else //Move messagebtn to dragdroppanel last
                    {
                        if (_sourceMessageBtn != null)
                        {
                            if (Controls.GetChildIndex(_sourceMessageBtn as Control) == Controls.Count - 1)
                            {
                                _playlistCtrl.dragDropLine1.Visible = false;
                                return;
                            }
                            int sourceIndex = Controls.GetChildIndex(_sourceMessageBtn);
                            int destIndex = Controls.Count;
                            MoveItem(sourceIndex, destIndex);
                        }
                    }
                    #endregion
                    _playlistCtrl.dragDropLine1.Visible = false;
                    //LocalMessageBus.Send(this, new MenuMessage(new MenuCommand[]{
                    //        new MenuCommand(MenuCommands.Save,true)
                    //        , new MenuCommand(MenuCommands.SaveAs,true)
                    //        }));
                    //_playlistCtrl.ChangedService.MarkChanged();
                    //_playlistCtrl.ChangedService. = true;
                }
                catch (Exception ex)
                {
                    DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListDragDropLayoutControlPanelControlDragDropEventException), ex);
                }
            }

            private void MessageBtn_DragDrop(object sender, DragEventArgs e)
            {
                try
                {
                    LibraryNode newNode;//The TreeNode of be draged               

                    #region DragDrop TreeNode
                    //it is TreeListNode or no which the control was draged     
                    //Drag LibraryNod to dragdroppanel's messagebtn
                    if (e.Data.GetDataPresent(typeof(LibraryNode)))
                    {
                        newNode = (LibraryNode)e.Data.GetData(typeof(LibraryNode));
                        MemoryLibraryItem source = null;
                        PlaylistItemControl dest = null;
                        source = (MemoryLibraryItem)(newNode.Tag);
                        if (source.Type == LibraryType.Playlist && source.Name == _playlistCtrl.Model.Name)
                        {
                            MsgBox.Warning(Resource.GetString(Resource.Strings.PlaylistNotDragItself));
                            return;
                        }
                        if (source != null && source.Length == 0)
                        {
                            if (source.Type == LibraryType.Message)
                            {
                                MsgBox.Warning(Resource.GetString(Resource.Strings.PlayListMessageLengthEmpty));
                            }
                            if (source.Type == LibraryType.Playlist)
                            {
                                MsgBox.Warning(Resource.GetString(Resource.Strings.PlayListPlayListLengthEmpty));
                            }
                            if (source.Type == LibraryType.TimeSliceGroup)
                            {
                                MsgBox.Warning(Resource.GetString(Resource.Strings.PlayListTimeSliceGroupLengthEmpty));
                            }
                            _playlistCtrl.dragDropLine1.Visible = false; 
                            return;
                        }
                        if (source.Type == LibraryType.TimeSliceGroup)
                        {
                            TimeSliceGroupInfo group = source as TimeSliceGroupInfo;
                            if (group.Items == null || group.Items.Length == 0)
                            {
                                MsgBox.Warning(Resource.GetString(Resource.Strings.PlayListTimeSliceGroupLengthEmpty));
                                _playlistCtrl.dragDropLine1.Visible = false;
                                return;
                            }
                        }
                        if (source.Type == LibraryType.Playlist)
                        {
                            PlaylistInfo playlist = source as PlaylistInfo;
                            if (playlist.Items == null || playlist.Items.Length == 0)
                            {
                                MsgBox.Warning(Resource.GetString(Resource.Strings.PlayListPlayListLengthEmpty));
                                _playlistCtrl.dragDropLine1.Visible = false;
                                return;
                            }
                            if (playlist.IsManyLevel || _playlistCtrl.Model.IsInPlaylist)
                            {
                                MsgBox.Warning(Resource.GetString(Resource.Strings.PlaylistManyLevel));
                                _playlistCtrl.dragDropLine1.Visible = false;
                                return;
                            }
                            playlist.IsInPlaylist = true;
                        }
                        dest = sender as PlaylistItemControl;

                        Point pt = dest.PointToClient(new Point(e.X, e.Y));

                        int index = Controls.GetChildIndex(dest);

                        if (pt.X > (dest.Width / 2))
                            index = index + 1;

                        InsertLibrary(source.ToProxy(), index, true);
                    }
                    else //Move messagebtn to dragdroppanel's messagebtn
                    {
                        PlaylistItemControl dest = sender as PlaylistItemControl;
                        if (dest != null && _sourceMessageBtn != null)
                        {
                            int sourceIndex = Controls.GetChildIndex(_sourceMessageBtn);
                            int destIndex = Controls.GetChildIndex(dest);

                            Point pt = dest.PointToClient(new Point(e.X, e.Y));

                            //source = dest
                            if (sourceIndex == destIndex)
                            {
                                _sourceMessageBtn = null;
                                _playlistCtrl.dragDropLine1.Visible = false;
                                return;
                            }

                            //abs(sourceIndex - destIndex) = 1
                            if (Math.Abs(sourceIndex - destIndex) == 1)
                            {
                                if (sourceIndex > destIndex)
                                {
                                    if (pt.X > dest.Width / 2)
                                    {
                                        _sourceMessageBtn = null;
                                        _playlistCtrl.dragDropLine1.Visible = false;
                                        return;
                                    }
                                }
                                else
                                {
                                    if (pt.X < dest.Width / 2)
                                    {
                                        _sourceMessageBtn = null;
                                        _playlistCtrl.dragDropLine1.Visible = false;
                                        return;
                                    }
                                    else
                                        destIndex = destIndex + 1;
                                }
                            }
                            else
                            {
                                if (pt.X > (dest.Width / 2))
                                    destIndex = destIndex + 1;
                            }

                            MoveItem(sourceIndex, destIndex);
                        }
                    }
                    #endregion
                    _sourceMessageBtn = null;
                    _playlistCtrl.dragDropLine1.Visible = false;
                }
                catch (Exception ex)
                {
                    DataGate.Log.Error(Resource.GetString(Resource.Strings.PlayListDragDropLayoutControlPanelControlDragDropEventException), ex);
                }
            }

            protected override void OnDragEnter(DragEventArgs e)
            {
                this.Focus();
                e.Effect = DragDropEffects.Copy | DragDropEffects.All;
                base.OnDragEnter(e);
            }

            protected override void OnDragLeave(EventArgs e)
            {                
                base.OnDragLeave(e);
                _playlistCtrl.dragDropLine1.Visible = false;
            }

            private void MessageBtn_DragEnter(object sender, DragEventArgs e)
            { 
                e.Effect = DragDropEffects.Copy | DragDropEffects.All;
                base.OnDragEnter(e);
            }

            private void CopyToolStripMenuItem_Click(object sender, EventArgs e)
            {
                if (CopyAction.Current != null) 
                { 
                    CopyAction.Current.Copy(); 
                }
            }

            private void PastetoolStripMenuItem_Click(object sender, EventArgs e)
            {
                if (CopyAction.Current != null) 
                { 
                    CopyAction.Current.Paste(); 
                }
            }

            private void deleteToolStripMenuItem_Click(object sender, EventArgs e)
            {
                if (MsgBox.Confirm(Resource.GetString(Resources.Resource.Strings.ConfirmDeleteItem)) == DialogResult.Yes)
                {
                    Delete();
                }
            }

            private void setDefaultImagetoolStripMenuItem_Click(object sender, EventArgs e)
            {
                SetDefaultNailImage();
            }

            private void OnDurationChage(object o, EventArgs e)
            {
               PlaylistItemControl item= o as PlaylistItemControl;

               for (int i = item.Order + 1; i < this.Controls.Count; i++)
               {
                   this.Controls[i].Left = this.Controls[i - 1].Right;
               }
               OnUpdateTotalLength();
            }

            private EventHandler<UpdateTotalLengthEventArgs> _UpdateTotalLength;
            public event EventHandler<UpdateTotalLengthEventArgs> UpdateTotalLength
            {
                add { _UpdateTotalLength += value; }
                remove { _UpdateTotalLength -= value; }
            }

            private void OnUpdateTotalLength()
            {
                string strPos = string.Empty;
                int intPos = 0;
                PlaylistItemControl btn = null;
                if (Controls.Count != 0)
                {
                    btn = Controls[Controls.Count - 1] as PlaylistItemControl;
                    intPos = btn.Left + btn.Width;
                }
                //Get total length by position and unitwidth and tick
                strPos = Common.CommonHelper.ConvertPixelToTime(intPos, _unitWidth, Constance.TrackBar.Tick);
                _totalLength = strPos;
                _playlistCtrl._model.Length = Common.CommonHelper.ConvertLabelTimeToSecond(strPos, _tick);
                _UpdateTotalLength(this, new UpdateTotalLengthEventArgs(_totalLength));

                if (intPos > this.ClientRectangle.Right - defaultWidth)
                {
                    OnUpdateTotalWidth(intPos);
                }
            }

            private EventHandler<UpdateTotalWidthEventArgs> _UpdateMaxWidth;
            public event EventHandler<UpdateTotalWidthEventArgs> UpdateMaxWidth
            {
                add { _UpdateMaxWidth += value; }
                remove { _UpdateMaxWidth -= value; }
            }
            private void OnUpdateTotalWidth(int pos)
            {
                this.Width += pos + _scrollWidth;
                _UpdateMaxWidth(this, new UpdateTotalWidthEventArgs(pos+_scrollWidth));

            }

            public void PopulateSize()
            {
                if (Controls.Count > 0)
                {
                    int temp = 0;
                    if(_currentItem!=null)
                        temp = Controls.GetChildIndex(_currentItem as Control);
                    foreach (Control item in Controls)
                    {
                        (item as PlaylistItemControl).NailImage = GetNailImage((item as PlaylistItemControl));                        
                    }
                                     
                    _currentItem = Controls[temp] as PlaylistItemControl;
                }
            }

            public Image GetNailImage1(PlaylistItemControl item)
            {
                if (item.PlaylistItem.Target.Image != null)
                {
                    decimal wRate = decimal.Divide(item.PlaylistItem.Target.Image.Width, _playlistCtrl.playPanel.Width);
                    decimal hRate = decimal.Divide(item.PlaylistItem.Target.Image.Height, _playlistCtrl.playPanel.Height);
                    decimal newWidth, newHeight, _zoom = 1;

                    if (wRate > hRate)
                    {
                        _zoom = decimal.Divide(_playlistCtrl.playPanel.Width,item.PlaylistItem.Target.Image.Width);
                        //_zoom = _zoom == 0 ? 1 : _zoom;
                        newWidth = item.PlaylistItem.Target.Image.Width * _zoom;
                        newHeight = item.PlaylistItem.Target.Image.Height * _zoom;
                    }
                    else
                    {
                        _zoom = decimal.Divide(_playlistCtrl.playPanel.Height, item.PlaylistItem.Target.Image.Height);
                        //_zoom = _zoom == 0 ? 1 : _zoom;
                        newWidth = item.PlaylistItem.Target.Image.Width * _zoom;
                        newHeight = item.PlaylistItem.Target.Image.Height * _zoom;
                    }

                    int newLastWidth, newLastHeight;
                    newLastWidth = decimal.ToInt32(newWidth);
                    newLastHeight = decimal.ToInt32(newHeight);

                    Bitmap img = ImageHelper.ReSizeImage(item.PlaylistItem.Target.Image, newLastWidth, newLastHeight);

                    //Bitmap img = new Bitmap(_playlistCtrl.playPanel.Width, _playlistCtrl.playPanel.Height);
                    //using (var g = Graphics.FromImage(img))
                    //    g.DrawImage(img1,
                    //                new Rectangle((_playlistCtrl.playPanel.Width - newLastWidth) / 2,
                    //                                (_playlistCtrl.playPanel.Height - newLastHeight) / 2,
                    //                                    newLastWidth,
                    //                                    newLastHeight),
                    //                new Rectangle(0,
                    //                                0,
                    //                                img1.Width,
                    //                                img1.Height),
                    //                GraphicsUnit.Pixel);
                    //_NailPlaylistItemItem = item;
                    return img;
                }
                else
                {
                    Image nailImage = null;
                    if (item.PlaylistItem.Target.Type == LibraryType.Message)
                        nailImage = NailImageGenerator.GenerateNailImage(item.PlaylistItem.Target as MessageInfo, this._playlistCtrl.playPanel.ClientRectangle);
                    else if (item.PlaylistItem.Target.Type == LibraryType.TimeSliceGroup)
                    {
                        TimeSliceGroupInfo group = item.PlaylistItem.Target as TimeSliceGroupInfo;
                        if (string.IsNullOrEmpty(group.NailImageID) || LibraryGroup.Current.Messages.GetById(group.NailImageID) == null)
                            return null;
                        nailImage = NailImageGenerator.GenerateNailImage(LibraryGroup.Current.Messages.GetById(group.NailImageID), this._playlistCtrl.playPanel.ClientRectangle);
                    }
                    else if (item.PlaylistItem.Target.Type == LibraryType.Playlist)
                    {
                        PlaylistInfo playlist = item.PlaylistItem.Target as PlaylistInfo;
                        if (string.IsNullOrEmpty(playlist.NailImageID) || LibraryGroup.Current.Messages.GetById(playlist.NailImageID) == null)
                            return null;
                        nailImage = NailImageGenerator.GenerateNailImage(LibraryGroup.Current.Messages.GetById(playlist.NailImageID), this._playlistCtrl.playPanel.ClientRectangle);
                    }
                    item.PlaylistItem.Target.Image = nailImage;
                    return nailImage;
                }
            }

            public Image GetNailImage(PlaylistItemControl item)
            {
                if (item.PlaylistItem.Target.Image != null)
                {

                    Bitmap img = ImageHelper.ReSizeImagePlaylist(item.PlaylistItem.Target.Image, _playlistCtrl.playPanel.ClientRectangle.Width, _playlistCtrl.playPanel.ClientRectangle.Height);
                    //img.Save("c:\\a.jpg");
                    //Bitmap img = new Bitmap(_playlistCtrl.playPanel.Width, _playlistCtrl.playPanel.Height);
                    //using (var g = Graphics.FromImage(img))
                    //    g.DrawImage(img1,
                    //                new Rectangle((_playlistCtrl.playPanel.Width - newLastWidth) / 2,
                    //                                (_playlistCtrl.playPanel.Height - newLastHeight) / 2,
                    //                                    newLastWidth,
                    //                                    newLastHeight),
                    //                new Rectangle(0,
                    //                                0,
                    //                                img1.Width,
                    //                                img1.Height),
                    //                GraphicsUnit.Pixel);
                    //_NailPlaylistItemItem = item;
                    return img;
                    //return SplitImage(img);
                }
                else
                {
                    return null;
                }
            }

            private Image SplitImage(Image img1)
            {
                Bitmap image = new Bitmap(img1); //("c:\\3.bmp");
                int Height = image.Height;
                int Width = image.Width;

                //定义将图片切分成四个部分的区域
                RectangleF[] block = new RectangleF[2];
                block[0] = new Rectangle(0, 0, 10, Height);
                block[1] = new Rectangle(10, 0, Width - 10, Height);

                //分别克隆图片的四个部分	
                Bitmap[] s = new Bitmap[2];
                s[0] = image.Clone(block[0], PixelFormat.Format32bppPArgb);
                s[1] = image.Clone(block[1], PixelFormat.Format32bppPArgb);
                //绘制图片的四个部分，各部分绘制时间间隔为1秒

                Bitmap img = new Bitmap(Width, Height);
                using (var g = Graphics.FromImage(img))
                {
                    g.DrawImage(s[0],
                                new Rectangle(Width - 10, 0, 10, Height),

                                new Rectangle(0,
                                                0,
                                                s[0].Width,
                                                s[0].Height),
                                GraphicsUnit.Pixel);
                    g.DrawImage(s[1],
                        new Rectangle(0, 0, Width - 10, Height),
                        new Rectangle(0, 0, s[1].Width, s[1].Height),
                        GraphicsUnit.Pixel);
                }
                return img;
                //img.Save("c:\\3_bak.bmp", ImageFormat.Bmp);
            }
            #endregion
        }
    }
}
