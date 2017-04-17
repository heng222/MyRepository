using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using System.ComponentModel;
using PropertyChangedEventArgs = ProWrite.Entity.PropertyChangedEventArgs;
using ProWrite.Core;

namespace ProWrite.Entity
{
    [Serializable]
    public class UndoObject : DisposableObject, IEditableObject, IChangeTracking
    {
        [XmlIgnore]
        [NonSerialized]
        private EventHandler<PropertyChangedEventArgs> _PropertyChanged;
        [XmlIgnore]
        [NonSerialized]
        private bool _isChanged;
        [XmlIgnore]
        [NonSerialized]
        private int _editLevel;

        [Browsable(false)]
        public event EventHandler<PropertyChangedEventArgs> PropertyChanged
        {
            add { _PropertyChanged += value; }
            remove { _PropertyChanged -= value; }
        }

        /// <summary>
        /// Update frame layer control
        /// </summary>
        /// <param name="propertyName">property name</param>
        protected virtual void OnPropertyChanged(string propertyName, object newValue, object oldValue)
        {
            _isChanged = true;
            if (IsEdit)
                return;

            UndoManager undoMgr = UndoManager.Current;
            if (undoMgr != null)
            {
                if (undoMgr.BeginTransaction("Changed the " + propertyName + "Property"))
                {
                    undoMgr.AddAction(new SimpleUndoAction
                    {
                        UndoHandler = () => this.SetProperty(propertyName, oldValue),
                        RedoHandler = () => this.SetProperty(propertyName, newValue),
                    });
                    undoMgr.Commit();
                }
            }

            if (_PropertyChanged != null)
                _PropertyChanged(this, new PropertyChangedEventArgs(propertyName, newValue, oldValue));
        }
        

        /// <summary>
        /// Judge whether data is changed
        /// </summary>
        [Browsable(false)]
        public virtual bool IsChanged
        {
            get { return _isChanged; }
        }

        /// <summary>
        /// Accept change
        /// </summary>
        public virtual void AcceptChanges()
        {
            _isChanged = false;
        }

        

        [Browsable(false)]
        public bool IsEdit
        {
            get { return _editLevel > 0; }
        }

        public void BeginEdit()
        {
            _editLevel++;
        }

        public void CancelEdit()
        {
            _editLevel--;
        }

        public void EndEdit()
        {
            _editLevel--;
        }

        protected override void Dispose(bool disposing)
        {
            _PropertyChanged = null;
            base.Dispose(disposing);
        }
    }
}
