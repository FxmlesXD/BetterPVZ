#pragma once
#include <windows.h>
#include <tlhelp32.h>    //���̿��պ���ͷ�ļ�
#include <stdio.h>

bool getProcess(const char *procressName)                //�˺��������������ִ�Сд
{
	char pName[MAX_PATH];                                //��PROCESSENTRY32�ṹ���е�szExeFile�ַ����鱣��һ�£����ڱȽ�
	strcpy(pName, procressName);                            //��������
	CharLowerBuff(pName, MAX_PATH);                        //������ת��ΪСд
	PROCESSENTRY32 currentProcess;                        //��ſ��ս�����Ϣ��һ���ṹ��
	currentProcess.dwSize = sizeof(currentProcess);        //��ʹ������ṹ֮ǰ�����������Ĵ�С
	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//��ϵͳ�ڵ����н�����һ������

	if (hProcess == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot()����ʧ��!\n");
		return false;
	}

	bool bMore = Process32First(hProcess, &currentProcess);        //��ȡ��һ��������Ϣ
	while (bMore)
	{
		CharLowerBuff(currentProcess.szExeFile, MAX_PATH);        //��������ת��ΪСд
		if (strcmp(currentProcess.szExeFile, pName) == 0)            //�Ƚ��Ƿ���ڴ˽���
		{
			CloseHandle(hProcess);                                //���hProcess���
			return true;
		}
		bMore = Process32Next(hProcess, &currentProcess);            //������һ��
	}

	CloseHandle(hProcess);    //���hProcess���
	return false;
}