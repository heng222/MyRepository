using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using ProWrite.Entity.Shape;

namespace ProWrite.Entity.Live
{
    [Serializable]
    public class LiveMessageItemConfig
    {
        public class PlayPanel
        {
            public const int Left = 13;
            public const int Top = 23;
            public const int Width = 113;
            public const int Height = 100;
            public const int Right = 126;
            public const int Bottom = 123;
        }

        public class Counter
        {
            public RectangleF rectF = new RectangleF(PlayPanel.Right - 10, PlayPanel.Top - 10, 20, 20);
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
            
        }

        public class Title
        {
            RectangleF rectF = new RectangleF(10, PlayPanel.Bottom + 5, 122, 21);
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

        }


        public int Width = 142;
        public int height = 144;

        public RectangleF RectNail = new RectangleF(PlayPanel.Left - 10, PlayPanel.Top - 10, 20, 20);



    }
}
