using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.DES.Effect;
using ProWrite.Entity.Shape;

namespace ProWrite.UI.Controls.Editor.Effect
{
    public partial class eucTravel : eucBase<EffectTravel>
    {
        public eucTravel()
        {
            InitializeComponent();
        }

        protected override void DoBind()
        {
            var directions = Enum.GetValues(typeof(EffectTravel.DirectionWay));
            foreach (EffectTravel.DirectionWay item in directions)
            {
                this.ddlDirection.Properties.Items.Add(item);
            }
            this.ddlDirection.SelectedItem = _effect.Direction;

            this.ddlSpacing.Value = (decimal)_effect.Spacing;
            this.ddlSpeed.Value = (decimal)_effect.Speed;
            this.rbtnCircular.EditValue = _effect.Circular;
            this.ddlDirection.SelectedItem = _effect.Direction;            
        }

        protected override void DoSave()
        {
            _effect.Spacing = (int)this.ddlSpacing.Value;
            _effect.Speed = (int)this.ddlSpeed.Value;

            _effect.Circular = bool.Parse(this.rbtnCircular.EditValue.ToString());

            if (_effect.ShapeLayer.Shape.Type == ProWrite.Core.ShapeType.Text)
            {
                var lable = _effect.ShapeLayer.Shape as ShapeLabel;

            }
            if (this.ddlDirection.SelectedItem != null)
            {
                _effect.Direction = (EffectTravel.DirectionWay)ddlDirection.SelectedItem;
            }
        }
    }
}
