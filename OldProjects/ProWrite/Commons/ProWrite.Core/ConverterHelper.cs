//---------------------------------------------------------------------
//
// File: ConverterHelper.cs
//
// Description:
// Converter Helper class
//
// Author: Kevin
// 
// Modify History:
//
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using System.Data;
using System.Collections;
using System.Drawing;
using System.Globalization;

namespace ProWrite.Core
{
    public sealed class ConverterHelper
    {
        private ConverterHelper() { }

        static Hashtable defaultValues = new Hashtable();
        static readonly Hashtable typeMap = new Hashtable();


        static ConverterHelper()
        {
            defaultValues[TypeCode.Boolean] = false;
            defaultValues[TypeCode.Byte] = 0;
            defaultValues[TypeCode.Char] = '\0';
            defaultValues[TypeCode.DateTime] = DateTime.MinValue;
            defaultValues[TypeCode.Decimal] = 0.0d;
            defaultValues[TypeCode.Double] = 0.0;
            defaultValues[TypeCode.Int16] = 0;
            defaultValues[TypeCode.Int32] = 0;
            defaultValues[TypeCode.Int64] = (long)0;
            defaultValues[TypeCode.SByte] = 0;
            defaultValues[TypeCode.Single] = 0f;
            defaultValues[TypeCode.String] = string.Empty;
            defaultValues[TypeCode.UInt16] = 0;
            defaultValues[TypeCode.UInt32] = 0;
            defaultValues[TypeCode.UInt64] = 0;

            defaultValues[typeof(bool)] = false;
            defaultValues[typeof(byte)] = 0;
            defaultValues[typeof(char)] = '\0';
            defaultValues[typeof(DateTime)] = DateTime.MinValue;
            defaultValues[typeof(decimal)] = 0.0d;
            defaultValues[typeof(double)] = 0.0;
            defaultValues[typeof(short)] = 0;
            defaultValues[typeof(int)] = 0;
            defaultValues[typeof(long)] = (long)0;
            defaultValues[typeof(sbyte)] = 0;
            defaultValues[typeof(Single)] = 0f;
            defaultValues[typeof(string)] = string.Empty;
            defaultValues[typeof(ushort)] = 0;
            defaultValues[typeof(uint)] = 0;
            defaultValues[typeof(ulong)] = 0;
            defaultValues[typeof(Color)] = Color.White;

            defaultValues[typeof(bool?)] = null;
            defaultValues[typeof(byte?)] = null;
            defaultValues[typeof(char?)] = null;
            defaultValues[typeof(DateTime?)] = null;
            defaultValues[typeof(decimal?)] = null;
            defaultValues[typeof(double?)] = null;
            defaultValues[typeof(short?)] = null;
            defaultValues[typeof(int?)] = null;
            defaultValues[typeof(long)] = null;
            defaultValues[typeof(sbyte?)] = null;
            defaultValues[typeof(Single?)] = null;
            defaultValues[typeof(ushort?)] = null;
            defaultValues[typeof(uint?)] = null;
            defaultValues[typeof(ulong?)] = null;
            defaultValues[typeof(Color?)] = null;

            typeMap[typeof(bool)] = "bool";
            typeMap[typeof(byte)] = "byte";
            typeMap[typeof(char)] = "char";
            typeMap[typeof(DateTime)] = "date";
            typeMap[typeof(decimal)] = "decimal";
            typeMap[typeof(double)] = "double";
            typeMap[typeof(float)] = "float";
            typeMap[typeof(Guid)] = "guid";
            typeMap[typeof(short)] = "short";
            typeMap[typeof(int)] = "int";
            typeMap[typeof(long)] = "long";
            typeMap[typeof(sbyte)] = "sbyte";
            typeMap[typeof(Single)] = "single";
            typeMap[typeof(string)] = "string";
            typeMap[typeof(ushort)] = "ushort";
            typeMap[typeof(uint)] = "uint";
            typeMap[typeof(ulong)] = "ulong";


            typeMap[typeof(bool?)] = "bool?";
            typeMap[typeof(byte?)] = "byte?";
            typeMap[typeof(char?)] = "char?";
            typeMap[typeof(DateTime?)] = "date?";
            typeMap[typeof(decimal?)] = "decimal?";
            typeMap[typeof(double?)] = "double?";
            typeMap[typeof(float)] = "float?";
            typeMap[typeof(Guid?)] = "guid?";
            typeMap[typeof(short?)] = "short?";
            typeMap[typeof(int?)] = "int?";
            typeMap[typeof(long?)] = "long?";
            typeMap[typeof(sbyte?)] = "sbyte?";
            typeMap[typeof(Single?)] = "single?";
            typeMap[typeof(ushort?)] = "ushort?";
            typeMap[typeof(uint?)] = "uint?";
            typeMap[typeof(ulong?)] = "ulong?";

            typeMap["bool"] = typeof(bool);
            typeMap["byte"] = typeof(byte);
            typeMap["char"] = typeof(char);
            typeMap["date"] = typeof(DateTime);
            typeMap["decimal"] = typeof(decimal);
            typeMap["double"] = typeof(double);
            typeMap["float"] = typeof(float);
            typeMap["guid"] = typeof(Guid);
            typeMap["short"] = typeof(short);
            typeMap["int"] = typeof(int);
            typeMap["long"] = typeof(long);
            typeMap["sbyte"] = typeof(sbyte);
            typeMap["single"] = typeof(Single);
            typeMap["string"] = typeof(string);
            typeMap["ushort"] = typeof(ushort);
            typeMap["uint"] = typeof(uint);
            typeMap["ulong"] = typeof(ulong);

            typeMap["bool?"] = typeof(bool?);
            typeMap["byte?"] = typeof(byte?);
            typeMap["char?"] = typeof(char?);
            typeMap["date?"] = typeof(DateTime?);
            typeMap["decimal?"] = typeof(decimal?);
            typeMap["double?"] = typeof(double?);
            typeMap["float?"] = typeof(float?);
            typeMap["guid?"] = typeof(Guid?);
            typeMap["short?"] = typeof(short?);
            typeMap["int?"] = typeof(int?);
            typeMap["long?"] = typeof(long?);
            typeMap["sbyte?"] = typeof(sbyte?);
            typeMap["single?"] = typeof(Single?);
            typeMap["ushort?"] = typeof(ushort?);
            typeMap["uint?"] = typeof(uint?);
            typeMap["ulong?"] = typeof(ulong?);


        }

