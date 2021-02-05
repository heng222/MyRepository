/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ�������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-2 10:43:04 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���� 2019����������Ȩ��
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
    /// ϵͳ������
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

        #region "��ֵ"
        /// <summary>
        /// ��ȡ��Ŀ��š�
        /// </summary>
        public ushort ProjectCode { get; private set; }
        #endregion

        #region "�ַ���"
        /// <summary>
        /// ��ȡһ���ַ��������ڱ�ʾ���������Ϣ��
        /// </summary>
        public string ApplicationDescription { get; private set; }

        /// <summary>
        /// ��ȡһ���ַ��������ڱ�ʾ��˾���ļ�ơ�
        /// </summary>
        public string CompanyChsAbbrName { get; private set; }
        /// <summary>
        /// ��ȡһ���ַ��������ڱ�ʾ��˾����ȫ�ơ�
        /// </summary>
        public string CompanyChsFullName { get; private set; }
        /// <summary>
        /// ��ȡһ���ַ��������ڱ�ʾ��˾��˾Ӣ�ļ�ơ�
        /// </summary>
        public string CompanyEnAbbrName { get; private set; }
        /// <summary>
        /// ��ȡһ���ַ��������ڱ�ʾ��˾��˾Ӣ��ȫ�ơ�
        /// </summary>
        public string CompanyEnFullName { get; private set; }

        /// <summary>
        /// ��ȡһ���ַ��������ڱ�ʾ��Ŀ�������ơ�
        /// </summary>
        public string ProjectChsName { get; private set; }
        /// <summary>
        /// ��ȡһ���ַ��������ڱ�ʾ��ĿӢ�����ơ�
        /// </summary>
        public string ProjectEnName { get; private set; }

        /// <summary>
        /// ��ȡһ���ַ��������ڱ�ʾ��ƷӢ�����ơ�
        /// </summary>
        public string ProductEnName { get; private set; }
        /// <summary>
        /// ��ȡһ���ַ��������ڱ�ʾ��Ʒ�汾�š�
        /// </summary>
        public string ProductStringVersion { get; private set; }
        /// <summary>
        /// ��ȡ��Ʒ�汾�ŵ���ֵ��ʾ��ʽ��
        /// </summary>
        public byte[] ProductNumericVersion { get; private set; }

        /// <summary>
        /// ��ȡһ���ַ��������ڱ�ʾ��Ʒ��Ȩ��
        /// </summary>
        public string Copyright { get; private set; }
        #endregion

        #region "ͼ��"
        /// <summary>
        /// ��ȡӦ�ó���ͼ��
        /// </summary>
        public Icon ApplicationIcon { get; private set; } = Resources.Application;

        /// <summary>
        /// ��ȡӦ�ó���ͼ��
        /// </summary>
        public Image ApplicationImage { get; private set; } = Resources.AppImage;

        /// <summary>
        /// ��ȡ��˾LOGOͼ��
        /// </summary>
        public Icon CompanyLogoIcon { get; private set; } = Resources.IconCompany;
        #endregion

        #region "ͼ��"
        /// <summary>
        /// ��ȡ����ͼ��
        /// </summary>
        public Bitmap BackgroundImage { get; private set; } = Resources.backcolor;

        /// <summary>
        /// ��ȡ��˾LOGOͼ��
        /// </summary>
        public Bitmap CompanyLogoImage { get; private set; } = Resources.ImgCompany;

        /// <summary>
        /// ��ȡ����ǰ��ͼ��
        /// </summary>
        public Bitmap SplashScreenBackgroundImage { get; private set; } = Resources.splashscreenBkg;
        #endregion


        #region "��Ƶ"
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
