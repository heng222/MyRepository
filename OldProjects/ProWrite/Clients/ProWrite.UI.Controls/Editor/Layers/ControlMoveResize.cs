using System.Drawing;
using System.Windows.Forms;

namespace ProWrite.UI.Controls.Editor
{
	/// <summary>
	///使窗口的中的指定控件支持运行时移动
	/// TODO:运行时缩放
	/// // 2008-6-19, Kevin 迁移
	/// </summary>
	public class ControlMoveResize
	{
		#region  私有成员

		private const int width = 10;
		private ScrollableControl Containe = null;
		private Control ctrl = null;
		private bool IsMoving = false;
		private Point pCtrlLastCoordinate = new Point(0, 0);
		private Point pCursorLastCoordinate = new Point(0, 0);
		private Point pCursorOffset = new Point(0, 0);

		#endregion

		#region  私有方法

		private Rectangle dragBoxFromMouseDown;

		private Control FindControl(ScrollableControl ctrls, string ctrlname)
		{
			if (ctrls == null)
			{
				return null;
			}

			foreach (Control ctrl in ctrls.Controls)
			{
				if (ctrl.GetType() == typeof (Label))
				{
					if (ctrl.Name == ctrlname)
					{
						return ctrl;
					}
				}
			}

			return null;
		}

		private bool ComparePos(ScrollableControl ctrls, Control ctrl, ref int newOffsetX)
		{
			if (ctrls == null || ctrl == null)
			{
				return false;
			}

			Control ctrla = null;
			Control ctrlb = null;

			switch (ctrl.Name)
			{
				case "BeforeEnterEffect":
					{
						if (0 > ctrl.Left + newOffsetX)
						{
							newOffsetX = 0 - ctrl.Left;
							return true;
						}

						ctrla = FindControl(ctrls, "BeforeTimeSpan");
						if (ctrla != null)
						{
							if (ctrla.Left - width < ctrl.Right + newOffsetX)
							{
								newOffsetX = ctrla.Left - width - ctrl.Right;
								return true;
							}
						}
					}
					break;
				case "BeforeTimeSpan":
					{
						ctrla = FindControl(ctrls, "BeforeEnterEffect");
						if (ctrla != null)
						{
							if (ctrla.Visible && ctrla.Right + width > ctrl.Left + newOffsetX)
							{
								newOffsetX = ctrla.Right + width - ctrl.Left;
								return true;
							}
						}

						if (0 > ctrl.Left + newOffsetX)
						{
							newOffsetX = 0 - ctrl.Left;
							return true;
						}

						ctrla = FindControl(ctrls, "AfterTimeSpan");
						if (ctrla != null)
						{
							if (ctrla.Left - width < ctrl.Right + newOffsetX)
							{
								newOffsetX = ctrla.Left - width - ctrl.Right;
								return true;
							}
						}
					}
					break;
				case "AfterTimeSpan":
					{
						ctrla = FindControl(ctrls, "BeforeTimeSpan");
						if (ctrla != null)
						{
							if (ctrla.Right + width > ctrl.Left + newOffsetX)
							{
								newOffsetX = ctrla.Right + width - ctrl.Left;
								return true;
							}
						}

						ctrla = FindControl(ctrls, "AfterExitEffect");
						if (ctrla != null)
						{
							if (ctrla.Visible && ctrla.Left - width < ctrl.Right + newOffsetX)
							{
								newOffsetX = ctrla.Left - width - ctrl.Right;
								return true;
							}
						}

						if (!ctrla.Visible && ctrl.Right + newOffsetX > ctrls.ClientRectangle.Right)
						{
							newOffsetX = ctrls.ClientRectangle.Right - ctrl.Right;
							return true;
						}
					}
					break;
				case "AfterExitEffect":
					{
						ctrla = FindControl(ctrls, "AfterTimeSpan");
						if (ctrla != null)
						{
							if (ctrla.Right + width > ctrl.Left + newOffsetX)
							{
								newOffsetX = ctrla.Right + width - ctrl.Left;
								return true;
							}
						}

						if (ctrl.Right + newOffsetX > ctrls.ClientRectangle.Right)
						{
							newOffsetX = ctrls.ClientRectangle.Right - ctrl.Right;
							return true;
						}
					}
					break;
				case "TimeSpan":
					{
						//ctrlb = FindControl(ctrls, "lblLayerName");
						//if (ctrlb == null)
						//{
						//        return false;
						//}

						ctrla = FindControl(ctrls, "BeforeEnterEffect");
						if (ctrla != null)
						{
							if (ctrla.Left + newOffsetX < 0)
							{
								newOffsetX = (-1)*ctrla.Left;
								return true;
							}
						}


						ctrlb = FindControl(ctrls, "AfterExitEffect");
						if (ctrlb != null)
						{
							if (ctrlb.Right + newOffsetX > ctrls.ClientRectangle.Right)
							{
								newOffsetX = ctrls.ClientRectangle.Right - ctrlb.Right;
								return true;
							}
						}
					}
					break;
			}
			return false;
		}

