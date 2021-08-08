#include "stdafx.h"
#include "PVZ_Helper.h"
#include "PVZ_1_0.h"
#include "stdio.h"
#include "commctrl.h"
#include "DllFromMem.h"
#include "getProcess.h"
#include "getProcess2.h"
#include "PluginsOpener.h"
#include <memory>
#include <direct.h>
#include <stdlib.h>
#include <shellapi.h>

#define WM_INIT WM_USER + 1

#define MAX_LOADSTRING 100

// 全锟街憋拷锟斤拷:
HINSTANCE hInst;					 // 锟斤拷前实锟斤拷
TCHAR szTitle[MAX_LOADSTRING];		 // 锟斤拷锟斤拷锟斤拷锟侥憋拷
TCHAR szWindowClass[MAX_LOADSTRING]; // 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷

string baohu;
std::shared_ptr<PVZ> pvz;
std::shared_ptr<PVZ> shabiboxuejia;

#define INIT_LIST(hwnd,IDC,_List) \
for (int i = 0; i < sizeof(_List) / sizeof(*_List); ++i)\
{\
	SendDlgItemMessage(hwnd, IDC, CB_ADDSTRING, 0, LPARAM(_List[i])); \
}\
	SendDlgItemMessage(hwnd, IDC, CB_SETCURSEL, 0, 0)

const char* pList[] = { "豌豆射手", "向日葵", "樱桃炸弹", "坚果墙", "土豆雷",
"寒冰射手", "大嘴花", "双发射手", "小喷菇", "阳光菇", "大喷菇", "墓碑吞噬者",
"魅惑菇", "胆小菇", "寒冰菇", "毁灭菇", "睡莲", "窝瓜", "三线射手", "缠绕海藻",
"火爆辣椒", "地刺", "火炬树桩", "高坚果", "海蘑菇", "路灯花", "仙人掌",
"三叶草", "裂荚射手", "杨桃", "南瓜头", "磁力菇", "卷心菜投手", "花盆",
"玉米投手", "咖啡豆", "大蒜", "叶子保护伞", "金盏花", "西瓜投手", "机枪射手",
"双子向日葵", "忧郁菇", "香蒲", "冰瓜", "吸金磁", "地刺王", "玉米加农炮",
"左向双发射手", "爆炸坚果", "巨大坚果" };

const char *cardList[] = { "豌豆射手", "向日葵", "樱桃炸弹", "坚果墙", "土豆雷",
"寒冰射手", "大嘴花", "双发射手", "小喷菇", "阳光菇", "大喷菇", "墓碑吞噬者",
"魅惑菇", "胆小菇", "寒冰菇", "毁灭菇", "睡莲", "窝瓜", "三线射手", "缠绕海藻",
"火爆辣椒", "地刺", "火炬树桩", "高坚果", "海蘑菇", "路灯花", "仙人掌",
"三叶草", "裂荚射手", "杨桃", "南瓜头", "磁力菇", "卷心菜投手", "花盆",
"玉米投手", "咖啡豆", "大蒜", "叶子保护伞", "金盏花", "西瓜投手", "机枪射手",
"双子向日葵", "忧郁菇", "香蒲", "冰瓜", "吸金磁", "地刺王", "玉米加农炮",
"左向双发射手", "爆炸坚果", "巨大坚果","花苗","反向双发","__________","刷新",
"弹坑","阳光","钻石","潜水僵尸","奖杯","普通僵尸","路障僵尸","撑杆跳僵尸","铁桶僵尸",
"扶梯僵尸","矿工僵尸","蹦极僵尸","橄榄球僵尸","气球僵尸","铁门僵尸",
"冰车僵尸","跳跳僵尸","舞王僵尸","白眼","小鬼" };

const char* zList[] = { "普通", "旗帜", "路障", "撑杆", "铁桶", "读报",
"铁栅门", "橄榄球", "舞王", "伴舞", "鸭子", "潜水", "冰车", "雪橇", "海豚",
"小丑", "气球", "矿工", "跳跳", "雪人", "蹦极", "扶梯", "篮球", "白眼", "小鬼",
"僵博", "豌豆", "坚果", "辣椒", "机枪", "窝瓜", "高坚果", "红眼" };

const char* bList[] = { "草地", "裸地", "水池" };

const char* LSList[] = { "暂停","选卡","正常","食脑" };

const char* NowMList[] = { "铲子","锤子","瞄准","浇水","肥料","杀虫剂","音乐盒","巧克力","手套","卖掉","运送车","树肥","正常" };

const char* nList[] = { "1", "2", "3", "4", "5", "6" };

const char* SceneList[] = { "白天草坪", "夜晚草坪", "白天泳池", "夜晚泳池", "白天屋顶", "夜晚屋顶","蘑菇园","花园","水族馆","智慧树" };

const char* rList[] = { "不出怪", "陆路", "水路" };

const char* mList[] = { "冒险模式", "白天简单", "夜晚简单", "泳池简单",
"浓雾简单", "屋顶简单", "白天困难", "夜晚困难", "泳池困难", "浓雾困难",
"屋顶困难", "白天无尽", "夜晚无尽", "泳池无尽", "浓雾无尽", "屋顶无尽",
"植物僵尸", "坚果保龄球", "老虎机", "雨中种植物", "宝石迷阵", "隐形食脑者",
"看星星", "僵尸水族馆", "宝石转转看", "小僵尸大麻烦", "保护传送门", "柱子一样",
"雪橇区", "僵尸快跑", "锤僵尸", "谁笑到最后", "植物僵尸2", "坚果保龄球2",
"跳跳舞会", "僵王复仇", "坚果艺术", "晴天", "无草皮之地", "重要时间",
"种太阳花", "空袭", "冰冻关卡", "超乎寻常压力", "坟墓模式", "把它挖出来",
"暴风雨之夜", "蹦极闪电战", "松鼠", "花瓶无尽", "我是僵尸无尽" };

const char* FireDouList[] = { "豌豆","寒冰","卷心菜","西瓜","孢子","冰瓜","隐形火豆","星星","刺","篮球","玉米","大炮","黄油","敌方豌豆" };

const char* FireIceDouList[] = { "豌豆","寒冰","卷心菜","西瓜","孢子","冰瓜","隐形火豆","星星","刺","篮球","玉米","大炮","黄油","敌方豌豆" };

const char* ShopPrice[] = { "机枪/双子/第8卡槽", "曾哥/地刺王", "香蒲/冰瓜/智慧树/水壶", "屋顶推车/蜗牛/吸金磁", "春哥", "茄子/蘑菇花园/水族馆", "花盆/智慧树肥料", "肥料/第7卡槽", "收音盒", "杀虫剂/手套/池塘清洁车", "花盆推车/草耙", "包扎坚果" };

const char* plantSpeedList[] = { "豌豆射手", "向日葵", "樱桃炸弹", "坚果墙", "土豆雷",
"寒冰射手", "大嘴花", "双发射手", "小喷菇", "阳光菇", "大喷菇", "墓碑吞噬者",
"魅惑菇", "胆小菇", "寒冰菇", "毁灭菇", "睡莲", "窝瓜", "三线射手", "缠绕海藻",
"火爆辣椒", "地刺", "火炬树桩", "高坚果", "海蘑菇", "路灯花", "仙人掌",
"三叶草", "裂荚射手", "杨桃", "南瓜头", "磁力菇", "卷心菜投手", "花盆",
"玉米投手", "咖啡豆", "大蒜", "叶子保护伞", "金盏花", "西瓜投手", "机枪射手",
"双子向日葵", "忧郁菇", "香蒲", "冰瓜", "吸金磁", "地刺王" };

const char* plantvalueList[] = { "豌豆射手", "向日葵", "樱桃炸弹", "坚果墙", "土豆雷",
"寒冰射手", "大嘴花", "双发射手", "小喷菇", "阳光菇", "大喷菇", "墓碑吞噬者",
"魅惑菇", "胆小菇", "寒冰菇", "毁灭菇", "睡莲", "窝瓜", "三线射手", "缠绕海藻",
"火爆辣椒", "地刺", "火炬树桩", "高坚果", "海蘑菇", "路灯花", "仙人掌",
"三叶草", "裂荚射手", "杨桃", "南瓜头", "磁力菇", "卷心菜投手", "花盆",
"玉米投手", "咖啡豆", "大蒜", "叶子保护伞", "金盏花", "西瓜投手", "机枪射手",
"双子向日葵", "忧郁菇", "香蒲", "冰瓜", "吸金磁", "地刺王","玉米加农炮" };

const char* PlantTimeList[] = { "樱桃炸弹/火爆辣椒", "食人花", "土豆雷" };

const char* plantHealthyList[] = { "一般植物", "坚果", "高坚果", "南瓜头", "南瓜头", "地刺王" };

const char* ValueList[] = { "银币", "钻石", "普通阳光", "小阳光", "大阳光" };

const char* ZLifeList[] = { "普通僵尸", "舞王僵尸", "冰车僵尸", "海豚僵尸", "小丑僵尸", "矿工僵尸", "跳跳僵尸",
"雪人僵尸", "蹦极僵尸", "扶梯僵尸", "巨人僵尸", "僵王博士", "迷你模式僵王博士", "坚果僵尸", "辣椒僵尸",
"高坚果僵尸", "红眼僵尸", "IZ小鬼" };

const char* ZALifeList[] = { "路障", "铁桶", "报纸", "铁门", "橄榄帽", "气球", "矿工帽" };

const char* ZHitList[] = { "僵尸啃咬", "巨人锤击", "篮球", "豌豆" };

const char* MoneyFlowerList[] = { "银币", "金币", "钻石", "普通阳光", "小阳光", "大阳光" };

const char* ProTimeList[] = { "冰冻时间", "黄油时间", "减速时间" };

const char* BulletDamageList[] = { "普通豌豆", "冰豌豆",
"卷心菜", "西瓜", "孢子","冰西瓜", "火豌豆", "星星", "尖刺",
"玉米粒", "黄油", "土豆雷", "窝瓜","寒冰菇", "食人花" };

const char* PeaZombieDamageType[] = { "无异常", "向后攻击", "在空中留下子弹" };

const char* izeList[] = { "豌豆阵", "大嘴地雷阵", "地刺杨桃阵", "大喷磁铁阵", "胆小阵",
"大杂烩阵1", "大杂烩阵2", "大杂烩阵3" };

