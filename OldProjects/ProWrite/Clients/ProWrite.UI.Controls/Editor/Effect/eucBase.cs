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
using ProWrite.Core;
using ProWrite.Entity.Shape;

namespace ProWrite.UI.Controls.Editor.Effect
{
    public partial class eucBase : UserControl
    {

        public eucBase()
        {
            InitializeComponent();
        }

        public LayerEffect Effect { get; protected set; }

        public virtual void Bind(LayerEffect effect) { }

        public virtual void Save() { }
      
        public virtual void DoDispose()
        {
        }
    }

    public class eucBase<TEffect> : eucBase
        where TEffect : LayerEffect, new()
    {
        protected TEffect _effect = null;

        public eucBase()
        {
            Effect = new TEffect();
        }

        public new TEffect Effect
        {
            get
            {
                return _effect;
            }
            protected set
            {
                _effect = (TEffect)value;
                base.Effect = value;
            }
        }

        public override void Bind(LayerEffect effect)
        {
            Effect.FromTo(effect);

            DoBind();
        }

        public override void Save()
        {
            if (_effect != null)
            {
                DoSave();
                MessageControl.Current.ChangedService.MarkChanged();
            }
        }

        protected virtual void DoSave() { }

        protected virtual void DoBind() { }
    }
}
