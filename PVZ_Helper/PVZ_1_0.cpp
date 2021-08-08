#include "stdafx.h"
#include "PVZ_1_0.h"
#include "resource.h"

#define DATA_ADDR 0x006a9ec0
#define OFFSET_1 0x768
#define OFFSET_2 0x160
#define MODE_OFFSET 0x7f8
#define GARDON_OFFSET 0x82c
void PVZ_1_0::RunAsm()
{
	if (getLength() > 0)
	{
		WriteMemory(-2, 1, 0x00552014);
		Sleep(10);
		ret();
		runThread(GetHandle(), eCode.Thread);
		WriteMemory(0xdb, 1, 0x00552014);
	}
}
void PVZ_1_0::GetPlants()
{
	vp.clear();
	Plant one;
	one.addr = ReadMemory(4, DATA_ADDR, 2, OFFSET_1, 0xac);
	int pnum = ReadMemory(4, DATA_ADDR, 2, OFFSET_1, 0xbc);
	for (int i = 0; i < pnum; one.addr += 0x14c)
	{
		if (ReadMemory(1, one.addr + 0x141) == 0)
		{
			one.Row = ReadMemory(4, one.addr + 0x1c);
			one.Col = ReadMemory(4, one.addr + 0x28);
			one.Type = ReadMemory(4, one.addr + 0x24);
			one.Sleeping = ReadMemory(1, one.addr + 0x143) == 1;
			vp.push_back(one);
			++i;
		}
	}
}
void PVZ_1_0::GetItems()
{
	vi.clear();
	Item one;
	one.addr = ReadMemory(4, DATA_ADDR, 2, OFFSET_1, 0x11c);
	int inum = ReadMemory(4, DATA_ADDR, 2, OFFSET_1, 0x12c);
	for (int i = 0; i < inum; one.addr += 0xec)
	{
		if (ReadMemory(1, one.addr + 0x20) == 0)
		{
			one.Row = ReadMemory(4, one.addr + 0x14);
			one.Col = ReadMemory(4, one.addr + 0x10);
			one.Type = ReadMemory(4, one.addr + 8);
			vi.push_back(one);
			++i;
		}
	}
}
void PVZ_1_0::GetCars()
{
	vc.clear();
	Car one;
	one.addr = ReadMemory(4, DATA_ADDR, 2, OFFSET_1, 0x100);
	int cnum = ReadMemory(4, DATA_ADDR, 2, OFFSET_1, 0x110);
	for (int i = 0; i < cnum; one.addr += 0x48)
	{
		if (ReadMemory(1, one.addr + 0x30) == 0)
		{
			one.Row = ReadMemory(4, one.addr + 0x14);
			vc.push_back(one);
			++i;
		}
	}
}
void PVZ_1_0::GetZombies()
{
	vz.clear();
	Zombie one;
	one.addr = ReadMemory(4, DATA_ADDR, 2, OFFSET_1, 0x90);
	int znum = ReadMemory(4, DATA_ADDR, 2, OFFSET_1, 0xa0);
	for (int i = 0; i < znum; one.addr += 0x15c)
	{
		if (ReadMemory(1, one.addr + 0xec) == 0)
		{
			one.Row = ReadMemory(4, one.addr + 0x1c);
			one.Type = ReadMemory(4, one.addr + 0x24);
			vz.push_back(one);
			++i;
		}
	}
}
int PVZ_1_0::GetMapType()
{
	return ReadMemory(4, DATA_ADDR, 2, OFFSET_1, 0x554c);
}
int PVZ_1_0::GetBlockType(int row, int col)/*1.草地2.裸地3.水池*/
{
	return ReadMemory(4, DATA_ADDR, 2, OFFSET_1, 0x168 + row * 4 + col * 24);
}
void PVZ_1_0::SetBlockType(int row, int col, int type)/*1.草地2.裸地3.水池*/
{
	WriteMemory(type, 4, DATA_ADDR, 2, OFFSET_1, 0x168 + row * 4 + col * 24);
}
int PVZ_1_0::GetRowType(int row)/*0.不出怪1.草地2.水路*/
{
	return ReadMemory(4, DATA_ADDR, 2, OFFSET_1, 0x5d8 + row * 4);
}
void PVZ_1_0::SetRowType(int row, int type)/*0.不出怪1.草地2.水路*/
{
	WriteMemory(type, 4, DATA_ADDR, 2, OFFSET_1, 0x5d8 + row * 4);
}
bool PVZ_1_0::InGame()
{
	return ReadMemory(4, DATA_ADDR, 1, OFFSET_1) != 0;
}

int PVZ_1_0::GetMode()
{
	return ReadMemory(4, DATA_ADDR, 1, MODE_OFFSET);
}

void PVZ_1_0::SetSun(int sun)
{
	WriteMemory(sun, 4, DATA_ADDR, 2, OFFSET_1, 0x5560);
}

void PVZ_1_0::SetBackground(int back)
{
	WriteMemory(back, 4, DATA_ADDR, 2, OFFSET_1, 0x554C);
}

void PVZ_1_0::LockCar(bool b)
{
	if (b)
	{
		WriteMemory(0xC3, 1, 0x000458DA0);
		WriteMemory(0x90, 1, 0x000458DA1);
		WriteMemory(0x90, 1, 0x000458DA2);
	}
	else
	{
		WriteMemory(0x83, 1, 0x000458DA0);
		WriteMemory(0xEC, 1, 0x000458DA1);
		WriteMemory(0x08, 1, 0x000458DA2);
	}
}

void PVZ_1_0::Hammering(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x004538A2);
		WriteMemory(0xEB, 1, 0x004222B1);
	}
	else
	{
		WriteMemory(0x75, 1, 0x004538A2);
		WriteMemory(0x74, 1, 0x004222B1);
	}
}

void PVZ_1_0::AlienZombies(bool b)
{
	if (b)
	{
		WriteMemory(0x90, 1, 0x0052AFC7);
		WriteMemory(0x90, 1, 0x0052AFC8);
		WriteMemory(0x90, 1, 0x0052AFC9);
	}
	else
	{
		WriteMemory(0xD9, 1, 0x0052AFC7);
		WriteMemory(0x46, 1, 0x0052AFC8);
		WriteMemory(0x30, 1, 0x0052AFC9);
	}
}

void PVZ_1_0::FuckFaster(bool b)
{
	if (b)
	{
		WriteMemory(0x90, 1, 0x0052AFBF);
		WriteMemory(0x90, 1, 0x0052AFC0);
		WriteMemory(0x90, 1, 0x0052AFC1);
	}
	else
	{
		WriteMemory(0xD9, 1, 0x0052AFBF);
		WriteMemory(0x46, 1, 0x0052AFC0);
		WriteMemory(0x2C, 1, 0x0052AFC1);
	}
}

void PVZ_1_0::EatHouse(bool b)
{
	if (b)
	{
		WriteMemory(0x90, 1, 0x0052E7E9);
		WriteMemory(0x90, 1, 0x0052E7EA);
		WriteMemory(0x90, 1, 0x0052E7EB);
	}
	else
	{
		WriteMemory(0x8D, 1, 0x0052E7E9);
		WriteMemory(0x04, 1, 0x0052E7EA);
		WriteMemory(0x1F, 1, 0x0052E7EB);
	}
}

void PVZ_1_0::SetPlantsRoleFriendly(bool b)
{
	if (b)
	{
		WriteMemory(0xC7, 1, 0x0045DC49);
		WriteMemory(0x43, 1, 0x0045DC4A);
		WriteMemory(0x24, 1, 0x0045DC4B);
		WriteMemory(0x0C, 1, 0x0045DC4C);
		WriteMemory(0x00, 1, 0x0045DC4D);
		WriteMemory(0x00, 1, 0x0045DC4E);
		WriteMemory(0x00, 1, 0x0045DC4F);
		WriteMemory(0x90, 1, 0x0045DC50);
		WriteMemory(0x90, 1, 0x0045DC51);
	}
	else
	{
		WriteMemory(0x89, 1, 0x0045DC49);
		WriteMemory(0x73, 1, 0x0045DC4A);
		WriteMemory(0x24, 1, 0x0045DC4B);
		WriteMemory(0x89, 1, 0x0045DC4C);
		WriteMemory(0x93, 1, 0x0045DC4D);
		WriteMemory(0x38, 1, 0x0045DC4E);
		WriteMemory(0x01, 1, 0x0045DC4F);
		WriteMemory(0x00, 1, 0x0045DC50);
		WriteMemory(0x00, 1, 0x0045DC51);
	}
}

void PVZ_1_0::SetPlantsRoleIce(bool b)
{
	if (b)
	{
		WriteMemory(0xC7, 1, 0x0045DC49);
		WriteMemory(0x43, 1, 0x0045DC4A);
		WriteMemory(0x24, 1, 0x0045DC4B);
		WriteMemory(0x0E, 1, 0x0045DC4C);
		WriteMemory(0x00, 1, 0x0045DC4D);
		WriteMemory(0x00, 1, 0x0045DC4E);
		WriteMemory(0x00, 1, 0x0045DC4F);
		WriteMemory(0x90, 1, 0x0045DC50);
		WriteMemory(0x90, 1, 0x0045DC51);
	}
	else
	{
		WriteMemory(0xC7, 1, 0x0045DC49);
		WriteMemory(0x43, 1, 0x0045DC4A);
		WriteMemory(0x24, 1, 0x0045DC4B);
		WriteMemory(0x0C, 1, 0x0045DC4C);
		WriteMemory(0x00, 1, 0x0045DC4D);
		WriteMemory(0x00, 1, 0x0045DC4E);
		WriteMemory(0x00, 1, 0x0045DC4F);
		WriteMemory(0x90, 1, 0x0045DC50);
		WriteMemory(0x90, 1, 0x0045DC51);
	}
}

void PVZ_1_0::MaxSun(int sun)
{
	WriteMemory(sun, 4, 0x00430A1F);
	WriteMemory(sun, 4, 0x00430A2B);
}

void PVZ_1_0::MaxMoney(int money)
{
	WriteMemory(money, 4, 0x00430A7D);
	WriteMemory(money, 4, 0x00430A74);
}

void PVZ_1_0::TheWorld(bool b)
{
	if (b)
	{
		WriteMemory(0xC3, 1, 0x004130D0);
		WriteMemory(0x90, 1, 0x004130D1);
		WriteMemory(0x90, 1, 0x004130D2);
	}
	else
	{
		WriteMemory(0x83, 1, 0x004130D0);
		WriteMemory(0xEC, 1, 0x004130D1);
		WriteMemory(0x08, 1, 0x004130D2);
	}
}

void PVZ_1_0::SetPlantsRoleBoomMax(bool b)
{
	if (b)
	{
		WriteMemory(0xC7, 1, 0x0045DC49);
		WriteMemory(0x43, 1, 0x0045DC4A);
		WriteMemory(0x24, 1, 0x0045DC4B);
		WriteMemory(0x0F, 1, 0x0045DC4C);
		WriteMemory(0x00, 1, 0x0045DC4D);
		WriteMemory(0x00, 1, 0x0045DC4E);
		WriteMemory(0x00, 1, 0x0045DC4F);
		WriteMemory(0x90, 1, 0x0045DC50);
		WriteMemory(0x90, 1, 0x0045DC51);
	}
	else
	{
		WriteMemory(0xC7, 1, 0x0045DC49);
		WriteMemory(0x43, 1, 0x0045DC4A);
		WriteMemory(0x24, 1, 0x0045DC4B);
		WriteMemory(0x0C, 1, 0x0045DC4C);
		WriteMemory(0x00, 1, 0x0045DC4D);
		WriteMemory(0x00, 1, 0x0045DC4E);
		WriteMemory(0x00, 1, 0x0045DC4F);
		WriteMemory(0x90, 1, 0x0045DC50);
		WriteMemory(0x90, 1, 0x0045DC51);
	}
}

void PVZ_1_0::PlantsAllRed(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x004636E4);
		WriteMemory(0x00, 1, 0x004636E9);
		WriteMemory(0x00, 1, 0x004636EE);
		WriteMemory(0x01, 1, 0x004636EF);
	}
	else
	{
		WriteMemory(0x75, 1, 0x004636E4);
		WriteMemory(0x64, 1, 0x004636E9);
		WriteMemory(0x64, 1, 0x004636EE);
		WriteMemory(0x00, 1, 0x004636EF);
	}
}

void PVZ_1_0::PlantsAllGreen(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x004636E4);
		WriteMemory(0x01, 1, 0x004636EA);
		WriteMemory(0x00, 1, 0x004636EE);
		WriteMemory(0x00, 1, 0x004636E9);
	}
	else
	{
		WriteMemory(0x75, 1, 0x004636E4);
		WriteMemory(0x64, 1, 0x004636E9);
		WriteMemory(0x64, 1, 0x004636EE);
		WriteMemory(0x00, 1, 0x004636EA);
	}
}

void PVZ_1_0::PlantsAllBlack(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x004636E4);
		WriteMemory(0x00, 1, 0x004636EE);
		WriteMemory(0x00, 1, 0x004636E9);
	}
	else
	{
		WriteMemory(0x75, 1, 0x004636E4);
		WriteMemory(0x64, 1, 0x004636E9);
		WriteMemory(0x64, 1, 0x004636EE);
	}
}

void PVZ_1_0::baolingqiu(bool b)
{
	if (b)
	{
		WriteMemory(-28528, 2, 0x0046325B);
	}
	else
	{
		WriteMemory(2420, 2, 0x0046325B);
	}
}

void PVZ_1_0::ChNotKill(bool b)
{
	if (b)
	{
		WriteMemory(0x90, 1, 0x00461454);
		WriteMemory(0x90, 1, 0x00461455);
	}
	else
	{
		WriteMemory(0x75, 1, 0x00461454);
		WriteMemory(0x02, 1, 0x00461455);
	}
}

void PVZ_1_0::SetPlantsRoleWoGua(bool b)
{
	if (b)
	{
		WriteMemory(0xC7, 1, 0x0045DC49);
		WriteMemory(0x43, 1, 0x0045DC4A);
		WriteMemory(0x24, 1, 0x0045DC4B);
		WriteMemory(0x11, 1, 0x0045DC4C);
		WriteMemory(0x00, 1, 0x0045DC4D);
		WriteMemory(0x00, 1, 0x0045DC4E);
		WriteMemory(0x00, 1, 0x0045DC4F);
		WriteMemory(0x90, 1, 0x0045DC50);
		WriteMemory(0x90, 1, 0x0045DC51);
	}
	else
	{
		WriteMemory(0xC7, 1, 0x0045DC49);
		WriteMemory(0x43, 1, 0x0045DC4A);
		WriteMemory(0x24, 1, 0x0045DC4B);
		WriteMemory(0x0C, 1, 0x0045DC4C);
		WriteMemory(0x00, 1, 0x0045DC4D);
		WriteMemory(0x00, 1, 0x0045DC4E);
		WriteMemory(0x00, 1, 0x0045DC4F);
		WriteMemory(0x90, 1, 0x0045DC50);
		WriteMemory(0x90, 1, 0x0045DC51);
	}
}

void PVZ_1_0::Bungee(bool b)
{
	if (b)
	{
		/*
		117 = 0x75
		116 = 0x74
		112 = 0x70
		 */
		WriteMemory(0x75, 1, 0x00412F16);
	}
	else
	{
		WriteMemory(0x74, 1, 0x00412F16);
	}
}

void PVZ_1_0::GraveMode(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x004268FA);
	}
	else
	{
		WriteMemory(0x75, 1, 0x004268FA);
	}
}

void PVZ_1_0::SetAdNum(int num)
{
	WriteMemory(num, 4, 0x006A9F38, 2, 0x82c, 0x2c);
}

void PVZ_1_0::SetChomper(int num)
{
	WriteMemory(num, 4, 0x0046805E);
}

void PVZ_1_0::SetFumeShroom(int num)
{
	WriteMemory(num, 4, 0x004680F2);
}

