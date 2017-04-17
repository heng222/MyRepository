using System;
using System.Collections.Generic;
using System.Text;
//---------------------------------------------------------------------
//
// File: Extensions.cs
//
// Description:
// Extensions class
//
// Author: qswang@live.cn
// 
// Modify History:
//
//
// Copyright (C) 2008 by qswang All rights reserved.
// 
//---------------------------------------------------------------------
using System.Runtime.InteropServices;
using System.Threading;
using System.Diagnostics;
using System.Reflection;
using System.Linq;
using System.Collections;
using System.ComponentModel;
using System.Web.Script.Serialization;
using System.Runtime.Remoting.Contexts;
using System.Runtime.Serialization.Json;
using System.IO;
using System.Text.RegularExpressions;

namespace System
{
    
    public static class ReflectExtensions
    {
       
        public static T GetProperty<T>(this object obj, string propertyName)
        {
            if (obj == null || string.IsNullOrEmpty(propertyName))
                return default(T);

            T value = default(T);
            //如果是对象是Dictionary类型的，需要另作处理
            Dictionary<string, object> map = obj as Dictionary<string, object>;
            if (map != null)
            {
                object tmpValue = null;
                map.TryGetValue(propertyName, out tmpValue);
                value = (T)tmpValue;
            }
            else
            {
                //处理普通对象
                Property p = ParseProperty(obj, propertyName);

                if (p != null && p.Name != null && p.Name.CanRead)
                {
                    try
                    {
                        value = (T)p.Name.GetValue(p.Owner, null);
                    }
                    finally { }
                }
            }
            return value;
        }
        
        public static object GetProperty(this object obj, string propertyName)
        {
            if (obj == null || string.IsNullOrEmpty(propertyName))
                return null;

            Property p = ParseProperty(obj, propertyName);

            if (p != null && p.Name != null && p.Name.CanRead)
            {
                try
                {
                    return p.Name.GetValue(p.Owner, null);
                }
                finally { }
            }
            return null;
        }
        
        public static void SetProperty(this object obj, string propertyName, object value)
        {
            if (obj == null || string.IsNullOrEmpty(propertyName))
                return;

            Property p = ParseProperty(obj, propertyName);
            if (p == null || p.Name == null)
                return;

            if (p.Name.CanRead)
            {
                try
                {
                    object old = p.Name.GetValue(p.Owner, null);
                    if (old == value)
                        return;
                }
                finally { }
            }

            if (p.Name.CanWrite)
            {
                try
                {
                    p.Name.SetValue(p.Owner, value, null);
                }
                finally { }
            }
        }

        private static readonly BindingFlags propertyBindingFlags = BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Static;
 

        private class Property
        {
            public readonly PropertyInfo Name;
            public readonly object Owner;

            public Property(PropertyInfo name, object owner)
            {
                Name = name;
                Owner = owner;
            }
        }
        
        private static Property ParseProperty(object root, string propertyName)
        {
            try
            {
                if (root == null)
                    return null;
                string[] items = propertyName.Split('.');
                if (items == null || items.Length < 1)
                    return null;
                //单个属性
                if (items.Length == 1)
                    return new Property(root.GetType().GetProperty(propertyName,propertyBindingFlags), root);
                //多个属性
                object target = root;

                string name = null;
                for (int i = 0; i < items.Length; i++)
                {
                    name = items[i];
                    //依据属性名称获取对象的属性
                    PropertyInfo p = target.GetType().GetProperty(name, propertyBindingFlags);
                    //取最后一个即属性的本身(过滤了该属性的基类)
                    if (i < items.Length - 1)
                        target = p.GetValue(target, null);
                }
                return new Property(target.GetType().GetProperty(name, propertyBindingFlags), target);
            }
            catch
            {
                return null;
            }
        }

    }

    
    public static class SequenceExtensions
    {
        public static void Clear<T>(this T[] items)
        {
            if (items == null) throw new ArgumentNullException("items");
            Array.Clear(items, 0, items.Length);
        }

        public static void ForEach<T>(this IEnumerable<T> items, Action<T> action)
        {
            if (items == null) throw new ArgumentNullException("items");
            if (action == null) throw new ArgumentNullException("action");

            foreach (var item in items)
                action(item);
        }

        public static IEnumerable<T> Filter<T>(this IEnumerable<T> items, Predicate<T> predicate)
        {
            if (items == null) throw new ArgumentNullException("items");
            if (predicate == null) throw new ArgumentNullException("predicate");

            foreach (var item in items)
            {
                if (predicate(item))
                    yield return item;
            }
        }

        // Seq.fold
        public static T Fold<T, U>(this IEnumerable<U> items, Func<T, U, T> func, T acc)
        {
            foreach (var item in items)
                acc = func(acc, item);

            return acc;
        }

        // F# List.fold_left
        public static T FoldLeft<T, U>(this IList<U> list, Func<T, U, T> func, T acc)
        {
            for (var index = 0; index < list.Count; index++)
                acc = func(acc, list[index]);

            return acc;
        }

        // F# List.fold_right
        public static T FoldRight<T, U>(this IList<U> list, Func<T, U, T> func, T acc)
        {
            for (var index = list.Count - 1; index >= 0; index--)
                acc = func(acc, list[index]);

            return acc;
        }

        public static void ForIndex<T>(this IEnumerable<T> items, Action<int, T> action)
        {
            if (items == null) throw new ArgumentNullException("items");
            if (action == null) throw new ArgumentNullException("action");

            var index = 0;
            foreach (var item in items)
            {
                action(index, item);
                index++;
            }
        }

    }

    public static class ICollectionExtensions
    {
        public static bool IsEmpty(this ICollection self)
        {
            return self.Count == 0;
        }
    }
   
}
