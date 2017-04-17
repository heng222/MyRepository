/*
 * Name: ImageButtonDesigner.cs
 * Create By:  Andy
 * Create Date:  2008.05.28
 * Description:  
 * 
 * 
 * Revision History
 * ----------------------------------------------------------------------------------------------------------
 * Author         	Date                Version		      Detail
 * ----------------------------------------------------------------------------------------------------------
 * Andy 		    2008.05.28          1.0		          
 */
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Windows.Forms.Design;
using System.Drawing;

namespace ProWrite.UI.Controls.Designer
{
    /// <summary>
    /// The designer of ImageButton
    /// </summary>
    public class ImageButtonDesigner : ControlDesigner
    {
        /// <summary>
        /// Paint adornments
        /// </summary>
        /// <param name="pe"></param>
        protected override void OnPaintAdornments ( PaintEventArgs pe )
        {
            /*
             * if the NormalImage property is not set, draw a border on the button.
             */
            ImageButton button = Control as ImageButton;
            if ( button != null && button.NormalImage == null )
            {
                Rectangle rect = pe.ClipRectangle;
                rect.Width--;
                rect.Height--;
                pe.Graphics.DrawRectangle ( Pens.Gray, rect );
            }
        }
    }
}