void PVZ_1_0::SetZeng(int num)
{
	WriteMemory(num, 4, 0x00468113);
}

void PVZ_1_0::NoSeePlants(bool b)
{
	if (b)
	{
		WriteMemory(0x90, 1, 0x0052AFCA);
		WriteMemory(0x90, 1, 0x0052AFCB);
		WriteMemory(0x90, 1, 0x0052AFCC);
	}
	else
	{
		WriteMemory(0x89, 1, 0x0052AFCA);
		WriteMemory(0x46, 1, 0x0052AFCB);
		WriteMemory(0x08, 1, 0x0052AFCC);
	}
}

void PVZ_1_0::BuPaSanYe(bool b)
{
	if (b)
	{
		WriteMemory(255, 1, 0x004620D5);
	}
	else
	{
		WriteMemory(1, 1, 0x004620D5);
	}
}

void PVZ_1_0::ConterMarch(bool b)
{
	if (b)
	{
		WriteMemory(0xD8, 1, 0x0052AB2A);
		WriteMemory(0x44, 1, 0x0052AB2B);
		WriteMemory(0x24, 1, 0x0052AB2C);
		WriteMemory(0x08, 1, 0x0052AB2D);
	}
	else
	{
		WriteMemory(0xD8, 1, 0x0052AB2A);
		WriteMemory(0x64, 1, 0x0052AB2B);
		WriteMemory(0x24, 1, 0x0052AB2C);
		WriteMemory(0x08, 1, 0x0052AB2D);
	}
}

void PVZ_1_0::DancerFunny(bool b)
{
	if (b)
	{
		WriteMemory(0xEB, 1, 0x0052B222);
	}
	else
	{
		WriteMemory(0x75, 1, 0x0052B222);
	}
}

void PVZ_1_0::NoCar(bool b)
{
	if (b)
	{
		WriteMemory(0xC2, 1, 0x0040BC70);
		WriteMemory(0x04, 1, 0x0040BC71);
		WriteMemory(0x00, 1, 0x0040BC72);
		WriteMemory(0x90, 1, 0x0040BC73);
		WriteMemory(0x90, 1, 0x0040BC74);
		WriteMemory(0x90, 1, 0x0040BC75);
	}
	else
	{
		WriteMemory(0x53, 1, 0x0040BC70);
		WriteMemory(0x55, 1, 0x0040BC71);
		WriteMemory(0x8B, 1, 0x0040BC72);
		WriteMemory(0x6C, 1, 0x0040BC73);
		WriteMemory(0x24, 1, 0x0040BC74);
		WriteMemory(0x0C, 1, 0x0040BC75);
	}
}

void PVZ_1_0::SunMore(bool b)
{
	if (b)
	{
		WriteMemory(0x01, 1, 0x00041BA76);
		WriteMemory(0x9F, 1, 0x00041BA77);
		WriteMemory(0x60, 1, 0x00041BA78);
		WriteMemory(0x55, 1, 0x00041BA79);
		WriteMemory(0x00, 1, 0x00041BA7A);
		WriteMemory(0x00, 1, 0x00041BA7B);
	}
	else {
		WriteMemory(0xB9, 1, 0x00041BA76);
		WriteMemory(0xB7, 1, 0x00041BA77);
		WriteMemory(0x60, 1, 0x00041BA78);
		WriteMemory(0x55, 1, 0x00041BA79);
		WriteMemory(0x00, 1, 0x00041BA7A);
		WriteMemory(0x00, 1, 0x00041BA7B);
	}
}

void PVZ_1_0::MoneyMore(bool b) {
	if (b)
	{
		WriteMemory(0x01, 1, 0x00048CAA5);
	}
	else {
		WriteMemory(0x29, 1, 0x00048CAA5);
	}
}

void PVZ_1_0::SetMoney(int money)
{
	WriteMemory(money, 4, DATA_ADDR, 2, GARDON_OFFSET, 0x28);
}

void PVZ_1_0::IgnoreSun(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x0041ba72);
		WriteMemory(0x3b, 1, 0x0041ba74);
		WriteMemory(0x91, 1, 0x0041bac0);
		WriteMemory(0x80, 1, 0x00427a92);
		WriteMemory(0x80, 1, 0x00427dfd);
		WriteMemory(0xeb, 1, 0x0042487f);
	}
	else
	{
		WriteMemory(0x7f, 1, 0x0041ba72);
		WriteMemory(0x2b, 1, 0x0041ba74);
		WriteMemory(0x9e, 1, 0x0041bac0);
		WriteMemory(0x8f, 1, 0x00427a92);
		WriteMemory(0x8f, 1, 0x00427dfd);
		WriteMemory(0x74, 1, 0x0042487f);
	}
}

void PVZ_1_0::AutoPickup(bool b)
{
	if (b)
	{
		WriteMemory(0xeb, 1, 0x0043158f);
	}
	else
	{
		WriteMemory(0x75, 1, 0x0043158f);
	}
}

void PVZ_1_0::StartCar()
{
	if (InGame())
	{
		clear();
		GetCars();
		for (auto& rc : vc)
		{
			mov_exx(RegType::ESI, rc.addr);
			call(0x00458da0);
		}
		RunAsm();
	}
}

void PVZ_1_0::PlantSetSpeed(int plant, int speed)
{
	if (plant == 0)
	{
		WriteMemory(speed, 4, 0x0069F2CC);
	}

	if (plant == 1)
	{
		WriteMemory(speed, 4, 0x0069F2F0);
	}

	if (plant == 2)
	{
		WriteMemory(speed, 4, 0x0069F314);
	}

	if (plant == 3)
	{
		WriteMemory(speed, 4, 0x0069F338);
	}

	if (plant == 4)
	{
		WriteMemory(speed, 4, 0x0069F35C);
	}

	if (plant == 5)
	{
		WriteMemory(speed, 4, 0x0069F380);
	}

	if (plant == 6)
	{
		WriteMemory(speed, 4, 0x0069F3A4);
	}

	if (plant == 7)
	{
		WriteMemory(speed, 4, 0x0069F3C8);
	}

	if (plant == 8)
	{
		WriteMemory(speed, 4, 0x0069F3EC);
	}

	if (plant == 9)
	{
		WriteMemory(speed, 4, 0x0069F410);
	}

	if (plant == 10)
	{
		WriteMemory(speed, 4, 0x0069F434);
	}

	if (plant == 11)
	{
		WriteMemory(speed, 4, 0x0069F458);
	}

	if (plant == 12)
	{
		WriteMemory(speed, 4, 0x0069F47C);
	}

	if (plant == 13)
	{
		WriteMemory(speed, 4, 0x0069F4A0);
	}

	if (plant == 14)
	{
		WriteMemory(speed, 4, 0x0069F4C4);
	}

	if (plant == 15)
	{
		WriteMemory(speed, 4, 0x0069F4E8);
	}

	if (plant == 16)
	{
		WriteMemory(speed, 4, 0x0069F530);
	}

	if (plant == 18)
	{
		WriteMemory(speed, 4, 0x0069F554);
	}

	if (plant == 19)
	{
		WriteMemory(speed, 4, 0x0069F578);
	}

	if (plant == 20)
	{
		WriteMemory(speed, 4, 0x0069F59C);
	}

	if (plant == 21)
	{
		WriteMemory(speed, 4, 0x0069F5C0);
	}

	if (plant == 22)
	{
		WriteMemory(speed, 4, 0x0069F5E4);
	}

	if (plant == 23)
	{
		WriteMemory(speed, 4, 0x0069F608);
	}

	if (plant == 24)
	{
		WriteMemory(speed, 4, 0x0069F62C);
	}

	if (plant == 25)
	{
		WriteMemory(speed, 4, 0x0069F650);
	}

	if (plant == 26)
	{
		WriteMemory(speed, 4, 0x0069F674);
	}

	if (plant == 27)
	{
		WriteMemory(speed, 4, 0x0069F698);
	}

	if (plant == 28)
	{
		WriteMemory(speed, 4, 0x0069F6BC);
	}

	if (plant == 29)
	{
		WriteMemory(speed, 4, 0x0069F6E0);
	}

	if (plant == 30)
	{
		WriteMemory(speed, 4, 0x0069F704);
	}

	if (plant == 31)
	{
		WriteMemory(speed, 4, 0x0069F728);
	}

	if (plant == 32)
	{
		WriteMemory(speed, 4, 0x0069F74C);
	}

	if (plant == 33)
	{
		WriteMemory(speed, 4, 0x0069F770);
	}

	if (plant == 34)
	{
		WriteMemory(speed, 4, 0x0069F794);
	}

	if (plant == 35)
	{
		WriteMemory(speed, 4, 0x0069F7B8);
	}

	if (plant == 36)
	{
		WriteMemory(speed, 4, 0x0069F7DC);
	}

	if (plant == 37)
	{
		WriteMemory(speed, 4, 0x0069F800);
	}

	if (plant == 38)
	{
		WriteMemory(speed, 4, 0x0069F824);
	}

	if (plant == 39)
	{
		WriteMemory(speed, 4, 0x0069F848);
	}

	if (plant == 40)
	{
		WriteMemory(speed, 4, 0x0069F86C);
	}

	if (plant == 41)
	{
		WriteMemory(speed, 4, 0x0069F890);
	}

	if (plant == 42)
	{
		WriteMemory(speed, 4, 0x0069F8B4);
	}

	if (plant == 43)
	{
		WriteMemory(speed, 4, 0x0069F8D8);
	}

	if (plant == 44)
	{
		WriteMemory(speed, 4, 0x0069F8FC);
	}

	if (plant == 45)
	{
		WriteMemory(speed, 4, 0x0069F920);
	}

	if (plant == 46)
	{
		WriteMemory(speed, 4, 0x0069F944);
	}
}
void PVZ_1_0::PlantSetHealthy(int plant, int healthy)
{
	if (plant == 0)
	{
		WriteMemory(healthy, 4, 0x0045DC55);
	}
	if (plant == 1)
	{
		WriteMemory(healthy, 4, 0x0045E1A7);
	}
	if (plant == 2)
	{
		WriteMemory(healthy, 4, 0x0045E215);
	}
	if (plant == 3)
	{
		WriteMemory(healthy, 4, 0x0045E445);
	}
	if (plant == 4)
	{
		WriteMemory(healthy, 4, 0x0045E242);
	}
	if (plant == 5)
	{
		WriteMemory(healthy, 4, 0x0045E5C3);
	}
}
void PVZ_1_0::SetItemValue(int item, int value)
{
	if (item == 0)
	{
		WriteMemory(value, 1, 0x00430A63);
	}
	if (item == 1)
	{
		WriteMemory(value, 1, 0x00430A46);
	}
	if (item == 2)
	{
		WriteMemory(value, 4, 0x004309F0);
	}
	if (item == 3)
	{
		WriteMemory(value + 5, 1, 0x004309FD);
	}
	if (item == 4)
	{
		WriteMemory(value, 1, 0x00430A0D);
	}
}
void PVZ_1_0::SetPlantValue(int plant, int speed)
{
	if (plant == 0)
	{
		WriteMemory(speed, 4, 0x0069F2C0);
	}

	if (plant == 1)
	{
		WriteMemory(speed, 4, 0x0069F2E4);
	}

	if (plant == 2)
	{
		WriteMemory(speed, 4, 0x0069F308);
	}

	if (plant == 3)
	{
		WriteMemory(speed, 4, 0x0069F32C);
	}

	if (plant == 4)
	{
		WriteMemory(speed, 4, 0x0069F350);
	}

	if (plant == 5)
	{
		WriteMemory(speed, 4, 0x0069F374);
	}

	if (plant == 6)
	{
		WriteMemory(speed, 4, 0x0069F398);
	}

	if (plant == 7)
	{
		WriteMemory(speed, 4, 0x0069F3BC);
	}

	if (plant == 8)
	{
		WriteMemory(speed, 4, 0x0069F3E0);
	}

	if (plant == 9)
	{
		WriteMemory(speed, 4, 0x0069F404);
	}

	if (plant == 10)
	{
		WriteMemory(speed, 4, 0x0069F428);
	}

	if (plant == 11)
	{
		WriteMemory(speed, 4, 0x0069F44C);
	}

	if (plant == 12)
	{
		WriteMemory(speed, 4, 0x0069F470);
	}

	if (plant == 13)
	{
		WriteMemory(speed, 4, 0x0069F494);
	}

	if (plant == 14)
	{
		WriteMemory(speed, 4, 0x0069F4B8);
	}

	if (plant == 15)
	{
		WriteMemory(speed, 4, 0x0069F4DC);
	}

	if (plant == 16)
	{
		WriteMemory(speed, 4, 0x0069F500);
	}

	if (plant == 18)
	{
		WriteMemory(speed, 4, 0x0069F548);
	}

	if (plant == 19)
	{
		WriteMemory(speed, 4, 0x0069F56C);
	}

	if (plant == 20)
	{
		WriteMemory(speed, 4, 0x0069F590);
	}

	if (plant == 21)
	{
		WriteMemory(speed, 4, 0x0069F5B4);
	}

	if (plant == 22)
	{
		WriteMemory(speed, 4, 0x0069F5D8);
	}

	if (plant == 23)
	{
		WriteMemory(speed, 4, 0x0069F5FC);
	}

	if (plant == 24)
	{
		WriteMemory(speed, 4, 0x0069F620);
	}

	if (plant == 25)
	{
		WriteMemory(speed, 4, 0x0069F644);
	}

	if (plant == 26)
	{
		WriteMemory(speed, 4, 0x0069F668);
	}

	if (plant == 27)
	{
		WriteMemory(speed, 4, 0x0069F68C);
	}

	if (plant == 28)
	{
		WriteMemory(speed, 4, 0x0069F6B0);
	}

	if (plant == 29)
	{
		WriteMemory(speed, 4, 0x0069F6D4);
	}

	if (plant == 30)
	{
		WriteMemory(speed, 4, 0x0069F6F8);
	}

	if (plant == 31)
	{
		WriteMemory(speed, 4, 0x0069F71C);
	}

	if (plant == 32)
	{
		WriteMemory(speed, 4, 0x0069F740);
	}

	if (plant == 33)
	{
		WriteMemory(speed, 4, 0x0069F764);
	}

	if (plant == 34)
	{
		WriteMemory(speed, 4, 0x0069F788);
	}

	if (plant == 35)
	{
		WriteMemory(speed, 4, 0x0069F7AC);
	}

	if (plant == 36)
	{
		WriteMemory(speed, 4, 0x0069F7D0);
	}

	if (plant == 37)
	{
		WriteMemory(speed, 4, 0x0069F7F4);
	}

	if (plant == 38)
	{
		WriteMemory(speed, 4, 0x0069F818);
	}

	if (plant == 39)
	{
		WriteMemory(speed, 4, 0x0069F83C);
	}

	if (plant == 40)
	{
		WriteMemory(speed, 4, 0x0069F860);
	}

	if (plant == 41)
	{
		WriteMemory(speed, 4, 0x0069F884);
	}

	if (plant == 42)
	{
		WriteMemory(speed, 4, 0x0069F8A8);
	}

	if (plant == 43)
	{
		WriteMemory(speed, 4, 0x0069F8CC);
	}

	if (plant == 44)
	{
		WriteMemory(speed, 4, 0x0069F8F0);
	}

	if (plant == 45)
	{
		WriteMemory(speed, 4, 0x0069F914);
	}

	if (plant == 46)
	{
		WriteMemory(speed, 4, 0x0069F938);
	}

	if (plant == 47)
	{
		WriteMemory(speed, 4, 0x0069F95C);
	}
}

void PVZ_1_0::SetPlantTime(int plant, int value)
{
	if (plant == 0)
	{
		WriteMemory(value, 4, 0x0045E300);
	}
	if (plant == 1)
	{
		WriteMemory(value, 4, 0x00461551);
	}
	if (plant == 2)
	{
		WriteMemory(value, 4, 0x0045E34E);
	}
}

