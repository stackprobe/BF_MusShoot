#include "Stdinc.h"

EnemyCommonData_t *CreateEnemyCommonData(void) // ret: dummy ecd
{
	return CreateEnemyCommonData(0.0, 0);
}
EnemyCommonData_t *CreateEnemyCommonData(
	double haichiX,
	int start_hp
	)
{
	EnemyCommonData_t *i = nb(EnemyCommonData_t);

	m_range(haichiX, (double)ENEMY_X_MIN, (double)ENEMY_X_MAX);
	m_range(start_hp, -1, IMAX);

	i->HaichiX = haichiX;
	i->StartHP = start_hp;

	return i;
}
EnemyCommonData_t *CreateEnemyCommonData(autoList<char *> *lines)
{
	return CreateEnemyCommonData(
		PL_ReadDouble(lines, 0, 32.0),
		PL_ReadInt(lines, 1, -1)
		);
}
void ReleaseEnemyCommonData(EnemyCommonData_t *i)
{
	memFree(i);
}

// <== ECD

Enemy_t *CreateEnemy_ved(
	int (*funcProc)(Enemy_t *, void *),
	void (*funcDraw)(Enemy_t *, void *),
	void (*funcRelease)(void *),
	int hp,
	EnemyCommonData_t *commonData,
	void *extraData
	)
{
	Enemy_t *i = nb(Enemy_t);

	errorCase(!funcProc);
	errorCase(!funcDraw);

	if(!funcRelease)
		funcRelease = memFree;

	ec_range(hp, 0, IMAX);
	errorCase(!commonData);
	errorCase(!extraData);

	i->ProcFunc = funcProc;
	i->DrawFunc = funcDraw;
	i->ReleaseFunc = funcRelease;
	i->HP = hp;
	i->CommonData = commonData;
	i->ExtraData = extraData;

	// ! X, Y は 0.0 のまま。

	return i;
}
void ReleaseEnemy(Enemy_t *i)
{
	if(!i)
		return;

	ReleaseEnemyCommonData(i->CommonData);
	i->ReleaseFunc(i->ExtraData);
	memFree(i);
}

void GmProcEnemy(void)
{
	for(int index = 0; index < GmDc.EnemyList->GetCount(); index++)
	{
		Enemy_t *e = GmDc.EnemyList->GetElement(index);

		// reset {
		e->PicInfo.Enabled = 0;
		// }

		// ? death || out of rect
		if(
			e->ProcFunc(e, e->ExtraData) == 0 ||
			e->X < ENEMY_X_MIN || ENEMY_X_MAX < e->X ||
			e->Y < ENEMY_Y_MIN || ENEMY_Y_MAX < e->Y
			)
		{
			ReleaseEnemy(GmDc.EnemyList->FastDesertElement(index));
			index--;
		}
		else
		{
			e->Frame++;
			m_countDown(e->CrashFrame);
		}
	}
}
void GmDrawEnemy(int wall_mode)
{
	for(int index = 0; index < GmDc.EnemyList->GetCount(); index++)
	{
		Enemy_t *e = GmDc.EnemyList->GetElement(index);

		if(!e->Frame) // Proc前の敵を表示しない。
			continue;

		if(IsWall(e) ? !wall_mode : wall_mode) // ? IsWall() != wall_mode
			continue;

		e->Frame--; // Proc時のフレームにする。
		e->DrawFunc(e, e->ExtraData);
		e->Frame++; // 戻す。
	}
}

