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
    public partial class eucCoalesce : eucBase<EffectCoalesce>
    {
        public eucCoalesce()
        {
            InitializeComponent();
        }
        protected override void DoBind()
        {
            spHeight.Value = _effect.EntityHeight;
            spWidth.Value = _effect.EntityWidth;
        }

        protected override void DoSave()
        {
            _effect.EntityHeight = (int)spHeight.Value;
            _effect.EntityWidth = (int)spWidth.Value;
        }
    }
}
