using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web.Script.Serialization;
using log4net;

namespace ProWrite.UFE
{
    public class JsonSerializer : JavaScriptSerializer
    {
        static readonly ILog log = LogManager.GetLogger(typeof(JsonSerializer));

        public new T Deserialize<T>(string input)
        {
            try
            {
                return base.Deserialize<T>(input);
            }
            catch (ArgumentException ex)
            {
                log.Error("Json:" + input + "\t" + ex.Message, ex);
                return default(T);
            }
            catch (InvalidOperationException ex)
            {
                log.Error("Json:" + input + "\t" + ex.Message, ex);
                return default(T);
            }
            catch (Exception ex)
            {
                log.Error("Json:" + input + "\t" + ex.Message, ex);
                return default(T);
            }
        }

        public new T ConvertToType<T>(object obj)
        {
            try
            {
                return base.ConvertToType<T>(obj);
            }
            catch (ArgumentException ex)
            {
                log.Error(ex.Message, ex);
                return default(T);
            }
            catch (InvalidOperationException ex)
            {
                log.Error(ex.Message, ex);
                return default(T);
            }
            catch (Exception ex)
            {
                log.Error(ex.Message, ex);
                return default(T);
            }
        }
    }

    
}
