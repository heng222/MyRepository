//---------------------------------------------------------------------
//
// File: LibraryGroupCombo.cs
//      
// Description:
//      Library group combo class
//
// Author: Kevin 2008-7-28
//
// Modify History:
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using DevExpress.XtraEditors;
using ProWrite.Entity.Library;
using System.Windows.Forms;
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls.Library
{
    /// <summary>
    /// Library group combo class
    /// </summary>
    public class LibraryGroupCombo : ComboBoxEdit
    {
        public LibraryGroupCombo()
        {
            AllowDrop = true;
            SetStyle(ControlStyles.Selectable, true);
            this.Properties.AutoComplete = true;
        }

        public void Populate()
        {
            Properties.Items.Clear();
            if (DataGate.Project.LibraryGroups.Count > 0)
            {
                Properties.Items.AddRange(DataGate.Project.LibraryGroups.ToArray());
                SelectedIndex = 0;
            }         
        }

        public new LibraryGroup SelectedItem
        {
            get
            {
                return base.SelectedItem as LibraryGroup;
            }
        }

        /// <summary>
        /// Search
        /// </summary>
        private void DoSearch()
        {
            if (this.Text != String.Empty && !string.Equals("Not Found", this.Text))
            {
                Cursor.Current = Cursors.WaitCursor;

                Properties.Items.Clear();

                OnSearch();

                Cursor.Current = Cursors.Default;
            }
        }

        private void OnSearch()
        {
            LibraryGroup[] entities;
            entities = Search(Text);

            if (entities == null)
            {
                this.Text = "Not Found";
            }
            else if (entities.Length == 1)
            {
                this.Properties.Items.Add(entities[0]);
                SelectedIndex = 0;
            }
            else if (entities.Length > 1)
            {
                this.Properties.Items.AddRange(entities);

                this.SelectAll();
                this.ShowPopup();
            }
            else
            {
                this.Text = "Not Found";
            }
        }

        /// <summary>
        /// Look up the matched result according to the input string
        /// </summary>
        /// <param name="searchString"></param>
        /// <returns></returns>
        private LibraryGroup[] Search(string searchString)
        {
            LibraryGroup[] groups = DataGate.Project.LibraryGroups.ToArray();
            if (groups != null && groups.Length > 0)
            {
                List<LibraryGroup> matchs = new List<LibraryGroup>();
                List<LibraryGroup> halfMatchs = new List<LibraryGroup>();
                List<LibraryGroup> unMatchs = new List<LibraryGroup>();
                foreach (LibraryGroup item in groups)
                {
                    if (item.Name == searchString)
                        matchs.Add(item);
                    else if (item.Name.Contains(searchString))
                        halfMatchs.Add(item);
                    else
                        unMatchs.Add(item);
                }

                matchs.AddRange(halfMatchs);
                matchs.AddRange(unMatchs);
                return matchs.ToArray();
            }
            return null;
        }

        protected override void OnEnter(EventArgs e)
        {
            this.SelectAll();
            base.OnEnter(e);
        }

        protected override void OnKeyPress(KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)13)
            {
                this.DoSearch();
            }

            base.OnKeyPress(e);
        }

    }
}
