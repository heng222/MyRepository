using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Live;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public partial class HotButtonControl : DevExpress.XtraEditors.XtraUserControl
    {
        private List<object> _lstButton = new List<object>();

        public HotButtonControl()
        {
            InitializeComponent();

            if(!DesignMode)
                Init();
        }

        public void LoadSession()
        {
            hotButtonPanelControl.HotButtonItems = SessionInfo.Current.HotButtons;
        }

        public void Save()
        {
            SessionInfo.Current.ClearAllHotButton();
            SessionInfo.Current.AddHotButton(hotButtonPanelControl.HotButtonItems);
        }

        public void New()
        {
            hotButtonPanelControl.New();
        }

        private void Init()
        {
            scoBar.Maximum = hotButtonPanelControl.Height;
            scoBar.Minimum = hotButtonPanelControl.MinimumSize.Height;
            hotButtonPanelControl.MouseClick += new MouseEventHandler(hotButtonPanelControl_MouseClick);
            hotButtonPanelControl.MouseLeave += new EventHandler(hotButtonPanelControl_MouseLeave);
            hotButtonPanelControl.OnButtonClick += new EventHandler<MouseEventArgs>(hotButtonPanelControl_OnButtonClick);
            hotButtonPanelControl.OnButtonContainerClick += new EventHandler<MouseEventArgs>(hotButtonPanelControl_OnButtonContainerClick);

            SetPoputMenuLock(false);
        }

        void hotButtonPanelControl_OnButtonContainerClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                OpenPoputMenu(e.Location, null);
            }
        }

        void hotButtonPanelControl_OnButtonClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                OpenPoputMenu(e.Location, sender);
            }
        }

        void hotButtonPanelControl_MouseLeave(object sender, EventArgs e)
        {

        }

        void hotButtonPanelControl_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                OpenPoputMenu(e.Location, null);
            }
        }

        private void InitContentMenu()
        {

        }

        private void scoBar_Scroll(object sender, ScrollEventArgs e)
        {
            hotButtonPanelControl.Top = -e.NewValue;
        }

        private void itmLockButton_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            ClosePoputMenu();
            SetPoputMenuLock(true);
        }

        private void SetPoputMenuLock(bool lockState)
        {
            if (lockState)
            {
                itmLockButton.Enabled = false;
                itmUnLockButton.Enabled = true;
            }
            else
            {
                itmLockButton.Enabled = true;
                itmUnLockButton.Enabled = false;
            }
            hotButtonPanelControl.Lock = !lockState;
        }

        private void itmUnLockButton_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            ClosePoputMenu();
            SetPoputMenuLock(false);
        }

        private void itmAddButton_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            HotButtonSettingForm frmHotButton = null;
            try
            {
                frmHotButton = new HotButtonSettingForm();
                frmHotButton.SignList = SignList;

                if (frmHotButton.ShowDialog() == DialogResult.OK)
                {
                    Control hotkey = frmHotButton.HotKeyButton;
                    hotkey.Dock = DockStyle.Fill;

                    if (typeof(SmallButtonControl) == hotkey.GetType())
                    {
                        SmallButtonControl btn = hotkey as SmallButtonControl;
                        btn.Sign = frmHotButton.LiveSigns;

                        PanelControl panel = hotButtonPanelControl.NewButtonContainer(HotButtonPanelControl.ButtonContainerType.Small);
                        panel.Controls.Add(btn);
                        hotButtonPanelControl.AddButtonContainer(panel);
                    }
                    else if (typeof(LargeButtonControl) == hotkey.GetType())
                    {
                        LargeButtonControl btn = hotkey as LargeButtonControl;
                        btn.Sign = frmHotButton.LiveSigns;

                        PanelControl panel = hotButtonPanelControl.NewButtonContainer(HotButtonPanelControl.ButtonContainerType.Large);
                        panel.Controls.Add(hotkey);
                        hotButtonPanelControl.AddButtonContainer(panel);
                    }
                }
            }
            finally
            {
                if (frmHotButton != null)
                    frmHotButton.Dispose();
                ClosePoputMenu();
            }
        }

        private object _editButton = null;
        
        private void itmRemoveButton_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            if (_editButton != null)
            {
                hotButtonPanelControl.RemoveHotButton(_editButton);
            }
            ClosePoputMenu();
        }

        private void itmEditButton_ItemClick(object sender, DevExpress.XtraBars.ItemClickEventArgs e)
        {
            if (_editButton != null)
            {
                HotButtonSettingForm frmHotButton = null;

                try
                {
                    frmHotButton = new HotButtonSettingForm();
                    frmHotButton.SignList = SignList;
                    frmHotButton.Load(_editButton);

                    if (frmHotButton.ShowDialog() == DialogResult.OK)
                    {
                        hotButtonPanelControl.UpdateHotButtonData(_editButton, frmHotButton.HotKeyButton, frmHotButton.LiveSigns);
                    }
                }
                finally
                {
                    if (frmHotButton != null)
                        frmHotButton.Dispose();
                    ClosePoputMenu();
                }
            }
        }

        private void OpenPoputMenu(Point openPoint, object editBtn)
        {
            popupMenu.ShowPopup(openPoint);

            if (editBtn != null)
            {
                itmEditButton.Enabled = true;
                itmRemoveButton.Enabled = true;
                _editButton = editBtn;
            }
            else
            {
                itmEditButton.Enabled = false;
                itmRemoveButton.Enabled = false;
            }
        }

        private void ClosePoputMenu()
        {
            if (popupMenu.Opened)
            {
                popupMenu.HidePopup();
            }
            _editButton = null;
        }

        public bool ContextMenuEnable
        {
            set
            {
                
            }
        }

        private DashboardItem[] _signItems = null;
        public DashboardItem[] SignList
        {
            set
            {
                _signItems = value;
            }
            get
            {
                return _signItems;
            }
        }
        

    }
}
