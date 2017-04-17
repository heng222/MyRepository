using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.UI.Controls.Common;
using ProWrite.Entity.DataManager;
using DevExpress.XtraGrid.Views.Grid;
using DevExpress.XtraEditors;
using ProWrite.Entity;
using ProWrite.Entity.Shape;
using ProWrite.Entity.Library;
using ProWrite.Core;

namespace ProWrite.UI.Controls.Settings
{
    public partial class DataPassThrough : XtraForm
    {
        //add by Michael
        private ShapeBase SourceShape = null;
        private ShapeType SourceType = ShapeType.Default;

        public DataPassThrough()
        {
            InitializeComponent();
            InitData();
        }

        public DataPassThrough(ShapeBase shape, ShapeType type)
        {
            SourceShape = shape;
            SourceType = type;
            InitializeComponent();
            InitData();
        }

        protected void InitData()
        {
            gridControl1.ShowOnlyPredefinedDetails = true;
            gridControl1.DataSource = DataGate.Project.DataSources;
            repositoryItemComboBox1.Items.AddRange(Enum.GetValues(typeof(DataSourceType)));
        }

        private void chEdit_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void sbStart_Click(object sender, EventArgs e)
        {

        }

        private void gridControl1_EmbeddedNavigator_ButtonClick(object sender, DevExpress.XtraEditors.NavigatorButtonClickEventArgs e)
        {

        }

        void gridView1_InitNewRow(object sender, DevExpress.XtraGrid.Views.Grid.InitNewRowEventArgs e)
        {
            DataRow row = gridView1.GetDataRow(e.RowHandle);
            row["Name"] = 1;
            row["Source"] = 0;
            row["PassThrough"] = 0;
            row["Note"] = 99999;
        }

        void gridView1_Layout(object sender, System.EventArgs e)
        {
            //updateLayout = true;
            //icbNewItemRow.EditValue = gridView1.OptionsView.NewItemRowPosition;
            //ceMultiSelect.Checked = gridView1.OptionsSelection.MultiSelect;
            SetPosition();
            //updateLayout = false;
        }

        void gridView1_SelectionChanged(object sender, DevExpress.Data.SelectionChangedEventArgs e)
        {
            SetButtonEnabled();
        }

        void SetButtonEnabled()
        {
            //sbRecords.Enabled = gridView1.SelectedRowsCount > 0 && ceMultiSelect.Checked;
            //icbSelectMode.Enabled = ceMultiSelect.Checked;
        }

        void SetPosition()
        {
            if (gridView1.OptionsView.NewItemRowPosition == NewItemRowPosition.Bottom && gridView1.SortInfo.GroupCount == 0)
            {
                gridView1.FocusedRowHandle = gridView1.RowCount - 2;
                gridView1.MakeRowVisible(gridView1.FocusedRowHandle, false);
            }
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            DataPassThroughDetail item = new DataPassThroughDetail(null);
            item.ShowModalDialog();
            if (item.IsRefresh)
                InitData();
        }

        private void simpleButton1_Click(object sender, EventArgs e)
        {
            if (gridView1.GetFocusedRow() == null)
                return;
            DataItem current = new DataItem();
            current = (ProWrite.Entity.DataManager.DataItem)((gridView1.GetFocusedRow()));
            //string name=gridView1.GetDataRow(gridView1.FocusedRowHandle)[0].ToString();//.RowHandle)
            //foreach (DataItem dItem in DataGate.Project.DataSources)
            //{
            //    if (dItem.Name == name)
            //    {
            //        current = dItem;
            //    }
            //}
            if (current == null)
                return;
            //dataItem=gridView1.foc
            DataPassThroughDetail item = new DataPassThroughDetail(current);
            item.ShowModalDialog();
            if (item.IsRefresh)
                InitData();
        }

        private void simpleButton2_Click(object sender, EventArgs e)
        {
            if (gridView1.GetFocusedRow() == null)
                return;
            if (MsgBox.Confirm(Resources.Resource.GetString(Resources.Resource.Strings.ConfirmDeleteItem)) == DialogResult.No)
                return;
            DataItem current = new DataItem();
            current = (ProWrite.Entity.DataManager.DataItem)((gridView1.GetFocusedRow()));
            DataGate.Project.DataSources.Remove(current);
            InitData();
        }

        //add by Michael
        private void SetDataSource(string srcname)
        {
            if (SourceShape != null)
            {
                if (SourceType == ShapeType.DynamicText)
                {
                    (SourceShape as ShapeDynamicText).DataSource = srcname;
                    DataItem item = DataGate.Project.DataSources.GetByName(srcname);
                    if (item != null && item.SourceProvider != null)
                    {
                        (SourceShape as ShapeDynamicText).Text = item.SourceProvider.Content.ToString();
                    }
                    else
                    {
                        (SourceShape as ShapeDynamicText).Text = "Empty";
                    }
                }
                if (SourceType == ShapeType.DynamicVideo)
                {
                    (SourceShape as ShapeDynamicVideo).DataSource = srcname;
                }
            }
        }
    }
}
