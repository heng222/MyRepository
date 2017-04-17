//---------------------------------------------------------------------
//
// File: ValidatorBaseAttribute.cs
//
// Description:
// Validator Base class
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

namespace ProWrite.Core.Validation
{
    [AttributeUsage(AttributeTargets.Property)]
    public abstract class ValidatorBaseAttribute:Attribute
    {
        #region DataMember
        private string _errorMessage;
        protected internal PropertyInfo Property;
        #endregion

        #region Properties

        /// <summary>
        /// Get/Set for ErrorMessage
        /// </summary>
        public string ErrorMessage
        {
            get { return _errorMessage; }
            protected set { _errorMessage = value; }
        }

        #endregion

        public abstract bool IsValid(object target, object value);
    }
}
