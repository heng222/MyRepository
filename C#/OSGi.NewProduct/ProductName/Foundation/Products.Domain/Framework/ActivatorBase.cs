using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using Acl;
using Acl.Log;
using Acl.ServiceManagement;
using Products.Infrastructure.Specification;
using Products.Infrastructure.Types;

namespace Products.Domain
{
    /// <summary>
    /// Bundle激活器基类
    /// </summary>
    public abstract class ActivatorBase : CompositeDisposable
    {
        #region "Filed"
        private string _logName = "";
        private List<ILifeCycleManagement> _lifeCycleManagements;
        #endregion

        #region "Constructor"
        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="logName">日志名称</param>
        protected ActivatorBase(string logName)
        {
            _logName = logName;
        }
        #endregion

        #region "Properties"
        /// <summary>
        /// 获取日志接口
        /// </summary>
        protected ILog Log { get; private set; }
        #endregion

        #region "virtual/abstract methods"
        /// <summary>
        /// 插件类型
        /// </summary>
        public abstract PluginType Type { get; }

        /// <summary>
        /// 模板方法，当启动时调用。
        /// </summary>
        /// <param name="settings"></param>
        protected abstract void OnBundleStart(IDictionary<string, string> settings);

        /// <summary>
        /// 当关闭时调用。
        /// </summary>
        /// <param name="settings"></param>
        protected virtual void OnBundleStop(IDictionary<string, string> settings) { }
        #endregion


        #region "Public methods"
        /// <summary>
        /// 
        /// </summary>
        /// <param name="settings"></param>
        public void Start(IDictionary<string, string> settings)
        {
            try
            {
                _lifeCycleManagements = new List<ILifeCycleManagement>();

                // 获取日志记录器
                this.Log = LogManager.GetLogger(_logName);

                // 记录日志。
                var bundleName = settings["Bundle-Name"];
                this.Log.InfoFormat("{0}子系统正在启动...", bundleName);

                // 调用模板方法
                this.OnBundleStart(settings);

                // 
                this.Log.InfoFormat("{0}子系统启动完毕。", bundleName);
            }
            catch (System.Exception ex)
            {
                HandleStartingException(ex);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="settings"></param>
        public void Stop(IDictionary<string, string> settings)
        {
            try
            {
                var bundleName = settings["Bundle-Name"];

                this.Log.InfoFormat("{0}子系统正在结束...", bundleName);

                this.OnBundleStop(settings);

                if (_lifeCycleManagements != null)
                {
                    foreach (var item in _lifeCycleManagements)
                    {
                        try
                        {
                            item.Close();
                        }
                        catch { }
                    }

                    _lifeCycleManagements.Clear();
                    _lifeCycleManagements = null;
                }

                this.Dispose();

                this.Log.InfoFormat("{0}子系统已结束。", bundleName);
            }
            catch (System.Exception ex)
            {
                this.Log.Error(ex);
            }
        }

        /// <summary>
        /// Bundle规约验证
        /// </summary>
        public bool Match(IDictionary<string, string> context)
        {
            if (this.Type == PluginType.None) return false;

            return NodeContextManager.Current.ContainsPlugin(Type);
        }
        #endregion


        #region "Protected methods"

        /// <summary>
        /// 注册服务
        /// </summary>
        /// <typeparam name="TContract"></typeparam>
        /// <typeparam name="TComponent"></typeparam>
        /// <param name="isSingleton"></param>
        /// <param name="id"></param>
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1004:GenericMethodsShouldProvideTypeParameter")]
        protected void RegisterService<TContract, TComponent>(bool? isSingleton = false, string id = null)
        {
            ServiceManager.Current.Register<TContract, TComponent>(isSingleton, id);
        }
        /// <summary>
        /// 注册服务
        /// </summary>
        /// <typeparam name="TComponent"></typeparam>
        /// <param name="contractType"></param>
        /// <param name="isSingleton"></param>
        /// <param name="id"></param>
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1004:GenericMethodsShouldProvideTypeParameter")]
        protected void RegisterService<TComponent>(Type contractType = null, bool? isSingleton = false, string id = null)
        {
            ServiceManager.Current.Register<TComponent>(contractType, isSingleton, id);
        }
        /// <summary>
        /// 注册服务
        /// </summary>
        /// <param name="componentType"></param>
        /// <param name="contractType"></param>
        /// <param name="isSingleton"></param>
        /// <param name="id"></param>
        protected void RegisterService(Type componentType, Type contractType = null, bool? isSingleton = false, string id = null)
        {
            ServiceManager.Current.Register(componentType, contractType, isSingleton, id);
        }
        /// <summary>
        /// 注册服务
        /// </summary>
        /// <param name="instance"></param>
        /// <param name="serviceType"></param>
        /// <param name="id"></param>
        protected void RegisterInstance(object instance, Type serviceType = null, string id = null)
        {
            ServiceManager.Current.RegisterInstance(instance, serviceType, id);
        }
        /// <summary>
        /// 获取服务
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns></returns>
        protected T GetService<T>()
        {
            return ServiceManager.Current.Get<T>();
        }
        /// <summary>
        /// 获取服务
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        protected object GetService(string id)
        {
            return ServiceManager.Current.Get(id);
        }
        /// <summary>
        /// 获取服务
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="id"></param>
        /// <returns></returns>
        protected T GetService<T>(string id)
        {
            return ServiceManager.Current.Get<T>(id);
        }
        /// <summary>
        /// 获取服务
        /// </summary>
        /// <param name="type"></param>
        /// <returns></returns>
        protected object GetService(Type type)
        {
            return ServiceManager.Current.Get(type);
        }

        /// <summary>
        /// 注册生命周期管理组件
        /// </summary>
        /// <param name="item"></param>
        protected void RegisterLifeCycleManagement(ILifeCycleManagement item)
        {
            Guard.NotNull(item, "item");
            _lifeCycleManagements.Add(item);
        }

        /// <summary>
        /// 注册可释放组件
        /// </summary>
        /// <param name="item"></param>
        protected void RegisterDisposible(IDisposable item)
        {
            Guard.NotNull(item, "item");
            this.AddDisposable(item);
        }
        #endregion


        #region "Private methods"
       
        /// <summary>
        /// 处理启动过程中发生的异常。
        /// </summary>
        private void HandleStartingException(Exception ex)
        {
            // 写日志
            if (this.Log != null) { this.Log.Error(ex); }

            var strText = "程序启动时发生严重错误，是否立即停止？" + "\r\n信息：" + ex.Message;
            var strCaption = "启动错误";
            var btns = MessageBoxButtons.YesNo;
            var icons = MessageBoxIcon.Error;
            var rc = DialogResult.Cancel;

            var ownerForm = Application.OpenForms.Cast<Form>().FirstOrDefault();

            if (ownerForm == null)
            {
                rc = MessageBox.Show(ownerForm, strText, strCaption, btns, icons);
            }
            else
            {
                ownerForm.Invoke(new Action(() => rc = MessageBox.Show(ownerForm, strText, strCaption, btns, icons)));
            }

            if (rc == DialogResult.Yes) throw ex;
        }
        #endregion      
    }
}
