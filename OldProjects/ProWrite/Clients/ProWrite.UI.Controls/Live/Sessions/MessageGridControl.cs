using System;
using System.Windows.Forms;
using System.Collections.Generic;
using DevExpress.XtraGrid.Views.Base;
using ProWrite.Entity.Library;
using DevExpress.XtraTreeList;
using ProWrite.Entity.Live;
using DevExpress.XtraGrid.Views.Grid.ViewInfo;
using System.Drawing;
using DevExpress.XtraGrid.Views.Grid;

namespace ProWrite.UI.Controls.Live.Sessions
{
    public class CategoryItemEventArgs : EventArgs
    {
        private string _categoryId;
        public string CategoryId
        {
            set { _categoryId = value; }
            get { return _categoryId; }
        }

        List<LiveMessageItem> _lstItem = new List<LiveMessageItem>();
        public LiveMessageItem[] CategoryItems
        {
            set { _lstItem.AddRange(value); }
            get { return _lstItem.ToArray(); }
        }
    }

    public partial class MessageGridControl : UserControl
    {
        public event EventHandler<CategoryItemEventArgs> OnCategoryItemChanged = null;
        GridHitInfo hitInfo = null;

        public MessageGridControl()
        {
            InitializeComponent();
            if (!DesignMode)
                gridControl.ContextMenu = null;
        }

        public BaseView View
        {
            set
            {
                this.gridControl.MainView = value;
            }
            get
            {
                return this.gridControl.MainView;
            }
        }

        public List<LiveMessageItem> DataSource
        {
            set
            {
                if (value != null)
                {
                    if (this.gridControl.DataSource != value)
                    {
                        this.gridControl.DataSource = value;

                        CategoryItemChanged();
                    }
                }
            }
            get
            {
                return (this.gridControl.DataSource as List<LiveMessageItem>);
            }
        }

        public BaseView ListView
        {
            get
            {
                return gridView;
            }
        }

        public BaseView CardView
        {
            get
            {
                return cardView;
            }
        }

        private string _categoryID;
        public string CategoryID
        {
            set
            {
                _categoryID = value;
            }
            get
            {
                return _categoryID;
            }
        }

        public List<LiveMessageItem> SelectDataRow
        {
            get
            {
                List<LiveMessageItem> selectDataRow = new List<LiveMessageItem>();

                if (View == ListView)
                {
                    if (gridView.GetSelectedRows().Length > 0)
                    {
                        for (int i = 0; i < gridView.GetSelectedRows().Length; i++)
                            selectDataRow.Add(gridView.GetRow(i) as LiveMessageItem);
                    }
                }
                else
                {
                    if (cardView.GetSelectedRows().Length > 0)
                    {
                        for (int i = 0; i < cardView.GetSelectedRows().Length; i++)
                            selectDataRow.Add(cardView.GetRow(i) as LiveMessageItem);
                    }
                }

                return selectDataRow;
            }
        }

        void MessageGridControl_Load(object sender, System.EventArgs e)
        {
            RefreshDataSource();
            InitGrid();
        }

        private void InitGrid()
        {
            gridView.FocusedColumn = gridView.Columns[0];
            gridView.FocusedRowHandle = 1;

            gridView.OptionsSelection.EnableAppearanceFocusedRow = true;
            gridView.OptionsSelection.InvertSelection = false;
            gridView.OptionsSelection.EnableAppearanceFocusedCell = false;
            gridView.FocusRectStyle = DrawFocusRectStyle.RowFocus;
            SetFocusedColumnAppearance(null, gridView.FocusedColumn);
            gridControl.Focus();
        }
        public void RefreshDataSource()
        {
            this.gridControl.RefreshDataSource();
        }

        void gridControl_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            hitInfo = gridView.CalcHitInfo(new Point(e.X, e.Y));
            if (hitInfo.RowHandle < 0) hitInfo = null;
        }

