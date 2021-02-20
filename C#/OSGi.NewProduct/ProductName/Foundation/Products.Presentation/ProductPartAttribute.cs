using System;
using System.Drawing;
using System.Windows.Forms;

using Acl.Presentation;

using Products.Infrastructure;

namespace Products.Presentation
{
    /// <summary>
    /// Part 特性定义。
    /// </summary>
    [AttributeUsage(AttributeTargets.Class)]
    public class ProductPartAttribute : TabSmartPartAttribute
    {
        /// <summary>
        /// 字符串格式的GUID值，用于唯一标识一个控件。
        /// </summary>
        public string ID { get; private set; }

        /// <summary>
        /// 显示本Part需要的权限。
        /// <para>默认值为 None，表示显示本Part不需要权限。</para>
        /// </summary>
        public SystemPrivilege PrivilegeNecessary { get; set; } = SystemPrivilege.None;

        /// <summary>
        /// 获取/设置Part使用的图标。
        /// </summary>
        public Icon DefaultIcon { get; set; }

        /// <summary>
        /// 获取/设置控件的停靠方式。
        /// </summary>
        public DockStyle Dock { get; set; } = DockStyle.Fill;
        /// <summary>
        /// 获取/设置控件在当前停靠方式中的对齐方式。
        /// </summary>
        public AnchorStyles Alignment { get; set; } = AnchorStyles.Left;
        /// <summary>
        /// 获取/设置控件在当前停靠方式中所占的比例。
        /// </summary>
        public float Proportion { get; set; } = 1.0f;

        /// <summary>
        /// 构造函数。
        /// </summary>
        /// <param name="id">字符串格式的GUID值，用于唯一标识一个控件。</param>
        /// <param name="title">控件的标题。</param>
        public ProductPartAttribute(string id, string title)
        {
            if (string.IsNullOrWhiteSpace(id)) throw new ArgumentException();

            this.ID = id;
            this.Title = title;
        }

        /// <inheritdoc/>
        public override Int32 GetHashCode()
        {
            return this.ID.GetHashCode();
        }

        /// <inheritdoc/>
        public override bool Equals(object obj)
        {
            if (null == obj) return false;

            if (obj.GetType() != this.GetType()) return false;

            return (((ProductPartAttribute)obj).ID.Equals(this.ID));
        }
    }
}