        public static object DefaultValue(Type type)
        {
            return defaultValues[type];
        }

        public static object ToObject(Type type, string str, object defaultValue)
        {
            if (str == null || str.Trim() == string.Empty)
            {
                return defaultValue;
            }
            try
            {
                return Convert.ChangeType(str, type);
            }
            catch
            {
                return defaultValue;
            }


        }

        public static object ToObject(Type type, string str)
        {
            if (str == null || str.Trim() == string.Empty)
            {
                if (defaultValues.ContainsKey(type))
                    return defaultValues[type];
                if (type.IsEnum)
                    return Enum.GetValues(type).GetValue(0);
            }
            try
            {
                if (type.IsEnum)
                    return Enum.Parse(type, str, true);
                if (type == typeof(Color))
                    return Color.FromName(str);
                return Convert.ChangeType(str, type);

            }
            catch
            {
                if (defaultValues.ContainsKey(type))
                    return defaultValues[type];
                if (type.IsEnum)
                    return Enum.GetValues(type).GetValue(0);
            }

            return null;
        }

        public static object ToObject(TypeCode typeCode, string str, object defaultValue)
        {
            if (str == null || str.Trim() == string.Empty)
            {
                return defaultValue;
            }
            try
            {
                return Convert.ChangeType(str, typeCode);
            }
            catch
            {
                return defaultValue;
            }
        }

        public static string ToString(object o)
        {
            return o == null || o == DBNull.Value ? null : o.ToString();
        }

        public static string FromType(Type type)
        {
            return typeMap[type] as string;
        }
        public static Type ToType(string typeName)
        {
            return typeMap[typeName] as Type;
        }

        public static DataTable ToTable(object[] items)
        {
            return TableHelper.ToTable(items);
        }
        private class TableHelper
        {
            private class SchemaInfo
            {
                public readonly Type Type;
                public readonly PropertyInfo[] Props;
                public readonly DataTable Schema;

                public SchemaInfo(Type type, PropertyInfo[] ps, DataTable schema)
                {
                    Type = type;
                    Props = ps;
                    Schema = schema;
                }
            }

            static Dictionary<Type, SchemaInfo> schemaCache;

            static TableHelper()
            {
                schemaCache = new Dictionary<Type, SchemaInfo>();
            }

