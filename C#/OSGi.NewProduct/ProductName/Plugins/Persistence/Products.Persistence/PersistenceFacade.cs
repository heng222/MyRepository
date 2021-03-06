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
using Acl.ServiceManagement;

using Products.Persistence.Services;

namespace Products.Persistence
{
    /// <summary>
    /// Persistence module facade.
    /// </summary>
    public class PersistenceFacade : Acl.CompositeDisposable
    {
        #region "Field"
        private DbConfigurationProvider _dbCfgProvider = new DbConfigurationProvider();
        private RepositoryManager _persistenceMgr = new RepositoryManager();
        private CommStreamStorage _commLogStorage = new CommStreamStorage();
        #endregion

        #region "Constructor"
        /// <summary>
        /// Constructor.
        /// </summary>
        public PersistenceFacade()
        {
            this.AddDisposable(_persistenceMgr);
            this.AddDisposable(_commLogStorage);

            ServiceManager.Current.RegisterInstance(_dbCfgProvider);
        }
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        /// <summary>
        /// Open facade.
        /// </summary>
        public void Open()
        {
            _persistenceMgr.Open();
        }

        /// <summary>
        /// Close facade.
        /// </summary>
        public void Close()
        {
            this.Dispose();

            // 
            _persistenceMgr.Close();
        }
        #endregion
    }
}
