#include "Stdinc.h"

typedef struct Info_st
{
	PShot_t *PS;
	int IsRect;

	union
	{
		struct
		{
			double X;
			double Y;
			double R;
		}
		Circle;

		struct
		{
			double L;
			double T;
			double W;
			double H;
		}
		Rect;
	}
	u;
}
Info_t;

static singleton_VTI(InfoList, autoList<Info_t *>, new autoList<Info_t *>())

/*
	ps ÇÕéüÇÃ AllClear Ç‹Ç≈ê∂ë∂ÇµÇƒÇ¢ÇÈÇ±Ç∆ÅB
*/
void PutPShotCrashCircle(PShot_t *ps, double x, double y, double r)
{
	errorCase(!ps);
	errorCase(r < 0.0);

	Info_t *i = nb_(Info_t);

	i->PS = ps;
	i->IsRect = 0;
	i->u.Circle.X = x;
	i->u.Circle.Y = y;
	i->u.Circle.R = r;

	S_InfoList()->AddElement(i);

#if SCOPE_ENABLED
	AddScopeCircle(SCPLAY_PSHOT_CRASH, x, y, r); // TEST
#endif
}
void PutPShotCrashRect(PShot_t *ps, double l, double t, double w, double h)
{
	errorCase(!ps);
	errorCase(w <= 0.0);
	errorCase(h <= 0.0);

	Info_t *i = nb_(Info_t);

	i->PS = ps;
	i->IsRect = 1;
	i->u.Rect.L = l;
	i->u.Rect.T = t;
	i->u.Rect.W = w;
	i->u.Rect.H = h;

	S_InfoList()->AddElement(i);

#if SCOPE_ENABLED
	AddScopeRect(SCPLAY_PSHOT_CRASH, l, t, w, h); // TEST
#endif
}
void AllClearPShotCrashArea(void)
{
	S_InfoList()->Clear((void (*)(Info_t *))memFree);
}
PShot_t *GetCrashedPShot(double x, double y, double r) // ret: NULL == not crashed
{
	errorCase(r < 0.0);

	for(int index = 0; index < S_InfoList()->GetCount(); index++)
	{
		Info_t *i = S_InfoList()->GetElement(index);

		if(i->IsRect == 0) // ? Circle
		{
			double xd = abs(x - i->u.Circle.X);
			double yd = abs(y - i->u.Circle.Y);
			double rd = r + i->u.Circle.R;

			if(
				xd < rd &&
				yd < rd &&
				m_pow(xd) + m_pow(yd) < m_pow(rd)
				)
			{
				return i->PS;
			}
		}
		else // ? Rect
		{
			double x1 = i->u.Rect.L;
			double x2 = i->u.Rect.L + i->u.Rect.W;
			double y1 = i->u.Rect.T;
			double y2 = i->u.Rect.T + i->u.Rect.H;

			double x1r = x1 - r;
			double x2r = x2 + r;
			double y1r = y1 - r;
			double y2r = y2 + r;

			if(
				x1r < x && x < x2r &&
				y1r < y && y < y2r
				)
			{
				int crashed = 0;

				if(
					x1 <= x && x <= x2 ||
					y1 <= y && y <= y2
					)
				{
					crashed = 1;
				}
				else
				{
					double xe;
					double ye;

					if(x < x1 + x2 / 2.0)
						xe = x1;
					else
						xe = x2;

					if(y < y1 + y2 / 2.0)
						ye = y1;
					else
						ye = y2;

					double xd = abs(x - xe);
					double yd = abs(y - ye);

					if(m_pow(xd) + m_pow(yd) < m_pow(r))
						crashed = 1;
				}
				if(crashed)
				{
					return i->PS;
				}
			}
		}
	}
	return NULL; // not found
}
