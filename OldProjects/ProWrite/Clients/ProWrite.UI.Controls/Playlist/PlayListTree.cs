using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Library;
using ProWrite.UI.Controls.Common;
using ProWrite.Core;
using ProWrite.Entity.DES;
using ProWrite.Entity.Shape;

namespace ProWrite.UI.Controls.Playlist
{
    public partial class PlayListTree :ControlPanel<PlaylistInfo, PlayListTree>
    {

        public PlayListTree()
        {
            InitializeComponent();
        }


        private void PopulateTree()
        {
            //treeList.DataSource=
        }

        protected override void DoPopulate()
        {
            base.DoPopulate();
        }

        public override void LoadModelInfo()
        {
            _model.Clear();
            //foreach (PlaylistItemControl item in dragDropControl.Controls)
            //{
            //    if (_model.Image == null)
            //        _model.Image = item.PlaylistItem.Target.Image;
            //    _model.AddLast(item.PlaylistItem);
            //}
        }

        void btnDelete_DragLeave(object sender, System.EventArgs e)
        {
            
        }

        void btnDelete_DragDrop(object sender, System.Windows.Forms.DragEventArgs e)
        {
           
        }

        void btnDelete_Click(object sender, System.EventArgs e)
        {
            
        }

        void btnDelete_DragEnter(object sender, System.Windows.Forms.DragEventArgs e)
        {
            
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
             
        }

    }
}
