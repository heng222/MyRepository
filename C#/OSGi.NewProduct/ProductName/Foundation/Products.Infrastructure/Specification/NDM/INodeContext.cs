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
using System.Collections.Generic;
using System.Text;

using Products.Infrastructure.Types;

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
