using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.Utils;
using DevExpress.Utils.Drawing;
using DevExpress.XtraBars;
using DevExpress.XtraEditors;
using DevExpress.XtraEditors.Drawing;
using DevExpress.XtraEditors.Popup;
using DevExpress.XtraEditors.Repository;
using DevExpress.XtraEditors.ViewInfo;
using ProWrite.Core;
using ProWrite.Entity.Dashboard;
using ProWrite.UI.Controls.Editor;

namespace ProWrite.UI.Controls
{
    public class PWColorCellsControl : BaseControl
    {
        PWColorCellsControlViewInfo viewInfo;
        PWColorCellsControlPainter painter;
        RepositoryItemColorEdit properties;
        bool lockFocus;
        PopupBaseForm shadowForm;
        public PopupControlContainer PopupContainer { get; set; }

        public event EnterColorEventHandler EnterColor;
        public PWColorCellsControl(PopupBaseForm shadowForm)
            : this(shadowForm, 8, 8)
        {
        }
        public PWColorCellsControl(PopupBaseForm shadowForm, int columnCount, int rowCount)
        {
            if (columnCount * rowCount > 64)
                throw new Exception("Incorrect cells count.");
            SetStyle(ControlStyles.UserMouse, false);
            this.shadowForm = shadowForm;
            viewInfo = new PWColorCellsControlViewInfo(this, columnCount, rowCount);
            painter = new PWColorCellsControlPainter(columnCount * rowCount);
            properties = null;
            lockFocus = false;
            SetStyle(ControlStyles.AllPaintingInWmPaint | ControlConstants.DoubleBuffer, true);
        }
        public Size GetBestSize()
        {
            return viewInfo.GetBestSize();
        }
        protected override void OnKeyDown(KeyEventArgs e)
        {
            base.OnKeyDown(e);
            if (e.Handled) return;
            e.Handled = true;
            int horzStep = 0, vertStep = 0;
            switch (e.KeyCode)
            {
                case Keys.Left: horzStep = -1; break;
                case Keys.Right: horzStep = 1; break;
                case Keys.Up: vertStep = -1; break;
                case Keys.Down: vertStep = 1; break;
                case Keys.Return:
                case Keys.Space: OnEnterColor(SelectedCellIndex); return;
                default: e.Handled = false; break;
            }
            if (horzStep != 0 || vertStep != 0) MoveSelectedCell(horzStep, vertStep);
        }
        protected override void OnMouseDown(MouseEventArgs e)
        {
            base.OnMouseDown(e);
            if ((e.Button & MouseButtons.Left) != 0)
            {
                int cellIndex = viewInfo.GetCellIndex(new Point(e.X, e.Y));
                if (cellIndex != -1)
                {
                    Capture = true;
                    SelectedCellIndex = cellIndex;
                }
            }
        }
        protected override void OnMouseMove(MouseEventArgs e)
        {
            base.OnMouseMove(e);
            if ((e.Button & MouseButtons.Left) != 0 && Capture)
            {
                int cellIndex = viewInfo.GetCellIndex(new Point(e.X, e.Y));
                if (cellIndex != -1) SelectedCellIndex = cellIndex;
            }
        }
        protected override void OnMouseUp(MouseEventArgs e)
        {
            if (PopupContainer != null) PopupContainer.CloseOnOuterMouseClick = false;
            base.OnMouseUp(e);
            int cellIndex = viewInfo.GetCellIndex(new Point(e.X, e.Y));
            if ((e.Button & MouseButtons.Left) != 0 && Capture)
            {
                if (cellIndex != -1)
                {
                    SelectedCellIndex = cellIndex;
                    Capture = false;
                    OnEnterColor(SelectedCellIndex);
                }
            }
            //if ((e.Button & MouseButtons.Right) != 0 && cellIndex >= 64 && Properties.ShowColorDialog)
            if ((e.Button & MouseButtons.Right) != 0 && cellIndex >= ColorCellsControlViewInfo.CellColors.Length && Properties.ShowColorDialog)
            {
                ColorDialog cd = null;
                MonoColorDialog mcd = null;
                switch(viewInfo.SignType)
                {
                    case SignType.Amber:
                        mcd = new MonoColorDialog(Color.FromArgb(255, 191, 63));
                        break;
                    case SignType.Red:
                        mcd = new MonoColorDialog(Color.Red);
                        break;
                    case SignType.Green:
                        mcd = new MonoColorDialog(Color.Green);
                        break;
                    case SignType.Blue:
                        mcd = new MonoColorDialog(Color.Blue);
                        break;
                    case SignType.White:
                        mcd = new MonoColorDialog();
                        break;
                    default:
                        cd = new ColorDialog();
                        cd.FullOpen = true;
                        cd.Color = viewInfo.GetCellColor(cellIndex);
                        break;
                }
                lockFocus = true;
                if (shadowForm != null)
                    this.shadowForm.HideShadows();
                try
                {
                    if (cd != null && cd.ShowDialog() == DialogResult.OK)
                    {
                        viewInfo.CustomColors[cellIndex - ColorCellsControlViewInfo.CellColors.Length] = cd.Color;
                        OnEnterColor(cellIndex);
                    }
                    if(mcd != null && mcd.ShowDialog() == DialogResult.OK)
                    {
                        viewInfo.CustomColors[cellIndex - ColorCellsControlViewInfo.CellColors.Length] = mcd.Color;
                        OnEnterColor(cellIndex);
                    }
                }
                finally
                {
                    lockFocus = false;
                    if (shadowForm != null)
                        this.shadowForm.ShowHideShadows();
                }
            }
            if (PopupContainer != null) PopupContainer.CloseOnOuterMouseClick = true;
        }
        private void MoveSelectedCell(int horzStep, int vertStep)
        {
            int vertIndex = SelectedCellIndex / 8;
            int horzIndex = SelectedCellIndex - vertIndex * 8;
            if (horzIndex + horzStep < 0) horzStep = 7;
            if (horzIndex + horzStep > 7) horzStep = -7;
            if (vertIndex + vertStep < 0) vertStep = 7;
            if (vertIndex + vertStep > 7) vertStep = -7;
            SelectedCellIndex = 8 * (vertIndex + vertStep) + (horzIndex + horzStep);
        }
        private void OnEnterColor(int index)
        {
            Color clr = viewInfo.GetCellColor(index);
            if (clr == Color.Empty) return;
            if (EnterColor != null) EnterColor(this, new EnterColorEventArgs(clr));
        }
        public virtual void ProcessKeyDown(KeyEventArgs e) { OnKeyDown(e); }
        protected override BaseControlPainter Painter { get { return painter; } }
        protected override BaseControlViewInfo ViewInfo { get { return viewInfo; } }
        public BaseControlViewInfo _ViewInfo { get { return viewInfo; } }
        [Category(CategoryName.Properties)]
        public RepositoryItemColorEdit Properties { get { return properties; } set { properties = value; } }
        [Browsable(false)]
        public bool LockFocus { get { return lockFocus; } }
        [Category(CategoryName.Appearance)]
        public virtual int SelectedCellIndex
        {
            get { return viewInfo.SelectedCellIndex; }
            set
            {
                if (value < 0) value = 0;
                if (value > 63) value = 63;
                if (SelectedCellIndex != value)
                {
                    viewInfo.SelectedCellIndex = value;
                    LayoutChanged();
                }
            }
        }
    }

