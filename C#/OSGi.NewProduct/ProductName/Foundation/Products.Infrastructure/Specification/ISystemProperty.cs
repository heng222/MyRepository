/*----------------------------------------------------------------
// 公司名称：请输入公司名称
// 
// 项目名称：输入项目名称
//
// 创 建 人：zhangheng
// 创建日期：2015-1-30 11:21:42 
// 邮    箱：zhangheng@163.com
//
// Copyright (C) 公司名称 2019，保留所有权利
//
//----------------------------------------------------------------*/

using System.Drawing;

namespace Products.Infrastructure.Specification
{
    /// <summary>
    /// 系统属性接口
    /// </summary>
    public interface ISystemProperty
    {
        /// <summary>
        /// 获取一个字符串，用于表示公司中文简称。
        /// </summary>
        string CompanyChsAbbrName { get; }
        /// <summary>
        /// 获取一个字符串，用于表示公司中文全称。
        /// </summary>
        string CompanyChsFullName { get; }
        /// <summary>
        /// 获取一个字符串，用于表示公司公司英文简称。
        /// </summary>
        string CompanyEnAbbrName { get; }
        /// <summary>
        /// 获取一个字符串，用于表示公司公司英文全称。
        /// </summary>
        string CompanyEnFullName { get; }

        /// <summary>
        /// 获取项目编号。
        /// </summary>
        ushort ProjectCode { get; }
        /// <summary>
        /// 获取一个字符串，用于表示项目中文名称。
        /// </summary>
        string ProjectChsName { get; }
        /// <summary>
        /// 获取一个字符串，用于表示项目英文名称。
        /// </summary>
        string ProjectEnName { get; }

        /// <summary>
        /// 获取一个字符串，用于表示产品英文名称。
        /// </summary>
        string ProductEnName { get; }
        /// <summary>
        /// 获取产品版本号的字符串表示形式。
        /// </summary>
        string ProductStringVersion { get; }
        /// <summary>
        /// 获取产品版本号的数值表示形式。
        /// </summary>
        byte[] ProductNumericVersion { get; }
        /// <summary>
        /// 获取一个字符串，用于表示产品版权。
        /// </summary>
        string Copyright { get; }

        /// <summary>
        /// 获取一个字符串，用于表示软件描述信息。
        /// </summary>
        string ApplicationDescription { get; }
        /// <summary>
        /// 获取应用程序图标
        /// </summary>
        Icon ApplicationIcon { get; }

        /// <summary>
        /// 获取公司LOGO图标
        /// </summary>
        Icon CompanyLogoIcon { get; }
        /// <summary>
        /// 获取公司LOGO图像
        /// </summary>
        Bitmap CompanyLogoImage { get; }
    }
}
