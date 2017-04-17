using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using ProWrite.Core;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Live;
using ProWrite.Entity.Library;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public class ButtonGraphicEventArgs : EventArgs
    {
        SignSettingControl _sign = new SignSettingControl();

        public SignSettingControl Sign
        {
            set { _sign = value; }
            get { return _sign; }
        }
    }

    public partial class SignSettingControl : UserControl
    {
        public event EventHandler<ButtonGraphicEventArgs> OnButtonGraphicCheckChanged = null;

        public SignSettingControl()
        {
            InitializeComponent();

            if (!DesignMode)
                Init();
        }

        private void Init()
        {
            _sign.CreateTime = DateTime.Now;
            _sign.Id = Guid.NewGuid().ToString();
            
            string[] queueCtlType = Enum.GetNames(typeof(QueueControlType));
            string[] mediaCtlType = Enum.GetNames(typeof(MediaControlType));

            foreach (string str in mediaCtlType)
            {
                MediaControlType type = (MediaControlType)Enum.Parse(typeof(MediaControlType), str, true);

                switch (type)
                {
                    case MediaControlType.PlayNext:
                        this.rdoMediaControl.Properties.Items.Add(new DevExpress.XtraEditors.Controls.RadioGroupItem(str,"Play Next"));
                        break;

                    case MediaControlType.PlayNormal:
                        this.rdoMediaControl.Properties.Items.Add(new DevExpress.XtraEditors.Controls.RadioGroupItem(str, "Play Normal"));
                        break;

                    case MediaControlType.PlayNow:
                        this.rdoMediaControl.Properties.Items.Add(new DevExpress.XtraEditors.Controls.RadioGroupItem(str, "Play Now"));
                        break;

                    case MediaControlType.SendToAutoQueue:
                        this.rdoMediaControl.Properties.Items.Add(new DevExpress.XtraEditors.Controls.RadioGroupItem(str, "Send To Auto-Queue"));
                        break;
                }
            }

            foreach (string str in queueCtlType)
            {
                QueueControlType type = (QueueControlType)Enum.Parse(typeof(QueueControlType), str, true);

                switch (type)
                {
                    case QueueControlType.AutoQueueOff:
                        chkQueueControl.Items.Add(str, "Auto-Queue Off");
                        break;

                    case QueueControlType.AutoQueueOn:
                        chkQueueControl.Items.Add(str, "Auto-Queue On");
                        break;

                    case QueueControlType.ClearAll:
                        chkQueueControl.Items.Add(str, "Clear All");
                        break;

                    case QueueControlType.ClearQueue:
                        chkQueueControl.Items.Add(str, "Clear Queue");
                        break;

                    case QueueControlType.EjectMessage:
                        chkQueueControl.Items.Add(str, "Eject Message");
                        break;

                    case QueueControlType.Pause:
                        chkQueueControl.Items.Add(str, "Pause");
                        break;

                    case QueueControlType.Resume:
                        chkQueueControl.Items.Add(str, "Resume");
                        break;
                }
            }

        }

        private LiveSign _sign = new LiveSign();
        public LiveSign LiveSign
        {
            set
            {
                _sign = value;
                SetSign();
            }
            get
            {
                GetSign();
                return _sign;
            }
        }

        public string SignName
        {
            set
            {
                lblSignName.Text = value;
            }
            get
            {
                return lblSignName.Text;
            }
        }

        public bool SignEnable
        {
            set
            {
                chkSignEnable.Checked = value;
                SetSignEnable();
            }
            get
            {
                return chkSignEnable.Checked;
            }
        }

        private LiveMessageItem _messageItem = new LiveMessageItem();
        public LiveMessageItem LiveMessage
        {
            set
            {
                _messageItem = value;
                if (_messageItem != null)
                {
                    txtMedia.Text = _messageItem.Name;
                    picMedia.Image = _messageItem.Image;
                }
            }
            get
            {
                return _messageItem;
            }
        }

        private DashboardItem _item;
        public DashboardItem SignItem
        {
            set
            {
                _item = value;
            }
            get
            {
                return _item;
            }
        }

        private void chkSignEnable_CheckedChanged(object sender, EventArgs e)
        {
            SetSignEnable();
        }

        private void SetSignEnable()
        {
            panelControl1.Enabled = chkSignEnable.Checked;
            panelControl2.Enabled = chkSignEnable.Checked;
            panelControl3.Enabled = chkSignEnable.Checked;
        }

        private void btnLoadMedia_Click(object sender, EventArgs e)
        {
            HotButtonMediaForm frmHotButtonMedia = null;

            try
            {
                frmHotButtonMedia = new HotButtonMediaForm();

                if (frmHotButtonMedia.ShowDialog() == DialogResult.OK)
                {
                    MemoryLibraryItem memItem = frmHotButtonMedia.Media;
                    LiveMessage = CreateLiveMsgItem(memItem);
                    chkButtonGraphic_CheckedChanged(sender, e);
                }
            }
            finally
            {
                if (frmHotButtonMedia != null)
                    frmHotButtonMedia.Dispose();
            }
        }

        private LiveMessageItem CreateLiveMsgItem(MemoryLibraryItem item)
        {
            LiveMessageItem msgItem = new LiveMessageItem();
            msgItem.Name = item.Name;
            msgItem.Id = item.Id;
            msgItem.Target = item;
            return msgItem;
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            LiveMessage = null;
            txtMedia.Text = string.Empty;
            picMedia.Image = null;
            chkButtonGraphic_CheckedChanged(sender, e);
        }

        private void rdoMediaControl_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetLogicDisplayState();
        }

        private void chkQueueControl_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetLogicDisplayState();
        }

        private void SetLogicDisplayState()
        {
            if (    rdoMediaControl.SelectedIndex == 0
                ||  rdoMediaControl.SelectedIndex == 1)
            {
                chkQueueControl.Items[0].Enabled = false;
            }
        }

        private void GetSign()
        {
            _sign.Name = SignName;
            _sign.Sign = SignItem;
            _sign.Message = LiveMessage;
            _sign.ButtonGraphic = chkButtonGraphic.Checked;
            
            List<QueueControlType> lstQueueCtlType = new List<QueueControlType>();
            for(int i = 0; i < chkQueueControl.Items.Count; i++)
            {
                if (chkQueueControl.Items[i].CheckState == CheckState.Checked)
                {
                    QueueControlType queueCtlType = (QueueControlType)Enum.Parse(typeof(QueueControlType), chkQueueControl.Items[i].Value.ToString(), true);
                    lstQueueCtlType.Add(queueCtlType);
                }
            }
            _sign.QueueControl = lstQueueCtlType.ToArray();

            if (rdoMediaControl.SelectedIndex >= 0)
            {
                string mediaType = rdoMediaControl.Properties.Items[rdoMediaControl.SelectedIndex].Value.ToString();
                MediaControlType mediaCtlType = (MediaControlType)Enum.Parse(typeof(MediaControlType), mediaType, true);
                _sign.MediaControl = mediaCtlType;
            }
        }

        private void SetSign()
        {
            this.chkSignEnable.Checked = true;
            SignName = _sign.Name;
            SignItem = _sign.Sign;
            LiveMessage = _sign.Message;
            chkButtonGraphic.Checked = _sign.ButtonGraphic;

            for (int queueCtlIndex = 0; queueCtlIndex < _sign.QueueControl.Length; queueCtlIndex++)
            {
                for (int i = 0; i < chkQueueControl.Items.Count; i++)
                {
                    if (_sign.QueueControl[queueCtlIndex].ToString() == chkQueueControl.Items[i].Value.ToString())
                    {
                        chkQueueControl.Items[i].CheckState = CheckState.Checked;
                        break;
                    }
                }
            }

            for (int i = 0; i < rdoMediaControl.Properties.Items.Count; i++)
            {
                if (rdoMediaControl.Properties.Items[i].Value.ToString() == _sign.MediaControl.ToString())
                {
                    rdoMediaControl.SelectedIndex = i;
                    break;
                }
            }

            SetLogicDisplayState();
        }

        private void chkButtonGraphic_CheckedChanged(object sender, System.EventArgs e)
        {
            if (OnButtonGraphicCheckChanged != null)
            {
                ButtonGraphicEventArgs args = new ButtonGraphicEventArgs();
                args.Sign = this;
                OnButtonGraphicCheckChanged(sender, args);
            }
        }

        public bool ButtonGraphic
        {
            set
            {
                chkButtonGraphic.Checked = value;
            }
            get
            {
                return chkButtonGraphic.Checked;
            }
        }


    }
}
