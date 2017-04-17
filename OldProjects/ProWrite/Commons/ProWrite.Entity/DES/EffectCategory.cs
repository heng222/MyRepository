//---------------------------------------------------------------------
//
// File: EffectCategory.cs
//
// Description:
// Effect group
//
// Author: Kevin 2008-7-3
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Serialization;
using System.Reflection;
using System.IO;
using System.Linq;
using ProWrite.Core;
using ProWrite.Entity.DES.Effect;

namespace ProWrite.Entity.DES
{
	/// <summary>
	/// Effect group
	/// </summary>
	[Serializable]
	public class EffectCategory
	{
		/// <summary>
		/// group name
		/// </summary>
		private EffectType _name;
        //private bool _IsSystem;

		/// <summary>
		/// effect list
		/// </summary>
		private List<LayerEffect> _effects = new List<LayerEffect>();

		public EffectCategory()
		{
		}

		public EffectCategory(EffectType name)
		{
			_name = name;
		}

		/// <summary>
		/// populate effect type in current group
		/// </summary>
		public void PopulateEffectType()
		{
			if (_effects.Count > 0)
			{
				foreach (LayerEffect effect in _effects)
					effect.Type = _name;
			}
		}

		/// <summary>
		/// get or set group name
		/// </summary>
		[XmlAttribute]
		public EffectType Name
		{
			get { return _name; }
			set { _name = value; }
		}

		/// <summary>
		/// get or set effect list
		/// </summary>
		[XmlArrayItem("Effect")]
		public List<LayerEffect> Effects
		{
			get { return _effects; }
			set { _effects = value; }
		}

		[NonSerialized]
		private static List<EffectCategory> _effectCategory;

		public static Property[] GetEffectProperties(Guid id)
		{
			if (_effectCategory == null)
				return null;

			foreach (EffectCategory item in _effectCategory)
			{
				foreach (LayerEffect eff in item.Effects)
				{
					if (eff.GUID == id)
						return eff.ToPropertyArray();
				}
			}

			return null;
		}

		/// <summary>
		/// get effect groups
		/// </summary>
		public static List<EffectCategory> EffectGroups
		{
			get
			{
				if (_effectCategory != null)
					return _effectCategory;
                _effectCategory = new List<EffectCategory>();
                _effectCategory.Add(new EffectCategory(EffectType.Entry));
                _effectCategory.Add(new EffectCategory(EffectType.Emphasis));
                _effectCategory.Add(new EffectCategory(EffectType.Exit));
                SetEffect();

                //List<EffectCategory> newCategory;
                ////edit by Michael
                //string[] fileArr = Directory.GetFiles(Constance.AppPath + "Effect");
                //Serialiser<List<EffectCategory>> ser = Serialiser<List<EffectCategory>>.Xml;
                //foreach (string file in fileArr)
                //{
                //    if (File.Exists(file))
                //    {
                //        newCategory = ser.Deserialise(file);
                //        foreach (EffectCategory item in newCategory)
                //            item.PopulateEffectType();
                //        MergeCategory(newCategory);
                //    }
                //}
				return _effectCategory;
			}
		}

