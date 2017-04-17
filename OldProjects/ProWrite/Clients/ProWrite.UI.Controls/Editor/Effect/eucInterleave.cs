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
    public partial class eucInterleave : eucBase<EffectInterleave>
    {
        int height = ControlService.SignCombo.Current.Height;
        int width = ControlService.SignCombo.Current.Width;
        public eucInterleave()
        {
            InitializeComponent();
        }

        private void radLines_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (radLines.SelectedIndex == 0)
                this.ddlThickness.Properties.MaxValue = width;
            else
                this.ddlThickness.Properties.MaxValue = height;
        }

        protected override void DoBind()
        {
            foreach (EffectInterleave.DirectionWays item in Enum.GetValues(typeof(EffectInterleave.DirectionWays)))
            {
                this.ddlDirection.Properties.Items.Add(item);
            }
            this.radLines.EditValue = !_effect.Lines;
            this.ddlThickness.Value = _effect.Thickness;
            this.ddlDirection.SelectedIndex = (int)_effect.DirectionWay;
        }

        protected override void DoSave()
        {
            _effect.Thickness = (int)this.ddlThickness.Value;
            _effect.Lines = !bool.Parse(this.radLines.EditValue.ToString());
            if (this.ddlDirection.SelectedItem != null && Enum.IsDefined(typeof(EffectInterleave.DirectionWays), this.ddlDirection.SelectedItem))
            {
                _effect.DirectionWay = (EffectInterleave.DirectionWays)Enum.ToObject(typeof(EffectInterleave.DirectionWays), this.ddlDirection.SelectedIndex);
            }
        }
    }
}
