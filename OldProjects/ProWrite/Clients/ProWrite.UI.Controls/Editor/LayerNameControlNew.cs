using System;
using System.Collections.Generic;
using System.Text;
using DevExpress.XtraEditors;
using System.Windows.Forms;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Drawing.Text;

namespace ProWrite.UI.Controls.Editor
{
    public class LayerNameControlNew:Control
    {
        private Caret caret;
        protected string text = "";
        protected int currentPosition = 0;
        private const int DefaultMaxLength = 50;
        private int maxLength = DefaultMaxLength;

        public LayerNameControlNew()
        {
            this.AllowDrop = true;
            this.BackColor = System.Drawing.Color.Gainsboro;
            this.ForeColor = System.Drawing.Color.ForestGreen;
            this.Margin = new Padding(0);
            this.Size = new Size(133, 25);
            caret = new Caret(this);
            caret.Size = new Size(2, Font.Height);
            caret.Position = new Point(1, 0);
            //caret.Show();
            //Cursor = Cursors.IBeam;
        }

        public new string Text
        {
            get { return text; }
            set
            {
                text = value;
                Invalidate();
            }
        }

        public int MaxLength
        {
            get { return maxLength; }
            set { maxLength = value; }
        }

        protected override void Dispose(bool disposing)
        {
            caret.Dispose();
            base.Dispose(disposing);
        }

        protected override void OnKeyPress(KeyPressEventArgs e)
        {
            base.OnKeyPress(e);

            caret.Hide();
            Graphics g = CreateGraphics();
            g.FillRectangle(new SolidBrush(BackColor),
                             new RectangleF(Point.Empty,
                             g.MeasureString(text, Font,
                             Point.Empty, StringFormat.GenericTypographic)));

           
            switch (e.KeyChar)
            {
                case '\b':
                    if (currentPosition > 0)
                    {
                        text = text.Substring(0, currentPosition - 1) +
                                                    text.Substring(currentPosition);
                        currentPosition -= 1;
                    }
                    break;
                case '\r':
                case '\n':
                    break;
                default:
                    if (currentPosition == maxLength)
                        break;
                    if (currentPosition == text.Length)
                        text += e.KeyChar;
                    else
                        text = text.Substring(0, currentPosition) +
                                  e.KeyChar +
                                  text.Substring(currentPosition);
                    currentPosition++;
                    break;
            }
            g.TextRenderingHint = TextRenderingHint.AntiAlias;
            g.DrawString(text, Font, new SolidBrush(ForeColor),
                            0, 0, StringFormat.GenericTypographic);
            PositionCaret(g);
            g.Dispose();
            caret.Show();
        }

        protected override void OnKeyUp(KeyEventArgs e)
        {
            base.OnKeyUp(e);

            switch (e.KeyData)
            {
                case Keys.Left:
                    if (currentPosition > 0)
                        currentPosition--;
                    break;
                case Keys.Right:
                case Keys.Back:
                    if (currentPosition < text.Length)
                        currentPosition++;
                    break;
                case Keys.Home:
                    currentPosition = 0;
                    break;
                case Keys.End:
                    currentPosition = text.Length;
                    break;
                case Keys.Delete:
                    if (currentPosition < text.Length)
                    {
                        currentPosition++;
                        OnKeyPress(new KeyPressEventArgs('\b'));
                    }
                    break;
                default:
                    return;
            }
            using (Graphics g = CreateGraphics())
                PositionCaret(g);
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            base.OnMouseDown(e);
            if (text.Length == 0)
                return;

            Graphics g = CreateGraphics();
            float xPrev = 0;
            int i;

            for (i = 0; i < text.Length; i++)
            {
                SizeF sizef = g.MeasureString(text.Substring(0, i + 1),
                                         Font, Point.Empty,
                                         StringFormat.GenericTypographic);

                if (Math.Abs(e.X - xPrev) < Math.Abs(e.X - sizef.Width))
                    break;

                xPrev = sizef.Width;
            }
            currentPosition = i;

            PositionCaret(g);
            g.Dispose();
        }

        protected void PositionCaret(Graphics g)
        {
            string str = text.Substring(0, currentPosition);
            StringFormat strfmt = StringFormat.GenericTypographic;
            strfmt.FormatFlags |= StringFormatFlags.MeasureTrailingSpaces;
            SizeF sizef = g.MeasureString(str, Font, Point.Empty, strfmt);
            caret.Position = new Point((int)sizef.Width, 0);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            g.TextRenderingHint = TextRenderingHint.AntiAlias;
            //ControlPaint.DrawBorder(g, Bounds, Color.Black, ButtonBorderStyle.Solid);
            g.DrawString(text, Font, new SolidBrush(ForeColor),
                            0, 0, StringFormat.GenericTypographic);
        }
    }

    class Caret:IDisposable
    {
        [DllImport("user32.dll")]
        private static extern int CreateCaret(IntPtr hwnd, IntPtr hbm, int cx, int cy);
        [DllImport("user32.dll")]
        private static extern int DestroyCaret();
        [DllImport("user32.dll")]
        private static extern int SetCaretPos(int x, int y);
        [DllImport("user32.dll")]
        private static extern int ShowCaret(IntPtr hwnd);
        [DllImport("user32.dll")]
        private static extern int HideCaret(IntPtr hwnd);
        
        Control _ctrl;
        Size _size;
        Point _ptPos;
        bool _bVisible;
        
        private Caret()
        {
        }

        public Caret(Control ctrl)
        {
            this._ctrl = ctrl;
            Position = Point.Empty;
            Size = new Size(1, ctrl.Font.Height);

            _ctrl.GotFocus += new EventHandler(ControlOnGotFocus);
            _ctrl.LostFocus += new EventHandler(ControlOnLostFocus);

            if (_ctrl.Focused)
                ControlOnGotFocus(_ctrl, new EventArgs());
        }
       
        public Size Size
        {
            get
            {
                return _size;
            }
            set
            {
                _size = value;
            }
        }
        public Point Position
        {
            get
            {
                return _ptPos;
            }
            set
            {
                _ptPos = value;
                SetCaretPos(_ptPos.X, _ptPos.Y);
            }
        }
        public bool Visibility
        {
            get
            {
                return _bVisible;
            }
            set
            {
                if (_bVisible = value)
                    ShowCaret(_ctrl.Handle);
                else
                    HideCaret(_ctrl.Handle);
            }
        }
        // Methods
        public void Show()
        {
            Visibility = true;
        }
        public void Hide()
        {
            Visibility = false;
        }
        public void Dispose()
        {
            // If the control has focus, destroy the caret.

            if (_ctrl.Focused)
                ControlOnLostFocus(_ctrl, new EventArgs());

            _ctrl.GotFocus -= new EventHandler(ControlOnGotFocus);
            _ctrl.LostFocus -= new EventHandler(ControlOnLostFocus);
        }

        // Event handlers
        void ControlOnGotFocus(object obj, EventArgs ea)
        {
            CreateCaret(_ctrl.Handle, IntPtr.Zero,
                        Size.Width, Size.Height);
            SetCaretPos(Position.X, Position.Y);
            Show();
        }
        void ControlOnLostFocus(object obj, EventArgs ea)
        {
            Hide();
            DestroyCaret();
        }
    }
}
