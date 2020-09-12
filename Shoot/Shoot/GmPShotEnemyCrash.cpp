#include "Stdinc.h"

static void EnemyDeath(Enemy_t *e)
{
	if(EProcIs(e, EProc_Ningyo)) // l‹›‚³‚ñ
	{
		AddEnemy(e->X, e->Y, CreateEnemy(
			EProc_NingyoDead,
			EDraw_NingyoDead,
			ReleaseED_NingyoDead,
			0, CreateEnemyCommonData(),
			CreateED_NingyoDead()
			));

		return;
	}

	if(e->PicInfo.Enabled)
	{
		double z = GetEnemyPicInfo(e->PicInfo.PicResno)->Width / 50.0;

		GTACE_BlendAddMode = 1;
		GTACE_PicResnoIncDelay = 1;
		GTACE_PicResnoEnd = P_ENEMY_DEATH_00 + 10;
		GTAddCommonEffect_ZR(
			GmDc.EffectList,
			P_ENEMY_DEATH_00,
			1,
			0,
			e->X, e->Y, z, 0.0, 1.0
			);
		GTACE_Reset();
	}
	else
	{
		// dummy
		GTAddCommonEffect_ZR(
			GmDc.EffectList,
			P_DUMMY,
			0,
			10,
			e->X, e->Y, 1.0, 0.0, 1.0
			);
	}
}
void PShotEnemyCrash_Action(PShot_t *ps, Enemy_t *e)
{
	errorCase(!ps);
	errorCase(!e);
	errorCase(!e->HP); // ? –³“G

	if(e->CrashFrame) // ? â^ƒNƒ‰ƒbƒVƒ…’† -> –³“G
		return;

	e->HP--;

	if(!e->HP) // dead
		EnemyDeath(e);
	else
		e->CrashFrame = 5;

	ps->Crashed = 1;
}
