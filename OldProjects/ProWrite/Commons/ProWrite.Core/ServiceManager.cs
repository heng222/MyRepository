using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel.Design;

namespace ProWrite.Core
{
    public static class ServiceManager
    {
        private static ServiceContainer sc = new ServiceContainer();

        public static void Add(Type serviceType, object serviceInstance)
        {
            sc.AddService(serviceType, serviceInstance);
        }

        public static void Add(Type serviceType, ServiceCreatorCallback callback)
        {
            sc.AddService(serviceType, callback);
        }

        public static void Add(Type serviceType, object serviceInstance, bool promote)
        {
            sc.AddService(serviceType, serviceInstance, promote);
        }

        public static void Add(Type serviceType, ServiceCreatorCallback callback, bool promote)
        {
            sc.AddService(serviceType, callback, promote);
        }

        public static void Add<T>(object serviceInstance)
        {
            sc.AddService(typeof(T), serviceInstance);
        }
        public static void Add<T>(ServiceCreatorCallback callback)
        {
            sc.AddService(typeof(T), callback);
        }

        public static object Get(Type serviceType)
        {
            return sc.GetService(serviceType);
        }

        public static T Get<T>()
        {
            return (T)sc.GetService(typeof(T));
        }

        public static void Remove(Type serviceType)
        {
            sc.RemoveService(serviceType);
        }

        public static void Remove(Type serviceType, bool promote)
        {
            sc.RemoveService(serviceType, promote);
        }

        public static void Remove<T>()
        {
            sc.RemoveService(typeof(T));
        }

        public static void Remove<T>(bool promote)
        {
            sc.RemoveService(typeof(T), promote);
        }

        public static void RemoveAll()
        {
            sc.Dispose();
            sc = new ServiceContainer();
        }
    }
}
