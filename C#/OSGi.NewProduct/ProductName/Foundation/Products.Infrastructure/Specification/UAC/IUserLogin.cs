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

namespace Products.Infrastructure
{
    /// <summary>
    /// �û���¼���
    /// </summary>
    public enum UserLogOnResult
    {
        /// <summary>
        /// ȡ��
        /// </summary>
        Canceled,

        /// <summary>
        /// ��֤�ɹ�
        /// </summary>
        Successful,

        /// <summary>
        /// ��֤ʧ��
        /// </summary>
        Failure,
    }

    /// <summary>
    /// �û���¼�ӿ�
    /// </summary>
    public interface IUserLogOn
    {
        /// <summary>
        /// ��ʾ��¼�Ի���
        /// </summary>
        /// <returns>�û���¼���</returns>
        UserLogOnResult ShowLogOnDialog();
    }
}