void PVZ_1_0::ProTime(int pro, int value)
{
	if (pro == 0)
	{
		WriteMemory(value, 4, 0x00532426);
	}
	if (pro == 1)
	{
		WriteMemory(value, 4, 0x00532741);
	}
	if (pro == 2)
	{
		WriteMemory(value, 4, 0x005309CE);
	}
}

void PVZ_1_0::BulletDamage(int bullet, int damage)
{
	if (bullet == 0)
	{
		WriteMemory(damage, 4, 0x0069F1C8);
	}
	if (bullet == 1)
	{
		WriteMemory(damage, 4, 0x0069F1D4);
	}
	if (bullet == 2)
	{
		WriteMemory(damage, 4, 0x0069F1E0);
	}
	if (bullet == 3)
	{
		WriteMemory(damage, 4, 0x0069F1EC);
	}
	if (bullet == 4)
	{
		WriteMemory(damage, 4, 0x0069F1F8);
	}
	if (bullet == 5)
	{
		WriteMemory(damage, 4, 0x0069F204);
	}
	if (bullet == 6)
	{
		WriteMemory(damage, 4, 0x0069F210);
	}
	if (bullet == 7)
	{
		WriteMemory(damage, 4, 0x0069F21C);
	}
	if (bullet == 8)
	{
		WriteMemory(damage, 4, 0x0069F228);
	}
	if (bullet == 9)
	{
		WriteMemory(damage, 4, 0x0069F240);
	}
	if (bullet == 10)
	{
		WriteMemory(damage, 4, 0x0069F258);
	}
	if (bullet == 11)
	{
		WriteMemory(damage, 4, 0x0041D931);
	}
	if (bullet == 12)
	{
		WriteMemory(damage, 4, 0x004607A9);
	}
	if (bullet == 13)
	{
		if(damage > 127)
		{
			MessageBoxA(NULL, "请输入小于127的数！", "注意", MB_OK);
		}
		else
		{
			WriteMemory(damage, 1, 0x00532493);
		}
	}
	if (bullet == 14)
	{
		if (damage > 127)
		{
			MessageBoxA(NULL, "请输入小于127的数！", "注意", MB_OK);
		}
		else
		{
			WriteMemory(damage, 1, 0x004614DD);
		}
	}
}

void PVZ_1_0::MoneyFlowerChange(int num1, int num2, int num1gailv )
{
	if (num1gailv == 127 || num1gailv < 127)
	{
		WriteMemory(256 - 37 + num1, 1, 0x0045FAFC);
		WriteMemory(num2 + 1, 1, 0x0045FB0B);
		WriteMemory(num1gailv, 1, 0x0045FB07);
	}
	else
	{
		MessageBoxA(NULL, "请输入小于127的数！", "注意", MB_OK);
	}
}

void PVZ_1_0::FuckingZombieDamageType(int type)
{
	if (type == 0)
	{
		WriteMemory(6, 1, 0x00527A94);
	}
	if (type == 1)
	{
		WriteMemory(0, 1, 0x00527A94);
	}
	if (type == 2)
	{
		WriteMemory(7, 1, 0x00527A94);
	}
}

void PVZ_1_0::PeaZombieDamageType(int type)
{
	if (type == 0)
	{
		WriteMemory(6, 1, 0x005275Ab);
	}
	if (type == 1)
	{
		WriteMemory(0, 1, 0x005275Ab);
	}
	if (type == 2)
	{
		WriteMemory(7, 1, 0x005275Ab);
	}
}

void PVZ_1_0::bulletStraight(bool b)
{
	if (b)
	{
		WriteMemory(0x90, 1, 0x00467523);
		WriteMemory(0x90, 1, 0x00467524);
		WriteMemory(0x90, 1, 0x00467525);
		WriteMemory(0x90, 1, 0x00467526);
		WriteMemory(0x90, 1, 0x00467527);
		WriteMemory(0x90, 1, 0x00467528);
		WriteMemory(0x90, 1, 0x00467529);
	}
	else
	{
		WriteMemory(0xC7, 1, 0x00467523);
		WriteMemory(0x40, 1, 0x00467524);
		WriteMemory(0x58, 1, 0x00467525);
		WriteMemory(0x01, 1, 0x00467526);
		WriteMemory(0x00, 1, 0x00467527);
		WriteMemory(0x00, 1, 0x00467528);
		WriteMemory(0x00, 1, 0x00467529);
	}
}

void PVZ_1_0::ShopPrice(int item, int price)
{
	int a = item * 6 + 4769362;
	if (item < 12)
	{
		WriteMemory(price, 4, a);
	}
	if (item == 12)
	{
		WriteMemory(price, 4, 0x0048C6BF);
	}
}

void PVZ_1_0::ResetCar()
{
	if (InGame())
	{
		clear();
		GetCars();
		for (auto& rc : vc)
		{
			mov_exx(RegType::EAX, rc.addr);
			call(0x00458d10);
		}
		WriteMemory(0x60eb, 2, 0x0040bc98);
		WriteMemory(1, 1, 0x0040bd17);
		WriteMemory(0x99fc, 2, 0x00458002);
		mov_exx_dword_ptr(RegType::EAX, DATA_ADDR);
		mov_exx_dword_ptr_exx_add_dword(RegType::EAX, OFFSET_1);
		push_exx(RegType::EAX);
		call(0x0040bc70);
		RunAsm();
		WriteMemory(0x0975, 2, 0x0040bc98);
		WriteMemory(0, 1, 0x0040bd17);
		WriteMemory(0x9bf8, 2, 0x00458002);
	}
}

void PVZ_1_0::asm_plant(int row, int col, int type, bool copy)
{
	if (copy)
	{
		push_byte(type);
		push_byte(48);
		mov_exx(RegType::EAX, row);
		push_byte(col);
		mov_exx_dword_ptr(RegType::EBP, DATA_ADDR);
		mov_exx_dword_ptr_exx_add_dword(RegType::EBP, OFFSET_1);
		push_exx(RegType::EBP);
		call(0x0040d120);
		mov_exx_eyy(RegType::ESI, RegType::EAX);
		push_exx(RegType::EAX);
		call(0x00466b80);
		pop_exx(RegType::EAX);
	}
	else
	{
		push_byte(-1);
		push_byte(type);
		mov_exx(RegType::EAX, row);
		push_byte(col);
		mov_exx_dword_ptr(RegType::EBP, DATA_ADDR);
		mov_exx_dword_ptr_exx_add_dword(RegType::EBP, OFFSET_1);
		push_exx(RegType::EBP);
		call(0x0040d120);
	}
}

void PVZ_1_0::asm_plant_paper(int row, int col, int type)
{
	asm_plant(row, col, type, false);
	push_exx(RegType::EAX);
	mov_exx_dword_ptr(RegType::EAX, DATA_ADDR);
	mov_exx_dword_ptr_exx_add_dword(RegType::EAX, OFFSET_1);
	mov_exx_dword_ptr_exx_add_dword(RegType::EAX, OFFSET_2);
	call(0x0042a530);
}

void PVZ_1_0::NoPause(bool b)
{
	if (b)
	{
		WriteMemory(0xc3, 1, 0x0054ebef);
	}
	else
	{
		WriteMemory(0x57, 1, 0x0054ebef);
	}
}

void PVZ_1_0::asm_put_zombie(int row, int col, int type)
{
	push_byte(col);
	push_byte(type);
	mov_exx(RegType::EAX, row);
	mov_exx_dword_ptr(RegType::ECX, DATA_ADDR);
	mov_exx_dword_ptr_exx_add_dword(RegType::ECX, OFFSET_1);
	mov_exx_dword_ptr_exx_add_dword(RegType::ECX, OFFSET_2);
	call(0x0042a0f0);
}

void PVZ_1_0::asm_put_boss()
{
	mov_exx_dword_ptr(RegType::EAX, DATA_ADDR);
	mov_exx_dword_ptr_exx_add_dword(RegType::EAX, OFFSET_1);
	push_byte(0);
	push_byte(25);
	call(0x0040ddc0);
}

void PVZ_1_0::asm_put_ladder(int row, int col)
{
	mov_exx(RegType::EDI, row);
	push_byte(col);
	mov_exx_dword_ptr(RegType::EAX, DATA_ADDR);
	mov_exx_dword_ptr_exx_add_dword(RegType::EAX, OFFSET_1);
	call(0x00408f40);
}

void PVZ_1_0::asm_put_grave(int row, int col)
{
	mov_exx_dword_ptr(RegType::EDX, DATA_ADDR);
	mov_exx_dword_ptr_exx_add_dword(RegType::EDX, OFFSET_1);
	mov_exx_dword_ptr_exx_add_dword(RegType::EDX, OFFSET_2);
	push_exx(RegType::EDX);
	mov_exx(RegType::EDI, row);
	mov_exx(RegType::EBX, col);
	call(0x00426620);
}

// static void asm_put_rake(int row, int col)
// {
// 	push_byte(row);
// 	push_byte(col);
// 	mov_exx_dword_ptr(ECX, DATA_ADDR);
// 	mov_exx_dword_ptr_exx_add_dword(ECX, OFFSET_1);
// 	push_exx(ECX);
// 	call(0x0040b9c0);
// 	add_esp(8);
// }
// 
// void PVZ_1_0::PutRake(int row, int col)
// {
// 	if (InGame())
// 	{
// 		Map_1_0 map(process);
// 		int Rows = map.GetRowCount();
// 		int Cols = 9;
// 		clear();
// 		if (row == -1 && col == -1)
// 		{
// 			for (int i = 0; i < Rows; ++i)
// 			{
// 				for (int j = 0; j < Cols; ++j)
// 				{
// 					asm_put_rake(i, j);
// 				}
// 			}
// 		}
// 		else if (row != -1 && col == -1)
// 		{
// 			for (int i = 0; i < Cols; ++i)
// 			{
// 				asm_put_rake(row, i);
// 			}
// 		}
// 		else if (row == -1 && col != -1)
// 		{
// 			for (int i = 0; i < Rows; ++i)
// 			{
// 				asm_put_rake(i, col);
// 			}
// 		}
// 		else
// 		{
// 			asm_put_rake(row, col);
// 		}
// 		WriteMemory(0x0000a681, 4, 0x0040b9e3);
// 		WriteMemory(0, 1, 0x0040bb2b);
// 		WriteMemory(0x900c4d8b, 4, 0x0040bb3b);
// 		WriteMemory(0x9010458b, 4, 0x0040bb41);
// 		RunAsm();
// 		WriteMemory(0x00027984, 4, 0x0040b9e3);
// 		WriteMemory(-1, 1, 0x0040bb2b);
// 		WriteMemory(0x10244c8b, 4, 0x0040bb3b);
// 		WriteMemory(0x1424448b, 4, 0x0040bb41);
// 	}
// }

void PVZ_1_0::NoDelete(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x0054b267);
	}
	else
	{
		WriteMemory(0x74, 1, 0x0054b267);
	}
}

void PVZ_1_0::ShowShovel(bool b)
{
	if (b)
	{
		WriteMemory(1, 4, 0x006a9ec0, 2, 0x768, 0x55F1); //数字,字节,基址,偏移量,偏移
	}
	else
	{
		WriteMemory(0, 4, 0x006a9ec0, 2, 0x768, 0x55F1);
	}
}

void PVZ_1_0::SetWoGua(int num)
{
	WriteMemory(num, 1, 0x00468044); //数字,字节,基址,偏移量,偏移
}

void PVZ_1_0::CardFlicker(bool b)
{
	if (b)
	{
		WriteMemory(29, 4, 0x006a9ec0, 2, 0x768, 0x5584);
	}
	else
	{
		WriteMemory(0, 4, 0x006a9ec0, 2, 0x768, 0x5584);
	}
}

void PVZ_1_0::SetPlantsRoleGarlic(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x0052BA41);
		/*
117 = 0x75
116 = 0x74
112 = 0x70
 */
	}
	else
	{
		WriteMemory(0x75, 1, 0x0052BA41);
	}
}

void PVZ_1_0::SetPlantsRoleRadish(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x0041D3F8);
		/*
117 = 0x75
116 = 0x74
112 = 0x70
 */
	}
	else
	{
		WriteMemory(0x75, 1, 0x0041D3F8);
	}
}

void PVZ_1_0::JumpZomMax(bool b)
{
	if (b)
	{
		WriteMemory(11, 4, 0x0052613D);
	}
	else
	{
		WriteMemory(13, 4, 0x0052613D);
	}
}

void PVZ_1_0::PaperNoAngry(bool b)
{
	if (b)
	{
		WriteMemory(29, 4, 0x00525D21);
	}
	else
	{
		WriteMemory(31, 4, 0x00525D21);
	}
}

void PVZ_1_0::FastSpeed(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x0052B215);
	}
	else//112 70 117 75
	{
		WriteMemory(0x75, 1, 0x0052B215);
	}
}

void PVZ_1_0::FastSpeedMax(bool b)
{
	if (b)
	{
		WriteMemory(21621, 2, 0x0052F103);
	}
	else//112 70 117 75
	{
		WriteMemory(21620, 2, 0x0052F103);
	}
}

void PVZ_1_0::OneCardStart(bool b)
{
	if (b)
	{
		WriteMemory(0x90, 1, 0x0048610C);
		WriteMemory(0x90, 1, 0x0048610D);
		WriteMemory(0x90, 1, 0x0048610E);
	}
	else
	{
		WriteMemory(0x3B, 1, 0x0048610C);
		WriteMemory(0x51, 1, 0x0048610D);
		WriteMemory(0x24, 1, 0x0048610E);
	}
}

void PVZ_1_0::ForceCard(bool b)
{
	if (b)
	{
		WriteMemory(0xC3, 1, 0x0040BD30);
	}
	else
	{
		WriteMemory(0x56, 1, 0x0040BD30);
	}
}

void PVZ_1_0::NoGrave(bool b)
{
	if (b)
	{
		WriteMemory(0x90, 1, 0x0041BE25);
		WriteMemory(0x90, 1, 0x0041BE26);
		WriteMemory(0x90, 1, 0x0041BE27);
	}
	else
	{
		WriteMemory(0x38, 1, 0x0041BE25);
		WriteMemory(0x58, 1, 0x0041BE26);
		WriteMemory(0x20, 1, 0x0041BE27);
	}
}

void PVZ_1_0::NoSave(bool b)
{
	if (b)
	{
		WriteMemory(0x2e, 1, 0x00482149);
	}
	else
	{
		WriteMemory(0x13, 1, 0x00482149);
	}
}

void PVZ_1_0::Anywhere(bool b)
{
	if (b)
	{
		WriteMemory(0x81, 1, 0x0040fe30);
		WriteMemory(0xeb, 1, 0x00438e40);
		WriteMemory(0x8d, 1, 0x0042a2d9);
	}
	else
	{
		WriteMemory(0x84, 1, 0x0040fe30);
		WriteMemory(0x74, 1, 0x00438e40);
		WriteMemory(0x84, 1, 0x0042a2d9);
	}
}

void PVZ_1_0::FastBelt(bool b)
{
	if (b)
	{
		WriteMemory(0x80, 1, 0x00422d20);
		WriteMemory(0x33, 1, 0x00489ca1);
	}
	else
	{
		WriteMemory(0x8f, 1, 0x00422d20);
		WriteMemory(0x85, 1, 0x00489ca1);
	}
}

void PVZ_1_0::ShowHide(bool b)
{
	if (b)
	{
		WriteMemory(0x38, 1, 0x0042df5d);
	}
	else
	{
		WriteMemory(0x88, 1, 0x0042df5d);
	}
}

