using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices.ComTypes;
using DevExpress.XtraEditors;

using ProWrite.Entity.Live;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public partial class HotKeyAssignForm : DevExpress.XtraEditors.XtraForm
    {
        public HotKeyAssignForm()
        {
            InitializeComponent();

            if (!DesignMode)
                Init();
        }

        private void Init()
        {
            string[] mainKey = Enum.GetNames(typeof(MainHotKey));

            cmbMainHotKey.Properties.BeginUpdate();
            cmbMainHotKey.Properties.Items.AddRange(mainKey);
            cmbMainHotKey.Properties.EndUpdate();

            string[] subKey = Enum.GetNames(typeof(SubHotKey));

            cmbSubHotKey.Properties.BeginUpdate();
            cmbSubHotKey.Properties.Items.AddRange(subKey);
            cmbSubHotKey.Properties.EndUpdate();

            if (cmbMainHotKey.Properties.Items.Count > 0)
                cmbMainHotKey.SelectedIndex = 0;

            if (cmbSubHotKey.Properties.Items.Count > 0)
                cmbSubHotKey.SelectedIndex = 0;
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            _mainHotKey = (MainHotKey)Enum.Parse(typeof(MainHotKey), cmbMainHotKey.Text, true);
            _subHotKey = (SubHotKey)Enum.Parse(typeof(SubHotKey), cmbSubHotKey.Text, true);
        }

        private MainHotKey _mainHotKey;
        public MainHotKey MainHotKey
        {
            set
            {
                _mainHotKey = value;
            }
            get
            {
                return _mainHotKey;
            }
        }

        private SubHotKey _subHotKey;
        public SubHotKey SubHotKey
        {
            set
            {
                _subHotKey = value;
            }
            get
            {
                return _subHotKey;
            }
        }

    }
}