        void gridControl_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left) return;
            if (gridControl.MainView == cardView)
            {
                if (cardView.FocusedRowHandle < 0)
                    return;
                var row = cardView.GetRow(cardView.FocusedRowHandle);
                gridControl.DoDragDrop(new object[] { cardView.FocusedRowHandle, row }, DragDropEffects.All);
            }
            else
            {
                if (hitInfo == null) return;

                Rectangle dragRect = new Rectangle(new Point(
                    hitInfo.HitPoint.X - SystemInformation.DragSize.Width / 2,
                    hitInfo.HitPoint.Y - SystemInformation.DragSize.Height / 2), SystemInformation.DragSize);
                if (!dragRect.Contains(new Point(e.X, e.Y)))
                {
                    if (hitInfo.InRow)
                    {
                        gridControl.DoDragDrop(new object[] { hitInfo.RowHandle, gridControl.Views[0].GetRow(hitInfo.RowHandle) }, DragDropEffects.All);
                    }
                }
            }

        }

        void cardView_SelectionChanged(object sender, DevExpress.Data.SelectionChangedEventArgs e)
        {

        }

        private void SetFocusedColumnAppearance(DevExpress.XtraGrid.Columns.GridColumn col1, DevExpress.XtraGrid.Columns.GridColumn col2)
        {

            if (col1 != null) col1.AppearanceCell.Reset();
            if (col2 != null)
            //{
            //    col2.AppearanceCell.BackColor = SystemColors.Highlight;
            //col2.AppearanceCell.ForeColor = SystemColors.HighlightText;
            //}
            ////else
                col2.AppearanceCell.Reset();
        }

        /* private void SetFocusedColumnAppearance(DevExpress.XtraGrid.Columns.GridColumn col1, DevExpress.XtraGrid.Columns.GridColumn col2)
         {

             if (col1 != null) col1.AppearanceCell.Reset();
             if (col2 != null)
                 //if (3.Equals(radioGroup1.EditValue))
                 //{
                 col2.AppearanceCell.BackColor = SystemColors.Highlight;
             col2.AppearanceCell.ForeColor = SystemColors.HighlightText;
             //}
             //else
             //    col2.AppearanceCell.Reset();
         }*/

        void gridView_FocusedColumnChanged(object sender, DevExpress.XtraGrid.Views.Base.FocusedColumnChangedEventArgs e)
        {
            SetFocusedColumnAppearance(e.PrevFocusedColumn, e.FocusedColumn);
        }

        void gridView_FocusedRowChanged(object sender, DevExpress.XtraGrid.Views.Base.FocusedRowChangedEventArgs e)
        {

        }

        private void gridControl_DragDrop(object sender, DragEventArgs e)
        {
            TreeListMultiSelection selectionItem = e.Data.GetData(typeof(TreeListMultiSelection)) as TreeListMultiSelection;

            bool changed = false;
            foreach (Library.LibraryNode item in selectionItem)
            {
                MemoryLibraryItem tmpItem = item.Tag as MemoryLibraryItem;
                LiveMessageItem libItem = new LiveMessageItem();
                libItem.Name = tmpItem.Name;
                libItem.Target = tmpItem;
                libItem.Id = tmpItem.Id;
                if (CategoryControl.CheckSameMemoryLibraryItem(libItem, DataSource))
                {
                    DataSource.Add(libItem);
                    RefreshDataSource();
                    changed = true;
                }
            }

            if (changed)
                CategoryItemChanged();
        }

        private void gridControl_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(typeof(TreeListMultiSelection)))
            {
                e.Effect = DragDropEffects.Copy;
            }
        }

        public void CategoryItemChanged()
        {
            if (OnCategoryItemChanged != null)
            {
                CategoryItemEventArgs args = new CategoryItemEventArgs();
                args.CategoryId = CategoryID;
                args.CategoryItems = DataSource.ToArray();
                OnCategoryItemChanged(this, args);
            }
        }

    }
}
