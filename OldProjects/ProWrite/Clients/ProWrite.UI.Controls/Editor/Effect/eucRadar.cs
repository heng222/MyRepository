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
    public partial class eucRadar : eucBase<EffectRadar>
    {
        public eucRadar()
        {
            InitializeComponent();
        }

        protected override void DoBind()
        {
            foreach (EffectBijou.DirectionType item in Enum.GetValues(typeof(EffectBijou.DirectionType)))
            {
                this.ddlDirection.Properties.Items.Add(item);
            }
            this.ddlDirection.SelectedIndex = _effect.Direction;
            this.colorEdit.Color = _effect.EdgeColor;
            checkBox1.Checked = _effect.EdgeVisible == 1 ? true : false;
        }

        protected override void DoSave()
        {
            if (this.ddlDirection.SelectedItem != null && Enum.IsDefined(typeof(EffectBijou.DirectionType), this.ddlDirection.SelectedItem))
            {
                _effect.Direction = this.ddlDirection.SelectedIndex;
            }

            _effect.EdgeVisible = checkBox1.Checked ? 1 : 0;
            _effect.EdgeColor =(Color)colorEdit.EditValue;
        }
    }
}
