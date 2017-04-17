using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using ProWrite.Entity;
using ProWrite.Entity.Shape;
using ProWrite.Entity.Library;
using DevExpress.XtraSpellChecker.Rules;
using DevExpress.XtraSpellChecker;
using DevExpress.XtraBars;
using System.Globalization;
using ProWrite.Core;
using DevExpress.XtraSpellChecker.Forms;

namespace ProWrite.UI.Controls.Editor
{
    public partial class TextInputForm : XtraForm
    {
        private class SpellAndDirtyWordChecker : SpellChecker
        {
            public override void Check(Control editControl)
            {
                //base.Check(editControl);
                new DirtyWordChecker().Check(editControl as ITextBox);
            }
        }

        private class MyTextBox : MemoEdit, ITextBox
        {
        }

        private bool IsChanged = true;
        private static string _text;
        public delegate void SetShapeText(string text);
        public event SetShapeText UpdateShapeText;
        SpellCheckerCustomDictionary customDictionary;
        public TextInputForm(string text)
        {
            _text = text;
            spellChecker1 = ControlService.SpellChedker;
            InitializeComponent();

            //System.Threading.Tasks.Task.Create((state) =>
            //                                       {

            //                                           //this.InvokeMethod(()=>);
            //                                           memoEdit.InvokeProperty("Text", _text);
            //                                           this.InvokeMethod(()=> Initialize());
            //                                       });
            memoEdit.Text = _text;
            
            
        }

        private void Initialize()
        {
           
           
            sharedDictionaryStorage1.Dictionaries.Clear();
            SpellCheckerISpellDictionary dictionary = ControlService.SpellDictionary;
            sharedDictionaryStorage1.Dictionaries.Add(dictionary);

            customDictionary = ControlService.SpellCustomDictionary;
            sharedDictionaryStorage1.Dictionaries.Add(customDictionary);

            spellChecker1.Culture = customDictionary.Culture;

            barManager1.SetPopupContextMenu(this.memoEdit, popupMenu1);
            //DoCheck();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            UpdateShapeText(_text);
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void btnOk_Click(object sender, EventArgs e)
        {
            _text = memoEdit.Text.TrimEnd();
            DialogResult = DialogResult.OK;
            Close();
        }

        private void memoEdit_KeyUp(object sender, EventArgs e)
        {
            if (UpdateShapeText != null)
                UpdateShapeText(memoEdit.Text.TrimEnd());
        }

        private void memoEdit_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Up
                || e.KeyCode == Keys.Down
                || e.KeyCode == Keys.Right
                || e.KeyCode == Keys.Left)
                return;
            CheckDirtyWords(false);
        }

        public string InputText
        {
            get { return _text; }
        }