            static SchemaInfo GetSchema(Type type)
            {
                if (schemaCache.ContainsKey(type))
                    return schemaCache[type];

                DataTable schema = new DataTable();
                PropertyInfo[] ps;

                ps = type.GetProperties(BindingFlags.Public | BindingFlags.Instance | BindingFlags.GetProperty);

                if (ps != null && ps.Length > 0)
                {
                    schema.Columns.Add("Item", type);
                    Type[] types = null;
                    foreach (PropertyInfo p in ps)
                    {
                        if (!p.CanRead) continue;

                        if (p.PropertyType.IsGenericType)
                        {
                            types = p.PropertyType.GetGenericArguments();
                            if (types.Length == 1)
                                schema.Columns.Add(p.Name, types[0]).AllowDBNull = true;
                        }
                        else
                            schema.Columns.Add(p.Name, p.PropertyType);
                    }
                }

                SchemaInfo info = new SchemaInfo(type, ps, schema);
                schemaCache[type] = info;
                return info;
            }

            private static object CheckNullable(object item)
            {
                if (item == null)
                    return DBNull.Value;

                Type type = item.GetType();
                if (!type.IsGenericType)
                    return item;

                Type underType = Nullable.GetUnderlyingType(type);

                if (underType == typeof(bool))
                {
                    return (item as bool?).Value;
                }
                else if (underType == typeof(long))
                {
                    return (item as long?).Value;
                }
                else if (underType == typeof(int))
                {
                    return (item as int?).Value;
                }
                else if (underType == typeof(short))
                {
                    return (item as short?).Value;
                }
                else if (underType == typeof(ulong))
                {
                    return (item as ulong?).Value;
                }
                else if (underType == typeof(uint))
                {
                    return (item as uint?).Value;
                }
                else if (underType == typeof(ushort))
                {
                    return (item as ushort?).Value;
                }
                else if (underType == typeof(double))
                {
                    return (item as double?).Value;
                }
                else if (underType == typeof(decimal))
                {
                    return (item as decimal?).Value;
                }
                else if (underType == typeof(Single))
                {
                    return (item as Single?).Value;
                }
                else if (underType == typeof(DateTime))
                {
                    return (item as DateTime?).Value;
                }
                else if (underType == typeof(char))
                {
                    return (item as char?).Value;
                }
                else if (underType == typeof(byte))
                {
                    return (item as byte?).Value;
                }
                else if (underType == typeof(sbyte))
                {
                    return (item as sbyte?).Value;
                }
                else
                {
                    return item;
                }
            }

            public static DataTable ToTable(object[] items)
            {
                if (items == null || items.Length < 1 || items[0] == null)
                    return null;

                SchemaInfo info = GetSchema(items[0].GetType());

                DataTable rs = info.Schema.Clone();
                if (info.Props != null && info.Props.Length > 0)
                {
                    DataRow row = null;
                    object value = null;
                    foreach (object item in items)
                    {
                        row = rs.NewRow();
                        row["Item"] = item;

                        foreach (PropertyInfo p in info.Props)
                        {
                            if (rs.Columns.Contains(p.Name))
                            {
                                value = CheckNullable(p.GetValue(item, null));
                                row[p.Name] = value;
                            }
                        }

                        rs.Rows.Add(row);

                    }
                }
                return rs;
            }

        }

        #region Helper Methods
        public static bool ToBoolean(string str, bool defaultValue)
        {
            return (bool)ConverterHelper.ToObject(TypeCode.Boolean, str, defaultValue);
        }


        public static byte ToByte(string str, byte defaultValue)
        {
            return (byte)ConverterHelper.ToObject(TypeCode.Byte, str, defaultValue);
        }


        public static char ToChar(string str, char defaultValue)
        {
            return (char)ConverterHelper.ToObject(TypeCode.Char, str, defaultValue);
        }


        public static DateTime ToDateTime(string str, DateTime defaultValue)
        {
            return (DateTime)ConverterHelper.ToObject(TypeCode.DateTime, str, defaultValue);
        }


        public static decimal ToDecimal(string str, decimal defaultValue)
        {
            return (decimal)ConverterHelper.ToObject(TypeCode.Decimal, str, defaultValue);
        }


        public static double ToDouble(string str, double defaultValue)
        {
            return (double)ConverterHelper.ToObject(TypeCode.Double, str, defaultValue);
        }


        public static short ToInt16(string str, short defaultValue)
        {
            return (short)ConverterHelper.ToObject(TypeCode.Int16, str, defaultValue);
        }


        public static int ToInt32(string str, int defaultValue)
        {
            return (int)ConverterHelper.ToObject(TypeCode.Int32, str, defaultValue);
        }

