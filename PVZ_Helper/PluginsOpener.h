#pragma once

void pluginsopener(string pluginname)
{
	string path;
	TCHAR szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0; // 删除文件名，只获得路径字串
	for (int i = 0; i < sizeof(szFilePath); i++)
	{
		if (szFilePath[i] == '\\')
		{
			szFilePath[i] = '/';
		}
	}
	path = szFilePath + path;
	path = path + "plugins" + "/";
	path = path + pluginname;
	path = "\"" + path;
	path = path + "\"";
	WinExec(path.c_str(), SW_NORMAL );
}