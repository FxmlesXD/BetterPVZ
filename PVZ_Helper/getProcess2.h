#pragma region 依赖
#pragma once
#include <windows.h>
#include <tlhelp32.h>    //进程快照函数头文件
#include <stdio.h>
#include <string>
#include <vector>

using namespace::std;

typedef struct EnumHWndsArg {
	std::vector<HWND> *vecHWnds;
	DWORD dwProcessId;
}EnumHWndsArg, *LPEnumHWndsArg;

// 判断窗口是否属于目标进程
BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam) {
	EnumHWndsArg *pArg = (LPEnumHWndsArg)lParam;
	DWORD  processId;

	// 检索窗口线程标识符
	GetWindowThreadProcessId(
		hwnd,			// 窗口句柄
		&processId		// 接收 PID 的指针
	);

	// 如果这个 HWND 属于这个 PID ，则加入到 vecHWnds 数组末尾
	if (processId == pArg->dwProcessId) { pArg->vecHWnds->push_back(hwnd); }

	return TRUE;
}

// 根据 PID 获取 HWND
void GetHWndsByProcessID(DWORD processID, std::vector<HWND> &vecHWnds) {
	EnumHWndsArg wi;
	wi.dwProcessId = processID;
	wi.vecHWnds = &vecHWnds;

	// 枚举所有顶级窗口
	EnumWindows(
		lpEnumFunc,		// 回调函数指针
		(LPARAM)&wi		// 传递给回调函数的值
	);
}

#pragma endregion

bool getProcessA(const char *text)
{
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 process = { sizeof(PROCESSENTRY32) };

	// 遍历进程
	while (Process32Next(hProcessSnap, &process)) {
		std::
		string processName = process.szExeFile;		// 进程名
		std::vector<HWND> vecHWnds;					// 进程下的窗体句柄数组
		GetHWndsByProcessID(process.th32ProcessID, vecHWnds);

		// 获取 HWND 窗口标题、窗口类名
		TCHAR szBuf_title[MAX_PATH];
		TCHAR szBuf_class[MAX_PATH];
		for (const HWND &h : vecHWnds) {
			GetWindowText(
				h,					// 窗口句柄
				szBuf_title,		// 接收窗口标题的缓冲区指针
				MAX_PATH			// 缓冲区字节大小
			);
			GetClassName(
				h,					// 窗口句柄
				szBuf_class,		// 接收窗口类名的缓冲区指针
				MAX_PATH			// 缓冲区字节大小
			);

			// 判断是否有符合要求的窗体
 			if (strcmp(szBuf_title, text) == 0) {
				return true;
			}

			// 输出结果	
			//cout << "szBuf_title = " << szBuf_title << endl;
			//cout << "szBuf_class = " << szBuf_class << endl;
			//cout << "--------------------------------------------" << endl;
		}

	}

	return false;
}