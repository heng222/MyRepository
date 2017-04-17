//---------------------------------------------------------------------
//
// File: EffectSetForm.cs
//
// Description:
// Set Effect Propertys
//
// Author: Michael
//
// Date:2008-11-14
//
// Modify history:
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.DES;
using DevExpress.XtraEditors;
using ProWrite.UI.Controls.Editor.Effect;
using ProWrite.Entity.Shape;
using ProWrite.Entity.DES.Effect;
using ProWrite.Core;
using System.Reflection;

namespace ProWrite.UI.Controls.Editor.Layers
{
    public partial class EffectSetForm : XtraForm
    {
        private LayerEffect layerEffect = null;
        private eucBase uc;

        public LayerEffect Effect
        {
            get { return layerEffect;}
        }
        public EffectSetForm(LayerEffect efc)
        {
            layerEffect = efc;
            InitializeComponent();
            Text = efc.Name + " Effect Set";
        }

        private void EffectSetForm_Load(object sender, EventArgs e)
        {
            LoadUC();
        }

        private void EffectSetForm_FormClosed(object sender, FormClosedEventArgs e)
        {
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            if (uc != null)
            {
                uc.Save();
                this.layerEffect.FromTo(uc.Effect);
                //if (layerEffect.ShapeLayer == null && layerEffect.Type == EffectType.Emphasis)
                //    MessageControl.Current.Model.EmphasisEffect = this.layerEffect;
            }
            this.Close();
        }

        private void LoadUC()
        {
            uc = EffectControlFactory.Create(layerEffect.Name);

           if (uc == null)
           {
               uc = new eucNone();
               this.btnSave.Enabled = false;
           }

           uc.Bind(layerEffect);
           this.pnlUC.Controls.Add(uc);
        }
    }

    public abstract class EffectControlFactory
    {
        private static readonly Dictionary<string, Func<eucBase>> _factories = new Dictionary<string,Func<eucBase>>();
        static EffectControlFactory()
        {
            _factories[EffectId.Bijou.Name] = () => new eucBijou();
            _factories[EffectId.BlackHole.Name] = () => new eucBlackHole();
            _factories[EffectId.Bounce.Name] = () => new eucNone();
            _factories[EffectId.Coalesce.Name] = () => new eucCoalesce();
            _factories[EffectId.Filter.Name] = () => new eucFilter();
            _factories[EffectId.Flash.Name] = () => new eucFlash();
            _factories[EffectId.Interleave.Name] = () => new eucInterleave();
            _factories[EffectId.Line.Name] = () => new eucLine();
            _factories[EffectId.MultiWipe.Name] = () => new eucMultiWipe();
            _factories[EffectId.Rain.Name] = () => new eucRain();
            _factories[EffectId.Radar.Name] = () => new eucRadar();
            _factories[EffectId.Slide.Name] = () => new eucSlide();
            _factories[EffectId.Snow.Name] = () => new eucSnow();
            _factories[EffectId.Sparkle.Name] = () => new eucSparkle();
            _factories[EffectId.Travel.Name] = () => new eucTravel();
            _factories[EffectId.Venetian.Name] = () => new eucVenetian();
            _factories[EffectId.Wipe.Name] = () => new eucWipe();
            _factories[EffectId.WrapAround.Name] = () => new eucWrapAround();
        }

        public static eucBase Create(string effectName)
        {
            Func<eucBase> f = null;
            if (_factories.TryGetValue(effectName, out f))
                return f();

            return null;
        }
    }
}
