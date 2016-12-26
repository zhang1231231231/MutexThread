// MutexThread.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>

using namespace std;
DWORD WINAPI Thread1(LPVOID lpParmeter);
DWORD WINAPI Thread2(LPVOID lpParmeter);
static	HANDLE g_hMutex = INVALID_HANDLE_VALUE;
static int g_iCnt = 100;

int main()
{
	HANDLE hThread1 = INVALID_HANDLE_VALUE;
	HANDLE hThread2 = INVALID_HANDLE_VALUE;
	//�������Ƿ�ӵ������Ȩ��FALSEΪû������Ȩ
	//������һ��WaitForSingleObject��ʱ��Ͱ�����Ȩ����
	g_hMutex = ::CreateMutex(NULL, FALSE, L"Mutex");
	if (!g_hMutex)
	{
		cout << "Failed to CreateMutex !" << endl;
		return 0;
	}
	hThread1 = CreateThread(NULL, 0, Thread1, NULL, 0, NULL);
	hThread2 = CreateThread(NULL, 0, Thread2, NULL, 0, NULL);
	Sleep(4000);
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	system("PAUSE");
    return 0;
}

DWORD WINAPI Thread1(LPVOID lpParmeter)
{
	while (true)
	{
		//�����¼�����
		WaitForSingleObject(g_hMutex, INFINITE);
		if (g_iCnt>0)
		{
			Sleep(20);
			cout << "Thread1:" << g_iCnt-- << endl;
			ReleaseMutex(g_hMutex);
		}
		else
		{
			ReleaseMutex(g_hMutex);
			break;
		}
	}
	return 0;
}

DWORD WINAPI Thread2(LPVOID lpParmeter)
{
	while (true)
	{
		WaitForSingleObject(g_hMutex, INFINITE);
		if (g_iCnt>0)
		{
			Sleep(20);
			cout << "Thread2:" << g_iCnt-- << endl;
			ReleaseMutex(g_hMutex);
		}
		else
		{
			ReleaseMutex(g_hMutex);
			break;
		}
	}
	return 0;
}

