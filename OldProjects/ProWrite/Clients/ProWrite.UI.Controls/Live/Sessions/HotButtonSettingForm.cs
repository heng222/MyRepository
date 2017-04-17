using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using ProWrite.Entity.Live;
using ProWrite.Entity.Dashboard;
using DevExpress.XtraEditors;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public partial class HotButtonSettingForm : Form
    {
        public HotButtonSettingForm()
        {
            InitializeComponent();

            if(!DesignMode)
                Init();
        }

        enum ButtonSizeType
        {
            Small,
            Large
        }

        Color _defaulButtonColor = Color.Red;

        private MainHotKey _mainKey;
        private SubHotKey _subKey;

        private bool _hotButtonSettingFinish = false;
        private List<LiveSign> _lstSign = new List<LiveSign>();

        private bool _useButtonGraphic = false;
        private Image _buttonImage = null;

        public void Load(object button)
        {
            if (typeof(SmallButtonControl) == button.GetType())
            {
                SmallButtonControl btn = button as SmallButtonControl;

                txtName.Text = btn.ButtonName;
                _mainKey = btn.MainHotKey;
                _subKey = btn.SubHotKey;
                HotKeyChanged();
                _hotButtonSettingFinish = true;
                ddlColor.EditValue = btn.ButtonColor;
                rdoSize.SelectedIndex = 0;
                
                LoadSignsFromSession(btn.Sign);
            }
            else if (typeof(LargeButtonControl) == button.GetType())
            {
                LargeButtonControl btn = button as LargeButtonControl;

                txtName.Text = btn.ButtonName;
                _mainKey = btn.MainHotKey;
                _subKey = btn.SubHotKey;
                HotKeyChanged();
                _hotButtonSettingFinish = true;
                ddlColor.EditValue = btn.ButtonColor;
                rdoSize.SelectedIndex = 1;
                LoadSignsFromSession(btn.Sign);
            }
        }

        private void LoadSignsFromSession(LiveSign[] signs)
        {
            for (int i = 0; i < signs.Length; i++)
            {
                foreach (DashboardItem item in SignList)
                {
                    if (item.Name == signs[i].Name)
                    {
                        LoadSignToControl(signs[i]);
                    }
                }
            }
        }

        private void LoadSignToControl(LiveSign sign)
        {
            for (int i = 0; i < panelSign.Controls.Count; i++)
            {
                SignSettingControl ctlSign = panelSign.Controls[i] as SignSettingControl;
                if (ctlSign.SignName == sign.Name)
                {
                    ctlSign.LiveSign = sign;
                    break;
                }
            }
        }

        private void Init()
        {
            ddlColor.Text = _defaulButtonColor.ToString();
            rdoSize.SelectedIndex = 0;
            rdoSize_SelectedIndexChanged(null, null);
        }

        private void rdoSize_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(rdoSize.SelectedIndex == 0)
            {
                ButtonTypeChanged(ButtonSizeType.Small);
            }
            else if (rdoSize.SelectedIndex == 1)
            {
                ButtonTypeChanged(ButtonSizeType.Large);
            }
        }

        private void ddlColor_EditValueChanged(object sender, EventArgs e)
        {
            rdoSize_SelectedIndexChanged(sender, e);
        }

        private void txtName_EditValueChanging(object sender, DevExpress.XtraEditors.Controls.ChangingEventArgs e)
        {
            rdoSize_SelectedIndexChanged(sender, e);
        }

        private void txtHotKey_DoubleClick(object sender, EventArgs e)
        {
            btnHotKey_Click(sender, e);
        }

        private void ButtonTypeChanged(ButtonSizeType buttonType)
        {
            if (buttonType == ButtonSizeType.Small)
            {
                btnSmall.Visible = true;
                btnLarge.Visible = false;

                btnSmall.ButtonName = txtName.Text;
                btnSmall.ButtonColor = (Color)(ddlColor.EditValue);

                if (_hotButtonSettingFinish)
                {
                    btnSmall.MainHotKey = _mainKey;
                    btnSmall.SubHotKey = _subKey;
                }

                if (_useButtonGraphic)
                {
                    btnSmall.BackgroundImage = _buttonImage;
                }
                else
                {
                    btnSmall.BackgroundImage = null;
                }

                _returnButtonControl = btnSmall;
            }
            else if (buttonType == ButtonSizeType.Large)
            {
                btnSmall.Visible = false;
                btnLarge.Visible = true;

                btnLarge.ButtonName = txtName.Text;
                btnLarge.ButtonColor = (Color)(ddlColor.EditValue);

                if (_hotButtonSettingFinish)
                {
                    btnLarge.MainHotKey = _mainKey;
                    btnLarge.SubHotKey = _subKey;
                }

                if (_useButtonGraphic)
                {
                    btnLarge.BackgroundImage = _buttonImage;
                }
                else
                {
                    btnLarge.BackgroundImage = null;
                }

                _returnButtonControl = btnLarge;
            }
        }

        private Control _returnButtonControl;
        public Control HotKeyButton
        {
            get
            {
                return _returnButtonControl;
            }
        }

        private void btnHotKey_Click(object sender, EventArgs e)
        {
            HotKeyAssignForm frmHotKeyAssign = null;

            try
            {
                frmHotKeyAssign = new HotKeyAssignForm();
                if (frmHotKeyAssign.ShowDialog(this) == DialogResult.OK)
                {
                    _hotButtonSettingFinish = true;
                    _mainKey = frmHotKeyAssign.MainHotKey;
                    _subKey = frmHotKeyAssign.SubHotKey;
                    rdoSize_SelectedIndexChanged(sender, e);

                    HotKeyChanged();
                }
            }
            finally
            {
                if (frmHotKeyAssign != null)
                    frmHotKeyAssign.Dispose();
            }
        }

        private void HotKeyChanged()
        {
            txtHotKey.Text = "(" + _mainKey.ToString() + ")" + " + " + _subKey.ToString();
        }

        public LiveSign[] LiveSigns
        {
            get
            {
                return _lstSign.ToArray();
            }
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            int ctlCount = panelSign.Controls.Count;

            if (ctlCount > 0)
            {
                for (int i = 0; i < ctlCount; i++)
                {
                    SignSettingControl ctlSign = panelSign.Controls[i] as SignSettingControl;

                    if(ctlSign.SignEnable)
                        _lstSign.Add(ctlSign.LiveSign);
                }
            }

            this.DialogResult = DialogResult.OK;
        }

        private void btnApply_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
        }

        private DashboardItem[] _signItem;
        public DashboardItem[] SignList
        {
            set
            {
                _signItem = value;
                LoadSign();
            }
            get
            {
                return _signItem;
            }
        }

        private void LoadSign()
        {
            if (_signItem != null)
            {
                DashboardItem[] itms = _signItem;

                if (itms.Length > 0)
                {

                    SignSettingControl sign = null;
                    Point point = new Point(1, 1);

                    for (int i = 0; i < itms.Length; i++)
                    {
                        if (itms[i] == null)
                        {
                            return;
                        }
                        sign = new SignSettingControl();
                        sign.OnButtonGraphicCheckChanged += new EventHandler<ButtonGraphicEventArgs>(sign_OnButtonGraphicCheckChanged);
                        sign.SignName = itms[i].Name;
                        sign.Location = point;
                        sign.SignItem = itms[i];
                        sign.SignEnable = false;
                        panelSign.Controls.Add(sign);
                        point.Y += sign.Height + 4;
                    }

                    if (panelSign.Height < point.Y)
                        panelSign.Height = point.Y;

                    SetScrollBar();
                }
            }
        }


        void sign_OnButtonGraphicCheckChanged(object sender, ButtonGraphicEventArgs e)
        {
            for (int i = 0; i < panelSign.Controls.Count; i++)
            {
                SignSettingControl sign = panelSign.Controls[i] as SignSettingControl;
                if (sign != e.Sign)
                    sign.ButtonGraphic = false;
            }

            _useButtonGraphic = e.Sign.ButtonGraphic;

            if (e.Sign.LiveMessage != null)
            {
                if (e.Sign.LiveMessage.Target != null && e.Sign.LiveMessage.Image != null)
                {
                    _buttonImage = e.Sign.LiveMessage.Image;
                }
                else
                {
                    _buttonImage = null;
                }
            }
            else
            {
                _buttonImage = null;
            }

            rdoSize_SelectedIndexChanged(sender, e);
        }

        private void SetScrollBar()
        {
            scrBar.Minimum = -5;
            scrBar.Maximum = panelSign.Height;

            if (scrBar.Maximum <= scrBar.Minimum)
                scrBar.Visible = false;
        }

        private void scrBar_Scroll(object sender, ScrollEventArgs e)
        {
            panelSign.Top = -e.NewValue;
        }

    }
}
