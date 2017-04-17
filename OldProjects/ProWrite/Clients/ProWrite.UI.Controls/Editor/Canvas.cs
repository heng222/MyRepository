//---------------------------------------------------------------------
//
// File: SignContainer.cs
//
// Description:
// 2008-6-19, Kevin 迁移
//
// Author: 
// 
// Modify history:
//      Jerry Xu 2008-7-24 Add method:SetShapeRectangleF
//      Michael  2008-7-28 修改OnDoubleClick方法，获取视频中的图象
//      Jerry Xu 2008-8-3  Add methods:SetShapeText,SetShapeImage,SetShapeVideo
//      Jerry Xu 2008-8-3  Update method:DefautShapeSize
//      Jerry Xu 2008-8-4  Update method:AddShape(ShapeBase shape,bool isClone)->set zoom
//      Jerry Xu 2008-8-5  Update method:SetShapeText
//      Jerry Xu 2008-8-5  Add some coments
//      Jerry Xu 2008-8-5  Delete method:SetFontSize
//      Jerry Xu 2008-8-5  Update event:OnMouseDown(MouseEventArgs e)->(_StartPoint = new PointF(e.X, e.Y); //PointToOriginal(new Point(e.X, e.Y));)
//      Jerry Xu 2008-9-9  Update method:FitToSign
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Text;
using System.IO;
using System.Windows.Forms;
using DevExpress.XtraNavBar;
using DevExpress.XtraTreeList.Nodes;
using ProWrite.Entity.Library;
using ProWrite.Entity.Shape;
using ProWrite.Resources;
using ProWrite.UI.Controls.Editor;
using ProWrite.Core;
using System.Collections.Generic;
using PropertyChangedEventArgs = ProWrite.Entity.PropertyChangedEventArgs;
using ProWrite.UI.Controls.Common;
using ProWrite.UI.Controls.Common.Messages;

//using ProWrite.UI.Common;

namespace ProWrite.UI.Controls.Editor
{
    /// <summary>
    /// Summary description for Container.
    /// </summary>
    public partial class Canvas : Control
    {
        #region Private variant define
        private const int WM_KILLFOCUS = 0x0008;
        private const int WM_MOUSELEAVE = 0x02a3;
        private const int WM_SETFOCUS = 0x0007;
		private const int WM_LBUTTONUP = 0x0202;

        private ShapeBase _ActiveShape = null;
        private HScrollBar _HScrollBar;
        private VScrollBar _VScrollBar;

        // Drawing settings
        private const int _FocusBorderWidth = 3;

        // State variable
        private bool _IsDrawDragOver = false;
        private bool _ResizeBlockDrag = false;
        private Rectangle _SelectedBounds = Rectangle.Empty;
        private Document _document;
        private Rectangle _WorkingBounds;
        #endregion

        public Canvas()
        {
            if (!DesignMode)
            {
                Init();
                InitShapePaints();
            }
        }

        #region Propertis define
        // properties
        public static int FocusBorderWidth
        {
            get { return _FocusBorderWidth; }
        }

        public Document Document
        {
            get { return _document; }
        }

        //public int Zoom { get; set; }
        #endregion

        #region Function define

        private void Init()
        {
            this.AllowDrop = true;
            _document = new Document();

            this.SetStyle(ControlStyles.DoubleBuffer, true);
            this.SetStyle(ControlStyles.UserPaint, true);
            this.SetStyle(ControlStyles.AllPaintingInWmPaint, true);

            // load scroll bars
            _HScrollBar = new HScrollBar();
            _VScrollBar = new VScrollBar();
        }

        private void ScrollBarsLayout()
        {
            _HScrollBar.Hide();
            _VScrollBar.Hide();

            int scrollHeight = this.Height - 2 * _FocusBorderWidth - _HScrollBar.Height;
            int scrollWidth = this.Width - 2 * _FocusBorderWidth - _VScrollBar.Width;

            _HScrollBar.Width = scrollWidth;
            _VScrollBar.Height = scrollHeight;
            _HScrollBar.Location = new Point(_FocusBorderWidth, scrollHeight + _FocusBorderWidth);
            _VScrollBar.Location = new Point(scrollWidth + _FocusBorderWidth, _FocusBorderWidth);

            _HScrollBar.Show();
            _VScrollBar.Show();
        }
        #endregion

        #region Event define

