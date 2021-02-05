
using System.Collections.Generic;

using Products.Plugin1.Presentation;

namespace Products.Plugin1
{
    class Facade : Acl.CompositeDisposable
    {
        #region "Field"
        private DebugMemuItemProvider _topMenuProvider;
        #endregion

        #region "Property"

        /// <summary>
        /// 需要注册的对象
        /// </summary>
        public IEnumerable<object> ComponentsToRegister
        {
            get { return new List<object>() { _topMenuProvider }; }
        }
        #endregion

        #region "Constructor"
        public Facade()
        {
            _topMenuProvider = new DebugMemuItemProvider();
            this.AddDisposable(_topMenuProvider);
        }
        #endregion

        #region "Public methods"
        public void Open()
        {

        }
        #endregion

    }
}