void PutEnemyPicInfo(Enemy_t *e, int picResno, double x, double y, double r, double z)
{
	errorCase(!e);
	errorCase(picResno & DTP); // Der() のシルエットはないよ。

	e->PicInfo.Enabled = 1;
	e->PicInfo.PicResno = picResno;
	e->PicInfo.X = x;
	e->PicInfo.Y = y;
	e->PicInfo.R = r;
	e->PicInfo.Z = z;
}
void PutEnemyCrashAreaByPI(Enemy_t *e)
{
	errorCase(!e);
	errorCase(!e->PicInfo.Enabled);

	EnemyPicInfo_t *epi = GetEnemyPicInfo(e->PicInfo.PicResno);

	PutEnemyCrashArea(
		e,
		epi->STSilhouette,
		e->PicInfo.X,
		e->PicInfo.Y,
		e->PicInfo.R,
		e->PicInfo.Z
		);
}
void DrawEnemyByPI(Enemy_t *e)
{
	errorCase(!e);
	errorCase(!e->PicInfo.Enabled);

	DrawBegin(
		e->PicInfo.X,
		e->PicInfo.Y,
		Pic(e->PicInfo.PicResno)
		);
	DrawRotate(e->PicInfo.R);
	DrawZoom(e->PicInfo.Z);
	DrawEnd();
}
int ProcPShotEnemyCrash(Enemy_t *e, double x, double y, double r) // ? e 生存
{
	errorCase(!e);
	errorCase(r < 0.0);

	if(!e->HP) // ? 無敵
		return 1;

#if SCOPE_ENABLED
	AddScopeCircle(SCPLAY_PS_ENEMY_CRASH, x, y, r);
#endif

	PShot_t *ps = GetCrashedPShot(x, y, r);

	if(ps) // ? 被弾した。
	{
		PShotEnemyCrash_Action(ps, e);
	}
	return e->HP ? 1 : 0;
}
int ProcPShotEnemyCrashByPI(Enemy_t *e, double zoom) // ? e 生存
{
	errorCase(!e);
	errorCase(!e->PicInfo.Enabled);

	bitTable *silhouette = GetEnemyPicInfo(e->PicInfo.PicResno)->Silhouette;
	double r = silhouette->GetWidth(); // ! 幅を使う。

	r /= 2.0;
	r *= e->PicInfo.Z;
	r *= zoom;

	return ProcPShotEnemyCrash(e, e->PicInfo.X, e->PicInfo.Y, r);
}

static Enemy_t *Prv_LoadEnemy(MapCellData_t *mcd) // ret: NULL == ロードされなかった。
{
	EnemyCommonData_t *ecd = CreateEnemyCommonData(mcd->CommonParamLines);
	Enemy_t *e = NULL;

	switch(atoi(mcd->TopLine))
	{
	case 0:
		e = CreateEnemy(
			EProc_Wall,
			EDraw_Wall,
			ReleaseED_Wall,
			0, ecd,
			CreateED_Wall(mcd->ParamLines)
			);
		break;

	case 1:
		GmDc.ScrollSpeed = PL_ReadDouble(mcd->ParamLines, 0, 0.0);
		break;

	case 2:
		e = CreateEnemy(
			EProc_Fei,
			EDraw_Fei,
			ReleaseED_Fei,
			1, ecd,
			CreateED_Fei(mcd->ParamLines)
			);
		break;

	case 3:
		e = CreateEnemy(
			EProc_Hikaru,
			EDraw_Hikaru,
			ReleaseED_Hikaru,
			1, ecd,
			CreateED_Hikaru(mcd->ParamLines)
			);
		break;

	case 4:
		e = CreateEnemy(
			EProc_Lina,
			EDraw_Lina,
			ReleaseED_Lina,
			1, ecd,
			CreateED_Lina(mcd->ParamLines)
			);
		break;

	case 5:
		e = CreateEnemy(
			EProc_Ningyo,
			EDraw_Ningyo,
			ReleaseED_Ningyo,
			1, ecd,
			CreateED_Ningyo(mcd->ParamLines)
			);
		break;

	default:
		break;
	}
	if(e)
	{
		if(ecd->StartHP != -1) // デフォルトを使用しない。
			e->HP = ecd->StartHP;

		ec_range(e->HP, 0, IMAX);
	}
	else
		ReleaseEnemyCommonData(ecd);

	return e;
}

void LoadMapEnemyData(autoList<Enemy_t *> *outList, autoList<MapCellData_t *> *list)
{
	for(int index = 0; index < list->GetCount(); index++)
	{
		MapCellData_t *mcd = list->GetElement(index);

		outList->AddElement(mcd ? Prv_LoadEnemy(mcd) : NULL);
	}
}
void AddEnemy(double x, double y, Enemy_t *e)
{
	errorCase(!e);

	// 2bs {
	m_range(x, ENEMY_X_MIN, ENEMY_X_MAX);
	m_range(y, ENEMY_Y_MIN, ENEMY_Y_MAX);
	// }

	e->X = x;
	e->Y = y;

	GmDc.EnemyList->AddElement(e);
}
void TamaCleanup(void)
{
	for(int index = 0; index < GmDc.EnemyList->GetCount(); index++)
	{
		Enemy_t *e = GmDc.EnemyList->GetElement(index);

		if(EProcIs(e, EProc_EShot)) // ? 弾 -> 消去
		{
			ReleaseEnemy(GmDc.EnemyList->FastDesertElement(index));
			index--;
		}
	}
}
