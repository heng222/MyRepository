/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ʒ���ƣ���Ʒ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2018-7-17 14:34:15 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) 2018 ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;

using Products.Resource;

namespace Products.Infrastructure.Log
{
    /// <summary>
    /// ͨѶ��־�����������붨��
    /// </summary>
    public abstract class CommLogParserCode
    {
        /// <summary>
        /// ��Чֵ��
        /// </summary>
        public static readonly uint None = 0;

        /// <summary>
        /// ��ϵͳ�ڲ���־����������š�
        /// </summary>
        public static readonly UInt32 Internal = (uint)((ProductResources.ProjectCode << 16) + 0x0001);


        #region "ϵͳ1"
        /// <summary>
        /// ��ϵͳ �� System1 �����������������š�
        /// </summary>
        public static readonly UInt32 System1Input = (uint)((ProductResources.ProjectCode << 16) + 0x0004);
        /// <summary>
        /// ��ϵͳ�� System1 ����������������š�
        /// </summary>
        public static readonly UInt32 System1Output = (uint)((ProductResources.ProjectCode << 16) + 0x0005);
        #endregion
    }
}
