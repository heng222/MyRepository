/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ŀ���ƣ���SIL2��֤�ı�׼��ATS
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-2-2 10:43:04 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;
using Products.Resource;
using System.Drawing;
using Products.Infrastructure.Specification;

namespace Products.Ats.Domain
{
    /// <summary>
    /// ϵͳ������
    /// </summary>
    public sealed class SystemAttributeImpl : ISystemAttribute
    {
        #region "Filed"
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

        #region ISystemAttribute ��Ա
        /// <inherit/>
        public string CompanyChsAbbrName
        {
            get { return ATSResources.CompanyChsAbbrName; }
        }

        /// <inherit/>
        public string CompanyChsFullName
        {
            get { return ATSResources.CompanyChsFullName; }
        }

        /// <inherit/>
        public string CompanyEnAbbrName
        {
            get { return ATSResources.CompanyEnAbbrName; }
        }

        /// <inherit/>
        public string CompanyEnFullName
        {
            get { return ATSResources.CompanyEnFullName; }
        }

        /// <inherit/>
        public string ProjectChsName
        {
            get { return ATSResources.ProjectChsName; }
        }

        /// <inherit/>
        public string ProjectEnName
        {
            get { return ATSResources.ProjectEnName; }
        }

        /// <inherit/>
        public string ProductEnName
        {
            get { return ATSResources.ProductEnName; }
        }

        /// <inherit/>
        public string ProductStringVersion
        {
            get { return ATSResources.ProductStringVersion; }
        }

        /// <inherit/>
        public byte[] ProductNumericVersion
        {
            get { return ATSResources.ProductNumericVersion; }
        }

        /// <inherit/>
        public string Copyright
        {
            get { return ATSResources.Copyright; }
        }

        /// <inherit/>
        public string ApplicationDescription
        {
            get { return ATSResources.ApplicationDescription; }
        }

        /// <summary>
        /// ��ȡӦ�ó���ͼ��
        /// </summary>
        public Icon ApplicationIcon
        {
            get { return ATSResources.ApplicationIcon; }
        }
        /// <summary>
        /// ��ȡ��˾LOGOͼ��
        /// </summary>
        public Icon CompanyLogoIcon
        {
            get { return ATSResources.CompanyLogoIcon; }
        }
        #endregion
    }
}
