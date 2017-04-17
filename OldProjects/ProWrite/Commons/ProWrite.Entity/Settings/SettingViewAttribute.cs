using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace ProWrite.Entity.Settings
{
    [AttributeUsage(AttributeTargets.Class,Inherited=false)]
    public class SettingViewAttribute:Attribute
    {
        public SettingViewAttribute(string view)
        {
            Check.Require(view, "view", Check.NotNullOrEmpty);
            var parts = view.Split(',');
            Check.Require(parts.Length == 2, "parts.Length ==2");

            var asm = Assembly.LoadWithPartialName(parts[1]);
            Check.Require(asm, "asm", Check.NotNull);

            try
            {
                View = asm.GetType(parts[0]);
            }
            catch
            {
            }
        }

        public Type View { get; private set; }
    }
}
