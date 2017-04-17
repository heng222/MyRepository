using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using DevExpress.XtraEditors.DXErrorProvider;
using ProWrite.UI.Controls.Common;
using ProWrite.Entity.Settings;
using ProWrite.Resources;

namespace ProWrite.UI.Controls
{
    public partial class InputDialog : DialogForm
    {
        private string _info = string.Empty;
        private InputDialog(string caption)
        {
            InitializeComponent();
            if (caption == "Enter Password")
            {
                txtInfo.Properties.PasswordChar = '*';
                btnSave.Text = "Ok";
            }
   
            if (!string.IsNullOrEmpty(caption))
                this.Text = caption;// 
            dxValidationProvider1.ValidationMode = ValidationMode.Auto;
        }

        public static DialogResult Result;
        public static string GetInputValue(string caption)
        {
            using (InputDialog dlg = new InputDialog(caption))
            {
                dlg.Controls[2].Text = "Ok";
                DialogResult result = dlg.ShowModalDialog();
                Result = result;
                if (result == DialogResult.OK)
                {
                    return dlg.Info;
                }
                return null;
            }
        }

        public static string GetInputValue(string caption, string text)
        {
            using (InputDialog dlg = new InputDialog(caption))
            {                
                dlg.Controls[0].Text = text;
                
                DialogResult result = dlg.ShowModalDialog();
                Result = result;
                if (result == DialogResult.OK)
                {
                    if (dlg.Info.Trim() == "")
                        MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.MessageLayerNameNotNull));
                    return dlg.Info;
                }
                return null;
            }
        }



        private string Info
        {
            get { return _info; }
        }

        protected override void OnOk()
        {
            base.OnOk();
            _info = txtInfo.Text.Trim();
            if (_info.Length > 64)
            {
                MsgBox.Warning("Sorry,Your name is too long");
                return;
            }
            bool isTemplate = this.Text == "New Template";
            bool isLayerChangeName = this.Text == Resource.GetString(Resource.Strings.MessageChangeLayerName);
            if (_info == "")
            {
                if (isTemplate)
                {
                    MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.TemplateEmpty));
                    return;
                }
                else if (isLayerChangeName)
                {
                    MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.MessageLayerNameNotNull));
                    return;
                }
                else if (this.Text != "Enter Password")
                //    MsgBox.Warning("Sorry,the password can't be empty.");
                //else
                {
                    MsgBox.Warning("Sorry,the name can't be empty.");
                    return;
                }
            }
            if (isTemplate)
            {
                bool isRepeat = false;
                TemplateGroups groups = DataGate.Project.Templates;
                foreach (TemplateGroup template in groups)
                {
                    if (template.Name == _info)
                    {
                        isRepeat = true;
                    }
                }
                if (isRepeat)
                {
                    MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.TemplateRepeat));
                    return;
                }
            }
            DialogResult = DialogResult.OK;
            Result = DialogResult;
            Close();
        }

        protected override void OnCancel()
        {
            base.OnCancel();
            _info = string.Empty;
            DialogResult = DialogResult.Cancel;
            Result = DialogResult;
        }

    }
}
