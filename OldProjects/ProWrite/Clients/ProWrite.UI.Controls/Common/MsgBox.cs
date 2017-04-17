//---------------------------------------------------------------------
//
// File: MsgBox.cs
//
// Description:
// Standard message box
//
// Author: Louis
// Modify histories:
//      Jerry Xu 2009-1-4 Add method: Information(string msg,string title)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using DevExpress.Utils;
using System.Runtime.InteropServices;
using DevExpress.LookAndFeel;
using System.ComponentModel;
using System.Drawing;

namespace ProWrite.UI.Controls.Common
{
	/// <summary>
	/// The MsgBox class collected all message box can be used in project
	/// </summary>
	public static class MsgBox
	{
        const string DefaultCaption = "";
        const IWin32Window DefaultOwner = null;
        const MessageBoxButtons DefaultButtons = MessageBoxButtons.OK;
        const MessageBoxIcon DefaultIcon = MessageBoxIcon.None;
        const MessageBoxDefaultButton DefaultDefButton = MessageBoxDefaultButton.Button1;

        [DllImport("user32.dll")]
        static extern bool MessageBeep(int uType);
        static bool _AllowCustomLookAndFeel = false;
        public static bool AllowCustomLookAndFeel
        {
            get { return _AllowCustomLookAndFeel; }
            set { _AllowCustomLookAndFeel = value; }
        }

        private static DialogResult Show(string text) { return Show(DefaultOwner, text, DefaultCaption, DefaultButtons, DefaultIcon, DefaultDefButton); }
        private static DialogResult Show(IWin32Window owner, string text) { return Show(owner, text, DefaultCaption, DefaultButtons, DefaultIcon, DefaultDefButton); }
        private static DialogResult Show(string text, string caption) { return Show(DefaultOwner, text, caption, DefaultButtons, DefaultIcon, DefaultDefButton); }
        private static DialogResult Show(IWin32Window owner, string text, string caption) { return Show(owner, text, caption, DefaultButtons, DefaultIcon, DefaultDefButton); }
        private static DialogResult Show(string text, string caption, MessageBoxButtons buttons) { return Show(DefaultOwner, text, caption, buttons, DefaultIcon, DefaultDefButton); }
        private static DialogResult Show(IWin32Window owner, string text, string caption, MessageBoxButtons buttons) { return Show(owner, text, caption, buttons, DefaultIcon, DefaultDefButton); }
        private static DialogResult Show(string text, string caption, MessageBoxButtons buttons, MessageBoxIcon icon) { return Show(DefaultOwner, text, caption, buttons, icon, DefaultDefButton); }
        private static DialogResult Show(IWin32Window owner, string text, string caption, MessageBoxButtons buttons, MessageBoxIcon icon) { return Show(owner, text, caption, buttons, icon, DefaultDefButton); }
        private static DialogResult Show(string text, string caption, MessageBoxButtons buttons, MessageBoxIcon icon, MessageBoxDefaultButton defaultButton) { return Show(DefaultOwner, text, caption, buttons, icon, defaultButton); }
        private static DialogResult Show(IWin32Window owner, string text, string caption, MessageBoxButtons buttons, MessageBoxIcon icon, MessageBoxDefaultButton defaultButton)
        {
            return Show(owner, text, caption, MessageBoxButtonsToDialogResults(buttons), MessageBoxIconToIcon(icon), MessageBoxDefaultButtonToInt(defaultButton), icon);
        }
        private static DialogResult Show(IWin32Window owner, string text, string caption, DialogResult[] buttons, Icon icon, int defaultButton, MessageBoxIcon messageBeepSound)
        {
            FormHelper.TopMost = true;
            MessageBeep((int)messageBeepSound);

            var args = new XtraMessageBoxArgs(null, FormHelper.ActiveForm, text, caption, buttons, icon, defaultButton);

            using (XtraMessageBoxForm dlg = new XtraMessageBoxForm())
            {
                if (dlg.InvokeRequired)
                {
                    Func<XtraMessageBoxForm,XtraMessageBoxArgs, DialogResult> fun = DoShowModalDialog;
                    return (DialogResult)dlg.Invoke(fun, new object[] { dlg,args });
                }
                else
                {
                    return DoShowModalDialog(dlg,args);
                }
            }
        }

        private static DialogResult DoShowModalDialog(XtraMessageBoxForm dlg, XtraMessageBoxArgs args)
        {
            var result = dlg.ShowMessageBoxDialog(args);
            FormHelper.TopMost = false;
            return result;
        }