        private static void SetEffect()
        {

            _effectCategory[0].Effects.Add(new EffectSlide { Type = EffectType.Entry });
            _effectCategory[0].Effects.Add(new EffectWipe { Type = EffectType.Entry });
            _effectCategory[1].Effects.Add(new EffectFlash());
            _effectCategory[2].Effects.Add(new EffectSlide { Type = EffectType.Exit });
            _effectCategory[2].Effects.Add(new EffectWipe { Type = EffectType.Exit });

//#if VERSION_2
            ////_effectCategory[0].Effects.Add(new EffectSlide { Type = EffectType.Entry });
            ////_effectCategory[0].Effects.Add(new EffectWipe { Type = EffectType.Entry });
            //_effectCategory[0].Effects.Add(new EffectCoalesce { Type = EffectType.Entry });
            //_effectCategory[0].Effects.Add(new EffectRain { Type = EffectType.Entry });
            //_effectCategory[0].Effects.Add(new EffectBounce { Type = EffectType.Entry });
            //_effectCategory[0].Effects.Add(new EffectBlackHole { Type = EffectType.Entry });
            //_effectCategory[0].Effects.Add(new EffectFade { Type = EffectType.Entry });
            //_effectCategory[0].Effects.Add(new EffectFilter { Type = EffectType.Entry });


            //_effectCategory[0].Effects.Add(new EffectSlot { Type = EffectType.Entry });
            _effectCategory[0].Effects.Add(new EffectInterleave { Type = EffectType.Entry });
            _effectCategory[0].Effects.Add(new EffectLine { Type = EffectType.Entry });

            //_effectCategory[0].Effects.Add(new EffectMultiWipe { Type = EffectType.Entry });
            ////_effectCategory[0].Effects.Add(new EffectPush { Type = EffectType.Entry }.ToLayerEffect());
            //_effectCategory[0].Effects.Add(new EffectRadar { Type = EffectType.Entry });
            _effectCategory[0].Effects.Add(new EffectVenetian { Type = EffectType.Entry });


            //_effectCategory[1].Effects.Add(new EffectSnow());
            _effectCategory[1].Effects.Add(new EffectBijou());
            //_effectCategory[1].Effects.Add(new EffectSparkle());
            ////_effectCategory[1].Effects.Add(new EffectFlash());
            //_effectCategory[1].Effects.Add(new EffectWrapAround());
            //_effectCategory[1].Effects.Add(new EffectTravel());

            //_effectCategory[2].Effects.Add(new EffectCoalesce { Type = EffectType.Exit });
            //_effectCategory[2].Effects.Add(new EffectBlackHole { Type = EffectType.Exit });
            //_effectCategory[2].Effects.Add(new EffectFade { Type = EffectType.Exit });
            //_effectCategory[2].Effects.Add(new EffectFilter { Type = EffectType.Exit });
            ////_effectCategory[2].Effects.Add(new EffectSlot { Type = EffectType.Exit}.ToLayerEffect());
            _effectCategory[2].Effects.Add(new EffectInterleave { Type = EffectType.Exit });
            _effectCategory[2].Effects.Add(new EffectLine { Type = EffectType.Exit });
            //_effectCategory[2].Effects.Add(new EffectMultiWipe { Type = EffectType.Exit });
            ////_effectCategory[2].Effects.Add(new EffectPush { Type = EffectType.Exit }.ToLayerEffect());
            //_effectCategory[2].Effects.Add(new EffectRadar { Type = EffectType.Exit });
            _effectCategory[2].Effects.Add(new EffectVenetian { Type = EffectType.Exit });

            ////_effectCategory[2].Effects.Add(new EffectCopy { Type = EffectType.Exit }.ToLayerEffect());
            ////_effectCategory[2].Effects.Add(new EffectSlide { Type = EffectType.Exit });
            ////_effectCategory[2].Effects.Add(new EffectWipe { Type = EffectType.Exit });
//#endif
        }

        private static void MergeCategory(List<EffectCategory> newCategory)
        {
            foreach (EffectCategory item in newCategory)
            {
                if (item._name == EffectType.Entry)
                {
                    MergeEffect(_effectCategory[0].Effects, item);
                }
                if (item._name == EffectType.Emphasis)
                {
                    MergeEffect(_effectCategory[1].Effects, item);
                }
                if (item._name == EffectType.Exit)
                {
                    MergeEffect(_effectCategory[2].Effects, item);
                }
            }
        }

        private static void MergeEffect(List<LayerEffect> effects, EffectCategory _category)
        {
            bool IsExit = false;
            foreach (LayerEffect item in _category.Effects)
            {
                IsExit = false;
                foreach (LayerEffect efc in effects)
                {
                    if (efc.Name == item.Name)
                    {
                        IsExit = true;
                        break;
                    }
                }
                if (!IsExit)
                    effects.Add(item);
            }
        }

        public  void Dispoble()
        {
            if (_effects != null)
            {
                int length = _effects.Count;
                if (length > 0)
                {
                    for (int i = 0; i < length; i++)
                    {
                        _effects[i].Dispose();
                        _effects[i] = null;
                    }
                    _effects.Clear();
                    _effects = null;
                }
            }
        }

    }
}