void PVZ_1_0::FullFog(bool b)
{
	if (b)
	{
		WriteMemory(0xc3c033, 3, 0x0041c1c0);
		WriteMemory(0x3feb, 2, 0x0041a476);
		WriteMemory(0, 1, 0x0041a4ba);
	}
	else
	{
		DWORD FogAddr = ReadMemory(4, DATA_ADDR, 1, OFFSET_1) + 0x4c8;
		for (int i = 0; i < 63; ++i)
		{
			WriteMemory(0, 4, FogAddr + i * 4);
		}
		WriteMemory(0x8c818b, 3, 0x0041c1c0);
		WriteMemory(0x0575, 2, 0x0041a476);
		WriteMemory(4, 1, 0x0041a4ba);
	}
}

void PVZ_1_0::SeeFog(bool b)
{
	if (b)
	{
		WriteMemory(0xd231, 2, 0x0041a68d);
	}
	else
	{
		WriteMemory(0xf23b, 2, 0x0041a68d);
	}
}

void PVZ_1_0::SeeVase(bool b)
{
	if (b)
	{
		WriteMemory(0x0033b866, 4, 0x0044e5cc);
	}
	else
	{
		WriteMemory(0x067ec085, 4, 0x0044e5cc);
	}
}

void PVZ_1_0::JmpLevel(int level)
{
	WriteMemory(level, 4, DATA_ADDR, 3, OFFSET_1, OFFSET_2, 0x6c);
}

void PVZ_1_0::MixMode(int mode, int level)
{
	if (mode == 0)
	{
		WriteMemory(level, 4, DATA_ADDR, 2, GARDON_OFFSET, 0x24);
		WriteMemory(level, 4, DATA_ADDR, 2, OFFSET_1, 0x5550);
	}
	WriteMemory(mode, 4, DATA_ADDR, 1, MODE_OFFSET);
}

void PVZ_1_0::Unlock(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x00454109);
		WriteMemory(0x70, 1, 0x0044a514);
		WriteMemory(0xc3c031, 3, 0x0042e440);
		WriteMemory(0xeb, 1, 0x00449e9d);
		WriteMemory(0xc3c030, 3, 0x0048aad0);
		WriteMemory(0xeb, 1, 0x0048a54c);
		WriteMemory(0xeb, 1, 0x0048d32b);
		WriteMemory(0xeb, 1, 0x0048c491);
		WriteMemory(0xeb, 1, 0x00449e7a);
		WriteMemory(0xeb, 1, 0x00453ad1);
		WriteMemory(0x5beb01b0, 4, 0x00403a10);
		WriteMemory(0, 4, 0x0069dca0);
		WriteMemory(0xc301b0, 3, 0x00403b30);
	}
	else
	{
		WriteMemory(0x7e, 1, 0x00454109);
		WriteMemory(0x7e, 1, 0x0044a514);
		WriteMemory(0x555351, 3, 0x0042e440);
		WriteMemory(0x7f, 1, 0x00449e9d);
		WriteMemory(0xd98b53, 3, 0x0048aad0);
		WriteMemory(0x7f, 1, 0x0048a54c);
		WriteMemory(0x7f, 1, 0x0048d32b);
		WriteMemory(0x7f, 1, 0x0048c491);
		WriteMemory(0x7f, 1, 0x00449e7a);
		WriteMemory(0x7f, 1, 0x00453ad1);
		WriteMemory(0x6c8b5551, 4, 0x00403a10);
		WriteMemory(40, 4, 0x0069dca0);
		WriteMemory(0x6c808b, 3, 0x00403b30);
	}
}

void PVZ_1_0::Win()
{
	int mode = GetMode();
	if (!InGame() ||
		mode >= 1 && mode <= 15 && ReadMemory(4, DATA_ADDR, 1, MODE_OFFSET + 4) != 3)
	{
		return;
	}
	clear();
	mov_exx_dword_ptr(RegType::ECX, DATA_ADDR);
	mov_exx_dword_ptr_exx_add_dword(RegType::ECX, OFFSET_1);
	call(0x0040c3e0);
	RunAsm();
}

void PVZ_1_0::Lock(bool b, int mode)
{
	if (b)
	{
		static const int val[] = { 24, -624, 73, 100, 122, 190, 249, 360 };
		WriteMemory(0x81, 1, 0x0042b047);
		WriteMemory(val[mode], 4, 0x0042b048);
	}
	else
	{
		WriteMemory(0x85, 1, 0x0042b047);
		WriteMemory(144, 4, 0x0042b048);
	}
}

void PVZ_1_0::Little(bool b)
{
	if (b)
	{
		WriteMemory(0xeb, 1, 0x00523ed5);
	}
	else
	{
		WriteMemory(0x74, 1, 0x00523ed5);
	}

}

void PVZ_1_0::Rain(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x00426b4e);
		WriteMemory(0x70, 1, 0x00416f07);
		WriteMemory(0xeb, 1, 0x00424715);
	}
	else
	{
		WriteMemory(0x75, 1, 0x00426b4e);
		WriteMemory(0x75, 1, 0x00416f07);
		WriteMemory(0x74, 1, 0x00424715);
	}
}

void PVZ_1_0::Storm(bool b)
{
	if (b)
	{
		WriteMemory(0xeb, 1, 0x00416eef);
		WriteMemory(0xeb, 1, 0x00426b6b);
		WriteMemory(0xeb, 1, 0x00426b35);
		WriteMemory(0xeb, 1, 0x004246c9);
		WriteMemory(0xeb, 1, 0x00424729);
	}
	else
	{
		WriteMemory(0x74, 1, 0x00416eef);
		WriteMemory(0x74, 1, 0x00426b6b);
		WriteMemory(0x74, 1, 0x00426b35);
		WriteMemory(0x74, 1, 0x004246c9);
		WriteMemory(0x74, 1, 0x00424729);
	}
}

void PVZ_1_0::Force(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x0046d546);
		WriteMemory(0x70, 1, 0x0046dc28);
		WriteMemory(0x70, 1, 0x00525bed);
	}
	else
	{
		WriteMemory(0x75, 1, 0x0046d546);
		WriteMemory(0x75, 1, 0x0046dc28);
		WriteMemory(0x75, 1, 0x00525bed);
	}
}

void PVZ_1_0::LikeCol(bool b)
{
	if (b)
	{
		WriteMemory(0x80, 1, 0x0043903d);
		WriteMemory(0x80, 1, 0x00410ae7);
	}
	else
	{
		WriteMemory(0x85, 1, 0x0043903d);
		WriteMemory(0x85, 1, 0x00410ae7);
	}
}

void PVZ_1_0::RunFast(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x004248aa);
	}
	else
	{
		WriteMemory(0x75, 1, 0x004248aa);
	}
}

void PVZ_1_0::SetCardNum(int num)
{
	if (InGame())
	{
		WriteMemory(0xc3, 1, 0x0041bee0);
		clear();
		mov_exx(RegType::EAX, num);
		mov_exx_dword_ptr(RegType::ESI, DATA_ADDR);
		mov_exx_dword_ptr_exx_add_dword(RegType::ESI, OFFSET_1);
		mov_exx_dword_ptr_exx_add_dword(RegType::ESI, 0x144);
		call(0x00489cd0);
		RunAsm();
		WriteMemory(0x56, 1, 0x0041bee0);
	}
}

void PVZ_1_0::SetCard(int cid, int type, bool copy)
{
	if (copy)
	{
		WriteMemory(48, 4, DATA_ADDR, 3, OFFSET_1, 0x144, 0x5c + cid * 0x50);
		WriteMemory(type, 4, DATA_ADDR, 3, OFFSET_1, 0x144, 0x60 + cid * 0x50);
	}
	else
	{
		WriteMemory(type, 4, DATA_ADDR, 3, OFFSET_1, 0x144, 0x5c + cid * 0x50);
	}
}

void PVZ_1_0::FSBoom(bool b)
{
	if (b)
	{
		WriteMemory(0x20eb, 2, 0x0041d8ff);
		WriteMemory(0x70, 1, 0x004664f2);
	}
	else
	{
		WriteMemory(0x3e7f, 2, 0x0041d8ff);
		WriteMemory(0x75, 1, 0x004664f2);
	}
}

void PVZ_1_0::FSSquash(bool b)
{
	if (b)
	{
		WriteMemory(0x45eb, 2, 0x00460929);
		WriteMemory(0x80, 1, 0x00460838);
		WriteMemory(0x5feb, 2, 0x00460747);
	}
	else
	{
		WriteMemory(0x707f, 2, 0x00460929);
		WriteMemory(0x85, 1, 0x00460838);
		WriteMemory(0x7275, 2, 0x00460747);
	}
}

void PVZ_1_0::FSMagnet(bool b)
{
	if (b)
	{
		WriteMemory(0x80, 1, 0x004620a3);
		WriteMemory(0x70, 1, 0x00462124);
	}
	else
	{
		WriteMemory(0x87, 1, 0x004620a3);
		WriteMemory(0x74, 1, 0x00462124);
	}
}

void PVZ_1_0::FSSputter(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x0046d455);
	}
	else
	{
		WriteMemory(0x74, 1, 0x0046d455);
	}
}

void PVZ_1_0::FSMouth(bool b)
{
	if (b)
	{
		WriteMemory(0x74, 1, eCode.Row + 0x18 - 0x0d);
		WriteMemory(0x74, 1, eCode.Col + 0x3d - 0x32);
	}
	else
	{
		WriteMemory(0x70, 1, eCode.Row + 0x18 - 0x0d);
		WriteMemory(0x70, 1, eCode.Col + 0x3d - 0x32);
	}
}

void PVZ_1_0::FSPrick(bool b)
{
	if (b)
	{
		WriteMemory(0x74, 1, eCode.Row + 0x22 - 0x0d);
		WriteMemory(0x74, 1, eCode.Row + 0x27 - 0x0d);
		WriteMemory(0x74, 1, eCode.Col + 0x4c - 0x32);
		WriteMemory(0x74, 1, eCode.Col + 0x51 - 0x32);
		WriteMemory(0x74, 1, eCode.RHurt + 0x69 - 0x5c);
		WriteMemory(0x74, 1, eCode.RHurt + 0x6e - 0x5c);
		WriteMemory(0x74, 1, eCode.CHurt + 0x8b - 0x79);
		WriteMemory(0x74, 1, eCode.CHurt + 0x90 - 0x79);
	}
	else
	{
		WriteMemory(0x70, 1, eCode.Row + 0x22 - 0x0d);
		WriteMemory(0x70, 1, eCode.Row + 0x27 - 0x0d);
		WriteMemory(0x70, 1, eCode.Col + 0x4c - 0x32);
		WriteMemory(0x70, 1, eCode.Col + 0x51 - 0x32);
		WriteMemory(0x70, 1, eCode.RHurt + 0x69 - 0x5c);
		WriteMemory(0x70, 1, eCode.RHurt + 0x6e - 0x5c);
		WriteMemory(0x70, 1, eCode.CHurt + 0x8b - 0x79);
		WriteMemory(0x70, 1, eCode.CHurt + 0x90 - 0x79);
	}
}

void PVZ_1_0::FSSpout(bool b)
{
	if (b)
	{
		WriteMemory(0x74, 1, eCode.Row + 0x1d - 0x0d);
		WriteMemory(0x74, 1, eCode.Col + 0x42 - 0x32);
		WriteMemory(0x74, 1, eCode.Col + 0x47 - 0x32);
		WriteMemory(0x74, 1, eCode.RHurt + 0x64 - 0x5c);
		WriteMemory(0x74, 1, eCode.CHurt + 0x81 - 0x79);
		WriteMemory(0x74, 1, eCode.CHurt + 0x86 - 0x79);
		WriteMemory(0x39eb, 2, 0x0046768d);
		WriteMemory(0x16eb, 2, 0x0045ed5c);
	}
	else
	{
		WriteMemory(0x70, 1, eCode.Row + 0x1d - 0x0d);
		WriteMemory(0x70, 1, eCode.Col + 0x42 - 0x32);
		WriteMemory(0x70, 1, eCode.Col + 0x47 - 0x32);
		WriteMemory(0x70, 1, eCode.RHurt + 0x64 - 0x5c);
		WriteMemory(0x70, 1, eCode.CHurt + 0x81 - 0x79);
		WriteMemory(0x70, 1, eCode.CHurt + 0x86 - 0x79);
		WriteMemory(0x8c0f, 2, 0x0046768d);
		WriteMemory(0x8c0f, 2, 0x0045ed5c);
	}
}

void PVZ_1_0::CatHack(bool b)
{
	if (b)
	{
		static unsigned char _3_code[] = { 144, 144, 144, 144, 144, 144 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x00462D87);
	}
	else
	{
		static unsigned char _3_code[] = { 15, 135, 177, 3, 0, 0 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x00462D87);
	}
}

void PVZ_1_0::BigWallnut(bool b)
{
	if (b)
	{
		WriteMemory(10731, 2, 0x004630D4);
	}
	else
	{
		WriteMemory(10612, 2, 0x004630D4);
	}
}

void PVZ_1_0::BombWallnut(bool b)
{
	if (b)
	{
		WriteMemory(128, 1, 0x00462DFC);
	}
	else
	{
		WriteMemory(133, 1, 0x00462DFC);
	}
}

void PVZ_1_0::TheWorld2(bool b)
{
	if (b)
	{
		WriteMemory(-28528, 2, 0x0041BC6A);
	}
	else
	{
		WriteMemory(31467, 2, 0x0041BC6A);
	}
}

void PVZ_1_0::BiaoBaZom(bool b)
{
	if (b)
	{
		WriteMemory(10608, 2, 0x00416A5D);
	}
	else
	{
		WriteMemory(10613, 2, 0x00416A5D);
	}
}

void PVZ_1_0::GaGangBuReng(bool b)
{
	if (b)
	{
		static unsigned char _3_code[] = { 193, 248, 2, 144, 144, 144, 144, 144, 125, 59 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x005271FD);
	}
	else
	{
		static unsigned char _3_code[] = { 209, 248, 57, 131, 200, 0, 0, 0, 125, 59 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x005271FD);
	}
}

void PVZ_1_0::OKRengIMP(bool b)
{
	if (b)
	{
		static unsigned char _3_code[] = { 193, 248, 2, 57, 131, 200, 0, 0, 0, 144 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x005271FD);
	}
	else
	{
		static unsigned char _3_code[] = { 209, 248, 57, 131, 200, 0, 0, 0, 125, 59 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x005271FD);
	}
}

void PVZ_1_0::FastBigZom(bool b)
{
	if (b)
	{
		WriteMemory(21621, 2, 0x0052F103);
	}
	else
	{
		WriteMemory(21620, 2, 0x0052F103);
	}
}

void PVZ_1_0::FastWallnut(bool b)
{
	if (b)
	{
		WriteMemory(2672, 2, 0x00462D30);
	}
	else
	{
		WriteMemory(2677, 2, 0x00462D30);
	}
}

void PVZ_1_0::SlowIMP(bool b)
{
	if (b)
	{
		static unsigned char _3_code[] = { 144, 144, 144, 144, 144, 144 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x005270F5);
	}
	else
	{
		static unsigned char _3_code[] = { 139, 139, 172, 0, 0, 0, 0, 224, 36, 12 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x005270F5);
	}
}

void PVZ_1_0::IMPFallDie(bool b)
{
	if (b)
	{
		WriteMemory(3, 2, 0x00527373);
	}
	else
	{
		WriteMemory(72, 2, 0x00527373);
	}
}

void PVZ_1_0::NormalOKSun(int sun)
{
	WriteMemory(sun, 4, 0x0040B09B);
}

void PVZ_1_0::FirstOKSun(int sun)
{
	WriteMemory(sun, 4, 0x0040B08F);
}

void PVZ_1_0::BackWallnut(bool b)
{
	if (b)
	{
		WriteMemory(337921240, 4, 0x00462D3F);
	}
	else
	{
		WriteMemory(337929432, 4, 0x00462D3F);
	}
}

