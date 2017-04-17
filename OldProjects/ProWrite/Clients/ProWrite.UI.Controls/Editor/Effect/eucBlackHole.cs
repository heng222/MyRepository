using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.DES;
using ProWrite.Entity.DES.Effect;
using ProWrite.Entity.Shape;

namespace ProWrite.UI.Controls.Editor.Effect
{
    public partial class eucBlackHole : eucBase<EffectBlackHole>
    {
        public eucBlackHole()
        {
            InitializeComponent();
        }

        protected override void DoBind()
        {
            Point location = ConvertLocation(new Point(_effect.StartX, _effect.StartY), false);
            this.ddlStartX.Value = location.X;
            this.ddlStartY.Value = location.Y;
        }

        protected override void DoSave()
        {
            Point location = ConvertLocation(new Point((int)this.ddlStartX.Value, (int)this.ddlStartY.Value), true);
            _effect.StartX = location.X;
            _effect.StartY = location.Y;
        }

        private Point ConvertLocation(Point location,bool flag)
        {
            Point rc = new Point();
            int width =ControlService.SignCombo.Current.Width;
            int height=ControlService.SignCombo.Current.Height;
            if(flag)
            {
                rc.X = (location.X*384)/width;
                rc.Y = (location.Y * 288) / height;
            }
            else
            {
                rc.X = (location.X * width) / 384;
                rc.Y = (location.Y * height) / 288;
            }
            return rc;
        }
    }
}
