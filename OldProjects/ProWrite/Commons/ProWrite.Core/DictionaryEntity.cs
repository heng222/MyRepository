using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Xml.Serialization;

namespace ProWrite.Core
{
    [Serializable]
    public class DictionaryEntity : INotifyPropertyChanged,IErrorInfo
    {
        private Dictionary<string, object> _settings;
        [Browsable(false)]
        public Dictionary<string, object> Settings
        {
            get
            {
                if (_settings == null)
                    _settings = new Dictionary<string, object>();
                return _settings;
            }
            set
            {
                _settings = value;
            }
        }

        [NonSerialized]
        private ErrorProperty _error;

        [Browsable(false)]
        public ErrorProperty Error { get { return _error; } set { _error = value; } }


        protected internal T Get<T>(string name)
        {
            if(_settings==null)
                _settings = new Dictionary<string, object>();
            if (_settings.ContainsKey(name))
                return (T)_settings[name];
            _settings.Add(name, default(T));
            return default(T);
        }

        protected void Set<T>(string name, T value)
        {
            if (!Settings.ContainsKey(name))
            {
                Settings.Add(name, value);
            }
            else
            {
                T old = Get<T>(name);
                if (!object.Equals(old, value))
                {
                    Settings[name] = value;
                    if (_propertyChanged != null)
                    {
                        _propertyChanged(this, new PropertyChangedEventArgs(name));
                    }
                    
                }
            }
        }

        [NonSerialized]
        private PropertyChangedEventHandler _propertyChanged;
        public event PropertyChangedEventHandler PropertyChanged
        {
            add { _propertyChanged += value; }
            remove { _propertyChanged -= value; }
        }

        //[NonSerialized]
        //private PropertyChangedEventHandler _propertyChanged;
        //public event PropertyChangedEventHandler PropertyChanged
        //{
        //    add { _propertyChanged += value; }
        //    remove { _propertyChanged -= value; }
        //}
    }
}
