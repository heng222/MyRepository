using System;
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
using System.Text;
using ProWrite.Core;

namespace ProWrite.Core.Validation
{
    public class RangeValidatorAttribute:ValidatorBaseAttribute
    {
        private IComparable MinimumValue;
        private IComparable MaximumValue;

        public RangeValidatorAttribute(int minimumValue, int maximumValue)
        {
            Init(minimumValue, maximumValue);
        }

        protected void Init(IComparable minimumValue, IComparable maximumValue)
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

            if (CompareHelper.Compare(CompareOp.LessThan, value as IComparable, MinimumValue as IComparable))
            {
                ErrorMessage = string.Format(errorText, value, MinimumValue, MaximumValue);
                return false;
            }

            if (CompareHelper.Compare(CompareOp.GreaterThan, value as IComparable, MaximumValue as IComparable))
            {
                ErrorMessage = string.Format(errorText, value, MinimumValue, MaximumValue);
                return false;
            }

            return true;
        }

    }
}
