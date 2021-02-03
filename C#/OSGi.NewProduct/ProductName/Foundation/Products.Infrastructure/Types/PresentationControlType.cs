
using System;

using Acl.Utility;

namespace Products.Infrastructure.Types
{
    /// <summary>
    /// ��ʾ��ؼ����Ͷ���
    /// </summary>
    [Obsolete]
    public enum PresentationControlType : uint
    {
        /// <summary>
        /// �����ͻ�������Ч
        /// </summary>
        None = 0,

        #region  "Shell"
        /// <summary>
        /// ����������־
        /// </summary>
        [MemberDes("����������־")]
        ApplicationLog = 1,
        /// <summary>
        /// �����ʱ�ӿؼ�
        /// </summary>
        [MemberDes("�����ʱ�ӿؼ�")]
        NixieTubeClock = 2,
        #endregion

        /// <summary>
        /// ��־����
        /// </summary>
        [MemberDes("��־����")]
        LogReport = 5,

        #region "SEM / ϵͳ�¼�����"
        /// <summary>
        /// ϵͳ�¼�
        /// </summary>
        [MemberDes("ϵͳ�¼�")]
        SystemEvent = 11,
        /// <summary>
        /// ������¼
        /// </summary>
        [MemberDes("������¼")]
        OperationLog = 12,
        #endregion

        #region  "Plugin1"
        /// <summary>
        /// ���1���ؼ�
        /// </summary>
        [MemberDes("���1���ؼ�")]
        Plugin1Main = 27,
        #endregion
    }
}
