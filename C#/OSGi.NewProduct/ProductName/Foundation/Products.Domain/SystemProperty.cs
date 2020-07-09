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

using System.Drawing;

using Products.Infrastructure.Specification;
using Products.Resource;

namespace Products.Domain
{
    /// <summary>
    /// ϵͳ������
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

        #region ISystemAttribute ��Ա
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
        /// ��ȡӦ�ó���ͼ��
        /// </summary>
        public Icon ApplicationIcon
        {
            get { return ProductResources.ApplicationIcon; }
        }
        /// <summary>
        /// ��ȡ��˾LOGOͼ��
        /// </summary>
        public Icon CompanyLogoIcon
        {
            get { return ProductResources.CompanyLogoIcon; }
        }
        #endregion
    }
}
