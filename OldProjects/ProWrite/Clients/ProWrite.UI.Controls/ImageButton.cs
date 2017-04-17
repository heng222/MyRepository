/*
 * Name: ImageButton.cs
 * Create By: Andy Lang
 * Create Date: 2008.05.27
 * Description: Use four shape to simulate a button's four state: Normal,Hover,Pressed and Disabled.
 * 
 * 
 * Revision History
 * ----------------------------------------------------------------------------------------------------------
 * Author         	Date                Version		      Detail
 * ----------------------------------------------------------------------------------------------------------
 * Andy Lang		2008.05.27          1.0		
 * Update history:
 *      Jerry Xu 2008-8-22 Update Disable
 *      Jerry Xu 2008-8-25 Update mouse event:if(mState!= ButtonState.Disabled)
 */
using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using System.Windows.Forms.Design;
using System.ComponentModel;
using System.Drawing.Drawing2D;
using ProWrite.UI.Controls.Designer;

namespace ProWrite.UI.Controls
{
    /// <summary>
    /// ImageButton
    /// </summary>
    [Designer ( typeof ( ImageButtonDesigner ) ), ToolboxBitmap ( typeof ( Button ) )]
    public class ImageButton : Control
    {
        #region... Variables ...
        /// <summary>
        /// state of button
        /// </summary>
        enum ButtonState
        {
            /// <summary>
            /// 正常
            /// </summary>
            Normal,
            /// <summary>
            /// 鼠标悬浮
            /// </summary>
            Hover,
            /// <summary>
            /// 按下
            /// </summary>
            Pushed,
            /// <summary>
            /// 禁用
            /// </summary>
            Disabled
        }
        /// <summary>
        ///  current button state 
        /// </summary>
        private ButtonState mState = ButtonState.Normal;
        /// <summary>
        /// images that state used
        /// </summary>
        private Dictionary<ButtonState,Image> mImages = new Dictionary<ButtonState, Image> ( );
        #endregion

        #region... Events	   ...

        #endregion

        #region... Construct ...
        /// <summary>
        /// ImageButton
        /// </summary>
        public ImageButton ( )
        {
            /*
             * support double buffer and transparent
             */
            DoubleBuffered = true;
            ResizeRedraw = true;

            SetStyle ( ControlStyles.UserPaint, true );
            SetStyle ( ControlStyles.AllPaintingInWmPaint, true );
            SetStyle ( ControlStyles.SupportsTransparentBackColor, true );

            BackColor = Color.Transparent;
        }
        #endregion

        #region... Property  ...
        /// <summary>
        /// Get or set normal state shape
        /// </summary>
        [DefaultValue ( null )]
        public Image NormalImage
        {
            get
            {
                if ( !mImages.ContainsKey ( ButtonState.Normal ) )
                    mImages.Add ( ButtonState.Normal, null );
                return mImages [ ButtonState.Normal ];
            }
            set
            {
                mImages [ ButtonState.Normal ] = value;
                Invalidate ( );
            }
        }
        /// <summary>
        /// Get or set hover state shape
        /// </summary>
        [DefaultValue ( null )]
        public Image HoverImage
        {
            get
            {
                if ( !mImages.ContainsKey ( ButtonState.Hover ) )
                    mImages.Add ( ButtonState.Hover, null );
                return mImages [ ButtonState.Hover ];
            }
            set
            {
                mImages [ ButtonState.Hover ] = value;
                Invalidate ( );
            }
        }
        /// <summary>
        /// get or set the shape when mouse push down.
        /// </summary>
        [DefaultValue ( null )]
        public Image PushedImage
        {
            get
            {
                if ( !mImages.ContainsKey ( ButtonState.Pushed ) )
                    mImages.Add ( ButtonState.Pushed, null );
                return mImages [ ButtonState.Pushed ];
            }
            set
            {
                mImages [ ButtonState.Pushed ] = value;
                Invalidate ( );
            }
        }
        /// <summary>
        /// Get or set disable state shape
        /// </summary>
        [DefaultValue ( null )]
        public Image DisabledImage
        {
            get
            {
                if ( !mImages.ContainsKey ( ButtonState.Disabled ) )
                    mImages.Add ( ButtonState.Disabled, null );
                return mImages [ ButtonState.Disabled ];
            }
            set
            {
                mImages [ ButtonState.Disabled ] = value;
                Invalidate ( );
            }
        }
        /// <summary>
        /// Get default size 
        /// </summary>
        protected override Size DefaultSize
        {
            get
            {
                return new Size( 70,23 );
            }
        }
        #endregion

        #region... Method    ...
        /// <summary>
        /// Draw shape 
        /// </summary>
        /// <param name="g"></param>
        /// <param name="shape"></param>
        private void DrawImage ( Graphics g, Image image )
        {
            Rectangle rect = ClientRectangle;

            g.DrawImage ( image, rect );
        }
        /// <summary>
        /// Paint
        /// </summary>
        /// <param name="e"></param>
        protected override void OnPaint ( PaintEventArgs e )
        {
            base.OnPaint ( e );

            Graphics g = e.Graphics;
            g.SmoothingMode = SmoothingMode.HighQuality;
            g.CompositingQuality = CompositingQuality.HighQuality;
            g.InterpolationMode = InterpolationMode.HighQualityBicubic;

            g.Clear ( BackColor );
            if ( mImages.ContainsKey ( mState ) )
            {
                Image image = mImages [ mState ];
                if ( image != null )
                    DrawImage ( g, image );
            }
        }
        /// <summary>
        /// Process mouse leave
        /// </summary>
        /// <param name="e"></param>
        protected override void OnMouseLeave ( EventArgs e )
        {
            base.OnMouseLeave ( e );
            if(mState!= ButtonState.Disabled)
                mState = ButtonState.Normal;
            Invalidate ( );
        }
        /// <summary>
        /// Process mouse move
        /// </summary>
        /// <param name="e"></param>
        protected override void OnMouseMove ( MouseEventArgs e )
        {
            base.OnMouseMove ( e );
            if ( e.Button != MouseButtons.Left )
            {
                if ( mState != ButtonState.Hover )
                {
                    if (mState != ButtonState.Disabled)
                        mState = ButtonState.Hover;
                    Invalidate ( );
                }
            }           
        }
        /// <summary>
        /// Process mouse down
        /// </summary>
        /// <param name="e"></param>
        protected override void OnMouseDown ( MouseEventArgs e )
        {
            base.OnMouseDown ( e );
            if (mState != ButtonState.Disabled)
                mState = ButtonState.Pushed;
            Invalidate ( );
        }
        /// <summary>
        /// Process mouse up
        /// </summary>
        /// <param name="e"></param>
        protected override void OnMouseUp ( MouseEventArgs e )
        {
            base.OnMouseUp ( e );
            if (mState != ButtonState.Disabled)
                mState = ButtonState.Normal;
            Invalidate ( );
        }
        /// <summary>
        /// Process Enabled property changed 
        /// </summary>
        /// <param name="e"></param>
        protected override void OnEnabledChanged ( EventArgs e )
        {
            base.OnEnabledChanged ( e );
            if ( !Enabled )
            {
                mState = ButtonState.Disabled;
                Invalidate ( );
            }
            else
            {
                mState = ButtonState.Normal;
                Invalidate();
            }
        }       
        /// <summary>
        /// For button user use to simulate a click operate.
        /// </summary>
        public void PerformClicked ( )
        {
            base.OnClick ( EventArgs.Empty );
        }
        #endregion

        #region... Interface ...

        #endregion
    }  
}
