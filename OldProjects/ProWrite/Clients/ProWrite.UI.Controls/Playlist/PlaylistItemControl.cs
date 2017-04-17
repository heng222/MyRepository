//---------------------------------------------------------------------
//
// File: PlaylistItemControl.cs
//
// Description:
//      PlaylistItem Control
//
// Author: Jerry Xu
// Date  : 2008-10-22
//
//Modify History:
//      Jerry Xu 2009-3-16 Add new property:NailImage
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using DevExpress.XtraEditors;
using ProWrite.Entity.Library;
using System.Drawing;
using System.Windows.Forms;
using ProWrite.Resources;

using ProWrite.Core;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;
using System.Communication.Messaging;

namespace ProWrite.UI.Controls.Playlist
{
    public class PlaylistItemControl: Button
    {
        private class Images
        {
            internal static ImageList imageList;
            static LibraryType[] types;
            static Images()
            {
                imageList = new ImageList();
                imageList.Images.Add(Resource.GetImage(Resource.Images.InsertTimeSliceGroup16.ToString()));
                imageList.Images.Add(Resource.GetImage(Resource.Images.MessageIcon16x16.ToString()));
                imageList.Images.Add(Resource.GetImage(Resource.Images.PlaylistIcon16x16.ToString()));

                types = new LibraryType[]{
                    LibraryType.TimeSliceGroupProxy
                    , LibraryType.MessageProxy
                    , LibraryType.PlaylistProxy
                };

            }

            internal static int GetIndex(LibraryType type)
            {
                return Array.IndexOf(types, type);
            }

        }

        #region Variant define
        private LibraryAdapter _playlistItem;
        private int _order = 0;
        private Rectangle _initRect;
        private string _durationTxt = string.Empty;
        public event EventHandler OnDurationChage = null;
        public event MouseEventHandler OnlblNameMouseDown = null;
        public event EventHandler OnlblNameMouseHover = null;
        public event EventHandler OnlblNameMouseLeave = null;
        public event DragEventHandler OnlblNameDragDrop = null;
        public event DragEventHandler OnlblNameDragOver = null;
        public event DragEventHandler OnlblNameDragEnter = null;
        public event MouseEventHandler OnlblNameMouseMove = null;
        public Label lblName = new Label();
        private string strToolTip;
        private ToolTip toolTip1 = new ToolTip();
        private static Brush brush = Brushes.Black;
        #endregion

        public PlaylistItemControl(LibraryAdapter item)
        {
            this.Text = "";
        }

        
        public PlaylistItemControl(LibraryAdapter item,int unitWidth)
        {
            this.lblName.TextAlign = ContentAlignment.TopCenter;
            this.lblName.BackColor = Color.Transparent;
            this.lblName.Width = this.Width;
            this.lblName.Dock = DockStyle.Bottom;
            this.lblName.MouseDown += new MouseEventHandler(lblName_MouseDown);
            this.lblName.MouseMove += new MouseEventHandler(lblName_MouseMove);
            this.lblName.MouseHover += new EventHandler(lblName_MouseHover);
            this.lblName.MouseLeave += new EventHandler(lblName_MouseLeave);
            this.lblName.DragDrop += new DragEventHandler(lblName_DragDrop);
            this.lblName.DragOver += new DragEventHandler(lblName_DragOver);
            this.lblName.DragEnter += new DragEventHandler(lblName_DragEnter);
            this.lblName.Text = item.Target.Name;
            this.Controls.Add(lblName);

            this.Text = "";
            this.BackColor = ControlService.MouseLeaveColor;
            this.AllowDrop = true;
            this.ImageAlign = ContentAlignment.TopLeft;
            this.TextAlign = ContentAlignment.BottomCenter;
            ImageList = Images.imageList;
            ImageIndex = Images.GetIndex(item.Type);
            SetTitle(this.lblName.Text, item.Target.Type.ToString(), item.Target.LengthText);
            Width = item.Target.Length * unitWidth;

            _durationTxt = item.Target.LengthText;
            if (_durationTxt.Substring(0, 2) == "00")
                _durationTxt = _durationTxt.Substring(3, _durationTxt.Length - 3);

            Top = 10;
            Height = 48;
            if (item.Type == LibraryType.TimeSliceGroupProxy)
            {
                TimeSliceGroupInfo group = item.Target as TimeSliceGroupInfo;
                foreach (MessageAdapterInfo adp in group.Items)
                {
                    if (adp.IsActive)
                    {
                        (item as TimeSliceGroupAdapterInfo).CurrentMessageAdapterName = adp.Name;
                        break;
                    }
                }
            }
            _playlistItem = item;
            _initRect = new Rectangle(this.Width - 40, 8, 35, 30);
            LocalMessageBus.Subject<LibraryRenameMessage>().Observers += new ObserverHandler<LibraryRenameMessage>(OnLibraryRename);
            //LocalMessageBus.Subject<LibraryImageChangeMessage>().Observers += new ObserverHandler<LibraryImageChangeMessage>(OnLibraryImageChange);
        }

