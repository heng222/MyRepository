using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsApplication
{
    public partial class CtrlDataGridViewDemo : UserControl
    {
        class DispatchPlan
        {
            public int GroupNo { get; set; }
            public string Description { get; set; }
        }

        private List<DispatchPlan> _dataSrc;

        public CtrlDataGridViewDemo()
        {
            this.Dock = DockStyle.Fill;
            InitializeComponent();

            Initialize1();
        }

        private void Initialize1()
        {
            _dataSrc = new List<DispatchPlan>() 
                {
                    new DispatchPlan(){ GroupNo = 1, Description = "111"},
                    new DispatchPlan(){ GroupNo = 2, Description = "222"},
                    new DispatchPlan(){ GroupNo = 2},
                };
            this.dataGridView1.DataSource = _dataSrc;

            dataGridView1.Columns[0].HeaderText = "车组号";
            dataGridView1.Columns[1].HeaderText = "描述";
        }

        private void Initialze2()
        {
            // Columns
            this.dataGridView1.ColumnCount = 2;
            this.dataGridView1.Columns[0].Name = "第1列";
            this.dataGridView1.Columns[0].Tag = new List<string>() { "text1", "text2" };
            this.dataGridView1.Columns[1].Name = "第2列";

            // Rows
            this.dataGridView1.RowCount = 3;
            this.dataGridView1.Rows[0].HeaderCell.Value = "第1行";
            this.dataGridView1.Rows[1].HeaderCell.Value = "第2行";
            this.dataGridView1.Rows[2].HeaderCell.Value = "第3行";
        }

        private void dataGridView1_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            try
            {
                if (0 == e.ColumnIndex)
                {
                    e.Value = string.Format("No {0}", e.Value);
                }
                else if(1 == e.ColumnIndex)
                {
                    if (e.Value == null) e.Value = "N/A";
                }
            }
            catch (System.Exception /*ex*/)
            {
            	
            }
        }

        private void saveSToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }
    }
}
