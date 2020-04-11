/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2014-6-10 14:57:11 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

using System;
using System.Collections.Generic;
using System.Text;

namespace Products.Infrastructure.Protocol.Framework
{
    /// <summary>
    /// һ���ӿڣ�������������������
    /// </summary>
    public interface IStreamFrameParser
    {
        /// <summary>
        /// ��ָ����������ΪЭ��֡����
        /// </summary>
        /// <param name="stream">��Ҫ����������</param>
        /// <param name="startIndex">����ʱ��ʼ��ַ</param>
        /// <returns>һ��<seealso cref="ProtocolFrame"/>����</returns>
        ProtocolFrame Parse(Array stream, int startIndex);
    }

    /// <summary>
    /// һ���ӿڣ�������������������
    /// </summary>
    public interface IStreamFrameParser<T> : IStreamFrameParser
    {
        /// <summary>
        /// ��ָ����������ΪЭ��֡����
        /// </summary>
        /// <param name="stream">��Ҫ����������</param>
        /// <param name="startIndex">����ʱ��ʼ��ַ</param>
        /// <returns>һ��<seealso cref="ProtocolFrame"/>����</returns>
        ProtocolFrame Parse(T[] stream, int startIndex);
    }
}
