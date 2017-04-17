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

namespace ProWrite.UFE.Files
{
    
    /// <summary>
    /// Generic binary serialiser
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public class XmlSerialiser<T> 
        where T : class
    {
        private XmlSerializer _ser;
        public XmlSerializerNamespaces Namespaces { get; set;}

        public XmlSerialiser()
        {
            _ser = new XmlSerializer(typeof(T));
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="file"></param>
        /// <returns></returns>
        public T Deserialise(string file)
        {
            Check.Assert(!string.IsNullOrEmpty(file));
          
            T ret = default(T);
            Stream stream = null;
            try
            {
                stream = File.OpenRead(file);

                ret = InternalDeserialize(stream);
            }
            catch (Exception ex)
            {
                throw ex;
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

                InternalSerialize(o, stream);
            }
            catch (Exception ex)
            {
                throw ex;
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

            ret = InternalDeserialize(stream);
            
            return ret;
        }

       

        //public void Serialize(T o, Stream stream)
        //{
        //    Check.Assert(o != null);
        //    Check.Assert(stream != null);

        //    _ser.Serialize(stream, o, Namespaces);
        //}

       

        private void InternalSerialize(T o, Stream stream)
        {
			//using (BufferedStream bs = new BufferedStream(stream, GetBufferSize(stream.Length)))
			//    _fmt.Serialize(bs, o);
            _ser.Serialize(stream, o,Namespaces );
        }

      
        private T InternalDeserialize(Stream stream)
        {
            //using (BufferedStream bs = new BufferedStream(stream, GetBufferSize(stream.Length)))
            //    return (T)_fmt.Deserialize(bs);
            return (T)_ser.Deserialize(stream);
        }
    }
}
