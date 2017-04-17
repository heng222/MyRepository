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
    public partial class eucFilter : eucBase<EffectFilter>
    {
        public eucFilter()
        {
            InitializeComponent();
        }

        protected override void DoBind()
        {
            this.ddlWidth.Value = _effect.Width;
            this.ddlHeight.Value = _effect.Spacing;
        }

        protected override void DoSave()
        {
            _effect.Width = (int)this.ddlWidth.Value;
            _effect.Spacing = (int)this.ddlHeight.Value;
        }
    }
}