    public class PWColorCellsControlViewInfo : BaseControlViewInfo
    {
        public const int CellsInternval = 3;
        public Color[] fCustomColors;
        int selectedCellIndex;
        int columnCount;
        int rowCount;

        private SignType? signType = null;
        internal SignType? SignType
        {
            get
            {
                return signType;
            }

            set
            {
                signType = value;
            }
        }
       

        #region cellColorsRGB
        static Color[] cellColorsRGB = new Color[] {
                                                       Color.FromArgb(255, 255, 255),
                                                       Color.FromArgb(255, 192, 192),
                                                       Color.FromArgb(255, 224, 192),
                                                       Color.FromArgb(255, 255, 192),
                                                       Color.FromArgb(192, 255, 192),
                                                       Color.FromArgb(192, 255, 255),
                                                       Color.FromArgb(192, 192, 255),
                                                       Color.FromArgb(255, 192, 255),
                                                       Color.FromArgb(224, 224, 224),
                                                       Color.FromArgb(255, 128, 128),
                                                       Color.FromArgb(255, 192, 128),
                                                       Color.FromArgb(255, 255, 128),
                                                       Color.FromArgb(128, 255, 128),
                                                       Color.FromArgb(128, 255, 255),
                                                       Color.FromArgb(128, 128, 255),
                                                       Color.FromArgb(255, 128, 255),
                                                       Color.FromArgb(192, 192, 192),
                                                       Color.FromArgb(255, 0, 0),
                                                       Color.FromArgb(255, 128, 0),
                                                       Color.FromArgb(255, 255, 0),
                                                       Color.FromArgb(0, 255, 0),
                                                       Color.FromArgb(0, 255, 255),
                                                       Color.FromArgb(0, 0, 255),
                                                       Color.FromArgb(255, 0, 255),
                                                       Color.FromArgb(128, 128, 128),
                                                       Color.FromArgb(192, 0, 0),
                                                       Color.FromArgb(192, 64, 0),
                                                       Color.FromArgb(192, 192, 0),
                                                       Color.FromArgb(0, 192, 0),
                                                       Color.FromArgb(0, 192, 192),
                                                       Color.FromArgb(0, 0, 192),
                                                       Color.FromArgb(192, 0, 192),
                                                       Color.FromArgb(64, 64, 64),
                                                       Color.FromArgb(128, 0, 0),
                                                       Color.FromArgb(128, 64, 0),
                                                       Color.FromArgb(128, 128, 0),
                                                       Color.FromArgb(0, 128, 0),
                                                       Color.FromArgb(0, 128, 128),
                                                       Color.FromArgb(0, 0, 128),
                                                       Color.FromArgb(128, 0, 128),
                                                       Color.FromArgb(0, 0, 0),
                                                       Color.FromArgb(64, 0, 0),
                                                       Color.FromArgb(128, 64, 64),
                                                       Color.FromArgb(64, 64, 0),
                                                       Color.FromArgb(0, 64, 0),
                                                       Color.FromArgb(0, 64, 64),
                                                       Color.FromArgb(0, 0, 64),
                                                       Color.FromArgb(64, 0, 64)};
        #endregion cellColorsRGB

