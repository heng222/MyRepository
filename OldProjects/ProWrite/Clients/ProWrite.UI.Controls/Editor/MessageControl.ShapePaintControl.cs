using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using DevExpress.XtraTreeList.Nodes;
using DevExpress.XtraNavBar;

using System.Windows.Forms;
using ProWrite.Entity;
using ProWrite.Entity.Shape;
using ProWrite.Core;
using ProWrite.Entity.Dashboard;

namespace ProWrite.UI.Controls.Editor
{
    public partial class MessageControl 
    {
        //public SignInfo SignInfo
        //{
        //    get { return _sign; }
        //}

        private void SetShapePaintLayerSelected(object o, EventArgs<ShapeBase> e)
        {
            LayerControl frameLayer = GetLayerControl(e.First);
            if (frameLayer != null) frameLayer.IsSelected = true;
            //Invalidate();
        }
    }  
}
