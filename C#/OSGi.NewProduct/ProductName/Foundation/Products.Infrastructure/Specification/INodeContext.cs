/*----------------------------------------------------------------
// ��˾���ƣ���˾����
// 
// ��Ŀ���ƣ���SIL2��֤�ı�׼��ATS
//
// �� �� �ˣ�zhangheng
// �������ڣ�2018-8-1 13:17:50 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

using Products.Infrastructure.Types;
using System;
using System.Collections.Generic;
using System.Text;

namespace Products.Infrastructure.Specification
{
    /// <summary>
    /// һ���ӿڣ����������ڵ���������Ϣ��
    /// </summary>
    public interface INodeContext
    {
        #region "Properties"

        /// <summary>
        /// ��ȡ��ǰ�ڵ���
        /// </summary>
        UInt32 Code { get; }
        /// <summary>
        /// ��ȡ��ǰ�ڵ�����
        /// </summary>
        string Name { get; }
        /// <summary>
        /// ��ȡ��ǰ�ڵ�����
        /// </summary>
        NodeType Type { get; }
        
        /// <summary>
        /// ��ȡ��ǰ�ڵ���Ҫ���صĲ����
        /// </summary>
        PluginType Plugins { get; }

        /// <summary>
        /// ��ȡ��ǰ�ڵ���Ҫ���صĿؼ����͡�
        /// </summary>
        IEnumerable<PresentationControlType> ControlTypes { get; }

        #endregion


        #region "Operations"
        /// <summary>
        /// ��ǰ�ڵ��Ƿ����ָ���Ĳ����
        /// </summary>
        /// <param name="pluginType">ָ���Ĳ�����͡�</param>
        /// <returns>true��ʾ��Ҫ����ָ���Ĳ����false��ʾ����Ҫ���ء�</returns>
        bool ContainsPlugin(PluginType pluginType);
        #endregion

    }
}
