using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace ProWrite.UI.Controls.Settings
{
    public partial class LogFileForm : UserControl
    {
        public LogFileForm()
        {
            InitializeComponent();
        }

        private void Init()
        {
            //DataTable dt = new DataTable();
            //DataRow dr = new DataRow();
            //DataColumn dc1 = new DataColumn();
            //DataColumn dc2 = new DataColumn();
            //DataColumn dc3 = new DataColumn();
            //DataColumn dc4 = new DataColumn();
            //dt.Rows.Add(dr);
            //dt.Columns.Add(dc1);
            //dc.Caption = "MessageName";

        }

        private void MakeDataTableAndDisplay()
        {
            // Create new DataTable.
            DataTable table = new DataTable();

            // Declare DataColumn and DataRow variables.
            DataColumn column;
            DataRow row;

            // Create new DataColumn, set DataType, ColumnName
            // and add to DataTable.    
            column = new DataColumn();
            column.DataType = System.Type.GetType("System.Int32");
            column.ColumnName = "MessageName";
            table.Columns.Add(column);

            column = new DataColumn();
            column.DataType = Type.GetType("System.String");
            column.ColumnName = "Startdate";
            table.Columns.Add(column);

            column = new DataColumn();
            column.DataType = Type.GetType("System.String");
            column.ColumnName = "FinishDate";
            table.Columns.Add(column);

            column = new DataColumn();
            column.DataType = Type.GetType("System.String");
            column.ColumnName = "Errorcodes";
            table.Columns.Add(column);

            // Create new DataRow objects and add to DataTable.    
            for (int i = 0; i < 10; i++)
            {
                row = table.NewRow();
                row["Message"] ="Message"+ i;
                row["Startdate"] = "Startdate " + i;
                row["FinishDate"] = "FinishDate" + i;
                row["Errorcodes"] = "Errorcodes " + i;
                table.Rows.Add(row);
            }
            // Set to DataGrid.DataSource property to the table.
            this.gridMessage.DataSource = table;
        }

    }
}