        #region cellColorsRed
        static Color[] cellColorsRed = new Color[] {
                                                       Color.FromArgb(255, 0, 0),
                                                       Color.FromArgb(250, 0, 0),
                                                       Color.FromArgb(245, 0, 0),
                                                       Color.FromArgb(240, 0, 0),
                                                       Color.FromArgb(235, 0, 0),

                                                       Color.FromArgb(229, 0, 0),
                                                       Color.FromArgb(224, 0, 0),
                                                       Color.FromArgb(216, 0, 0),
                                                       Color.FromArgb(211, 0, 0),

                                                       Color.FromArgb(205, 0, 0),
                                                       Color.FromArgb(200, 0, 0),
                                                       Color.FromArgb(195, 0, 0),
                                                       Color.FromArgb(190, 0, 0),
                                                       Color.FromArgb(185, 0, 0),

                                                       Color.FromArgb(179, 0, 0),
                                                       Color.FromArgb(174, 0, 0),
                                                       Color.FromArgb(169, 0, 0),
                                                       Color.FromArgb(164, 0, 0),

                                                       Color.FromArgb(158, 0, 0),
                                                       Color.FromArgb(153, 0, 0),
                                                       Color.FromArgb(148, 0, 0),
                                                       Color.FromArgb(143, 0, 0),
                                                       Color.FromArgb(138, 0, 0),

                                                       Color.FromArgb(132, 0, 0),
                                                       Color.FromArgb(127, 0, 0),
                                                       Color.FromArgb(122, 0, 0),
                                                       Color.FromArgb(117, 0, 0),

                                                       Color.FromArgb(111, 0, 0),
                                                       Color.FromArgb(106, 0, 0),
                                                       Color.FromArgb(101, 0, 0),
                                                       Color.FromArgb(96, 0, 0),
                                                       Color.FromArgb(91, 0, 0),

                                                       Color.FromArgb(85, 0, 0),
                                                       Color.FromArgb(80, 0, 0),
                                                       Color.FromArgb(75, 0, 0),
                                                       Color.FromArgb(70, 0, 0),

                                                       Color.FromArgb(64, 0, 0),
                                                       Color.FromArgb(59, 0, 0),
                                                       Color.FromArgb(54, 0, 0),
                                                       Color.FromArgb(49, 0, 0),
                                                       Color.FromArgb(44, 0, 0),

                                                       Color.FromArgb(38, 0, 0),
                                                       Color.FromArgb(32, 0, 0),
                                                       Color.FromArgb(26, 0, 0),
                                                       Color.FromArgb(20, 0, 0),

                                                       Color.FromArgb(14, 0, 0),
                                                       Color.FromArgb(7, 0, 0),
                                                       Color.FromArgb(0, 0, 0),

                                                   };
        #endregion cellColorsRed