void PVZ_1_0::FSCat(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x004677ef);
		WriteMemory(0x75, 1, eCode.CatR + 0xc3 - 0x9b);
		WriteMemory(0x74, 1, eCode.CatC + 0xd1 - 0xc8);
		WriteMemory(0x1beb, 2, 0x00464a52);
		static unsigned char code1[] = { 0x33, 0xc0, 0xb0, 0x03, 0xeb, 0x0f };
		WriteArrayMemory(code1, sizeof(code1), 0x0045eb10);
		WriteMemory(0x3f, 1, 0x00464a61);
		static unsigned char _3_code[] = { 0xE9, 0x91, 0x00, 0x00, 0x00, 0x83, 0xF8, 0x12, 0x75, 0xE9, 0x8B, 0x87, 0x90, 0x00, 0x00, 0x00, 0x83, 0xF8, 0x09, 0x74, 0xBE, 0x83, 0xF8, 0x05, 0x74, 0xB9, 0x83, 0xF8, 0x01, 0x74, 0xB4, 0xE9, 0x74, 0xFE, 0xFF, 0xFF };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x00464a9c);
		WriteMemory(0xeb, 1, 0x004672f4);
		WriteMemory(0x70, 1, 0x00467369);
		WriteMemory(0x70, 1, eCode.Split);
		WriteMemory(0xe9, 1, 0x00464bbc);
		WriteMemory(0xfffffeae, 4, 0x00464bbd);
		WriteMemory(0x70, 1, eCode.Throw);
		WriteMemory(0x02ebd175, 4, 0x004673b3);
		WriteMemory(0x80, 1, 0x004672d1);
		WriteMemory(0x80, 1, 0x004672da);
		WriteMemory(0x80, 1, 0x004672e3);
		WriteMemory(0x80, 1, 0x004672ec);
		WriteMemory(0x80, 1, 0x00467353);
		WriteMemory(0x80, 1, 0x0046735c);
		WriteMemory(0xeb, 1, 0x0046736e);
	}
	else
	{
		WriteMemory(0x75, 1, 0x004677ef);
		WriteMemory(0x70, 1, eCode.CatR + 0xc3 - 0x9b);
		WriteMemory(0xeb, 1, eCode.CatC + 0xd1 - 0xc8);
		WriteMemory(0x4f8b, 2, 0x00464a52);
		static unsigned char code1[] = { 0x8B, 0x40, 0x24, 0x83, 0xF8, 0x1A };
		WriteArrayMemory(code1, sizeof(code1), 0x0045eb10);
		WriteMemory(0x2d, 1, 0x00464a61);
		static unsigned char _3_code[] = { 0x83, 0xF8, 0x12, 0x0F, 0x85, 0x8D, 0x00, 0x00, 0x00, 0x8B, 0x5F, 0x1C, 0x8B, 0x37, 0x8B, 0x8F, 0x9C, 0x00, 0x00, 0x00, 0x8D, 0x53, 0xFF, 0x8B, 0xC6, 0x89, 0x54, 0x24, 0x14, 0xE8, 0xF2, 0xF1, 0xFE, 0xFF, 0x8B, 0x8F };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x00464a9c);
		WriteMemory(0x75, 1, 0x004672f4);
		WriteMemory(0x74, 1, 0x00467369);
		WriteMemory(0xeb, 1, eCode.Split);
		WriteMemory(0x8b, 1, 0x00464bbc);
		WriteMemory(0x006a1c4f, 4, 0x00464bbd);
		WriteMemory(0xeb, 1, eCode.Throw);
		WriteMemory(0x0193850f, 4, 0x004673b3);
		WriteMemory(0x84, 1, 0x004672d1);
		WriteMemory(0x84, 1, 0x004672da);
		WriteMemory(0x84, 1, 0x004672e3);
		WriteMemory(0x84, 1, 0x004672ec);
		WriteMemory(0x84, 1, 0x00467353);
		WriteMemory(0x84, 1, 0x0046735c);
		WriteMemory(0x75, 1, 0x0046736e);
	}
}

void PVZ_1_0::CatTouch(bool b)
{
	if (b)
	{
		WriteMemory(0x81, 1, 0x0046cecc);
	}
	else
	{
		WriteMemory(0x85, 1, 0x0046cecc);
	}
}

static void __declspec(naked) DoorCode()
{
	_asm {
		jmp fend;
		mov[eax + 0x14], ecx;
		mov dword ptr[eax + 0x1c], 0x00054b78;
		ret;
		int 3;
		int 3;
	fend:
	}
}

static void __declspec(naked) RowCode()
{
	_asm {
		jmp fend;
		je short label;
		mov edx, [ebp + 8];
		mov edx, [edx + 0x24];
		cmp edx, 6;
		jo short label;
		cmp edx, 10;
		jo short label;
		cmp edx, 21;
		jo short label;
		cmp edx, 46;
		jo short label;
		pop edx;
		push 0x00467884;
	label:
		ret;
		int 3;
		int 3;
	fend:
	}
}

static void __declspec(naked) ColCode()
{
	_asm {
		jmp fend;
		jge short label;
		mov edi, [ebp + 8];
		mov edi, [edi + 0x24];
		cmp edi, 6;
		jo short label;
		cmp edi, 10;
		jo short label;
		cmp edi, 42;
		jo short label;
		cmp edi, 21;
		jo short label;
		cmp edi, 46;
		jo short label;
		pop edi;
		push 0x00467881;
	label:
		ret;
		int 3;
		int 3;
	fend:
	}
}

static void __declspec(naked) RHurtCode()
{
	_asm {
		jmp fend;
		je short label;
		mov edx, [ebp + 0x24];
		cmp edx, 10;
		jo short label;
		cmp edx, 21;
		jo short label;
		cmp edx, 46;
		jo short label;
		pop edx;
		push 0x0045ee76;
	label:
		ret;
		int 3;
		int 3;
	fend:
	}
}

static void __declspec(naked) CHurtCode()
{
	_asm {
		jmp fend;
		jg short label;
		mov edx, [ebp + 0x24];
		cmp edx, 10;
		jo short label;
		cmp edx, 42;
		jo short label;
		cmp edx, 21;
		jo short label;
		cmp edx, 46;
		jo short label;
		pop edx;
		push 0x0045ee76;
	label:
		ret;
		int 3;
		int 3;
	fend:
	}
}

static void __declspec(naked) CatRCode()
{
	_asm {
		jmp fend;
		cmp eax, 43;
		jne short _1;
	_2:
		pop eax;
		_jmp(0x004676c8);
	_1:
		cmp eax, 4;
		je short label;
		cmp eax, 6;
		je short label;
		cmp eax, 10;
		je short label;
		cmp eax, 42;
		je short label;
		cmp eax, 21;
		je short label;
		cmp eax, 46;
		jo short _2;
	label:
		ret;
		int 3;
		int 3;
	fend:
	}
}

static void __declspec(naked) CatCCode()
{
	_asm {
		jmp fend;
		mov ecx, [ebp + 8];
		mov ecx, [ecx + 0x24];
		cmp ecx, 4;
		jmp short label;
		cmp ecx, 6;
		je short label;
		cmp ecx, 10;
		je short label;
		cmp ecx, 42;
		je short label;
		cmp ecx, 21;
		je short label;
		cmp ecx, 46;
		je short label;
		pop ecx;
		push 0x004677e0;
	label:
		cmp byte ptr[esp + 0x17], 0;
		ret;
		int 3;
		int 3;
	fend:
	}
}

static void __declspec(naked) ThrowCode()
{
	_asm {
		jmp fend;
		jmp short _1;
		cmp dword ptr[edi + 0x24], 47;
		je _2;
		test eax, eax;
		jne _2;
		_jmp(0x00464934);
	_2:
		mov ecx, [edi + 0x1c];
		push esi;
		_jmp(0x00464a88);
	_1:
		mov ecx, [edi + 0x1c];
		push esi;
		push ecx;
		_jmp(0x00464c2d);
		int 3;
		int 3;
	fend:
	}
}

static void __declspec(naked) CatDirCode()
{
	_asm {
		jmp fend;
		cmp eax, 52;
		jne short _1;
	_3:
		fld dword ptr ds : [0x006799e8];
		ret;
	_1:
		cmp eax, 28;
		jne short _2;
		cmp edx, 1;
		je short _3;
	_2:
		fld dword ptr ds : [0x006793e0];
		ret;
		int 3;
		int 3;
	fend:
	}
}

static void __declspec(naked) SplitCode()
{
	_asm {
		jmp fend;
		jmp short _1;
		mov ecx, [edi + 0x1c];
		push ecx;
		push edi;
		xor ecx, ecx;
		_call(0x004675c0);
		test eax, eax;
		jne _2;
		_jmp(0x00464934);
	_2:
		push eax;
		mov ecx, [edi + 0x1c];
		push 0;
		push ecx;
		push eax;
		push edi;
		_call(0x00466e00);
		pop eax;
		mov edx, [edi + 0x1c];
		push 1;
		push edx;
		push eax;
		push edi;
		_call(0x00466e00);
		_jmp(0x00464934);
	_1:
		mov esi, 3;
		_jmp(0x00464b5a);
		int 3;
		int 3;
	fend:
	}
}

static void __declspec(naked) ZTimerCode()
{
	_asm {
		jmp fend;
		mov ecx, 0xffffffff;
		cmp[edi + 0x559c], ecx;
		ja _1;
		dec dword ptr ds : [edi + 0x559c];
		ret;
	_1:
		mov[edi + 0x559c], ecx;
		ret;
		int 3;
		int 3;
	fend:
	}
}

static void __declspec(naked) GetHeadRowsCode()
{
	_asm {
		jmp fend;
		mov eax, ds:[DATA_ADDR];
		mov eax, [eax + OFFSET_1];
		mov eax, [eax + 0x554c];
		cmp eax, 2;
		je _6;
		cmp eax, 3;
		jne _5;
	_6:
		mov eax, 6;
		jmp label;
	_5:
		mov eax, 5;
	label:
		ret;
		int 3;
		int 3;
	fend:
	}
}

static void __declspec(naked) GetRVRowsCode()
{
	_asm {
		jmp fend;
		mov eax, ds:[DATA_ADDR];
		mov eax, [eax + OFFSET_1];
		mov eax, [eax + 0x554c];
		cmp eax, 2;
		je _6;
		cmp eax, 3;
		jne _5;
	_6:
		mov eax, 5;
		jmp label;
	_5:
		mov eax, 4;
	label:
		ret;
		int 3;
		int 3;
	fend:
	}
}

static void __declspec(naked) DoorRowsCode()
{
	_asm {
		jmp fend;
		mov eax, ds:[DATA_ADDR];
		mov eax, [eax + OFFSET_1];
		mov eax, [eax + 0x554c];
		cmp eax, 2;
		je _6;
		cmp eax, 3;
		jne _5;
	_6:
		mov eax, 6;
		jmp label;
	_5:
		mov eax, 5;
	label:
		inc edi;
		cmp edi, eax;
		ret;
		int 3;
		int 3;
	fend:
	}
}

void PVZ_1_0::InitExtraCode()
{
#define WRITE_CODE(f) \
	WriteArrayMemory(GET_ADDR(f) + HEAD_OF(f), SIZE_OF(f), temp), \
	WriteArrayMemory(CallCode, sizeof(CallCode), Caller)

	DWORD temp = ReadMemory(4, 0x00426fb7);
	bool b = (temp != 0xcccccccc);
	if (!b)
	{
		temp = (DWORD)VirtualAllocEx(GetHandle(), NULL, 4096 * 2, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if (temp)
			WriteMemory(temp, 4, 0x00426fb7);
	}
	DWORD Caller;
	/*传送门*/
	if (!b)
	{
		Caller = 0x0042706c;
		static unsigned char CallCode[] = { 0xb9, 4, 0, 0, 0, 0xe8, 0, 0, 0, 0 };
		(DWORD&)CallCode[6] = temp - Caller - 10;
		WRITE_CODE(DoorCode);
	}
	temp += SIZE_OF(DoorCode);
	/*行判定*/
	eCode.Row = temp;
	if (!b)
	{
		Caller = 0x004676c2;
		static unsigned char CallCode[] = { 0xe8, 0, 0, 0, 0, 0x90 };
		(DWORD&)CallCode[1] = temp - Caller - 5;
		WRITE_CODE(RowCode);
	}
	temp += SIZE_OF(RowCode);
	/*列判定*/
	eCode.Col = temp;
	if (!b)
	{
		Caller = 0x004677da;
		static unsigned char CallCode[] = { 0xe8, 0, 0, 0, 0, 0x90 };
		(DWORD&)CallCode[1] = temp - Caller - 5;
		WRITE_CODE(ColCode);
	}
	temp += SIZE_OF(ColCode);
	/*行伤害判定*/
	eCode.RHurt = temp;
	if (!b)
	{
		Caller = 0x0045ed6e;
		static unsigned char CallCode[] = { 0xe8, 0, 0, 0, 0, 0x90 };
		(DWORD&)CallCode[1] = temp - Caller - 5;
		WRITE_CODE(RHurtCode);
	}
	temp += SIZE_OF(RHurtCode);
	/*列伤害判定*/
	eCode.CHurt = temp;
	if (!b)
	{
		Caller = 0x0045ede2;
		static unsigned char CallCode[] = { 0xe8, 0, 0, 0, 0, 0x90 };
		(DWORD&)CallCode[1] = temp - Caller - 5;
		WRITE_CODE(CHurtCode);
	}
	temp += SIZE_OF(CHurtCode);
	/*香蒲免行判定*/
	eCode.CatR = temp;
	if (!b)
	{
		Caller = 0x00467680;
		static unsigned char CallCode[] = { 0xe8, 0, 0, 0, 0 };
		(DWORD&)CallCode[1] = temp - Caller - 5;
		WRITE_CODE(CatRCode);
	}
	temp += SIZE_OF(CatRCode);
	/*香蒲免列判定*/
	eCode.CatC = temp;
	if (!b)
	{
		Caller = 0x004677c0;
		static unsigned char CallCode[] = { 0xe8, 0, 0, 0, 0 };
		(DWORD&)CallCode[1] = temp - Caller - 5;
		WRITE_CODE(CatCCode);
	}
	temp += SIZE_OF(CatCCode);
	/*投手特殊处理*/
	eCode.Throw = temp;
	if (!b)
	{
		Caller = 0x00464c28;
		static unsigned char CallCode[] = { 0xe9, 0, 0, 0, 0 };
		(DWORD&)CallCode[1] = temp - Caller - 5;
		WRITE_CODE(ThrowCode);
	}
	temp += SIZE_OF(ThrowCode);
	/*猫式全屏子弹方向处理*/
	eCode.CatDir = temp;
	if (!b)
	{
		Caller = 0x00467386;
		static unsigned char CallCode[] = { 0xe8, 0, 0, 0, 0, 0x90 };
		(DWORD&)CallCode[1] = temp - Caller - 5;
		WRITE_CODE(CatDirCode);
	}
	temp += SIZE_OF(CatDirCode);
	/*裂荚处理*/
	eCode.Split = temp;
	if (!b)
	{
		Caller = 0x00464b55;
		static unsigned char CallCode[] = { 0xe9, 0, 0, 0, 0 };
		(DWORD&)CallCode[1] = temp - Caller - 5;
		WRITE_CODE(SplitCode);
	}
	temp += SIZE_OF(SplitCode);
	/*刷怪倒计时*/
	eCode.ZTimer = temp;
	if (!b)
	{
		Caller = 0x00413e45;
		static unsigned char CallCode[] = { 0xe8, 0, 0, 0, 0, 0x90, 0x90 };
		(DWORD&)CallCode[1] = temp - Caller - 5;
		WRITE_CODE(ZTimerCode);
	}
	temp += SIZE_OF(ZTimerCode);
	/*僵博吐球行*/
	if (!b)
	{
		Caller = 0x00535484;
		static unsigned char CallCode[] = { 0xe8, 0, 0, 0, 0 };
		(DWORD&)CallCode[1] = temp - Caller - 5;
		WRITE_CODE(GetHeadRowsCode);
	}
	temp += SIZE_OF(GetHeadRowsCode);
	if (!b)
	{
		Caller = 0x00534aeb;
		static unsigned char CallCode[] = { 0xe8, 0, 0, 0, 0 };
		(DWORD&)CallCode[1] = temp - Caller - 5;
		WRITE_CODE(GetRVRowsCode);
	}
	temp += SIZE_OF(GetRVRowsCode);
	/*传送门行*/
	if (!b)
	{
		Caller = 0x00427535;
		static unsigned char CallCode[] = { 0xe8, 0, 0, 0, 0, 0x90 };
		(DWORD&)CallCode[1] = temp - Caller - 5;
		WRITE_CODE(DoorRowsCode);
	}
	temp += SIZE_OF(DoorRowsCode);


	eCode.Thread = temp;
	return;
}

void PVZ_1_0::StartDoor(bool b)
{
	if (b)
	{
		if (InGame() && ReadMemory(4, DATA_ADDR, 1, MODE_OFFSET + 4) > 2)
		{
			bool HasDoor = false;
			GetItems();
			for (auto& ri : vi)
			{
				if (ri.Type == 4 || ri.Type == 5)
				{
					HasDoor = true;
					break;
				}
			}
			if (!HasDoor)
			{
				SetDoor(0, 2, 1, 9, 3, 9, 4, 2);
			}
		}
		WriteMemory(0x70, 1, 0x00467665);
		WriteMemory(0x70, 1, 0x004248ce);
		WriteMemory(0x70, 1, 0x0041ffb4);
	}
	else
	{
		WriteMemory(0x75, 1, 0x00467665);
		WriteMemory(0x75, 1, 0x004248ce);
		WriteMemory(0x75, 1, 0x0041ffb4);
	}
}

void PVZ_1_0::StableDoor(bool b)
{
	if (b)
	{
		WriteMemory(0, 1, 0x004276dd);
	}
	else
	{
		WriteMemory(-1, 1, 0x004276dd);
	}
}

void PVZ_1_0::SetDoor(int b1r, int b1c, int b2r, int b2c, int w1r, int w1c, int w2r, int w2c)
{
	if (InGame())
	{
		clear();
		GetItems();
		for (auto& ri : vi)
		{
			if (ri.Type == 4 || ri.Type == 5)
			{
				mov_exx(RegType::ESI, ri.addr);
				call(0x0044d000);
			}
		}
		WriteMemory(b1c, 1, 0x00426fe2);
		WriteMemory(b1r, 1, 0x00426fe9);
		WriteMemory(b2c, 1, 0x0042700d);
		WriteMemory(b2r, 1, 0x00427014);
		WriteMemory(w1c, 1, 0x0042703d);
		WriteMemory(w1r, 1, 0x00427044);
		WriteMemory(w2c, 1, 0x00427068);
		WriteMemory(w2r, 1, 0x0042706d);
		mov_exx_dword_ptr(RegType::EDI, DATA_ADDR);
		mov_exx_dword_ptr_exx_add_dword(RegType::EDI, OFFSET_1);
		mov_exx_dword_ptr_exx_add_dword(RegType::EDI, OFFSET_2);
		call(0x00426fc0);
		RunAsm();
		WriteMemory(2, 1, 0x00426fe2);
		WriteMemory(0, 1, 0x00426fe9);
		WriteMemory(9, 1, 0x0042700d);
		WriteMemory(1, 1, 0x00427014);
		WriteMemory(9, 1, 0x0042703d);
		WriteMemory(3, 1, 0x00427044);
		WriteMemory(2, 1, 0x00427068);
		WriteMemory(4, 1, 0x0042706d);
	}
}

void PVZ_1_0::CornNoWait(bool b)
{
	if (b)
	{
		WriteMemory(0x80, 1, 0x0046103b);
	}
	else
	{
		WriteMemory(0x85, 1, 0x0046103b);
	}
}

void PVZ_1_0::MagnetNoWait(bool b)
{
	if (b)
	{
		WriteMemory(0x80, 1, 0x00461e37);
	}
	else
	{
		WriteMemory(0x85, 1, 0x00461e37);
	}
}

void PVZ_1_0::PotatoNoWait(bool b)
{
	if (b)
	{
		WriteMemory(0x80, 1, 0x0045fe54);
	}
	else
	{
		WriteMemory(0x85, 1, 0x0045fe54);
	}
}

void PVZ_1_0::MouthNoWait(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x00461565);
	}
	else
	{
		WriteMemory(0x75, 1, 0x00461565);
	}
}

