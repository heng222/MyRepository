using System;
using OSGi;

namespace Products.Domain
{
    /// <summary>
    /// Class FrameworkActivatorBase.
    /// </summary>
    public abstract class FrameworkActivatorBase : ActivatorBase, IBundleActivator, IFrameworkListener
    {
        #region "Constructor"
        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="logName">日志名称</param>
        protected FrameworkActivatorBase(string logName)
            : base(logName)
        {
        }
        #endregion

        #region "Abstract/Virtual methods"
        /// <summary>
        /// 当框架启动完毕时调用。
        /// </summary>
        protected abstract void OnFrameworkStarted();
        #endregion


        #region IBundleActivator
        void IBundleActivator.Start(IBundleContext context)
        {
            // 注册Framework监听器
            context.AddFrameworkListener(this);

            base.Start(context.Bundle.Headers);
        }

        void IBundleActivator.Stop(IBundleContext context)
        {
            // 注销Framework监听器
            //context.RemoveFrameworkListener(this);

            base.Stop(context.Bundle.Headers);
        }
        #endregion


        #region IFrameworkListener 成员
        void IFrameworkListener.FrameworkEvent(FrameworkEvent e)
        {
            try
            {
                if (e.Type == FrameworkEventType.Started)
                {
                    try
                    {
                        OnFrameworkStarted();
                    }
                    catch (Exception ex)
                    {
                        base.Log.Error(ex.Message, ex);
                    }
                }
            }
            catch (System.Exception ex)
            {
                base.Log.Error(ex);
            }
        }
        #endregion
    }
}