        #region cellColorsGreen
        static Color[] cellColorsGreen = new Color[] {
                                                         Color.FromArgb(0, 255, 0),
                                                         Color.FromArgb(0,250,  0),
                                                         Color.FromArgb( 0,245, 0),
                                                         Color.FromArgb( 0,240, 0),
                                                         Color.FromArgb( 0,235, 0),

                                                         Color.FromArgb( 0,229, 0),
                                                         Color.FromArgb( 0,224, 0),
                                                         Color.FromArgb( 0,216, 0),
                                                         Color.FromArgb( 0,211, 0),

                                                         Color.FromArgb( 0,205, 0),
                                                         Color.FromArgb( 0,200, 0),
                                                         Color.FromArgb( 0,195, 0),
                                                         Color.FromArgb( 0,190, 0),
                                                         Color.FromArgb( 0,185, 0),

                                                         Color.FromArgb( 0,179, 0),
                                                         Color.FromArgb( 0,174, 0),
                                                         Color.FromArgb( 0,169, 0),
                                                         Color.FromArgb( 0,164, 0),

                                                         Color.FromArgb( 0,158, 0),
                                                         Color.FromArgb( 0,153, 0),
                                                         Color.FromArgb( 0,148, 0),
                                                         Color.FromArgb( 0,143, 0),
                                                         Color.FromArgb( 0,138, 0),

                                                         Color.FromArgb( 0,132, 0),
                                                         Color.FromArgb( 0,127, 0),
                                                         Color.FromArgb( 0,122, 0),
                                                         Color.FromArgb( 0,117, 0),

                                                         Color.FromArgb( 0,111, 0),
                                                         Color.FromArgb( 0,106, 0),
                                                         Color.FromArgb( 0,101, 0),
                                                         Color.FromArgb(0, 96, 0),
                                                         Color.FromArgb(0, 91, 0),

                                                         Color.FromArgb( 0,85, 0),
                                                         Color.FromArgb( 0,80, 0),
                                                         Color.FromArgb( 0,75, 0),
                                                         Color.FromArgb( 0,70, 0),

                                                         Color.FromArgb( 0,64, 0),
                                                         Color.FromArgb( 0,59, 0),
                                                         Color.FromArgb( 0,54, 0),
                                                         Color.FromArgb( 0,49, 0),
                                                         Color.FromArgb( 0,44, 0),

                                                         Color.FromArgb( 0,38, 0),
                                                         Color.FromArgb( 0,32, 0),
                                                         Color.FromArgb( 0,26, 0),
                                                         Color.FromArgb( 0,20, 0),

                                                         Color.FromArgb( 0,14, 0),
                                                         Color.FromArgb(0, 7, 0),
                                                         Color.FromArgb(0, 0, 0),

                                                     };
        #endregion cellColorsGreen

