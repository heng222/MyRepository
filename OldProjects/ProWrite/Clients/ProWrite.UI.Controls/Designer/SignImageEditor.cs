using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing.Design;
using System.Windows.Forms.Design;
using ProWrite.Entity.Settings;
using System.Windows.Forms;
using ProWrite.Core;
using System.IO;
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls.Designer
{
    public class SignImageEditor : UITypeEditor
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
            SignTemplateInfo signTemplate = context.Instance as SignTemplateInfo;

            //ShapeVideo shape = context.Instance as ShapeVideo;

            using (OpenFileDialog dlg = new OpenFileDialog())
            {
                dlg.Filter = Constance.FileFilter.Image;
                if (dlg.ShowModalDialog() == DialogResult.OK)
                {
                    //if (btSignImage.Text.Length <= 0)
                    //    return;
                    //string path = AppDomain.CurrentDomain.BaseDirectory;
                    string path = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\ProWrite\\";
                    //要保存图片的最终路径
                    string urlString = path + "Image";
                    if (!Directory.Exists(urlString))
                    {
                        Directory.CreateDirectory(urlString); // File.Create(urlString);
                    }
                    string[] arrery = Directory.GetFiles(urlString);

                    string strImageFullName = dlg.FileName.Substring(dlg.FileName.LastIndexOf("\\") + 1);
                    //判断要上传的图片是否存在，如果存在则不需要再上传
                    foreach (string str in arrery)
                    {
                        if (str.Substring(str.LastIndexOf("\\") + 1) == strImageFullName)
                        {
                            //Current.Image = strImageFullName;
                            return strImageFullName;
                        }
                    }
                    DataGate.Upload(dlg.FileName);
                    //MessageControl.Current.LayerEditor.SetFrameLayerFocusByShapeId(shape.ID);
                    //FrameLayer.Current.Layer.Duration = Helper.GetMediaLength(dlg.FileName) / SysConsts.UNITS;
                    if (strImageFullName.Contains(".gif")
                || strImageFullName.Contains(".Gif")
                || strImageFullName.Contains(".GIF"))
                    {
                        strImageFullName = strImageFullName.Substring(0, strImageFullName.IndexOf(".")) + ".jpg";
                    }
                    return strImageFullName;
                }
            }
            return value;

        }
    }
}

