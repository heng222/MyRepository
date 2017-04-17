//---------------------------------------------------------------------
//
// File: ValidationContext.cs
//
// Description:
// Validation Context class
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
    public class ValidationContext
    {
        public readonly object Target;
        public readonly Type TargetType;
        public readonly PropertyInfo Property;
        public readonly object Value;
        private bool _valid = true;
        private string _errorMessage;


        public ValidationContext(object target, PropertyInfo property, object value)
        {
            Target = target;
            TargetType = target.GetType();
            Property = property;
            if (value != null)
                Value = PopulateValue(value.ToString());
            else
                Value = null;
        }

        private object PopulateValue(string value)
        {
            return ConverterHelper.ToObject(Property.PropertyType, value);
        }
        
        public bool Valid
        {
            get { return _valid; }
            internal set { _valid = value; }
        }

        public string ErrorMessage
        {
            get { return _errorMessage; }
            internal set { _errorMessage = value; }
        }
    }
}
