using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.Settings;
using System.Reflection;
using ProWrite.UI.Controls.Options.Views;
using System.ComponentModel;

namespace ProWrite.UI.Controls.Options
{
    public class OptionNode:TreeNode
    {
        public OptionNode(TemplateInfo item)
        {
            Text = item.Caption();//item.Type.ToString();
            Tag = item;
        }

        public OptionNode(TemplateGroup item)
        {
            Text = item.Name;
            Tag = item;
        }

        public TemplateInfo Template
        {
            get { return Tag as TemplateInfo; }
            set { Tag = value; }
        }

        public Type ViewType
        {
            get;
            internal set;
        }

        public ViewBase View { get; internal set; } 
    }

    public class OptionTree : TreeView
    {
        TemplateGroup _group;
        public OptionTree()
        {
        }

        public OptionNode Root { get; private set; }

        [Browsable(false)]
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
                    OptionNode node = new OptionNode(_group);
                    node.Text = _group.Name;
                    node.Tag = _group;
                    node.ViewType = PopulateViewType(_group.View());
                    if (node.ViewType != null)
                    {
                        try
                        {
                            node.View = Activator.CreateInstance(node.ViewType) as ViewBase;
                            Nodes.Add(node);
                            Root = node;

                            Populate(node, _group);
                        }
                        catch
                        {
                        }
                    }
                }

                ExpandAll();
            }
        }

        private void Populate(OptionNode parentNode,IEnumerable<TemplateInfo> data)
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

                var viewType = PopulateViewType(it.Current.View());
                if (viewType != null)
                {
                    OptionNode node = new OptionNode(it.Current);
                    node.ViewType = viewType;

                    if (parentNode == null)
                        Nodes.Add(node);
                    else
                        parentNode.Nodes.Add(node);
                    Populate(node, it.Current);
                }
                
            }
        }

        private static Type PopulateViewType(string view)
        {
            Check.Require(view, "view", Check.NotNullOrEmpty);

            try
            {
                return Assembly.GetExecutingAssembly().GetType(view);
            }
            catch
            {
                return null;
            }
        }
    }
}
