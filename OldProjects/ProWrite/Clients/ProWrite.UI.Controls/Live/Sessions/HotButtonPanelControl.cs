using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using DevExpress.XtraEditors;
using ProWrite.Entity.Live;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public partial class HotButtonPanelControl : UserControl
    {
        private const int _defaultColumnQuantity = 4;
        private const int _defaultMargin = 4;
        private const int _defaultWidth = 100;
        private const int _defaultHeight = 40;
        private const int _defaultButtonQuantity = _defaultColumnQuantity * 5;
        private const int _defaultBlankCell = _defaultColumnQuantity * 2;

        private Size _smallButtonSize = new Size(_defaultWidth, _defaultHeight);
        private Size _largeButtonSize = new Size(_defaultWidth, _defaultHeight * 2 + _defaultMargin);

        private List<object> _lstButton = new List<object>();

        public event EventHandler<MouseEventArgs> OnButtonClick = null;
        public event EventHandler<MouseEventArgs> OnButtonContainerClick = null;

        public HotButtonPanelControl()
        {
            InitializeComponent();

            if (!DesignMode)
                Init();
        }

        private void Init()
        {
            
        }

        public void New()
        {
            if (_lstButton.Count > 0)
                _lstButton.Clear();

            _lstButton.AddRange(new object[_defaultButtonQuantity]);
            UpdateDrawGrid();
        }

        private List<HotButtonItemInfo> _hotButtonItems = new List<HotButtonItemInfo>();
        public HotButtonItemInfo[] HotButtonItems
        {
            set
            {
                _hotButtonItems.Clear();
                _hotButtonItems.AddRange(value);
                SetHotButtonItem();
                UpdateDrawGrid();
            }
            get 
            {
                _hotButtonItems.Clear();
                GetHotButtonItem();
                return _hotButtonItems.ToArray();
            }
        }

        private void SetHotButtonItem()
        {
            this.Controls.Clear();
            this._lstButton.Clear();

            for (int i = 0; i < _hotButtonItems.Count; i++)
            {
                object obj = null;

                if (_hotButtonItems[i].Name != string.Empty)
                {
                    PanelControl panel = null;
                    if (_hotButtonItems[i].IsLarge)
                    {
                        LargeButtonControl btn = new LargeButtonControl();
                        btn.ButtonName = _hotButtonItems[i].ButtonName;
                        btn.BackColor = _hotButtonItems[i].ButtonBackColor;
                        btn.Sign = _hotButtonItems[i].Sign;
                        btn.MainHotKey = _hotButtonItems[i].MainHotKey;
                        btn.SubHotKey = _hotButtonItems[i].SubHotKey;
                        panel = NewButtonContainer(ButtonContainerType.Large);
                        panel.Controls.Add(btn);
                    }
                    else
                    {
                        SmallButtonControl btn = new SmallButtonControl();
                        btn.ButtonName = _hotButtonItems[i].ButtonName;
                        btn.BackColor = _hotButtonItems[i].ButtonBackColor;
                        btn.Sign = _hotButtonItems[i].Sign;
                        btn.MainHotKey = _hotButtonItems[i].MainHotKey;
                        btn.SubHotKey = _hotButtonItems[i].SubHotKey;
                        panel = NewButtonContainer(ButtonContainerType.Small);
                        panel.Controls.Add(btn);
                    }
                    _lstButton.Add(panel);
                }
                else
                {
                    _lstButton.Add(obj);
                }
            }
        }

        private void GetHotButtonItem()
        {
            if (this.Controls.Count == 0) return;

            for (int i = 0; i < this._lstButton.Count; i++)
            {
                HotButtonItemInfo item = new HotButtonItemInfo();
                item.Name = string.Empty;

                if (_lstButton[i] != null)
                {
                    object btnCtrl = (_lstButton[i] as PanelControl).Controls[0];
                    if (btnCtrl.GetType() == typeof(LargeButtonControl))
                    {
                        LargeButtonControl btn = btnCtrl as LargeButtonControl;
                        item = GetLargeButtonItemContent(btn);
                    }
                    else
                    {
                        SmallButtonControl btn = btnCtrl as SmallButtonControl;
                        item = GetSmallButtonItemContent(btn);
                    }
                }

                _hotButtonItems.Add(item);
            }
        }

        private HotButtonItemInfo GetLargeButtonItemContent(LargeButtonControl btn)
        {
            HotButtonItemInfo item = new HotButtonItemInfo();
            item.CreateTime = DateTime.Now;
            item.Id = Guid.NewGuid().ToString();
            item.Name = btn.ButtonName;
            item.Sign = btn.Sign;
            item.SubHotKey = btn.SubHotKey;
            item.MainHotKey = btn.MainHotKey;
            item.ButtonBackColor = btn.ButtonColor;
            item.IsLarge = true;
            item.ButtonName = btn.ButtonName;
            return item;
        }

        private HotButtonItemInfo GetSmallButtonItemContent(SmallButtonControl btn)
        {
            HotButtonItemInfo item = new HotButtonItemInfo();
            item.CreateTime = DateTime.Now;
            item.Id = Guid.NewGuid().ToString();
            item.Name = btn.ButtonName;
            item.Sign = btn.Sign;
            item.SubHotKey = btn.SubHotKey;
            item.MainHotKey = btn.MainHotKey;
            item.ButtonBackColor = btn.ButtonColor;
            item.IsLarge = false;
            item.ButtonName = btn.ButtonName;
            return item;
        }

        private Control[] DrawGrid()
        {
            Control[] ctls = new Control[CellCount];

            Point lastButtonPoint = new Point(0, 0);
            List<int> lstLargeButton = new List<int>();

            int loopCount = CellCount % ColumnCount == 0 ? CellCount / ColumnCount : CellCount / ColumnCount + 1;

            int drawButtonIndex = 0;
            int drawCellIndex = 0;
            PanelControl cell = null;

            for (int i = 0; i < loopCount; i++)
            {
                if (lastButtonPoint.Y + ButtonHeight > this.Height)
                    this.Height += ButtonHeight;

                for (int index = 0; index < ColumnCount; index++)
                {
                    Point location = lastButtonPoint;
                    if (index == 0)
                        location = new Point(0, lastButtonPoint.Y);
                    else
                        location = new Point(lastButtonPoint.X + CellMargin + ButtonWidth, lastButtonPoint.Y);
                    lastButtonPoint = location;

                    cell = GetNextCell(location, drawButtonIndex);

                    if (!CheckLargeButtonList(lstLargeButton, drawCellIndex))
                    {
                        if (cell != null)
                        {
                            ctls[drawButtonIndex] = cell;
                            cell = null;
                        }
                        ButtonContainerType btnType = GetButtonType(drawButtonIndex);
                        if (btnType == ButtonContainerType.Large)
                        {
                            lstLargeButton.Add(drawCellIndex);
                            lstLargeButton.Add(drawCellIndex + ColumnCount);
                        }
                        drawButtonIndex++;
                    }

                    drawCellIndex++;
                }
                lastButtonPoint = new Point(lastButtonPoint.X, lastButtonPoint.Y + ButtonHeight + CellMargin);
            }
            return ctls;
        }

        private void RegisterEvent(PanelControl panel)
        {
            panel.DragEnter += new DragEventHandler(ctlPanel_DragEnter);
            panel.DragDrop += new DragEventHandler(ctlPanel_DragDrop);
            panel.MouseDown += new MouseEventHandler(panel_MouseDown);
            panel.MouseClick += new MouseEventHandler(panel_MouseClick);

            if (panel.Controls.Count > 0)
            {
                if (panel.Controls[0].GetType() == typeof(SmallButtonControl))
                {
                    SmallButtonControl btn = panel.Controls[0] as SmallButtonControl;
                    btn.MouseDown += new MouseEventHandler(btnSmall_MouseDown);
                }
                else if (panel.Controls[0].GetType() == typeof(LargeButtonControl))
                {
                    LargeButtonControl btn = panel.Controls[0] as LargeButtonControl;
                    btn.MouseDown += new MouseEventHandler(btnLarge_MouseDown);
                }
            }
        }

        private void UnRegisterEvent(PanelControl panel)
        {
            panel.DragEnter -= ctlPanel_DragEnter;
            panel.DragDrop -= ctlPanel_DragDrop;
            panel.MouseDown -= panel_MouseDown;
            panel.MouseClick += panel_MouseClick;

            if (panel.Controls.Count > 0)
            {
                if (panel.Controls[0].GetType() == typeof(SmallButtonControl))
                {
                    SmallButtonControl btn = panel.Controls[0] as SmallButtonControl;
                    btn.MouseDown -= btnSmall_MouseDown;
                }
                else if (panel.Controls[0].GetType() == typeof(LargeButtonControl))
                {
                    LargeButtonControl btn = panel.Controls[0] as LargeButtonControl;
                    btn.MouseDown -= btnLarge_MouseDown;
                }
            }
        }

        void panel_MouseClick(object sender, MouseEventArgs e)
        {
            if (OnButtonClick != null)
                OnButtonContainerClick(sender, e);
        }

        private PanelControl GetNextCell(Point location, int cellIndex)
        {
            object obj = null;

                obj = _lstButton[cellIndex];

            PanelControl panel = null;

            if (obj != null)
            {
                panel = obj as PanelControl;
            }
            else
            {
                panel = NewButtonContainer(ButtonContainerType.Small);
            }

            RegisterEvent(panel);

            panel.Location = location;
            return panel;
        }

        private bool CheckLargeButtonList(List<int> lstLargeButton, int cellIndex)
        {
            bool bCheck = false;
            if (lstLargeButton.IndexOf(cellIndex) >= 0)
                bCheck = true;
            return bCheck;
        }

        public void AddButtonContainer(object btnContainer)
        {
            Add(btnContainer);
            AutoAddBlankCell();
            UpdateDrawGrid();
        }

        private void Add(object cell)
        {
            for(int i = 0; i < _lstButton.Count; i++)
            {
                if (_lstButton[i] == null)
                {
                    _lstButton[i] = cell;
                    break;
                }
            }
        }

        private void Remove(object cell)
        {
            foreach (object tmpCell in _lstButton)
            {
                if (tmpCell == cell)
                {
                    Object obj = tmpCell;
                    _lstButton.Remove(obj);
                    break;
                }
            }
        }

        private int CellCount
        {
            get
            {
                return _lstButton.Count;
            }
        }

        private int ColumnCount
        {
            get 
            {
                return _defaultColumnQuantity;
            }
        }

        private int ButtonHeight
        {
            get
            {
                return _defaultHeight;
            }
        }

        private int ButtonWidth
        {
            get
            {
                return _defaultWidth;
            }
        }

        private int CellMargin
        {
            get
            {
                return _defaultMargin;
            }
        }

        private void AutoAddBlankCell()
        {
            int blankCell = 0;
            foreach (object obj in _lstButton)
            {
                if (obj == null)
                {
                    blankCell++;
                    if (blankCell == _defaultBlankCell)
                        return;
                }
            }

            _lstButton.AddRange(new object[_defaultBlankCell - blankCell]);
        }

        private void UpdateDrawGrid()
        {
            if (this.Controls.Count > 0)
            {
                for (int i = 0; i < this.Controls.Count; i++)
                {
                    UnRegisterEvent((this.Controls[i] as PanelControl));
                }
                this.Controls.Clear();
            }

            Control[] ctls = DrawGrid();

            this.Controls.AddRange(ctls);
            this.Invalidate();
        }

        public enum ButtonContainerType
        {
            Small,
            Large
        }

        void ctlPanel_DragDrop(object sender, DragEventArgs e)
        {
            if (e.Effect == DragDropEffects.Move)
            {
                PanelControl targetPanel = sender as PanelControl;
                PanelControl sourcePanel = e.Data.GetData(typeof(PanelControl)) as PanelControl;

                int sourceIndex = this.Controls.IndexOf(sourcePanel);
                int targetIndex = this.Controls.IndexOf(targetPanel);

                if (targetPanel.Controls.Count > 0)
                {
                    _lstButton[targetIndex] = sourcePanel;
                    _lstButton[sourceIndex] = targetPanel;
                }
                else
                {
                    _lstButton[targetIndex] = sourcePanel;
                    _lstButton[sourceIndex] = null;
                }

                UpdateDrawGrid();
            }
        }

        void ctlPanel_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(typeof(PanelControl)))
            {
                e.Effect = DragDropEffects.Move;
            }
        }

        void panel_MouseDown(object sender, MouseEventArgs e)
        {
            if (sender.GetType() == typeof(SmallButtonControl))
            {
                SmallButtonControl btnSamll = sender as SmallButtonControl;
                PanelControl panel = btnSamll.Parent as PanelControl;
                panel.DoDragDrop(panel, DragDropEffects.Move);
            }
            else if (sender.GetType() == typeof(LargeButtonControl))
            {
                LargeButtonControl btnLarge = sender as LargeButtonControl;
                PanelControl panel = btnLarge.Parent as PanelControl;
                panel.DoDragDrop(panel, DragDropEffects.Move);
            }
        }

        void btnSmall_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                panel_MouseDown(sender, e);
            }
            else if (e.Button == MouseButtons.Right)
            {
                if (OnButtonClick != null)
                    OnButtonClick(sender, e);
            }
        }

        void btnLarge_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                panel_MouseDown(sender, e);
            }
            else if (e.Button == MouseButtons.Right)
            {
                if (OnButtonClick != null)
                    OnButtonClick(sender, e);
            }
        }

        public PanelControl NewButtonContainer(ButtonContainerType containerType)
        {
            PanelControl panel = new PanelControl();

            if (containerType == ButtonContainerType.Small)
                panel.Size = _smallButtonSize;
            else
                panel.Size = _largeButtonSize;

            panel.AllowDrop = _lockState;

            return panel;
        }

        private ButtonContainerType GetButtonType(int idx)
        {
            ButtonContainerType type = ButtonContainerType.Small;
            if (idx < _lstButton.Count)
            {
                object cell = _lstButton[idx];
                if (cell != null)
                {
                    PanelControl panel = cell as PanelControl;
                    if (panel.Controls.Count > 0)
                    {
                        object ctrl = panel.Controls[0];
                        if (ctrl.GetType() == typeof(LargeButtonControl))
                        {
                            type = ButtonContainerType.Large;
                        }
                    }
                }
            }
            return type;
        }

        private bool _lockState = true;
        public bool Lock
        {
            set
            {
                if (_lockState != value)
                {
                    SetCellLockState(value);
                    _lockState = value;
                }
            }
            get
            {
                return _lockState;
            }
        }

        private void SetCellLockState(bool state)
        {
            for (int i = 0; i < this.Controls.Count; i++)
                (this.Controls[i] as PanelControl).AllowDrop = state;
        }

        public void UpdateHotButtonData(object oldBtn, object newBtn, LiveSign[] signs)
        {
            for (int i = 0; i < this.Controls.Count; i++)
            {
                PanelControl panel = this.Controls[i] as PanelControl;

                if (panel.Controls.Count > 0)
                {
                    Control ctrl = panel.Controls[0];

                    if (ctrl == oldBtn)
                    {
                        Control hotkey = newBtn as Control;
                        hotkey.Dock = DockStyle.Fill;

                        if (typeof(SmallButtonControl) == hotkey.GetType())
                        {
                            SmallButtonControl btn = hotkey as SmallButtonControl;
                            btn.Sign = signs;

                            PanelControl newPanel = NewButtonContainer(HotButtonPanelControl.ButtonContainerType.Small);
                            newPanel.Controls.Add(hotkey);

                            UnRegisterEvent(panel);

                            _lstButton.Remove(panel);
                            _lstButton.Insert(i, newPanel);
                        }
                        else if (typeof(LargeButtonControl) == hotkey.GetType())
                        {
                            LargeButtonControl btn = hotkey as LargeButtonControl;
                            btn.Sign = signs;

                            PanelControl newPanel = NewButtonContainer(HotButtonPanelControl.ButtonContainerType.Large);
                            newPanel.Controls.Add(hotkey);

                            UnRegisterEvent(panel);

                            _lstButton.Remove(panel);
                            _lstButton.Insert(i, newPanel);
                        }

                        break;
                    }
                }
            }

            UpdateDrawGrid();
        }

        public void RemoveHotButton(object btn)
        {
            for (int i = 0; i < this.Controls.Count; i++)
            {
                PanelControl panel = this.Controls[i] as PanelControl;

                if (panel.Controls.Count > 0)
                {
                    Control ctrl = panel.Controls[0];

                    if (ctrl == btn)
                    {
                        _lstButton[i] = null;
                        break;
                    }
                }
            }
            UpdateDrawGrid();
        }

    }
}
