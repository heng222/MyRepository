/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ʒ���ƣ�ATS
//
// �� �� �ˣ�heng222_z
// �������ڣ�2018/5/22 14:14:21 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2018 ATS����������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Products.UAC.Domain
{
    /// <summary>
    /// ��¼��֤�ӿڡ�
    /// </summary>
    interface ILoginVerification
    {
        /// <summary>
        /// ��¼
        /// </summary>
        void LogOn(string userName, byte[] pwdMd5);
        
        /// <summary>
        /// ע��
        /// </summary>
        void Logoff(string userName);
    }
}
