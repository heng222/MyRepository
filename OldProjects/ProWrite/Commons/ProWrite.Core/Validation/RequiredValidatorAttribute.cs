//---------------------------------------------------------------------
//
// File: RangeValidatorAttribute.cs
//
// Description:
// Range Validator class
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

namespace ProWrite.Core.Validation
{
    public class RequiredValidatorAttribute:ValidatorBaseAttribute
    {
        public override bool IsValid(object target, object value)
        {
            this.ErrorMessage = null;
            const string errText = "The value is not allow empty.";

            if (value == null)
            {
                ErrorMessage = errText;
                return false;
            }

            if (value is string)
            {
                if (string.IsNullOrEmpty(((string)value)))
                {
                    this.ErrorMessage = errText;
                    return false;
                }
            }

            return true;
        }
    }
}
