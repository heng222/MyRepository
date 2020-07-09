using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace Products.Persistence
{
    /// <summary>
    /// 节点选择对话框
    /// </summary>
    partial class NodeSelectionForm : Form
    {
        /// <summary>
        /// 构造函数。
        /// </summary>
        /// <param name="dataSource">数据源。</param>
        public NodeSelectionForm(Dictionary<uint, string> dataSource)
        {
            InitializeComponent();

            cbxNodeNames.DisplayMember = "Name";
            cbxNodeNames.ValueMember = "Code";
            cbxNodeNames.DataSource = dataSource.Select(p => new { Code = p.Key, Name = p.Value }).ToList();
            cbxNodeNames.SelectedIndex = 0;
        }

        /// <summary>
        /// 获取选择的节点编号。
        /// </summary>
        public uint NodeCode { get { return Convert.ToUInt32(cbxNodeNames.SelectedValue); } }
    }
}
