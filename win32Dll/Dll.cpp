#include<stdio.h>
#include "Dll.h"
BOOL APIENTRY DllMain(HMODULE hModule,			// ģ��ľ��
	DWORD  ul_reason_for_call,	// ����ʼ�͹رգ��߳̿�ʼ�ͽ���
	LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: // ���и��� ֻ����һ��
	case DLL_THREAD_ATTACH: //�̸߳���
	case DLL_THREAD_DETACH: // �̷߳���
	case DLL_PROCESS_DETACH: //���̷��� ֻ����һ��
		break;
	}
	return true;
}
//����������ʽ ��������/ģ�鶨���ļ�����
//��������
extern "C" _declspec(dllexport) void funTest1()
{
	printf("��������������funTest1����\n");
}
//ģ�鶨�嵼��
void funTest2()
{
	printf("ģ�鶨�嵼������");
}