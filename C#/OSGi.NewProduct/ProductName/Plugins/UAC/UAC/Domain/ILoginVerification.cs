/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
//
//----------------------------------------------------------------*/

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
        void Logoff();
    }
}
