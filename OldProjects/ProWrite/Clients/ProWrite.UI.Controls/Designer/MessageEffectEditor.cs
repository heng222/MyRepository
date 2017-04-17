using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing.Design;
using ProWrite.Core;
using ProWrite.Entity.Library;
using System.Windows.Forms.Design;
using ProWrite.Entity.DES;
using System.Windows.Forms;
using ProWrite.Entity.Shape;
using System.ComponentModel;

namespace ProWrite.UI.Controls.Designer
{
    public abstract class MessageEffectEditor : UITypeEditor
    {
        private MessageInfo message = null;
        private ListBox lsbEffects = null;
        private LayerEffect effect = null;
        //private string emptyEffect = "[None]";
        private IWindowsFormsEditorService service = null;
        public MessageEffectEditor()
        {
            //FillList();
        }

        public override UITypeEditorEditStyle GetEditStyle(ITypeDescriptorContext context)
        {
            return UITypeEditorEditStyle.DropDown;
        }

        protected abstract EffectType Type
        {
            get;
        }
        public override object EditValue(System.ComponentModel.ITypeDescriptorContext context, IServiceProvider provider, object value)
        {
            if (context == null
                || context.Instance == null
                || provider == null)
                return value;
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
            if (lsbEffects.Items.Count == 0)
                FillList(effect);

            service.DropDownControl(lsbEffects);
            return effect;
        }

        private void FillList(LayerEffect effect)
        {

            lsbEffects.Items.Clear();
            ShapeLayer layer = null;
            lsbEffects.Items.Add(LayerEffect.EmptyEffect(layer, EffectType.Emphasis));
            EffectCategory group = GetEffectGroup(EffectType.Emphasis);
            

            if (group != null)
            {
                LayerEffect selected = null;
                foreach (LayerEffect item in group.Effects)
                {
                    if (item.Name!="WrapAround")
                    {
                        lsbEffects.Items.Add(item);
                        if (effect != null && item.Name == effect.Name)
                            selected = item;
                    }
                }

                //
                if (selected != null)
                    lsbEffects.SelectedItem = selected;
                else
                    lsbEffects.SelectedIndex = 0;
            }
        }

        private EffectCategory GetEffectGroup(EffectType type)
        {
            foreach (EffectCategory item in EffectCategory.EffectGroups)
                if (item.Name == type) return item;
            return null;
        }

        void lsbEffects_Click(object sender, EventArgs e)
        {
            service.CloseDropDown();
            if (lsbEffects.SelectedIndex == -1)
                return;
            //var type = effect.Type;
            effect = lsbEffects.SelectedItem as LayerEffect;
            //effect.Type = type;

            if (!effect.IsEmpty)
                effect.Duration = 2;

            //if (effect.IsEmpty)
            //{
            //    message.EmphasisEffect = LayerEffect.Empty.Copy();
            //}
            //else
            //{
            //    effect = lsbEffects.SelectedItem as LayerEffect;
            //    effect.Duration = 2;
            //}
        }

    }
    /// <summary>
    /// emphasis effect editor
    /// </summary>
    public class MessageEmphasisEffectEditor : MessageEffectEditor
    {
        protected override EffectType Type
        {
            get { return EffectType.Emphasis; }
        }
    }
}