        #region cellColorsBlue
        static Color[] cellColorsBlue = new Color[] {
                                                        Color.FromArgb(0,  0,255),
                                                        Color.FromArgb(0,  0,250),
                                                        Color.FromArgb( 0, 0,245),
                                                        Color.FromArgb( 0, 0,240),
                                                        Color.FromArgb( 0, 0,235),

                                                        Color.FromArgb( 0, 0,229),
                                                        Color.FromArgb( 0, 0,224),
                                                        Color.FromArgb( 0, 0,216),
                                                        Color.FromArgb( 0, 0,211),

                                                        Color.FromArgb( 0, 0,205),
                                                        Color.FromArgb( 0, 0,200),
                                                        Color.FromArgb( 0, 0,195),
                                                        Color.FromArgb( 0, 0,190),
                                                        Color.FromArgb( 0, 0,185),

                                                        Color.FromArgb( 0, 0,179),
                                                        Color.FromArgb( 0, 0,174),
                                                        Color.FromArgb( 0, 0,169),
                                                        Color.FromArgb( 0, 0,164),

                                                        Color.FromArgb( 0, 0,158),
                                                        Color.FromArgb( 0, 0,153),
                                                        Color.FromArgb( 0, 0,148),
                                                        Color.FromArgb( 0, 0,143),
                                                        Color.FromArgb( 0, 0,138),

                                                        Color.FromArgb( 0, 0,132),
                                                        Color.FromArgb( 0, 0,127),
                                                        Color.FromArgb( 0, 0,122),
                                                        Color.FromArgb( 0, 0,117),

                                                        Color.FromArgb( 0, 0,111),
                                                        Color.FromArgb( 0, 0,106),
                                                        Color.FromArgb( 0, 0,101),
                                                        Color.FromArgb(0, 0,96),
                                                        Color.FromArgb(0, 0,91) ,

                                                        Color.FromArgb( 0, 0,85),
                                                        Color.FromArgb( 0, 0,80),
                                                        Color.FromArgb( 0, 0,75),
                                                        Color.FromArgb( 0, 0,70),

                                                        Color.FromArgb( 0, 0,64),
                                                        Color.FromArgb( 0, 0,59),
                                                        Color.FromArgb( 0, 0,54),
                                                        Color.FromArgb( 0, 0,49),
                                                        Color.FromArgb( 0, 0,44),

                                                        Color.FromArgb( 0, 0,38),
                                                        Color.FromArgb( 0, 0,32),
                                                        Color.FromArgb( 0, 0,26),
                                                        Color.FromArgb( 0, 0,20),

                                                        Color.FromArgb( 0, 0,14),
                                                        Color.FromArgb(0, 0,7) ,
                                                        Color.FromArgb(0, 0,0) 
                                                                                             
                                                    };
        #endregion cellColorsBlue

