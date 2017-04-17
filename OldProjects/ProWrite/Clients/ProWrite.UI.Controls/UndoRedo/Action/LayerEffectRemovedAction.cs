using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Entity.Shape;
using ProWrite.UI.Controls.Editor;
using ProWrite.Core;
using ProWrite.Entity.DES;

namespace ProWrite.UI.Controls.UndoRedo.Action
{
    public class LayerEffectRemovedAction : UndoAction
    {
        private LayerEffect _removedEffect;
        //private LayerEffect _oldEffect;
        private LayerControl _layerControl;
        public LayerEffectRemovedAction(LayerControl frameLayer, LayerEffect effect)
        {
            _removedEffect = effect;
            _layerControl = frameLayer;

            Name = string.Format("remove a <{0}> Effect", effect.Type);
        }

        public override void Undo()
        {
            _layerControl.AddEffect(_removedEffect);
            ControlService.RefreshPropertyGrid(_layerControl.Layer);
        }

        public override void Redo()
        {
            if (_removedEffect.Type == EffectType.Entry)
                _layerControl.EntryEffect.Name = null;
            else if (_removedEffect.Type == EffectType.Emphasis || _removedEffect.Type == EffectType.None)
                _layerControl.EmphasisEffect.Name = null;
            else if (_removedEffect.Type == EffectType.Exit)
                _layerControl.ExitEffect.Name = null;

            var type = _removedEffect.Type;
            _layerControl.RemoveEffect(type);

            ControlService.RefreshPropertyGrid(_layerControl.Layer);
        }
    }
}
