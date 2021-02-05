/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�heng222_z
// �������ڣ�2018/5/28 15:46:41 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

using Acl;

using Products.Infrastructure.Events;
using Products.Infrastructure.Messages;
using Products.SystemEvents.Utilities;

namespace Products.SystemEvents.Domain
{
    /// <summary>
    /// ��ϵͳ�¼�+������¼�� �־û���������
    /// </summary>
    class PersistenceProcessor : CompositeDisposable
    {
        #region "Field"
        #endregion

        #region "Constructor"
        public PersistenceProcessor()
        {
            this.AddDisposable(GlobalMessageBus.SubscribeNewSystemEventGenerated(OnNewSystemEventGenerated));
            this.AddDisposable(GlobalMessageBus.SubscribeOperationLogChanged(OnNewOperLogGenerated));
        }
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"

        /// <summary>
        /// ���µ�ϵͳ�¼�����ʱ��
        /// </summary>
        private void OnNewSystemEventGenerated(object sender, NewSystemEventArgs args)
        {
            try
            {
                if (args.Value.Code == 0)
                {
                    GlobalServices.SEM.AddSysEventLog(args.Value);
                }
                else
                {
                    GlobalServices.SEM.UpdateSysEventLog(args.Value);
                }
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }

        /// <summary>
        /// ���µĲ�����־����ʱ��
        /// </summary>
        private void OnNewOperLogGenerated(object sender, OpeationLogCreateOrUpdateEventArgs args)
        {
            try
            {
                if (args.Value.Code == 0)
                {
                    GlobalServices.SEM.AddOperationLog(args.Value);
                }
                else
                {
                    GlobalServices.SEM.UpdateOperationLog(args.Value);
                }
            }
            catch (System.Exception ex)
            {
                LogUtility.Error(ex);
            }
        }
        #endregion

        #region "Public methods"
        #endregion

    }
}