        //void OnLibraryImageChange(object sender, LibraryImageChangeMessage msg)
        //{
        //    NailImage = (LibraryGroup.Current.GetByName(msg.Name, msg.Type) as MemoryLibraryItem).Image;
        //}

        void lblName_MouseMove(object sender, MouseEventArgs e)
        {
            if (OnlblNameMouseMove != null)
            {
                OnlblNameMouseMove(this, e);
            }
        }

        void lblName_DragEnter(object sender, DragEventArgs e)
        {
            if (OnlblNameDragEnter != null)
            {
                OnlblNameDragEnter(this, e);
            }
        }

        void lblName_DragOver(object sender, DragEventArgs e)
        {
            if (OnlblNameDragOver != null)
            {
                OnlblNameDragOver(this, e);
            }
        }

        void lblName_DragDrop(object sender, DragEventArgs e)
        {
            if (OnlblNameDragDrop != null)
            {
                OnlblNameDragDrop(this, e);
            }
        }

        void lblName_MouseLeave(object sender, EventArgs e)
        {
            if (OnlblNameMouseLeave != null)
            {
                OnlblNameMouseLeave(this, e);
            }
        }

        void lblName_MouseHover(object sender, EventArgs e)
        {
            if (OnlblNameMouseHover != null)
            {
                OnlblNameMouseHover(this, e);
            }
        }

        void lblName_MouseDown(object sender, MouseEventArgs e)
        {
            if (OnlblNameMouseDown != null)
            {
                OnlblNameMouseDown(this, e);
            }
        }

        #region Properties define
        
        public LibraryAdapter PlaylistItem
        {
            set { _playlistItem = value; }
            get { return _playlistItem; }
        }
        public int Order
        {
            set { _order = value; }
            get { return _order; }
        }
        private int _unitWidth = Constance.TrackBar.UnitWidth;
        public int UnitWidth
        {
            set { _unitWidth = value; }
            get { return _unitWidth; }
        }
        public Image NailImage { get; set; }
        #endregion

        #region Functions define

       
        /// <summary>
        /// Function: Config target rectangle
        /// Author  : Jerry Xu
        /// Date    : 2008-8-21
        /// </summary>
        /// <param name="shape">Image</param>
        /// <param name="sourceRect">Rectangle</param>
        /// <returns>Rectangle:target</returns>
        private Rectangle GetTargetRectangle(Image image, Rectangle sourceRect)
        {
            //Zoom value,default value is 1
            float zoom = 1;

            //Computer zoom
            float wn = sourceRect.Width * 1.0f / image.Width;
            float hn = sourceRect.Height * 1.0f / image.Height;
            float n = wn < hn ? wn : hn;
            zoom = n;
            //Set width and height
            int width = (int)Math.Round(n * image.Width);
            int height = (int)Math.Round(n * image.Height);

            //return target rectangle
            return new Rectangle(this.Width - width - 5, sourceRect.Top, width, height);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            if (Width != _playlistItem.Target.Length * Constance.TrackBar.UnitWidth)
            {
                //Width = _playlistItem.Target.Length * Constance.TrackBar.UnitWidth;
                Width = _playlistItem.Target.Length * _unitWidth;
                if (OnDurationChage != null)
                    OnDurationChage(this, new EventArgs());
                this.lblName.Text = _playlistItem.Target.Name;
            }
            if (this.lblName.Text != _playlistItem.Target.Name)
            {
                this.lblName.Text = _playlistItem.Target.Name;
                SetTitle(this.lblName.Text, _playlistItem.Target.Type.ToString(), _playlistItem.Target.LengthText);
            }
            _initRect = new Rectangle(this.Width - 40, 8, 35, 30);
            _durationTxt = _playlistItem.Target.LengthText;
            if (_durationTxt.Substring(0, 2) == "00")
                _durationTxt = _durationTxt.Substring(3, _durationTxt.Length - 3);
            SizeF d = e.Graphics.MeasureString(_durationTxt, this.Font);

            Image nailImg = _playlistItem.Target.Image;
            if (d.Width + 25 < _initRect.X && nailImg != null)
                e.Graphics.DrawImage(nailImg, GetTargetRectangle(nailImg, _initRect));

            if (d.Width + 25 < Width)
                e.Graphics.DrawString(_durationTxt, this.Font, brush, 25, 8);

        }

        void OnLibraryRename(object sender, LibraryRenameMessage msg)
        {
            this.lblName.Text = _playlistItem.Target.Name;
            SetTitle(this.lblName.Text, _playlistItem.Target.Type.ToString(), _playlistItem.Target.LengthText);
        }

        private void SetTitle(string name,string type, string LengthText)
        {
            strToolTip = "Name  :" + name + "\nType  :" + type + "\nLength:" + LengthText;
            toolTip1.SetToolTip(this, strToolTip);
            toolTip1.SetToolTip(this.lblName, strToolTip);
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
            LocalMessageBus.Subject<LibraryRenameMessage>().Observers -= new ObserverHandler<LibraryRenameMessage>(OnLibraryRename);
            //LocalMessageBus.Subject<LibraryImageChangeMessage>().Observers -= new ObserverHandler<LibraryImageChangeMessage>(OnLibraryImageChange);
        }
        #endregion
    }
}
