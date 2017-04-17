using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Settings;
using ProWrite.Entity.Dashboard;
using ProWrite.UI.Controls.Common;

namespace ProWrite.UI.Controls.Options
{
    public partial class OptionDialog : Form
    {
        private bool haveParmeter;
        public bool HaveParmeter
        {
            get { return haveParmeter; }
            set { haveParmeter = value; }
        }

        private void RegisterHelp()
        {
            this.SetShowHelp(HelpNavigator.Topic, Resources.Resource.Helps.DashboardSettingDefault);
        }

        private static TemplateGroup _currentGroup;

        public static TemplateGroup CurrentGroup
        {
            get { return _currentGroup; }
        }

        private void Init()
        {
            if (Tree.Root != null)
                Panel.Controls.Add(Tree.Root.View);
            BindCombox();
        }

        private void BindCombox()
        {
            ddlTemplate.Properties.Items.Clear();
            TemplateGroups groups = DataGate.Project.Templates;
            if (groups != null && groups.Count > 0)
            {
                this.ddlTemplate.Properties.Items.AddRange(groups.ToArray());
                ddlTemplate.Text = TemplateGroup.Default.Name;
                btnDelete.Enabled = false;
                btnActive.Enabled = false;
                //ddlTemplate.SelectedIndex = 0;
            }

            //instance.Tree.TemplateGroup = TemplateGroup.Current;
        }

        public OptionDialog(TemplateGroup templateGroup)
        {
            InitializeComponent();
            if (!DesignMode)
            {
                if (templateGroup != null)
                {
                    Tree.TemplateGroup = templateGroup;
                    BindCombox();
                    ddlTemplate.SelectedItem = templateGroup;
                    _currentGroup = templateGroup;
                }
                else
                {
                    Tree.TemplateGroup = TemplateGroup.Default;
                    ddlTemplate.SelectedItem = TemplateGroup.Default;
                }

                Init();
                RegisterHelp();

                lblTemplate.Text = "Template";
                if (groupControl1.Controls.Count == 5)
                    groupControl1.Controls[4].Visible = false;
                ddlTemplate.Visible = true;
                btnAdd.Visible = true;
                btnDelete.Visible = true;
                btnActive.Visible = true;
            }
        }

        private void NewTemplate()
        {
            string name = InputDialog.GetInputValue("New Template");
            
            if (string.IsNullOrEmpty(name))
                return;
            if (name.Trim() == "")
            {
                MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.TemplateEmpty));
                return;
            }
            bool isRepeat = false;
            TemplateGroups groups = DataGate.Project.Templates;
            foreach (TemplateGroup template in groups)
            {
                if (template.Name == name)
                {
                    isRepeat = true;
                }
            }
            if (isRepeat)
            {
                MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.TemplateRepeat));
                return;
            }
            TemplateGroup group = new TemplateGroup();
            group.Name = name;

            DataGate.Project.Templates.Add(group);
            BindCombox();
            ddlTemplate.SelectedItem = group;
            _currentGroup = group;
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            NewTemplate();
        }

        private void Tree_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {

        }

        void Tree_BeforeSelect(object sender, System.Windows.Forms.TreeViewCancelEventArgs e)
        {
           
        }

        private void Tree_AfterSelect(object sender, TreeViewEventArgs e)
        {
            if (Tree.SelectedNode != null
                && Panel.Controls.Count>0)
            {
                var prev = Panel.Controls[0] as ViewBase;
                if (prev != null)
                {
                    prev.UpdateData();
                }

                Panel.Controls.Clear();
                var node = Tree.SelectedNode as OptionNode;
                if (node.View == null)
                {
                    try
                    {
                        node.View = Activator.CreateInstance(node.ViewType) as ViewBase;
                        node.View.Dock = DockStyle.Fill;
                        Panel.Controls.Add(node.View);
                    }
                    catch
                    {
                    }
                }

            }
        }

        private void ddlTemplate_SelectedIndexChanged(object sender, EventArgs e)
        {
            btnDelete.Enabled = true;
            btnActive.Enabled = true;
            Tree.TemplateGroup = ddlTemplate.SelectedItem as TemplateGroup;
            //instance.grid.SelectedObject = Tree.TemplateGroup;
            if (Tree.TemplateGroup != null && Tree.TemplateGroup.IsDefault)
            {
                btnDelete.Enabled = false;
                btnActive.Enabled = false;
            }
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {

            int countSigns = SignGroupInfo._allSigns.Count;
            if (countSigns > 0)
            {
                for (int i = 0; i < countSigns; i++)
                {
                    if (SignGroupInfo._allSigns[i].TemplateName == Tree.TemplateGroup.Name)
                    {
                        MsgBox.Warning(Resources.Resource.GetString(Resources.Resource.Strings.SettingDefaultHasUsed));
                        return;
                    }
                }
            }
            if (MsgBox.Confirm(Resources.Resource.GetString(Resources.Resource.Strings.ConfirmDeleteItem)) == DialogResult.Yes)
            {
                DataGate.Project.Templates.Remove(Tree.TemplateGroup);
                BindCombox();
                Tree.TemplateGroup = TemplateGroup.Default;
            }
        }

        private void btnActive_Click(object sender, EventArgs e)
        {
            //TemplateGroup.Current = ddlTemplate.SelectedItem as TemplateGroup;
            if (ddlTemplate.SelectedItem == null)
                return;
            TemplateGroup temp = (ddlTemplate.SelectedItem as TemplateGroup).Copy();
            if (temp == null)
                return;
            TemplateGroup.Default.Sign = temp.Sign;
            TemplateGroup.Default.Message = temp.Message;
            TemplateGroup.Default.Playlist = temp.Playlist;
            TemplateGroup.Default.Scheduler = temp.Scheduler;
            MsgBox.Information(Resources.Resource.GetString(Resources.Resource.Strings.Savesuccess));
            BindCombox();
            ddlTemplate.SelectedItem = TemplateGroup.Default;
            Tree.TemplateGroup = ddlTemplate.SelectedItem as TemplateGroup;
            //instance.grid.SelectedObject = Tree.TemplateGroup;
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            //var selectedObj = grid.SelectedObject as IErrorInfo;
            //if (selectedObj != null && selectedObj.Error != null)
            //    selectedObj.SetProperty(selectedObj.Error.Name, selectedObj.Error.OldValue);
            this.Close();
        }

        private void SettingDialog_DoubleClick(object sender, EventArgs e)
        {
            //DataPassThrough dataPass = new DataPassThrough();
            //dataPass.ShowModalDialog(false);
        }


    }
}