        #region cellColorsWhite
        static Color[] cellColorsWhite = new Color[] {
                                                         Color.FromArgb(255, 255,255),
                                                         Color.FromArgb(250, 250,250),
                                                         Color.FromArgb(245, 245,245),
                                                         Color.FromArgb(240, 240,240),
                                                         Color.FromArgb(235, 235,235),

                                                         Color.FromArgb( 229, 229,229),
                                                         Color.FromArgb( 224, 224,224),
                                                         Color.FromArgb( 216, 216,216),
                                                         Color.FromArgb( 211, 211,211),

                                                         Color.FromArgb( 205, 205,205),
                                                         Color.FromArgb( 200, 200,200),
                                                         Color.FromArgb( 195, 195,195),
                                                         Color.FromArgb( 190, 190,190),
                                                         Color.FromArgb( 185, 185,185),

                                                         Color.FromArgb( 179, 179,179),
                                                         Color.FromArgb( 174, 174,174),
                                                         Color.FromArgb( 169, 169,169),
                                                         Color.FromArgb( 164, 164,164),

                                                         Color.FromArgb( 158, 158,158),
                                                         Color.FromArgb( 153, 153,153),
                                                         Color.FromArgb( 148, 148,148),
                                                         Color.FromArgb( 143, 143,143),
                                                         Color.FromArgb( 138, 138,138),

                                                         Color.FromArgb( 132, 132,132),
                                                         Color.FromArgb( 127, 127,127),
                                                         Color.FromArgb( 122, 122,122),
                                                         Color.FromArgb( 117, 117,117),

                                                         Color.FromArgb( 111, 111,111),
                                                         Color.FromArgb( 106, 106,106),
                                                         Color.FromArgb( 101, 101,101),
                                                         Color.FromArgb( 96 , 96 ,96 ),
                                                         Color.FromArgb( 91 , 91 ,91 ) ,

                                                         Color.FromArgb( 85, 85,85),
                                                         Color.FromArgb( 80, 80,80),
                                                         Color.FromArgb( 75, 75,75),
                                                         Color.FromArgb( 70, 70,70),

                                                         Color.FromArgb( 64, 64,64),
                                                         Color.FromArgb( 59, 59,59),
                                                         Color.FromArgb( 54, 54,54),
                                                         Color.FromArgb( 49, 49,49),
                                                         Color.FromArgb( 44, 44,44),

                                                         Color.FromArgb( 38, 38,38),
                                                         Color.FromArgb( 32, 32,32),
                                                         Color.FromArgb( 26, 26,26),
                                                         Color.FromArgb( 20, 20,20),

                                                         Color.FromArgb( 14, 14,14),
                                                         Color.FromArgb( 7 , 7 ,7 ) ,
                                                         Color.FromArgb( 0 , 0 ,0 ) 
                                                                                             
                                                     };
        #endregion cellColorsWhite

        #region cellColorsAmber
        static Color[] cellColorsAmber = new Color[] {
                                                         Color.FromArgb(255,188,62),
                                                         Color.FromArgb(250,184,61),
                                                         Color.FromArgb(245,180,60),
                                                         Color.FromArgb(240,176,59),
                                                         Color.FromArgb(235,172,58),

                                                         Color.FromArgb(230,168,57),
                                                         Color.FromArgb(225,164,56),
                                                         Color.FromArgb(220,160,55),
                                                         Color.FromArgb(211,156,51),

                                                         Color.FromArgb(206,152,50),
                                                         Color.FromArgb(201,148,49),
                                                         Color.FromArgb(196,144,48),
                                                         Color.FromArgb(191,140,47),
                                                         Color.FromArgb(186,136,46),

                                                         Color.FromArgb(181,132,45),
                                                         Color.FromArgb(176,128,44),
                                                         Color.FromArgb(167,124,40),
                                                         Color.FromArgb(162,120,39),

                                                         Color.FromArgb(157,116,38),
                                                         Color.FromArgb(152,112,37),
                                                         Color.FromArgb(147,108,36),
                                                         Color.FromArgb(142,104,35),
                                                         Color.FromArgb(137,100,34),

                                                         Color.FromArgb(132,96,33),
                                                         Color.FromArgb(123,92,29),
                                                         Color.FromArgb(118,88,28),
                                                         Color.FromArgb(113,84,27),

                                                         Color.FromArgb(108,80,26),
                                                         Color.FromArgb(103,76,25),
                                                         Color.FromArgb(98,72,24),
                                                         Color.FromArgb(93,68,23),
                                                         Color.FromArgb(88,64,22) ,

                                                         Color.FromArgb(79,60,18),
                                                         Color.FromArgb(74,56,17),
                                                         Color.FromArgb(69,52,16),
                                                         Color.FromArgb(64,48,15),

                                                         Color.FromArgb(59,44,14),
                                                         Color.FromArgb(54,40,13),
                                                         Color.FromArgb(49,36,12),
                                                         Color.FromArgb(44,32,11),
                                                         Color.FromArgb(35,28,7),

                                                         Color.FromArgb(30,24,6),
                                                         Color.FromArgb(25,20,5),
                                                         Color.FromArgb(20,16,4),
                                                         Color.FromArgb(15,12,3),

                                                         Color.FromArgb(10,8,2),
                                                         Color.FromArgb(5,4,1) ,
                                                         Color.FromArgb( 0 , 0 ,0 ) 
                                                                                             
                                                     };
        #endregion cellColorsWhite

