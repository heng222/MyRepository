/*----------------------------------------------------------------
// ��˾���ƣ���������΢���Ƽ����޹�˾
// 
// ��Ŀ���ƣ���������15����ATS��Ŀ
//
// �� �� �ˣ��� ��
// �������ڣ�06/10/2011 09:03:23 
// ��    �䣺zhh_217@bjmut.com
//
// Copyright (C) ��������΢���Ƽ����޹�˾ 2009-2015 ��������Ȩ��
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
    /// ͨ����Դ�����ࡣ
    /// �û��Զ������Դ�ļ�����������¹���[ModuleName].Resources.[code].resx��code = en-US,zh-CN�ȡ�
    /// </summary>
    public class CommonResourceService
    {
        #region "Field"
        /// <summary>
        /// ͨ����Դ�����������ڹ���ǰ�����е���Դ��
        /// </summary>
        private ResourceManager _resCommonMgr = null;

        /// <summary>
        /// �ض���Դ�����������ڹ���ͻ�ָ���ĳ����е���Դ��
        /// </summary>
        private ResourceManager _resCustomMgr = null;

        /// <summary>
        /// ��������Ϣ��
        /// </summary>
        private CultureInfo _culture = CultureInfo.CurrentUICulture;

        /// <summary>
        /// �����ض���Դ�ĳ���
        /// </summary>
        private Assembly _customAssembly = null;
        #endregion

        #region "Constructors"
        /// <summary>
        /// Ĭ�Ϲ��캯��
        /// </summary>
        public CommonResourceService()
        {
            BuildCommonResourceManager();
        }
        /// <summary>
        /// �������Ĺ��캯��
        /// </summary>
        /// <param name="assembly">�����û��Զ�����Դ�ĳ���</param>
        public CommonResourceService(Assembly assembly)
        {
            _customAssembly = assembly;
            BuildCommonResourceManager();
            BuildCustomResourceManager();
        }
        /// <summary>
        /// �������Ĺ��캯��
        /// </summary>
        /// <param name="culture">��������Ϣ</param>
        /// <param name="assembly">�����û��Զ�����Դ�ĳ���</param>
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
        /// ��ȡ/���õ�ǰʹ�õ���������Ϣ
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
        /// ��ȡ��˾����
        /// </summary>
        public string CompanyName
        {
            get { return GetCommonString("CompanyName"); }
        }
        #endregion


        #region "Private methods"
        /// <summary>
        /// ����ͨ����Դ������
        /// </summary>
        private void BuildCommonResourceManager()
        {
            Assembly commAssembley = Assembly.GetExecutingAssembly();
            string[] temp = commAssembley.FullName.Split(new char[] { ',' });
            string rcName = String.Format("{0}.Resources.{1}", temp[0], _culture.Name);
            _resCommonMgr = new ResourceManager(rcName, Assembly.GetExecutingAssembly());
        }

        /// <summary>
        /// �����û��Զ������Դ������
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
        ///// ��ʼ����Դ������
        ///// </summary>
        ///// <param name="culture">��������Ϣ</param>
        ///// <param name="assembly">�Զ�����Դ���ڵĳ���</param>
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
        /// ��ȡͨ����Դ�ļ��ж�����ַ�����ֵ
        /// </summary>
        /// <param name="name">Ҫ��ȡ����Դ��</param>
        /// <returns>ͨ����Դ���е�ֵ��</returns>
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
        /// ��ȡ�ͻ��Զ�����ַ�����ֵ
        /// </summary>
        /// <param name="name">Ҫ��ȡ����Դ��</param>
        /// <returns>�Զ�����Դ���е�ֵ��</returns>
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
