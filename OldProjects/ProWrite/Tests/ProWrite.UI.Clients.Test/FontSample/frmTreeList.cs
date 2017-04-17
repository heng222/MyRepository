using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using DevExpress.XtraTreeList.Nodes;
using DevExpress.XtraTreeList;

namespace ProWrite.UI.Clients.Test.FontSample
{
    public partial class frmTreeList : Form
    {
        #region Variant define
        TreeListNode _node;
        private Point _pMouse;
        #endregion


        public frmTreeList()
        {
            InitializeComponent();
            if (!DesignMode)
                Init();
        }

        private void Init()
        {
            //this.imgEdit.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            //new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Close,"aa")});
            
            //this.imgEdit.Buttons.AddRange(new DevExpress.XtraEditors.Controls.EditorButton[] {
            //new DevExpress.XtraEditors.Controls.EditorButton(DevExpress.XtraEditors.Controls.ButtonPredefines.Close,"aa")});
            //this.imgEdit.Appearance.TextOptions.Assign(DevExpress.Utils.TextOptions.HorzAlignmentToStringAlignment);
            //this.imgEdit.Appearance.
            //this.imgEdit.Buttons[0].Image = imageList1.Images[0];
            //this.imgEdit.Buttons[0].Caption = "bb";
            //this.imgEdit.Name = "imgEdit";
            //this.imgEdit.TextEditStyle = DevExpress.XtraEditors.Controls.TextEditStyles.Standard;
            //this.imgEdit.

            label1.Buttons[0].Caption = "bbb";
            label1.Buttons[0].Image = imageList1.Images[0];


            this.tlGroup.BeginUnboundLoad();
            this.tlGroup.AppendNode(new object[] {
            true,
            "McDonalds",
            "Message",
            "00.05.00"}, -1);
            this.tlGroup.AppendNode(new object[] {
            true,
            "Coke Zero",
            "Message",
            "00.05.00"}, -1);
            this.tlGroup.AppendNode(new object[] {
            true,
            "Sprite",
            "Message",
            "00.05.00"}, -1);
            this.tlGroup.AppendNode(new object[] {
            false,
            "Subway",
            "Message",
            "00.05.00"}, -1);
            this.tlGroup.AppendNode(new object[] {
            false,
            "Sears",
            "Message",
            "00.05.00"}, -1);
            this.tlGroup.AppendNode(new object[] {
            true,
            "Red Letters",
            "Message",
            "00.05.00"}, -1);
            this.tlGroup.AppendNode(new object[] {
            true,
            "Al\'s Toy Barn",
            "Message",
            "00.05.00"}, -1);
            this.tlGroup.AppendNode(new object[] {
            true,
            "Dharma",
            "Message",
            "00.05.00"}, -1);
            this.tlGroup.AppendNode(new object[] {
            true,
            "CTU",
            "Message",
            "00.05.00"}, -1);
            this.tlGroup.EndUnboundLoad();
        }

        /// <summary>
        /// Function: Set current node state
        /// Author  : Jerry Xu
        /// Date    : 2008-7-13
        /// </summary>
        /// <param name="node">TreeListNode:message info</param>
        /// <param name="check">bool</param>
        private void SetCheckedNode(TreeListNode node, bool check)
        {
            tlGroup.FocusedNode = node;
            tlGroup.BeginUpdate();
            node["IsActive"] = check;
        }

        private void tlGroup_MouseDown(object sender, MouseEventArgs e)
        {
            _pMouse = new Point(e.X, e.Y);
            //Get node info by mouse point 
            TreeListHitInfo hInfo = tlGroup.CalcHitInfo(new Point(e.X, e.Y));
            if (e.Button == MouseButtons.Left)
            {
                //When click the active column£¬change active state
                if (hInfo.HitInfoType == HitInfoType.Cell && hInfo.Column.Caption == "ACTIVE")
                {
                    //hInfo.Column.c
                    TreeListNode node = hInfo.Node;
                    SetCheckedNode(node, !(bool)(node["IsActive"]));
                }
                else
                {
                    return;
                }
            }
        }

        private void tlGroup_FocusedNodeChanged(object sender, FocusedNodeChangedEventArgs e)
        {

        }
    }
}