using System;
using System.Collections.Generic;
using System.Text;

namespace Products.Infrastructure.Protocol.Framework
{

    /// <summary>
    /// һ���ӿڣ����ڱ�ʾ����������Ϣ��
    /// </summary>
    public interface IStreamFrame
    {
        /// <summary>
        /// ��ȡ��Ϣ��Ӧ����������
        /// </summary>
        /// <returns>Э���Ӧ��������</returns>
        Array GetStream();

        /// <summary>
        /// ����ָ������������
        /// </summary>
        /// <param name="stream">������</param>
        /// <param name="startIndex">Э���������������е���ʼ��ַ</param>
        void ParseStream(Array stream, int startIndex);
    }

    /// <summary>
    /// һ���ӿڣ����ڱ�ʾ����������Ϣ��
    /// </summary>
    public interface IStreamFrame<T> : IStreamFrame
    {
        /// <summary>
        /// ��ȡ��Ϣ��Ӧ����������
        /// </summary>
        /// <returns>Э���Ӧ��������</returns>
        new T[] GetStream();

        /// <summary>
        /// ����ָ������������
        /// </summary>
        /// <param name="stream">������</param>
        /// <param name="startIndex">Э���������������е���ʼ��ַ</param>
        void ParseStream(T[] stream, int startIndex);
    }
}