void PVZ_1_0::PStrong()
{
	WriteMemory(0x004046, 3, 0x0052fcf1);
	WriteMemory(0x909090, 3, 0x0046cfeb);
	WriteMemory(0x909090, 3, 0x0046d7a6);
	WriteMemory(0xeb, 1, 0x0052e93b);
	WriteMemory(0xeb, 1, 0x0041cc2f);
	WriteMemory(0xeb, 1, 0x005276ea);
	WriteMemory(0x70, 1, 0x0045ee0a);
	WriteMemory(0, 1, 0x0045ec66);
}

void PVZ_1_0::PNormal()
{
	WriteMemory(0xfc4046, 3, 0x0052fcf1);
	WriteMemory(0x405029, 3, 0x0046cfeb);
	WriteMemory(0x404e29, 3, 0x0046d7a6);
	WriteMemory(0x74, 1, 0x0052e93b);
	WriteMemory(0x74, 1, 0x0041cc2f);
	WriteMemory(0x75, 1, 0x005276ea);
	WriteMemory(0x75, 1, 0x0045ee0a);
	WriteMemory(-32, 1, 0x0045ec66);
}

void PVZ_1_0::PWeak()
{
	WriteMemory(0x004066, 3, 0x0052fcf1);
	WriteMemory(0x404029, 3, 0x0046cfeb);
	WriteMemory(0x407629, 3, 0x0046d7a6);
	WriteMemory(0x74, 1, 0x0052e93b);
	WriteMemory(0x74, 1, 0x0041cc2f);
	WriteMemory(0x75, 1, 0x005276ea);
	WriteMemory(0x70, 1, 0x0045ee0a);
	WriteMemory(-32, 1, 0x0045ec66);
}

void PVZ_1_0::NoMark(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x0041d79e);
	}
	else
	{
		WriteMemory(0x75, 1, 0x0041d79e);
	}
}

void PVZ_1_0::NoSleep(bool b)
{
	if (b)
	{
		WriteMemory(0xeb, 1, 0x0045de8e);
		if (InGame())
		{
			clear();
			GetPlants();
			for (auto& rp : vp)
			{
				if (rp.Sleeping)
				{
					mov_exx(RegType::EAX, rp.addr);
					push_byte(0);
					call(0x0045e860);
				}
			}
			RunAsm();
		}
	}
	else
	{
		WriteMemory(0x74, 1, 0x0045de8e);
	}
}

void PVZ_1_0::StrongWind(bool b)
{
	if (b)
	{
		WriteMemory(0xeb, 1, 0x00466601);
	}
	else
	{
		WriteMemory(0x74, 1, 0x00466601);
	}
}

void PVZ_1_0::StrongBean(bool b)
{
	if (b)
	{
		WriteMemory(0xc3, 1, 0x0046e429);
	}
	else
	{
		WriteMemory(0xe9, 1, 0x0046e429);
	}
}

void PVZ_1_0::Umbrella(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x0041d3f8);
	}
	else
	{
		WriteMemory(0x75, 1, 0x0041d3f8);
	}
}

void PVZ_1_0::NowMouse(int mouse)
{
	WriteMemory(mouse, 4, 0x006a9ec0, 3, 0x768, 0x138, 0x30); //数字,字节,基址,偏移量,偏移
}

void PVZ_1_0::ChKiller(bool b)
{
	if (b)
	{
		WriteMemory(0x90, 1, 0x004613CA);
		WriteMemory(0x90, 1, 0x004613CB);
		WriteMemory(0x90, 1, 0x004613CC);
		WriteMemory(0x90, 1, 0x004613CD);
		WriteMemory(0x90, 1, 0x004613CE);
		WriteMemory(0x90, 1, 0x004613CF);
	}
	else
	{
		WriteMemory(0x0F, 1, 0x004613CA);
		WriteMemory(0x85, 1, 0x004613CB);
		WriteMemory(0x3C, 1, 0x004613CC);
		WriteMemory(0x01, 1, 0x004613CD);
		WriteMemory(0x00, 1, 0x004613CE);
		WriteMemory(0x00, 1, 0x004613CF);
	}
}

void PVZ_1_0::PlantsPaper(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x00465DF2);
	}
	else
	{
		WriteMemory(0x74, 1, 0x00465DF2);
	}
}

void PVZ_1_0::CheatMode(bool b)
{
	if (b)
	{
		WriteMemory(1, 4, 0x006A9EC0, 1, 0x814);
	}
	else
	{
		WriteMemory(0, 4, 0x006A9EC0, 1, 0x814);
	}
}

void PVZ_1_0::PlantsZipBoom(bool b)
{
	if (b)
	{
		WriteMemory(0xEB, 1, 0x00462B8E);
		WriteMemory(0x6D, 1, 0x00462B8F);
		WriteMemory(0x8B, 1, 0x00462B90);

		WriteMemory(0x30, 1, 0x00466ADF);
		WriteMemory(0xFC, 1, 0x00466AE0);
		WriteMemory(0xFF, 1, 0x00466AE1);
		WriteMemory(0xFF, 1, 0x00466AE2);
	}
	else
	{
		WriteMemory(0x75, 1, 0x00462B8E);
		WriteMemory(0x1E, 1, 0x00462B8F);
		WriteMemory(0x8B, 1, 0x00462B90);

		WriteMemory(0x8A, 1, 0x00466ADF);
		WriteMemory(0x0, 1, 0x00466AE0);
		WriteMemory(0x0, 1, 0x00466AE1);
		WriteMemory(0x0, 1, 0x00466AE2);
	}
}

void PVZ_1_0::FunnyNut(bool b)
{
	if (b)
	{
		WriteMemory(0xEB, 1, 0x0045DDA7);
	}
	else
	{
		WriteMemory(0x74, 1, 0x0045DDA7);
	}
}

void PVZ_1_0::CrazyPlants(bool b)
{
	if (b)
	{
		WriteMemory(0x90, 1, 0x00464A96);
		WriteMemory(0x90, 1, 0x00464A97);
		WriteMemory(0x90, 1, 0x00464A98);
		WriteMemory(0x90, 1, 0x00464A99);
		WriteMemory(0x90, 1, 0x00464A9A);
		WriteMemory(0x90, 1, 0x00464A9B);
	}
	else
	{
		WriteMemory(0x0F, 1, 0x00464A96);
		WriteMemory(0x85, 1, 0x00464A97);
		WriteMemory(0x98, 1, 0x00464A98);
		WriteMemory(0xFE, 1, 0x00464A99);
		WriteMemory(0xFF, 1, 0x00464A9A);
		WriteMemory(0xFF, 1, 0x00464A9B);
	}
}

void PVZ_1_0::KillAllPlants()
{
	WriteMemory(0x70, 1, 0x0041BB2E);
	Sleep(100);
	WriteMemory(0x74, 1, 0x0041BB2E);
}

void PVZ_1_0::ChHitNum(int num)
{
	WriteMemory(num, 1, 0x004614DD);
}

void PVZ_1_0::MeiHuoHanBingGu(bool b)
{
	if (b)
	{
		WriteMemory(0x83, 1, 0x00532425);
		WriteMemory(0xC0, 1, 0x00532426);
		WriteMemory(0x01, 1, 0x00532427);
		WriteMemory(0x90, 1, 0x00532428);
		WriteMemory(0x90, 1, 0x00532429);
		WriteMemory(0xB8, 1, 0x0053242C);
	}
	else
	{
		WriteMemory(0x05, 1, 0x00532425);
		WriteMemory(0x60, 1, 0x00532426);
		WriteMemory(0x01, 1, 0x00532427);
		WriteMemory(0x0, 1, 0x00532428);
		WriteMemory(0x0, 1, 0x00532429);
		WriteMemory(0xB4, 1, 0x0053242C);
	}
}

void PVZ_1_0::HuangYouHanBingGu(bool b)
{
	if (b)
	{
		WriteMemory(0x83, 1, 0x00532425);
		WriteMemory(0xC0, 1, 0x00532426);
		WriteMemory(0x01, 1, 0x00532427);
		WriteMemory(0x90, 1, 0x00532428);
		WriteMemory(0x90, 1, 0x00532429);
		WriteMemory(0xB0, 1, 0x0053242C);
	}
	else
	{
		WriteMemory(0x05, 1, 0x00532425);
		WriteMemory(0x60, 1, 0x00532426);
		WriteMemory(0x01, 1, 0x00532427);
		WriteMemory(0x0, 1, 0x00532428);
		WriteMemory(0x0, 1, 0x00532429);
		WriteMemory(0xB4, 1, 0x0053242C);
	}
}

void PVZ_1_0::BossLife(int life)
{
	WriteMemory(life, 4, 0x006a9ec0, 3, 0x768, 0x90, 0xC8); //数字,字节,基址,偏移量,偏移
}

void PVZ_1_0::SetZombieTimer(int time)
{
	WriteMemory(time, 4, 0x006a9ec0, 3, 0x768, 0x90, 0x114); //数字,字节,基址,偏移量,偏移
}

void PVZ_1_0::ShowHeadTimer(int time)
{
	WriteMemory(time, 4, 0x006a9ec0, 3, 0x768, 0x90, 0x13C); //数字,字节,基址,偏移量,偏移
}

void PVZ_1_0::FirePea(int Pea, int IcePea)
{
	WriteMemory(Pea, 4, 0x0046ECCB);
	WriteMemory(IcePea, 4, 0x0046EE15);
	WriteMemory(0x0, 1, 0x0046EDE2);
}

void PVZ_1_0::NoCD(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x00487296);
		WriteMemory(0xeb, 1, 0x00488250);
	}
	else
	{
		WriteMemory(0x7e, 1, 0x00487296);
		WriteMemory(0x75, 1, 0x00488250);
	}
}

void PVZ_1_0::LockScoop(bool b)
{
	if (b)
	{
		WriteMemory(0x39, 1, 0x004123a3);
		WriteMemory(6, 4, DATA_ADDR, 3, OFFSET_1, 0x138, 0x30);
	}
	else
	{
		WriteMemory(0x89, 1, 0x004123a3);
	}
}

void PVZ_1_0::AnyMove(bool b)
{
	if (b)
	{
		WriteMemory(0x81, 1, 0x004208fb);
		WriteMemory(0x81, 1, 0x00420533);
	}
	else
	{
		WriteMemory(0x85, 1, 0x004208fb);
		WriteMemory(0x85, 1, 0x00420533);
	}
}

void PVZ_1_0::NoPurple(bool b)
{
	if (b)
	{
		WriteMemory(0xc301b0, 3, 0x0041d7d0);
		WriteMemory(0xeb, 1, 0x0040e477);
	}
	else
	{
		WriteMemory(0xf88351, 3, 0x0041d7d0);
		WriteMemory(0x74, 1, 0x0040e477);
	}
}

void PVZ_1_0::LockButter(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x00464bd6);
	}
	else
	{
		WriteMemory(0x75, 1, 0x00464bd6);
	}
}

void PVZ_1_0::LockCorn(bool b)
{
	if (b)
	{
		WriteMemory(0xeb, 1, 0x00464bd6);
	}
	else
	{
		WriteMemory(0x75, 1, 0x00464bd6);
	}
}

void PVZ_1_0::BoomIm()
{
	WriteMemory(0x80, 1, 0x00526afc);
	WriteMemory(0x80, 1, 0x005275dd);
}

void PVZ_1_0::BoomNormal()
{
	WriteMemory(0x8f, 1, 0x00526afc);
	WriteMemory(0x85, 1, 0x005275dd);
}

void PVZ_1_0::BoomNever()
{
	WriteMemory(0x81, 1, 0x00526afc);
	WriteMemory(0x81, 1, 0x005275dd);
}

