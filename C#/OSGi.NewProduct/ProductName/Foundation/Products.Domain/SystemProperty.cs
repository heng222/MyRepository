/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-2-2 10:43:04 
// 邮    箱：heng222_z@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System.Drawing;

using Products.Infrastructure.Specification;
using Products.Resource;

namespace Products.Domain
{
    /// <summary>
    /// 系统属性类
    /// </summary>
    public sealed class SystemProperty : ISystemProperty
    {
        #region "Field"
        #endregion

        #region "Constructor"
        #endregion

        #region "Properties"
        #endregion

        #region "Override methods"
        #endregion

        #region "Private methods"
        #endregion

        #region "Public methods"
        #endregion

        #region ISystemAttribute 成员
        /// <inherit/>
        public string CompanyChsAbbrName
        {
            get { return ProductResources.CompanyChsAbbrName; }
        }

        /// <inherit/>
        public string CompanyChsFullName
        {
            get { return ProductResources.CompanyChsFullName; }
        }

        /// <inherit/>
        public string CompanyEnAbbrName
        {
            get { return ProductResources.CompanyEnAbbrName; }
        }

        /// <inherit/>
        public string CompanyEnFullName
        {
            get { return ProductResources.CompanyEnFullName; }
        }

        /// <inherit/>
        public string ProjectChsName
        {
            get { return ProductResources.ProjectChsName; }
        }

        /// <inherit/>
        public string ProjectEnName
        {
            get { return ProductResources.ProjectEnName; }
        }

        /// <inherit/>
        public string ProductEnName
        {
            get { return ProductResources.ProductEnName; }
        }

        /// <inherit/>
        public string ProductStringVersion
        {
            get { return ProductResources.ProductStringVersion; }
        }

        /// <inherit/>
        public byte[] ProductNumericVersion
        {
            get { return ProductResources.ProductNumericVersion; }
        }

        /// <inherit/>
        public string Copyright
        {
            get { return ProductResources.Copyright; }
        }

        /// <inherit/>
        public string ApplicationDescription
        {
            get { return ProductResources.ApplicationDescription; }
        }

        /// <summary>
        /// 获取应用程序图标
        /// </summary>
        public Icon ApplicationIcon
        {
            get { return ProductResources.ApplicationIcon; }
        }
        /// <summary>
        /// 获取公司LOGO图标
        /// </summary>
        public Icon CompanyLogoIcon
        {
            get { return ProductResources.CompanyLogoIcon; }
        }
        #endregion
    }
}
