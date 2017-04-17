/*----------------------------------------------------------------
// 公司名称：北京交大微联科技有限公司
// 
// 项目名称：北京地铁15号线ATS项目
//
// 创 建 人：张 恒
// 创建日期：06/10/2011 09:03:23 
// 邮    箱：zhh_217@bjmut.com
//
// Copyright (C) 北京交大微联科技有限公司 2009-2015 保留所有权利
//
//----------------------------------------------------------------*/

using System;
using System.Text;
using System.Globalization;
using System.Resources;
using System.Reflection;
using System.Collections.Generic;

namespace CommResources
{
    /// <summary>
    /// 通用资源服务类。
    /// 用户自定义的资源文件必须符合以下规则：[ModuleName].Resources.[code].resx，code = en-US,zh-CN等。
    /// </summary>
    public class CommonResourceService
    {
        #region "Field"
        /// <summary>
        /// 通用资源管理器。用于管理当前程序集中的资源。
        /// </summary>
        private ResourceManager _resCommonMgr = null;

        /// <summary>
        /// 特定资源管理器。用于管理客户指定的程序集中的资源。
        /// </summary>
        private ResourceManager _resCustomMgr = null;

        /// <summary>
        /// 区域性信息。
        /// </summary>
        private CultureInfo _culture = CultureInfo.CurrentUICulture;

        /// <summary>
        /// 包括特定资源的程序集
        /// </summary>
        private Assembly _customAssembly = null;
        #endregion

        #region "Constructors"
        /// <summary>
        /// 默认构造函数
        /// </summary>
        public CommonResourceService()
        {
            BuildCommonResourceManager();
        }
        /// <summary>
        /// 带参数的构造函数
        /// </summary>
        /// <param name="assembly">包含用户自定义资源的程序集</param>
        public CommonResourceService(Assembly assembly)
        {
            _customAssembly = assembly;
            BuildCommonResourceManager();
            BuildCustomResourceManager();
        }
        /// <summary>
        /// 带参数的构造函数
        /// </summary>
        /// <param name="culture">区域性信息</param>
        /// <param name="assembly">包含用户自定义资源的程序集</param>
        public CommonResourceService(CultureInfo culture, Assembly assembly)
        {
            _culture = culture;
            _customAssembly = assembly;
            BuildCommonResourceManager();
            BuildCustomResourceManager();
        }
        #endregion


        #region "Properites"
        /// <summary>
        /// 获取/设置当前使用的区域性信息
        /// </summary>
        public CultureInfo Culture
        {
            get { return _culture; }

            set 
            {
                if (value != null)
                {
                    _culture = value;
                    BuildCommonResourceManager();
                    BuildCustomResourceManager();
                }
            }
        }
        /// <summary>
        /// 获取公司名称
        /// </summary>
        public string CompanyName
        {
            get { return GetCommonString("CompanyName"); }
        }
        #endregion


        #region "Private methods"
        /// <summary>
        /// 构建通用资源管理器
        /// </summary>
        private void BuildCommonResourceManager()
        {
            Assembly commAssembley = Assembly.GetExecutingAssembly();
            string[] temp = commAssembley.FullName.Split(new char[] { ',' });
            string rcName = String.Format("{0}.Resources.{1}", temp[0], _culture.Name);
            _resCommonMgr = new ResourceManager(rcName, Assembly.GetExecutingAssembly());
        }

        /// <summary>
        /// 构建用户自定义的资源管理器
        /// </summary>
        private void BuildCustomResourceManager()
        {
            string[] temp = _customAssembly.FullName.Split(new char[] { ',' });
            string rcName = String.Format("{0}.Resources.{1}", temp[0], _culture.Name);
            _resCustomMgr = new ResourceManager(rcName, _customAssembly);
        }
        #endregion


        #region "Public methods"

        //public void Initialize()
        //{

        //}



        ///// <summary>
        ///// 初始化资源管理器
        ///// </summary>
        ///// <param name="culture">区域性信息</param>
        ///// <param name="assembly">自定义资源所在的程序集</param>
        //public void Initialize(CultureInfo culture, Assembly assembly)
        //{
        //    _culture = culture;
        //    _customAssembly = assembly;

        //    BuildCommonResourceManager();

        //    BuildCustomResourceManager();

        //    //_resourceMgr = ResourceManager.CreateFileBasedResourceManager(resPath,
        //    //    Application.StartupPath, null);
        //}


        /// <summary>
        /// 获取通用资源文件中定义的字符串的值
        /// </summary>
        /// <param name="name">要获取的资源名</param>
        /// <returns>通用资源库中的值。</returns>
        public string GetCommonString(string name)
        {
            try
            {
                return _resCommonMgr.GetString(name);
            }
            catch (System.Exception /*ex*/)
            {
                return name;
            }
        }

        /// <summary>
        /// 获取客户自定义的字符串的值
        /// </summary>
        /// <param name="name">要获取的资源名</param>
        /// <returns>自定义资源库中的值。</returns>
        public string GetCustomString(string name)
        {
            try
            {
                return _resCustomMgr.GetString(name);   
            }
            catch (System.Exception /*ex*/)
            {
                return name;
            }
        }


        #endregion
    }
}
