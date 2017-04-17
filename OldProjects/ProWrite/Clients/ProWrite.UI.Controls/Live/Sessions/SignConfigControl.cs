//---------------------------------------------------------------------
//
// File: SignConfigControl.cs
//
// Description:
// SignConfigControl UserControl
//
// Author: Jerry
// Date  : 2009-7-16
//
// Modify history:
//      
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public partial class SignConfigControl : ControlBase
    {

        public class PlayPanelContainer
        {
            public const int Left = 13;
            public const int Top = 10;
            public const int Width = 113;
            public const int Height = 90;
            public const int Right = 126;
            public const int Bottom = 113;
            public static Color BackColor = Color.Gray;
        }

        public class SignTitle
        {
            public Rectangle Rect;
            public Color ForeColor = Color.White;
            public Color BackColor = Color.Black;
            //public Color BorderColor = Color.Blue;            
            public string FontName = "Arial";
            public float FontSize = 12;
            public FontStyle Style = FontStyle.Regular;
            public GraphicsUnit Unit = GraphicsUnit.Pixel;
            public StringAlignment Align = StringAlignment.Center;
            public StringAlignment Valign = StringAlignment.Near;
            public Font FontInfo;
            public string Text = "Sign";
            public Brush TitleBrush;
            public StringFormat Format;
            public SignTitle()
            {
                FontInfo = new Font(FontName, FontSize, Style, Unit);

                TitleBrush = new SolidBrush(ForeColor);
                Format = new StringFormat();
                Format.Alignment = Align;
                Format.LineAlignment = Valign;
            }

        }

        public Size Sign;
        public int ControlWidth = 142;
        public int ControlHeight = 144;
        public Color ControlBackColor = Color.Green;

        public SignConfigControl()
        {
            InitializeComponent();
            this.Width = ControlWidth;
            this.Height = ControlHeight;
            if (!DesignMode)
                Init();
        }

        private void Init()
        {
            this.Width = ControlWidth;
            this.Height = ControlHeight;
            this.BackColor = ControlBackColor;
            this.BorderStyle = BorderStyle.FixedSingle;
            Sign = new Size(96, 32);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            PaintAll(e.Graphics);
        }

        private void PaintAll(Graphics g)
        {
            PaintPlayPanelContainer(g);

            PaintPlayPanel(g);

            //PaintImageIndex(g);

            //PaintCounter(g);

            PaintSignName(g);
        }

        private void PaintPlayPanelContainer(Graphics g)
        {
            Rectangle rect = new Rectangle(PlayPanelContainer.Left, PlayPanelContainer.Top, PlayPanelContainer.Width, PlayPanelContainer.Height);
            Brush brush = new SolidBrush(PlayPanelContainer.BackColor);
            g.FillRectangle(brush, rect);
        }



        private void PaintPlayPanel(Graphics g)
        {
            Rectangle rect = GetPlayPanel();

            Brush brush = new SolidBrush(Color.Black);
            g.FillRectangle(brush, rect);

            PaintSignTitle(g, rect);

        }

        private void PaintSignTitle(Graphics g, Rectangle rect)
        {
            SignTitle title = new SignTitle();
            title.Rect = new Rectangle(rect.Width / 2 + rect.Left - 20, rect.Height / 2 + rect.Top - 10, 50, 50);
            g.DrawString(title.Text, title.FontInfo, title.TitleBrush, title.Rect, title.Format);
        }

        private void PaintSignName(Graphics g)
        {
            SignTitle title = new SignTitle();

            title.Rect = new Rectangle(10, PlayPanelContainer.Bottom + 5, this.Width - 20, this.Height - PlayPanelContainer.Bottom);

            g.DrawString(title.Text, title.FontInfo, title.TitleBrush, title.Rect, title.Format);
        }

        private Rectangle GetPlayPanel()
        {
            if (!Sign.IsEmpty)
            {
                decimal wRate = decimal.Divide(Sign.Width, PlayPanelContainer.Width);
                decimal hRate = decimal.Divide(Sign.Height, PlayPanelContainer.Height);
                decimal newWidth, newHeight, _zoom = 1;

                if (wRate > hRate)
                {
                    _zoom = decimal.Parse(PlayPanelContainer.Width.ToString()) / decimal.Parse(Sign.Width.ToString());
                    //_zoom = _zoom == 0 ? 1 : _zoom;
                    newWidth = Sign.Width * _zoom;
                    newHeight = Sign.Height * _zoom;
                }
                else
                {
                    _zoom = decimal.Parse(PlayPanelContainer.Height.ToString()) / decimal.Parse(Sign.Height.ToString());
                    //_zoom = _zoom == 0 ? 1 : _zoom;
                    newWidth = Sign.Width * _zoom;
                    newHeight = Sign.Height * _zoom;
                }

                int newLastWidth, newLastHeight;
                newLastWidth = decimal.ToInt32(newWidth);
                newLastHeight = decimal.ToInt32(newHeight);

                return new Rectangle((PlayPanelContainer.Width - newLastWidth) / 2 + PlayPanelContainer.Left, (PlayPanelContainer.Height - newLastHeight) / 2 + PlayPanelContainer.Top, newLastWidth, newLastHeight);
            }
            else
                return new Rectangle(PlayPanelContainer.Left, PlayPanelContainer.Top, PlayPanelContainer.Width, PlayPanelContainer.Height);
        }
    }
}
