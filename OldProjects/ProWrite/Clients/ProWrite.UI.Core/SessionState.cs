using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.UI.Controls
{
    [Serializable]
    public class SessionState:Dictionary<string,object>
    {
        private SessionState()
        {
        }

        public static SessionState Instance = new SessionState();

        public T Get<T>(string key)
        {
            object o = null;
            TryGetValue(key, out o);
            return (T)o;
        }
    }
}
