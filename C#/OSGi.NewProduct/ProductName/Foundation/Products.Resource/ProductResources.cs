using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Products.Resource
{
    /// <summary>
    /// 产品资源定义
    /// </summary>
    public static class ProductResources
    {
        #region "字符串"
        /// <summary>
        /// 获取一个字符串，用于表示公司中文简称。
        /// </summary>
        public static string CompanyChsAbbrName
        {
            get { return Products.Resource.Properties.Resources.CompanyChsAbbrName; }
        }
        /// <summary>
        /// 获取一个字符串，用于表示公司中文全称。
        /// </summary>
        public static string CompanyChsFullName
        {
            get { return Products.Resource.Properties.Resources.CompanyChsFullName; }
        }
        /// <summary>
        /// 获取一个字符串，用于表示公司公司英文简称。
        /// </summary>
        public static string CompanyEnAbbrName
        {
            get { return Products.Resource.Properties.Resources.CompanyEnAbbrName; }
        }
        /// <summary>
        /// 获取一个字符串，用于表示公司公司英文全称。
        /// </summary>
        public static string CompanyEnFullName
        {
            get { return Products.Resource.Properties.Resources.CompanyEnFullName; }
        }
        /// <summary>
        /// 获取一个字符串，用于表示项目中文名称。
        /// </summary>
        public static string ProjectChsName
        {
            get { return Products.Resource.Properties.Resources.ProjectChsName; }
        }
        /// <summary>
        /// 获取一个字符串，用于表示项目英文名称。
        /// </summary>
        public static string ProjectEnName
        {
            get { return Products.Resource.Properties.Resources.ProjectEnName; }
        }
        /// <summary>
        /// 获取一个字符串，用于表示产品英文名称。
        /// </summary>
        public static string ProductEnName
        {
            get { return Products.Resource.Properties.Resources.ProductEnName; }
        }
        /// <summary>
        /// 获取一个字符串，用于表示产品版本号。
        /// </summary>
        public static string ProductStringVersion
        {
            get { return Products.Resource.Properties.Resources.ProductStringVersion; }
        }

        /// <summary>
        /// 版本号
        /// </summary>
        private static byte[] _appVersion = null;
        /// <summary>
        /// 获取产品版本号的数值表示形式。
        /// </summary>
        public static byte[] ProductNumericVersion
        {
            get
            {
                if (_appVersion == null)
                {
                    var version = Products.Resource.Properties.Resources.ProductNumericVersion;
                    var value = version.Split('.');

                    var result = new List<byte>();
                    value.ToList().ForEach(p =>
                    {
                        result.Add(byte.Parse(p));
                    });

                    _appVersion = result.ToArray();
                }

                return _appVersion;
            }
        }
        /// <summary>
        /// 获取一个字符串，用于表示产品版权。
        /// </summary>
        public static string Copyright
        {
            get { return Products.Resource.Properties.Resources.CopyRight; }
        }
        /// <summary>
        /// 获取一个字符串，用于表示软件描述信息。
        /// </summary>
        public static string ApplicationDescription
        {
            get { return Products.Resource.Properties.Resources.AppDescription; }
        }
        #endregion

        #region "图标"
        /// <summary>
        /// 获取应用程序图标
        /// </summary>
        public static Icon ApplicationIcon
        {
            get { return Products.Resource.Properties.Resources.AppIcon; }
        }
        /// <summary>
        /// 获取公司LOGO图标
        /// </summary>
        public static Icon CompanyLogoIcon
        {
            get { return Products.Resource.Properties.Resources.CompanyIcon; }
        }
        #endregion

        #region "图像"
        /// <summary>
        /// 获取背景图像
        /// </summary>
        public static Bitmap BackgroundImage
        {
            get { return Products.Resource.Properties.Resources.background; }
        }
        /// <summary>
        /// 获取公司LOGO图像
        /// </summary>
        public static Bitmap CompanyLogoImage
        {
            get { return Products.Resource.Properties.Resources.companyLogo; }
        }
        /// <summary>
        /// 获取闪屏前景图像
        /// </summary>
        public static Bitmap SplashScreenBackgroundImage
        {
            get { return Products.Resource.Properties.Resources.splashscreenBkg; }
        }
        #endregion


        #region "音频"
        #endregion

        #region "其它"
        #endregion
    }
}
