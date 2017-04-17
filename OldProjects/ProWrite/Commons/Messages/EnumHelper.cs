using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Reflection;
using System.ComponentModel;

namespace System
{
    /// <summary>
    /// Author:qswang
    /// Create:2008-11-28
    /// Function:
    /// </summary>
    public static class EnumHelper
    {
        private static Dictionary<Type, EnumDescriptionAttribute[]> cache = new Dictionary<Type, EnumDescriptionAttribute[]>();

        public static T Parse<T>(string value)
        {
            Check.Require(value, "value", Check.NotNullOrEmpty);

            try
            {
                return (T)Enum.Parse(typeof(T), value);
            }
            catch
            {
            }

            return default(T);
        }

        public static T Parse<T>(int value)
        {
            return (T)Enum.ToObject(typeof(T), value);
        }

        public static string GetEnumDescription(Enum enumValue)
        {
            Check.Require(enumValue, "enumValue", Check.NotNull);

            var enumType = enumValue.GetType();

            var descriptions = GetEnumDescriptions(enumType);
            if (descriptions != null && descriptions.Length > 0)
            {
                foreach (var item in descriptions)
                    if (item.FieldName == enumValue.ToString())
                        return item.Description;
            }
            return enumValue.ToString();
        }


        public static EnumDescriptionAttribute[] GetEnumDescriptions(Type enumType)
        {
            Check.Require(enumType, "enumType", Check.NotNull);

            if (!enumType.IsEnum)
                return null;

            if (!cache.ContainsKey(enumType))
            {
                var fields = enumType.GetFields();
                var attrs = new List<EnumDescriptionAttribute>();
                

                foreach (FieldInfo fi in fields)
                {
                    object[] tmpAttrs = fi.GetCustomAttributes(typeof(EnumDescriptionAttribute), false);
                    if (tmpAttrs.Length != 1) continue;

                    var attr = tmpAttrs[0] as EnumDescriptionAttribute;
                    attr.FieldName = fi.Name;
                    if (string.IsNullOrEmpty(attr.Description))
                        attr.Description = attr.FieldName;

                    attr.Value = (Enum)fi.GetValue(null);
                    attrs.Add(attr);
                }

                cache[enumType] = attrs.ToArray();
            }

            var descriptions = cache[enumType];
            if (descriptions == null || descriptions.Length <= 0)
                return null;

            return descriptions;
        }
    }

    [AttributeUsage(AttributeTargets.Field)]
    public class EnumDescriptionAttribute : Attribute
    {
        public EnumDescriptionAttribute() { }

        public EnumDescriptionAttribute(string description)
        {
            this.Description = description;
        }

		public EnumDescriptionAttribute( string description, int rank )
		{
            this.Description = description;
			this.Rank = rank;
		}

        public Enum Value { get; internal set; }

        public string Description { get; internal set; }

        public int Rank { get; internal set; }

        public string FieldName { get; internal set; }

        public override string ToString()
        {
            return Description;
        }
    }

    public class EnumTypeConverter : TypeConverter
    {
        public override bool CanConvertTo(ITypeDescriptorContext context, Type destinationType)
        {
            return true;
        }

        public override object ConvertTo(ITypeDescriptorContext context, System.Globalization.CultureInfo culture, object value, Type destinationType)
        {
            if (value == null)
                return null;

            var items = EnumHelper.GetEnumDescriptions(value.GetType());
            Enum enumValue = value as Enum;
            foreach (var item in items)
            {
                if (item.Value.Equals(enumValue))
                {
                    return item.Description;
                }
            }
            return null;
        }
    }


}
