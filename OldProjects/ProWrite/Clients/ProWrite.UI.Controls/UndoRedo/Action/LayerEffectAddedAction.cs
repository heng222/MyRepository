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
    public class LayerEffectAddedAction : UndoAction
    {
        private LayerEffect _newEffect;
        private LayerEffect _oldEffect;
        private LayerControl _layerControl;
        public LayerEffectAddedAction(LayerEffect effect)
        {
            _newEffect = effect;
            if (LayerControl.CurrentDrag != null)
                _layerControl = LayerControl.CurrentDrag;
            else
                _layerControl = LayerControl.Current;

            if (effect.Type == EffectType.Entry)
                _oldEffect = _layerControl.Layer.EntryEffect.Copy(false);
            else if (effect.Type == EffectType.Emphasis)
                _oldEffect = _layerControl.Layer.EmphasisEffect.Copy(false);
            else if (effect.Type == EffectType.Exit)
                _oldEffect = _layerControl.Layer.ExitEffect.Copy(false);
            else
                _oldEffect = LayerEffect.Empty;
            //_oldEffect.ShapeLayer = _layerControl.Layer;

            Name = string.Format("add a <{0}> Effect", effect.Type);
        }

        public override void Undo()
        {
            if (_oldEffect.IsEmpty)
            {
                _layerControl.RemoveEffect(_oldEffect.Type);
                ControlService.RefreshPropertyGrid(_layerControl.Layer);
                _layerControl.Invalidate();
            }
            else
            {
                _layerControl.AddEffect(_oldEffect);
            }
        }

        public override void Redo()
        {
            _layerControl.AddEffect(_newEffect);
            ControlService.RefreshPropertyGrid(_layerControl.Layer);
        }
    }
}
