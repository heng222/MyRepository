using System;
using System.Collections.Generic;
using System.Text;
using DevExpress.XtraEditors;
using ProWrite.Entity;
using ProWrite.Entity.Library;
using System.Windows.Forms;
using System.Drawing;
using DevExpress.XtraEditors.Controls;
using ProWrite.Core;
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls.Library
{
    class LibraryGroupLookup : LookUpEdit
    {
        public LibraryGroupLookup()
        {
            Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            Location = new System.Drawing.Point(3, 3);
            Size = new Size(158, 20);
            TabIndex = 0;
            //Properties.Buttons.AddRange(new EditorButton[] {
            //    new EditorButton(ButtonPredefines.Combo)});
            Properties.NullText = "[Library Group is null]";
            Properties.DropDownItemHeight = 0;
            Properties.HotTrackItems = true;
            Properties.Columns.Add(new LookUpColumnInfo("Name"));
            Properties.ValueMember = "Name";
            Properties.DisplayMember = "Name";
            Properties.ShowHeader = false;
            Properties.ShowFooter = false;
            Properties.HeaderClickMode = HeaderClickMode.Sorting;
            Properties.SearchMode = SearchMode.AutoFilter;
            Properties.BestFit();
            Properties.PopupWidth = Width;

            if (!DesignMode)
                Populate();
        }

        public void Populate(string libraryGrpName)
        {
            ListSet<LibraryGroup> list = DataGate.Project.LibraryGroups;
            if (list.Count == 0)
                return;
            
            Properties.DataSource = list.ToArray();

            if (string.IsNullOrEmpty(libraryGrpName))
                EditValue = list[0].Name;
            else
                EditValue = libraryGrpName;           

        }

        public void Populate()
        {
            Populate(string.Empty);
        }

    }
}
