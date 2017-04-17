using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using ProWrite.Core;

namespace ProWrite.Core
{
    public static class EventHelper
    {
        static Dictionary<Type, EventInfo[]> _events;
        static readonly BindingFlags _flags = BindingFlags.Public 
                                     | BindingFlags.NonPublic 
                                     | BindingFlags.Static
                                     | BindingFlags.Instance;
        static EventHelper()
        {
            _events = new Dictionary<Type, EventInfo[]>();
            RegisterEvent(Assembly.GetExecutingAssembly());
        }

        private static void RegisterEvent(Assembly asm)
        {
            Type[] types = asm.GetTypes();
            foreach (Type type in types)
            {
                RegisterEvent(type);
            }
        }

        private static void RegisterEvent(Type type)
        {
            if (_events.ContainsKey(type))
                return;

            EventInfo[] es = type.GetEvents(_flags);
            if (es != null && es.Length > 0)
                _events[type] = es;
        }

        public static void ClearEvent(object o)
        {
            Check.Require(o, "o", Check.NotNull);
            Type type = o.GetType();

            EventInfo[] es = null;

            if (_events.ContainsKey(type))
                es = _events[type];
            else
                es = type.GetEvents(_flags);

            if (es == null || es.Length < 1)
                return;

            foreach (EventInfo ei in es)
            {
                FieldInfo f = ei.DeclaringType.GetField(ei.Name, _flags);
                if (f != null)
                {
                    try
                    {
                        f.SetValue(o, null);
                    }
                    finally
                    {
                    }
                }
            }

        }
    }
}
