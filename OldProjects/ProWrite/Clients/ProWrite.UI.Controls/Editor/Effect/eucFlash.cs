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
using ProWrite.UI.Controls.Common;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Editor.Effect
{
    public partial class eucFlash : eucBase<EffectFlash>
    {
        public eucFlash()
        {
            InitializeComponent();
        }

        protected override void DoBind()
        {
            this.ddlColor.Enabled = false;
            this.ddlColor.EditValue = Color.Transparent;
            foreach (FlashStyle item in Enum.GetValues(typeof(FlashStyle)))
            {
                this.ddlFlashStyle.Properties.Items.Add(item);
            }
            this.ddlOffTime.Value = (decimal)_effect.OffTime;
            this.ddlOnTime.Value = (decimal)_effect.OnTime;
            this.ddlWED.Value = (decimal)_effect.WED;
            this.ddlFlashStyle.SelectedItem = _effect.Style;

            if (_effect.ShapeLayer != null)
            {
                var shape = _effect.ShapeLayer.Shape;
                var shapeType = shape.Type;
                if (shapeType == ShapeType.Text || shapeType == ShapeType.Time || shapeType == ShapeType.Temperature || shapeType == ShapeType.DynamicText)
                {
                    this.ddlColor.Enabled = true;
                    this.ddlColor.EditValue = (shape as ShapeTextBase).BackColor;
                }
            }
            //else
            //{
            //    this.ddlFlashStyle.Properties.Items.Remove(EffectFlash.FlashStyle.RandomFlash);
            //}
            this.ddlWED.Visible = false;
            this.ddlColor.Visible = false;
        }

        protected override void DoSave()
        {
            _effect.BackColor = (Color)this.ddlColor.EditValue;
            _effect.OffTime = (int)this.ddlOffTime.Value;
            _effect.OnTime = (int)this.ddlOnTime.Value;
            _effect.WED = (int)this.ddlWED.Value;
            if (this.ddlFlashStyle.SelectedItem != null)
            {
                _effect.Style = (FlashStyle)ddlFlashStyle.SelectedItem;
            }
        }

    }
}
