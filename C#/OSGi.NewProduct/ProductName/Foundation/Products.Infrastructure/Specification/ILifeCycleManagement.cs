/*----------------------------------------------------------------
// ��˾���ƣ������빫˾����
// 
// ��Ŀ���ƣ���������Ŀ����
//
// �� �� �ˣ�zhangheng
// �������ڣ�2013-7-23 15:14:23 
// ��    �䣺heng222_z@163.com
//
// Copyright (C) ��˾���ƣ���������Ȩ����
//
//----------------------------------------------------------------*/

namespace Products.Infrastructure.Specification
{
    /// <summary>
    /// �������ڹ���ӿ�
    /// </summary>
    public interface ILifeCycleManagement
    {
        /// <summary>
        /// ��
        /// </summary>
        void Open();

        /// <summary>
        /// �ر�
        /// </summary>
        void Close();
    }
}
