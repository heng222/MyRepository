//---------------------------------------------------------------------
//
// File: CompareValidatorAttribute.cs
//
// Description:
// Compare Validator class
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
    public class CompareValidatorAttribute:ValidatorBaseAttribute
    {
        private readonly IComparable CompareTo;
        private readonly CompareOp Op;
        public CompareValidatorAttribute(CompareOp op, IComparable compareTo)
        {
            Op = op;
            CompareTo = compareTo;
        }

        public override bool IsValid(object target, object value)
        {
            ErrorMessage = null;
            const string errorText = "The value {0} must {1} {2}.";

            IComparable source = (IComparable)value;

            if (!CompareHelper.Compare(Op, source, CompareTo))
            {
                ErrorMessage = string.Format(errorText, source, Op.ToString(), CompareTo);
                return false;
            }

            return true;
        }
    }
}