void PVZ_1_0::VisiableNo()
{
	WriteMemory(0x70, 1, 0x0052e357);
	WriteMemory(0x70, 1, 0x0053402b);
}

void PVZ_1_0::VisiableNormal()
{
	WriteMemory(0x75, 1, 0x0052e357);
	WriteMemory(0x75, 1, 0x0053402b);
}

void PVZ_1_0::VisiableYes()
{
	WriteMemory(0xeb, 1, 0x0052e357);
	WriteMemory(0xeb, 1, 0x0053402b);
}

void PVZ_1_0::ZStrong()
{
	WriteMemory(0xc0, 1, 0x00531045);
	WriteMemory(0x90909090, 4, 0x0053130f);
	WriteMemory(0xd233c033, 4, 0x00530c9b);
	WriteMemory(0x81, 1, 0x00532ba1);
	WriteMemory(0xeb, 1, 0x0046144a);
}

void PVZ_1_0::ZNormal()
{
	WriteMemory(0xc8, 1, 0x00531045);
	WriteMemory(0x20247c2b, 4, 0x0053130f);
	WriteMemory(0xc28b027c, 4, 0x00530c9b);
	WriteMemory(0x8d, 1, 0x00532ba1);
	WriteMemory(0x74, 1, 0x0046144a);
}

void PVZ_1_0::ZWeak()
{
	WriteMemory(0xc9, 1, 0x00531045);
	WriteMemory(0x9090ff2b, 4, 0x0053130f);
	WriteMemory(0xc28bd08b, 4, 0x00530c9b);
	WriteMemory(0x80, 1, 0x00532ba1);
	WriteMemory(0x74, 1, 0x0046144a);
}

void PVZ_1_0::NoSlow(bool b)
{
	if (b)
	{
		WriteMemory(0x90c033, 3, 0x0052b448);
	}
	else
	{
		WriteMemory(0xffc083, 3, 0x0052b448);
	}
}

void PVZ_1_0::NoButter(bool b)
{
	if (b)
	{
		WriteMemory(0x90c033, 3, 0x0052b464);
	}
	else
	{
		WriteMemory(0xffc083, 3, 0x0052b464);
	}
}

void PVZ_1_0::No3zGroup(bool b)
{
	if (b)
	{
		WriteMemory(0xeb, 1, 0x0042694a);
		WriteMemory(0xeb, 1, 0x00413083);
	}
	else
	{
		WriteMemory(0x75, 1, 0x0042694a);
		WriteMemory(0x75, 1, 0x00413083);
	}
}

void PVZ_1_0::NoIMP(bool b)
{
	if (b)
	{
		WriteMemory(0xeb, 1, 0x00527205);
	}
	else
	{
		WriteMemory(0x7d, 1, 0x00527205);
	}
}

void PVZ_1_0::NoICE(bool b)
{
	if (b)
	{
		WriteMemory(0xc3, 1, 0x0052a7b0);
		WriteMemory(0xeb, 1, 0x0041f79a);
		for (int i = 0; i < 6; ++i)
		{
			WriteMemory(1, 4, DATA_ADDR, 2, OFFSET_1, 0x624 + i * 4);
		}
	}
	else
	{
		WriteMemory(0x51, 1, 0x0052a7b0);
		WriteMemory(0x75, 1, 0x0041f79a);
	}
}

void PVZ_1_0::ZEatable(bool b)
{
	if (b)
	{
		WriteMemory(0, 1, 0x00461457);
	}
	else
	{
		WriteMemory(1, 1, 0x00461457);
	}
}

void PVZ_1_0::StopZTimer(bool b)
{
	if (b)
	{
		WriteMemory(0xc3, 1, eCode.ZTimer);
	}
	else
	{
		WriteMemory(0xb9, 1, eCode.ZTimer);
	}
}

void PVZ_1_0::StopZombies(bool b)
{
	if (b)
	{
		WriteMemory(0x54, 1, 0x0052ab2b);
		WriteMemory(0x54, 1, 0x0052ab34);
	}
	else
	{
		WriteMemory(0x64, 1, 0x0052ab2b);
		WriteMemory(0x44, 1, 0x0052ab34);
	}
}

void PVZ_1_0::StopBoss(bool b)
{
	if (b)
	{
		WriteMemory(0xc3, 1, 0x00536080);
	}
	else
	{
		WriteMemory(0x83, 1, 0x00536080);
	}
}

void PVZ_1_0::BalloonBoom(bool b)
{
	if (b)
	{
		WriteMemory(0x70, 1, 0x00525cab);
		WriteMemory(0x70, 1, 0x00525cc6);
	}
	else
	{
		WriteMemory(0x75, 1, 0x00525cab);
		WriteMemory(0x74, 1, 0x00525cc6);
	}
}

void PVZ_1_0::ZTimerSpeed(int value)
{
	WriteMemory(value, 4, eCode.ZTimer + 1);
}

void PVZ_1_0::GatherZombie(bool b, float pos)
{
	if (b)
	{
		static unsigned char code[] = { 0xc7, 0x46, 0x2c, 0, 0, 0, 0, 0xeb, 0x23 };
		(DWORD&)code[3] = (DWORD&)pos;
		WriteMemory(0x32, 1, 0x0052aa4a);
		WriteArrayMemory(code, 0x0052ab18);
	}
	else
	{
		static unsigned char code[] = { 0xe8, 0xc3, 0x13, 0, 0, 0x84, 0xc0, 0x75, 0x0f };
		WriteMemory(0x84, 1, 0x0052aa4a);
		WriteArrayMemory(code, 0x0052ab18);
	}
}

void PVZ_1_0::KillAllZombies()
{
	GetZombies();
	for (auto& rz : vz)
	{
		WriteMemory(3, 4, rz.addr + 0x28);
	}
}

void PVZ_1_0::VoidAllZombies()
{
	GetZombies();
	for (auto& rz : vz)
	{
		WriteMemory(1, 4, rz.addr + 0x28);
	}
}

void PVZ_1_0::BlackAllZombies()
{
	GetZombies();
	for (auto& rz : vz)
	{
		WriteMemory(2, 4, rz.addr + 0x28);
	}
}

void PVZ_1_0::ZALife(int type, int life)
{
	if (type == 0)
	{
		WriteMemory(life, 4, 0x00522892);
	}
	if (type == 1)
	{
		WriteMemory(life, 4, 0x0052292B);
	}
	if (type == 2)
	{
		WriteMemory(life, 4, 0x0052337D);
	}
	if (type == 3)
	{
		WriteMemory(life, 4, 0x00522949);
	}
	if (type == 4)
	{
		WriteMemory(life, 4, 0x00522BB0);
	}
	if (type == 5)
	{
		WriteMemory(life, 4, 0x005234BF);
	}
	if (type == 6)
	{
		WriteMemory(life, 4, 0x00522BEF);
	}
}

void PVZ_1_0::ZHit(int type, int hit)
{
	if (type == 0)
	{
		WriteMemory(hit, 1, 0x0052FCF3);
	}
	if (type == 1)
	{
		WriteMemory(hit, 1, 0x0045EC66);
	}
	if (type == 2)
	{
		WriteMemory(hit, 4, 0x0069F234);
	}
	if (type == 3)
	{
		WriteMemory(hit, 4, 0x0069F264);
	}
}

void PVZ_1_0::FastGetPlant(bool b)
{
	if (b)
	{
		WriteMemory(0, 4, 0x00525127);
	}
	else
	{
		WriteMemory(300, 4, 0x00525127);
	}
}

void PVZ_1_0::BungeeStop(bool b)
{
	if (b)
	{
		WriteMemory(235, 1, 0x0052AF6E);
	}
	else
	{
		WriteMemory(117, 1, 0x0052AF6E);
	}
}

void PVZ_1_0::BungeeFunny(bool b)
{
	if (b)
	{
		WriteMemory(10, 4, 0x00525120);
	}
	else
	{
		WriteMemory(6, 4, 0x00525120);
	}
}

void PVZ_1_0::GraveSpawnZCD(int CD)
{
	WriteMemory(CD, 4, 0x004263FD);
}

void PVZ_1_0::GraveSpawnZCT(int CT)
{
	WriteMemory(CT, 4, 0x00426193);
}

void PVZ_1_0::GraveSpawnZSP(int SP)
{
	WriteMemory(SP + 4115762432, 4, 0x0042630B);
}

void PVZ_1_0::GraveSpawnCT(int CT)
{
	WriteMemory(CT, 4, 0x00426044);
	WriteMemory(CT, 4, 0x00426050);
}

void PVZ_1_0::SporeShoot(bool b)
{
	if (b)
	{
		WriteMemory(-28528, 2, 0x00464895);
	}
	else
	{
		WriteMemory(10613, 2, 0x00464895);
	}
}

void PVZ_1_0::LightPlants(bool b)
{ 
	if (b)
	{
		static unsigned char _3_code[] = { 0xC6,0x80,0x45,0x01,0x00,0x00,0x01 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x0040EAEA);
	}
	else
	{
		static unsigned char _3_code[] = { 0xC6,0x80,0x45,0x01,0x00,0x00,0x00 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x0040EAEA);
	}
}

void PVZ_1_0::CantSeeZoms(bool b)
{
	if (b)
	{
		static unsigned char _3_code[] = { 0x80,0xBF,0x44,0x01,0x00,0x00,0x01 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x00463155);
	}
	else
	{
		static unsigned char _3_code[] = { 0x80,0xBF,0x44,0x01,0x00,0x00,0x00 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x00463155);
	}
}

void PVZ_1_0::InvShoot(bool b)
{
	if (b)
	{
		WriteMemory(-28528, 2, 0x00467531);
		WriteMemory(-1869574000, 4, 0x0046C783);
	}
	else
	{
		WriteMemory(-4391, 2, 0x00467531);
		WriteMemory(472138969, 4, 0x0046C783);
	}
}

void PVZ_1_0::SlowShoot(bool b)
{
	if (b)
	{
		static unsigned char _3_code[] = { 0xB8,0x08,0x00,0x00,0x00,0x90 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x0046D89D);
	}
	else
	{
		static unsigned char _3_code[] = { 0x8B,0x43,0x58,0x83,0xF8,0x06 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x0046D89D);
	}
}

void PVZ_1_0::FastSun(bool b)
{
	if (b)
	{
		WriteMemory(-28528, 2, 0x00413BC9);
	}
	else
	{
		WriteMemory(-15613, 2, 0x00413BC9);
	}
}

void PVZ_1_0::ThisPult(bool b)
{
	if (b)
	{
		WriteMemory(-1869574000, 4, 0x0052A5E2);
	}
	else
	{
		WriteMemory(136594569, 4, 0x0052A5E2);
	}
}

void PVZ_1_0::FastPult(bool b)
{
	if (b)
	{
		WriteMemory(-1869574000, 4, 0x0052A5E7);
	}
	else
	{
		WriteMemory(69485787, 4, 0x0052A5E7);
	}
}

void PVZ_1_0::FastSqa(bool b)
{
	if (b)
	{
		static unsigned char _3_code[] = { 0x90,0x90,0x90,0x90,0x90,0x90,0x90 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x00460A3A);
	}
	else
	{
		static unsigned char _3_code[] = { 0xC7,0x46,0x54,0x50,0x00,0x00,0x00 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x00460A3A);
	}
}

void PVZ_1_0::FunnySqa(bool b)
{
	if (b)
	{
		WriteMemory(-28528, 2, 0x00460AC1);
	}
	else
	{
		WriteMemory(15221, 2, 0x00460AC1);
	}
}

void PVZ_1_0::GrassPlant(bool b)
{
	if (b)
	{
		WriteMemory(-28528, 2, 0x004633C9);
	}
	else
	{
		WriteMemory(2165, 2, 0x004633C9);
	}
}

void PVZ_1_0::InvBull(bool b)
{
	if (b)
	{
		static unsigned char _3_code[] = { 0x90,0x90,0x90,0x90,0x90,0x90,0x90 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x0052E39E);
	}
	else
	{
		static unsigned char _3_code[] = { 0x83,0xBB,0xB0,0x00,0x00,0x00,0x00 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x0052E39E);
	}
}

void PVZ_1_0::FastGar(bool b)
{
	if (b)
	{
		WriteMemory(21621, 2, 0x0052F103);
	}
	else
	{
		WriteMemory(21620, 2, 0x0052F103);
	}
}

void PVZ_1_0::StuckIMP(bool b)
{
	if (b)
	{
		static unsigned char _3_code[] = { 0x90,0x90,0x90,0x90,0x90,0x90,0x90 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x005270EB);
	}
	else
	{
		static unsigned char _3_code[] = { 0xC7,0x46,0x28,0x47,0x00,0x00,0x00 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x005270EB);
	}
}

void PVZ_1_0::LevelState(int state)
{
	WriteMemory(state + 1, 4, 0x006a9ec0, 1, 0x7fc);
}

void PVZ_1_0::StandSmash(bool b)
{
	if (b)
	{
		WriteMemory(12661, 2, 0x0052E94D);
		static unsigned char _3_code[] = { 0x3B,0x51,0x28 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x0052E953);
		WriteMemory(-28528, 2, 0x0052E94D);
	}
	else
	{
		WriteMemory(12661, 2, 0x0052E94D);
	}
}

void PVZ_1_0::StraightSmash(bool b)
{
	if (b)
	{
		WriteMemory(12661, 2, 0x0052E94D);
		static unsigned char _3_code[] = { 0x3B,0x51,0x28 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x0052E953);
		static unsigned char _4_code[] = { 0x90,0x90,0x90 };
		WriteArrayMemory(_4_code, sizeof(_4_code), 0x0052E953);
	}
	else
	{
		static unsigned char _3_code[] = { 0x3B,0x51,0x28 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x0052E953);
	}
}

void PVZ_1_0::FullSmash(bool b)
{
	if (b)
	{
		WriteMemory(-28528, 2, 0x0052E7D6);
		WriteMemory(-28528, 2, 0x0052E956);
		WriteMemory(-28528, 2, 0x0052E94D);
	}
	else
	{
		WriteMemory(-12661, 2, 0x0052E7D6);
		WriteMemory(10357, 2, 0x0052E956);
		WriteMemory(12661, 2, 0x0052E94D);
	}
}

void PVZ_1_0::HitBeLight(bool b)
{
	if (b)
	{
		WriteMemory(-1869574000, 4, 0x0052AF8E);
	}
	else
	{
		WriteMemory(-11254141, 4, 0x0052AF8E);
	}
}

void PVZ_1_0::HitNoLight(bool b)
{
	if(b)
	{
		static unsigned char _3_code[] = { 0x90,0x90,0x90,0x90,0x90,0x90,0x90 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x005312EA);
	}
	else
	{
		static unsigned char _3_code[] = { 0xC7,0x45,0x54,0x19,0x00,0x00,0x00 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x005312EA);
	}
}

void PVZ_1_0::NoBroken(bool b)
{
	if (b)
	{
		static unsigned char _3_code[] = { 0x90,0x90,0x90,0x90,0x90,0x90 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x0052A4E6);
	}
	else
	{
		static unsigned char _3_code[] = { 0x8B,0xB3,0xC8,0x00,0x00,0x00 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x0052A4E6);
	}
}

void PVZ_1_0::DeadNoHead(bool b)
{
	if (b)
	{
		static unsigned char _3_code[] = { 0x90,0x90,0x90,0x90,0x90,0x90 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x0052A527);
	}
	else
	{
		static unsigned char _3_code[] = { 0x39,0x8B,0xC8,0x00,0x00,0x00 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x0052A527);
	}
}

void PVZ_1_0::VoidEat(bool b)
{
	if (b)
	{
		static unsigned char _3_code[] = { 144, 144, 144, 144, 116, 102, 131, 248, 76, 117 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x0052F261);
	}
	else
	{
		static unsigned char _3_code[] = { 198, 71, 81, 1, 116, 102, 131, 248, 76, 117 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x0052F261);
	}
}

