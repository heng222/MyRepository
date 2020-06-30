/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�heng222_z
// �������ڣ�2018/5/25 9:57:36 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Acl;

using Products.Infrastructure.Specification;

namespace Products.SystemEvents.Domain
{
    /// <summary>
    /// ��ϵͳ����ࡣ
    /// </summary>
    public class EventFacade : CompositeDisposable
    {
        #region "Field"
        private SystemEventManageImpl _sysEventMgr = new SystemEventManageImpl();
        private PersistenceProcessor _eventPeristence = new PersistenceProcessor();
        private NodeCommEventGenerator _commEventGenerator = new NodeCommEventGenerator();
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯����
        /// </summary>
        public EventFacade()
        {
            this.AddDisposable(_eventPeristence);
            this.AddDisposable(_commEventGenerator);
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// ��ȡϵͳ�¼�����ӿڡ�
        /// </summary>
        public ISystemEventManage SEM { get { return _sysEventMgr; } }
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        /// <summary>
        /// ��
        /// </summary>
        public void Open()
        {
        }
        #endregion

    }
}
