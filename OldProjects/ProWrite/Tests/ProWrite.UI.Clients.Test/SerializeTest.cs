using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ProWrite.Core;
using System.Diagnostics;
using ProWrite.Entity.Library;
using System.IO;

namespace ProWrite.UI.Clients.Test
{
    public class SerializeTest
    {
        [Serializable]
        public class User
        {
            public string Name;
            private User() { }
            internal User(string name)
            {
                Name = name;
            }


        }

        public class address
        {
        }

        public static void Test()
        {
            User source = new User("ZhangSan");
            User dest = CloneManager.Clone<User>(source);
            Debug.Assert(source.Name == dest.Name);
        }

      
    }
}