		/// <summary>
		///在鼠标左键按下的状态记录鼠标当前的位置,以及被移动组件的当前位置
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private void MouseDown(object sender, MouseEventArgs e)
		{
			if (Containe == null)
			{
				return;
			}
			if (e.Button == MouseButtons.Left)
			{
				IsMoving = true;
				pCtrlLastCoordinate.X = ctrl.Left;
				pCtrlLastCoordinate.Y = ctrl.Top;
				pCursorLastCoordinate.X = Cursor.Position.X;
				pCursorLastCoordinate.Y = Cursor.Position.Y;

				Size dragSize = SystemInformation.DragSize;

				// Create a rectangle using the DragSize, with the mouse position being
				// at the center of the rectangle.
				dragBoxFromMouseDown = new Rectangle(new Point(e.X - (dragSize.Width/2),
				                                               e.Y - (dragSize.Height/2)), dragSize);
			}
		}

		private void MouseMove(object sender, MouseEventArgs e)
		{
			if (Containe == null)
			{
				return;
			}

			if (e.Button == MouseButtons.Left)
			{
				if (this.IsMoving)
				{
					Point pCursor = new Point(Cursor.Position.X, Cursor.Position.Y);

					pCursorOffset.X = pCursor.X - pCursorLastCoordinate.X;

					pCursorOffset.Y = pCursor.Y - pCursorLastCoordinate.Y;

					int xOffset = pCursorOffset.X;
					ComparePos(Containe, ctrl, ref xOffset);
					pCursorOffset.X = xOffset;

					ctrl.Left = ctrl.Left + pCursorOffset.X;
					pCursorLastCoordinate.X = pCursor.X;
					//ctrl.Top = pCtrlLastCoordinate.Y + pCursorOffset.Y;
				}

				if ((e.Button & MouseButtons.Left) == MouseButtons.Left)
				{
					if (dragBoxFromMouseDown != Rectangle.Empty && !dragBoxFromMouseDown.Contains(e.X, e.Y))
					{
						// Containe.Parent.DoDragDrop(Containe.Parent.Name, DragDropEffects.Move);
					}
				}
			}
		}

		private void MouseUp(object sender, MouseEventArgs e)
		{
			if (Containe == null)
			{
				return;
			}
			if (this.IsMoving)
			{
				if (pCursorOffset.X == 0 && pCursorOffset.Y == 0)
				{
					return;
				}
				if ((pCtrlLastCoordinate.X + pCursorOffset.X + ctrl.Width) > 0)
				{
					//ctrl.Left = pCtrlLastCoordinate.X + pCursorOffset.X;
				}
				else
				{
					//ctrl.Left = 0;
				}
				if ((pCtrlLastCoordinate.Y + pCursorOffset.Y + ctrl.Height) > 0)
				{
					//ctrl.Top = pCtrlLastCoordinate.Y + pCursorOffset.Y;
				}
				else
				{
					//ctrl.Top = 0;
				}
				pCursorOffset.X = 0;
				pCursorOffset.Y = 0;
			}

			dragBoxFromMouseDown = Rectangle.Empty;
		}

		#endregion

		/// <summary>
		///获取被移动控件对象和容器对象
		/// </summary>
		/// <param name="c">被设置为可运行时移动的控件</param>
		/// <param name="parentContain">可移动控件的容器</param>
		public ControlMoveResize(Control c, ScrollableControl parentContain)
		{
			ctrl = c;
			this.Containe = parentContain;
		}

        public void SubscribeEvent()
        {
            ctrl.MouseDown += MouseDown;
            ctrl.MouseMove += MouseMove;
            ctrl.MouseUp += MouseUp;
        }

        public void UnSubscribeEvent()
        {
            ctrl.MouseDown -= MouseDown;
            ctrl.MouseMove -= MouseMove;
            ctrl.MouseUp -= MouseUp;
        }
	}
}