//---------------------------------------------------------------------
//
// File: SortComparer.cs
//
// Description:
// Sort comparer class
//
// Author: Kevin 2008-6-25
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using System.Collections;
using System.ComponentModel;

namespace ProWrite.Core
{
    /// <summary>
    /// Value type comparer
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public class ValueTypeComparer<T> : IComparer<T> where T : struct
    {
        private bool ascending = true;
        public ValueTypeComparer()
        {
        }

        public ValueTypeComparer(bool asc)
        {
            this.ascending = asc;
        }

        public int Compare(T x, T y)
        {
            int retValue = Comparer<T>.Default.Compare(x, y);

            return ascending ? retValue : retValue * -1;
        }
    }

    /// <summary>
    /// Sort comparer class
    /// </summary>
    public class SortComparer : IComparer
    {
        protected string[] properties;
        protected bool[] ascendings;

        public SortComparer(params string[] properties)
        {
            if (properties != null && properties.Length > 0)
            {
                this.properties = properties;
                this.ascendings = new bool[properties.Length];
                for (int i = 0; i < properties.Length; i++)
                {
                    ascendings[i] = true;
                }
            }
        }

        public SortComparer(string[] properties, bool[] ascendings)
        {
            if (properties != null && ascendings != null)
            {
                if (properties.Length != ascendings.Length)
                    throw new Exception("properties length should be the same as descending length!");

                this.properties = properties;
                this.ascendings = ascendings;
            }
        }

        public SortComparer(string property, bool ascending)
            : this(new string[] { property }, new bool[] { ascending })
        {

        }



        public int Compare(object x, object y)
        {
            if (properties != null && ascendings != null
                && properties.Length > 0 && ascendings.Length > 0)
            {
                return CompareValues(x, y, properties, ascendings);
            }
            else return 0;
        }

        private static int CompareValues(object x, object y, string[] properties, bool[] ascendings)
        {
            Type type = x.GetType();
            PropertyInfo prop = null;
            FieldInfo field = null;
            int retValue = 0;
            for (int i = 0; i < properties.Length; i++)
            {
                prop = type.GetProperty(properties[i]);
                if (prop != null)
                {
                    object xValue = prop.GetValue(x, null);
                    object yValue = prop.GetValue(y, null);
                    retValue = CompareValues(xValue, yValue, ascendings[i]);

                    if (retValue != 0) break;

                }
                else
                {
                    field = type.GetField(properties[i]);
                    if (field != null)
                    {
                        object xValue = field.GetValue(x);
                        object yValue = field.GetValue(y);
                        retValue = CompareValues(xValue, yValue, ascendings[i]);

                        if (retValue != 0) break;
                    }
                }
            }

            return retValue;
        }

        private static int CompareValues(object x, object y, bool ascending)
        {
            int retValue = Comparer.Default.Compare(x, y);

            return ascending ? retValue : retValue * -1;
        }

        private static int CompareValues(object x, object y, ListSortDirection direction)
        {
            int retValue = Comparer.Default.Compare(x, y);

            if (direction == ListSortDirection.Ascending)
            {
                return retValue;
            }
            else
            {
                return retValue * -1;
            }
        }
    }

    /// <summary>
    /// Sort comparer class
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public class SortComparer<T> : IComparer<T>
    {
        private ListSortDescriptionCollection sortCollection = null;
        private PropertyDescriptor propDesc = null;
        private ListSortDirection direction = ListSortDirection.Ascending;

        private string[] properties;
        private bool[] ascendings;

        public SortComparer(PropertyDescriptor propDesc, ListSortDirection direction)
        {
            this.propDesc = propDesc;
            this.direction = direction;
        }

        public SortComparer(ListSortDescriptionCollection sortCollection)
        {
            this.sortCollection = sortCollection;
        }

        public SortComparer(params string[] properties)
        {
            if (properties != null && properties.Length > 0)
            {
                this.properties = properties;
                this.ascendings = new bool[properties.Length];
                for (int i = 0; i < properties.Length; i++)
                {
                    ascendings[i] = true;
                }
            }
        }

        public SortComparer(string[] properties, bool[] ascendings)
        {
            if (properties != null && ascendings != null)
            {
                if (properties.Length != ascendings.Length)
                    throw new Exception("properties length should be the same as descending length!");

                this.properties = properties;
                this.ascendings = ascendings;
            }
        }

        public SortComparer(string property, bool ascending)
            : this(new string[] { property }, new bool[] { ascending })
        {

        }


        int IComparer<T>.Compare(T x, T y)
        {
            if (propDesc != null)
            {
                object xValue = propDesc.GetValue(x);
                object yValue = propDesc.GetValue(y);
                return CompareValues(xValue, yValue, direction);
            }
            else if (sortCollection != null &&
                     sortCollection.Count > 0)
            {
                return RecursiveCompareInternal(x, y, 0);
            }
            else if (properties != null && ascendings != null
                && properties.Length > 0 && ascendings.Length > 0)
            {
                return CompareValues(x, y, properties, ascendings);
            }
            else return 0;
        }

        private static int CompareValues(T x, T y, string[] properties, bool[] ascendings)
        {
            Type type = typeof(T);
            PropertyInfo prop = null;
            FieldInfo field = null;
            int retValue = 0;
            for (int i = 0; i < properties.Length; i++)
            {
                prop = type.GetProperty(properties[i]);
                if (prop != null)
                {
                    object xValue = prop.GetValue(x, null);
                    object yValue = prop.GetValue(y, null);
                    retValue = CompareValues(xValue, yValue, ascendings[i]);

                    if (retValue != 0) break;

                }
                {
                    field = type.GetField(properties[i]);
                    if (field != null)
                    {
                        object xValue = field.GetValue(x);
                        object yValue = field.GetValue(y);
                        retValue = CompareValues(xValue, yValue, ascendings[i]);

                        if (retValue != 0) break;
                    }
                }
            }

            return retValue;
        }

        private static int CompareValues(object x, object y, bool ascending)
        {
            int retValue = Comparer.Default.Compare(x, y);

            return ascending ? retValue : retValue * -1;
        }

        private static int CompareValues(object x, object y, ListSortDirection direction)
        {
            int retValue = Comparer.Default.Compare(x, y);

            if (direction == ListSortDirection.Ascending)
            {
                return retValue;
            }
            else
            {
                return retValue * -1;
            }
        }

        private int RecursiveCompareInternal(T x, T y, int index)
        {
            if (index >= sortCollection.Count)
                return 0;

            ListSortDescription listSortDesc = sortCollection[index];
            object xValue = listSortDesc.PropertyDescriptor.GetValue(x);
            object yValue = listSortDesc.PropertyDescriptor.GetValue(y);

            int retValue = CompareValues(xValue,
                                         yValue, listSortDesc.SortDirection);
            if (retValue == 0)
            {
                return RecursiveCompareInternal(x, y, ++index);
            }
            else
            {
                return retValue;
            }
        }
    }
}