const char* cnList[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

const char* czList[] = { "普通", "路障", "撑杆", "铁桶", "扶梯", "矿工", "蹦极", "橄榄球", "气球", "铁栅门", "冰车", "跳跳", "舞王", "白眼", "小鬼" };

const char* fList[] = { "豌豆射手", "向日葵", "樱桃炸弹", "坚果墙", "土豆雷",
"寒冰射手", "大嘴花", "双发射手", "小喷菇", "阳光菇", "大喷菇", "墓碑吞噬者",
"魅惑菇", "胆小菇", "寒冰菇", "毁灭菇", "睡莲", "窝瓜", "三线射手", "缠绕海藻",
"火爆辣椒", "地刺", "火炬树桩", "高坚果", "海蘑菇", "路灯花", "仙人掌",
"三叶草", "裂荚射手", "杨桃", "南瓜头", "磁力菇", "卷心菜投手", "花盆",
"玉米投手", "咖啡豆", "大蒜", "叶子保护伞", "金盏花", "西瓜投手", "机枪射手",
"双子向日葵", "忧郁菇", "香蒲", "冰瓜", "吸金磁", "地刺王", "玉米加农炮", "模仿者",
"爆炸坚果", "巨大坚果" };

const char* fsList[] = { "幼苗", "小花", "中花", "大花" };

const char* fpList[] = { "花园", "蘑菇园", "小车", "水族馆" };

enum
{
	Tab_General,
	Tab_Pass,
	Tab_Plants,
	Tab_Zombies,
	Tab_GaGngTeEr,
	Tab_Scene,
	Tab_Seed,
	Tab_FullScreen,
	Tab_Garden,
	Tab_More,

	Tab_Num
};

class Tabs
{
public:
	void init(HWND hWnd
		, const int ID[]
		, const DLGPROC Procs[]
		, const char* Name[]
		, const int count)
	{
		RECT rect;
		GetClientRect(hWnd, &rect);
		TCITEM tie;
		tie.mask = TCIF_TEXT | TCIF_IMAGE;
		tie.iImage = -1;
		for (int i = 0; i < count; ++i)
		{
			HWND hc = CreateDialog(hInst, MAKEINTRESOURCE(ID[i]), hWnd, Procs[i]);
			m_child.push_back(hc);
			MoveWindow(m_child[i], 1, 39, rect.right - rect.left - 2, rect.bottom - rect.top - 40, FALSE);
			tie.pszText = const_cast<char*>(Name[i]);
			SendMessage(hWnd, TCM_INSERTITEM, i, LPARAM(&tie));
			ShowWindow(hc, SW_HIDE);
		}
		m_curWnd = 0;
	}
	void Show(const int n)
	{
		ShowWindow(m_child[m_curWnd], SW_HIDE);
		ShowWindow(m_child[m_curWnd = n], SW_SHOW);
	}
	HWND getChild(const int n) { return m_child[n]; }
private:
	std::vector<HWND> m_child;
	int m_curWnd;
};

INT_PTR CALLBACK GeneralProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK PassProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK PlantsProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK MoreProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK ZombiesProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK GaGangTeErProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK SceneProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK SeedProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK FullScreenProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK GardenProc(HWND, UINT, WPARAM, LPARAM);

const int Tab_ID[Tab_Num] = { IDD_GENERAL, IDD_PASS, IDD_PLANTS, IDD_ZOMBIES, IDD_GAGANGTEER, IDD_SCENE, IDD_SEED, IDD_FULLSCREEN, IDD_GARDEN, IDD_MORE };
const DLGPROC Tab_Procs[Tab_Num] = { GeneralProc, PassProc, PlantsProc, ZombiesProc, GaGangTeErProc, SceneProc, SeedProc, FullScreenProc, GardenProc, MoreProc };
const char* Tab_Name[Tab_Num] = { "常规", "穿越", "植物", "僵尸", "伽刚特尔", "场景", "出怪", "全屏", "花园", "更多"};
// 锟剿达拷锟斤拷模锟斤拷锟叫帮拷锟斤拷锟侥猴拷锟斤拷锟斤拷前锟斤拷锟斤拷锟斤拷:
BOOL				InitInstance(HINSTANCE, int);
INT_PTR CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void LoadSkin();
std::shared_ptr<PVZ> judgeProcess(Process &p, std::string &err);

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO:  在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PVZ_HELPER, szWindowClass, MAX_LOADSTRING);

	// 执行应用程序初始化: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PVZ_HELPER));
	// 主消息循环: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}


DWORD WINAPI CheckOKThread(LPVOID pWaitTime)
{
	string str1 = "你触发了第";
	string str3 = "层保护机制，按确认退出";
	string str4 = str1 + baohu + str3;
	LPCSTR a = str4.c_str();
	MessageBoxA(NULL, a, "MsgMonitor dead.", MB_OK || MB_ICONERROR);
	exit(0);
	return 0;
}

void CALLBACK CheckSBTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTimer)
{
	if (DeveloperMode != true)
	{
		bool cunzai = getProcess("MsgMonitor.exe");
		bool cunzai2 = getProcessA("MsgMonitor");

		if (cunzai == true)
		{
			system("taskkill /im MsgMonitor.exe");
			baohu = "一";
			DWORD threadId;
			CreateThread(NULL, 0, &CheckOKThread, NULL, 0, &threadId);
			Sleep(939504396034869345);
		}
		else if (cunzai2 == true)
		{
			baohu = "二";
			DWORD threadId;
			CreateThread(NULL, 0, &CheckOKThread, NULL, 0, &threadId);
			Sleep(939504396034869345);
		}
	}
}

Tabs htabs;

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // 锟斤拷实锟斤拷锟斤拷锟斤拷娲?锟斤拷全锟街憋拷锟斤拷锟斤拷
	LoadSkin();

	hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, WndProc);
	SetWindowPos(hWnd, NULL, 500, 100, 730, 475, SWP_NOREPOSITION);
	if (!hWnd)
	{
		return FALSE;
	}

	char winTitle[256];
	SendMessage(hWnd, WM_GETTEXT, sizeof(winTitle), LPARAM(winTitle));
	SendMessage(hWnd, WM_SETTEXT, 0, LPARAM(winTitle));

	htabs.init(GetDlgItem(hWnd, IDC_TAB1)
		, Tab_ID
		, Tab_Procs
		, Tab_Name
		, Tab_Num);
	SetWindowTextA(hWnd, version);
	SetDlgItemTextA(htabs.getChild(Tab_General), IDC_SUNNUM, "9990");
	SetDlgItemTextA(htabs.getChild(Tab_General), IDC_MONEYNUM, "99999");
	SetDlgItemTextA(htabs.getChild(Tab_Pass), IDC_B1R, "1");
	SetDlgItemTextA(htabs.getChild(Tab_Pass), IDC_NORMALOKSUNNUM, "50");
	SetDlgItemTextA(htabs.getChild(Tab_Pass), IDC_FIRSTOKSUNNUM, "150");
	SetDlgItemTextA(htabs.getChild(Tab_Pass), IDC_B1C, "3");
	SetDlgItemTextA(htabs.getChild(Tab_Pass), IDC_B2R, "2");
	SetDlgItemTextA(htabs.getChild(Tab_Pass), IDC_B2C, "10");
	SetDlgItemTextA(htabs.getChild(Tab_Pass), IDC_W1R, "4");
	SetDlgItemTextA(htabs.getChild(Tab_Pass), IDC_W1C, "10");
	SetDlgItemTextA(htabs.getChild(Tab_Pass), IDC_W2R, "5");
	SetDlgItemTextA(htabs.getChild(Tab_Pass), IDC_W2C, "3");
	INIT_LIST(htabs.getChild(Tab_Pass), IDC_LSLIST, LSList);
	SetTimer(hWnd, 31, 500, (TIMERPROC)CheckSBTimer);
	INIT_LIST(htabs.getChild(Tab_General), IDC_PLIST, pList);
	INIT_LIST(htabs.getChild(Tab_General), IDC_ZLIST, zList);
	SendDlgItemMessage(hWnd, IDC_ZLIST, CB_ADDSTRING, 0, LPARAM("无梯僵尸"));
	INIT_LIST(htabs.getChild(Tab_General), IDC_BLIST, bList);
	INIT_LIST(htabs.getChild(Tab_General), IDC_NOWMLIST, NowMList);
	INIT_LIST(htabs.getChild(Tab_Plants), IDC_FIREDOULIST, FireDouList);
	INIT_LIST(htabs.getChild(Tab_Plants), IDC_FIREICEDOULIST, FireIceDouList);
	INIT_LIST(htabs.getChild(Tab_General), IDC_SHOPPRICELIST, ShopPrice);
	INIT_LIST(htabs.getChild(Tab_General), IDC_PLANTSPEEDLIST, plantSpeedList);
	INIT_LIST(htabs.getChild(Tab_General), IDC_PLANTVALUELIST, plantvalueList);
	INIT_LIST(htabs.getChild(Tab_General), IDC_PLANTHEALTHYLIST, plantHealthyList);
	INIT_LIST(htabs.getChild(Tab_General), IDC_VALUELIST, ValueList);
	INIT_LIST(htabs.getChild(Tab_Plants), IDC_MONEYFLOWERLIST1, MoneyFlowerList);
	INIT_LIST(htabs.getChild(Tab_Plants), IDC_MONEYFLOWERlist2, MoneyFlowerList);
	INIT_LIST(htabs.getChild(Tab_Zombies), IDC_FUCKINGPEAZOMBIEDAMAGETYPELIST, PeaZombieDamageType);
	INIT_LIST(htabs.getChild(Tab_Zombies), IDC_PEAZOMBIEDAMAGETYPELIST, PeaZombieDamageType);
	INIT_LIST(htabs.getChild(Tab_Zombies), IDC_ZLIFELIST, ZLifeList);
	INIT_LIST(htabs.getChild(Tab_Zombies), IDC_ZALIFELIST, ZALifeList);
	INIT_LIST(htabs.getChild(Tab_Zombies), IDC_ZHITLIST, ZHitList);
	INIT_LIST(htabs.getChild(Tab_General), IDC_PLANTTIMELIST, PlantTimeList);
	INIT_LIST(htabs.getChild(Tab_General), IDC_PROTIMELIST, ProTimeList);
	INIT_LIST(htabs.getChild(Tab_General), IDC_BULLETDAMAGELIST, BulletDamageList);
	INIT_LIST(htabs.getChild(Tab_Scene), IDC_NLIST, nList);
	INIT_LIST(htabs.getChild(Tab_Scene), IDC_RLIST, rList);
	INIT_LIST(htabs.getChild(Tab_Scene), IDC_SCENELIST, SceneList);
	INIT_LIST(htabs.getChild(Tab_Pass), IDC_MLIST, mList);
	INIT_LIST(htabs.getChild(Tab_Pass), IDC_IZELIST, izeList);
	INIT_LIST(htabs.getChild(Tab_General), IDC_CNLIST, cnList);
	INIT_LIST(htabs.getChild(Tab_General), IDC_CIDLIST, cnList);
	INIT_LIST(htabs.getChild(Tab_General), IDC_CPLIST, cardList);
	INIT_LIST(htabs.getChild(Tab_General), IDC_CZLIST, czList);
	INIT_LIST(htabs.getChild(Tab_Seed), IDC_SLIST, zList);
	INIT_LIST(htabs.getChild(Tab_Garden), IDC_FLOWER_LIST, fList);
	INIT_LIST(htabs.getChild(Tab_Garden), IDC_FLOWER_SIZE, fsList);
	INIT_LIST(htabs.getChild(Tab_Garden), IDC_PLACE_LIST, fpList);

	CheckDlgButton(htabs.getChild(Tab_Plants), IDC_PNORMAL, BST_CHECKED);
	CheckDlgButton(htabs.getChild(Tab_Zombies), IDC_BOOM_NORMAL, BST_CHECKED);
	CheckDlgButton(htabs.getChild(Tab_Zombies), IDC_VISIABLE_NORMAL, BST_CHECKED);
	CheckDlgButton(htabs.getChild(Tab_Zombies), IDC_ZNORMAL, BST_CHECKED);
	CheckDlgButton(htabs.getChild(Tab_Seed), IDC_NATURAL, BST_CHECKED);

	SendDlgItemMessage(htabs.getChild(Tab_Zombies), IDC_SLIDER_TIMER, TBM_SETRANGE, TRUE, MAKELONG(0, 350));
	SendDlgItemMessage(htabs.getChild(Tab_Zombies), IDC_SLIDER_GATHER, TBM_SETRANGE, TRUE, MAKELONG(0, 800));
	SendDlgItemMessage(htabs.getChild(Tab_Zombies), IDC_SLIDER_GATHER, TBM_SETPOS, TRUE, 800);

	SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL)));
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	htabs.Show(Tab_General);
	SendMessage(hWnd, WM_INIT, 0, 0);
	return TRUE;
}

