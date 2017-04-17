using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.UFE;

namespace ProWrite.UI.Controls.Dashboard
{
    public partial class ConnectionChooseForm : XtraForm
    {
        public ConnectionChooseForm()
        {
            InitializeComponent();

            //cmbTypes.Properties.Items.Add(new DevExpress.XtraEditors.Controls.RadioGroupItem(ConnectionMode.Mock,ConnectionMode.Mock.ToString()));
            cmbTypes.Properties.Items.Add(new DevExpress.XtraEditors.Controls.RadioGroupItem(ConnectionMode.Tcp, ConnectionMode.Tcp.ToString()));
            cmbTypes.Properties.Items.Add(new DevExpress.XtraEditors.Controls.RadioGroupItem(ConnectionMode.RS232, ConnectionMode.RS232.ToString()));
            cmbTypes.Properties.Items.Add(new DevExpress.XtraEditors.Controls.RadioGroupItem(ConnectionMode.Modem, ConnectionMode.Modem.ToString()));

            cmbTypes.SelectedIndex = 0;

            btnOK.Click += new EventHandler(btnOK_Click);
            btnCancel.Click += new EventHandler(btnCancel_Click);
        }

        void btnCancel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            Close();
        }

        void btnOK_Click(object sender, EventArgs e)
        {
            ConnectionMode mode = (ConnectionMode)cmbTypes.Properties.Items[cmbTypes.SelectedIndex].Value;
            ControlService.SignCombo.Current.ConnectionMode = mode;
            DialogResult = DialogResult.OK;
            Close();
        }
    }
}
