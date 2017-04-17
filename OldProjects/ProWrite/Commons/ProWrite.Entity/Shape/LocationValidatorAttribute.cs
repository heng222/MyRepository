using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core.Validation;
using ProWrite.Core;
using System.Drawing;

namespace ProWrite.Entity.Shape
{
    public class LocationValidatorAttribute:ValidatorBaseAttribute
    {
        private ValidatorType _valiType;
        public ValidatorType ValidatorType
        {
            get { return _valiType; }
            set { _valiType = value; }
        }

        public LocationValidatorAttribute()
        {
        }
        public LocationValidatorAttribute(ValidatorType validatorType)
        {
            _valiType = validatorType;
        }
        public override bool IsValid(object target, object value)
        {
            this.ErrorMessage = null;
            const string errText = "The value is invalid.";

            if (value == null)
            {
                ErrorMessage = errText;
                return false;
            }
            ShapeBase shap = target as ShapeBase;
            int cHeight = shap.SignSize.Height;
            int cWidth = shap.SignSize.Width;
            int newValue=Convert.ToInt32(value);
            if (_valiType == ValidatorType.Height)
            {
                //shap.VirtualBounds
                if (newValue < shap.Zoom)
                {
                    this.ErrorMessage = errText;
                    return false;
                }
            }
            if (_valiType == ValidatorType.Width)
            {
                if (newValue < shap.Zoom)
                {
                    this.ErrorMessage = errText;
                    return false;
                }
            }
            if (_valiType == ValidatorType.X)
            {
                int newX = newValue + shap.Width;
                if (newX > cWidth || newX < Constance.ShapeOffset)
                {
                    this.ErrorMessage = errText;
                    return false;
                }
            }
            if (_valiType == ValidatorType.Y)
            {
                int newY = newValue + shap.Height;
                if (newY > cHeight || newY < Constance.ShapeOffset)
                {
                    this.ErrorMessage = errText;
                    return false;
                }
            }

            return true;
        }
    }

    public enum ValidatorType
    {
        Height,
        Width,
        X,
        Y
    }
}
