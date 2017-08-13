#include "Stdinc.h"

typedef struct Info_st
{
	Enemy_t *Enemy;
	bitSubTable *Silhouette;
	double X;
	double Y;
	double R;
	double Z;
}
Info_t;

static singleton_VTI(InfoList, autoList<Info_t *>, new autoList<Info_t *>())

/*
	e ÇÕéüÇÃ AllClear Ç‹Ç≈ê∂ë∂ÇµÇƒÇ¢ÇÈÇ±Ç∆ÅB
*/
void PutEnemyCrashArea(Enemy_t *e, bitSubTable *silhouette, double x, double y, double r, double z)
{
	errorCase(!silhouette);
	errorCase(z <= 0.0);

	Info_t *i = nb(Info_t);

	i->Enemy = e;
	i->Silhouette = silhouette;
	i->X = x;
	i->Y = y;
	i->R = r;
	i->Z = z;

	S_InfoList()->AddElement(i);
}
void AllClearEnemyCrashArea(void)
{
	S_InfoList()->Clear((void (*)(Info_t *))memFree);
}
Enemy_t *GetCrashedEnemy(double x, double y, int wallOnlyMode) // ret: NULL == not crashed
{
	for(int index = 0; index < S_InfoList()->GetCount(); index++)
	{
		Info_t *i = S_InfoList()->GetElement(index);

		if(wallOnlyMode && !IsWall(i->Enemy))
			continue;

		double xd = x - i->X;
		double yd = y - i->Y;

		if(abs(xd) < i->Silhouette->HD && abs(yd) < i->Silhouette->HD)
		{
			double r = P2Angle(0, 0, xd, yd);
			double z = sqrt(m_pow(xd) + m_pow(yd));

			r -= i->R;
			z /= i->Z;

			double rx = cos(r) * z;
			double ry = sin(r) * z;

			int sx = m_d2i(rx) + i->Silhouette->GetWidth() / 2;
			int sy = m_d2i(ry) + i->Silhouette->GetHeight() / 2;

			if(i->Silhouette->RefBit(sx, sy))
			{
				return i->Enemy;
			}
		}
	}
	return NULL; // not found
}