        protected override void OnPaint(PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            
            g.TextRenderingHint = TextRenderingHint.AntiAlias;
            g.SmoothingMode = SmoothingMode.HighQuality;

            _document.Paint(g, Bounds.Size);

            if (drawNetRectangle)
                DrawNetSelection(g);

            if (MessageControl.Current.Sign.Template.Message.IsShowGrid)
            {
                int width = Width;
                int height = Height;
                int zoom = _document.Zoom;
                if (zoom == 1)
                {
                    width = width * 2;
                    height = height * 2;
                    zoom = 2;
                }
                Color linecolor = Color.FromArgb(255, 130, 130, 130);

                var pen = ResourceCache.DefaultCache.GetPen(linecolor);
                for (int x = 0; x <= Width; x = x + zoom)
                    g.DrawLine(pen, new Point(x, 0), new Point(x, height));
                for (int y = 0; y <= height; y = y + zoom)
                    g.DrawLine(pen, new Point(0, y), new Point(width, y));
                g.DrawRectangle(pen, 0, 0, width, height);
            }
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            ScrollBarsLayout();

            _WorkingBounds = (Rectangle)this.DisplayRectangle;
            _WorkingBounds.Offset(_FocusBorderWidth, _FocusBorderWidth);
            _WorkingBounds.Width = _HScrollBar.Width - 1;
            _WorkingBounds.Height = _VScrollBar.Height - 1;
            //AdjustShapesSize();
            this.Invalidate();
        }

        #endregion

        #region control drag & drop

        private const string errorUnableToLocateFileString = "ErrorUnableToLocateFile";

        protected override void OnDragOver(DragEventArgs drgevent)
        {
            if (!_IsDrawDragOver)
            {
                ShapeControlPaintNew.DrawReversibleBorder(this);
                _IsDrawDragOver = true;
            }
            base.OnDragOver(drgevent);
        }

        protected override void OnDragLeave(EventArgs e)
        {
            ReverseReverseBorder();
            base.OnDragLeave(e);
        }

        
        public void ReverseReverseBorder()
        {
            ShapeControlPaintNew.DrawReversibleBorder(this);
            _IsDrawDragOver = false;
        }

        #endregion

        #region mouse click event handle

        protected override void OnClick(EventArgs e)
        {
            if (this.CanFocus)
            {
                this.Focus();

                ShapeBase shape = _document.SelectedShape;
                ControlMenuItemEnable(shape);
            }

            base.OnClick(e);
            this.Invalidate();
        }

        public Keys ShortcutKey
        {
            get
            {
                return ModifierKeys;
            }
        }

        public static void ControlMenuItemEnable(ShapeBase shape)
        {
            if (shape != null)
            {
                if (shape.Type == ShapeType.Ellipse
                    || shape.Type == ShapeType.DownArrow
                    || shape.Type == ShapeType.LeftArrow
                    || shape.Type == ShapeType.Line
                    || shape.Type == ShapeType.Rectangle
                    || shape.Type == ShapeType.RightArrow
                    || shape.Type == ShapeType.UpArrow
                    || shape.Type == ShapeType.ShapeDraw)
                {
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.LineColor, Enabled = true, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.LineThickness, Enabled = true, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.LineDash, Enabled = true, Visibility = ItemVisibility.Always } }));

