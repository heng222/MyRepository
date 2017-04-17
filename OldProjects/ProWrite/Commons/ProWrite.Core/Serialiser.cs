//---------------------------------------------------------------------
//
// File: Serialiser.cs
//
// Description:
// Binary deserialise or serialize class
//
// Author: Kevin
//
// Copyright (C) 2008 by Trans-Lux All rights reserved.
// 
//---------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Diagnostics;
using System.Runtime.Serialization;
using System.Xml.Serialization;
using log4net;
using System.ComponentModel;
using System.Net.Sockets;

namespace ProWrite.Core
{
    
    public enum SerialiseType:byte
    {
        Binary,
        Xml,
        Json,
    }

    public interface ISerialiser
    {
        void Serialize(object o, Stream stream);
        object Deserialise(Stream stream);
    }

    /// <summary>
    /// Generic binary serialiser
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public class Serialiser<T> : ISerialiser where T : class
    {
        private static readonly ILog _log = LogManager.GetLogger("Serialiser");
        private IFormatter _fmt;
        private SerialiseType _type;
        private static Serialiser<T> _binary;
        private static Serialiser<T> _xml;
        private static Serialiser<T> _json;
        private const int defaultBufferSize = 4096;
        private class XmlFormatter : IFormatter
        {
            private XmlSerializer _ser;
            public XmlFormatter(Type type)
            {
                Init(type);
            }

            private void Init(Type type)
            {
                try
                {
                    _ser = new XmlSerializer(type);
                }
                catch (Exception ex)
                {
                    _log.Error(ex.Message, ex);
                }
            }
            public SerializationBinder Binder
            {
                get
                {
                    throw new Exception("The method or operation is not implemented.");
                }
                set
                {
                    throw new Exception("The method or operation is not implemented.");
                }
            }

            public StreamingContext Context
            {
                get
                {
                    throw new Exception("The method or operation is not implemented.");
                }
                set
                {
                    throw new Exception("The method or operation is not implemented.");
                }
            }

            public object Deserialize(Stream serializationStream)
            {             
                return _ser.Deserialize(serializationStream);
            }

            public void Serialize(Stream serializationStream, object graph)
            {
                _ser.Serialize(serializationStream, graph);
            }

            public ISurrogateSelector SurrogateSelector
            {
                get
                {
                    throw new Exception("The method or operation is not implemented.");
                }
                set
                {
                    throw new Exception("The method or operation is not implemented.");
                }
            }
        }

        private class JsonFormatter : IFormatter
        {
            private System.Web.Script.Serialization.JavaScriptSerializer _ser = new System.Web.Script.Serialization.JavaScriptSerializer();
            
            public SerializationBinder Binder
            {
                get
                {
                    throw new Exception("The method or operation is not implemented.");
                }
                set
                {
                    throw new Exception("The method or operation is not implemented.");
                }
            }

            public StreamingContext Context
            {
                get
                {
                    throw new Exception("The method or operation is not implemented.");
                }
                set
                {
                    throw new Exception("The method or operation is not implemented.");
                }
            }

            public object Deserialize(Stream serializationStream)
            {
                using (StreamReader reader = new StreamReader(serializationStream))
                    return _ser.DeserializeObject(reader.ReadToEnd());
            }

            public void Serialize(Stream serializationStream, object graph)
            {
                if (serializationStream.CanWrite)
                {
                    using (StreamWriter writer = new StreamWriter(serializationStream))
                        writer.WriteLine(_ser.Serialize(graph));
                }
                
            }

            public ISurrogateSelector SurrogateSelector
            {
                get
                {
                    throw new Exception("The method or operation is not implemented.");
                }
                set
                {
                    throw new Exception("The method or operation is not implemented.");
                }
            }
        }

        private Serialiser(SerialiseType type)
        {
            _type = type;
            if (type == SerialiseType.Binary)
                _fmt = new BinaryFormatter();
            else if (type == SerialiseType.Json)
                _fmt = new JsonFormatter();
            else
                _fmt = new XmlFormatter(typeof(T));
        }

        public static Serialiser<T> Binaray
        {
            get
            {
                if (_binary == null)
                    _binary = new Serialiser<T>(SerialiseType.Binary);
                return _binary;
            }
        }

        public static Serialiser<T> Xml
        {
            get
            {
                if (_xml == null)
                    _xml = new Serialiser<T>(SerialiseType.Xml);
                return _xml;
            }
        }

        public static Serialiser<T> Json
        {
            get
            {
                if (_json == null)
                    _json = new Serialiser<T>(SerialiseType.Json);
                return _json;
            }
        }

        /// <summary>
        /// Serialise Type
        /// </summary>
        public SerialiseType Type
        {
            get { return _type; }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="file"></param>
        /// <returns></returns>
        public T Deserialise(string file)
        {
            Check.Assert(!string.IsNullOrEmpty(file));
            if (!File.Exists(file))
                return default(T);

            T ret = default(T);
            Stream stream = null;
            try
            {
                stream = File.OpenRead(file);
                ret = InternalDeserialize(stream);
            }
            catch (Exception ex)
            {
                _log.Error(ex.Message, ex);
                Debug.WriteLine(ex.Message);
            }
            finally
            {
                if (stream != null)
                    stream.Close();
                stream.Dispose();
                stream = null;
            }

            return ret;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="o"></param>
        /// <param name="file"></param>
        public void Serialize(T o, string file)
        {
            Check.Assert(o != null);
            Check.Assert(!string.IsNullOrEmpty(file));

            FileStream stream = null;
            try
            {
                if (!File.Exists(file))
                    stream = File.Create(file);
                else
                    stream = new FileStream(file, FileMode.OpenOrCreate);

                _log.Info("Serializing " + o.GetType().Name);
                InternalSerialize(o, stream);
                _log.Info("Serialized " + o.GetType().Name);
            }
            catch (Exception ex)
            {
                _log.Error(ex.Message, ex);
                Debug.WriteLine(ex.Message);
            }
            finally
            {
                if (stream != null)
                {
                    stream.Close();
                    stream.Dispose();
                    stream = null;
                }
            }
        }

        public T Deserialise(Stream stream)
        {
            Check.Assert(stream != null);
            //if (!(stream is NetworkStream))
            Check.Assert( stream.Length > 0);

            T ret = default(T);

            try
            {
                ret = InternalDeserialize(stream);
            }
            catch (Exception ex)
            {
                _log.Error(ex.Message, ex);
                Debug.WriteLine(ex.Message);
            }
            
            return ret;
        }

        object ISerialiser.Deserialise(Stream stream)
        {
            return Deserialise(stream) as T;
        }

        public void Serialize(T o, Stream stream)
        {
            Check.Assert(o != null);
            Check.Assert(stream != null);
            _log.Info("Serializing " + o.GetType().Name);
            try
            {
                _fmt.Serialize(stream, o);
            }
            catch (Exception ex)
            {
                _log.Error(ex.Message, ex);
                Debug.WriteLine(ex.Message);
            }
            _log.Info("Serialized" + o.GetType().Name);
        }

        void ISerialiser.Serialize(object o, Stream stream)
        {
            Serialize(o as T, stream);
        }

        private void InternalSerialize(T o, Stream stream)
        {
			//using (BufferedStream bs = new BufferedStream(stream, GetBufferSize(stream.Length)))
			//    _fmt.Serialize(bs, o);
        	_fmt.Serialize(stream, o);
        }

        private static int GetBufferSize(long length)
        {
            int onePercentSize = (int)Math.Ceiling(length / 100.0);
            return onePercentSize > defaultBufferSize ? defaultBufferSize : onePercentSize;
        }

        private T InternalDeserialize(Stream stream)
        {
            //using (BufferedStream bs = new BufferedStream(stream, GetBufferSize(stream.Length)))
            //    return (T)_fmt.Deserialize(bs);
            return (T)_fmt.Deserialize(stream);
        }
    }
}
