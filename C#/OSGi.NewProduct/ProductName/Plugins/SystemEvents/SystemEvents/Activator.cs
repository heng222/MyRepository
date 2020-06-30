/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-3 21:20:58 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
//
//----------------------------------------------------------------*/
using System.Collections.Generic;
using System.Threading.Tasks;

using Acl.ServiceManagement;

using Platform.Presentation;

using Products.Domain;
using Products.Infrastructure.Log;
using Products.Infrastructure.Types;
using Products.Presentation;
using Products.SystemEvents.Controls;
using Products.SystemEvents.Domain;
using Products.SystemEvents.Properties;

namespace Products.SystemEvents
{
    /// <summary>
    /// ��ϵͳ������
    /// </summary>
    class Activator : FrameworkActivatorBase
    {
        #region "Field"
        private EventFacade _facade;
        #endregion

        #region "Constructor"
        /// <summary>
        /// ���캯��
        /// </summary>
        public Activator()
            : base(LoggerNames.SEM)
        {
        }
        #endregion

        #region "Override methods"

        public override PluginType Type
        {
            get { return PluginType.SEM; }
        }

        protected override void OnBundleStart(IDictionary<string, string> context)
        {
            _facade = new EventFacade();

            // ע�� ISystemEventManage �ӿ�
            ServiceManager.Current.RegisterInstance(_facade.SEM);

            // ������ʾ��
            Workbench.SendMessage(() =>
            {
                // ������ʾ��
                MainWorkSpace.AddPart(new CtrlSysEvents(), Resources.SystemEvent);
                MainWorkSpace.AddPart(new CtrlOperationRecord(), Resources.OperationLog);

                //// �������ҳ�档
                //var optionControl = new Plugin1ConfigPage();
                //Workbench.AddOption(optionControl);
            });
        }

        protected override void OnBundleStop(IDictionary<string, string> context)
        {
            if (_facade != null)
            {
                _facade.Dispose();
                _facade = null;
            }
        }

        protected override void OnFrameworkStarted()
        {
            try
            {
                Task.Factory.StartNew(() =>
                {
                    try
                    {
                        _facade.Open();
                    }
                    catch (System.Exception ex)
                    {
                        this.Log.Error(ex);
                    }
                });
            }
            catch (System.Exception ex)
            {
                base.Log.Error(ex);
            }
        }
        #endregion

    }
}
