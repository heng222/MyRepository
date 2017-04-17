using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Shape;
using ProWrite.UI.Controls.Editor;

namespace ProWrite.UI.Clients.Test
{
    public partial class FrmLayerTest : Form
    {
        private MessageControl layerContainer;
        public FrmLayerTest()
        {
            InitializeComponent();
            layerContainer = new MessageControl();
            layerContainer.Dock = DockStyle.Fill;
            pnLayers.Controls.Add(layerContainer);
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            ShapeLabel shape = new ShapeLabel();
            ShapeLayer layer = new ShapeLayer(shape);
            //layerContainer.AddLayer(layer);
            //pnLayers.Controls.Add(frameLayer);
            //pnLayers.Controls.SetChildIndex(frameLayer, 0);
            //propertyGrid1.SelectedObject = layer;
        }
    }
}