using System.Windows.Forms;
using ProWrite.UI.Controls.Editor;

namespace ProWrite.UI.Controls.ShapeTools
{
	/// <summary>
	/// Base class for all drawing tools
	/// </summary>
	public abstract class ShapeTool:System.DisposableObject
	{
        // Left nous button is pressed
		public virtual void OnMouseDown(Canvas drawArea, MouseEventArgs e)
		{
		}

		// Mouse is moved, left mouse button is pressed or none button is pressed
        public virtual void OnMouseMove(Canvas drawArea, MouseEventArgs e)
		{
		}

		// Left mouse button is released
        public virtual void OnMouseUp(Canvas drawArea, MouseEventArgs e)
		{
		}
	}
}