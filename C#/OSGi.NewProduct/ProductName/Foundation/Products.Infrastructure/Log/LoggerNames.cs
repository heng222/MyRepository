/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ʒ���ƣ���Ʒ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2013-7-17 14:34:15 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2013 ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/


using Acl.Utility;

namespace Products.Infrastructure.Log
{
    /// <summary>
    /// ��־�������ƶ���
    /// </summary>
    public static class LoggerNames
    {
        /// <summary>
        /// ƽ̨
        /// </summary>
        [MemberDes("ƽ̨")]
        public const string Platform = "ƽ̨";
        /// <summary>
        /// �־û�ģ��
        /// </summary>
        [MemberDes("�־û�")]
        public const string Persistence = "�־û�";
        /// <summary>
        /// Shell
        /// </summary>
        [MemberDes("��־����")]
        public const string LogReport = "LogReport";

        /// <summary>
        /// Shell
        /// </summary>
        [MemberDes("Shell")]
        public const string Shell = "Shell";

        /// <summary>
        /// �û����ʿ���
        /// </summary>
        [MemberDes("UAC")]
        public const string UAC = "UAC";
        /// <summary>
        /// ϵͳ�¼�����
        /// </summary>
        [MemberDes("SEM")]
        public const string SEM = "SEM";
        /// <summary>
        /// Plugin1
        /// </summary>
        [MemberDes("Plugin1")]
        public const string Plugin1 = "Plugin1";
    }
}
