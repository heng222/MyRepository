//---------------------------------------------------------------------
//
// File: QueueAlertItem.cs
//
// Description:
// QueueAlert class 
//
// Author: Jerry
// Date  : 2009-7-10
//
// Modify history:
//      
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;
using System.Runtime.Serialization;
using System.Xml.Serialization;

namespace ProWrite.Entity.Live
{
    [Serializable]
    public class QueueAlertItem:KeyInfo
    {
        public QueueAlertItem()
        {
        }


        protected QueueAlertItem(SerializationInfo info, StreamingContext context)
        {

        }

        #region Properties define      

        [field: NonSerialized]
        [XmlIgnore]
        public EventHandler<PropertyChangedEventArgs> PropertyChanged;

        private QueueAlertLevel _level;
        public QueueAlertLevel Level
        {
            get
            {
                return _level;
            }
            set
            {
                _level = value;
            }
        }
        private int _length;
        public int Length
        {
            get
            {
                return _length;
            }
            set
            {                
                if (value != _length)
                {
                    _length = value;
                    MessageBus.Send(this, new SessionChangeMessage());
                }
            }
        }

        
        #endregion

        #region Functions define
        public QueueAlertItem Copy()
        {
            QueueAlertItem item = new QueueAlertItem();
            item.FromTo(this);
            return item;
        }

        public void FromTo(QueueAlertItem item)
        {
            this._length = item._length;
            this._level = item._level;
        }
        #endregion

    }
}
