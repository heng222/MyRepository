﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Products.UAC.Domain;
using Products.UAC.Presentation;
using Products.UAC.Presentation.Forms;

namespace Products.UAC
{
    /// <summary>
    /// UAC子系统外观类。
    /// </summary>
    public class UacFacade : Acl.CompositeDisposable
    {
        private LocalLoginVerification _verification;
        private UserManagementImpl _userManagement;
        private TopMemuItemProvider _topMenuProvider;

        /// <summary>
        /// 构造函数。
        /// </summary>
        public UacFacade(UacSettings settings)
        {
            _userManagement = new UserManagementImpl();

            _verification = new LocalLoginVerification(settings, _userManagement);

            _topMenuProvider = new TopMemuItemProvider(_verification, _userManagement);
        }

        /// <summary>
        /// 需要注册的对象
        /// </summary>
        public IEnumerable<object> ComponentsToRegister
        {
            get
            {
                return new List<object>() { _verification, _topMenuProvider/*, new FormLogin(_verification)*/ };
            }
        }
    }
}
