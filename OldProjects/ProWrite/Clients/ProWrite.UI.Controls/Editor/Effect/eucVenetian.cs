using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.DES.Effect;

namespace ProWrite.UI.Controls.Editor.Effect
{
    public partial class eucVenetian : eucBase<EffectVenetian>
    {
        public eucVenetian()
        {
            InitializeComponent();
            this.spBlindWidth.Properties.MaxValue = ControlService.SignCombo.Current.Width / 2;
            this.spBlindWidth.Properties.MinValue = 4;
        }

        protected override void DoBind()
        {
            spBlindWidth.Value = _effect.BlindWidth;
            var directions = Enum.GetValues(typeof(ProWrite.Entity.DES.Effect.EffectVenetian.DirectionWays));
            foreach (ProWrite.Entity.DES.Effect.EffectVenetian.DirectionWays item in directions)
            {
                this.ddlDirection.Properties.Items.Add(item);
            }
            this.ddlDirection.SelectedItem = _effect.Direction;
        }

        protected override void DoSave()
        {
            _effect.BlindWidth= (int)spBlindWidth.Value;

            if (this.ddlDirection.SelectedItem != null)
            {
                _effect.Direction = (ProWrite.Entity.DES.Effect.EffectVenetian.DirectionWays)ddlDirection.SelectedItem;
            }
        }
    }
}
