#include "Stdinc.h"

typedef struct EWCPoint_st
{
	Enemy_t *Enemy;
	double X;
	double Y;
}
EWCPoint_t;

static singleton_VTI(EWCPointList, autoList<EWCPoint_t>, new autoList<EWCPoint_t>())

void EWC_AddPoint(Enemy_t *e, double x, double y)
{
	EWCPoint_t ewcp;

	ewcp.Enemy = e;
	ewcp.X = x;
	ewcp.Y = y;

	S_EWCPointList()->AddElement(ewcp);
}

static void Crash_Action(Enemy_t *e, double x, double y)
{
	e->Crashed = 1;
}

void CheckEnemyWallCrash(void)
{
	for(int index = 0; index < S_EWCPointList()->GetCount(); index++)
	{
		EWCPoint_t *ewcp = S_EWCPointList()->ElementAt(index);
		Enemy_t *wall_e = GetCrashedEnemy(ewcp->X, ewcp->Y, 1);

		if(IsWall(wall_e))
		{
			Crash_Action(ewcp->Enemy, ewcp->X, ewcp->Y);
		}
	}
}
void AllClearEnemyWallCrash(void)
{
	S_EWCPointList()->Clear();
}
