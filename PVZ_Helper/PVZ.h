#pragma once

#include "Process.h"
#include "Asm.h"
#include <vector>
#include <string>

#define _call(addr)	\
	call $ + 7}\
	_asm{_emit 0xeb}\
	_asm{_emit 6}\
	_asm{push addr}\
	_asm{ret

#define _jmp(addr)	\
	push addr}\
	_asm{ret

#define _j(flag, addr) \
	_emit flag}\
	_asm{_emit 6}\
	_asm{_jmp(addr)

#define GET_ADDR(f)	(unsigned char*)f
#define HEAD_OF(f)	(*GET_ADDR(f) == 0xeb ? 2 : 5)
#define SIZE_OF(f)	(*GET_ADDR(f) == 0xeb ? *(GET_ADDR(f)+1) : *(unsigned int*)(GET_ADDR(f)+1))

#define DECLARE_PUBLIC	\
	virtual bool InGame();\
	virtual int	 GetMode();\
	virtual void SetSun(int);\
	virtual void SetBackground(int);\
	virtual void SetMoney(int);\
	virtual void LockCar(bool);\
	virtual void NoCar(bool);\
	virtual void Hammering(bool);\
	virtual void Bungee(bool);\
	virtual void GraveMode(bool);\
	virtual void SetAdNum(int);\
	virtual void SetChomper(int);\
	virtual void SetFumeShroom(int);\
	virtual void SetZeng(int);\
	virtual void SunMore(bool);\
	virtual void MoneyMore(bool);\
	virtual void IgnoreSun(bool);\
	virtual void AutoPickup(bool);\
	virtual void StartCar();\
	virtual void ResetCar();\
	virtual void NoPause(bool);\
	/*virtual void PutRake(int row, int col);*/\
	virtual void NoDelete(bool);\
	virtual void NoSave(bool);\
	virtual void AlienZombies(bool);\
	virtual void FuckFaster(bool);\
	virtual void EatHouse(bool);\
	virtual void Anywhere(bool);\
	virtual void FastBelt(bool);\
	virtual void ShowHide(bool);\
	virtual void FullFog(bool);\
	virtual void SeeFog(bool);\
	virtual void SeeVase(bool);\
	virtual void JmpLevel(int);\
	virtual void MixMode(int mode, int level = 0);\
	virtual void Unlock(bool);\
	virtual void Win();\
	virtual void Lock(bool,int = 0);\
	virtual void Little(bool);\
	virtual void Rain(bool);\
	virtual void Storm(bool);\
	virtual void ShowShovel(bool);\
	virtual void CardFlicker(bool);\
	virtual void OneCardStart(bool);\
	virtual void ForceCard(bool);\
	virtual void NoGrave(bool);\
	virtual void SetWoGua(int num);\
	virtual void SetPlantsRoleGarlic(bool);\
	virtual void SetPlantsRoleRadish(bool);\
	virtual void JumpZomMax(bool);\
	virtual void PaperNoAngry(bool);\
	virtual void FastSpeed(bool);\
	virtual void FastSpeedMax(bool);\
	virtual void NoSeePlants(bool);\
	virtual void BuPaSanYe(bool);\
	virtual void ConterMarch(bool);\
	virtual void DancerFunny(bool);\
	virtual void Force(bool);\
	virtual void LikeCol(bool);\
	virtual void RunFast(bool);\
	virtual void SetCardNum(int);\
	virtual void SetCard(int cid, int type, bool copy = false);\
	virtual void FSBoom(bool);\
	virtual void SetPlantsRoleFriendly(bool);\
	virtual void SetPlantsRoleIce(bool);\
	virtual void SetPlantsRoleWoGua(bool);\
	virtual void SetPlantsRoleBoomMax(bool);\
	virtual void PlantsAllRed(bool);\
	virtual void PlantsAllGreen(bool);\
	virtual void ChNotKill(bool);\
	virtual void NowMouse(int mouse);\
	virtual void ChKiller(bool);\
	virtual void PlantsPaper(bool);\
	virtual void CheatMode(bool);\
	virtual void FirePea(int Pea,int IcePea);\
	virtual void PlantsZipBoom(bool);\
	virtual void FunnyNut(bool);\
	virtual void CrazyPlants(bool);\
	virtual void KillAllPlants();\
	virtual void ChHitNum(int num);\
	virtual void MeiHuoHanBingGu(bool);\
	virtual void HuangYouHanBingGu(bool);\
	virtual void BossLife(int life);\
	virtual void SetZombieTimer(int time);\
	virtual void ShowHeadTimer(int time);\
	virtual void MaxSun(int sun);\
	virtual void SetPlantValue(int plant,int value);\
	virtual void SetPlantTime(int plant,int value);\
	virtual void MaxMoney(int money);\
	virtual void ShopPrice(int item,int price);\
	virtual void PlantSetSpeed(int plant,int speed);\
	virtual void PlantSetHealthy(int plant,int healthy);\
	virtual void SetItemValue(int item,int value);\
	virtual void FSSquash(bool);\
	virtual void TheWorld(bool);\
	virtual void FSMagnet(bool);\
	virtual void FSSputter(bool);\
	virtual void FSMouth(bool);\
	virtual void FuckingZombieDamageType(int type);\
	virtual void PeaZombieDamageType(int type);\
	virtual void bulletStraight(bool);\
	virtual void PlantsAllBlack(bool);\
	virtual void MoneyFlowerChange(int num1 , int num2 , int num1gailv);\
	virtual void FSPrick(bool);\
	virtual void baolingqiu(bool);\
	virtual void CatHack(bool);\
	virtual void BombWallnut(bool);\
	virtual void BackWallnut(bool);\
	virtual void FastWallnut(bool);\
	virtual void IMPFallDie(bool);\
	virtual void NormalOKSun(int sun);\
	virtual void FirstOKSun(int sun);\
	virtual void BigWallnut(bool);\
	virtual void TheWorld2(bool);\
	virtual void BiaoBaZom(bool);\
	virtual void GaGangBuReng(bool);\
	virtual void OKRengIMP(bool);\
	virtual void FastBigZom(bool);\
	virtual void SlowIMP(bool);\
	virtual void BulletDamage(int bullet,int damage);\
	virtual void ProTime(int pro,int value);\
	virtual void FSSpout(bool);\
	virtual void FSCat(bool);\
	virtual void CatTouch(bool);\
	virtual void InitExtraCode();\
	virtual void StartDoor(bool);\
	virtual void StableDoor(bool);\
	virtual void SetDoor(int b1r, int b1c, int b2r, int b2c, int w1r, int w1c, int w2r, int w2c);\
	virtual void CornNoWait(bool);\
	virtual void MagnetNoWait(bool);\
	virtual void PotatoNoWait(bool);\
	virtual void MouthNoWait(bool);\
	virtual void PStrong();\
	virtual void PNormal();\
	virtual void PWeak();\
	virtual void NoMark(bool);\
	virtual void NoSleep(bool);\
	virtual void StrongWind(bool);\
	virtual void StrongBean(bool);\
	virtual void Umbrella(bool);\
	virtual void NoCD(bool);\
	virtual void LockScoop(bool);\
	virtual void AnyMove(bool);\
	virtual void NoPurple(bool);\
	virtual void LockButter(bool);\
	virtual void LockCorn(bool);\
	virtual void BoomIm();\
	virtual void BoomNormal();\
	virtual void BoomNever();\
	virtual void VisiableNo();\
	virtual void VisiableNormal();\
	virtual void VisiableYes();\
	virtual void ZStrong();\
	virtual void ZNormal();\
	virtual void ZWeak();\
	virtual void NoSlow(bool);\
	virtual void NoButter(bool);\
	virtual void No3zGroup(bool);\
	virtual void NoIMP(bool);\
	virtual void NoICE(bool);\
	virtual void ZEatable(bool);\
	virtual void StopZTimer(bool);\
	virtual void StopZombies(bool);\
	virtual void StopBoss(bool);\
	virtual void BalloonBoom(bool);\
	virtual void ZTimerSpeed(int);\
	virtual void GatherZombie(bool, float = 0.0f);\
	virtual void KillAllZombies();\
	virtual void ConfuseZombies();\
	virtual void BlackAllZombies();\
	virtual void VoidAllZombies();\
	virtual void ZLife(int type,int life);\
	virtual void ZALife(int type,int life);\
	virtual void ZHit(int type,int hit);\
	virtual void FastGetPlant(bool);\
	virtual void BungeeStop(bool);\
	virtual void BungeeFunny(bool);\
	virtual void GraveSpawnZCD(int CD);\
	virtual void GraveSpawnZCT(int CT);\
	virtual void GraveSpawnZSP(int SP);\
	virtual void GraveSpawnCT(int CT);\
	virtual void SporeShoot(bool);\
	virtual void LightPlants(bool);\
	virtual void InvShoot(bool);\
	virtual void SlowShoot(bool);\
	virtual void FastSun(bool);\
	virtual void ThisPult(bool);\
	virtual void FastPult(bool);\
	virtual void FastSqa(bool);\
	virtual void FunnySqa(bool);\
	virtual void jumpingSqa(bool);\
	virtual void GrassPlant(bool);\
	virtual void InvBull(bool);\
	virtual void FastBungee(bool);\
	virtual void FastGar(bool);\
	virtual void StuckIMP(bool);\
	virtual void LevelState(int state);\
	virtual void StandSmash(bool);\
	virtual void StraightSmash(bool);\
	virtual void FullSmash(bool);\
	virtual void HitBeLight(bool);\
	virtual void HitNoLight(bool);\
	virtual void NoBroken(bool);\
	virtual void HitBroken(bool);\
	virtual void DeadNoHead(bool);\
	virtual void VoidEat(bool);\
	virtual void VoidWalk(bool);\
	virtual void LongEat(bool);\
	virtual void LJNormalZ(bool);\
	virtual void FaGuoZom(bool);\
	virtual void CantSeeZoms(bool);\
	virtual void NaturalSeed(int* zombies, int znum);\
	virtual void LimitSeed(int* zombies, int znum, bool thief, bool red);\
	virtual void ResetSeed();\
	virtual void SeeLeftZombies(bool(&zombies)[33]);\
	virtual void FlowerNPK(bool);\
	virtual void HighIMP(bool);\
	virtual void LongIMP(bool);\
	virtual void ShitIMP(bool);\
	virtual void VoidIMP(bool);\
	virtual void HomeIMP(bool);\
	virtual void Medicine(bool);\
	virtual void Chocolate(bool);\
	virtual void TreeNPK(bool);\
	virtual void TreeHeight(int);\
	virtual void FlowerNum(int);\
	virtual void ChangeFlower(int fid, int type);\
	virtual void ChangeFSize(int fid, int size);\
	virtual void ChangeFDir(int fid, int dir);\
	virtual void ChangeFPlace(int fid, int place);\
	virtual void Patch();\
	virtual void RunAsm();\
	virtual void GetPlants();\
	virtual void GetCars();\
	virtual void GetItems();\
	virtual void GetZombies();\
	virtual int GetMapType();\
	virtual int GetBlockType(int row, int col);/*1.草地2.裸地3.水池*/\
	virtual void SetBlockType(int row, int col, int type);/*1.草地2.裸地3.水池*/\
	virtual int GetRowType(int row);/*0.不出怪1.草地2.水路*/\
	virtual void SetRowType(int row, int type);/*0.不出怪1.草地2.水路*/\
	virtual std::string getUserdataDir(char systemDir);\


#define DECLARE_PRIVATE	\
	virtual void asm_plant(int row, int col, int type, bool copy);\
	virtual void asm_plant_paper(int row, int col, int type);\
	virtual void asm_put_zombie(int row, int col, int type);\
	virtual void asm_put_boss();\
	virtual void asm_put_ladder(int row, int col);\
	virtual void asm_put_grave(int row, int col);\
	virtual void asm_create_model();\
	virtual void asm_destroy_model();\
	virtual void asm_init_seed();\
	virtual void asm_init_zlist();\


struct Plant
{
	DWORD addr;
	int Row;
	int Col;
	int Type;
	bool Sleeping;
};

struct Item
{
	DWORD addr;
	int Row;
	int Col;
	int Type;
};

struct Car
{
	DWORD addr;
	int Row;
};

struct Zombie
{
	DWORD addr;
	int Row;
	int Type;
};


class PVZ : protected Process, protected Asm
{
public:
	PVZ(const Process& p) : Process(p), Asm(4) {}
	void SetBlocks(int row, int col, int type);
	int GetRowCount();
	int GetColCount();
	void Planting(int row, int col, int type, bool copy);
	void PutZombie(int row, int col, int type);
	void PutLadder(int row, int col);
	void PutGrave(int row, int col);
	void AutoLadder();
	std::string getUserdataDirXP();
	DECLARE_PUBLIC
protected:
	std::vector<Plant> vp;
	std::vector<Item> vi;
	std::vector<Car> vc;
	std::vector<Zombie> vz;

	struct ExtraCodeAddr
	{
		DWORD Row;
		DWORD Col;
		DWORD RHurt;
		DWORD CHurt;
		DWORD CatR;
		DWORD CatC;
		DWORD Throw;
		DWORD CatDir;
		DWORD Split;
		DWORD ZTimer;
		DWORD Thread;
	}eCode;
private:
	DECLARE_PRIVATE
};

