using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.ComponentModel;

namespace ProWrite.UI.Controls
{
    public static class FormHelper
    {
        private static Form activeForm;
        public static Form ActiveForm
        {
            get
            {
                if (Form.ActiveForm != null)
                    return Form.ActiveForm;
                if (activeForm != null)
                    return activeForm;
                if (Application.OpenForms.Count < 0)
                    return null;
                if(Application.OpenForms.Count>0)
                    return Application.OpenForms[0];
                return null;

            }
            set
            {
                activeForm = value;
            }
        }

        public static bool TopMost
        {
            get
            {
                if (ActiveForm != null)
                    return ActiveForm.TopMost;
                return false;
            }
            set
            {
                if (ActiveForm != null)
                    ActiveForm.TopMost = value;
            }
        }

        public static DialogResult ShowModalDialog(this Form dlg)
        {
            return ShowModalDialog(dlg, true);
        }

        public static DialogResult ShowModalDialog(this Form dlg,bool enableControlBox)
        {
            Check.Assert(dlg != null);

            if (dlg.InvokeRequired)
            {
                Func<Form,bool,DialogResult> fun = DoShowModalDialog;
                return (DialogResult)dlg.Invoke(fun, new object[] { dlg, enableControlBox });
            }
            else
            {
                return DoShowModalDialog(dlg,enableControlBox);
            }
        }


        private static DialogResult DoShowModalDialog(Form dlg,bool enableControlBox)
        {
            Form owner = ActiveForm;
            if (owner == null)
            {
                owner = Form.ActiveForm;
                if (owner == null)
                    owner = dlg.Owner;
                ActiveForm = owner;
            }

            bool hasOwnerForm = ActiveForm != null;

            if (hasOwnerForm)
                dlg.StartPosition = FormStartPosition.CenterParent;
            else
                dlg.StartPosition = FormStartPosition.CenterScreen;

            dlg.MaximizeBox = false;
            dlg.MinimizeBox = false;
            dlg.FormBorderStyle = FormBorderStyle.FixedSingle;
            dlg.ControlBox = enableControlBox;
            dlg.ShowInTaskbar = !hasOwnerForm;

#if DEBUG
            //dlg.TopMost = hasOwnerForm;
            TopMost = false;
            var result = dlg.ShowDialog(ActiveForm);
            TopMost = false;

            return result;
           //return dlg.ShowDialog(ActiveForm);
#else
            if(SessionState.Instance.ContainsKey("ImportOpen") || SessionState.Instance.ContainsKey("Import"))
                TopMost = true;
            //dlg.TopMost = hasOwnerForm; //comment out by louis for dialog can be hidden by Alt-Tab
            //TopMost = true;
            var result = dlg.ShowDialog(ActiveForm);
            dlg.Activate();
            TopMost = false;

            return result;
#endif

        }

        public static DialogResult ShowModalDialog(this CommonDialog dlg)
        {
            Check.Assert(dlg != null);
            if (ActiveForm != null)
                ActiveForm.TopMost = true;
            var result = dlg.ShowDialog(ActiveForm);
            if (ActiveForm != null)
                ActiveForm.TopMost = false;
            return result;
        }

        public static void InvokeMethod(this ISynchronizeInvoke hwnd, Action method)
        {
            InternalInvokeMethod(hwnd, method, null);
        }

        public static void InvokeMethod<T>(this ISynchronizeInvoke hwnd, Action<T> method,T arg)
        {
            InternalInvokeMethod(hwnd, method, arg);
        }

        private static void InternalInvokeMethod(ISynchronizeInvoke hwnd, Delegate method, params object[] args)
        {
            Check.Assert(hwnd != null);
            Check.Assert(method != null);

            if (hwnd.InvokeRequired)
                hwnd.Invoke(method, args);
            else
            {
                
                try
                {
                    method.DynamicInvoke(args);
                }
                catch
                {

                    try
                    {
                        System.Threading.SynchronizationContext.Current.Post((state) => method.DynamicInvoke(args), null);
                    }
                    finally
                    {
                    }
                }
            }
        }

        public static void InvokeProperty(this ISynchronizeInvoke hwnd, string propertyName,object propertyValue)
        {
            Check.Assert(hwnd != null);
            Check.Assert(propertyName != null);
            Action<string, object> method = hwnd.SetProperty;
            InternalInvokeMethod(hwnd, method, propertyName, propertyValue);
        }
    }
}
