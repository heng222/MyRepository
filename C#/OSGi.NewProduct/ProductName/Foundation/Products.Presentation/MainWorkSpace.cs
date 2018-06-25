using System.Drawing;
using System.Linq;
using System.Windows.Forms;
using Acl;
using Platform.Presentation;
using Products.Infrastructure.Types;

namespace Products.Presentation
{
    /// <summary>
    /// 
    /// </summary>
    public static class MainWorkSpace
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="part"></param>
        public static void AddPart(Control part)
        {
            Guard.NotNull(Workbench.MainWorkspace, "Workbench.MainWorkspace");
            Guard.NotNull(part, "part");
            
            var attri = part.GetType().GetCustomAttributes(typeof(ProductPartAttribute), false)
                .OfType<ProductPartAttribute>().FirstOrDefault();            

            Guard.NotNull(attri, "attri");

            //part.Text = attri.Title;
            attri.Position = TabPosition.Bottom;

            Workbench.MainWorkspace.Show(part, attri);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="part"></param>
        /// <param name="attri"></param>
        public static void AddPart(Control part, ProductPartAttribute attri)
        {
            Guard.NotNull(Workbench.MainWorkspace, "Workbench.MainWorkspace");
            Guard.NotNull(part, "part");
            Guard.NotNull(attri, "attri");

            //part.Text = attri.Title;
            attri.Position = TabPosition.Bottom;

            Workbench.MainWorkspace.Show(part, attri);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="part"></param>
        /// <param name="defaultIcon"></param>
        public static void AddPart(Control part, Icon defaultIcon)
        {            
           var attri = part.GetType().GetCustomAttributes(typeof(ProductPartAttribute), false)
               .OfType<ProductPartAttribute>().FirstOrDefault();            

            Guard.NotNull(attri, "attri");

            //part.Text = attri.Title;
            attri.DefaultIcon = defaultIcon;
            attri.Position = TabPosition.Bottom;

            Workbench.MainWorkspace.Show(part, attri);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="type"></param>
        /// <returns></returns>
        public static Control GetControl(PresentationControlType type)
        {
            foreach (var smartPart in Workbench.MainWorkspace.SmartParts)
            {
                var attr = smartPart.GetType().GetCustomAttributes(typeof(ProductPartAttribute), false).
                    OfType<ProductPartAttribute>().FirstOrDefault();

                if (attr == null) continue;

                if (attr.ControlType == type) return smartPart as Control;
            }

            return null;
        }
    }
}
