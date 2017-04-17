using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors;
using DevExpress.XtraEditors.Controls;
using DevExpress.XtraEditors.Registrator;
using DevExpress.XtraEditors.Repository;
using ProWrite.Entity.Shape;

namespace ProWrite.UI.Controls.Editor
{
	public partial class RepositoryItemTextEffectEdit : RepositoryItemButtonEdit
	{
		public event EventHandler TextEffectChanged;
		static RepositoryItemTextEffectEdit()
		{
			Register();
		}

		public RepositoryItemTextEffectEdit()
		{
			this.TextEditStyle = TextEditStyles.Standard;
			ButtonClick += new ButtonPressedEventHandler(RepositoryItemTextEffectEdit_ButtonClick);
		}

		void RepositoryItemTextEffectEdit_ButtonClick(object sender, ButtonPressedEventArgs e)
		{
            TextEffectEdit edit = sender as TextEffectEdit;
			TextEffect te = new TextEffect();
			te = ((TextEffect) (edit.EditValue)).Copy();
			TextEffectForm textEffectForm = new TextEffectForm(te);

            if (textEffectForm.ShowModalDialog() == DialogResult.OK)
			{
				edit.EditValue = textEffectForm.TextEffect;
                if (TextEffectChanged != null)
                {
                    this.NullText = edit.EditValue.ToString();
                    TextEffectChanged(sender, e);
                }
			}
		}

		internal const string EditorName = "TextEffectEdit";

        public static void Register() {
			EditorRegistrationInfo.Default.Editors.Add(new EditorClassInfo(EditorName, typeof(TextEffectEdit),
				typeof(RepositoryItemTextEffectEdit), typeof(DevExpress.XtraEditors.ViewInfo.ButtonEditViewInfo), 
                new DevExpress.XtraEditors.Drawing.ButtonEditPainter(), true, null));
        }
        public override string EditorTypeName { 
            get { return EditorName; } 
        }
    }

	public class TextEffectEdit : ButtonEdit
	{
        static TextEffectEdit() {
			RepositoryItemFontEdit.Register();
        }
		public TextEffectEdit() { }

        public override string EditorTypeName {
			get { return RepositoryItemFontEdit.EditorName; } 
        }

        [DesignerSerializationVisibility(DesignerSerializationVisibility.Content)]
		public new RepositoryItemTextEffectEdit Properties
		{
			get { return base.Properties as RepositoryItemTextEffectEdit; } 
        }

	}
}
