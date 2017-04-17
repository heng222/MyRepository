//---------------------------------------------------------------------
//
// File: ValidationService.cs
//
// Description:
// Validation Service class
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

namespace ProWrite.Core.Validation
{
    public static class ValidationService
    {
        private static readonly Dictionary<Type, Dictionary<PropertyInfo, List<ValidatorBaseAttribute>>> _maps;
        static ValidationService()
        {
            _maps = new Dictionary<Type, Dictionary<PropertyInfo, List<ValidatorBaseAttribute>>>();
        }

        public static void Register(Assembly asm)
        {
            if (asm == null)
                return;
            Type[] types = asm.GetTypes();
            if (types == null || types.Length < 1)
                return;
            foreach (Type type in types)
            {
                PropertyInfo[] props = type.GetProperties();
                if (props == null || props.Length < 1)
                    continue;
                foreach (PropertyInfo p in props)
                {
                    object[] objs = p.GetCustomAttributes(typeof(ValidatorBaseAttribute),true) ;
                    if (objs == null)
                        continue;
                    if (!_maps.ContainsKey(type))
                        _maps[type] = new Dictionary<PropertyInfo,List<ValidatorBaseAttribute>>();
                    List<ValidatorBaseAttribute> validators = new List<ValidatorBaseAttribute>(objs.Length);
                    foreach (ValidatorBaseAttribute validate in objs)
                    {
                        validate.Property = p;
                        validators.Add(validate);
                    }

                    _maps[type][p] = validators;
                }
            }
        }

        public static void Validate(ValidationContext ctx)
        {
            if (ctx == null
                || ctx.Target == null
                || ctx.Property == null
                || !_maps.ContainsKey(ctx.TargetType)
                || !_maps[ctx.TargetType].ContainsKey(ctx.Property))
                return;

            List<ValidatorBaseAttribute> validators = _maps[ctx.TargetType][ctx.Property];
            if (validators == null
                || validators.Count < 1)
                return;

            bool valid = true;
            StringBuilder sb = new StringBuilder();
            foreach (ValidatorBaseAttribute validator in validators)
            {
                if (!validator.IsValid(ctx.Target, ctx.Value))
                {
                    valid = false;
                    sb.Append(validator.ErrorMessage).AppendLine();
                }
            }

            ctx.Valid = valid;
            ctx.ErrorMessage = sb.ToString();
        }

        public static void Dispose()
        {
            _maps.Clear();
        }
    }
}
