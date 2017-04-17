using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.DataManager;
using ProWrite.UI.Controls.Common;
using DevExpress.XtraEditors;

namespace ProWrite.UI.Controls.Settings
{
    public partial class DataPassThroughDetail : XtraForm
    {
        private DataItem Current;
        public bool IsEdit;
        public bool IsRefresh;

        public DataPassThroughDetail()
        {
            InitializeComponent();
            Init();
        }

        public DataPassThroughDetail(DataItem dataItem)
        {
            if (dataItem != null)
            {
                IsEdit = true;
                Current = dataItem;
            }
            else
            {
                Current = new DataItem();
                IsEdit = false;
            }
            InitializeComponent();
            Init();
        }

        private void Init()
        {
            ddlSource.Properties.Items.AddRange(Enum.GetValues(typeof(DataSourceType)));
            if (IsEdit)
            {
                txtName.Text = Current.Name;
                txtNote.Text = Current.Note;
                chkPassThrough.Checked = Current.PassThrough;
                ddlSource.SelectedItem =Enum.Parse((typeof(DataSourceType)), Current.Source);
            }
        }

        private void Save()
        {
            Current.Name = txtName.Text;
            Current.PassThrough = chkPassThrough.Checked;
            Current.Source = ddlSource.SelectedItem.ToString();
            Current.Note = txtNote.Text.ToString();
            if (!IsEdit)
                DataGate.Project.DataSources.Add(Current);
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            Save();
            IsRefresh = true;
            Close();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
