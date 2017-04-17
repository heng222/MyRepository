using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Core;
using ProWrite.Entity.DES;
using System.Drawing;
using ProWrite.Entity.DES.Effect;

namespace ProWrite.Entity.DES
{
	[Serializable]
	public class Layer :IEquatable<Layer>,IComparable,IComparable<Layer>
	{
		private int _ID;
		public int ID
		{
			get{return _ID;}
			set
			{
				_ID = value;
			}
		}

		private string _Name;
		public string Name
		{
			get { return _Name; }
			set
			{
				if (value != Name)
				{
					_Name = value;
				}
			}
		}

		private bool _Visible;
		public bool Visible
		{
			get { return _Visible; }
			set
			{
				if (value != Visible)
				{
					_Visible = value;
				}
			}
		}

		private LayerType _Type;
		public LayerType LayerType
		{
			get { return _Type; }
			set
			{
				if (value != LayerType)
				{
					_Type = value;
				}
			}
		}

		private int _Level = 0;
		public int Level
		{
			get { return _Level; }
			set
			{
				if (value != Level)
				{
					_Level = value;
				}
			}
		}

        private Rectangle _Rect;
        public Rectangle Rect
		{
			get { return _Rect; }
			set
			{
				_Rect = value;
			}
		}

		private long _StartTime = 0;
		public long StartTime
		{
			get { return _StartTime; }
			set
			{
				if (value != StartTime)
				{
					_StartTime = value;
				}
			}
		}

		private long _EndTime = 0;
		public long EndTime
		{
			get { return _EndTime; }
			set
			{
				if (value != EndTime)
				{
					_EndTime = value;
				}
			}
		}

		private string _FilePath = "";
		public string FilePath
		{
			get{return _FilePath;}
			set
			{
				if (value != FilePath)
				{
					_FilePath = value;
				}
			}
		}


        public EffectTravel TextInfo { get; set; }

		private LayerEffect _EntryEffect;
		public LayerEffect EntryEffect
		{
			get{return _EntryEffect;}
			set
			{
				if (value != EntryEffect)
				{
					_EntryEffect = value;
				}
			}
		}

		private LayerEffect _EmphasisEffect;
		public LayerEffect EmphasisEffect
		{
			get{return _EmphasisEffect;}
			set
			{
				if (value != EmphasisEffect)
				{
					_EmphasisEffect = value;
				}
			}
		}

		private LayerEffect _ExitEffect;
		public LayerEffect ExitEffect
		{
			get { return _ExitEffect; }
			set
			{
				if (value != ExitEffect)
				{
					_ExitEffect = value;
				}
			}
		}
        
		public bool Equals(Layer other)
		{
			if (other == null)
				return false;
			//if (Active != other.Active)
			//    return false;
			return base.Equals(other);
		}

		public override bool Equals(object obj)
		{
			return Equals(obj as Layer);
		}

		public int CompareTo(object obj)
		{
			return CompareTo(obj as Layer);
		}

		public int CompareTo(Layer other)
		{
			return Level.CompareTo(other.Level);
		}

		public override int GetHashCode()
		{
			return base.GetHashCode();
		}
	}
}