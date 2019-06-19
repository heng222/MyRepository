using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MessagePack;
using NUnit.Framework;

namespace CSharpLearning.ThirdParty
{
    [TestFixture]
    class MessagePackTest
    {
        // 标记 MessagePackObjectAttribute
        [MessagePackObject]
        public class MyClass
        {
            // Key 是序列化索引，对于版本控制非常重要。
            [Key(0)]
            public int Age { get; set; }

            [Key(1)]
            public string FirstName { get; set; }

            [Key(2)]
            public string LastName { get; set; }

            // 公共成员中不序列化目标，标记IgnoreMemberAttribute
            [IgnoreMember]
            public string FullName { get { return FirstName + LastName; } }
        }

        [Test]
        public void MessagePackSerializer_Test1()
        {
            var mc = new MyClass
            {
                Age = 99,
                FirstName = "hoge",
                LastName = "huga",
            };

            // 序列化
            var bytes = MessagePackSerializer.Serialize(mc);
            // 反序列化
            var mc2 = MessagePackSerializer.Deserialize<MyClass>(bytes);

            // 你可以将msgpack二进制转储为可读的json。
            // 在默认情况下，MeesagePack for C＃减少了属性名称信息。
            // [99,"hoge","huga"]
            var json = MessagePackSerializer.ToJson(bytes);
            Console.WriteLine(json);
        }




        [MessagePackObject]
        public class Sample1
        {
            [Key(0)]
            public int Foo { get; set; }
            [Key(1)]
            public int Bar { get; set; }
        }

        [MessagePackObject]
        public class Sample2
        {
            [Key("foo")]
            public int Foo { get; set; }
            [Key("bar")]
            public int Bar { get; set; }
        }

        [MessagePackObject(keyAsPropertyName: true)]
        public class Sample3
        {
            // 不需要key特性
            public int Foo { get; set; }

            // 不需要序列化的成员使用IgnoreMember特性
            [IgnoreMember]
            public int Bar { get; set; }
        }
        public void MessagePackSerializer_Test3()
        {
            // 结果 [10,20]
            Console.WriteLine(MessagePackSerializer.ToJson(new Sample1 { Foo = 10, Bar = 20 }));

            // 结果 {"foo":10,"bar":20}
            Console.WriteLine(MessagePackSerializer.ToJson(new Sample2 { Foo = 10, Bar = 20 }));

            // 结果 {"Foo":10}
            Console.WriteLine(MessagePackSerializer.ToJson(new Sample3 { Foo = 10, Bar = 20 }));
        }

        [Test]
        public void LZ4MessagePackSerializer_Test1()
        {
            var array = Enumerable.Range(1, 100).Select(x => new MyClass { Age = 5, FirstName = "foo", LastName = "bar" }).ToArray();

            // call LZ4MessagePackSerializer instead of MessagePackSerializer, api is completely same
            var lz4Bytes = LZ4MessagePackSerializer.Serialize(array);
            var mc2 = LZ4MessagePackSerializer.Deserialize<MyClass[]>(lz4Bytes);

            // you can dump lz4 message pack
            // [[5,"hoge","huga"],[5,"hoge","huga"],....]
            var json = LZ4MessagePackSerializer.ToJson(lz4Bytes);
            Console.WriteLine(json);

            // lz4Bytes is valid MessagePack, it is using ext-format( [TypeCode:99, SourceLength|CompressedBinary] )
            // [99,"0gAAA+vf3ABkkwWjZm9vo2JhcgoA////yVBvo2Jhcg=="]
            var rawJson = MessagePackSerializer.ToJson(lz4Bytes);
            Console.WriteLine(rawJson);
        }

    }
}
