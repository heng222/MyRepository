using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraEditors.Repository;
using DevExpress.XtraVerticalGrid;
using DevExpress.XtraEditors.Popup;
using ProWrite.UI.Controls.Editor;
using System.Diagnostics;
using System.Reflection;
using System.Collections;
//using RepositoryItemFontEdit = ProWrite.UI.Controls.Editor.RepositoryItemFontEdit;
using DevExpress.XtraVerticalGrid.Rows;
using ProWrite.Core.Validation;
using ProWrite.Core;
using ProWrite.Resources;
using ProWrite.Entity.Settings;
using System.Drawing;

namespace ProWrite.UI.Controls
{
    public class PropertyGridControl : DevExpress.XtraVerticalGrid.PropertyGridControl
    {
        //private RepositoryItemFontEdit repositoryItemFontEdit1;
        public PropertyGridControl()
        {
            if (!DesignMode)
            {
                Dock = DockStyle.Fill;
                //LookAndFeel.SkinName = "Lilian";
                //LookAndFeel.UseDefaultLookAndFeel = false;

                //repositoryItemFontEdit1 = new RepositoryItemFontEdit();
                RepositoryItemPictureEdit repositoryItemPictureEdit1 = new RepositoryItemPictureEdit();
                repositoryItemPictureEdit1.CustomHeight = 64;
                repositoryItemPictureEdit1.ReadOnly = true;
                repositoryItemPictureEdit1.ShowMenu = false;
                repositoryItemPictureEdit1.SizeMode = DevExpress.XtraEditors.Controls.PictureSizeMode.Zoom;

                LineStyleRepositoryItemEdit lineStypeEdit = new LineStyleRepositoryItemEdit();
                RepositoryItemPWColorEdit colorEditor = new RepositoryItemPWColorEdit();
                //RepositoryItemColorEdit colorEditor = new RepositoryItemColorEdit();
                colorEditor.ShowSystemColors = false;

                this.DefaultEditors.AddRange(new DevExpress.XtraVerticalGrid.Rows.DefaultEditor[]
                                                {
                                                     new DevExpress.XtraVerticalGrid.Rows.DefaultEditor(typeof (System.Drawing.Image),
                                                                                                       repositoryItemPictureEdit1)
                                                    ,new DefaultEditor(typeof(DashKind),lineStypeEdit)
                                                    ,new DefaultEditor(typeof(Color),colorEditor)
                                                });

                RepositoryItems.AddRange(new RepositoryItem[]
				                         	{
				                         		repositoryItemPictureEdit1
                                                ,lineStypeEdit
                                                ,colorEditor
				                         	});
                AutoGenerateRows = true;

                TreeButtonStyle = TreeButtonStyle.TreeView;
                lineStypeEdit.SelectedIndexChanged += new EventHandler(lineStypeEdit_SelectedIndexChanged);
                CellValueChanged += new DevExpress.XtraVerticalGrid.Events.CellValueChangedEventHandler(PropertyGridControl_CellValueChanged);
            }
            RegisterHelp();
        }

        void lineStypeEdit_SelectedIndexChanged(object sender, EventArgs e)
        {
            ProWrite.Entity.Shape.ShapeLayer[] layers = MessageControl.Current.Layers;

            for (int i = 0; i < layers.Length; i++)
            {
                if (layers[i].Shape.Type == ShapeType.ShapeDraw)
                {
                    ProWrite.Entity.Shape.ShapeDraw shapes = layers[i].Shape as ProWrite.Entity.Shape.ShapeDraw;

                    for (int index = 0; index < shapes.Count; index++)
                    {
                        if (shapes.Childs[index].IsSelected)
                        {
                            ControlService.RefreshPropertyGrid(shapes.Childs[index]);
                            break;
                        }
                    }
                }
            }
        }

        private void RegisterHelp()
        {
            this.SetShowHelp(HelpNavigator.Topic, Resource.Helps.EditorProperty);
        }

        void PropertyGridControl_ValidatingEditor(object sender, DevExpress.XtraEditors.Controls.BaseContainerValidateEditorEventArgs e)
        {
            if (FocusedRow == null)
                return;

            ValidationContext ctx = DoValidate(FocusedRow.Properties.FieldName, e.Value);
            if (ctx != null && !ctx.Valid)
            {
                e.Valid = false;
                var propName = ctx.Property.Name;
                e.Value = ctx.Target.GetProperty(propName);
                e.ErrorText = ctx.ErrorMessage;
                var target = ctx.Target as IErrorInfo;
                target.Error = new ErrorProperty { Name = propName, OldValue = e.Value };
            }
        }

        ValidationContext DoValidate(string propertyName, object propertyValue)
        {
            Property propertyOwner = PropertyParser.Parse(this.SelectedObject, propertyName);
            if (propertyOwner == null
                || propertyOwner.Owner == null
                || string.IsNullOrEmpty(propertyOwner.Name))
                return null;

            PropertyInfo p = propertyOwner.Owner.GetType().GetProperty(propertyOwner.Name);
            if (p == null)
                return null;

            ValidationContext ctx = new ValidationContext(propertyOwner.Owner, p, propertyValue);

            ValidationService.Validate(ctx);
            return ctx;
        }

        void PropertyGridControl_CellValueChanged(object sender, DevExpress.XtraVerticalGrid.Events.CellValueChangedEventArgs e)
        {
            if (MessageControl.Current != null)
                MessageControl.Current.ShapeControl.Invalidate();

        }

        private class Property
        {
            public readonly string Name;
            public readonly object Owner;

            public Property(string name, object owner)
            {
                Name = name;
                Owner = owner;
            }
        }

        private class PropertyParser
        {
            public static Property Parse(object root, string propertyName)
            {
                try
                {
                    if (root == null)
                        return null;
                    string[] items = propertyName.Split('.');
                    if (items == null || items.Length < 1)
                        return null;
                    if (items.Length == 1)
                        return new Property(propertyName, root);

                    object target = root;


                    for (int i = 0; i < items.Length - 1; i++)
                    {
                        string name = null;
                        if (items[i].StartsWith("[") && items[i].EndsWith("]"))
                        {
                            int index = int.Parse(items[i].TrimStart('[').TrimEnd(']'));
                            name = items[i - 1];
                            PropertyInfo p = target.GetType().GetProperty(name);
                            target = p.GetValue(target, null);
                            if (target.GetType().IsArray)
                                target = (target as Array).GetValue(index);
                            else
                                target = (target as IList)[index];
                        }
                        else
                        {
                            int j = i + 1;
                            if (!(j < items.Length - 1
                                && items[j].StartsWith("[") && items[j].EndsWith("]"))) target = target.GetType().GetProperty(items[i]).GetValue(target, null);
                        }
                    }

                    return new Property(items[items.Length - 1], target);
                }
                catch
                {
                    return null;
                }
            }
        }

    }
}