        public PWColorCellsControlViewInfo(PWColorCellsControl owner, int columnCount, int rowCount)
            : base(owner)
        {
            this.fCustomColors = null;
            this.selectedCellIndex = 0;
            this.columnCount = columnCount;
            this.rowCount = rowCount;
        }
        protected override void UpdateFromOwner()
        {
            Appearance = OwnerControl.Properties.Appearance;
            UpdatePaintAppearance();
        }
        public int GetCellIndex(Point pt)
        {
            int x = (pt.X - CellsInternval) / (CellSize.Width + CellsInternval);//horzIndex 4
            int y = (pt.Y - CellsInternval) / (CellSize.Height + CellsInternval);//vertIndex 7
            if (y > 5) y--;
            if (x < 0 || x > columnCount - 1 || y < 0 || y > rowCount - 1) return -1;
            Rectangle r = GetCellRect(columnCount * y + x);
            if (r.Contains(pt)) return columnCount * y + x;
            return -1;
        }
        public Rectangle GetCellRect(int index)
        {
            int vertIndex = index / columnCount;
            int horzIndex = index - vertIndex * columnCount;

            int x = Bounds.Left + ColorCellsControlViewInfo.CellsInternval +
                    horzIndex * (ColorCellsControlViewInfo.CellsInternval + ColorCellsControlViewInfo.CellSize.Width);
            int y = Bounds.Top + ColorCellsControlViewInfo.CellsInternval +
                    vertIndex * (ColorCellsControlViewInfo.CellsInternval + ColorCellsControlViewInfo.CellSize.Height);
            if (vertIndex > 5)
                y += ColorCellsControlViewInfo.CellsInternval + ColorCellsControlViewInfo.CellSize.Height;

            return new Rectangle(x, y, ColorCellsControlViewInfo.CellSize.Width, ColorCellsControlViewInfo.CellSize.Height);
        }
        public Color GetCellColor(int cellIndex)
        {
            int cellColorLength = 48;
            Color cellColor = Color.Black;

            if (cellIndex >= cellColorLength )
                return GetCustomColor(cellIndex - cellColorLength);
            //if(!SignType.HasValue)
                SignType = MessageControl.Current.Sign.Type;// SignInfo.Current.Type;
            switch(SignType.Value)
            {
                case Core.SignType.Blue:
                    cellColor = cellColorsBlue[cellIndex];
                    break;
                case Core.SignType.Green:
                    cellColor = cellColorsGreen[cellIndex];
                    break;
                case Core.SignType.Red:
                    cellColor = cellColorsRed[cellIndex];
                    break;
                case Core.SignType.Amber:
                    cellColor = cellColorsAmber[cellIndex];
                break;
                case Core.SignType.White:
                    cellColor = cellColorsWhite[cellIndex];
                break;
                default:
                    cellColor = cellColorsRGB[cellIndex];
                break;
            }
            return cellColor;
        }
        public int GetCellColorLength()
        {
            return CellColorsRed.Length;
        }
        protected virtual Color GetCustomColor(int index)
        {
            if (CustomColors == null) return Color.Empty;
            return CustomColors[index];
        }
        internal Size GetBestSize()
        {
            int x = columnCount * CellSize.Width + (columnCount + 1) * CellsInternval;
            int y = rowCount > 5 ? (rowCount + 1) * CellSize.Height + (rowCount + 1) * CellsInternval : rowCount * CellSize.Height + (rowCount + 1) * CellsInternval;
            return new Size(x, y);
        }
        protected new PWColorCellsControl OwnerControl { get { return base.OwnerControl as PWColorCellsControl; } }
        public BorderPainter CellBorderPainter { get { return OwnerControl.LookAndFeel.Painter.Border; } }
        public static Size CellSize { get { return new Size(19, 19); } }
        public static Size BestSize { get { return new Size(8 * CellSize.Width + 9 * CellsInternval, 8 * CellSize.Height + 9 * CellsInternval); } }
        public int SelectedCellIndex { get { return selectedCellIndex; } set { selectedCellIndex = value; } }
        public Color[] CustomColors { get { return OwnerControl.Properties.CustomColors; } }
        public static Color[] CellColorsRGB { get { return cellColorsRGB; } }
        public static Color[] CellColorsRed { get { return cellColorsRed; } }
    }

