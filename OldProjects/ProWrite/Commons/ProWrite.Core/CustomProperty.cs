using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using System.ComponentModel;

namespace ProWrite.Core
{
    public class CustomProperty
    {
        #region Private Variables
        private string _name = string.Empty;
        private object _defaultValue = null;
        private object _value = null;
        private object _objectSource = null;
        private PropertyInfo[] _propertyInfos = null;
        #endregion

        #region Contructors
        public CustomProperty()
        {
        }

        public CustomProperty(string name, string category, string description, object objectSource)
            : this(name, name, null, category, description, objectSource, null)
        {
        }

        public CustomProperty(string name, string propertyName, string category, string description, object objectSource)
            : this(name, propertyName, null, category, description, objectSource, null)
        {
        }

        public CustomProperty(string name, string propertyName, string category, string description, object objectSource, Type editorType)
            : this(name, propertyName, null, category, description, objectSource, editorType)
        {
        }

        public CustomProperty(string name, string propertyName, Type valueType, string category, string description,
            object objectSource, Type editorType)
            : this(name, new string[] { propertyName }, valueType, null, null, false, true, category, description, objectSource, editorType)
        {
        }

        public CustomProperty(string name, string[] propertyNames, string category, string description, object objectSource)
            : this(name, propertyNames, category, description, objectSource, null)
        {
        }

        public CustomProperty(string name, string[] propertyNames, string category, string description, object objectSource, Type editorType)
            : this(name, propertyNames, null, category, description, objectSource, editorType)
        {
        }

        public CustomProperty(string name, string[] propertyNames, Type valueType, string category, string description,
            object objectSource, Type editorType)
            : this(name, propertyNames, valueType, null, null, false, true, category, description, objectSource, editorType)
        {
        }

        public CustomProperty(string name, string[] propertyNames, Type valueType, object defaultValue, object value,
            bool isReadOnly, bool isBrowsable, string category, string description, object objectSource, Type editorType)
        {
            Name = name;
            PropertyNames = propertyNames;
            ValueType = valueType;
            _defaultValue = defaultValue;
            _value = value;
            IsReadOnly = isReadOnly;
            IsBrowsable = isBrowsable;
            Category = category;
            Description = description;
            ObjectSource = objectSource;
            EditorType = editorType;
        }
        #endregion

        #region Public Properties

        public string Name
        {
            get { return _name; }
            set
            {
                _name = value;

                if (PropertyNames == null)
                {
                    PropertyNames = new string[] { _name };
                }
            }
        }

        public string[] PropertyNames;

        public Type ValueType;

        public object DefaultValue
        {
            get { return _defaultValue; }
            set
            {
                _defaultValue = value;
                if (_defaultValue != null)
                {
                    if (_value == null) _value = _defaultValue;
                    if (ValueType == null) ValueType = _defaultValue.GetType();
                }
            }
        }

        public object Value
        {
            get { return _value; }
            set
            {
                _value = value;

                OnValueChanged();
            }
        }

        public bool IsReadOnly;

        public string Description;

        public string Category;

        public bool IsBrowsable;

        public object ObjectSource
        {
            get { return _objectSource; }
            set
            {
                _objectSource = value;
                OnObjectSourceChanged();
            }
        }

        public Type EditorType;
        #endregion

        #region Protected Functions

        protected void OnObjectSourceChanged()
        {
            if (PropertyInfos.Length == 0) return;

            object value = PropertyInfos[0].GetValue(_objectSource, null);
            if (_defaultValue == null) DefaultValue = value;
            _value = value;
        }

        protected void OnValueChanged()
        {
            if (_objectSource == null) return;

            foreach (PropertyInfo propertyInfo in PropertyInfos)
            {
                propertyInfo.SetValue(_objectSource, _value, null);
            }
        }

        protected PropertyInfo[] PropertyInfos
        {
            get
            {
                if (_propertyInfos == null)
                {
                    Type type = ObjectSource.GetType();
                    _propertyInfos = new PropertyInfo[PropertyNames.Length];
                    for (int i = 0; i < PropertyNames.Length; i++)
                    {
                        _propertyInfos[i] = type.GetProperty(PropertyNames[i]);
                    }
                }
                return _propertyInfos;
            }
        }
        #endregion

