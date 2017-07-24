/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ŀ���ƣ���SIL2��֤�ı�׼��ATS
//
// �� �� �ˣ�zhangheng
// �������ڣ�2015-1-30 11:21:42 
// ��    �䣺zhangheng@163.com
//
// Copyright (C) ��˾���� 2009����������Ȩ��
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace Products.Infrastructure.Specification
{
    /// <summary>
    /// ϵͳ���Խӿ�
    /// </summary>
    public interface ISystemAttribute
    {
        /// <summary>
        /// ��ȡһ���ַ��������ڱ�ʾ��˾���ļ�ơ�
        /// </summary>
        string CompanyChsAbbrName { get; }
        /// <summary>
        /// ��ȡһ���ַ��������ڱ�ʾ��˾����ȫ�ơ�
        /// </summary>
        string CompanyChsFullName { get; }
        /// <summary>
        /// ��ȡһ���ַ��������ڱ�ʾ��˾��˾Ӣ�ļ�ơ�
        /// </summary>
        string CompanyEnAbbrName { get; }
        /// <summary>
        /// ��ȡһ���ַ��������ڱ�ʾ��˾��˾Ӣ��ȫ�ơ�
        /// </summary>
        string CompanyEnFullName { get; }
        /// <summary>
        /// ��ȡһ���ַ��������ڱ�ʾ��Ŀ�������ơ�
        /// </summary>
        string ProjectChsName { get; }
        /// <summary>
        /// ��ȡһ���ַ��������ڱ�ʾ��ĿӢ�����ơ�
        /// </summary>
        string ProjectEnName { get; }
        /// <summary>
        /// ��ȡһ���ַ��������ڱ�ʾ��ƷӢ�����ơ�
        /// </summary>
        string ProductEnName { get; }
        /// <summary>
        /// ��ȡ��Ʒ�汾�ŵ��ַ�����ʾ��ʽ��
        /// </summary>
        string ProductStringVersion { get; }
        /// <summary>
        /// ��ȡ��Ʒ�汾�ŵ���ֵ��ʾ��ʽ��
        /// </summary>
        byte[] ProductNumericVersion { get; }
        /// <summary>
        /// ��ȡһ���ַ��������ڱ�ʾ��Ʒ��Ȩ��
        /// </summary>
        string Copyright { get; }
        /// <summary>
        /// ��ȡһ���ַ��������ڱ�ʾ���������Ϣ��
        /// </summary>
        string ApplicationDescription { get; }

        /// <summary>
        /// ��ȡӦ�ó���ͼ��
        /// </summary>
        Icon ApplicationIcon { get; }
        /// <summary>
        /// ��ȡ��˾LOGOͼ��
        /// </summary>
        Icon CompanyLogoIcon { get; }
    }
}
