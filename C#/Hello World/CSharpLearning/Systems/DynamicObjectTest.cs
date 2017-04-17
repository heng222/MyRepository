using System;
using System.Collections.Generic;
using System.Dynamic;
using NUnit.Framework;
using System.Xml.Linq;
using System.Linq;

namespace CSharpLearning
{
    public sealed class MyExtendsObject : DynamicObject
    {
        private readonly Dictionary<string, object> _properties;

        public MyExtendsObject(Dictionary<string, object> properties)
        {
            _properties = properties;
        }

        public override IEnumerable<string> GetDynamicMemberNames()
        {
            return _properties.Keys;
        }

        public override bool TryGetMember(GetMemberBinder binder, out object result)
        {
            if (_properties.ContainsKey(binder.Name))
            {
                result = _properties[binder.Name];
                return true;
            }
            else
            {
                result = null;
                return false;
            }
        }

        public override bool TrySetMember(SetMemberBinder binder, object value)
        {
            if (_properties.ContainsKey(binder.Name))
            {
                _properties[binder.Name] = value;
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    public sealed class MyExtensXMLObj : DynamicObject
    {
        private readonly XElement node;

        public MyExtensXMLObj(XElement node)
        {
            this.node = node;
        }

        public override bool TrySetMember(SetMemberBinder binder, object value)
        {
            var elements = node.Elements().ToList();
            var currentElement = elements.FirstOrDefault(x => x.Name == binder.Name);
            if (currentElement != null)
            {
                currentElement.Value = value as string;
                return true;
            }
            else
            {
                return false;
            }
        }

        public override bool TryGetMember(GetMemberBinder binder, out object result)
        {
            var elements = node.Elements().ToList();
            var currentElement = elements.FirstOrDefault(x => x.Name == binder.Name);
            if (currentElement != null)
            {
                result = currentElement.Value;
                return true;
            }
            else
            {
                result = null;
                return false;
            }
        }
    }

    /// <summary>
    /// 背景: 在Coding中有时候会遇到一些需要解析的数据,可是数据的字段数量和名称未统一，我们没法定义实体类来对应。
    /// 那么我们就会想到通过C#的dynamic动态类来实现，如果大家注意的话一些ORM框架里面貌似都有用到dynamic来实现一部分功能。
    /// </summary>
    [TestFixture(Description = "动态对象学习")]
    class DynamicObjectTest
    {
        [Test]
        public void Test1()
        {
            dynamic myObj = new ExpandoObject();
            myObj.Name = "Frank";
            myObj.Age = 22;
            Console.WriteLine(myObj.Name + myObj.Age.ToString());
        }


        [Test]
        public void Test2()
        {
            var dic = new Dictionary<string, object>()
            {
                {"Name","Frank"},
                {"Age",23}
            };

            dynamic myObj = new MyExtendsObject(dic);
            Console.WriteLine(myObj.Age); //23
        }

        [Test]
        public void Test3()
        {
            var xmlText = "<?xml version=\"1.0\" encoding=\"utf-8\" ?><Person><Name>Frank</Name><Age>23</Age><Address>TianFu SoftWarePark</Address></Person>";

            XElement root = XElement.Parse(xmlText);
            dynamic personList = new MyExtensXMLObj(root);
            Console.WriteLine(personList.Name); // Frank
        }
    }
}
