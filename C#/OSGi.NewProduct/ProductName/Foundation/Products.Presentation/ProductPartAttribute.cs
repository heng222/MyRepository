using System;
using System.Drawing;

using Acl.Presentation;
using Acl.Utility;

using Products.Infrastructure.Types;

namespace Products.Presentation
{
    /// <summary>
    /// Part特性定义。
    /// </summary>
    [AttributeUsage(AttributeTargets.Class)]
    public class ProductPartAttribute : TabSmartPartAttribute
    {
        private PresentationControlType _controlType;

        /// <summary>
        /// 获取主控件的类型
        /// </summary>
        public PresentationControlType ControlType
        {
            get { return _controlType; }

            set
            {
                _controlType = value;
                Title = EnumUtility.GetDescription(value);
            }
        }

        /// <summary>
        /// 获取/设置Part使用的图标。
        /// </summary>
        public Icon DefaultIcon { get; set; }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public override int GetHashCode()
        {
            return (int)_controlType;
        }
    }
}
