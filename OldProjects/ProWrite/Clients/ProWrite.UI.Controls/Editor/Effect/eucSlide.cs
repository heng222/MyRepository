//---------------------------------------------------------------------
//
// File: eucSlide.cs
//
// Description:
//      Slide set UserControl
//
// Author: Jerry Xu
// Date  : 2009-2-19
//
//Modify History:
//      Jerry Xu 2009-2-12 Update Event:MessageBtn_DragDrop(object sender, DragEventArgs e)
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ProWrite.Entity.DES.Effect;

namespace ProWrite.UI.Controls.Editor.Effect
{
    public partial class eucSlide : eucBase<EffectSlide>
    {
        public eucSlide()
        {
            InitializeComponent();
        }

        protected override void DoBind()
        {
            var directions = Enum.GetValues(typeof(SlideDirection));
            foreach (SlideDirection item in directions)
            {
                this.ddlDirection.Properties.Items.Add(item);
            }
            this.ddlDirection.SelectedItem = _effect.Direction;
        }

        protected override void DoSave()
        {
            if (this.ddlDirection.SelectedItem != null)
            {
                _effect.Direction = (SlideDirection) ddlDirection.SelectedItem;
            }
        }
    }
}