        private void memoEdit_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.F7 && e.Modifiers == Keys.None)
                DoCheck();
            
        }

        private void DoCheck()
        {
            spellChecker1.Check(GetActiveControl());

        }

        private Control GetActiveControl()
        {
            //Control result = ActiveControl;
            //if (result is DevExpress.XtraEditors.TextBoxMaskBox)
            //    result = result.Parent;
            //return result;
            return this.memoEdit;
        }

        private void TextInputForm_Load(object sender, EventArgs e)
        {
            Initialize();
            DoCheck();
        }

        protected virtual bool NeedPopulateDictionariesCollection()
        {
            return sharedDictionaryStorage1.Dictionaries.Count == 0;
        }

        private void barManager1_QueryShowPopupMenu(object sender, DevExpress.XtraBars.QueryShowPopupMenuEventArgs e)
        {
            Point position = e.Control.PointToClient(e.Position);
            SpellCheckErrorBase error = spellChecker1.CalcError(position);
            e.Cancel = error == null;
            List<SpellCheckerCommand> commands = spellChecker1.GetCommandsByError(error);
            if (commands != null)
            {
                popupMenu1.ItemLinks.Clear();
                foreach (SpellCheckerCommand command in commands)
                {
                    BarButtonItem item = new BarButtonItem(barManager1, command.Caption);
                    item.Enabled = command.Enabled;
                    item.Tag = command;
                    item.ItemClick += new ItemClickEventHandler(OnPopupMenuItemClick);
                    popupMenu1.ItemLinks.Add(item);
                }
            }
            BarButtonItem bitem = new BarButtonItem(barManager1, "Option");
            bitem.Enabled = true;
            //bitem.Tag = command;
            bitem.ItemClick += new ItemClickEventHandler(Option_Click);
            popupMenu1.ItemLinks.Add(bitem);
        }

        void Option_Click(object sender, ItemClickEventArgs e)
        {
            DoCheck();
        }

        void OnPopupMenuItemClick(object sender, ItemClickEventArgs e)
        {
            (e.Item.Tag as SpellCheckerCommand).DoCommand();
        }


        private void memoEdit_MouseDown(object sender, MouseEventArgs e)
        {

        }



        private void CheckDirtyWords(bool isMoveMouse)
        {
            //if (e.KeyCode.ToString() == Keys.Space.ToString())
            //{
            var dirtyWords = ServiceManager.Get<DirtyWordList>();
            
            if (dirtyWords == null || dirtyWords.Count < 1)
                return;

            bool isReturn = false;
            foreach (var item in dirtyWords)
            {
                var txt = memoEdit.Text;//.GetProperty<string>("Text");
                var index = txt.ToUpper().LastIndexOf(item.ToUpper());
                if (index != -1)
                {
                    int count = 0;
                    //while (index != -1)
                    //{
                        isReturn = false;
                        if (!isMoveMouse && index + item.Length >= txt.Length)
                            isReturn = true;
                        if (index != 0 && index + item.Length < txt.Length)
                        {
                            var strBefore = txt.Substring(index - 1, 1);
                            var strAfter = txt.Substring(index + item.Length, 1);
                            if (strBefore != " " || strAfter != " ")
                                isReturn = true;
                        }
                        //this.memoEdit.InvokeProperty("Text", txt.Replace(item, "".PadRight(item.Length, '*')));
                        if (!isReturn)
                        {
                            var rep = "";
                            for (int i = 0; i < item.Length; i++)
                                rep += "*";

                            var sss = memoEdit.Text.Substring(0, index);
                            var str = memoEdit.Text.Substring(index, item.Length);
                            txt = memoEdit.Text.Substring(index);
                            if (!string.IsNullOrEmpty(txt.Trim()))
                            {
                                txt = txt.Replace(str, rep);
                                memoEdit.Text = sss + txt;
                            }// memoEdit.Text.Replace(str, rep)
                        }
                        //txt = txt.Substring(index + item.Length);//.IndexOf(item.ToUpper);

                        //index = txt.ToUpper().IndexOf(item.ToUpper());

                        //count++;
                        //if(memoEdit.Text.Substring(0,1)==" ")
                        //    memoEdit.Text.Replace(
                    
                }
            }
            //this.listBoxControl1.Focus();


            memoEdit.Select(this.memoEdit.Text.Length, 0);
            memoEdit.ScrollToCaret();
            //}
        }

        private void memoEdit_TextChanged(object sender, EventArgs e)
        {
            //    if (!IsChanged)
            //    {
            //        IsChanged = true;
            //        return;
            //    }

            //    var dirtyWords = ServiceManager.Get<DirtyWordList>();
            //    if (dirtyWords == null || dirtyWords.Count < 1)
            //        return;
            //    foreach (var item in dirtyWords)
            //    {
            //        var txt = memoEdit.Text;//.GetProperty<string>("Text");
            //        var index = txt.IndexOf(item);
            //        if (index != -1)
            //        {
            //            //this.memoEdit.InvokeProperty("Text", txt.Replace(item, "".PadRight(item.Length, '*')));
            //            var rep = "";
            //            for (int i = 0; i < item.Length; i++)
            //                rep += "*";
            //            IsChanged = false;
            //            memoEdit.Text = txt.Replace(item, rep);//"".PadRight(item.Length, '*'));

            //            //if(memoEdit.Text.Substring(0,1)==" ")
            //            //    memoEdit.Text.Replace(
            //        }
            //    }
        }
        private void memoEdit_MouseLeave(object sender, EventArgs e)
        {
            //DoCheck();
            CheckDirtyWords(true);
        }

        private void spellChecker1_OptionsFormShowing(object sender, FormShowingEventArgs e)
        {
            
            SpellingOptionsForm optionForm = new SpellingOptionsForm(spellChecker1);

            Control control=optionForm.Controls[3].Controls[0].Controls[1];
           

            SimpleButton btnDirtyWords = new SimpleButton();
            btnDirtyWords.Text = "DirtyWords";
            btnDirtyWords.Width = 96;
            btnDirtyWords.Height = 23;
            btnDirtyWords.Location = new Point(control.Controls[1].Location.X - 100, control.Controls[1].Location.Y);
            btnDirtyWords.Click += new EventHandler(btnDirtyWords_Click);
            control.Controls.Add(btnDirtyWords);

            optionForm.Controls[3].Controls[0].Controls[2].Visible = false;
            optionForm.Controls[3].Controls[0].Height = 300;

            optionForm.ShowModalDialog();

            e.Handled = true;
        }

        void btnDirtyWords_Click(object sender, EventArgs e)
        {
            CustomDirtyWordsDictionary dirty = new CustomDirtyWordsDictionary();
            dirty.ShowModalDialog();
        }

        
        private void spellChecker1_SpellingFormShowing(object sender, SpellingFormShowingEventArgs e)
        {
           
        }
    }

    public class DemoUtils
    {
        public static void SetConnectionString(System.Data.OleDb.OleDbConnection oleDbConnection, string path)
        {
            oleDbConnection.ConnectionString = String.Format(@"Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source={0};Mode=Share Deny None;Extended Properties="""";Jet OLEDB:System database="""";Jet OLEDB:Registry Path="""";Jet OLEDB:Database Password="""";Jet OLEDB:Engine Type=5;Jet OLEDB:Database Locking Mode=1;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password="""";Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False", path);
        }
        public static string GetRelativePath(string name)
        {
            //name = "Data\\" + name;
            string path = System.Windows.Forms.Application.StartupPath;
            string s = "\\";
            for (int i = 0; i <= 10; i++)
            {
                if (System.IO.File.Exists(path + s + name))
                    return (path + s + name);
                else
                    s += "..\\";
            }
            path = Environment.CurrentDirectory;
            s = "\\";
            for (int i = 0; i <= 10; i++)
            {
                if (System.IO.File.Exists(path + s + name))
                    return (path + s + name);
                else
                    s += "..\\";
            }
            return "";
        }

    }
}
