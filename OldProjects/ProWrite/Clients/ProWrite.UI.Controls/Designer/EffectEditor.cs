//---------------------------------------------------------------------
//
// File: EffectEditor.cs
//
// Description:
// The disigner control of Effect set
//
// Author: Terry
//
// Copyright (C) 2008 by ISoftstone Corporation.  All rights reserved.
// 
// Modify history:   
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing.Design;
using System.Windows.Forms;
using System.ComponentModel;
using System.Windows.Forms.Design;
using ProWrite.Entity.DES;
using ProWrite.Entity.Shape;
using ProWrite.Core;
using ProWrite.Entity.Library;
using ProWrite.UI.Controls.Editor;


namespace ProWrite.UI.Controls.Designer
{
    /// <summary>
    /// Effect editor
    /// </summary>
    public abstract class EffectEditor : UITypeEditor
    {
        private ShapeLayer layer = null;
        private MessageInfo message = null;
        private LayerEffect effect = null;
        private ListBox lsbEffects = null;

        private IWindowsFormsEditorService service = null;
        public override UITypeEditorEditStyle GetEditStyle(ITypeDescriptorContext context)
        {
            return UITypeEditorEditStyle.DropDown;
        }

        public override object EditValue(ITypeDescriptorContext context, IServiceProvider provider, object value)
        {
            if (context == null
                || context.Instance == null
                || provider == null)
                return value;

            layer = context.Instance as ShapeLayer;
            if (layer == null)
                message = context.Instance as MessageInfo;

            service = provider.GetService(typeof(IWindowsFormsEditorService)) as IWindowsFormsEditorService;

            if (service == null)
                return value;

            if (lsbEffects == null)
            {
                lsbEffects = new ListBox();
                lsbEffects.Width = 150;
                lsbEffects.Click += new EventHandler(lsbEffects_Click);
            }

            effect = value as LayerEffect;

            FillList(effect);

            service.DropDownControl(lsbEffects);

            return effect;
        }

        private EffectCategory GetEffectGroup(EffectType type)
        {
            foreach (EffectCategory item in EffectCategory.EffectGroups)
                if (item.Name == type) return item;
            return null;
        }

        protected abstract EffectType Type
        {
            get;
        }

        /// <summary>
        /// Fill list by effect data
        /// </summary>
        /// <param name="effect"></param>
        private void FillList(LayerEffect effect)
        {
            lsbEffects.Items.Clear();
            lsbEffects.Items.Add(LayerEffect.EmptyEffect(layer, Type));
            EffectCategory group = GetEffectGroup(Type);
            if (group != null)
            {
                LayerEffect selected = null;
                foreach (LayerEffect item in group.Effects)
                {
                    lsbEffects.Items.Add(item);
                    if (effect != null && item.Name == effect.Name)
                        selected = item;
                }
                if (selected != null)
                    lsbEffects.SelectedItem = selected;
                else
                    lsbEffects.SelectedIndex = 0;
            }
        }

        /// <summary>
        /// Effect select changed event
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void lsbEffects_Click(object sender, EventArgs e)
        {
            service.CloseDropDown();
            if (lsbEffects.SelectedIndex == -1)
                return;
            
            LayerEffect layereffect = lsbEffects.SelectedItem as LayerEffect;
            if (layereffect.Name.ToLower() == "none")
            {
                if (LayerControl.Current != null)
                    LayerControl.Current.RemoveEffect(effect.Type);
                lsbEffects.SelectedIndex = 0;
            }
            effect = lsbEffects.SelectedItem as LayerEffect;

            if (!effect.IsEmpty)
            {
                if (effect.Type != EffectType.Emphasis)
                    effect.Duration = 2;
                else
                {
                    if (LayerControl.Current != null)
                    {
                        LayerControl.Current.AddEffectFromDragDrop(effect);
                    }
                }
            }
            lsbEffects.Refresh();
        }
    }

    /// <summary>
    /// entry effect editor
    /// </summary>
    public class EntryEffectEditor : EffectEditor
    {
        protected override EffectType Type
        {
            get { return EffectType.Entry; }
        }
    }

    /// <summary>
    /// emphasis effect editor
    /// </summary>
    public class EmphasisEffectEditor : EffectEditor
    {
        protected override EffectType Type
        {
            get { return EffectType.Emphasis; }
        }
    }

    /// <summary>
    /// exit effect editor
    /// </summary>
    public class ExitEffectEditor : EffectEditor
    {
        protected override EffectType Type
        {
            get { return EffectType.Exit; }
        }
    }
}
