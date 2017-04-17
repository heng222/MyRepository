//---------------------------------------------------------------------
//
// File: TemplateType.cs
//      
// Description:
//      Template type enum
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

namespace ProWrite.Entity.Settings
{
	[Serializable]
	public enum TemplateType
	{
        [EnumDescription]
		Sign,
        [EnumDescription]
		Message,
        [EnumDescription]
		Playlist,
        [EnumDescription]
		TimeScliceGroup,
        [EnumDescription]
		Scheduler,
        [EnumDescription("Shape")]
		ShapeLayer,
        [EnumDescription("Paint")]
        PaintLayer,
        [EnumDescription]
		Line,
        [EnumDescription("Text")]
		TextLayer,
        [EnumDescription("Image")]
		ImageLayer,
        [EnumDescription("Dynamic Text")]
		DynamicTextLayer,
        [EnumDescription("Temperature")]
		TemperatureLayer,
        [EnumDescription("Time")]
		TimeLayer,
        [EnumDescription("Video")]
		VideoLayer,
	}

    
}