void PVZ_1_0::VoidWalk(bool b)
{
	if (b)
	{
		static unsigned char _3_code[] = { 0x90, 0x90, 0x90, 0x90, 0x0F, 0x85, 0x87, 0x01, 0x00, 0x00 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x0052A613);
	}
	else
	{
		static unsigned char _3_code[] = { 0x80, 0x7E, 0x51, 0x00, 0x0F, 0x85, 0x87, 0x01,0x00, 0x00 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x0052A613);
	}
}

void PVZ_1_0::LongEat(bool b)
{
	if (b)
	{
		WriteMemory(-4130, 2, 0x0052C5CA);
	}
	else
	{
		WriteMemory(-5666, 2, 0x0052C5CA);
	}
}

void PVZ_1_0::LJNormalZ(bool b)
{
	if (b)
	{
		static unsigned char _3_code[] = { 0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x005227B5);
	}
	else
	{
		static unsigned char _3_code[] = { 0xC7,0x87,0xC8,0x00,0x00,0x00,0x0E,0x01,0x00,0x00 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x005227B5);
	}
}

void PVZ_1_0::HighIMP(bool b)
{
	if (b)
	{
		WriteMemory(405036253, 4, 0x00527074);
		static unsigned char _3_code[] = { 0xDC,0x05,0x50,0xA0,0x67,0x00 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x00526EEA);
	}
	else
	{
		static unsigned char _3_code[] = { 0xDC,0x25,0x50,0xA0,0x67,0x00 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x00526EEA);
	}
}

void PVZ_1_0::LongIMP(bool b)
{
	if (b)
	{
		WriteMemory(405036253, 4, 0x00527074);
		static unsigned char _3_code[] = { 0x90,0x90,0x90,0x90,0x90,0x90 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x00526EEA);
	}
	else
	{
		static unsigned char _3_code[] = { 0xDC,0x25,0x50,0xA0,0x67,0x00 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x00526EEA);
	}
}

void PVZ_1_0::ShitIMP(bool b)
{
	if (b)
	{
		WriteMemory(-1869574000, 4, 0x00527074);
	}
	else
	{
		WriteMemory(405036253, 4, 0x00527074);
	}
}

void PVZ_1_0::VoidIMP(bool b)
{
	if (b)
	{
		static unsigned char _3_code[] = { 0xDD,0x05,0xB8,0xA2,0x67,0x00 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x005270A3);
	}
	else
	{
		static unsigned char _3_code[] = { 0xDC,0x25,0xB8,0xA2,0x67,0x00 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x005270A3);
	}
}

void PVZ_1_0::HomeIMP(bool b)
{
	if (b)
	{
		WriteMemory(0x2D, 1, 0x005270A4);
	}
	else
	{
		WriteMemory(0x25, 1, 0x005270A4);
	}
}

void PVZ_1_0::FaGuoZom(bool b)
{
	if (b)
	{
		WriteMemory(-1869574000, 4, 0x0052BEEC);
	}
	else
	{
		WriteMemory(174356867, 4, 0x0052BEEC);
	}
}

void PVZ_1_0::HitBroken(bool b)
{
	if (b)
	{
		static unsigned char _3_code[] = { 0x90,0x90,0x90,0x90,0x90,0x90 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x0052A4E0);
	}
	else
	{
		static unsigned char _3_code[] = { 0x8B,0x8B,0xCC,0x00,0x00,0x00 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x0052A4E0);
	}
}

void PVZ_1_0::FastBungee(bool b)
{
	if (b)
	{
		WriteMemory(5237, 2, 0x00412F16);
	}
	else
	{
		WriteMemory(5236, 2, 0x00412F16);
	}
}

void PVZ_1_0::jumpingSqa(bool b)
{
	if (b)
	{
		static unsigned char _3_code[] = { 0x90,0x90,0x90,0x90,0x90,0x90,0x90 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x00460B53);
	}
	else
	{
		static unsigned char _3_code[] = { 0xC7,0x46,0x54,0x32,0x00,0x00,0x00 };
		WriteArrayMemory(_3_code, sizeof(_3_code), 0x00460B53);
	}
}

void PVZ_1_0::ZLife(int type, int life)
{
	if (type == 0)
	{
		WriteMemory(life, 4, 0x005227BB);
	}
	if (type == 1)
	{
		WriteMemory(life, 4, 0x00523530);
	}
	if (type == 2)
	{
		WriteMemory(life, 4, 0x00522DE1);
	}
	if (type == 3)
	{
		WriteMemory(life, 4, 0x00522D64);
	}
	if (type == 4)
	{
		WriteMemory(life, 4, 0x005227BB);
	}
	if (type == 5)
	{
		WriteMemory(life, 4, 0x00522FC7);
	}
	if (type == 6)
	{
		WriteMemory(life, 4, 0x00522BEF);
	}
	if (type == 7)
	{
		WriteMemory(life, 4, 0x00523300);
	}
	if (type == 8)
	{
		WriteMemory(life, 4, 0x0052296E);
	}
	if (type == 9)
	{
		WriteMemory(life, 4, 0x00522A1B);
	}
	if (type == 10)
	{
		WriteMemory(life, 4, 0x0052299C);
	}
	if (type == 11)
	{
		WriteMemory(life, 4, 0x00523D26);
	}
	if (type == 12)
	{
		if (life >= ReadMemory(4, 0x00523624))
		{
			WriteMemory(life, 4, 0x0052361E);
		}
		else
		{
			MessageBoxA(NULL, "你输入的数字太小了，需要输入比冒险僵王更大的数。", "注意", MB_OK);
		}
	}
	if (type == 13)
	{
		WriteMemory(life, 4, 0x0052382B);
	}
	if (type == 14)
	{
		WriteMemory(life, 4, 0x00523A87);
	}
	if (type == 15)
	{
		WriteMemory(life, 4, 0x0052395D);
	}
	if (type == 16)
	{
		WriteMemory(life, 4, 0x00523E4A);
	}
	if (type == 17)
	{
		WriteMemory(life, 4, 0x005235AC);
	}
}

void PVZ_1_0::ConfuseZombies()
{
	GetZombies();
	for (auto& rz : vz)
	{
		WriteMemory(1, 1, rz.addr + 0xb8);
	}
}

void PVZ_1_0::NaturalSeed(int* zombies, int znum)
{
	if (InGame())
	{
		int minzid = zombies[0];
		int minindex = 0;
		bool LowZ = (minzid == 0 || minzid == 26);
		for (int i = 1; i < znum; ++i)
		{
			if (zombies[i] < minzid)
			{
				minzid = zombies[i];
				minindex = i;
			}
			if (zombies[i] == 0 || zombies[i] == 26)
				LowZ = true;
		}
		if (!LowZ)
		{
			zombies[minindex] = 26;
		}
		DWORD SeedAddr = ReadMemory(4, DATA_ADDR, 1, OFFSET_1) + 0x54d4;
		DWORD ListAddr = ReadMemory(4, DATA_ADDR, 1, OFFSET_1) + 0x6b4;
		for (int i = 0; i < 33; ++i)
		{
			WriteMemory(0, 1, SeedAddr + i);
		}
		for (int i = 0; i < znum; ++i)
		{
			WriteMemory(1, 1, SeedAddr + zombies[i]);
		}
		clear();
		asm_init_zlist();
		RunAsm();
		if (!LowZ)
		{
			for (int i = 0; i < 2000; ++i)
			{
				if (ReadMemory(4, ListAddr + i * 4) == 26)
					WriteMemory(minzid, 4, ListAddr + i * 4);
			}
		}
		if (ReadMemory(4, DATA_ADDR, 1, MODE_OFFSET + 4) == 2)
		{
			clear();
			asm_destroy_model();
			asm_create_model();
			WriteMemory(0x80, 1, 0x0043a153);
			RunAsm();
			WriteMemory(0x85, 1, 0x0043a153);
		}
	}
}
void PVZ_1_0::asm_destroy_model()
{
	mov_exx_dword_ptr(RegType::EBX, DATA_ADDR);
	mov_exx_dword_ptr_exx_add_dword(RegType::EBX, OFFSET_1);
	call(0x0040df70);
}

void PVZ_1_0::asm_create_model()
{
	mov_exx_dword_ptr(RegType::EAX, DATA_ADDR);
	mov_exx_dword_ptr_exx_add_dword(RegType::EAX, OFFSET_1);
	mov_exx_dword_ptr_exx_add_dword(RegType::EAX, 0x15c);
	push_exx(RegType::EAX);
	call(0x0043a140);
}
void PVZ_1_0::LimitSeed(int* zombies, int znum, bool thief, bool red)
{
	if (InGame())
	{
		DWORD buffer[2000];
		memset(buffer, -1, sizeof(buffer));
		bool HasThief = false;
		bool HasRed = false;
		for (int i = 0; i < znum; ++i)
		{
			if (zombies[i] == 20)
				HasThief = true;
			if (zombies[i] == 32)
				HasRed = true;
		}
		int j = 0;
		for (int i = 0; i < 2000; ++i)
		{
			if (HasThief && thief && znum > 1)
			{
				if (i >= 450 && i <= 453
					|| i >= 950 && i <= 953
					|| i >= 1450 && i <= 1453
					|| i >= 1950 && i <= 1953)
				{
					buffer[i] = 20;
					continue;
				}
				if (znum > 1 && zombies[j] == 20)
					++j;
				if (j >= znum)
					j = 0;
			}
			if (HasRed && red && zombies[j] == 32 && znum > 1)
			{
				if (i >= 500 && i <= 950
					|| i >= 1500 && i <= 1950)
					++j;
				if (j >= znum)
					j = 0;
				if (zombies[j] == 20 && thief)
					++j;
				if (j >= znum)
					j = 0;
			}
			buffer[i] = zombies[j++];
			if (j >= znum)
				j = 0;
		}
		DWORD ListAddr = ReadMemory(4, DATA_ADDR, 1, OFFSET_1) + 0x6b4;
		WriteArrayMemory(buffer, ListAddr);
		if (ReadMemory(4, DATA_ADDR, 1, MODE_OFFSET + 4) == 2)
		{
			clear();
			asm_destroy_model();
			asm_create_model();
			WriteMemory(0x80, 1, 0x0043a153);
			RunAsm();
			WriteMemory(0x85, 1, 0x0043a153);
		}
	}
}

void PVZ_1_0::asm_init_seed()
{
	mov_exx_dword_ptr(RegType::EDI, DATA_ADDR);
	mov_exx_dword_ptr_exx_add_dword(RegType::EDI, OFFSET_1);
	add_word(0xc781);
	add_dword(0x54d4);//add edi,0x54d4
	mov_exx(RegType::ECX, 33);
	add_word(0xc030);//xor al,al
	add_byte(0xfc);//cld
	add_word(0xaaf3);// rep stos byte ptr es : [edi]
	mov_exx_dword_ptr(RegType::ESI, DATA_ADDR);
	mov_exx_dword_ptr_exx_add_dword(RegType::ESI, OFFSET_1);
	mov_exx_dword_ptr_exx_add_dword(RegType::ESI, OFFSET_2);
	call(0x00425840);
}

void PVZ_1_0::asm_init_zlist()
{
	mov_exx_dword_ptr(RegType::EDI, DATA_ADDR);
	mov_exx_dword_ptr_exx_add_dword(RegType::EDI, OFFSET_1);
	call(0x004092e0);
}

void PVZ_1_0::ResetSeed()
{
	if (InGame())
	{
		clear();
		asm_init_seed();
		asm_init_zlist();
		if (ReadMemory(4, DATA_ADDR, 1, MODE_OFFSET + 4) == 2)
		{
			asm_destroy_model();
			asm_create_model();
			WriteMemory(0x80, 1, 0x0043a153);
		}
		RunAsm();
		WriteMemory(0x85, 1, 0x0043a153);
	}
}

void PVZ_1_0::SeeLeftZombies(bool(&zombies)[33])
{
	if (InGame())
	{
		DWORD Base = ReadMemory(4, DATA_ADDR, 1, OFFSET_1);
		DWORD WaveCount = ReadMemory(4, Base + 0x5564);
		DWORD CurWave = ReadMemory(4, Base + 0x557c);
		if (WaveCount == 0)
			return;
		DWORD LastAddr = Base + 0x6b4 + (WaveCount - 1) * 200;
		DWORD CurAddr = Base + 0x6b4 + CurWave * 200;
		if (CurWave == 40)
		{
			CurAddr = LastAddr;
		}
		while (CurAddr <= LastAddr)
		{
			for (int i = 0; i < 50; ++i)
			{
				int one = ReadMemory(4, CurAddr + i * 4);
				if (one < 0)
					break;
				else if (one < 33)
					zombies[one] = true;
			}
			CurAddr += 200;
		}
	}
}

void PVZ_1_0::FlowerNPK(bool b)
{
	if (b)
	{
		WriteMemory(0, 1, 0x0051f017);
		WriteMemory(1020, 4, DATA_ADDR, 2, GARDON_OFFSET, 0x1f8);
	}
	else
	{
		WriteMemory(-1, 1, 0x0051f017);
	}
}

void PVZ_1_0::Medicine(bool b)
{
	if (b)
	{
		WriteMemory(0, 1, 0x0051f110);
		WriteMemory(1020, 4, DATA_ADDR, 2, GARDON_OFFSET, 0x1fc);
	}
	else
	{
		WriteMemory(-1, 1, 0x0051f110);
	}
}

void PVZ_1_0::Chocolate(bool b)
{
	if (b)
	{
		WriteMemory(0, 1, 0x0051ec38);
		WriteMemory(0, 1, 0x0051ecb8);
		WriteMemory(1020, 4, DATA_ADDR, 2, GARDON_OFFSET, 0x228);
	}
	else
	{
		WriteMemory(-1, 1, 0x0051ec38);
		WriteMemory(-1, 1, 0x0051ecb8);
	}
}

void PVZ_1_0::TreeNPK(bool b)
{
	if (b)
	{
		WriteMemory(0, 1, 0x0042d463);
		WriteMemory(1020, 4, DATA_ADDR, 2, GARDON_OFFSET, 0x230);
	}
	else
	{
		WriteMemory(-1, 1, 0x0042d463);
	}
}

void PVZ_1_0::TreeHeight(int h)
{
	if (GetMode() == 50)
	{
		WriteMemory(h - 1, 4, DATA_ADDR, 2, GARDON_OFFSET, 0xf4);
		clear();
		mov_exx(RegType::EDI, DATA_ADDR);
		call(0x0042d1f0);
		RunAsm();
	}
	else
		WriteMemory(h, 4, DATA_ADDR, 2, GARDON_OFFSET, 0xf4);
}

void PVZ_1_0::FlowerNum(int n)
{
	WriteMemory(n, 4, DATA_ADDR, 2, GARDON_OFFSET, 0x350);
}

void PVZ_1_0::ChangeFlower(int fid, int type)
{
	WriteMemory(type, 4, DATA_ADDR, 2, GARDON_OFFSET, 0x358 + fid * 0x58);
}

void PVZ_1_0::ChangeFSize(int fid, int size)
{
	WriteMemory(size, 4, DATA_ADDR, 2, GARDON_OFFSET, 0x37c + fid * 0x58);
}

void PVZ_1_0::ChangeFDir(int fid, int dir)
{
	WriteMemory(dir, 4, DATA_ADDR, 2, GARDON_OFFSET, 0x368 + fid * 0x58);
}

void PVZ_1_0::ChangeFPlace(int fid, int place)
{
	WriteMemory(place, 4, DATA_ADDR, 2, GARDON_OFFSET, 0x35c + fid * 0x58);
}

void PVZ_1_0::Patch()
{
	WriteMemory(0x23, 1, 0x00534d01);
	WriteMemory(0x23, 1, 0x005354ba);
}

std::string PVZ_1_0::getUserdataDir(char systemDir)
{
	return PVZ::getUserdataDir(systemDir);
}