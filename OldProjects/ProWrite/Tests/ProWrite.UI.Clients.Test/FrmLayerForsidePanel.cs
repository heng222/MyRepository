using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ProWrite.UI.Controls.Editor.Layers;
using ProWrite.Entity.Shape;

namespace ProWrite.UI.Clients.Test
{
    public partial class FrmLayerForsidePanel : Form
    {
        private LayerForsidePanel ctrl;
        public FrmLayerForsidePanel()
        {
            InitializeComponent();

            ShapeLayer layer = new ShapeLayer(new ShapeLabel());
            layer.Name = "How are you";
            ctrl = new LayerForsidePanel(layer);
            this.Controls.Add(ctrl);
        }
    }
}