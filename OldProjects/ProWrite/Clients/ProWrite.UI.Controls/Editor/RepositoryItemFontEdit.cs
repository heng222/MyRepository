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
	[UserRepositoryItem("Register")]
	public partial class RepositoryItemFontEdit : RepositoryItemButtonEdit 
	{
		static RepositoryItemFontEdit()
		{
			Register();
		}

		public RepositoryItemFontEdit()
		{
			this.TextEditStyle = TextEditStyles.Standard;
			ButtonClick += new ButtonPressedEventHandler(RepositoryItemFontEdit_ButtonClick);
		}

		void RepositoryItemFontEdit_ButtonClick(object sender, ButtonPressedEventArgs e)
		{
			FontSelectForm fontForm = new FontSelectForm();
			ButtonEdit edit = sender as ButtonEdit;

			if (fontForm.ShowModalDialog() == DialogResult.OK)
			{
				FontWrapper font = fontForm.MyFont;
				edit.EditValue = font;
			}
		}

		internal const string EditorName = "MyFontEdit";

        public static void Register() {
            EditorRegistrationInfo.Default.Editors.Add(new EditorClassInfo(EditorName, typeof(MyFontEdit),
				typeof(RepositoryItemFontEdit), typeof(DevExpress.XtraEditors.ViewInfo.ButtonEditViewInfo), 
                new DevExpress.XtraEditors.Drawing.ButtonEditPainter(), true, null));
        }
        public override string EditorTypeName { 
            get { return EditorName; } 
        }
    }

	public class MyFontEdit : ButtonEdit
	{
        static MyFontEdit() {
			RepositoryItemFontEdit.Register();
        }
        public MyFontEdit() {}

        public override string EditorTypeName {
			get { return RepositoryItemFontEdit.EditorName; } 
        }

        [DesignerSerializationVisibility(DesignerSerializationVisibility.Content)]
		public new RepositoryItemFontEdit Properties
		{
			get { return base.Properties as RepositoryItemFontEdit; } 
        }

    }
}

