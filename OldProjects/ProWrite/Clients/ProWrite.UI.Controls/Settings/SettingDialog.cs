using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Settings;
using ProWrite.UI.Controls.Common;
using DevExpress.XtraBars.Docking;
using DevExpress.XtraEditors;
using ProWrite.Entity.Dashboard;
using ProWrite.Core;
using ProWrite.UI.Controls.Options;

namespace ProWrite.UI.Controls.Settings
{
    public partial class SettingDialog : XtraForm
    {
        private PropertyGridControl grid = new PropertyGridControl();
        private bool haveParmeter;
        public bool HaveParmeter
        {
            get { return haveParmeter; }
            set { haveParmeter = value; }
        }
        public SettingDialog()
        {
            InitializeComponent();
            if (!DesignMode)
                Init();
            RegisterHelp();
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
            
            Panel.Controls.Add(grid);
            BindCombox();

            //this.ddlTemplate
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

        private static readonly SettingDialog instance = new SettingDialog();
        
        public static void Display(TemplateGroup templateGroup)
        {
            Display(templateGroup, null);
        }

        public static void Display(TemplateGroup templateGroup,IWin32Window owner)
        {
            //Control gridContainer = new Control();
            //object preSelectedObj = ControlService.PropertyGrid.SelectedObject;
            //PropertyGridControl grid = new PropertyGridControl();
            instance.Tree.Nodes.Clear();
            instance.BindCombox();
            instance.grid.SelectedObject = null;
            if (templateGroup != null)
            {
                instance.Tree.TemplateGroup = templateGroup;
                instance.grid.SelectedObject = templateGroup;
                instance.grid.Dock = DockStyle.Fill;
                instance.grid.ScrollVisibility = DevExpress.XtraVerticalGrid.ScrollVisibility.Vertical;
                
                //instance.ddlTemplate.Text = templateGroup.Name;
                instance.BindCombox();
                instance.ddlTemplate.SelectedItem = templateGroup;
                SettingDialog._currentGroup = templateGroup;
            }
            else
            {
                instance.Tree.TemplateGroup = TemplateGroup.Default;
                instance.grid.SelectedObject = TemplateGroup.Default;
                instance.grid.Dock = DockStyle.Fill;
                instance.grid.ScrollVisibility = DevExpress.XtraVerticalGrid.ScrollVisibility.Vertical;
                instance.ddlTemplate.SelectedItem = TemplateGroup.Default;
            }
            instance.lblTemplate.Text = "Template";
            //TextBox txtSign = new TextBox();
            //txtSign.Text = sign.Name;
            //instance.groupControl1.Controls.Add(txtSign);
            //txtSign.Location = instance.ddlTemplate.Location;
            //if (instance.groupControl1.Controls.ContainsKey("txtSign"))
            if(instance.groupControl1.Controls.Count==5)
                instance.groupControl1.Controls[4].Visible = false;
            instance.ddlTemplate.Visible = true;
            instance.btnAdd.Visible = true;
            instance.btnDelete.Visible = true;
            instance.btnActive.Visible = true;
            
            instance.ShowModalDialog(false);



            //ControlService.PropertyGrid.Parent = gridContainer;
            //ControlService.PropertyGrid.SelectedObject = preSelectedObj;
        }

        public static void DisplaySign(SignInfo sign,IWin32Window owner)
        {
            //Control gridContainer = new Control();
            //object preSelectedObj = ControlService.PropertyGrid.SelectedObject;
            //PropertyGridControl grid = new PropertyGridControl();
            instance.Tree.Nodes.Clear();
            instance.grid.SelectedObject = null;
            if (sign != null)
            {
                instance.Tree.TemplateGroup = sign.Template;
                instance.grid.SelectedObject = sign.Template;
                instance.lblTemplate.Text = "Sign Name";
                if (instance.groupControl1.Controls.Count < 5)
                {
                    TextBox txtSign = new TextBox();
                    txtSign.Text = sign.Name;
                    txtSign.Enabled = false;
                    instance.groupControl1.Controls.Add(txtSign);
                    txtSign.Location = instance.ddlTemplate.Location;
                }
                else
                {
                    instance.groupControl1.Controls[4].Text = sign.Name;
                    instance.groupControl1.Controls[4].Visible = true;
                }
                instance.ddlTemplate.Visible = false;
                instance.btnAdd.Visible = false;
                instance.btnDelete.Visible = false;
                instance.btnActive.Visible = false;
                //instance.ddlTemplate.Text = templateGroup.Name;
                //instance.BindCombox();
                //instance.ddlTemplate.SelectedItem = sign.Template;
                //SettingDialog._currentGroup = sign.Template;
            }
            
            instance.ShowModalDialog(false);



            //ControlService.PropertyGrid.Parent = gridContainer;
            //ControlService.PropertyGrid.SelectedObject = preSelectedObj;
        }
        private void NewTemplate()
        {
            string name =  InputDialog.GetInputValue("New Template");
            //InputDialog dlg = new InputDialog("New Template");
            
            //DialogResult result = dlg.ShowModalDialog();
            //if (result == DialogResult.OK)
            //{
            //    name=dlg.Info;
            // }
            //else
                //return null;
            
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
            //Tree.TemplateGroup = group;
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

        private void Tree_AfterSelect(object sender, TreeViewEventArgs e)
        {
            if (Tree.SelectedNode != null)
                grid.SelectedObject = Tree.SelectedNode.Tag;
        }
        
        private void ddlTemplate_SelectedIndexChanged(object sender, EventArgs e)
        {
            btnDelete.Enabled = true;
            btnActive.Enabled = true;
            Tree.TemplateGroup = ddlTemplate.SelectedItem as TemplateGroup;
            instance.grid.SelectedObject = Tree.TemplateGroup;
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
                instance.Tree.TemplateGroup = TemplateGroup.Default;
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
            instance.grid.SelectedObject = Tree.TemplateGroup;
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

        private void panelControl1_DoubleClick(object sender, EventArgs e)
        {
            OptionDialog d = new OptionDialog(TemplateGroup.Default);
            d.ShowModalDialog();
        }


    }
}