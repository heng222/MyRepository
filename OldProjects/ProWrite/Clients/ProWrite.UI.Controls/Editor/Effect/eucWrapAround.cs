using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Shape;
using ProWrite.Entity.DES;
using ProWrite.Entity.DES.Effect;

namespace ProWrite.UI.Controls.Editor.Effect
{
    public partial class eucWrapAround : eucBase<EffectWrapAround>
    {
        public eucWrapAround()
        {
            InitializeComponent();
        }

        private void SetMaxNumRace()
        {
            //if (_effect.ShapeLayer == null)
            //    return;
            //var shape = _effect.ShapeLayer.Shape;
            if (this.ddlDirection.SelectedIndex == 0 || this.ddlDirection.SelectedIndex == 1)
            {
                this.tracRate.Properties.Maximum = ControlService.SignCombo.Current.Width - 1;
            }
            else
            {
                this.tracRate.Properties.Maximum = ControlService.SignCombo.Current.Height - 1;
            }

        }

        protected override void DoBind()
        {
            foreach (EffectWrapAround.DirectionWays item in Enum.GetValues(typeof(EffectWrapAround.DirectionWays)))
            {
                this.ddlDirection.Properties.Items.Add(item);
            }
            this.ddlBackColor.EditValue = _effect.BackColor;
            this.tracRate.Value = (int)(_effect.Rate);
            this.ddlDirection.SelectedIndex = (int)_effect.DirectionWay;
            this.spinSpacing.Text = _effect.Spacing.ToString();
            
            SetMaxNumRace();
            //this.tracRate.Properties.Maximum = ControlService.SignCombo.Current.Width - 1;
        }

        protected override void DoSave()
        {
            _effect.BackColor = (Color)this.ddlBackColor.EditValue;
            _effect.Rate = this.tracRate.Value;
            _effect.Spacing =Convert.ToInt32(spinSpacing.Value);
            if (this.ddlDirection.SelectedItem != null && Enum.IsDefined(typeof(EffectWrapAround.DirectionWays), this.ddlDirection.SelectedItem))
            {
                _effect.DirectionWay = (EffectWrapAround.DirectionWays)Enum.ToObject(typeof(EffectWrapAround.DirectionWays), this.ddlDirection.SelectedIndex);
            }
        }

        private void ddlDirection_SelectedIndexChanged(object sender, EventArgs e)
        {
            SetMaxNumRace();
            //this.tracRate.Properties.Maximum = 
        }
    }
}
