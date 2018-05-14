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

namespace Products.Infrastructure.Log
{
    /// <summary>
    /// ͨѶ��־�����������붨��
    /// ����λ�ֽڣ���Ŀ��ţ���׼�汾Ϊ0xFFFF��������Ŀʹ��0x0001~0xEFFF֮���һ��ֵ��
    /// ����λ�ֽڣ�˳��š�
    /// </summary>
    public enum CommLogParserCode : uint
    {
        /// <summary>
        /// ��Чֵ��
        /// </summary>
        None = 0,

        /// <summary>
        /// ��ϵͳ�ڲ���־����������š�
        /// </summary>
        Internal = 0xFFFF0001,

        #region "ϵͳ1"
        /// <summary>
        /// ��ϵͳ �� System1 �����������������š�
        /// </summary>
        System1Input = 0xFFFF0004,
        /// <summary>
        /// ��ϵͳ�� System1 ����������������š�
        /// </summary>
        System1Output = 0xFFFF0005,
        #endregion


        #region "ϵͳ2"
        /// <summary>
        /// ��ϵͳ�� System2 �����������������š�
        /// </summary>
        System2Input = 0xFFFF0010,
        #endregion

    }
}
