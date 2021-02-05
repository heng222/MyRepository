/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：heng222_z
// 创建日期：2018/5/28 15:46:41 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称，保留所有权利。
//
//----------------------------------------------------------------*/

using Acl;

using Products.Infrastructure.Events;
using Products.Infrastructure.Messages;
using Products.SystemEvents.Utilities;

namespace Products.SystemEvents.Domain
{
    /// <summary>
    /// “系统事件+操作记录” 持久化处理器。
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
        /// 当新的系统事件产生时。
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
        /// 当新的操作日志产生时。
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
