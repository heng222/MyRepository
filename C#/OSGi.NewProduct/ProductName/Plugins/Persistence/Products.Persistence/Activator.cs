﻿/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-3 21:20:58 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;

using Acl.CommStreamLog;

using Products.Domain;
using Products.Infrastructure.Log;

namespace Products.Persistence
{
    /// <summary>
    /// 子系统激活器
    /// </summary>
    class Activator : FrameworkActivatorBase
    {
        #region "Field"
        private PersistenceFacade _facade = null;
        #endregion

        #region "constructor"
        public Activator()
            : base(LoggerNames.Persistence)
        {
        }

        #endregion

        #region "override methods"
        public override string PluginID 
        { 
            get { return "B23F0B28-50D2-45D0-A722-5DD885AE14A4"; } 
        }

        public override bool Match(IDictionary<String, String> context)
        {
            return true;
        }

        protected override void OnBundleStart(IDictionary<string, string> context)
        {
            _facade = new PersistenceFacade();
            _facade.Open();

            CommStreamLogManager.DeleteExpiredLog();
        }

        protected override void OnBundleStop(IDictionary<string, string> context)
        {
            if (_facade != null)
            {
                _facade.Close();
            }
        }

        protected override void OnFrameworkStarted()
        {
        }
        #endregion

        #region "private methods"
        #endregion

        #region "public methods"
        #endregion

    }
}
