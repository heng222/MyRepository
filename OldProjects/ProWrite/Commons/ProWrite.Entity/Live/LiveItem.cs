using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using ProWrite.Core;
using System.Xml.Serialization;

namespace ProWrite.Entity.Live
{
    [Serializable]
    [TypeConverter(typeof(ExpandableObjectConverter))]
    public abstract class LiveItem:KeyInfo,ILiveItem
    {
        #region Non Serialized Fields
        [field: NonSerialized]
        [XmlIgnore]
        public EventHandler<PropertyChangedEventArgs> PropertyChanged;
        #endregion

        #region Serialized Fields
        #endregion

        #region Serialized Fields Version 2
        #endregion

        [Browsable(false)]
        public abstract LiveType Type { get; }

        public virtual object[] ToArray()
        {
            return new object[] { Name, Type, null };
        }

        public virtual bool IsReferenceLibrary(LiveItem library)
        {
            return false;
        }

        [Browsable(false)]
        public virtual LiveType AcceptType
        {
            get { return LiveType.None; }
        }
    }
}
