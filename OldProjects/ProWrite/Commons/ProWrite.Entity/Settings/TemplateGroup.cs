//---------------------------------------------------------------------
//
// File: TemplateGroup.cs
//      
// Description:
//      Template group class
//
// Author: Kevin 2008-7-28
//
// Modify History:
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using System.Collections;
using System.ComponentModel;
using ProWrite.Entity.Settings;
using ProWrite.Core;

namespace ProWrite.Entity.Settings
{
	/// <summary>
	/// Template group class
	/// </summary>
	[Serializable]
	[TypeConverter(typeof(ExpandableObjectConverter))]
    //[SettingView(SR.TemplateGroup)]
    public class TemplateGroup : KeyInfo, IOptionViewable,IEnumerable<TemplateInfo>
	{
		public TemplateGroup():this(false)
		{
		}

		private TemplateGroup(bool isDefault)
        {
            _sign = new SignTemplateInfo();
            _message = new MessageTemplate();
            _playlist = new PlayListTemplate();
            _scheduler = new SchedulerTemplate();
            _isDefault = isDefault;
            InitShape();

			if (_isDefault)
				Name = "System Default";
		}

        private void InitShape()
        {
            _message.DynamicTextLayer.Sign = _sign;
            _message.ImageLayer.Sign = _sign;
            _message.TextLayer.Sign = _sign;
            _message.VideoLayer.Sign = _sign;
            _message.TemperatureLayer.Sign = _sign;
            _message.TimeLayer.Sign = _sign;
        }

        [ReadOnly(true)]
        public override string Name
        {
            get { return base.Name; }
            set { base.Name = value; }
        }
    

		private SignTemplateInfo _sign;
		public SignTemplateInfo Sign
		{
			get { return _sign; }
			set { _sign = value; }
		}

        private MessageTemplate _message;

        public MessageTemplate Message
        {
            get { return _message; }
            set { _message = value; }
        }

        private PlayListTemplate _playlist;
        [Browsable(false)]
        public PlayListTemplate Playlist
        {
            get { return _playlist; }
            set { _playlist= value; }
        }

        private SchedulerTemplate _scheduler;

        public SchedulerTemplate Scheduler
        {
            get { return _scheduler; }
            set { _scheduler = value; }
        }

        
		private bool _isDefault;
		public virtual bool IsDefault
		{
			get { return _isDefault; }
		}

		private static TemplateGroup _current;
		public static TemplateGroup Current
		{
			get
			{
				if (_current == null)
					_current = Default;
				return _current;
			}

			set { _current = value; }
		}

		private static TemplateGroup _default;
		public static TemplateGroup Default
		{
			get
			{
				if (_default == null)
					_default = new TemplateGroup(true);
				return _default;
			}
			set { _default = value; }
		}

		[OnDeserialized]
		private void Deserialized(StreamingContext ctx)
		{
			if (_isDefault)
				_default = this;
            InitShape();
		}

        public TemplateGroup Copy()
        {
            TemplateGroup clone = new TemplateGroup();
            clone.Name = Name;
            clone._sign = CloneManager.Clone<SignTemplateInfo>(_sign);
            clone._scheduler = CloneManager.Clone<SchedulerTemplate>(_scheduler);
            clone._playlist = CloneManager.Clone<PlayListTemplate>(_playlist);
            clone._message = CloneManager.Clone<MessageTemplate>(_message);
            return clone;
        }

        public string View()
        {
            return SR.View.TemplateGroup;
        }

		#region IEnumerable<TemplateInfo> Members

		public IEnumerator<TemplateInfo> GetEnumerator()
		{
			yield return _sign;
            yield return _message;
            //yield return _playlist;
            yield return _scheduler;
		}

		#endregion

		#region IEnumerable Members

		IEnumerator IEnumerable.GetEnumerator()
		{
			return GetEnumerator() as IEnumerator;
		}
        
		#endregion
       
    }

    public interface IOptionViewable
    {
        string View();
    }
}