//---------------------------------------------------------------------
//
// File: MessageNailControl.cs
//
// Description:
// MessageNailControl UserControl 
//
// Author: Jerry
// Date  : 2009-7-14
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
    public partial class MessageNailControl : UserControl
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

        public class SignName
        {
            RectangleF Rect = new RectangleF(10, PlayPanelContainer.Bottom + 5, 122, 21);
            public Color ForeColor = Color.Black;
            public Color BackColor = Color.White;
            public Color BorderColor = Color.Blue;
            public int Count;
            public string FontName = "Arial";
            public float FontSize = 12;
            public FontStyle Style = FontStyle.Regular;
            public GraphicsUnit Unit = GraphicsUnit.Pixel;
            public StringAlignment Align = StringAlignment.Center;
            public StringAlignment Valign = StringAlignment.Near;
            public StringFormat Format;

        }

        public Size Sign;
        private int _Width = 142;
        private int _Height = 144;
        public Color ControlBackColor = Color.White;
        public Image NailImage;

        public MessageNailControl()
        {
            InitializeComponent();
            if (!DesignMode)
                Init();
        }

        private void Init()
        {
            this.Width = _Width;
            this.Height = _Height;
            this.BackColor = ControlBackColor;
            this.BorderStyle = BorderStyle.FixedSingle;
            Sign = new Size(96, 32);
            //string nailfile = @"C:\\Users\Public\\Pictures\\Sample Pictures\\Chrysanthemum.jpg";
            //NailImage = Image.FromFile(nailfile);
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

            PaintImageIndex(g);

            PaintCounter(g);

            PaintSignName(g);
        }

        public class Counter
        {
            public Rectangle Rect = new Rectangle(PlayPanelContainer.Right - 10, PlayPanelContainer.Top - 10, 20, 20);
            public Color ForeColor = Color.Black;
            public Color BackColor = Color.White;
            public Color BorderColor = Color.Blue;
            public int Count;
            public string FontName = "Arial";
            public float FontSize = 12;
            public Font FontInfo;
            public FontStyle Style = FontStyle.Regular;
            public GraphicsUnit Unit = GraphicsUnit.Pixel;
            public StringAlignment Align = StringAlignment.Center;
            public StringAlignment Valign = StringAlignment.Near;
            public string Text = "2";
            public Brush BackBrush;
            public Brush TextBrush;
            public StringFormat Format;
            public Pen BorderPen;
            public Counter()
            {
                FontInfo = new Font(FontName, FontSize, Style, Unit);

                BackBrush = new SolidBrush(BackColor);
                TextBrush = new SolidBrush(ForeColor);
                Format = new StringFormat();
                Format.Alignment = Align;
                Format.LineAlignment = Valign;
                BorderPen = new Pen(BorderColor);
            }
        }

        private void PaintCounter(Graphics g)
        {
            Counter counter = new Counter();

            Brush brush = new SolidBrush(ForeColor);

            g.FillRectangle(counter.BackBrush, counter.Rect);

            g.DrawRectangle(counter.BorderPen, counter.Rect);

            g.DrawString(counter.Text, counter.FontInfo, counter.TextBrush, counter.Rect, counter.Format);
        }

        private static void PaintImageIndex(Graphics g)
        {
            //string filename = @"C:\\Users\Public\\Pictures\\Sample Pictures\\Chrysanthemum.jpg";


            //Image img = Image.FromFile(filename);


            ////g = Graphics.FromImage(img);
            //g.DrawImage(img, PlayPanelContainer.Left - 10, PlayPanelContainer.Top - 10, 20, 20);
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

            PaintImage(g, rect);
            //PaintSignTitle(g, rect);

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

            title.ForeColor = Color.Black;
            title.BackColor = Color.White;
            title.TitleBrush = new SolidBrush(title.ForeColor);
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

        private void PaintImage(Graphics g, Rectangle rect)
        {
            if (NailImage != null)
            {
                g.DrawImage(NailImage, rect);
            }
        }
    }
}
