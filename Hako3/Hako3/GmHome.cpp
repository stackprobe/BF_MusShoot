#include "Stdinc.h"

GmDataCenter_t GmDc;
GmResultCenter_t GmRc;

void GmResetDataCenter(void)
{
	static int inited;

	if(!inited)
		goto init;

	// ---- uninit ----

	GmDc.BackMapData->CallAllElement(ReleaseMapCellData);
	GmDc.FrontMapData->CallAllElement(ReleaseMapCellData);
	GmDc.BackMapEnemyData->CallAllElement(ReleaseEnemy);
	GmDc.FrontMapEnemyData->CallAllElement(ReleaseEnemy);

	delete GmDc.BackMapData;
	delete GmDc.FrontMapData;
	delete GmDc.BackMapEnemyData;
	delete GmDc.FrontMapEnemyData;

	errorCase(GmDc.PShotList->GetCount()); // 2bs
	errorCase(GmDc.EnemyList->GetCount()); // 2bs

	delete GmDc.PShotList;
	delete GmDc.EnemyList;

	ReleaseTaskGroup(GmDc.EffectList_BS);
	ReleaseTaskGroup(GmDc.EffectList_BW);
	ReleaseTaskGroup(GmDc.EffectList_BP);
	ReleaseTaskGroup(GmDc.EffectList_BE);
	ReleaseTaskGroup(GmDc.EffectList);

	// ---- init ----

	/*
		配列など領域の確保と整地だけ行う。
		固定の初期値の設定のみ行う。
		具体的な値の設定は GmMain() の最初で行う。
	*/

init:
	memset(&GmDc, 0x00, sizeof(GmDc));

	GmDc.BackMapData = new autoList<MapCellData_t *>();
	GmDc.FrontMapData = new autoList<MapCellData_t *>();
	GmDc.BackMapEnemyData = new autoList<Enemy_t *>();
	GmDc.FrontMapEnemyData = new autoList<Enemy_t *>();

	GmDc.Player.X = (double)SCREEN_CENTER_X;
	GmDc.Player.Y = (double)SCREEN_CENTER_Y;

	GmDc.Player.CantDir = 5;

	GmDc.PShotList = new autoList<PShot_t *>();
	GmDc.EnemyList = new autoList<Enemy_t *>();

	GmDc.EffectList_BS = CreateTaskGroup();
	GmDc.EffectList_BW = CreateTaskGroup();
	GmDc.EffectList_BP = CreateTaskGroup();
	GmDc.EffectList_BE = CreateTaskGroup();
	GmDc.EffectList = CreateTaskGroup();

	inited = 1;
}
void GmResetResultCenter(void)
{
	static int inited;

	if(!inited)
		goto init;

	// ---- uninit ----

	// ---- init ----

init:
	memset(&GmRc, 0x00, sizeof(GmRc));

	inited = 1;
}

void GmHome(void)
{
	GmResetResultCenter();
	GmMain();
	GmResetDataCenter();
}
