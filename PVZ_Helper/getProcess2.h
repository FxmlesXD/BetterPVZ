#pragma region ����
#pragma once
#include <windows.h>
#include <tlhelp32.h>    //���̿��պ���ͷ�ļ�
#include <stdio.h>
#include <string>
#include <vector>

using namespace::std;

typedef struct EnumHWndsArg {
	std::vector<HWND> *vecHWnds;
	DWORD dwProcessId;
}EnumHWndsArg, *LPEnumHWndsArg;

// �жϴ����Ƿ�����Ŀ�����
BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam) {
	EnumHWndsArg *pArg = (LPEnumHWndsArg)lParam;
	DWORD  processId;

	// ���������̱߳�ʶ��
	GetWindowThreadProcessId(
		hwnd,			// ���ھ��
		&processId		// ���� PID ��ָ��
	);

	// ������ HWND ������� PID ������뵽 vecHWnds ����ĩβ
	if (processId == pArg->dwProcessId) { pArg->vecHWnds->push_back(hwnd); }

	return TRUE;
}

// ���� PID ��ȡ HWND
void GetHWndsByProcessID(DWORD processID, std::vector<HWND> &vecHWnds) {
	EnumHWndsArg wi;
	wi.dwProcessId = processID;
	wi.vecHWnds = &vecHWnds;

	// ö�����ж�������
	EnumWindows(
		lpEnumFunc,		// �ص�����ָ��
		(LPARAM)&wi		// ���ݸ��ص�������ֵ
	);
}

#pragma endregion

bool getProcessA(const char *text)
{
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 process = { sizeof(PROCESSENTRY32) };

	// ��������
	while (Process32Next(hProcessSnap, &process)) {
		std::
		string processName = process.szExeFile;		// ������
		std::vector<HWND> vecHWnds;					// �����µĴ���������
		GetHWndsByProcessID(process.th32ProcessID, vecHWnds);

		// ��ȡ HWND ���ڱ��⡢��������
		TCHAR szBuf_title[MAX_PATH];
		TCHAR szBuf_class[MAX_PATH];
		for (const HWND &h : vecHWnds) {
			GetWindowText(
				h,					// ���ھ��
				szBuf_title,		// ���մ��ڱ���Ļ�����ָ��
				MAX_PATH			// �������ֽڴ�С
			);
			GetClassName(
				h,					// ���ھ��
				szBuf_class,		// ���մ��������Ļ�����ָ��
				MAX_PATH			// �������ֽڴ�С
			);

			// �ж��Ƿ��з���Ҫ��Ĵ���
 			if (strcmp(szBuf_title, text) == 0) {
				return true;
			}

			// ������	
			//cout << "szBuf_title = " << szBuf_title << endl;
			//cout << "szBuf_class = " << szBuf_class << endl;
			//cout << "--------------------------------------------" << endl;
		}

	}

	return false;
}