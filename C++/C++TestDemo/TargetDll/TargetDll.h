// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� TARGETDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// TARGETDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

#include "Exercises.h"

//// �����Ǵ� TargetDll.dll ������
//class TARGETDLL_API CTargetDll {
//public:
//	CTargetDll(void);
//	// TODO: �ڴ�������ķ�����
//};


extern TARGETDLL_API int nTargetDll;

TARGETDLL_API int fnTargetDll(void);