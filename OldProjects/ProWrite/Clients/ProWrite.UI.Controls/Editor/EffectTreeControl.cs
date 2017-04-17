//---------------------------------------------------------------------
//
// File: EffectTreeControl.cs
//
// Description:
// User Control of effect tree 
//
// Author: Kevin 2008-6-30
//
// Modify History:
//      Kevin 2008-7-1 实现该控件并挂接在Editor 中
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using DevExpress.XtraTreeList;
using DevExpress.XtraTreeList.Nodes;
using ProWrite.Core;
using ProWrite.Entity.DES;
using ProWrite.Resources;

namespace ProWrite.UI.Controls.Editor
{
    public partial class EffectTreeControl : TreeList
    {
        /// <summary>
        /// drag box size
        /// </summary>
        private Rectangle dragBoxFromMouseDown = Rectangle.Empty;

        public EffectTreeControl()
        {

            if (!DesignMode)
                InitializationEffectTreeList();
            RegisterHelp();
        }

        private void RegisterHelp()
        {
            this.SetShowHelp(HelpNavigator.Topic, Resource.Helps.EditorEffect);
        }

        /// <summary>
        /// init effect tree
        /// </summary>
        private void InitializationEffectTreeList()
		{
			//new EffectHelper2();

			ImageList imageList2 = new ImageList();
			imageList2.TransparentColor = Color.Magenta;
			imageList2.Images.Add(Resource.GetImage(Resource.Images.EnterEffect16));
			imageList2.Images.Add(Resource.GetImage(Resource.Images.PlayEffect16));
			imageList2.Images.Add(Resource.GetImage(Resource.Images.ExitEffect16));

            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Bijou));//3
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Blackhole));//4
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Bounce));//5
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Coalesce));//6
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Fade));//7
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Filter));//8
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Flash));//9
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Green));//10
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Interleave));//11
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Line));//12
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Multiwipe));//13
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Questionmark));//14
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Radar));//15
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Rain));//16
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Red));//17
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Rss));//18
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Slot));//19
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Snow));//20
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Sparkle));//21
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Venitian));//22
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Wipe));//23
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Wraparound));//24
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Yellow));//25
            imageList2.Images.Add(Resource.GetIcon(Resource.Icons.Slide));//26


            Columns.AddField("Name").Visible = true;

            //LookAndFeel.SkinName = Resources.Resource.GetString(Resources.Resource.Strings.SkinName);
			LookAndFeel.UseDefaultLookAndFeel = true;
			Dock = DockStyle.Fill;
            OptionsBehavior.AutoChangeParent = false;
            OptionsBehavior.AutoNodeHeight = false;
            OptionsBehavior.AutoSelectAllInEditor = false;
            OptionsBehavior.CloseEditorOnLostFocus = false;
            OptionsBehavior.Editable = false;
            OptionsBehavior.ExpandNodeOnDrag = false;
            OptionsBehavior.ImmediateEditor = false;
            OptionsBehavior.KeepSelectedOnClick = false;
            OptionsBehavior.MoveOnEdit = false;
            OptionsBehavior.ResizeNodes = false;
            OptionsBehavior.SmartMouseHover = false;
            OptionsView.ShowButtons = false;
            OptionsView.ShowColumns = false;
            OptionsView.ShowFocusedFrame = false;
            OptionsView.ShowHorzLines = false;
            OptionsView.ShowRoot = false;
            OptionsView.ShowVertLines = false;
            OptionsView.ShowIndicator = false;
			TreeLevelWidth = 12;
			SelectImageList = imageList2;

			TreeListNode node = null;
			TreeListNode subNode = null;
            var _name = "";
            int index = 0;

			List<EffectCategory> effectCategory = EffectCategory.EffectGroups;
			foreach (EffectCategory cat in effectCategory)
			{
				node = AppendNode(new object[] {cat.Name}, null);
				if (cat.Name == EffectType.Entry)
					node.ImageIndex = 0;
				else if (cat.Name == EffectType.Emphasis)
					node.ImageIndex = 1;
				else
					node.ImageIndex = 2;

                foreach (LayerEffect item in cat.Effects)
				{
					subNode = AppendNode(new object[] {item.Name}, node, item);
                    _name = item.Name;
                    if (_name == "Bijou")
                        index = 3;
                    else if (_name == "BlackHole")
                        index = 4;
                    else if (_name == "Bounce")
                        index = 5;
                    else if (_name == "Coalesce")
                        index = 6;
                    else if (_name == "Fade")
                        index = 7;
                    else if (_name == "Filter")
                        index = 8;
                    else if (_name == "Flash")
                        index = 9;
                    else if (_name == "Interleave")
                        index = 11;
                    else if (_name == "Line")
                        index = 12;
                    else if (_name == "MultiWipe")
                        index = 13;
                    else if (_name == "Radar")
                        index = 15;
                    else if (_name == "Rain")
                        index = 16;
                    else if (_name == "Slot")
                        index = 19;
                    else if (_name == "Snow")
                        index = 20;
                    else if (_name == "Sparkle")
                        index = 21;
                    else if(_name =="Venetian")
                        index = 22;
                    else if (_name == "Wipe")
                        index = 23;
                    else if (_name == "WrapAround")
                        index = 24;
                    else if (_name == "Slide")
                        index = 26;
                    else
                        index = node.ImageIndex;

					subNode.ImageIndex = index; 
				}
			}
            
			BestFitColumns();
			ExpandAll();
		}


        /// <summary>
        /// effect tree mouse down event
        /// </summary>
        /// <param name="e"></param>
        protected override void OnMouseDown(MouseEventArgs e)
        {
            //base.OnMouseDown(e);
            if (e.Button == MouseButtons.Left)
            {
                Size dragSize = SystemInformation.DragSize;

                dragBoxFromMouseDown = new Rectangle(new Point(e.X - (dragSize.Width / 2),
                                                               e.Y - (dragSize.Height / 2)), dragSize);
            }
        }

        /// <summary>
        /// effect tree mouse up event
        /// </summary>
        /// <param name="e"></param>
        protected override void OnMouseUp(MouseEventArgs e)
        {
            base.OnMouseUp(e);
            dragBoxFromMouseDown = Rectangle.Empty;
        }

        /// <summary>
        /// effect tree mouse move event
        /// </summary>
        /// <param name="e"></param>
        protected override void OnMouseMove(MouseEventArgs e)
        {
            base.OnMouseMove(e);
            if ((e.Button & MouseButtons.Left) == MouseButtons.Left)
            {
                if (dragBoxFromMouseDown != Rectangle.Empty
                    && !dragBoxFromMouseDown.Contains(e.X, e.Y))
                {
                    TreeListNode node = CalcHitInfo(e.Location).Node;
                    if (node != null && node.Tag != null)
                        DoDragDrop(node.Tag, DragDropEffects.Copy);
                }
            }
        }


    }
}