    public class PWColorCellsControlPainter : BaseControlPainter
    {
        int cellsCount;
        public PWColorCellsControlPainter(int cellsCount)
        {
            this.cellsCount = cellsCount;
        }
        protected override void DrawContent(ControlGraphicsInfoArgs info)
        {
            //PWColorCellsControlViewInfo vi = info.ViewInfo as PWColorCellsControlViewInfo;
            //vi.PaintAppearance.DrawBackground(info.Cache, vi.ClientRect);
            //for (int i = 0; i < cellsCount; i++)
            //{
            //    Rectangle cellBounds = vi.GetCellRect(i);
            //    info.Graphics.FillRectangle(new SolidBrush(vi.GetCellColor(i)), cellBounds);
            //    vi.CellBorderPainter.DrawObject(new BorderObjectInfoArgs(info.Cache, cellBounds, null, ObjectState.Pressed));
            //    if (i == vi.SelectedCellIndex)
            //        ControlPaint.DrawFocusRectangle(info.Graphics, Rectangle.Inflate(cellBounds, 2, 2));
            //}
            PWColorCellsControlViewInfo vi = info.ViewInfo as PWColorCellsControlViewInfo;
            vi.PaintAppearance.DrawBackground(info.Cache, vi.ClientRect);
            for (int i = 0; i < cellsCount; i++)
            {
                Rectangle cellBounds = vi.GetCellRect(i);
                info.Graphics.FillRectangle(new SolidBrush(vi.GetCellColor(i)), cellBounds);
                vi.CellBorderPainter.DrawObject(new BorderObjectInfoArgs(info.Cache, cellBounds, null, ObjectState.Pressed));
                if (i == vi.SelectedCellIndex)
                    ControlPaint.DrawFocusRectangle(info.Graphics, Rectangle.Inflate(cellBounds, 2, 2));
            }
            Rectangle r = vi.ContentRect;
            float x = ColorCellsControlViewInfo.CellsInternval;
            float y = vi.GetCellRect(0).Height * 7 + ColorCellsControlViewInfo.CellsInternval;

            DevExpress.Skins.Skin currentSkin;
            DevExpress.Skins.SkinElement element;
            string elementName;

            currentSkin = DevExpress.Skins.CommonSkins.GetSkin(vi.LookAndFeel);
            elementName = DevExpress.Skins.CommonSkins.SkinTextBorder;
            element = currentSkin[elementName];
            Color skinBorderColor = element.Border.All;

            elementName = DevExpress.Skins.CommonSkins.SkinGroupPanel;
            element = currentSkin[elementName];
            Color skinBackColor = element.Color.BackColor;

            info.Graphics.DrawLine(new Pen(skinBorderColor), x, y + 1, 8 * vi.GetCellRect(0).Width + (8) * ColorCellsControlViewInfo.CellsInternval, y + 1);
            Rectangle stringRect = new Rectangle(0, (int)y + 2, 8 * (vi.GetCellRect(0).Width + ColorCellsControlViewInfo.CellsInternval + ColorCellsControlViewInfo.CellsInternval), vi.GetCellRect(0).Height);
            info.Graphics.FillRectangle(new SolidBrush(skinBackColor), stringRect);
            info.Graphics.DrawString("Right Click to Define Custom Color", vi.PaintAppearance.Font, vi.PaintAppearance.GetForeBrush(info.Cache), x, y + 2, vi.PaintAppearance.GetStringFormat(vi.DefaultTextOptions));

        }
    }
}