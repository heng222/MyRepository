using System;
using System.Collections.Generic;
using System.Text;

using Acl.Utility;

namespace Products.Infrastructure
{
    /// <summary>
    /// ��ʾ��ؼ����Ͷ���
    /// </summary>
    public enum PresentationControlType
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

        #region "SEM"
        /// <summary>
        /// ϵͳ�¼�
        /// </summary>
        [MemberDesAttribute("ϵͳ�¼�")]
        SystemEvent = 11,
        #endregion

        #region  "Plugin1"
        /// <summary>
        /// Plugin1Control1
        /// </summary>
        [MemberDesAttribute("Plugin1Control1")]
        Plugin1Control1 = 27,
        /// <summary>
        /// Plugin1Control2
        /// </summary>
        [MemberDesAttribute("Plugin1Control2")]
        Plugin1Control2 = 28,
        #endregion
    }
}