        public static long ToInt64(string str, long defaultValue)
        {
            return (long)ConverterHelper.ToObject(TypeCode.Int64, str, defaultValue);
        }

        public static sbyte ToSByte(string str, sbyte defaultValue)
        {
            return (sbyte)ConverterHelper.ToObject(TypeCode.SByte, str, defaultValue);
        }


        public static Single ToSingle(string str, Single defaultValue)
        {
            return (Single)ConverterHelper.ToObject(TypeCode.Single, str, defaultValue);
        }


        public static ushort ToUInt16(string str, ushort defaultValue)
        {
            return (ushort)ConverterHelper.ToObject(TypeCode.UInt16, str, defaultValue);
        }


        public static uint ToUInit32(string str, uint defaultValue)
        {
            return (uint)ConverterHelper.ToObject(TypeCode.UInt32, str, defaultValue);
        }


        public static ulong ToUInit64(string str, ulong defaultValue)
        {
            return (ulong)ConverterHelper.ToObject(TypeCode.UInt64, str, defaultValue);
        }

        public static string ToD(string Num, int n)
        {
            char[] nums = Num.ToCharArray();
            Int64 d = 0;
            for (int i = 0; i < nums.Length; i++)
            {
                string number = nums[i].ToString();
                if (n == 16)
                {
                    switch (number.ToUpper())
                    {
                        case "A":
                            number = "10";
                            break;
                        case "B":
                            number = "11";
                            break;
                        case "C":
                            number = "12";
                            break;
                        case "D":
                            number = "13";
                            break;
                        case "E":
                            number = "14";
                            break;
                        case "F":
                            number = "15";
                            break;
                    }
                }
                Double power = Math.Pow(Convert.ToDouble(n), Convert.ToDouble(nums.Length - (i + 1)));
                d = d + Convert.ToInt64(number) * Convert.ToInt64(power);
            }
            return d.ToString();
        }

        /// <summary>
        /// used in DES color
        /// </summary>
        /// <param name="_color"></param>
        /// <returns></returns>
        public static string ColorToHexString(Color _color)
        {
            string str = "";

            str += _color.A.ToString("X").Length > 1 ? _color.A.ToString("X") : "0" + _color.A.ToString("X");
            str += _color.B.ToString("X").Length > 1 ? _color.B.ToString("X") : "0" + _color.B.ToString("X");
            str += _color.G.ToString("X").Length > 1 ? _color.G.ToString("X") : "0" + _color.G.ToString("X");
            str += _color.R.ToString("X").Length > 1 ? _color.R.ToString("X") : "0" + _color.R.ToString("X");

            return str;
        }

        /// <summary>
        /// used in UFE color
        /// </summary>
        /// <param name="_color"></param>
        /// <param name="signType"></param>
        /// <returns></returns>
        public static string ColorToString(Color _color, SignType? signType)
        {
            string str = "0x";
            str += _color.A.ToString("X").Length > 1 ? _color.A.ToString("X") : "0" + _color.A.ToString("X");
            //str += _color.B.ToString("X").Length > 1 ? _color.B.ToString("X") : "0" + _color.B.ToString("X");
            //str += _color.G.ToString("X").Length > 1 ? _color.G.ToString("X") : "0" + _color.G.ToString("X");
            //str += _color.R.ToString("X").Length > 1 ? _color.R.ToString("X") : "0" + _color.R.ToString("X");
            if (signType.HasValue)
            {
                switch (signType.Value)
                {
                    case SignType.Red:
                        string r = _color.R.ToString("X").Length > 1
                                       ? _color.R.ToString("X")
                                       : "0" + _color.R.ToString("X");
                        str += r + r + r;
                        break;
                    case SignType.Green:
                        string g = _color.G.ToString("X").Length > 1
                                       ? _color.G.ToString("X")
                                       : "0" + _color.G.ToString("X");
                        str += g + g + g;
                        break;
                    case SignType.Blue:
                        string b = _color.B.ToString("X").Length > 1
                                       ? _color.B.ToString("X")
                                       : "0" + _color.B.ToString("X");
                        str += b + b + b;
                        break;
                    default:
                        str += _color.B.ToString("X").Length > 1 ? _color.B.ToString("X") : "0" + _color.B.ToString("X");
                        str += _color.G.ToString("X").Length > 1 ? _color.G.ToString("X") : "0" + _color.G.ToString("X");
                        str += _color.R.ToString("X").Length > 1 ? _color.R.ToString("X") : "0" + _color.R.ToString("X");
                        break;
                }
            }
            return str;
        }

        #endregion
    }
}
