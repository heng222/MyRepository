using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Web.Script.Serialization;
namespace System
{
    
    public static class SerializeExtensions
    {
       
        public static string ToJson(this object obj)
        {
            JavaScriptSerializer serializer = new JavaScriptSerializer();
            try
            {
                var st = serializer.Serialize(obj);
                return st;
            }
            finally { }
        }
        
        public static T FromJson<T>(this object obj, string json)
        {
            try
            {
                JavaScriptSerializer serializer = new JavaScriptSerializer();
                return serializer.Deserialize<T>(json);
            }
            finally { }
        }

    }

}
