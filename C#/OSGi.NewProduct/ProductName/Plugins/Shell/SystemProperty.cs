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
using System;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;

using Acl.IO;

using Products.Infrastructure.Specification;
using Products.Shell.Properties;

namespace Products.Shell
{
    /// <summary>
    /// 系统属性类
    /// </summary>
    class SystemProperty : ISystemProperty
    {
        public static readonly SystemProperty Instance = new SystemProperty();

        #region "Constructor"
        private SystemProperty()
        {
            ReadIniFiles();
        }
        #endregion

        #region "数值"
        /// <summary>
        /// 获取项目编号。
        /// </summary>
        public ushort ProjectCode { get; private set; }
        #endregion

        #region "字符串"
        /// <summary>
        /// 获取一个字符串，用于表示软件描述信息。
        /// </summary>
        public string ApplicationDescription { get; private set; }

        /// <summary>
        /// 获取一个字符串，用于表示公司中文简称。
        /// </summary>
        public string CompanyChsAbbrName { get; private set; }
        /// <summary>
        /// 获取一个字符串，用于表示公司中文全称。
        /// </summary>
        public string CompanyChsFullName { get; private set; }
        /// <summary>
        /// 获取一个字符串，用于表示公司公司英文简称。
        /// </summary>
        public string CompanyEnAbbrName { get; private set; }
        /// <summary>
        /// 获取一个字符串，用于表示公司公司英文全称。
        /// </summary>
        public string CompanyEnFullName { get; private set; }

        /// <summary>
        /// 获取一个字符串，用于表示项目中文名称。
        /// </summary>
        public string ProjectChsName { get; private set; }
        /// <summary>
        /// 获取一个字符串，用于表示项目英文名称。
        /// </summary>
        public string ProjectEnName { get; private set; }

        /// <summary>
        /// 获取一个字符串，用于表示产品英文名称。
        /// </summary>
        public string ProductEnName { get; private set; }
        /// <summary>
        /// 获取一个字符串，用于表示产品版本号。
        /// </summary>
        public string ProductStringVersion { get; private set; }
        /// <summary>
        /// 获取产品版本号的数值表示形式。
        /// </summary>
        public byte[] ProductNumericVersion { get; private set; }

        /// <summary>
        /// 获取一个字符串，用于表示产品版权。
        /// </summary>
        public string Copyright { get; private set; }
        #endregion

        #region "图标"
        /// <summary>
        /// 获取应用程序图标
        /// </summary>
        public Icon ApplicationIcon { get; private set; } = Resources.Application;

        /// <summary>
        /// 获取应用程序图像
        /// </summary>
        public Image ApplicationImage { get; private set; } = Resources.AppImage;

        /// <summary>
        /// 获取公司LOGO图标
        /// </summary>
        public Icon CompanyLogoIcon { get; private set; } = Resources.IconCompany;
        #endregion

        #region "图像"
        /// <summary>
        /// 获取背景图像
        /// </summary>
        public Bitmap BackgroundImage { get; private set; } = Resources.backcolor;

        /// <summary>
        /// 获取公司LOGO图像
        /// </summary>
        public Bitmap CompanyLogoImage { get; private set; } = Resources.ImgCompany;

        /// <summary>
        /// 获取闪屏前景图像
        /// </summary>
        public Bitmap SplashScreenBackgroundImage { get; private set; } = Resources.splashscreenBkg;
        #endregion


        #region "音频"
        #endregion

        #region "private methods"
        private void ReadIniFiles()
        {
            var fileName = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + @"\Resources.ini";
            var iniFile = new WinIniFile(fileName, System.Text.Encoding.UTF8);

            var section = "String";

            // ProjectCode
            var value = iniFile.ReadValue(section, "ProjectCode");
            ProjectCode = Convert.ToUInt16(value, 16);

            // 
            ApplicationDescription = iniFile.ReadValue(section, "AppDescription", Resources.AppDescription);
            CompanyChsAbbrName = iniFile.ReadValue(section, "CompanyChsAbbrName", Resources.CompanyChsAbbrName);
            CompanyChsFullName = iniFile.ReadValue(section, "CompanyChsFullName", Resources.CompanyChsFullName);
            Copyright = iniFile.ReadValue(section, "CopyRight", Resources.CopyRight);
            ProductNumericVersion = iniFile.ReadValue(section, "ProductNumericVersion", Resources.ProductNumericVersion).Split('.').Select(p => byte.Parse(p)).ToArray();
            ProductStringVersion = iniFile.ReadValue(section, "ProductStringVersion", Resources.ProductStringVersion);
            ProductEnName = iniFile.ReadValue(section, "ProductEnName", Resources.ProductEnName);
            ProjectEnName = iniFile.ReadValue(section, "ProjectEnName", Resources.ProjectEnName);
            ProjectChsName = iniFile.ReadValue(section, "ProjectChsName", Resources.ProjectChsName);
            CompanyEnFullName = iniFile.ReadValue(section, "CompanyEnFullName", Resources.CompanyEnFullName);
            CompanyEnAbbrName = iniFile.ReadValue(section, "CompanyEnAbbrName", Resources.CompanyEnAbbrName);
        }

        #endregion
    }
}
