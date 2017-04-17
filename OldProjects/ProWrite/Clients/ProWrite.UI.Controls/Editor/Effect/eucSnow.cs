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
    public partial class eucSnow : eucBase<EffectSnow>
    {
        public eucSnow()
        {
            InitializeComponent();
        }

        protected override void DoBind()
        {
            this.ddlColor.EditValue = _effect.Color;
            this.tracRate.Value = (int)_effect.Rate;
            this.tracAmount.Value = (int)(_effect.Amount * 10);
        }

        protected override void DoSave()
        {
            _effect.Color = (Color)this.ddlColor.EditValue;
            _effect.Rate = this.tracRate.Value;
            _effect.Amount = (this.tracAmount.Value * 1.0f) / 10;
        }
    }
}
