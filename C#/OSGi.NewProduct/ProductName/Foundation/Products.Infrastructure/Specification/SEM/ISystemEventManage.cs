/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�heng222_z
// �������ڣ�2018/6/11 15:16:54 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2018 ̩��˹�Ƽ�����������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Products.Infrastructure.Entities;
using Products.Infrastructure.Types;

namespace Products.Infrastructure.Specification
{
    /// <summary>
    /// ϵͳ�¼�����ӿڡ�
    /// </summary>
    public interface ISystemEventManage
    {
        #region "ϵͳ�¼�"
        /// <summary>
        /// ��ȡָ�����͵��¼�����
        /// </summary>
        /// <param name="eventType">�¼�����</param>
        /// <returns>�¼�����</returns>
        EventLevel GetEventLevel(EventType eventType);
        /// <summary>
        /// ��ȡһ��ֵ������ָʾָ�����͵��¼��Ƿ���Ҫȷ�ϡ�
        /// </summary>
        /// <param name="eventType">�¼����͡�</param>
        /// <returns>true ��ʾ��Ҫȷ�ϣ�false��ʾ����Ҫȷ�ϡ�</returns>
        bool GetConfirmEnabled(EventType eventType);
        /// <summary>
        /// ����ϵͳ�¼�
        /// </summary>
        void AddSysEventLog(SysEventLog log);
        /// <summary>
        /// ����ϵͳ�¼�
        /// </summary>
        void UpdateSysEventLog(SysEventLog log);
        #endregion

        #region "������¼"
        /// <summary>
        /// ��ȡָ����ŵĲ�����¼
        /// </summary>
        OperationLog GetOperationLog(uint code);
        /// <summary>
        /// ����������¼
        /// </summary>
        void AddOperationLog(OperationLog log);
        /// <summary>
        /// ���²�����¼
        /// </summary>
        void UpdateOperationLog(OperationLog log);
        #endregion
    }
}
