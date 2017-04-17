using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Settings;

namespace ProWrite.UI.Controls.Settings
{
    public class SettingNode:TreeNode
    {
        public SettingNode(TemplateInfo item)
        {
            Text = item.ToString();//item.Type.ToString();
            Tag = item;
        }

        public SettingNode(TemplateGroup item)
        {
            Text = item.Name;
            Tag = item;
        }

        public TemplateInfo Template
        {
            get { return Tag as TemplateInfo; }
            set { Tag = value; }
        }
    }

    public class SettingTree : TreeView
    {
        TemplateGroup _group;
        public SettingTree()
        {
        }

        public TemplateGroup TemplateGroup
        {
            get { return _group; }
            set
            {
                _group = value;
                Nodes.Clear();

                if (_group != null)
                {
                    //IEnumerator<TemplateInfo> it = _group.GetEnumerator();
                    //TreeNode node = new TreeNode();
                    SettingNode node = new SettingNode(_group);
                    node.Text = _group.Name;
                    node.Tag = _group;
                    Nodes.Add(node);
                    Populate(node, _group);
                }

                ExpandAll();
            }
        }

        private void Populate(SettingNode parentNode,IEnumerable<TemplateInfo> data)
        {
            if (data == null)
                return;

            IEnumerator<TemplateInfo> it = data.GetEnumerator();
            if (it == null)
                return;

            while (it.MoveNext())
            {
                if (it.Current == null)
                    continue;
                SettingNode node = new SettingNode(it.Current);
                if (parentNode == null)
                    Nodes.Add(node);
                else
                    parentNode.Nodes.Add(node);
                Populate(node,it.Current);
            }
        }
        
    }
}
