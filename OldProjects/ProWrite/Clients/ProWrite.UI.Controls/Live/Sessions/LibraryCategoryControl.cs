using System;
using System.Collections.Generic;
using System.Windows.Forms;

using ProWrite.UI.Controls.Library;
using ProWrite.Entity.Live;
using DevExpress.XtraTreeList;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public partial class LibraryCategoryControl : UserControl
    {
        private LibraryTreeControl _libTree;
        private static List<LiveCategory> _dataSource = new List<LiveCategory>();

        public event EventHandler<CategoryEventArgs> OnCategoryCheckedStateChange = null;

        public LibraryCategoryControl()
        {
            InitializeComponent();
            if (!DesignMode)
            {
                InitMsgTree();
                tabCategories_SelectedPageChanged(null, null);
                CategoryDataBinding();
            }
        }

        #region Events

        private void tabCategories_SelectedPageChanged(object sender, DevExpress.XtraTab.TabPageChangedEventArgs e)
        {
            if (tabCategories.SelectedTabPage.Text == "Library")
                btnDeleteCategory.Enabled = false;
            else
                btnDeleteCategory.Enabled = true;
        }

        private void btnDeleteCategory_Click(object sender, EventArgs e)
        {
            RemoveCategory();
        }

        private void _libTree_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                _libTree.DoDragDrop(SelectedItems, DragDropEffects.Copy | DragDropEffects.Move);
            }
        }

        #endregion

        #region Property

        public TreeListMultiSelection SelectedItems
        {
            get { return _libTree.Selection; }
        }

        public static LiveCategory[] Categories
        {
            get { return _dataSource.ToArray(); }
        }

        #endregion

        #region Public Methods

        public void UpdateCategoryItem(LiveMessageItem[] items, string categoryId)
        {
            LiveCategory[] categoies = _dataSource.ToArray();

            foreach (LiveCategory category in categoies)
            {
                if (categoryId == category.Id)
                {
                    category.RemoveAllItems();
                    category.AddItems(items);
                    break;
                }
            }
        }

        public void AddCategoryToGrid(LiveCategory[] categoryArray)
        {
            if (categoryArray != null && categoryArray.Length > 0)
            {
                foreach (LiveCategory tmpItem in categoryArray)
                {
                    _dataSource.Add(tmpItem);
                    gridExistCategory.RefreshDataSource();
                }
            }
        }

        public void InitNew(LiveCategory[] categoryArray)
        {
            _dataSource.Clear();

            if (categoryArray.Length > 0)
            {
                foreach (LiveCategory tmpItem in categoryArray)
                {
                    tmpItem.CheckedState = false;
                    _dataSource.Add(tmpItem);
                }
                gridExistCategory.RefreshDataSource();
            }
        }

        public void LoadSession(LiveCategory[] libCategories, LiveCategory[] sessionCategories)
        {
            InitNew(libCategories);

            if (sessionCategories.Length > 0)
            {
                foreach (LiveCategory tmpItem in sessionCategories)
                {
                    tmpItem.CheckedState = true;
                    AddRemoveTabPage(tmpItem);
                    SetCategoryShowState(tmpItem);
                }
                gridExistCategory.RefreshDataSource();
            }
        }

        public void SetCategoryShowState(LiveCategory category)
        {
            if (_dataSource.Count > 0)
            {
                foreach (LiveCategory tmpCategory in _dataSource)
                {
                    if (tmpCategory.Id == category.Id)
                    {
                        tmpCategory.CheckedState = category.CheckedState;
                        gridExistCategory.RefreshDataSource();
                        break;
                    }
                }
            }
        }

        #endregion

        #region Private Methods

        private void RemoveCategory()
        {
            if (_dataSource.Count > 0)
            {
                if (gridView.GetSelectedRows().Length > 0)
                {
                    for (int i = 0; i < gridView.GetSelectedRows().Length; i++)
                    {
                        LiveCategory removeCategory = gridView.GetRow(i) as LiveCategory;
                        removeCategory.CheckedState = false;
                        AddRemoveTabPage(removeCategory);
                        _dataSource.Remove(removeCategory);
                    }

                    gridExistCategory.RefreshDataSource();
                }
            }
        }

        /// <summary>
        /// 
        /// </summary>
        private void InitMsgTree()
        {
            _libTree = new LibraryTreeControl(false);
            _libTree.OptionsSelection.MultiSelect = true;
            _libTree.ContextMenuStrip = null;
            _libTree.Dock = DockStyle.Fill;
            _libTree.Type = ProWrite.Core.LibraryType.Message | ProWrite.Core.LibraryType.Playlist | ProWrite.Core.LibraryType.TimeSliceGroup;
            _libTree.MouseDown += new MouseEventHandler(_libTree_MouseDown);
            tabPageLibrary.Controls.Add(_libTree);
        }

        private void CategoryDataBinding()
        {
            gridExistCategory.DataSource = _dataSource;
        }

        #endregion

        private void gridView_CustomRowCellEditForEditing(object sender, DevExpress.XtraGrid.Views.Grid.CustomRowCellEditEventArgs e)
        {
            if (e.Column.Caption == "Show")
            {
                LiveCategory category = _dataSource[e.RowHandle] as LiveCategory;
                category.CheckedState = !category.CheckedState;
                AddRemoveTabPage(category);
                CategoryDataBinding();
                gridView.RefreshData();
            }
        }

        private void AddRemoveTabPage(LiveCategory category)
        {
            if (OnCategoryCheckedStateChange != null)
            {
                CategoryEventArgs args = new CategoryEventArgs();
                args.Category = category;
                OnCategoryCheckedStateChange(this, args);
            }
        }

        private void LibraryCategoryControl_Load(object sender, EventArgs e)
        {

        }

    }
}
