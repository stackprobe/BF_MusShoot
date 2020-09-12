#include "Stdinc.h"

typedef struct Info_st
{
	PShot_t *PS;
	double X;
	double Y;
}
Info_t;

static singleton_VTI(InfoList, autoList<Info_t *>, new autoList<Info_t *>())

/*
	ps ‚ÍŽŸ‚Ì AllClear ‚Ü‚Å¶‘¶‚µ‚Ä‚¢‚é‚±‚ÆB
*/
void PutPShotWallCrash(PShot_t *ps, double x, double y)
{
	Info_t *i = nb_(Info_t);

	i->PS = ps;
	i->X = x;
	i->Y = y;

	S_InfoList()->AddElement(i);

#if SCOPE_ENABLED
	AddScopePoint(SCPLAY_PS_WALL_CRASH, i->X, i->Y);
#endif
}
void AllClearPShotWallCrash(void)
{
	S_InfoList()->Clear((void (*)(Info_t *))memFree);
}

static void Crash_Action(PShot_t *ps, double x, double y)
{
	int crashed = 0;

	switch(ps->PShTyp)
	{
	case PST_MIRACLE:
		{
			GTACE_BlendAddMode = 1;
			GTAddCommonEffect_ZR(
				GmDc.EffectList,
				P_NEWMIRACLE_SPARK_00 + rnd(8),
				0,
				2,
				x, y, 1.0 + 2.0 * dRnd(), 0.0, 0.75
				);
			GTACE_BlendAddMode = 0;

			crashed = 1;
		}
		break;

	case PST_ROCK:
		{
			int wcr = 0;

			if(
				x < ps->X && ps->u.Rock.XAdd < 0.0 ||
				x > ps->X && ps->u.Rock.XAdd > 0.0
				)
			{
				wcr = 1;
				ps->u.Rock.XAdd *= -1.0;
			}
			else if(
				y < ps->Y && ps->u.Rock.YAdd < 0.0 ||
				y > ps->Y && ps->u.Rock.YAdd > 0.0
				)
			{
				wcr = 1;
				ps->u.Rock.YAdd *= -1.0;
			}

			if(wcr)
			{
				if(ps->u.Rock.HaneRemCnt)
				{
					GTACE_BlendAddMode = 1;
					GTACE_PicResnoIncDelay = 1;
					GTACE_PicResnoEnd = P_NEWSHOT_DEATH_00 + 8;
					GTAddCommonEffect_ZR(
						GmDc.EffectList,
						P_NEWSHOT_DEATH_00,
						1,
						0,
						x, y, 0.3
						);
					GTACE_Reset();

					ps->u.Rock.HaneRemCnt--;
				}
				else
					crashed = 1;
			}
		}
		break;

	case PST_DBL_BOUNCE:
		{
			double xa = cos(ps->R);
			double ya = sin(ps->R);

			int wcr = 0;

			if(
				x < ps->X && xa < 0.0 ||
				x > ps->X && xa > 0.0
				)
			{
				wcr = 1;
				xa *= -1.0;
			}
			else if(
				y < ps->Y && ya < 0.0 ||
				y > ps->Y && ya > 0.0
				)
			{
				wcr = 1;
				ya *= -1.0;
			}

			if(wcr)
			{
				ps->R = P2Angle(0.0, 0.0, xa, ya);

				if(ps->u.Double.BounceRemCnt)
				{
					GTACE_BlendAddMode = 1;
					GTACE_PicResnoIncDelay = 1;
					GTACE_PicResnoEnd = P_NEWSHOT_DEATH_00 + 8;
					GTAddCommonEffect_ZR(
						GmDc.EffectList,
						P_NEWSHOT_DEATH_00,
						1,
						0,
						x, y, 0.3
						);
					GTACE_Reset();

					ps->u.Double.BounceRemCnt--;
				}
				else
					crashed = 1;
			}
		}
		break;

	default: // other
		crashed = 1;
		break;
	}
	ps->Crashed = crashed ? 2 : 0;
}

void CheckPShotWallCrash(void)
{
	for(int index = 0; index < S_InfoList()->GetCount(); index++)
	{
		Info_t *i = S_InfoList()->GetElement(index);
		Enemy_t *e = GetCrashedEnemy(i->X, i->Y, 1);

		if(IsWall(e))
		{
			Crash_Action(i->PS, i->X, i->Y);
		}
	}
}
