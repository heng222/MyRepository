//---------------------------------------------------------------------
//
// File: StringLengthValidatorAttribute.cs
//
// Description:
// String Length Validator class
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

namespace ProWrite.Core.Validation
{
    public class StringLengthValidatorAttribute:ValidatorBaseAttribute
    {
        private readonly int MinimumValue;
        private readonly int MaximumValue;

        public StringLengthValidatorAttribute(int minimumValue, int maximumValue)
        {
            if (!CompareHelper.Compare(CompareOp.LessThan, minimumValue, maximumValue))
                throw new Exception("MinimumValue cannot be greater than MaximumValue.");
            MinimumValue = minimumValue;
            MaximumValue = maximumValue;
        }

        public override bool IsValid(object target, object value)
        {
            const string errorText = "The value {0} must fall within the range ({1} - {2}) .";
            ErrorMessage = null;

            string str = value as string;
            int realLength = 0;

            if (string.IsNullOrEmpty(str))
            {
                ErrorMessage = string.Format(errorText, realLength, MinimumValue, MaximumValue);
                return false;
            }

            realLength = str.Length;
            if (realLength < MinimumValue || realLength > MaximumValue)
            {
                ErrorMessage = string.Format(errorText, realLength, MinimumValue, MaximumValue);
                return false;
            }

            return true;
        }
    }
}
