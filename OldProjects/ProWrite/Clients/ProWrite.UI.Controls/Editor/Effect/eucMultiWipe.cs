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
    public partial class eucMultiWipe : eucBase<EffectMultiWipe>// UserControl
    {
        public eucMultiWipe()
        {
            InitializeComponent();
            this.spHorizontalWipes.Properties.MaxValue = ControlService.SignCombo.Current.Width;
            this.spVerticalWipes.Properties.MaxValue = ControlService.SignCombo.Current.Height;
        }

        protected override void DoBind()
        {
            spHorizontalWipes.Value = _effect.HorizontalWipes;
            spVerticalWipes.Value = _effect.VerticalWipes;

        }

        protected override void DoSave()
        {
            _effect.HorizontalWipes = (int)spHorizontalWipes.Value;
            _effect.VerticalWipes = (int)spVerticalWipes.Value;
        }
    }
}
