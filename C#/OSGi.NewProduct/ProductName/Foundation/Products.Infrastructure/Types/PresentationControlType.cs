using System;
using System.Collections.Generic;
using System.Text;

using Acl.Utility;

namespace Products.Infrastructure.Types
{
    /// <summary>
    /// ��ʾ��ؼ����Ͷ���
    /// </summary>
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
        [MemberDesAttribute("����������־")]
        ApplicationLog = 1,
        /// <summary>
        /// �����ʱ�ӿؼ�
        /// </summary>
        [MemberDesAttribute("�����ʱ�ӿؼ�")]
        NixieTubeClock = 2,
        #endregion

        /// <summary>
        /// ��־����
        /// </summary>
        [MemberDesAttribute("��־����")]
        LogReport = 5,

        #region "SEM / ϵͳ�¼�����"
        /// <summary>
        /// ϵͳ�¼�
        /// </summary>
        [MemberDesAttribute("ϵͳ�¼�")]
        SystemEvent = 11,
        /// <summary>
        /// ������¼
        /// </summary>
        [MemberDesAttribute("������¼")]
        OperationLog = 12,
        #endregion

        #region  "Plugin1"
        /// <summary>
        /// ���1���ؼ�
        /// </summary>
        [MemberDesAttribute("���1���ؼ�")]
        Plugin1Main = 27,
        #endregion
    }
}