                    if (shape.Type != ShapeType.Line)
                        LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.ColorFill, Enabled = true, Visibility = ItemVisibility.Always } }));

                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextFontSize, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextFontSizeFixed, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextFrameFixed, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextAlignRight, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextAlignLeft, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextAlignCenter, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextEffect, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextFont, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextItalic, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextBold, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextFontColor, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextBackgroundColor, Enabled = false, Visibility = ItemVisibility.Always } }));
                }
                else if (shape.Type == ShapeType.Image)
                {
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextFontSize, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextFontSizeFixed, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextFrameFixed, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextAlignRight, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextAlignLeft, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextAlignCenter, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextEffect, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextFont, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextItalic, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextBold, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextFontColor, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextBackgroundColor, Enabled = false, Visibility = ItemVisibility.Always } }));
                }
                else if (shape.Type == ShapeType.Temperature
                         || shape.Type == ShapeType.Time)
                {
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.LineColor, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.LineThickness, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.LineDash, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.ColorFill, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextKern, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextLead, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextEffect, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextItalic, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.TextBold, Enabled = false, Visibility = ItemVisibility.Always } }));
                }
                else
                {
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.LineColor, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.ColorFill, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.LineThickness, Enabled = false, Visibility = ItemVisibility.Always } }));
                    LocalMessageBus.Send(null, new MenuMessage(new MenuCommand[] { new MenuCommand { Command = MenuCommands.LineDash, Enabled = false, Visibility = ItemVisibility.Always } }));
                }
            }
        }

        /// <summary>
        /// Function: Text fit to sign
        /// Author  : Jerry Xu
        /// Date    : 2008-8-12
        /// </summary>
        public void FitToSign()
        {
            ShapeBase shape = _document.SelectedShape;
            if(shape == null)
                return;
            if(shape.Type == ShapeType.Text 
                || shape.Type == ShapeType.Image
                || shape.Type == ShapeType.Video 
                || shape.Type == ShapeType.DynamicText 
                || shape.Type == ShapeType.DynamicVideo
                || shape.Type == ShapeType.Temperature
                || shape.Type == ShapeType.Time)
            {
                shape.VirtualBounds = new Rectangle(new Point(0, 0), new Size(shape.SignSize.Width * shape.Zoom, shape.SignSize.Height * shape.Zoom));
                this.Invalidate();
            }
            
        }

        /// <summary>
        /// Function: Set VirtualBounds by Zoom
        /// Author  : Michael
        /// Date    : 2008-10-28
        /// </summary>
        private void SetVirtualBounds()
        {
			//float x, y, width, height;
            int x, y, width, height;

            if (this.Capture && _ActiveShape != null && !_ResizeBlockDrag)
            { 
                if (_document.SelectedShape.VirtualBounds.X % MessageControl.Current.Zoom > MessageControl.Current.Zoom / 2)
                {
                    x = _document.SelectedShape.VirtualBounds.X % MessageControl.Current.Zoom == 0 
						? _document.SelectedShape.VirtualBounds.X 
						: _document.SelectedShape.VirtualBounds.X + (MessageControl.Current.Zoom - _document.SelectedShape.VirtualBounds.X % MessageControl.Current.Zoom);
                }
                else
                {
                    x = _document.SelectedShape.VirtualBounds.X % MessageControl.Current.Zoom == 0
                        ? _document.SelectedShape.VirtualBounds.X
                        : _document.SelectedShape.VirtualBounds.X - Math.Abs(_document.SelectedShape.VirtualBounds.X % MessageControl.Current.Zoom);
                }

                if (_document.SelectedShape.VirtualBounds.Y % MessageControl.Current.Zoom > MessageControl.Current.Zoom / 2)
                {
                    y = _document.SelectedShape.VirtualBounds.Y % MessageControl.Current.Zoom == 0 
						? _document.SelectedShape.VirtualBounds.Y 
						: _document.SelectedShape.VirtualBounds.Y + (MessageControl.Current.Zoom - _document.SelectedShape.VirtualBounds.Y % MessageControl.Current.Zoom);
                }
                else
                {
                    y = _document.SelectedShape.VirtualBounds.Y % MessageControl.Current.Zoom == 0 
						? _document.SelectedShape.VirtualBounds.Y 
						: _document.SelectedShape.VirtualBounds.Y - Math.Abs(_document.SelectedShape.VirtualBounds.Y % MessageControl.Current.Zoom);
                }
                _document.SelectedShape.VirtualBounds = new Rectangle(x, y, _document.SelectedShape.VirtualBounds.Width, _document.SelectedShape.VirtualBounds.Height);
            }

            if (_ResizeBlockDrag)
            {
                if (_document.SelectedShape.VirtualBounds.Width % MessageControl.Current.Zoom > MessageControl.Current.Zoom / 2)
                {
                    width = _document.SelectedShape.VirtualBounds.Width % MessageControl.Current.Zoom == 0 ? _document.SelectedShape.VirtualBounds.Width : _document.SelectedShape.VirtualBounds.Width + (MessageControl.Current.Zoom - _document.SelectedShape.VirtualBounds.Width % MessageControl.Current.Zoom);
                }
                else
                {
                    width = _document.SelectedShape.VirtualBounds.Width % MessageControl.Current.Zoom == 0 ? _document.SelectedShape.VirtualBounds.Width : _document.SelectedShape.VirtualBounds.Width - _document.SelectedShape.VirtualBounds.Width % MessageControl.Current.Zoom;
                }

                if (_document.SelectedShape.VirtualBounds.Height % MessageControl.Current.Zoom > MessageControl.Current.Zoom / 2)
                {
                    height = _document.SelectedShape.VirtualBounds.Height % MessageControl.Current.Zoom == 0 ? _document.SelectedShape.VirtualBounds.Height : _document.SelectedShape.VirtualBounds.Height + (MessageControl.Current.Zoom - _document.SelectedShape.VirtualBounds.Height % MessageControl.Current.Zoom);
                }
                else
                {
                    height = _document.SelectedShape.VirtualBounds.Height % MessageControl.Current.Zoom == 0 ? _document.SelectedShape.VirtualBounds.Height : _document.SelectedShape.VirtualBounds.Height - _document.SelectedShape.VirtualBounds.Height % MessageControl.Current.Zoom;
                }
                _document.SelectedShape.VirtualBounds = new Rectangle(_document.SelectedShape.VirtualBounds.X, _document.SelectedShape.VirtualBounds.Y, width, height);
            }
        }
        #endregion
     }
}
