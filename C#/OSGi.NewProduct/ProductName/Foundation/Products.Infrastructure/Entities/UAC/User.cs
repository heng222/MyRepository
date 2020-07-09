/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2016-5-11 13:13:43 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
//
//----------------------------------------------------------------*/

using System.Linq;

using Acl.ComponentModel.Annotions;
using Acl.Data.Annotions;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// �û�ʵ�嶨��
    /// </summary>
    [Table(Name = "Users")]
    public class User : Entity
    {
        /// <summary>
        /// ����
        /// </summary>
        [Column]
        public string Name { get; set; }

        /// <summary>
        /// ����
        /// </summary>
        [Column]
        public byte[] Password { get; set; }

        /// <summary>
        /// Ȩ�ޡ�
        /// </summary>
        [Column(Name = "Privileges")]
        private byte[] _privilegesInner;
        /// <summary>
        /// ��ȡ�û�Ȩ�ޡ�
        /// </summary>
        //[Column(Name = "Privileges", Storage = "_privilegesInner")]
        [Ignore]
        public SystemPrivilege[] Privileges
        {
            get
            {
                if (_privileges == null) _privileges = _privilegesInner.Select(p => (SystemPrivilege)p).ToArray();
                return _privileges;
            }

            set
            {
                _privileges = value;
                _privilegesInner = value.Select(p => (byte)p).ToArray();
            }
        }
        private SystemPrivilege[] _privileges;
    }
}
