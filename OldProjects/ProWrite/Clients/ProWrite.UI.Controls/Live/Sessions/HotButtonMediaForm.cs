using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;

using ProWrite.UI.Controls.Library;
using ProWrite.Entity.Library;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public partial class HotButtonMediaForm : DevExpress.XtraEditors.XtraForm
    {
        private LibraryTreeControl _libTree;

        public HotButtonMediaForm()
        {
            InitializeComponent();

            if (!DesignMode)
            {
                InitMsgTree();
            }
        }

        /// <summary>
        /// 
        /// </summary>
        private void InitMsgTree()
        {
            _libTree = new LibraryTreeControl(false);
            _libTree.OptionsSelection.MultiSelect = true;
            _libTree.ContextMenuStrip = null;
            _libTree.Dock = DockStyle.Fill;
            _libTree.Type = ProWrite.Core.LibraryType.Message | ProWrite.Core.LibraryType.Playlist | ProWrite.Core.LibraryType.TimeSliceGroup;
            panelMedia.Controls.Add(_libTree);
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            if (_libTree.Selection.Count > 0)
            {
                this.DialogResult = DialogResult.OK;
            }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
        }

        public MemoryLibraryItem Media
        {
            get
            {
                return _libTree.Selection[0].Tag as MemoryLibraryItem;
            }
        }

    }
}