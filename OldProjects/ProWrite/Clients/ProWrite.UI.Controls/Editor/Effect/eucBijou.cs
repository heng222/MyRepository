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
using ProWrite.UI.Controls.Common;
using ProWrite.Entity.Shape;

namespace ProWrite.UI.Controls.Editor.Effect
{
    public partial class eucBijou :eucBase<EffectBijou>
    {
        
        public eucBijou()
        {
            InitializeComponent();
        }

        private void SetMaxNumRace()
        {
            this.tracRate.Properties.Maximum =
                (int)(this.ddlLampLength.Value + this.ddlGapLength.Value)/2;
            this.ddlLampHeight.Properties.MaxValue = ControlService.SignCombo.Current.Width / 2;
        }


        protected override void DoBind()
        {
            foreach (EffectBijou.DirectionType item in Enum.GetValues(typeof(EffectBijou.DirectionType)))
            {
                this.ddlDirection.Properties.Items.Add(item);
            }
            this.ddlColor.EditValue = _effect.Color;
            this.colorGap.EditValue = _effect.GapColor;
            this.tracRate.Value = _effect.Rate;
            this.ddlLampHeight.Value = (decimal)_effect.LampHeight;
            this.ddlLampLength.Value = (decimal)_effect.LampLength;
            this.ddlGapLength.Value = (decimal)_effect.GapLength;
            this.radCornersOn.EditValue = _effect.CornersOn;
            this.ddlDirection.SelectedIndex = (int)_effect.DirectionWay;


            // Determine the maximum of rate.
            SetMaxNumRace();
        }

        protected override void DoSave()
        {
            _effect.Color = (Color)this.ddlColor.EditValue;
            _effect.GapColor = (Color)this.colorGap.EditValue;
            _effect.Rate = this.tracRate.Value;
            _effect.LampHeight = (int)this.ddlLampHeight.Value;
            _effect.LampLength = (int)this.ddlLampLength.Value;
            _effect.GapLength = (int)this.ddlGapLength.Value;
            _effect.CornersOn = bool.Parse(this.radCornersOn.EditValue.ToString());
            if (this.ddlDirection.SelectedItem != null && Enum.IsDefined(typeof(EffectBijou.DirectionType), this.ddlDirection.SelectedItem))
            {
                _effect.DirectionWay = (EffectBijou.DirectionType)Enum.ToObject(typeof(EffectBijou.DirectionType), this.ddlDirection.SelectedIndex);
            }
            //base.Effect = _effect;
            //base.Propertys = _effect.ToPropertyArray();
        }

        private void ddlLampLength_ValueChanged(object sender, EventArgs e)
        {
            SetMaxNumRace();
        }

        private void ddlGapLength_ValueChanged(object sender, EventArgs e)
        {
            SetMaxNumRace();
        }
    }
}
