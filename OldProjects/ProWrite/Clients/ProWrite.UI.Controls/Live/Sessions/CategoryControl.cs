using System;
using System.Collections.Generic;
using System.Windows.Forms;

using ProWrite.Entity.Library;
using ProWrite.Entity.Live;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public partial class CategoryControl : UserControl
    {
        private const string NOCategory = "Please add a new category or open a exist category.";
        private const string SameLibItem = "Please don't repeat add same item.";

        public CategoryControl()
        {
            InitializeComponent();
            if (!DesignMode)
            {
                ctlCategories.OnCategoryCreated += new EventHandler<CategoryEventArgs>(ctlCategories_OnCategoryCreated);
                ctlCategories.OnCreateNewGrid += new EventHandler(ctlCategories_OnCreateNewGrid);
                ctlCategories.OnTabPageClosed += new EventHandler<CategoryEventArgs>(ctlCategories_OnTabPageClosed);
                ctlLibrary.OnCategoryCheckedStateChange += new EventHandler<CategoryEventArgs>(ctlLibrary_OnCategoryCheckedStateChange);
            }
        }

        private void ctlCategories_OnTabPageClosed(object sender, CategoryEventArgs e)
        {
            ctlLibrary.SetCategoryShowState(e.Category);
        }

        private void ctlLibrary_OnCategoryCheckedStateChange(object sender, CategoryEventArgs e)
        {
            ctlCategories.AddRemoveCategory(e.Category);
        }

        private void ctlCategories_OnCreateNewGrid(object sender, EventArgs e)
        {
            ctlCategories.CurrentMsgControl.OnCategoryItemChanged +=new EventHandler<CategoryItemEventArgs>(CurrentMsgControl_OnCategoryItemChanged);
        }

        private void CurrentMsgControl_OnCategoryItemChanged(object sender, CategoryItemEventArgs e)
        {
            ctlLibrary.UpdateCategoryItem(e.CategoryItems, e.CategoryId);
        }

        private void ctlCategories_OnCategoryCreated(object sender, CategoryEventArgs e)
        {
            ctlLibrary.AddCategoryToGrid(new LiveCategory[] { e.Category });
        }

        private void btnAddMsg_Click(object sender, EventArgs e)
        {
            AddItems();
        }

        private void btnRemoveMsg_Click(object sender, EventArgs e)
        {
            if (ctlCategories.CurrentMsgControl != null)
            {
                if (ctlCategories.CurrentMsgControl.SelectDataRow != null 
                    && ctlCategories.CurrentMsgControl.SelectDataRow.Count > 0)
                {
                    foreach (LiveMessageItem tmpItem in ctlCategories.CurrentMsgControl.SelectDataRow)
                        ctlCategories.CurrentTabPageDataSource.Remove(tmpItem);

                    ctlCategories.CurrentMsgControl.RefreshDataSource();
                    ctlCategories.CurrentMsgControl.CategoryItemChanged();
                }
                else
                {
                    if (ctlCategories.CurrentMsgControl.DataSource.Count > 0)
                    {
                        ctlCategories.CurrentMsgControl.DataSource.RemoveAt(0);
                        ctlCategories.CurrentMsgControl.RefreshDataSource();
                        ctlCategories.CurrentMsgControl.CategoryItemChanged();
                    }
                }
            }
        }

        public void New()
        {
            ctlCategories.InitNew();
            ctlLibrary.InitNew(SessionInfo.Current.LibraryCategories);
        }

        public void Save()
        {
            SessionInfo.Current.MergeCategoryLibrary(LibraryCategoryControl.Categories);
            SessionInfo.Current.MergeCategoryToSessionInfo(ctlCategories.SessionCategories);
        }

        public void LoadSession()
        {
            ctlCategories.InitNew();
            ctlLibrary.LoadSession(SessionInfo.Current.LibraryCategories, SessionInfo.Current.SessionCategories);
        }

        public static bool CheckSameMemoryLibraryItem(LiveMessageItem item, List<LiveMessageItem> itemList)
        {
            foreach (LiveMessageItem tmpItem in itemList)
                if (item.Target == tmpItem.Target) return false;
            return true;
        }

        private void AddItems()
        {
            if (ctlLibrary.SelectedItems != null &&
                ctlLibrary.SelectedItems.Count > 0)
            {
                foreach (Library.LibraryNode item in ctlLibrary.SelectedItems)
                {
                    if (ctlCategories.CurrentTabPageDataSource != null)
                    {
                        MemoryLibraryItem tmpItem = item.Tag as MemoryLibraryItem;

                        LiveMessageItem libItem = new LiveMessageItem();
                        libItem.Name = tmpItem.Name;
                        libItem.Target = tmpItem;
                        libItem.Id = tmpItem.Id;
                        
                        if (CheckSameMemoryLibraryItem(libItem, ctlCategories.CurrentTabPageDataSource))
                        {
                            ctlCategories.CurrentTabPageDataSource.Add(libItem);
                            ctlCategories.CurrentMsgControl.RefreshDataSource();
                        }
                        else
                        {
                            MessageBox.Show(SameLibItem, "Tip", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        }
                    }
                    else
                    {
                        MessageBox.Show(NOCategory, "Tip", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    }

                }

                if (ctlCategories.CurrentMsgControl != null
                    && ctlCategories.CurrentMsgControl.DataSource != null)
                {
                    ctlCategories.CurrentMsgControl.RefreshDataSource();
                    ctlCategories.CurrentMsgControl.CategoryItemChanged();
                }

            }
        }

    }
}
