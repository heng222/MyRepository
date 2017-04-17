using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using System.IO;
using System.Xml.Serialization;
using ProWrite.Core;

namespace ProWrite.Core
{
	public class KeyGenerator
	{
		private static InnerGenerator gen = InnerGenerator.Instance;

		private static Sequence _shape;
		public static long Shape
		{
			get
			{
				if (_shape != null)
					return _shape.Next;
				_shape = gen.Get("Shape");
				return _shape.Next;
			}
		}

		private static Sequence _library;
		public static long Library
		{
			get
			{
				if (_library != null)
					return _library.Next;
				_library = gen.Get("Library");
				return _library.Next;
			}
		}

        private static Sequence _signTemplate;
        public static long Table
        {
            get
            {
                if (_signTemplate != null)
                    return _signTemplate.Next;
                _signTemplate = gen.Get("Table");
                return _signTemplate.Next;
            }
        }

        private static Sequence _templateRegion;
        public static long Cell
        {
            get
            {
                if (_templateRegion != null)
                    return _templateRegion.Next;
                _templateRegion = gen.Get("Cell");
                return _templateRegion.Next;
            }
        }

        private static Sequence _templateRow;
        public static long Row
        {
            get
            {
                if (_templateRow != null)
                    return _templateRow.Next;
                _templateRow = gen.Get("Row");
                return _templateRow.Next;
            }
        }

		private class InnerGenerator:IDisposable
		{

			string file = Constance.DataPath + "keys.xml";
			internal List<Sequence> seqs = null;
			//private Serialiser<List<Sequence>> ser = null;

			public static readonly InnerGenerator Instance = new InnerGenerator(); 
			private InnerGenerator()
			{
                //ser = Serialiser<List<Sequence>>.Xml;

                
                //if (File.Exists(file))
                //{
                //    seqs = ser.Deserialise(file);
                //}

				if (seqs == null)
					seqs = new List<Sequence>();
			}

			public Sequence Get(string name)
			{
				Sequence seq = seqs.Find(delegate(Sequence item)
				                         	{
				                         		return item.Name == name;
				                         	});

				if (seq == null)
				{
					seq = new Sequence(name);
					seqs.Add(seq);
				}

				return seq;
			}

			public void Dispose()
			{
				Save();
			}

			public void Save()
			{
                //ser.Serialize(seqs, file);
			}
		}

		public static void Save()
		{
            //gen.Save();
		}
	}

	[Serializable]
	public class Sequence
	{

        public long Current;
        public string Name;
		public int Seed;

		public Sequence() { }
		internal Sequence(string name) : this(name, 1) { }
		internal Sequence(string name, int seed)
		{
			Name = name;
			Seed = seed;
		}

		private static readonly object _lock = new object();

		public long Next
		{
			get
			{
				lock (_lock)
				{
					Current += Seed;
					return Current;
				}
			}
		}
	}
}