        static DialogResult[] MessageBoxButtonsToDialogResults(MessageBoxButtons buttons)
        {
            if (!Enum.IsDefined(typeof(MessageBoxButtons), buttons))
            {
                throw new InvalidEnumArgumentException("buttons", (int)buttons, typeof(DialogResult));
            }
            switch (buttons)
            {
                case MessageBoxButtons.OK:
                    return new DialogResult[] { DialogResult.OK };
                case MessageBoxButtons.OKCancel:
                    return new DialogResult[] { DialogResult.OK, DialogResult.Cancel };
                case MessageBoxButtons.AbortRetryIgnore:
                    return new DialogResult[] { DialogResult.Abort, DialogResult.Retry, DialogResult.Ignore };
                case MessageBoxButtons.RetryCancel:
                    return new DialogResult[] { DialogResult.Retry, DialogResult.Cancel };
                case MessageBoxButtons.YesNo:
                    return new DialogResult[] { DialogResult.Yes, DialogResult.No };
                case MessageBoxButtons.YesNoCancel:
                    return new DialogResult[] { DialogResult.Yes, DialogResult.No, DialogResult.Cancel };
                default:
                    throw new ArgumentException("buttons");
            }
        }
        static Icon MessageBoxIconToIcon(MessageBoxIcon icon)
        {
            if (!Enum.IsDefined(typeof(MessageBoxIcon), icon))
            {
                throw new InvalidEnumArgumentException("icon", (int)icon, typeof(DialogResult));
            }
            switch (icon)
            {
                case MessageBoxIcon.None:
                    return null;
                case MessageBoxIcon.Error:
                    return SystemIcons.Error;
                case MessageBoxIcon.Exclamation:
                    return SystemIcons.Exclamation;
                case MessageBoxIcon.Information:
                    return SystemIcons.Information;
                case MessageBoxIcon.Question:
                    return SystemIcons.Question;
                default:
                    throw new ArgumentException("icon");
            }
        }
        static int MessageBoxDefaultButtonToInt(MessageBoxDefaultButton defButton)
        {
            if (!Enum.IsDefined(typeof(MessageBoxDefaultButton), defButton))
            {
                throw new InvalidEnumArgumentException("defaultButton", (int)defButton, typeof(DialogResult));
            }
            switch (defButton)
            {
                case MessageBoxDefaultButton.Button1:
                    return 0;
                case MessageBoxDefaultButton.Button2:
                    return 1;
                case MessageBoxDefaultButton.Button3:
                    return 2;
                default:
                    throw new ArgumentException("defaultButton");
            }
        }

		/// <summary>
		/// The Warnning message box
		/// </summary>
		/// <param name="msg">The content of message</param>
		/// <returns>DialogResult.OK</returns>
		public static DialogResult Warning(string msg)
		{
            return Show(msg, "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
		}
		/// <summary>
		/// The Warnning message box
		/// </summary>
		/// <param name="msg">The content of message</param>
		/// <param name="caption">The caption of the message box</param>
		/// <returns>DialogResult.OK</returns>
		public static DialogResult Warning(string msg,string caption)
		{
            return Show(msg, caption, MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }
		/// <summary>
		/// The Warnning message box
		/// </summary>
		/// <param name="msg">The content of message</param>
		/// <param name="caption">The caption of the message box</param>
		/// <param name="buttons">The MessageBoxButtons of the message box</param>
		/// <returns>DialogResult.OK</returns>
		public static DialogResult Warning(string msg, string caption,MessageBoxButtons buttons)
		{
            return Show(msg, caption, buttons, MessageBoxIcon.Warning);
        }
		/// <summary>
		/// The error message box
		/// </summary>
		/// <param name="msg">The content of message</param>
		/// <returns>DialogResult.OK</returns>
		public static DialogResult Error(string msg)
		{
            return Show(msg, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

		/// <summary>
		/// The confirm message box
		/// </summary>
		/// <param name="msg">The content of confirm message</param>
		/// <returns>Yes or No</returns>
		public static DialogResult Confirm(string msg)
		{
			return Confirm(msg, MessageBoxButtons.YesNo);
		}

		/// <summary>
		/// The confirm message box
		/// </summary>
		/// <param name="msg">The content of confirm message</param>
		/// <returns>Yes or No</returns>
		public static DialogResult Confirm(string msg, MessageBoxButtons buttons)
		{
           return Show(msg, "Confirm", buttons, MessageBoxIcon.Question);
        }

        public static DialogResult WarningConfirm(string msg, MessageBoxButtons buttons)
        {
            return Show(msg, "Confirm", buttons, MessageBoxIcon.Warning);
        }
		/// <summary>
		/// The information message box
		/// </summary>
		/// <param name="msg">The content of information message</param>
		/// <returns>DialogResult.OK</returns>
		public static DialogResult Information(string msg)
		{
            return Show(msg, "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        /// <summary>
        /// Function: The information message box
        /// Author  : Jerry Xu
        /// Date    : 2009-1-4
        /// </summary>
        /// <param name="msg">The content of information message</param>
        /// <param name="title">string</param>
        /// <returns>DialogResult.OK</returns>
        public static DialogResult Information(string msg,string title)
        {
            return Show(msg, title, MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

		public static string OpenFile(string filter)
		{
			using (OpenFileDialog dlg = new OpenFileDialog())
			{
				dlg.Filter = filter;
				if (dlg.ShowModalDialog() == DialogResult.OK)
				{
					return dlg.FileName;
				}
			}
			return null;
		}

	}
}