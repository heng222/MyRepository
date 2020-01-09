/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ĺ�˾����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2016-5-11 13:13:43 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Acl.ComponentModel.Annotions;
using Acl.Data.Annotions;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// �û�ʵ�嶨��
    /// </summary>
    [Table]
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
        [Ignore]
        //[Column(Name = "Privileges", Storage = "_privilegesInner")]
        public SystemPrivilege[] Privileges
        {
            get { return _privilegesInner.Select(p => (SystemPrivilege)p).ToArray(); }
            set { _privilegesInner = value.Select(p => (byte)p).ToArray(); }
        }
    }
}