void LoadSkin()
{
	static CDllFromMem dll;
	dll.LoadLibraryFromRs(hInst, "File", MAKEINTRESOURCE(IDR_SKINDLL));
	auto pLoadSkin = (void(__stdcall *)(void *, int, char *, int, int, int))dll.GetProcAddressFromRs("SkinH_AttachRes");
	HRSRC hres = FindResourceA(NULL, MAKEINTRESOURCE(IDR_SKIN), "File");
	size_t skinsize = SizeofResource(NULL, hres);
	LPVOID pSkinBuffer = LockResource(LoadResource(NULL, hres));
	pLoadSkin(pSkinBuffer, skinsize, "", 0, 0, 0);
}

static void InitGame(HWND hWnd)
{
	std::string err;
	Process::LookupProcess([&](const char* name, DWORD pid)
	{
		std::string strName = name;
		if (strName != "popcapgame1.exe"
			&& strName.find("PlantsVsZombies") == std::string::npos
			&& strName.find("植物大战僵尸") == std::string::npos)
		{
			return false;
		}
		Process tmp;
		tmp.OpenByPid(pid);
		pvz = judgeProcess(tmp, err);
		if (pvz != nullptr)
		{
			return true;
		}
		return false;
	});
	if (pvz == nullptr)
	{
		pvz = std::make_shared<PVZ>(Process());
		if (err != "")
		{
			MessageBox(hWnd, err.c_str(), "错误", MB_OK | MB_ICONERROR);
		}
		else
		{
			MessageBox(hWnd, "找不到游戏", "错误", MB_OK);
		}
	}
	else
	{
		pvz->Patch();
		pvz->InitExtraCode();
	}
}

std::shared_ptr<PVZ> judgeProcess(Process& process, std::string& err)
{
	if (!process.IsValid())
	{
		return nullptr;
	}
	if (process.ReadMemory(4, 0x0042748e) == 0xff563de8)
	{
		return std::make_shared<PVZ_1_0>(process);
	}
	else
	{
		if (process.ReadMemory(4, 0x0044002e) == 0xff531de8)
		{
			err = "这个版本的游戏会崩溃，请下载其他版本！";
		}
		return nullptr;
	}
}

INT_PTR CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 锟斤拷锟斤拷锟剿碉拷选锟斤拷:
		switch (wmId)
		{
		case IDCANCEL:
			DestroyWindow(hWnd);
			break;
		case IDC_RESTART:
			SendMessage(hWnd, WM_INIT, 0, 0);
			break;
		default:
			return FALSE;
		}
		break;
	case WM_NOTIFY:
		if (wParam == IDC_TAB1)
		{
			if (LPNMHDR(lParam)->code == TCN_SELCHANGE)
			{
				htabs.Show(SendDlgItemMessage(hWnd, IDC_TAB1, TCM_GETCURSEL, 0, 0));
			}
		}
		break;
	case WM_INIT:
		InitGame(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

void CALLBACK LockSunTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	pvz->SetSun(GetDlgItemInt(hWnd, IDC_SUNNUM, NULL, TRUE));
}

void CALLBACK LockMoneyTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	pvz->SetMoney(GetDlgItemInt(hWnd, IDC_MONEYNUM, NULL, TRUE));
}

void CALLBACK CardFlickerTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTimer)
{
	pvz->CardFlicker(IsDlgButtonChecked(hWnd, IDC_CARDFLICKER));
}

void CALLBACK LockMouseTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTimer)
{
	pvz->NowMouse(SendDlgItemMessage(hWnd, IDC_NOWMLIST, CB_GETCURSEL, 0, 0) + 6);
}

void CALLBACK LockBossLifeTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTimer)
{
	pvz->BossLife(GetDlgItemInt(hWnd, IDC_BOSSLIFENUM, NULL, TRUE));
}

void CALLBACK SetZombieTimerTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTimer)
{
	pvz->SetZombieTimer(GetDlgItemInt(hWnd, IDC_SETZOMBIETIMERNUM, NULL, TRUE));
}

void CALLBACK ShowHeadTimerTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTimer)
{
	pvz->ShowHeadTimer(GetDlgItemInt(hWnd, IDC_SHOWHEADTIMERNUM, NULL, TRUE));
}

