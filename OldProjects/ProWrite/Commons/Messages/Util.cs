using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using System.Linq;

namespace System
{
    public sealed class SupportClass
    {
        public static string GetTypeName(object e)
        {
            if (e == null)
                return "";

            Type type = e.GetType();

            return GetTypeName(type);
        }

        public static string[] GetGenericParameterNames(MethodInfo method)
        {
            return method.GetGenericArguments().Select(type => type.Name).ToArray<string>();
        }

        public static Type[] GetParametersType(MethodInfo method)
        {
            return method.GetParameters().Select(p => p.ParameterType).ToArray<Type>();
        }

        public static string GetTypeName(Type type)
        {
            if (type == null)
                return "";

            if (!type.IsGenericType)
                return type.Name;

            StringBuilder name = new StringBuilder(type.Name);
            name.Remove(name.Length - 2, 2);

            Type[] args = type.GetGenericArguments();

            name.Append("<").Append(GetTypeName(args[0]));
            for (int i = 1; i < args.Length; ++i)
            {
                name.Append(",").Append(GetTypeName(args[i]));
            }
            return name.Append(">").ToString();
        }

        public static void BuildErrorInfo(StringBuilder sb, Exception error)
        {
            if (error != null)
            {
                sb.AppendFormat("MessageException Content:\"{0}\".\r\n", error.Message);
                sb.AppendFormat("MessageException Type:[{0}].\r\n", GetTypeName(error));

                if (error.InnerException != null)
                {
                    BuildInnerErrorInfo(sb, error.InnerException);
                }
                sb.AppendFormat("\tStack Trace:\"{0}\".\r\n", error.StackTrace);
            }
        }

        private static void BuildInnerErrorInfo(StringBuilder sb, Exception error)
        {
            if (error != null)
            {
                sb.AppendFormat("Inner MessageException Content:\"{0}\".\r\n", error.Message);
                sb.AppendFormat("Inner MessageException Type:[{0}].\r\n", GetTypeName(error));

                if (error.InnerException != null)
                    BuildInnerErrorInfo(sb, error.InnerException);
            }
        }

    }
}
