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
    public partial class eucSparkle : eucBase<EffectSparkle>
    {
        public eucSparkle()
        {
            InitializeComponent();
        }

        protected override void DoBind()
        {
            this.ddlColor.EditValue = _effect.SparkleColor;
            this.tracAmount.Value = _effect.Amount;
            this.ddlSize.Value = _effect.Size;

        }

        protected override void DoSave()
        {
            _effect.SparkleColor = (Color)this.ddlColor.EditValue;
            _effect.Size = (int)this.ddlSize.Value;
            _effect.Amount = this.tracAmount.Value;

        }
    }
}
