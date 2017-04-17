using System;
using System.Windows.Forms;
using System.Collections.Generic;

using ProWrite.Entity.Library;
using ProWrite.Entity.Dashboard;
using ProWrite.Entity.Live;

using DevExpress.XtraTab;
using DevExpress.XtraGrid.Views.Grid.ViewInfo;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public class CategoryEventArgs : EventArgs
    {
        LiveCategory _category = new LiveCategory();
        public LiveCategory Category
        {
            set { _category = value; }
            get { return _category; }
        }
    }

    public partial class CategoriesControl : UserControl
    {
        public CategoriesControl()
        {
            InitializeComponent();
            if(!DesignMode)
                cmbView.SelectedIndex = 0;
        }

        GridHitInfo hitInfo = null;
        private bool _categoryChange = false;
        public const string SaveCategory = "Do you want save the category?";

        public event EventHandler<CategoryEventArgs> OnCategoryCreated = null;
        public event EventHandler OnCreateNewGrid = null;
        public event EventHandler<CategoryEventArgs> OnTabPageClosed = null;

        private void btnNew_Click(object sender, EventArgs e)
        {
            New();
        }

        public bool IsMainForm
        {
            set 
            {
                if (value)
                {
                    btnNew.Visible = false;
                    cmbView.Anchor = AnchorStyles.Top;
                    cmbView.Location = new System.Drawing.Point(labelControl2.Location.X, labelControl2.Location.Y-2);
                    labelControl2.Visible = false;
                    labelControl1.Anchor = AnchorStyles.Top;
                    labelControl1.Location = new System.Drawing.Point(labelControl2.Location.X - 28, labelControl2.Location.Y);
                }
            }
        }
        public List<LiveMessageItem> CurrentTabPageDataSource
        {
            get
            {
                List<LiveMessageItem> items = null;
                if (tabPageControl.SelectedTabPage != null)
                {
                    MessageGridControl msgGridCtl = tabPageControl.SelectedTabPage.Controls[0] as MessageGridControl;
                    items = msgGridCtl.DataSource as List<LiveMessageItem>;
                }
                return items;
            }
            set{
                if (tabPageControl.SelectedTabPage != null && tabPageControl.SelectedTabPage.Controls.Count > 0)
                {
                    MessageGridControl msgGridCtl = tabPageControl.SelectedTabPage.Controls[0] as MessageGridControl;
                    msgGridCtl.DataSource = value;
                }
            }
        }

        public List<LiveMessageItem> SelectedItems
        {
            get
            {
                MessageGridControl msgGridCtl = tabPageControl.SelectedTabPage.Controls[0] as MessageGridControl;
                return msgGridCtl.SelectDataRow;
            }
        }

        public LiveCategory[] SessionCategories
        {
            get
            {
                LiveCategory[] categories = new LiveCategory[tabPageControl.TabPages.Count];

                for (int i = 0; i < tabPageControl.TabPages.Count; i++)
                    categories[i] = tabPageControl.TabPages[i].Tag as LiveCategory;

                return categories;
            }
        }

        public void AddRemoveCategory(LiveCategory category)
        {
            if (category.CheckedState)
            {
                AddTabPage(NewTabPage(category));
            }
            else
            {
                RemoveTabPage(category.Id);
            }
        }

        public void InitNew()
        {
            tabPageControl.TabPages.Clear();
        }

        private void New()
        {
            //CloseCategory();
            if (!_categoryChange)
            {
                NewCategoryForm frmNewCategory = null;
                try
                {
                    frmNewCategory = new NewCategoryForm();
                    if (frmNewCategory.ShowDialog() == DialogResult.OK)
                    {
                        LiveCategory category = NewLiveCategory(frmNewCategory.CategoryName);
                        AddTabPage(NewTabPage(category));

                        if (OnCategoryCreated != null)
                        {
                            CategoryEventArgs args = new CategoryEventArgs();
                            args.Category = category;
                            OnCategoryCreated(this, args);
                        }
                    }
                }
                finally
                {
                    frmNewCategory.Dispose();
                }
            }
        }

        private LiveCategory NewLiveCategory(string name)
        {
            LiveCategory category = new LiveCategory();
            category.Id = Guid.NewGuid().ToString();
            category.Name = name;
            category.CreateTime = DateTime.Now;
            category.CheckedState = true;
            return category;
        }

        private XtraTabPage NewTabPage(LiveCategory category)
        {
            XtraTabPage tabPage = new XtraTabPage { Text = category.Name };
            tabPage.ShowCloseButton = DevExpress.Utils.DefaultBoolean.True;
            MessageGridControl grid = NewDataGrid(category.Id);
            if (category.Items.Length > 0)
                grid.DataSource.AddRange(category.Items);

            if (category.ViewState == ProWrite.Core.LiveCategoryViewState.CardView)
                grid.View = grid.CardView;

            tabPage.Controls.Add(grid);
            tabPage.Tag = category;

            return tabPage;
        }

        private void AddTabPage(XtraTabPage page)
        {
            tabPageControl.TabPages.Add(page);
            cmbView_SelectedIndexChanged(null, null);
            tabPageControl.SelectedTabPageIndex = tabPageControl.TabPages.Count - 1;

            if (OnCreateNewGrid != null)
            {
                OnCreateNewGrid(this, null);
            }
        }

        private void RemoveTabPage(string id)
        {
            for (int i = 0; i < tabPageControl.TabPages.Count; i++)
            {
                LiveCategory category = tabPageControl.TabPages[i].Tag as LiveCategory;
                if (category.Id == id)
                {
                    tabPageControl.TabPages.RemoveAt(i);
                    break;
                }
            }
        }

        private MessageGridControl NewDataGrid(string categoryId)
        {
            MessageGridControl ctlMsgGrid = new MessageGridControl();
            List<LiveMessageItem> data = new List<LiveMessageItem>();
            ctlMsgGrid.DataSource = data;
            ctlMsgGrid.Dock = DockStyle.Fill;
            ctlMsgGrid.CategoryID = categoryId;
            return ctlMsgGrid;
        }

        private void cmbView_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (tabPageControl.TabPages.Count > 0)
            {
                LiveCategory category = tabPageControl.SelectedTabPage.Tag as LiveCategory;

                if (cmbView.SelectedIndex == 0)
                {
                    CurrentMsgControl.View = CurrentMsgControl.ListView;
                    category.ViewState = ProWrite.Core.LiveCategoryViewState.ListView;
                }
                else
                {
                    CurrentMsgControl.View = CurrentMsgControl.CardView;
                    category.ViewState = ProWrite.Core.LiveCategoryViewState.CardView;
                }
            }
        }

        private void tabPageControl_SelectedPageChanged(object sender, TabPageChangedEventArgs e)
        {
            cmbView_SelectedIndexChanged(null, null);
        }

        public MessageGridControl CurrentMsgControl
        {
            get
            {
                MessageGridControl msgGridCtl = null;
                if (tabPageControl.SelectedTabPage != null)
                    msgGridCtl = tabPageControl.SelectedTabPage.Controls[0] as MessageGridControl;
                return msgGridCtl;
            }
        }

        private void tabPageControl_CloseButtonClick(object sender, EventArgs e)
        {
            if (tabPageControl.SelectedTabPage != null)
            {
                if (OnTabPageClosed != null)
                {
                    CategoryEventArgs categoryArgs = new CategoryEventArgs();
                    categoryArgs.Category = tabPageControl.SelectedTabPage.Tag as LiveCategory;
                    categoryArgs.Category.CheckedState = false;
                    OnTabPageClosed(this, categoryArgs);
                }

                tabPageControl.TabPages.Remove(tabPageControl.SelectedTabPage);
            }
        }

    }
}
