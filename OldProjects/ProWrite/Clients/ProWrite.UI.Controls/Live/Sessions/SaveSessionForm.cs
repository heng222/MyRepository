using System;
using System.Windows.Forms;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public partial class SaveSessionForm : Form
    {

        public SaveSessionForm()
        {
            InitializeComponent();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            SessionName = txtSessionName.Text;
        }

        public string _sessionName = string.Empty;
        public string SessionName
        {
            get { return _sessionName; }
            set { _sessionName = value; }
        }
        
    }
}
