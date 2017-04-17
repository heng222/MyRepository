using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing.Design;
using System.Windows.Forms.Design;
using System.Windows.Forms;
using ProWrite.Core;
using ProWrite.Entity.Shape;
using ProWrite.UI.Controls.Common;
using ProWrite.DES;
using ProWrite.UI.Controls.Editor;

namespace ProWrite.UI.Controls.Designer
{
    /// <summary>
    /// Video editor class
    /// </summary>
    public class VideoEditor : UITypeEditor
    {
        private IWindowsFormsEditorService service = null;

        public override UITypeEditorEditStyle GetEditStyle(System.ComponentModel.ITypeDescriptorContext context)
        {
            return UITypeEditorEditStyle.Modal;
        }

        public override object EditValue(System.ComponentModel.ITypeDescriptorContext context, IServiceProvider provider, object value)
        {
            if (context == null
                || context.Instance == null
                || provider == null)
                return value;

            service = provider.GetService(typeof(IWindowsFormsEditorService)) as IWindowsFormsEditorService;

            if (service == null)
                return value;

            ShapeVideo shape = context.Instance as ShapeVideo;

            using (OpenFileDialog dlg = new OpenFileDialog())
            {
                dlg.Filter = Constance.FileFilter.Video;
                if (dlg.ShowModalDialog() == DialogResult.OK)
                {
                    MessageControl.Current.SetFrameLayerFocus(shape);
                    LayerControl.Current.Layer.EmphasisEffect.Duration = CommonHelper.GetMediaLength(dlg.FileName) / DESConsts.UNITS;
                    return dlg.FileName;
                }
            }
            return value;

        }
    }
}
