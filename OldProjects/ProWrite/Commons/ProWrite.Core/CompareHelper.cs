//---------------------------------------------------------------------
//
// File: CompareHelper.cs
//
// Description:
// Compare Helper class
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
using ProWrite.Core;
using System.Collections;

namespace ProWrite.Core
{
    public class CompareHelper
    {
        public static bool Compare(CompareOp op, object compareFrom, object compareTo)
        {
            int i = Comparer.Default.Compare(compareFrom, compareTo);

            switch (op)
            {
                case CompareOp.GreaterThan: return i > 0;
                case CompareOp.GreaterOrEqual: return i >= 0;
                case CompareOp.LessOrEqual: return i <= 0;
                case CompareOp.LessThan: return i < 0;
                case CompareOp.NotEqual: return i != 0;
                default: return i == 0;
            }
        }

        public static bool Compare(CompareOp op, IComparable val, IComparable compareVal)
        {
            int i = val.CompareTo(compareVal);
            switch (op)
            {
                case CompareOp.GreaterThan: return i > 0;
                case CompareOp.GreaterOrEqual: return i >= 0;
                case CompareOp.LessOrEqual: return i <= 0;
                case CompareOp.LessThan: return i < 0;
                case CompareOp.NotEqual: return i != 0;
                default: return i == 0;
            }
        }

        public static bool Compare<T>(CompareOp op, T val, T compareVal) where T : IComparable
        {
            int i = val.CompareTo(compareVal);
            switch (op)
            {
                case CompareOp.GreaterThan: return i > 0;
                case CompareOp.GreaterOrEqual: return i >= 0;
                case CompareOp.LessOrEqual: return i <= 0;
                case CompareOp.LessThan: return i < 0;
                case CompareOp.NotEqual: return i != 0;
                default: return i == 0;
            }
        }

        public static bool Compare(CompareOp op, object val, string compareVal, Type type)
        {
            if (val == null)
            {
                if (string.IsNullOrEmpty(compareVal) || compareVal.Trim().ToLower() == "null" || compareVal.Trim().ToLower() == "nothing")
                {
                    switch (op)
                    {
                        case CompareOp.GreaterThan:
                        case CompareOp.LessThan:
                        case CompareOp.NotEqual: return false;
                        default: return true;
                    }
                }
                else
                {
                    switch (op)
                    {
                        case CompareOp.Equal:
                        case CompareOp.GreaterOrEqual:
                        case CompareOp.GreaterThan: return false;
                        default: return true;
                    }
                }
            }
            else if (type.IsGenericType && type.Name.IndexOf("Nullable") != -1)
            {
                Type underType = Nullable.GetUnderlyingType(type);
                if (underType == typeof(bool))
                {
                    return CompareHelper.Compare<bool>(op,
                        ((bool?)val).Value,
                        ConverterHelper.ToBoolean(compareVal, false));
                }
                else if (underType == typeof(long))
                {
                    return CompareHelper.Compare<long>(op,
                       ((long?)val).Value,
                       ConverterHelper.ToInt64(compareVal, long.MinValue));
                }
                else if (underType == typeof(int))
                {
                    return CompareHelper.Compare<int>(op,
                       ((int?)val).Value,
                       ConverterHelper.ToInt32(compareVal, int.MinValue));
                }
                else if (underType == typeof(short))
                {
                    return CompareHelper.Compare<short>(op,
                       ((short?)val).Value,
                       ConverterHelper.ToInt16(compareVal, short.MinValue));
                }
                else if (underType == typeof(ulong))
                {
                    return CompareHelper.Compare<ulong>(op,
                       ((ulong?)val).Value,
                       ConverterHelper.ToUInit64(compareVal, ulong.MinValue));
                }
                else if (underType == typeof(uint))
                {
                    return CompareHelper.Compare<uint>(op,
                       ((uint?)val).Value,
                       ConverterHelper.ToUInit32(compareVal, uint.MinValue));
                }
                else if (underType == typeof(ushort))
                {
                    return CompareHelper.Compare<ushort>(op,
                       ((ushort?)val).Value,
                       ConverterHelper.ToUInt16(compareVal, ushort.MinValue));
                }
                else if (underType == typeof(double))
                {
                    return CompareHelper.Compare<double>(op,
                       ((double?)val).Value,
                       ConverterHelper.ToDouble(compareVal, double.MinValue));
                }
                else if (underType == typeof(decimal))
                {
                    return CompareHelper.Compare<decimal>(op,
                       ((decimal?)val).Value,
                       ConverterHelper.ToDecimal(compareVal, decimal.MinValue));
                }
                else if (underType == typeof(Single))
                {
                    return CompareHelper.Compare<Single>(op,
                       ((Single?)val).Value,
                       ConverterHelper.ToSingle(compareVal, Single.MinValue));
                }
                else if (underType == typeof(DateTime))
                {
                    return CompareHelper.Compare<DateTime>(op,
                       ((DateTime?)val).Value,
                       ConverterHelper.ToDateTime(compareVal, DateTime.MinValue));
                }
                else if (underType == typeof(char))
                {
                    return CompareHelper.Compare<char>(op,
                       ((char?)val).Value,
                       ConverterHelper.ToChar(compareVal, char.MinValue));
                }
                else if (underType == typeof(byte))
                {
                    return CompareHelper.Compare<byte>(op,
                       ((byte?)val).Value,
                       ConverterHelper.ToByte(compareVal, byte.MinValue));
                }
                else if (underType == typeof(sbyte))
                {
                    return CompareHelper.Compare<sbyte>(op,
                       ((sbyte?)val).Value,
                       ConverterHelper.ToSByte(compareVal, sbyte.MinValue));
                }
            }
            else if (type == typeof(string) || type.IsValueType)
            {
                if (string.IsNullOrEmpty(compareVal) || compareVal.Trim().ToLower() == "null" || compareVal.Trim().ToLower() == "nothing")
                {
                    switch (op)
                    {
                        case CompareOp.GreaterThan:
                        case CompareOp.GreaterOrEqual:
                        case CompareOp.NotEqual: return true;
                        default: return false;
                    }
                }
                else
                {
                    IComparable tmpCompareVal = ConverterHelper.ToObject(type, compareVal, null) as IComparable;
                    IComparable tmpVal = (IComparable)val;

                    return CompareHelper.Compare(op, tmpVal, tmpCompareVal);
                }
            }

            return false;
        }

    }
}