INT_PTR CALLBACK GeneralProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// 锟斤拷锟斤拷锟剿碉拷选锟斤拷:
		switch (wmId)
		{
		case IDC_SUN_MORE1: /*锟斤拷锟斤拷越锟斤拷越锟斤拷*/
			pvz->SunMore(IsDlgButtonChecked(hWnd, IDC_SUN_MORE1));
			break;
		case IDC_MONEY_MORE1: /*锟斤拷锟皆斤拷锟皆斤拷锟?*/
			pvz->MoneyMore(IsDlgButtonChecked(hWnd, IDC_MONEY_MORE1));
			break;
		case IDC_SUN_LOCK: /*锟斤拷锟斤拷锟斤拷锟斤拷*/
			if (IsDlgButtonChecked(hWnd, IDC_SUN_LOCK) == true)
			{
				SetTimer(hWnd, 1, 50, (TIMERPROC)LockSunTimer);
			}
			else
			{
				KillTimer(hWnd, 1);
				return 0;
			}
			break;
		case IDC_LOCKMOUSE: /*������￿*/
			if (IsDlgButtonChecked(hWnd, IDC_LOCKMOUSE == true))
			{
				SetTimer(hWnd, 4, 1, (TIMERPROC)LockMouseTimer);
			}
			else
			{
				KillTimer(hWnd, 4);
					return 0;
			}
			break;
		case IDC_CARDFLICKER: //锟斤拷片锟斤拷烁
			if (IsDlgButtonChecked(hWnd, IDC_CARDFLICKER) == true)
			{
				SetTimer(hWnd, 3, 800, (TIMERPROC)CardFlickerTimer);
			}
			else
			{
				pvz->CardFlicker(IsDlgButtonChecked(hWnd, IDC_CARDFLICKER));
				KillTimer(hWnd, 3);
				return 0;
			}
			break;
		case IDC_ONECARD: //一锟斤拷锟斤拷锟斤拷
			pvz->OneCardStart(IsDlgButtonChecked(hWnd, IDC_ONECARD));
			break;
		case IDC_FORCECARD: //强锟斤拷选锟斤拷
			MessageBoxA(hWnd, "强制选卡指的是可以在一些无法选卡的关卡强制\n选卡，如传送带等关卡。", "提示", MB_OK);
			pvz->ForceCard(IsDlgButtonChecked(hWnd, IDC_FORCECARD));
			break;
		case IDC_NOGRAVE: //锟斤拷锟侥癸拷锟?
			pvz->NoGrave(IsDlgButtonChecked(hWnd, IDC_NOGRAVE));
			break;
		case IDC_UNLOCK: /*全模式锟斤拷锟斤拷*/
			pvz->Unlock(IsDlgButtonChecked(hWnd, IDC_UNLOCK));
			break;
		case IDC_MONEY_LOCK: /*锟斤拷锟斤拷锟斤拷锟?*/
			if (IsDlgButtonChecked(hWnd, IDC_MONEY_LOCK == true))
			{
				SetTimer(hWnd, 2, 50, (TIMERPROC)LockMoneyTimer);
			}
			else
			{
				KillTimer(hWnd, 2);
				return 0;
			}
			break;
		case IDC_CARD_NUM: /*锟斤拷锟斤拷锟斤拷锟斤拷*/
			pvz->SetCardNum(GetDlgItemInt(hWnd, IDC_CNLIST, NULL, TRUE));
			break;
		case IDC_CPBTN:/*修改为植物*/
		{
			int type = SendDlgItemMessage(hWnd, IDC_CPLIST, CB_GETCURSEL, 0, 0);
			if (type == 48)
				type = 52;
			pvz->SetCard(GetDlgItemInt(hWnd, IDC_CIDLIST, NULL, TRUE) - 1, type, IsDlgButtonChecked(hWnd, IDC_CPCOPY));
			break;
		}
		case IDC_CZBTN:/*修改为僵尸*/
			pvz->SetCard(GetDlgItemInt(hWnd, IDC_CIDLIST, NULL, TRUE) - 1, SendDlgItemMessage(hWnd, IDC_CZLIST, CB_GETCURSEL, 0, 0) + 60);
			break;
		case IDC_SHOPPRICE: //锟睫革拷锟教碉拷锟斤拷品
			pvz->ShopPrice(SendDlgItemMessage(hWnd, IDC_SHOPPRICELIST, CB_GETCURSEL, 0, 0), GetDlgItemInt(hWnd, IDC_SHOPPRICENUM, NULL, TRUE));
			break;
		case IDC_PLANTSPEED: //锟睫革拷植锟斤拷锟斤拷锟斤拷
			pvz->PlantSetSpeed(SendDlgItemMessage(hWnd, IDC_PLANTSPEEDLIST, CB_GETCURSEL, 0, 0), GetDlgItemInt(hWnd, IDC_PLANTSPEEDNUM, NULL, TRUE));
			break;
		case IDC_PLANTHEALTHY: //锟睫革拷植锟斤拷血锟斤拷
			pvz->PlantSetHealthy(SendDlgItemMessage(hWnd, IDC_PLANTHEALTHYLIST, CB_GETCURSEL, 0, 0), GetDlgItemInt(hWnd, IDC_PLANTHEALTHYNUM, NULL, TRUE));
			break;
		case IDC_VALUE: //锟??革拷锟斤拷品锟斤拷值
			pvz->SetItemValue(SendDlgItemMessage(hWnd, IDC_VALUELIST, CB_GETCURSEL, 0, 0), GetDlgItemInt(hWnd, IDC_VALUENUM, NULL, TRUE));
			break;
		case IDC_PLANTVALUE: //锟睫革拷植锟斤魁?革拷
			pvz->SetPlantValue(SendDlgItemMessage(hWnd, IDC_PLANTVALUELIST, CB_GETCURSEL, 0, 0), GetDlgItemInt(hWnd, IDC_PLANTVALUENUM, NULL, TRUE));
			break;
		case IDC_PLANTTIME: //锟揭斤拷时锟斤拷
			pvz->SetPlantTime(SendDlgItemMessage(hWnd, IDC_PLANTTIMELIST, CB_GETCURSEL, 0, 0), GetDlgItemInt(hWnd, IDC_PLANTTIMENUM, NULL, TRUE));
			break;
		case IDC_PROTIME: //效锟斤拷时锟斤拷
			pvz->ProTime(SendDlgItemMessage(hWnd, IDC_PROTIMELIST, CB_GETCURSEL, 0, 0), GetDlgItemInt(hWnd, IDC_PROTIMENUM, NULL, TRUE));
			break;
		case IDC_BULLETDAMAGE: //锟接碉拷锟斤拷锟斤拷锟斤拷
			pvz->BulletDamage(SendDlgItemMessage(hWnd, IDC_BULLETDAMAGELIST, CB_GETCURSEL, 0, 0), GetDlgItemInt(hWnd, IDC_BULLETDAMAGENUM, NULL, TRUE));
			break;
		case IDC_SUN: /*锟睫革拷锟斤拷锟斤拷*/
			pvz->SetSun(GetDlgItemInt(hWnd, IDC_SUNNUM, NULL, TRUE));
			break;
		case IDC_MONEY: /*锟??改斤拷钱*/
			pvz->SetMoney(GetDlgItemInt(hWnd, IDC_MONEYNUM, NULL, TRUE));
			break;
		case IDC_NOSUN: /*锟斤拷锟斤拷锟斤拷锟斤拷*/
			pvz->IgnoreSun(IsDlgButtonChecked(hWnd, IDC_NOSUN));
			break;
		case IDC_MAXSUN: //锟斤拷锟斤拷锟斤拷锟?
			pvz->MaxSun(GetDlgItemInt(hWnd, IDC_MAXSUNNUM, NULL, TRUE));
			break;
		case IDC_MAXMONEY: //锟斤拷锟斤拷锟斤拷锟?
			pvz->MaxMoney(GetDlgItemInt(hWnd, IDC_MAXMONEYNUM, NULL, TRUE));
			break;
		case IDC_COLLECT: /*锟皆讹拷锟秸硷拷*/
			pvz->AutoPickup(IsDlgButtonChecked(hWnd, IDC_COLLECT));
			break;
		case IDC_NOWMOUSE: //锟斤拷锟斤拷锟斤拷锟?
			pvz->NowMouse(SendDlgItemMessage(hWnd, IDC_NOWMLIST, CB_GETCURSEL, 0, 0 + 6));
			break;
		case IDC_PLANTING:/*种植物*/
		{
			int row = GetDlgItemInt(hWnd, IDC_ROW, NULL, TRUE) - 1;
			int col = GetDlgItemInt(hWnd, IDC_COL, NULL, TRUE) - 1;
			int type = SendDlgItemMessage(hWnd, IDC_PLIST, CB_GETCURSEL, 0, 0);
			if (type == 48)
				type = 52;
			pvz->Planting(row, col, type, IsDlgButtonChecked(hWnd, IDC_COPY));
			break;
		}
		case IDC_NOPAUSE: /*取锟斤拷锟斤拷停*/
			pvz->NoPause(IsDlgButtonChecked(hWnd, IDC_NOPAUSE));
			break;
		case IDC_THEWORLD: //锟斤拷锟斤拷鲁锟斤拷
			pvz->TheWorld(IsDlgButtonChecked(hWnd, IDC_THEWORLD));
			break;
		case IDC_PUT_ZOMBIE:/*放僵尸*/
		{
			int row = GetDlgItemInt(hWnd, IDC_ROW, NULL, TRUE) - 1;
			int col = GetDlgItemInt(hWnd, IDC_COL, NULL, TRUE) - 1;
			int type = SendDlgItemMessage(hWnd, IDC_ZLIST, CB_GETCURSEL, 0, 0);
			if (type == 33)
				type = 36;
			pvz->PutZombie(row, col, type);
			break;
		}
		case IDC_PUT_LADDER:/*放梯子*/
		{
			int row = GetDlgItemInt(hWnd, IDC_ROW, NULL, TRUE) - 1;
			int col = GetDlgItemInt(hWnd, IDC_COL, NULL, TRUE) - 1;
			pvz->PutLadder(row, col);
			break;
		}
		case IDC_PUT_GRAVE: /*锟斤拷墓锟斤拷*/
		{
			int row = GetDlgItemInt(hWnd, IDC_ROW, NULL, TRUE) - 1;
			int col = GetDlgItemInt(hWnd, IDC_COL, NULL, TRUE) - 1;
			pvz->PutGrave(row, col);
			break;
		}
		case IDC_AUTO_LADDER: /*锟斤拷锟??达拷锟斤拷*/
			pvz->AutoLadder();
			break;
		case IDC_SHOWSHOVEL: //锟斤拷示锟斤拷锟斤拷
			pvz->ShowShovel(IsDlgButtonChecked(hWnd, IDC_SHOWSHOVEL));
			break;
		case IDC_BLOCK:/*改土地块*/
			{
				int row = GetDlgItemInt(hWnd, IDC_ROW, NULL, TRUE) - 1;
				int col = GetDlgItemInt(hWnd, IDC_COL, NULL, TRUE) - 1;
				int type = SendDlgItemMessage(hWnd, IDC_BLIST, CB_GETCURSEL, 0, 0) + 1;
				pvz->SetBlocks(row, col, type);
			}
			break;
		case IDC_NO_DELETE: /*锟斤拷止删锟斤拷*/
			pvz->NoDelete(IsDlgButtonChecked(hWnd, IDC_NO_DELETE));
			break;
		case IDC_NO_SAVE: /*锟斤拷止锟芥档*/
			pvz->NoSave(IsDlgButtonChecked(hWnd, IDC_NO_SAVE));
			break;
		case IDC_ANYWHERE: /*锟斤拷锟缴凤拷锟斤拷*/
			pvz->Anywhere(IsDlgButtonChecked(hWnd, IDC_ANYWHERE));
			break;
		case IDC_FAST_BELT: /*锟斤拷锟酵达拷锟斤拷锟接筹拷*/
			pvz->FastBelt(IsDlgButtonChecked(hWnd, IDC_FAST_BELT));
			break;
		case IDC_SHOW_HIDE: /*锟斤拷锟斤拷锟斤拷小锟斤拷戏*/
			pvz->ShowHide(IsDlgButtonChecked(hWnd, IDC_SHOW_HIDE));
			break;
		case IDC_FULL_FOG: /*全锟斤拷浓锟斤拷*/
			pvz->FullFog(IsDlgButtonChecked(hWnd, IDC_FULL_FOG));
			break;
		case IDC_SEE_FOG: /*浓锟斤拷透锟斤拷*/
			pvz->SeeFog(IsDlgButtonChecked(hWnd, IDC_SEE_FOG));
			break;
		case IDC_SEE_VASE: /*锟斤拷瓶透锟斤拷*/
			pvz->SeeVase(IsDlgButtonChecked(hWnd, IDC_SEE_VASE));
			break;
		default:
			return FALSE;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK PassProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// 锟斤拷锟斤拷锟剿碉拷选锟斤拷:
		switch (wmId)
		{
		case IDC_JMP_LV: /*锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟?*/
			pvz->JmpLevel(GetDlgItemInt(hWnd, IDC_LV_NUM, NULL, TRUE));
			break;
		case IDC_MIX: /*锟斤拷锟斤拷*/
		{
			int lv = GetDlgItemInt(hWnd, IDC_LV2, NULL, TRUE);
			if (lv == 0)
				lv = 1;
			int mode = SendDlgItemMessage(hWnd, IDC_MLIST, CB_GETCURSEL, 0, 0);
			if (mode > 42)
				++mode;
			if (mode == 50)
				mode = 60;
			if (mode == 51)
				mode = 70;
			pvz->MixMode(mode, lv);
			break;
		}
		case IDC_WIN: /*直锟接癸拷锟斤拷*/
			pvz->Win();
			break;
		case IDC_LOCK: /*锟斤拷锟斤拷锟斤拷锟斤拷*/
			if (IsDlgButtonChecked(hWnd, IDC_LOCK))
			{
				EnableWindow(GetDlgItem(hWnd, IDC_IZELIST), FALSE);
				pvz->Lock(true, SendDlgItemMessage(hWnd, IDC_IZELIST, CB_GETCURSEL, 0, 0));
			}
			else
			{
				EnableWindow(GetDlgItem(hWnd, IDC_IZELIST), TRUE);
				pvz->Lock(false);
			}
			break;
		case IDC_LITTLE: /*小锟斤拷尸*/
			pvz->Little(IsDlgButtonChecked(hWnd, IDC_LITTLE));
			break;
		case IDC_RAIN: /*锟斤拷锟斤拷*/
			pvz->Rain(IsDlgButtonChecked(hWnd, IDC_RAIN));
			break;
		case IDC_hammering: //锟斤拷锟斤拷尸
			pvz->Hammering(IsDlgButtonChecked(hWnd, IDC_hammering));
			break;
		case IDC_BUNGEE: //锟侥硷拷锟斤拷锟斤拷战
			pvz->Bungee(IsDlgButtonChecked(hWnd, IDC_BUNGEE));
			break;
		case IDC_GRAVE: //锟斤拷墓模式
			pvz->GraveMode(IsDlgButtonChecked(hWnd, IDC_GRAVE));
			break;
		case IDC_ADNUM: //冒锟秸达拷锟斤拷
			pvz->SetAdNum(GetDlgItemInt(hWnd, IDC_ADNUMNUM, NULL, TRUE));
			break;
		case IDC_STORM: /*锟斤拷锟斤拷锟斤拷*/
			pvz->Storm(IsDlgButtonChecked(hWnd, IDC_STORM));
			break;
		case IDC_FORCE: /*锟斤拷锟斤拷*/
			pvz->Force(IsDlgButtonChecked(hWnd, IDC_FORCE));
			break;
		case IDC_LIKE_COL: /*锟斤拷锟斤拷锟斤拷一锟斤拷*/
			pvz->LikeCol(IsDlgButtonChecked(hWnd, IDC_LIKE_COL));
			break;
		case IDC_RUN_FAST: /*锟斤拷尸锟斤拷锟斤拷*/
			pvz->RunFast(IsDlgButtonChecked(hWnd, IDC_RUN_FAST));
			break;
		case IDC_NORMALOKSUN: //锟斤拷锟斤拷锟斤拷始锟斤拷锟斤拷
			pvz->NormalOKSun(GetDlgItemInt(hWnd, IDC_NORMALOKSUNNUM, NULL, TRUE));
			break;
		case IDC_FIRSTOKSUN: //1-1锟斤拷始锟斤拷锟斤拷
			pvz->FirstOKSun(GetDlgItemInt(hWnd, IDC_FIRSTOKSUNNUM, NULL, TRUE));
			break;
		case IDC_START_DOOR: /*锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷*/
			pvz->StartDoor(IsDlgButtonChecked(hWnd, IDC_START_DOOR));
			break;
		case IDC_STABLE_DOOR: /*锟教讹拷锟斤拷锟斤拷锟斤拷*/
			pvz->StableDoor(IsDlgButtonChecked(hWnd, IDC_STABLE_DOOR));
			break;
		case IDC_LSTATE://关卡状态
			pvz->LevelState(SendDlgItemMessage(hWnd, IDC_LSLIST, CB_GETCURSEL, 0, 0));
			break;
		case IDC_SET_DOOR: /*锟斤拷锟缴达拷锟斤拷锟斤拷*/
			pvz->SetDoor(
				GetDlgItemInt(hWnd, IDC_B1R, NULL, TRUE) - 1,
				GetDlgItemInt(hWnd, IDC_B1C, NULL, TRUE) - 1,
				GetDlgItemInt(hWnd, IDC_B2R, NULL, TRUE) - 1,
				GetDlgItemInt(hWnd, IDC_B2C, NULL, TRUE) - 1,
				GetDlgItemInt(hWnd, IDC_W1R, NULL, TRUE) - 1,
				GetDlgItemInt(hWnd, IDC_W1C, NULL, TRUE) - 1,
				GetDlgItemInt(hWnd, IDC_W2R, NULL, TRUE) - 1,
				GetDlgItemInt(hWnd, IDC_W2C, NULL, TRUE) - 1
			);
			break;
		default:
			return FALSE;
		}
		break;
	case WM_NOTIFY:
		if (wParam == IDC_TAB1)
		{
			if (LPNMHDR(lParam)->code == TCN_SELCHANGE)
			{
				htabs.Show(SendDlgItemMessage(hWnd, IDC_TAB1, TCM_GETCURSEL, 0, 0));
			}
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK PlantsProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// 锟斤拷锟斤拷锟剿碉拷选锟斤拷:
		switch (wmId)
		{
		case IDC_CORN_NO_WAIT: /*锟斤拷锟斤拷锟斤拷锟斤拷却锟?*/
			pvz->CornNoWait(IsDlgButtonChecked(hWnd, IDC_CORN_NO_WAIT));
			break;
		case IDC_MAGNET_NO_WAIT: /*锟斤拷锟斤拷锟斤拷锟斤拷却锟?*/
			pvz->MagnetNoWait(IsDlgButtonChecked(hWnd, IDC_MAGNET_NO_WAIT));
			break;
		case IDC_POTATO_NO_WAIT: /*锟斤拷锟斤拷锟斤拷锟斤拷却锟?*/
			pvz->PotatoNoWait(IsDlgButtonChecked(hWnd, IDC_POTATO_NO_WAIT));
			break;
		case IDC_MOUTH_NO_WAIT: /*锟斤拷锟届花锟斤拷却锟?*/
			pvz->MouthNoWait(IsDlgButtonChecked(hWnd, IDC_MOUTH_NO_WAIT));
			break;
		case IDC_PSTRONG: /*锟??碉拷*/
			pvz->PStrong();
			break;
		case IDC_PNORMAL: /*锟斤拷锟斤拷*/
			pvz->PNormal();
			break;
		case IDC_PWEAK: /*锟斤拷锟斤拷*/
			pvz->PWeak();
			break;
		case IDC_CHKILLER: //锟斤拷锟斤拷锟秸革拷锟?
			pvz->ChKiller(IsDlgButtonChecked(hWnd, IDC_CHKILLER));
			break;
		case IDC_PLANTSPAPER: //植锟斤拷纸锟斤拷
			pvz->PlantsPaper(IsDlgButtonChecked(hWnd, IDC_PLANTSPAPER));
			break;
		case IDC_CHEATMODE: //锟斤拷锟斤拷模式
			pvz->CheatMode(IsDlgButtonChecked(hWnd, IDC_CHEATMODE));
			break;
		case IDC_CHANGEBULLET: //锟接碉拷锟斤拷锟斤拷
			pluginsopener("BulletChanger.exe");
			break;
		case IDC_NO_MARK: /*锟斤拷锟斤拷锟睫猴拷*/
			pvz->NoMark(IsDlgButtonChecked(hWnd, IDC_NO_MARK));
			break;
		case IDC_SETEAT: //锟斤拷锟届花锟斤拷围
			pvz->SetChomper(GetDlgItemInt(hWnd, IDC_SETEATNUM, NULL, TRUE));
			break;
		case IDC_SETFUMESHROOM: //锟斤拷锟界范围
			pvz->SetFumeShroom(GetDlgItemInt(hWnd, IDC_SETSETFUMESHROOMNUM, NULL, TRUE));
			break;
		case IDC_SETZENG: //锟斤拷锟界范围
			pvz->SetZeng(GetDlgItemInt(hWnd, IDC_SETZENGNUM, NULL, TRUE));
			break;
		case IDC_CHNOKILL: //锟斤拷锟届不锟斤拷
			pvz->ChNotKill(IsDlgButtonChecked(hWnd, IDC_CHNOKILL));
			break;
		case IDC_CATHACK: //锟斤拷锟斤拷锟斤拷全锟斤拷
			pvz->CatHack(IsDlgButtonChecked(hWnd, IDC_CATHACK));
			break;
		case IDC_BIGWALLNUT: //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
			pvz->BigWallnut(IsDlgButtonChecked(hWnd, IDC_BIGWALLNUT));
			break;
		case IDC_BACKWALLNUT: //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟?
			pvz->BackWallnut(IsDlgButtonChecked(hWnd, IDC_BACKWALLNUT));
			break;
		case IDC_FASTWALLNUT: //锟斤拷锟??憋拷锟斤拷锟斤拷
			pvz->FastWallnut(IsDlgButtonChecked(hWnd, IDC_FASTWALLNUT));
			break;
		case IDC_THEWORLD2: //锟斤拷锟斤拷鲁锟斤拷2
			pvz->TheWorld2(IsDlgButtonChecked(hWnd, IDC_THEWORLD2));
			break;
		case IDC_BOMBWALLNUT: //锟斤拷锟斤拷锟斤拷浔?炸锟斤拷锟?
			pvz->BombWallnut(IsDlgButtonChecked(hWnd, IDC_BOMBWALLNUT));
			break;
		case IDC_PLANTSZIPBOOM: //锟斤拷压锟斤拷炸
			pvz->PlantsZipBoom(IsDlgButtonChecked(hWnd, IDC_PLANTSZIPBOOM));
			break;
		case IDC_NO_SLEEP: /*蘑锟斤拷锟解唤锟斤拷*/
			pvz->NoSleep(IsDlgButtonChecked(hWnd, IDC_NO_SLEEP));
			break;
		case IDC_FIREDOU_OK: //锟姐豆锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟?
			pvz->FirePea(SendDlgItemMessage(hWnd, IDC_FIREDOULIST, CB_GETCURSEL, 0, 0), SendDlgItemMessage(hWnd, IDC_FIREICEDOULIST, CB_GETCURSEL, 0, 0));
			break;
		case IDC_MONEYFLOWER: //锟斤拷盏锟斤拷锟睫革拷
			pvz->MoneyFlowerChange(SendDlgItemMessage(hWnd, IDC_MONEYFLOWERLIST1, CB_GETCURSEL, 0, 0), SendDlgItemMessage(hWnd, IDC_MONEYFLOWERlist2, CB_GETCURSEL, 0, 0), GetDlgItemInt(hWnd, IDC_MONEYFLOWERNUM, NULL, TRUE));
			break;
		case IDC_FUNNYNUT: //锟斤拷锟斤拷锟斤拷锟?
			pvz->FunnyNut(IsDlgButtonChecked(hWnd, IDC_FUNNYNUT));
			break;
		case IDC_CRAZYPLANTS: //植锟斤拷怒锟斤拷
			pvz->CrazyPlants(IsDlgButtonChecked(hWnd, IDC_CRAZYPLANTS));
			break;
		case IDC_SETWOGUA: //锟斤拷锟较凤拷围
			pvz->SetWoGua(GetDlgItemInt(hWnd, IDC_SETWOGUANUM, NULL, TRUE));
			break;
		case IDC_KILLALLPLANTS: //杀锟斤拷全锟斤拷植锟斤拷
			pvz->KillAllPlants();
			break;
		case IDC_CHHITNUM: //锟斤拷锟斤拷锟剿猴拷
			pvz->ChHitNum(GetDlgItemInt(hWnd, IDC_CHHITNUMNUM, NULL, TRUE));
			break;
		case IDC_FRIENDLYGU: //锟斤拷锟斤拷锟饺伙拷
			pvz->MeiHuoHanBingGu(IsDlgButtonChecked(hWnd, IDC_FRIENDLYGU));
			break;
		case IDC_HUANGYOUGU: //锟斤拷锟酵癸拷
			pvz->HuangYouHanBingGu(IsDlgButtonChecked(hWnd, IDC_HUANGYOUGU));
			break;
		case IDC_SETROLEGARLIC: //植锟斤拷锟斤拷锟?
			pvz->SetPlantsRoleGarlic(IsDlgButtonChecked(hWnd, IDC_SETROLEGARLIC));
			break;
		case IDC_SETROLEFRIENDLY: //植锟斤拷锟饺伙拷
			pvz->SetPlantsRoleFriendly(IsDlgButtonChecked(hWnd, IDC_SETROLEFRIENDLY));
			break;
		case IDC_SETROLEICE: //植锟斤寒锟斤拷锟斤拷
			pvz->SetPlantsRoleIce(IsDlgButtonChecked(hWnd, IDC_SETROLEICE));
			break;
		case IDC_SETROLEWOGUA: //植锟斤拷锟窖癸拷
			pvz->SetPlantsRoleWoGua(IsDlgButtonChecked(hWnd, IDC_SETROLEWOGUA));
			break;
		case IDC_SETROLEBOOMMAX: //植锟斤拷锟斤拷锟?
			pvz->SetPlantsRoleBoomMax(IsDlgButtonChecked(hWnd, IDC_SETROLEBOOMMAX));
			break;
		case IDC_PLANTSALLRED: //植锟斤拷锟斤拷
			pvz->PlantsAllRed(IsDlgButtonChecked(hWnd, IDC_PLANTSALLRED));
			break;
		case IDC_PLANTSALLGREEN: //植锟斤拷锟斤拷
			pvz->PlantsAllGreen(IsDlgButtonChecked(hWnd, IDC_PLANTSALLGREEN));
			break;
		case IDC_PLANTSALLBLACK: //植锟斤拷锟斤拷
			pvz->PlantsAllBlack(IsDlgButtonChecked(hWnd, IDC_PLANTSALLBLACK));
			break;
		case IDC_SETROLERADISH: //锟戒保锟斤拷伞
			pvz->SetPlantsRoleRadish(IsDlgButtonChecked(hWnd, IDC_SETROLERADISH));
			break;
		case IDC_1111BULLET: //直锟斤拷锟接碉拷
			pvz->bulletStraight(IsDlgButtonChecked(hWnd, IDC_1111BULLET));
			break;
		case IDC_BAOLINGQIU: //锟斤拷锟斤拷锟斤拷锟斤拷锟?
			pvz->baolingqiu(IsDlgButtonChecked(hWnd, IDC_BAOLINGQIU));
			break;
		case IDC_STRONG_WIND: /*强锟斤拷锟斤拷叶锟斤拷*/
			pvz->StrongWind(IsDlgButtonChecked(hWnd, IDC_STRONG_WIND));
			break;
		case IDC_STRONG_BEAN: /*锟斤拷锟斤拷锟姐豆*/
			pvz->StrongBean(IsDlgButtonChecked(hWnd, IDC_STRONG_BEAN));
			break;
		case IDC_UMBRELLA: /*锟斤拷锟斤拷伞*/
			pvz->Umbrella(IsDlgButtonChecked(hWnd, IDC_UMBRELLA));
			break;
		case IDC_NO_CD: /*锟斤拷锟斤拷却*/
			pvz->NoCD(IsDlgButtonChecked(hWnd, IDC_NO_CD));
			break;
		case IDC_LOCK_SCOOP: /*锟斤拷锟斤拷锟斤拷锟斤拷*/
			pvz->LockScoop(IsDlgButtonChecked(hWnd, IDC_LOCK_SCOOP));
			break;
		case IDC_ANY_MOVE: /*锟斤拷石锟斤拷锟斤拷锟斤拷*/
			pvz->AnyMove(IsDlgButtonChecked(hWnd, IDC_ANY_MOVE));
			break;
		case IDC_NO_PURPLE: /*锟较匡拷锟斤拷锟斤拷锟斤拷*/
			pvz->NoPurple(IsDlgButtonChecked(hWnd, IDC_NO_PURPLE));
			break;
		case IDC_LOCK_BUTTER: /*锟斤拷锟斤拷锟斤拷锟斤拷*/
			CheckDlgButton(hWnd, IDC_LOCK_CORN, BST_UNCHECKED);
			pvz->LockButter(IsDlgButtonChecked(hWnd, IDC_LOCK_BUTTER));
			break;
		case IDC_LOCK_CORN: /*锟斤拷锟斤拷锟斤拷锟斤拷*/
			CheckDlgButton(hWnd, IDC_LOCK_BUTTER, BST_UNCHECKED);
			pvz->LockCorn(IsDlgButtonChecked(hWnd, IDC_LOCK_CORN));
			break;
		default:
			return FALSE;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK MoreProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// 锟斤拷锟斤拷锟剿碉拷选锟斤拷:
		switch (wmId)
		{
		case IDC_SPORESHOOT: //锟斤拷锟斤拷锟斤拷效
			pvz->SporeShoot(IsDlgButtonChecked(hWnd, IDC_SPORESHOOT));
			break;
		case IDC_LIGHTPLANTS: //植锟斤拷锟斤拷锟?
			pvz->LightPlants(IsDlgButtonChecked(hWnd, IDC_LIGHTPLANTS));
			break;
		case IDC_CANTSEEZOMS: //锟斤拷锟接斤拷尸
			pvz->CantSeeZoms(IsDlgButtonChecked(hWnd, IDC_CANTSEEZOMS));
			break;
		case IDC_INVSHOOT: //锟斤拷锟斤拷锟接碉拷
			pvz->InvShoot(IsDlgButtonChecked(hWnd, IDC_INVSHOOT));
			break;
		case IDC_SLOWSHOOT: //锟斤拷锟斤拷锟接碉拷
			pvz->SlowShoot(IsDlgButtonChecked(hWnd, IDC_SLOWSHOOT));
			break;
		case IDC_FASTSUN: //锟斤拷锟斤拷锟劫碉拷
			pvz->FastSun(IsDlgButtonChecked(hWnd, IDC_FASTSUN));
			break;
		case IDC_THISPULT: //原锟斤拷投锟斤拷
			pvz->ThisPult(IsDlgButtonChecked(hWnd, IDC_THISPULT));
			break;
		case IDC_FASTPULT: //瞬锟斤拷投锟斤拷
			pvz->FastPult(IsDlgButtonChecked(hWnd, IDC_FASTPULT));
			break;
		case IDC_FASTSQA: //锟窖瓜诧拷锟斤拷
			pvz->FastSqa(IsDlgButtonChecked(hWnd, IDC_FASTSQA));
			break;
		case IDC_FUNNYSQA: //锟斤拷锟斤拷锟窖癸拷
			pvz->FunnySqa(IsDlgButtonChecked(hWnd, IDC_FUNNYSQA));
			break;
		case IDC_JUMPINGSQA: //锟斤拷锟斤拷锟窖癸拷
			pvz->jumpingSqa(IsDlgButtonChecked(hWnd, IDC_JUMPINGSQA));
			break;
		case IDC_GRASSPLANT:
			pvz->GrassPlant(IsDlgButtonChecked(hWnd, IDC_GRASSPLANT));
			break;
		case IDC_INVBULL: //锟斤拷锟轿伙拷锟斤拷
			pvz->InvBull(IsDlgButtonChecked(hWnd, IDC_INVBULL));
			break;
		case IDC_FASTBUNGEE: //锟侥硷拷锟斤拷锟斤拷
			pvz->FastBungee(IsDlgButtonChecked(hWnd, IDC_FASTBUNGEE));
			break;
		case IDC_HITBELIGHT: //锟斤拷锟斤拷锟斤拷锟?
			pvz->HitBeLight(IsDlgButtonChecked(hWnd, IDC_HITBELIGHT));
			break;
		case IDC_HITNOLIGHT: //锟斤拷锟斤拷锟斤拷
			pvz->HitNoLight(IsDlgButtonChecked(hWnd, IDC_HITNOLIGHT));
			break;
		case IDC_NOBROKEN: //锟斤拷锟斤拷锟斤拷锟斤拷
			pvz->NoBroken(IsDlgButtonChecked(hWnd, IDC_NOBROKEN));
			break;
		case IDC_HITBROKEN: //锟斤拷锟斤拷锟斤拷锟?
			pvz->HitBroken(IsDlgButtonChecked(hWnd, IDC_HITBROKEN));
			break;
		case IDC_DEADNOHEAD: //锟斤拷锟斤拷锟斤拷头
			pvz->DeadNoHead(IsDlgButtonChecked(hWnd, IDC_DEADNOHEAD));
			break;
		case IDC_VOIDEAT: //锟斤拷食锟斤拷止
			pvz->VoidEat(IsDlgButtonChecked(hWnd, IDC_VOIDEAT));
			break;
		case IDC_VOIDWALK: //原锟斤拷踏锟斤拷
			pvz->VoidWalk(IsDlgButtonChecked(hWnd, IDC_VOIDWALK));
			break;
		case IDC_LONGEAT: //锟斤拷锟斤拷止
			pvz->LongEat(IsDlgButtonChecked(hWnd, IDC_LONGEAT));
			break;
		case IDC_LJNORMALZ: //锟斤拷锟斤拷锟秸斤拷
			pvz->LJNormalZ(IsDlgButtonChecked(hWnd, IDC_LJNORMALZ));
			break;
		case IDC_FAGUOZOM: //锟斤拷锟斤拷锟斤拷尸
			pvz->FaGuoZom(IsDlgButtonChecked(hWnd, IDC_FAGUOZOM));
			break;
		case IDC_PROJECTILESHOOTER: //锟接碉拷锟斤拷锟斤拷锟斤拷
			pluginsopener("ProjectileShooter.exe");
			break;
		case IDC_GAMELISTENER1: //锟斤拷戏锟斤拷锟斤拷锟斤拷
			pluginsopener("listener.exe");
			break;
		default:
			return FALSE;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK ZombiesProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// 锟斤拷锟斤拷锟剿碉拷选锟斤拷:
		switch (wmId)
		{
		case IDC_BOOM_IM: /*锟斤拷锟教憋拷炸*/
			pvz->BoomIm();
			break;
		case IDC_BOOM_NORMAL:
			pvz->BoomNormal();
			break;
		case IDC_BOOM_NEVER:
			pvz->BoomNever();
			break;
		case IDC_VISIABLE_NO: /*锟斤拷锟斤拷*/
			pvz->VisiableNo();
			break;
		case IDC_VISIABLE_NORMAL:
			pvz->VisiableNormal();
			break;
		case IDC_VISIABLE_YES:
			pvz->VisiableYes();
			break;
		case IDC_ZSTRONG: /*锟??碉拷*/
			pvz->ZStrong();
			break;
		case IDC_ZNORMAL:
			pvz->ZNormal();
			break;
		case IDC_ZWEAK:
			pvz->ZWeak();
			break;
		case IDC_NO_SLOW: /*锟斤拷锟劫匡拷锟斤拷*/
			pvz->NoSlow(IsDlgButtonChecked(hWnd, IDC_NO_SLOW));
			break;
		case IDC_NO_BUTTER: /*锟斤拷锟斤拷*/
			pvz->NoButter(IsDlgButtonChecked(hWnd, IDC_NO_BUTTER));
			break;
		case IDC_NO3Z_GROUP: /*锟斤拷锟斤拷3锟斤拷锟斤拷*/
			pvz->No3zGroup(IsDlgButtonChecked(hWnd, IDC_NO3Z_GROUP));
			break;
		case IDC_JUMPZOMMAX: //锟脚革拷锟斤拷锟斤拷锟斤拷
			pvz->JumpZomMax(IsDlgButtonChecked(hWnd, IDC_JUMPZOMMAX));
			break;
		case IDC_PAPERNOANGRY: //锟斤拷纸息怒
			pvz->PaperNoAngry(IsDlgButtonChecked(hWnd, IDC_PAPERNOANGRY));
			break;
		case IDC_FASTSPEED: //锟??度加匡拷
			pvz->FastSpeed(IsDlgButtonChecked(hWnd, IDC_FASTSPEED));
			break;
		case IDC_NOSEEPLANTS: //锟斤拷锟斤拷
			pvz->NoSeePlants(IsDlgButtonChecked(hWnd, IDC_NOSEEPLANTS));
			break;
		case IDC_SHITSANYE: //锟斤拷锟斤拷锟斤拷叶
			pvz->BuPaSanYe(IsDlgButtonChecked(hWnd, IDC_SHITSANYE));
			break;
		case IDC_COUNTERMARCH: //锟斤拷锟斤拷锟斤拷锟?
			pvz->ConterMarch(IsDlgButtonChecked(hWnd, IDC_COUNTERMARCH));
			break;
		case IDC_DANCERFUNNY: //锟斤拷锟斤拷锟斤拷路
			pvz->DancerFunny(IsDlgButtonChecked(hWnd, IDC_DANCERFUNNY));
			break;
		case IDC_ALIENZOM: //锟斤拷锟斤拷锟斤拷
			pvz->AlienZombies(IsDlgButtonChecked(hWnd, IDC_ALIENZOM));
			break;
		case IDC_FUCKFASTER: //锟斤拷尸直锟接斤拷锟斤拷
			pvz->FuckFaster(IsDlgButtonChecked(hWnd, IDC_FUCKFASTER));
			break;
		case IDC_BIAOBAZOM: //锟斤拷薪锟绞?
			pvz->BiaoBaZom(IsDlgButtonChecked(hWnd, IDC_BIAOBAZOM));
			break;
		case IDC_ZLIFE: //锟斤拷尸血锟斤拷
			pvz->ZLife(SendDlgItemMessage(hWnd, IDC_ZLIFELIST, CB_GETCURSEL, 0, 0), GetDlgItemInt(hWnd, IDC_ZLIFENUM, NULL, TRUE));
			break;
		case IDC_ZALIFE: //锟斤拷尸锟斤拷品血锟斤拷
			pvz->ZALife(SendDlgItemMessage(hWnd, IDC_ZALIFELIST, CB_GETCURSEL, 0, 0), GetDlgItemInt(hWnd, IDC_ZALIFENUM, NULL, TRUE));
			break;
		case IDC_GRAVESPAWNZCD: //锟斤拷尸锟斤拷锟斤拷时锟斤拷
			pvz->GraveSpawnZCD(GetDlgItemInt(hWnd, IDC_GRAVESPAWNZCDNUM, NULL, TRUE));
			break;
		case IDC_GRAVESPAWNZCT: //锟斤拷尸锟斤拷锟斤拷锟斤拷锟斤拷
			pvz->GraveSpawnZCT(GetDlgItemInt(hWnd, IDC_GRAVESPAWNZCTNUM, NULL, TRUE));
			break;
		case IDC_GRAVESPAWNZSP: //锟斤拷锟街斤拷尸锟??讹拷
			pvz->GraveSpawnZSP(GetDlgItemInt(hWnd, IDC_GRAVESPAWNZSPNUM, NULL, TRUE));
			break;
		case IDC_GRAVESPAWNCT: //墓锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
			pvz->GraveSpawnCT(GetDlgItemInt(hWnd, IDC_GRAVESPAWNCTNUM, NULL, TRUE));
			break;
		case IDC_ZHIT: //锟斤拷尸锟剿猴拷
			pvz->ZHit(SendDlgItemMessage(hWnd, IDC_ZHITLIST, CB_GETCURSEL, 0, 0), GetDlgItemInt(hWnd, IDC_ZHITNUM, NULL, TRUE));
			break;
		case IDC_GAGANGBURENGGUI: //锟斤拷锟斤拷小锟斤拷
			pvz->GaGangBuReng(IsDlgButtonChecked(hWnd, IDC_GAGANGBURENGGUI));
			break;
		case IDC_FASTGETPLANT: //锟侥硷拷锟斤拷偷
			pvz->FastGetPlant(IsDlgButtonChecked(hWnd, IDC_FASTGETPLANT));
			break;
		case IDC_BUNGEESTOP: //锟侥硷拷锟斤拷锟斤拷
			pvz->BungeeStop(IsDlgButtonChecked(hWnd, IDC_BUNGEESTOP));
			break;
		case IDC_BUNGEEFUNNY: //锟侥硷拷锟斤拷锟斤拷
			pvz->BungeeFunny(IsDlgButtonChecked(hWnd, IDC_BUNGEEFUNNY));
			break;
		case IDC_OKRENGIMP: //直锟斤拷锟接癸拷
			pvz->OKRengIMP(IsDlgButtonChecked(hWnd, IDC_OKRENGIMP));
			break;
		case IDC_HITRENGIMP: //锟斤拷锟剿硷拷锟斤拷
			pvz->FastBigZom(IsDlgButtonChecked(hWnd, IDC_HITRENGIMP));
			break;
		case IDC_IMPFALLDEAD: //小锟斤拷摔锟斤拷
			pvz->IMPFallDie(IsDlgButtonChecked(hWnd, IDC_IMPFALLDEAD));
			break;
		case IDC_EATHOUSE: //锟斤拷锟斤拷锟斤拷锟斤拷
			pvz->EatHouse(IsDlgButtonChecked(hWnd, IDC_EATHOUSE));
			break;
		case IDC_FASTSPEEDMAX: //锟劫度革拷锟斤拷
			pvz->FastSpeedMax(IsDlgButtonChecked(hWnd, IDC_FASTSPEEDMAX));
			break;
		case IDC_NO_IMP: /*锟斤拷锟斤拷小锟斤拷*/
			pvz->NoIMP(IsDlgButtonChecked(hWnd, IDC_NO_IMP));
			break;
		case IDC_NO_ICE: /*锟斤拷锟斤拷锟??猴拷*/
			pvz->NoICE(IsDlgButtonChecked(hWnd, IDC_NO_ICE));
			break;
		case IDC_EATABLE: /*锟斤拷锟剿可憋拷锟斤拷*/
			pvz->ZEatable(IsDlgButtonChecked(hWnd, IDC_EATABLE));
			break;
		case IDC_STOP_ZTIMER: /*锟斤拷停刷锟斤拷尸*/
			pvz->StopZTimer(IsDlgButtonChecked(hWnd, IDC_STOP_ZTIMER));
			break;
		case IDC_STOP_ZOMBIES: /*锟斤拷尸锟斤拷前锟斤拷*/
			pvz->StopZombies(IsDlgButtonChecked(hWnd, IDC_STOP_ZOMBIES));
			break;
		case IDC_STOP_BOSS: /*锟斤拷BOSS*/
			pvz->StopBoss(IsDlgButtonChecked(hWnd, IDC_STOP_BOSS));
			break;
		case IDC_BALLOON_BOOM: /*锟斤拷锟斤拷锟皆憋拷*/
			pvz->BalloonBoom(IsDlgButtonChecked(hWnd, IDC_BALLOON_BOOM));
			break;
		case IDC_FUCKINGPEAZOMBIEDAMAGETYPE: //锟斤拷枪锟斤拷尸锟斤拷锟斤拷锟斤拷式
			pvz->FuckingZombieDamageType(SendDlgItemMessage(hWnd, IDC_FUCKINGPEAZOMBIEDAMAGETYPELIST, CB_GETCURSEL, 0, 0));
			break;
		case IDC_PEAZOMBIEDAMAGETYPE: //锟姐豆锟斤拷尸锟斤拷锟斤拷锟斤拷式
			pvz->PeaZombieDamageType(SendDlgItemMessage(hWnd, IDC_PEAZOMBIEDAMAGETYPELIST, CB_GETCURSEL, 0, 0));
			break;
		case IDC_ZTIMER_SPEEDUP: /*锟斤拷锟斤拷刷锟斤拷尸*/
			if (IsDlgButtonChecked(hWnd, IDC_ZTIMER_SPEEDUP))
				pvz->ZTimerSpeed(400 - SendMessage(GetDlgItem(hWnd, IDC_SLIDER_TIMER), TBM_GETPOS, 0, 0));
			else
				pvz->ZTimerSpeed(-1);
			break;
		case IDC_GATHER_ZOMBIE: /*锟斤拷锟斤拷*/
			pvz->GatherZombie(IsDlgButtonChecked(hWnd, IDC_GATHER_ZOMBIE),
				(float)SendMessage(GetDlgItem(hWnd, IDC_SLIDER_GATHER), TBM_GETPOS, 0, 0));
			break;
		case IDC_KILL_ALLZ: /*锟斤拷杀锟斤拷尸*/
			pvz->KillAllZombies();
			break;
		case IDC_BLACK_ALL: //锟斤拷诮锟绞?
			pvz->BlackAllZombies();
			break;
		case IDC_VOID_ALL: //莫锟斤拷锟斤拷失
			pvz->VoidAllZombies();
			break;
		case IDC_BOSSLIFE: //BOSS血锟斤拷
			pvz->BossLife(GetDlgItemInt(hWnd, IDC_BOSSLIFENUM, NULL, TRUE));
			break;
		case IDC_BOSSLIFE_LOCK: //锟斤拷锟斤拷BOSS血锟斤拷
			if (IsDlgButtonChecked(hWnd, IDC_BOSSLIFE_LOCK) == true)
			{
				SetTimer(hWnd, 5, 50, (TIMERPROC)LockBossLifeTimer);
			}
			else
			{
				KillTimer(hWnd, 5);
				return 0;
			}
			break;
		case IDC_SETZOMBIETIMER: //锟脚斤拷尸锟斤拷锟斤拷时
			pvz->SetZombieTimer(GetDlgItemInt(hWnd, IDC_SETZOMBIETIMERNUM, NULL, TRUE));
			break;
		case IDC_SETZOMBIETIMER_LOCK: //锟斤拷锟斤拷锟脚斤拷尸锟斤拷锟斤拷时
			if (IsDlgButtonChecked(hWnd, IDC_SETZOMBIETIMER_LOCK) == true)
			{
				SetTimer(hWnd, 6, 50, (TIMERPROC)SetZombieTimerTimer);
			}
			else
			{
				KillTimer(hWnd, 6);
				return 0;
			}
			break;
		case IDC_SHOWHEADTIMER: //锟斤拷头锟斤拷锟斤拷时
			pvz->ShowHeadTimer(GetDlgItemInt(hWnd, IDC_SHOWHEADTIMERNUM, NULL, TRUE));
			break;
		case IDC_SHOWHEADTIMER_LOCK: //锟斤拷锟斤拷锟斤拷头锟斤拷锟斤拷时
			if (IsDlgButtonChecked(hWnd, IDC_SHOWHEADTIMER_LOCK == true))
			{
				SetTimer(hWnd, 7, 50, (TIMERPROC)ShowHeadTimerTimer);
			}
			else
			{
				KillTimer(hWnd, 7);
					return 0;
			}
		case IDC_CONFUSE_ALL:/*魅惑僵尸*/
			pvz->ConfuseZombies();
				break;
		default:
			return FALSE;
		}
		break;
	case WM_HSCROLL:
		if (lParam == (LPARAM)GetDlgItem(hWnd, IDC_SLIDER_TIMER)
			&& IsDlgButtonChecked(hWnd, IDC_ZTIMER_SPEEDUP))
		{
			SendMessage(hWnd, WM_COMMAND, IDC_ZTIMER_SPEEDUP, 0);
		}
		else if (lParam == (LPARAM)GetDlgItem(hWnd, IDC_SLIDER_GATHER)
			&& IsDlgButtonChecked(hWnd, IDC_GATHER_ZOMBIE))
		{
			SendMessage(hWnd, WM_COMMAND, IDC_GATHER_ZOMBIE, 0);
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK SceneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// 锟斤拷锟斤拷锟剿碉拷选锟斤拷:
		switch (wmId)
		{

		case IDC_ROWTYPE: /*锟斤拷锟斤拷锟叫讹拷*/
		{
			int row = SendDlgItemMessage(hWnd, IDC_NLIST, CB_GETCURSEL, 0, 0);
			int type = SendDlgItemMessage(hWnd, IDC_RLIST, CB_GETCURSEL, 0, 0);
			pvz->SetRowType(row, type);
		}

		case IDC_SCENEOK1: /*锟??改筹拷锟斤拷*/
		{
			int back = SendDlgItemMessage(hWnd, IDC_SCENELIST, CB_GETCURSEL, 0, 0);
			pvz->SetBackground(back);
			break;
		}

		case IDC_START_CAR: /*锟斤拷锟斤拷小锟狡筹拷*/
			pvz->StartCar();
			break;
		case IDC_RESET_CAR: /*锟街革拷小锟狡筹拷*/
			pvz->ResetCar();
			break;
		case IDC_LOCKCAR: /*小锟狡筹拷锟斤拷锟斤拷锟斤拷效*/
			pvz->LockCar(IsDlgButtonChecked(hWnd, IDC_LOCKCAR));
			break;
		case IDC_NoCar: /*锟斤拷锟斤拷锟斤拷锟狡筹拷*/
			pvz->NoCar(IsDlgButtonChecked(hWnd, IDC_NoCar));
			break;

		default:
			return FALSE;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK SeedProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// 锟斤拷锟斤拷锟剿碉拷选锟斤拷:
		switch (wmId)
		{
		case IDC_ADD_LIST:
		{
			char zname[10];
			GetDlgItemText(hWnd, IDC_SLIST, zname, 10);
			if (SendDlgItemMessage(hWnd, IDC_SLIST_BOX, LB_FINDSTRING, -1, LPARAM(zname)) == LB_ERR)
			{
				SendDlgItemMessage(hWnd, IDC_SLIST_BOX, LB_ADDSTRING, 0, LPARAM(zname));
			}
			break;
		}
		case IDC_DEL_SLIST:
			SendDlgItemMessage(hWnd, IDC_SLIST_BOX, LB_DELETESTRING,
							   SendDlgItemMessage(hWnd, IDC_SLIST_BOX, LB_GETCURSEL, 0, 0), 0);
			break;
		case IDC_CLEAR_SLIST:
			SendDlgItemMessage(hWnd, IDC_SLIST_BOX, LB_RESETCONTENT, 0, 0);
			break;
		case IDC_HELP_SEED:
			MessageBox(hWnd,
				"暂无说明！\n",
				"提示 2333", MB_OK);
			break;
		case IDC_CHG_SEED:
		{
			char zname[10];
			int zombies[sizeof(zList) / sizeof(*zList)] = {0};
			int znum = SendDlgItemMessage(hWnd, IDC_SLIST_BOX, LB_GETCOUNT, 0, 0);
			if (znum == 0)
				break;
			for (int i = 0; i < znum; ++i)
			{
				SendDlgItemMessage(hWnd, IDC_SLIST_BOX, LB_GETTEXT, i, LPARAM(zname));
				zombies[i] = SendDlgItemMessage(hWnd, IDC_SLIST, CB_FINDSTRING, -1, LPARAM(zname));
			}
			if (IsDlgButtonChecked(hWnd, IDC_NATURAL))
			{
				pvz->NaturalSeed(zombies, znum);
			}
			else
			{
				if (znum == 2 &&
					(zombies[0] == 20 && zombies[1] == 32 || zombies[0] == 32 && zombies[1] == 20))
					CheckDlgButton(hWnd, IDC_RED_LIMIT, BST_UNCHECKED);
				pvz->LimitSeed(zombies, znum, IsDlgButtonChecked(hWnd, IDC_THIEF_LIMIT), IsDlgButtonChecked(hWnd, IDC_RED_LIMIT));
			}
			break;
		}
		case IDC_RESET_SEED: /*锟斤拷锟斤拷锟??改筹拷锟斤拷*/
			pvz->ResetSeed();
			break;
		case IDC_ZLEFT:
		{
			bool zombies[33] = {0};
			pvz->SeeLeftZombies(zombies);
			char str[300];
			char temp[10];
			str[0] = '\0';
			int j = 0;
			for (int i = 0; i < 33; ++i)
			{
				if (zombies[i])
				{
					sprintf(temp, "%d.%s\n", ++j, zList[i]);
					strcat(str, temp);
				}
			}
			if (str[0] != '\0')
				MessageBox(hWnd, str, "剩余出怪种类", MB_OK);
			break;
		}
		default:
			return FALSE;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK GaGangTeErProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if (pvz == NULL)
			return 0;
		// 锟斤拷锟斤拷锟剿碉拷选锟斤拷:
		switch (wmId)
		{
		case IDC_HIGHIMP: //锟斤拷锟斤拷锟接癸拷
			pvz->HighIMP(IsDlgButtonChecked(hWnd, IDC_HIGHIMP));
			break;
		case IDC_LONGIMP: //小锟斤拷锟斤拷远
			pvz->LongIMP(IsDlgButtonChecked(hWnd, IDC_LONGIMP));
			break;
		case IDC_SHITIMP: //锟斤拷锟斤拷锟接癸拷
			pvz->ShitIMP(IsDlgButtonChecked(hWnd, IDC_SHITIMP));
			break;
		case IDC_VOIDIMP: //原锟斤拷锟接癸拷
			pvz->VoidIMP(IsDlgButtonChecked(hWnd, IDC_VOIDIMP));
			break;
		case IDC_HOMEIMP: //小锟斤拷锟斤拷路
			pvz->HomeIMP(IsDlgButtonChecked(hWnd, IDC_HOMEIMP));
			break;
		case IDC_FASTGAR: //锟斤拷锟斤拷锟斤拷锟斤拷
			pvz->FastGar(IsDlgButtonChecked(hWnd, IDC_FASTGAR));
			break;
		case IDC_STUCKIMP://卡顿小鬼
			pvz->StuckIMP(IsDlgButtonChecked(hWnd, IDC_STUCKIMP));
			break;
		case IDC_STANDSMASH://垂直锤击
			pvz->StandSmash(IsDlgButtonChecked(hWnd, IDC_STANDSMASH));
			break;
		case IDC_STRAIGHTSMASH://横线锤击
			pvz->StraightSmash(IsDlgButtonChecked(hWnd, IDC_STRAIGHTSMASH));
			break;
		case IDC_FULLSMASH://全屏锤击
			pvz->FullSmash(IsDlgButtonChecked(hWnd, IDC_FULLSMASH));
			break;
		}
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK FullScreenProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if (pvz == NULL)
			return 0;
		// 锟斤拷锟斤拷锟剿碉拷选锟斤拷:
		switch (wmId)
		{
		case IDC_FSBOOM: /*锟揭斤拷全锟斤拷*/
			pvz->FSBoom(IsDlgButtonChecked(hWnd, IDC_FSBOOM));
			break;
		case IDC_FSSQUASH: /*锟窖癸拷全锟斤拷*/
			pvz->FSSquash(IsDlgButtonChecked(hWnd, IDC_FSSQUASH));
			break;
		case IDC_FSMAGNET: /*锟斤拷锟斤拷锟斤拷全锟斤拷*/
			pvz->FSMagnet(IsDlgButtonChecked(hWnd, IDC_FSMAGNET));
			break;
		case IDC_FSSPUTTER: /*锟斤拷锟斤拷全锟斤拷*/
			pvz->FSSputter(IsDlgButtonChecked(hWnd, IDC_FSSPUTTER));
			break;
		case IDC_FSMOUSE: /*锟斤拷锟届花全锟斤拷*/
			pvz->FSMouth(IsDlgButtonChecked(hWnd, IDC_FSMOUSE));
			break;
		case IDC_FSPRICK: /*锟截达拷全锟斤拷*/
			pvz->FSPrick(IsDlgButtonChecked(hWnd, IDC_FSPRICK));
			break;
		case IDC_FSSPOUT: /*锟斤拷锟斤拷全锟斤拷*/
			pvz->FSSpout(IsDlgButtonChecked(hWnd, IDC_FSSPOUT));
			break;
		case IDC_FSCAT: /*猫式全锟斤拷*/
			pvz->FSCat(IsDlgButtonChecked(hWnd, IDC_FSCAT));
			break;
		case IDC_CATTOUCH: /*锟斤拷锟斤拷锟剿猴拷*/
			pvz->CatTouch(IsDlgButtonChecked(hWnd, IDC_CATTOUCH));
			break;
		default:
			return FALSE;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK GardenProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// 锟斤拷锟斤拷锟剿碉拷选锟斤拷:
		switch (wmId)
		{
		case IDC_FLOWERNPK:
			pvz->FlowerNPK(IsDlgButtonChecked(hWnd, IDC_FLOWERNPK));
			break;
		case IDC_MEDICINE:
			pvz->Medicine(IsDlgButtonChecked(hWnd, IDC_MEDICINE));
			break;
		case IDC_CHOCOLATE:
			pvz->Chocolate(IsDlgButtonChecked(hWnd, IDC_CHOCOLATE));
			break;
		case IDC_TREENPK:
			pvz->TreeNPK(IsDlgButtonChecked(hWnd, IDC_TREENPK));
			break;
		case IDC_TREE_HIGH:
			pvz->TreeHeight(GetDlgItemInt(hWnd, IDC_TREE_HEIGHT, NULL, TRUE));
			break;
		case IDC_FLOWER_NUMBER:
			pvz->FlowerNum(GetDlgItemInt(hWnd, IDC_FLOWER_NUM, NULL, TRUE));
			break;
		case IDC_CHG_FLOWER:
			pvz->ChangeFlower(GetDlgItemInt(hWnd, IDC_FLOWER_ID, NULL, TRUE),
							  SendDlgItemMessage(hWnd, IDC_FLOWER_LIST, CB_GETCURSEL, 0, 0));
			break;
		case IDC_CHG_FSIZE:
			pvz->ChangeFSize(GetDlgItemInt(hWnd, IDC_FLOWER_ID, NULL, TRUE),
							 SendDlgItemMessage(hWnd, IDC_FLOWER_SIZE, CB_GETCURSEL, 0, 0));
			break;
		case IDC_F_LEFT:
			pvz->ChangeFDir(GetDlgItemInt(hWnd, IDC_FLOWER_ID, NULL, TRUE), 1);
			break;
		case IDC_F_RIGHT:
			pvz->ChangeFDir(GetDlgItemInt(hWnd, IDC_FLOWER_ID, NULL, TRUE), 0);
			break;
		case IDC_CHG_FPLACE:
			pvz->ChangeFPlace(GetDlgItemInt(hWnd, IDC_FLOWER_ID, NULL, TRUE),
							  SendDlgItemMessage(hWnd, IDC_PLACE_LIST, CB_GETCURSEL, 0, 0));
			break;
		default:
			return FALSE;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

INT_PTR CALLBACK ThanksProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// 锟斤拷锟斤拷锟剿碉拷选锟斤拷:
		switch (wmId)
		{
		default:
			return FALSE;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}