        #region Prublic Functions
        public void ResetValue()
        {
            Value = DefaultValue;
        }
        #endregion
    }

    public class CustomPropertyCollection : List<CustomProperty>, ICustomTypeDescriptor
    {
        #region ICustomTypeDescriptor ≥…‘±

        public AttributeCollection GetAttributes()
        {
            return TypeDescriptor.GetAttributes(this, true);
        }

        public string GetClassName()
        {
            return TypeDescriptor.GetClassName(this, true);
        }

        public string GetComponentName()
        {
            return TypeDescriptor.GetComponentName(this, true);
        }

        public TypeConverter GetConverter()
        {
            return TypeDescriptor.GetConverter(this, true);
        }

        public EventDescriptor GetDefaultEvent()
        {
            return TypeDescriptor.GetDefaultEvent(this, true);
        }

        public PropertyDescriptor GetDefaultProperty()
        {
            return TypeDescriptor.GetDefaultProperty(this, true);
        }

        public object GetEditor(Type editorBaseType)
        {
            return TypeDescriptor.GetEditor(this, editorBaseType, true);
        }

        public EventDescriptorCollection GetEvents(Attribute[] attributes)
        {
            return TypeDescriptor.GetEvents(this, attributes, true);
        }

        public EventDescriptorCollection GetEvents()
        {
            return TypeDescriptor.GetEvents(this, true);
        }

        public PropertyDescriptorCollection GetProperties(Attribute[] attributes)
        {
            PropertyDescriptorCollection properties = new PropertyDescriptorCollection(null);

            foreach (CustomProperty cp in this)
            {
                List<Attribute> attrs = new List<Attribute>();
                //[Browsable(false)]
                if (!cp.IsBrowsable)
                {
                    attrs.Add(new BrowsableAttribute(cp.IsBrowsable));
                }
                //[ReadOnly(true)]
                if (cp.IsReadOnly)
                {
                    attrs.Add(new ReadOnlyAttribute(cp.IsReadOnly));
                }
                //[Editor(typeof(editor),typeof(UITypeEditor))]
                if (cp.EditorType != null)
                {
                    attrs.Add(new EditorAttribute(cp.EditorType, typeof(System.Drawing.Design.UITypeEditor)));
                }

                properties.Add(new CustomPropertyDescriptor(cp, attrs.ToArray()));
            }
            return properties;
        }

        public PropertyDescriptorCollection GetProperties()
        {
            return TypeDescriptor.GetProperties(this, true);
        }

        public object GetPropertyOwner(PropertyDescriptor pd)
        {
            return this;
        }

        #endregion
    }

    public class CustomPropertyDescriptor : PropertyDescriptor
    {
        private CustomProperty _customProperty = null;

        public CustomPropertyDescriptor(CustomProperty customProperty, Attribute[] attrs)
            : base(customProperty.Name, attrs)
        {
            _customProperty = customProperty;
        }

        public override bool CanResetValue(object component)
        {
            return _customProperty.DefaultValue != null;
        }

        public override Type ComponentType
        {
            get { return _customProperty.GetType(); }
        }

        public override object GetValue(object component)
        {
            return _customProperty.Value;
        }

        public override bool IsReadOnly
        {
            get { return _customProperty.IsReadOnly; }
        }

        public override Type PropertyType
        {
            get { return _customProperty.ValueType; }
        }

        public override void ResetValue(object component)
        {
            _customProperty.ResetValue();
        }

        public override void SetValue(object component, object value)
        {
            _customProperty.Value = value;
        }

        public override bool ShouldSerializeValue(object component)
        {
            return true;
        }

        //
        public override string Description
        {
            get
            {
                return _customProperty.Description;
            }
        }

        public override string Category
        {
            get
            {
                return _customProperty.Category;
            }
        }

        public override string DisplayName
        {
            get
            {
                return _customProperty.Name;
            }
        }

        public override bool IsBrowsable
        {
            get
            {
                return _customProperty.IsBrowsable;
            }
        }

        public object CustomProperty
        {
            get
            {
                return _customProperty;
            }
        }
    }
}
