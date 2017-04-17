using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DevExpress.XtraTreeList;
using System.Reflection;

namespace ProWrite.UI.Controls
{
    public static class TreeListExtensions
    {
        private static readonly PropertyInfo dragInfoProperty = null;
        private static readonly PropertyInfo handlerProperty = null;
        private static readonly FieldInfo fStateData = null;
        private static readonly FieldInfo dragInsertDirectionField = null;
        private static readonly BindingFlags propertyFlags = BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.GetProperty;
        private static readonly BindingFlags fieldFlags = BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.GetField;

        static TreeListExtensions()
        {
            var treeType = typeof(TreeList);
            try
            {
                handlerProperty = treeType.GetProperty("Handler", propertyFlags);

                if (handlerProperty != null)
                {
                    fStateData = handlerProperty.PropertyType.GetField("fStateData", fieldFlags);
                    if (fStateData != null)
                    {
                        dragInfoProperty = fStateData.FieldType.GetProperty("DragInfo", propertyFlags);
                        if (dragInfoProperty != null)
                        {
                            dragInsertDirectionField = dragInfoProperty.PropertyType.GetField("dragInsertDirection",fieldFlags);
                        }
                    }
                }
            }
            catch
            {
            }
        }



        public static DragInsertDirection GetDragInsertDirection(this TreeList tree)
        {
            DragInsertDirection direction =  DragInsertDirection.None;

            if (dragInsertDirectionField != null)
            {
                try
                {
                    object handler = handlerProperty.GetValue(tree, null);
                    if (handler == null)
                        return direction;
                    object stateData = fStateData.GetValue(handler);
                    if (stateData == null)
                        return direction;
                    object dragInfo = dragInfoProperty.GetValue(stateData, null) as DragScrollInfo;
                    if (dragInfo != null)
                    {
                        direction = (DragInsertDirection)dragInsertDirectionField.GetValue(dragInfo);
                    }
                }
                catch (Exception ex)
                {

                }
            }

            return direction;
        }
    }
}
