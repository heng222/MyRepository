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

namespace ProWrite.UI.Controls.Editor.Effect
{
    public partial class eucRain : eucBase<EffectRain>
    {
        public eucRain()
        {
            InitializeComponent();
        }

        protected override void DoBind()
        {
            this.ddlColor.EditValue = _effect.Color;
            this.tracAmount.Value = _effect.Amount;
            this.ddlAngle.Value = (decimal)_effect.Angle;
        }

        protected override void DoSave()
        {
            _effect.Color = (Color)this.ddlColor.EditValue;
            _effect.Amount = this.tracAmount.Value;
            _effect.Angle = (float)this.ddlAngle.Value;
        }
    }
}
